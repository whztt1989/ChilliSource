//
//  The MIT License (MIT)
//
//  Copyright (c) 2016 Tag Games Limited
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//

#include <ChilliSource/Rendering/Base/ForwardRenderPassCompiler.h>

#include <ChilliSource/Core/Threading/TaskScheduler.h>
#include <ChilliSource/Rendering/Base/ForwardRenderPasses.h>
#include <ChilliSource/Rendering/Base/RenderFrame.h>
#include <ChilliSource/Rendering/Base/RenderObject.h>
#include <ChilliSource/Rendering/Base/RenderPass.h>
#include <ChilliSource/Rendering/Base/RenderPassObject.h>
#include <ChilliSource/Rendering/Base/RenderPassObjectSorter.h>
#include <ChilliSource/Rendering/Base/RenderPassVisibilityChecker.h>
#include <ChilliSource/Rendering/Model/RenderDynamicMesh.h>


namespace ChilliSource
{
    namespace
    {
        constexpr u32 k_reservedRenderPasses = 2; // Base + Transparent
        constexpr u32 k_targetRenderPassGroups = 1; // Main
        
        /// Converts the given RenderObject to a RenderPassObject using the given RenderMaterial.
        /// if the given RenderMaterial does not exist in the RenderMaterialGroup contained by
        /// the RenderObject, then this will assert.
        ///
        /// @param renderObject
        ///     The renderObject to convert.
        /// @param renderMaterial
        ///     The render material that should be used by the new RenderPassObject.
        ///
        /// @return The new RenderPassObject.
        ///
        RenderPassObject ConvertToRenderPassObject(const RenderObject& renderObject, const RenderMaterial* renderMaterial) noexcept
        {
            CS_ASSERT(renderObject.GetRenderMaterialGroup()->Contains(renderMaterial), "Invalid render material.");
            
            switch (renderObject.GetType())
            {
                case RenderObject::Type::k_static:
                    return RenderPassObject(renderMaterial, renderObject.GetRenderMesh(), renderObject.GetWorldMatrix(), renderObject.GetBoundingSphere());
                case RenderObject::Type::k_dynamic:
                    return RenderPassObject(renderMaterial, renderObject.GetRenderDynamicMesh(), renderObject.GetWorldMatrix(), renderObject.GetBoundingSphere());
                default:
                    CS_LOG_FATAL("Invalid RenderObject type.");
                    return RenderPassObject(nullptr, reinterpret_cast<const RenderMesh*>(NULL), Matrix4::k_identity, Sphere());
            }
        }
        
        /// Returns the vertex format of the given render object.
        ///
        /// @param renderObject
        ///     The render object.
        ///
        /// @return The vertex format.
        ///
        const VertexFormat& GetVertexFormat(const RenderObject& renderObject)
        {
            switch (renderObject.GetType())
            {
                case RenderObject::Type::k_static:
                    return renderObject.GetRenderMesh()->GetVertexFormat();
                case RenderObject::Type::k_dynamic:
                    return renderObject.GetRenderDynamicMesh()->GetVertexFormat();
                default:
                    CS_LOG_FATAL("Invalid RenderObject type.");
                    return renderObject.GetRenderMesh()->GetVertexFormat();
            }
        }
        
        /// Filters the given list of objects to return only the objects which are a part of the requested
        /// layer.
        ///
        /// @param renderLayer
        ///     The render layer to filter on.
        /// @param renderObjects
        ///     The list of render objects which should be filtered.
        ///
        /// @return The list of render objects for the requested layer.
        ///
        std::vector<RenderObject> GetLayerRenderObjects(RenderLayer renderLayer, const std::vector<RenderObject>& renderObjects) noexcept
        {
            std::vector<RenderObject> layerRenderObjects;
            
            for (const auto& renderObject : renderObjects)
            {
                if (renderObject.GetRenderLayer() == renderLayer)
                {
                    layerRenderObjects.push_back(renderObject);
                }
            }
            
            return layerRenderObjects;
        }
        
        /// Parses a list of RenderObjects and generates a list of RenderPassObjects for
        /// each RenderObject that has a Base pass defined.
        ///
        /// @param renderObjects
        ///     A list of RenderObjects to parse
        ///
        /// @return A collection of RenderPassObjects, one for each RenderObject Base pass
        ///
        std::vector<RenderPassObject> GetBaseRenderPassObjects(const std::vector<RenderObject>& renderObjects) noexcept
        {
            std::vector<RenderPassObject> baseRenderPassObjects;
            
            for (const auto& renderObject : renderObjects)
            {
                auto renderMaterial = renderObject.GetRenderMaterialGroup()->GetRenderMaterial(GetVertexFormat(renderObject), static_cast<u32>(ForwardRenderPasses::k_base));
                
                if (renderMaterial)
                {
                    baseRenderPassObjects.push_back(ConvertToRenderPassObject(renderObject, renderMaterial));
                }
            }
            
            return baseRenderPassObjects;
        }
        
        /// Parses a list of RenderObjects and generates a list of RenderPassObjects for
        /// each RenderObject that has a DirectionalLight pass defined.
        ///
        /// @param renderObjects
        ///     A list of RenderObjects to parse
        ///
        /// @return A collection of RenderPassObjects, one for each RenderObject Directional pass
        ///
        std::vector<RenderPassObject> GetDirectionalLightRenderPassObjects(const std::vector<RenderObject>& renderObjects) noexcept
        {
            std::vector<RenderPassObject> baseRenderPassObjects;
            
            for (const auto& renderObject : renderObjects)
            {
                auto renderMaterial = renderObject.GetRenderMaterialGroup()->GetRenderMaterial(GetVertexFormat(renderObject), static_cast<u32>(ForwardRenderPasses::k_directionalLight));
                
                if (renderMaterial)
                {
                    baseRenderPassObjects.push_back(ConvertToRenderPassObject(renderObject, renderMaterial));
                }
            }
            
            return baseRenderPassObjects;
        }
        
        /// Parses a list of RenderObjects and generates a list of RenderPassObjects for
        /// each RenderObject that has a Transparent pass defined.
        ///
        /// @param renderObjects
        ///     A list of RenderObjects to parse
        ///
        /// @return A collection of RenderPassObjects, one for each RenderObject Transparent pass
        ///
        std::vector<RenderPassObject> GetTransparentRenderPassObjects(const std::vector<RenderObject>& renderObjects) noexcept
        {
            std::vector<RenderPassObject> transparentRenderPassObjects;
            
            for (const auto& renderObject : renderObjects)
            {
                auto renderMaterial = renderObject.GetRenderMaterialGroup()->GetRenderMaterial(GetVertexFormat(renderObject), static_cast<u32>(ForwardRenderPasses::k_transparent));
                
                if (renderMaterial)
                {
                    transparentRenderPassObjects.push_back(ConvertToRenderPassObject(renderObject, renderMaterial));
                }
            }
            
            return transparentRenderPassObjects;
        }
        
        /// Gather all sorted visible RenderPassObjects into a RenderPass with the passed in light source.
        ///
        /// @param taskContext
        ///     Context to manage any spawned tasks
        /// @param camera
        ///     The camera to use for this pass
        /// @param light
        ///     The ambient light to use for this pass
        /// @param renderPassObjects
        ///     The render pass objects to use
        ///
        /// @return The list of target render pass groups
        ///
        RenderPass CompileRenderPass(const TaskContext& taskContext, const RenderCamera& camera, const RenderAmbientLight& light, const std::vector<RenderPassObject>& renderPassObjects,
                                     const RenderPassObjectSorter::SortFunc& sort) noexcept
        {
            auto visibleRenderPassObjects = RenderPassVisibilityChecker::CalculateVisibleObjects(taskContext, camera, renderPassObjects);
            
            //TODO: Handle properly
            if (sort != nullptr)
            {
                sort(camera, visibleRenderPassObjects);
            }
            
            return RenderPass(light, visibleRenderPassObjects);
        }
        
        /// Gather all sorted visible RenderPassObjects into a RenderPass with the passed in light source.
        ///
        /// @param taskContext
        ///     Context to manage any spawned tasks
        /// @param camera
        ///     The camera to use for this pass
        /// @param light
        ///     The directional light to use for this pass
        /// @param renderPassObjects
        ///     The render pass objects to use
        ///
        /// @return The list of target render pass groups
        ///
        RenderPass CompileRenderPass(const TaskContext& taskContext, const RenderCamera& camera, const RenderDirectionalLight& light, const std::vector<RenderPassObject>& renderPassObjects,
                                     const RenderPassObjectSorter::SortFunc& sort) noexcept
        {
            auto visibleRenderPassObjects = RenderPassVisibilityChecker::CalculateVisibleObjects(taskContext, camera, renderPassObjects);
            
            //TODO: Handle properly
            if (sort != nullptr)
            {
                sort(camera, visibleRenderPassObjects);
            }
            
            return RenderPass(light, visibleRenderPassObjects);
        }
        
        /// Gather all sorted visible RenderPassObjects into a RenderPass with the passed in light source.
        ///
        /// @param taskContext
        ///     Context to manage any spawned tasks
        /// @param camera
        ///     The camera to use for this pass
        /// @param light
        ///     The point light to use for this pass
        /// @param renderPassObjects
        ///     The render pass objects to use
        ///
        /// @return The list of target render pass groups
        ///
        RenderPass CompileRenderPass(const TaskContext& taskContext, const RenderCamera& camera, const RenderPointLight& light, const std::vector<RenderPassObject>& renderPassObjects,
                                     const RenderPassObjectSorter::SortFunc& sort) noexcept
        {
            auto visibleRenderPassObjects = RenderPassVisibilityChecker::CalculateVisibleObjects(taskContext, camera, renderPassObjects);
            
            //TODO: Handle properly
            if (sort != nullptr)
            {
                sort(camera, visibleRenderPassObjects);
            }
            
            return RenderPass(light, visibleRenderPassObjects);
        }
        
        /// Gather all render objects in the frame that are to be renderered into the default RenderTarget
        /// and parse them into different RenderPasses for each light source plus the required Base and
        /// Transparent passes. These passes are then compiled into a CameraRenderPassGroup.
        ///
        /// @param taskContext
        ///     Context to manage any spawned tasks
        /// @param renderFrame
        ///     Current frame data
        ///
        /// @return The CameraRenderPassGroup
        ///
        CameraRenderPassGroup CompleSceneCameraRenderPassGroup(const TaskContext& taskContext, const RenderFrame& renderFrame) noexcept
        {
            auto standardRenderObjects = GetLayerRenderObjects(RenderLayer::k_standard, renderFrame.GetRenderObjects());
            
            const u32 numPasses = k_reservedRenderPasses + u32(renderFrame.GetRenderDirectionalLights().size()) + u32(renderFrame.GetRenderPointLights().size());
            std::vector<RenderPass> renderPasses(numPasses);
            std::vector<Task> tasks;
            u32 nextPassIndex = 0;
            
            u32 basePassIndex = nextPassIndex++;
            tasks.push_back([=, &renderPasses, &renderFrame, &standardRenderObjects](const TaskContext& innerTaskContext)
            {
                auto renderPassObjects = GetBaseRenderPassObjects(standardRenderObjects);
                renderPasses[basePassIndex] = CompileRenderPass(innerTaskContext, renderFrame.GetRenderCamera(), renderFrame.GetRenderAmbientLight(), renderPassObjects, RenderPassObjectSorter::OpaqueSort);
            });
            
            for (const auto& directionalLight : renderFrame.GetRenderDirectionalLights())
            {
                u32 directionLightPassIndex = nextPassIndex++;
                tasks.push_back([=, &renderPasses, &renderFrame, &standardRenderObjects](const TaskContext& innerTaskContext)
                {
                    auto renderPassObjects = GetDirectionalLightRenderPassObjects(standardRenderObjects);
                    renderPasses[directionLightPassIndex] = CompileRenderPass(innerTaskContext, renderFrame.GetRenderCamera(), directionalLight, renderPassObjects, RenderPassObjectSorter::OpaqueSort);
                });
            }
            
            //TODO: Point lights
            
            u32 transparentPassIndex = nextPassIndex++;
            tasks.push_back([=, &renderPasses, &renderFrame, &standardRenderObjects](const TaskContext& innerTaskContext)
            {
                auto renderPassObjects = GetTransparentRenderPassObjects(standardRenderObjects);
                renderPasses[transparentPassIndex] = CompileRenderPass(innerTaskContext, renderFrame.GetRenderCamera(), renderFrame.GetRenderAmbientLight(), renderPassObjects, RenderPassObjectSorter::TransparentSort);
            });
            
            taskContext.ProcessChildTasks(tasks);
            
            return CameraRenderPassGroup(renderFrame.GetRenderCamera(), renderPasses);
        }
        
        /// Gathers all UI render objects in the frame that are to be rendered to the default Render Target
        /// and compiles them into RenderPasses. These render passes are then compiled into a
        /// CameraRenderPassGroup which uses the UI camera.
        ///
        /// @param taskContext
        ///     Context to manage any spawned tasks
        /// @param renderFrame
        ///     Current frame data
        ///
        /// @return The generated CameraRenderPassGroup
        ///
        CameraRenderPassGroup CompileUICameraRenderPassGroup(const TaskContext& taskContext, const RenderFrame& renderFrame) noexcept
        {
            constexpr f32 k_near = 0.0f;
            constexpr f32 k_far = 1.0f;
            auto projMatrix = Matrix4::CreateOrthographicProjectionLH(0, renderFrame.GetResolution().x, 0, renderFrame.GetResolution().y, k_near, k_far);
            RenderCamera uiCamera(Matrix4::k_identity, projMatrix);
            
            auto uiRenderObjects = GetLayerRenderObjects(RenderLayer::k_ui, renderFrame.GetRenderObjects());
            auto uiRenderPassObjects = GetTransparentRenderPassObjects(uiRenderObjects);
            CS_ASSERT(uiRenderObjects.size() == uiRenderPassObjects.size(), "Invalid number of render pass objects in transparent pass. All render objects in the UI layer should have a transparent material.");
            
            //TODO: Handle properly
            //std::vector<RenderPass> renderPasses { CompileRenderPass(taskContext, uiCamera, renderFrame.GetRenderAmbientLight(), uiRenderPassObjects, nullptr) };
            std::vector<RenderPass> renderPasses { RenderPass(renderFrame.GetRenderAmbientLight(), uiRenderPassObjects) };
            
            return CameraRenderPassGroup(uiCamera, renderPasses);
        }
        
        /// Gathers all UI render objects in the frame that are to be rendered to the default Render Target
        /// and compiles them into RenderPasses. These render passes are then compiled into a
        /// CameraRenderPassGroup which uses
        
        /// Gather all render objects in the frame that are to be renderered into the default RenderTarget
        /// into a TargetRenderPassGroup.
        ///
        /// @param taskContext
        ///     Context to manage any spawned tasks
        /// @param renderFrame
        ///     Current frame data
        ///
        /// @return The TargetRenderPassGroup
        ///
        TargetRenderPassGroup CompileMainTargetRenderPassGroup(const TaskContext& taskContext, const RenderFrame& renderFrame) noexcept
        {
            std::vector<CameraRenderPassGroup> cameraRenderPassGroup;
            
            //TODO: Schedule on background tasks
            
            cameraRenderPassGroup.push_back(CompleSceneCameraRenderPassGroup(taskContext, renderFrame));
            cameraRenderPassGroup.push_back(CompileUICameraRenderPassGroup(taskContext, renderFrame));
            
            return TargetRenderPassGroup(cameraRenderPassGroup);
        }
    }
    
    //------------------------------------------------------------------------------
    std::vector<TargetRenderPassGroup> ForwardRenderPassCompiler::CompileTargetRenderPassGroups(const TaskContext& taskContext, const RenderFrame& renderFrame) noexcept
    {
        std::vector<TargetRenderPassGroup> targetRenderPassGroups(k_targetRenderPassGroups);
        std::vector<Task> tasks;
        u32 nextPassIndex = 0;
        
        //TODO: Shadows
        
        u32 mainPassIndex = nextPassIndex++;
        tasks.push_back([=, &targetRenderPassGroups, &renderFrame](const TaskContext& innerTaskContext)
        {
            targetRenderPassGroups[mainPassIndex] = CompileMainTargetRenderPassGroup(innerTaskContext, renderFrame);
        });
        
        taskContext.ProcessChildTasks(tasks);
        
        return targetRenderPassGroups;
    }
} 
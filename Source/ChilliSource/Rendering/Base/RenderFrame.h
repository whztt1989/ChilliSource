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

#ifndef _CHILLISOURCE_RENDERING_BASE_RENDERFRAME_H_
#define _CHILLISOURCE_RENDERING_BASE_RENDERFRAME_H_

#include <ChilliSource/ChilliSource.h>
#include <ChilliSource/Rendering/Base/RenderObject.h>
#include <ChilliSource/Rendering/Camera/RenderCamera.h>
#include <ChilliSource/Rendering/Lighting/RenderAmbientLight.h>
#include <ChilliSource/Rendering/Lighting/RenderDirectionalLight.h>
#include <ChilliSource/Rendering/Lighting/RenderPointLight.h>

#include <vector>

namespace ChilliSource
{
    /// A container for the camera and all lights and objects within a single frame.
    ///
    /// This is immutable and therefore thread safe.
    ///
    class RenderFrame final
    {
    public:
        /// Creates a new instance with the given camera, lights and objects.
        ///
        /// @param renderCamera
        ///     The camera used for the frame.
        /// @param renderAmbientLight
        ///     An ambient light that represents the combination of all ambient lights in the
        ///     scene.
        /// @param renderDirectionalLights
        ///     A list of directional lights in the frame.
        /// @param renderPointLights
        ///     A list of point lights in the frame.
        /// @param renderObjects
        ///     A list of objects in the frame.
        ///
        RenderFrame(const RenderCamera& renderCamera, const RenderAmbientLight& renderAmbientLight, const std::vector<RenderDirectionalLight>& renderDirectionalLights,
                    const std::vector<RenderPointLight>& renderPointLights, const std::vector<RenderObject>& renderObjects) noexcept;
        
        /// @return The camera used for the frame.
        ///
        const RenderCamera& GetRenderCamera() const noexcept { return m_renderCamera; }
        
        /// @return An ambient light that represents the combination of all ambient lights in the
        ///     scene.
        ///
        const RenderAmbientLight& GetRenderAmbientLight() const noexcept { return m_renderAmbientLight; }
        
        /// @return A list of directional lights in the frame.
        ///
        const std::vector<RenderDirectionalLight>& GetRenderDirectionalLights() const noexcept { return m_renderDirectionalLights; }
        
        /// @return A list of point lights in the frame.
        ///
        const std::vector<RenderPointLight>& GetRenderPointLights() const noexcept { return m_renderPointLights; }
        
        /// @return A list of objects in the frame.
        ///
        const std::vector<RenderObject>& GetRenderObjects() const noexcept { return m_renderObjects; }
        
    private:
        RenderCamera m_renderCamera;
        RenderAmbientLight m_renderAmbientLight;
        std::vector<RenderDirectionalLight> m_renderDirectionalLights;
        std::vector<RenderPointLight> m_renderPointLights;
        std::vector<RenderObject> m_renderObjects;
    };
}

#endif

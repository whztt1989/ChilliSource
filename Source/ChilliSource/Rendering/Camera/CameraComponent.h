//
//  CameraComponent.h
//  Chilli Source
//  Created by Scott Downie on 12/10/2010.
//
//  The MIT License (MIT)
//
//  Copyright (c) 2010 Tag Games Limited
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

#ifndef _CHILLISOURCE_RENDERING_CAMERA_COMPONENT_H_
#define _CHILLISOURCE_RENDERING_CAMERA_COMPONENT_H_

#include <ChilliSource/ChilliSource.h>
#include <ChilliSource/Core/Entity/Component.h>
#include <ChilliSource/Core/Base/Colour.h>
#include <ChilliSource/Core/Base/Screen.h>
#include <ChilliSource/Core/Math/Geometry/Shapes.h>

namespace ChilliSource
{
	namespace Rendering
	{
        enum class CameraType
        {
            k_orthographic,
            k_perspective
        };
        
		struct CameraDescription
		{
			f32 fFOV;
			f32 fAspect;
			f32 fNearClipping;
			f32 fFarClipping;
			
			CameraType m_type;
			bool bShouldResizeToScreen;
			
			Core::Colour ClearCol; 
			Core::Vector2 vViewSize;
		};
		
		class CameraComponent : public Core::Component
		{
		public:
			CS_DECLARE_NAMEDTYPE(CameraComponent);
			CameraComponent(const CameraDescription &inCamDesc);
			~CameraComponent();
			//----------------------------------------------------------
			/// Is A
			///
			/// Returns if it is of the type given
			/// @param Comparison Type
			/// @return Whether the class matches the comparison type
			//----------------------------------------------------------
			bool IsA(Core::InterfaceIDType inInterfaceID) const override;
			//----------------------------------------------------------
			/// Set Look At
			///
			/// Set the camera orientation, target and position
			/// @param Position
			/// @param Look target
			/// @param Up direction
			//----------------------------------------------------------
			void SetLookAt(const Core::Vector3& invPos, const Core::Vector3& invTarget, const Core::Vector3& invUp);
			//----------------------------------------------------------
            /// Toggle between ortho and persp camera
            ///
			/// @author S Downie
			///
            /// @param Camera type
			//----------------------------------------------------------
			void SetType(CameraType in_type);
            //----------------------------------------------------------
			/// @author S Downie
			///
			/// @return Camera type
			//----------------------------------------------------------
			CameraType GetType() const;
			//----------------------------------------------------------
			/// Set Viewport Size
			///
			/// @param Vector containing width and height
			//----------------------------------------------------------
			void SetViewportSize(const Core::Vector2 &invSize);
			//----------------------------------------------------------
			/// Set Viewport Size
			///
			/// @param Width 
			/// @param Height
			//----------------------------------------------------------
			void SetViewportSize(u32 inudwWidth, u32 inudwHeight);
			//----------------------------------------------------------
			/// Get Viewport Size
			///
			/// @param Vector containing width and height
			//----------------------------------------------------------
			const Core::Vector2& GetViewportSize();			
			//------------------------------------------------------
			/// Set Field Of View
			///
			/// @param Viewing angle in radians
			//------------------------------------------------------
			void SetFieldOfView(const f32 in_fov);
			//------------------------------------------------------
			/// Set Aspect Ratio
			///
			/// @param Aspect Ratio (Viewport width/viewport height)
			//------------------------------------------------------
			void SetAspectRatio(const f32 infAspectRatio);
			//------------------------------------------------------
			/// Set Near Clipping
			///
			/// @param Near Z clipping distance in view space
			//------------------------------------------------------
			void SetNearClipping(const f32 infNear);
			//------------------------------------------------------
			/// Set Far Clipping
			///
			/// @param Far Z clipping distance in view space
			//------------------------------------------------------
			void SetFarClipping(const f32 infFar);
			//------------------------------------------------------
			/// Set Clear Colour
			///
			/// @param Render buffer clear colour
			//------------------------------------------------------
			void SetClearColour(const Core::Colour &inCol);
			//------------------------------------------------------
			/// Enable Viewport Resize with Screen
			///
			/// @param Whether the viewport should resize when
			/// the screen resizes
			//-----------------------------------------------------
			void EnableViewportResizeWithScreen(bool inbEnable);
			//------------------------------------------------------
			/// Get Field Of View
			///
			/// @return Viewing angle in radians
			//------------------------------------------------------
			const f32 GetFieldOfView() const;
			//------------------------------------------------------
			/// Get Aspect Ratio
			///
			/// @return Aspect Ratio (Viewport width/viewport height)
			//------------------------------------------------------
			const f32 GetAspectRatio() const;
			//------------------------------------------------------
			/// Get Near Clipping
			///
			/// @return Near Z clipping distance in view space
			//------------------------------------------------------
			const f32 GetNearClipping() const;
			//------------------------------------------------------
			/// Get Far Clipping
			///
			/// @return Far Z clipping distance in view space
			//------------------------------------------------------
			const f32 GetFarClipping() const;
			//------------------------------------------------------
			/// Get Clear Colour
			///
			/// @return Render buffer clear colour
			//------------------------------------------------------
			const Core::Colour& GetClearColour() const;
			
			//------------------------------------------------------
			/// Get Projection 
			///
			/// @return Projection matrix
			//------------------------------------------------------
			const Core::Matrix4& GetProjection();
			//------------------------------------------------------
			/// Get View 
			///
			/// @return View matrix
			//------------------------------------------------------
			const Core::Matrix4& GetView();
			//------------------------------------------------------
			/// Unproject
			///
			/// Project from a point in screen space to a ray in
			/// world space
			/// @param Point in screen space
			/// @return Ray in world space with camera view direction
			//------------------------------------------------------
			virtual Core::Ray Unproject(const Core::Vector2 &invScreenPos);
			//------------------------------------------------------
			/// Project
			///
			/// Convert from a point in world space to a point in
			/// screen space
			//------------------------------------------------------
			virtual Core::Vector2 Project(const Core::Vector3 &invWorldPos);
			
			//------------------------------------------------------
			/// Get Frustum Pointer
			///
			/// @return Pointer to camera frustum
			//------------------------------------------------------
			const Core::Frustum* GetFrustumPtr() const;
            //------------------------------------------------------
            /// Update Frustum
            ///
            /// Recalculate frustum planes
            //------------------------------------------------------
            void UpdateFrustum();
			//------------------------------------------------------
            /// Billboard
            ///
            /// Orientate the given matrix to face the cameras
            /// view vector
            //------------------------------------------------------
            void Billboard(const Core::Matrix4& inmatBillboarded, Core::Matrix4& outmatBillboarded);

			CameraDescription& GetDescription() { return mDesc; }
            
            //--------------------------------------------------------------------------------------------------
            /// Get Opaque Sort Predicate
            ///
            /// @return Gets the currently set opaque sort predicate for this camera
            //--------------------------------------------------------------------------------------------------
            RendererSortPredicateSPtr GetOpaqueSortPredicate() const;
            //--------------------------------------------------------------------------------------------------
            /// Get Transparent Sort Predicate
            ///
            /// @return Gets the currently set opaque sort predicate for this camera
            //--------------------------------------------------------------------------------------------------
            RendererSortPredicateSPtr GetTransparentSortPredicate() const;
            //--------------------------------------------------------------------------------------------------
            /// Set Opaque Sort Predicate
            ///
            /// @return Opaque sort predicate to use for this camera
            //--------------------------------------------------------------------------------------------------
            void SetOpaqueSortPredicate(const RendererSortPredicateSPtr & inpPredicate);
            //--------------------------------------------------------------------------------------------------
            /// Set Transparent Sort Predicate
            ///
            /// @param Transparent sort predicate to use for this camera
            //--------------------------------------------------------------------------------------------------
            void SetTransparentSortPredicate(const RendererSortPredicateSPtr & inpPredicate);
			         
            //--------------------------------------------------------------------------------------------------
            /// Get Culling Predicate
            ///
            /// @param Culling predicate to use for this camera
            //--------------------------------------------------------------------------------------------------
            ICullingPredicateSPtr GetCullingPredicate() const;
            //--------------------------------------------------------------------------------------------------
            /// Get Perspective Culling Predicate
            ///
            /// @param Culling predicate to use for this camera in perpective mode
            //--------------------------------------------------------------------------------------------------
            void SetPerspectiveCullingPredicate(const ICullingPredicateSPtr & inpPredicate);
            //--------------------------------------------------------------------------------------------------
            /// Get orthographic Culling Predicate
            ///
            /// @param Culling predicate to use for this camera in orthographic mode
            //--------------------------------------------------------------------------------------------------
            void SetOrthographicCullingPredicate(const ICullingPredicateSPtr & inpPredicate);
            
		private:
			//------------------------------------------------------
			/// Calculate Perspective Matrix (Normalized)
			///
			/// 
			//------------------------------------------------------
			void CalculatePerspectiveMatrix();
			//------------------------------------------------------
			/// Calculate Orthographic Matrix
			///
			///
			//------------------------------------------------------
			void CalculateOrthographicMatrix();
            //------------------------------------------------------
			/// Called when the resolution changes and resize with
			/// screen is enabled.
            ///
			/// @author I Copland
			//------------------------------------------------------
			void OnResolutionChanged(const Core::Vector2& in_resolution);

		private:
			
            Core::Screen* m_screen;
            
			bool mbProjectionCacheValid;
			
			CameraDescription mDesc;
			Core::Frustum mFrustum;
			
			Core::Matrix4 mmatProj;		//Projection matrix depending on whether we are an ortho or perspective camera
			Core::Matrix4 mmatView;		//View matrix
			Core::Matrix4 mmatViewProj;	//View projection;
            
            Core::EventConnectionUPtr m_screenOrientationChangedConnection;
            Core::EventConnectionUPtr m_screenResizedConnection;
            
            RendererSortPredicateSPtr mpOpaqueSortPredicate;
            RendererSortPredicateSPtr mpTransparentSortPredicate;
            
            ICullingPredicateSPtr      mpOrthographicCulling;
            ICullingPredicateSPtr      mpPerspectiveCulling;
		};
	}
}

#endif

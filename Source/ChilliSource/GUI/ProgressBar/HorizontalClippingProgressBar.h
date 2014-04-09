//
//  HorizontalClippingProgressBar.h
//  moFlo
//
//  Created by Scott Downie on 27/04/2011.
//  Copyright 2011 Tag Games. All rights reserved.
//

#ifndef _MOFLO_GUI_DEFAULTS_HORIZONTAL_CLIPPING_PROGRESS_BAR_H_
#define _MOFLO_GUI_DEFAULTS_HORIZONTAL_CLIPPING_PROGRESS_BAR_H_

#include <ChilliSource/ChilliSource.h>
#include <ChilliSource/Core/Math/Geometry/Shapes.h>
#include <ChilliSource/GUI/ProgressBar/ProgressBar.h>

namespace ChilliSource
{
	namespace GUI
	{
		class HorizontalClippingProgressBar : public ProgressBar
		{
		public:

			DECLARE_META_CLASS(HorizontalClippingProgressBar)

			HorizontalClippingProgressBar();
			HorizontalClippingProgressBar(const Core::ParamDictionary& insParams);
			//------------------------------------------------------
			/// Draw
			///
			/// Draws a background box with the progress bar
			/// as subview
			///
			/// @param Canvas renderer pointer
			//------------------------------------------------------
			void Draw(Rendering::CanvasRenderer* inpCanvas);
			//------------------------------------------------------
			/// Set Background Image
			///
			/// @param Texture representing the background
			//------------------------------------------------------
			void SetBackgroundImage(const Rendering::TextureSPtr& inpTexture);
			//------------------------------------------------------
			/// Set Progress Image
			///
			/// @param Texture representing the bar
			//------------------------------------------------------
			void SetProgressImage(const Rendering::TextureSPtr& inpTexture);
			//------------------------------------------------------
			/// Get Background Image
			///
			/// @return Texture representing the background
			//------------------------------------------------------
			const Rendering::TextureSPtr& GetBackgroundImage() const;
			//------------------------------------------------------
			/// Get Progress Image
			///
			/// @return Texture representing the bar
			//------------------------------------------------------
			const Rendering::TextureSPtr& GetProgressImage() const;
			//--------------------------------------------------------
			/// Set Background Sprite Sheet
			///
			/// @param Sprite sheet
			//--------------------------------------------------------
			void SetBackgroundTextureAtlas(const Rendering::TextureAtlasCSPtr& inpTextureAtlas);
			//--------------------------------------------------------
			/// Set Progress Sprite Sheet
			///
			/// @param Sprite sheet
			//--------------------------------------------------------
			void SetProgressTextureAtlas(const Rendering::TextureAtlasCSPtr& inpTextureAtlas);
			//--------------------------------------------------------
			/// Get Background Sprite Sheet
			///
			/// @return Sprite sheet
			//--------------------------------------------------------
			const Rendering::TextureAtlasCSPtr& GetBackgroundTextureAtlas() const;
			//--------------------------------------------------------
			/// Get Progress Sprite Sheet
			///
			/// @return Sprite sheet
			//--------------------------------------------------------
			const Rendering::TextureAtlasCSPtr& GetProgressTextureAtlas() const;
			//--------------------------------------------------------
			/// Set Background Sprite Sheet Index
			///
			/// @param The index of the image within the sprite sheet
			//--------------------------------------------------------
			void SetBackgroundTextureAtlasIndex(u32 inudwIndex);
			//--------------------------------------------------------
			/// Set Progress Sprite Sheet Index
			///
			/// @param The index of the image within the sprite sheet
			//--------------------------------------------------------
			void SetProgressTextureAtlasIndex(u32 inudwIndex);
			//--------------------------------------------------------
			/// Get Background Sprite Sheet Index
			///
			/// @return The index of the image within the sprite sheet
			//--------------------------------------------------------
			u32 GetBackgroundTextureAtlasIndex() const;
			//--------------------------------------------------------
			/// Get Progress Sprite Sheet Index
			///
			/// @return The index of the image within the sprite sheet
			//--------------------------------------------------------
			u32 GetProgressTextureAtlasIndex() const;
			//--------------------------------------------------------
			/// Set Background Sprite Sheet Index ID
			///
			/// @param The index ID of the image within the sprite sheet
			//--------------------------------------------------------
			void SetBackgroundTextureAtlasID(const std::string& instrID);
			//--------------------------------------------------------
			/// Set Progress Sprite Sheet Index ID
			///
			/// @param The index ID of the image within the sprite sheet
			//--------------------------------------------------------
			void SetProgressTextureAtlasID(const std::string& instrID);
            //--------------------------------------------------------
            /// Enable Height From Image
            ///
            /// When this is enabled the image view's height will be 
            /// based on the size of the image
            ///
            /// @param Enable/disable
            //--------------------------------------------------------
            void EnableHeightFromImage(bool inbEnable);
			//--------------------------------------------------------
			/// Is Height From Image Enabled
			///
			/// When this is enabled the image view's height will be 
			/// based on the size of the image
			///
			/// @return Whether the image view's height will be 
			/// based on the size of the image
			//--------------------------------------------------------
			bool IsHeightFromImageEnabled() const;
			//--------------------------------------------------------
			/// Get Background Sprite Sheet Index ID
			///
			/// @return The index of the image within the sprite sheet
			//--------------------------------------------------------
			const std::string& GetBackgroundTextureAtlasID() const;
			//--------------------------------------------------------
			/// Get Progress Sprite Sheet Index ID
			///
			/// @return The index ID of the image within the sprite sheet
			//--------------------------------------------------------
			const std::string& GetProgressTextureAtlasID() const;
            //--------------------------------------------------------
            /// Get Background View
            ///
            /// @return Background image view
            //--------------------------------------------------------
            const ImageViewSPtr& GetBackgroundView() const;

		private:

			DECLARE_PROPERTY_A(Rendering::TextureSPtr, BackgroundTexture, SetBackgroundImage, GetBackgroundImage);
			DECLARE_PROPERTY_A(Rendering::TextureSPtr, ProgressTexture, SetProgressImage, GetProgressImage);

			DECLARE_PROPERTY_A(Rendering::TextureAtlasCSPtr, BackgroundTextureAtlas, SetBackgroundTextureAtlas, GetBackgroundTextureAtlas);
			DECLARE_PROPERTY_A(Rendering::TextureAtlasCSPtr, ProgressTextureAtlas, SetProgressTextureAtlas, GetProgressTextureAtlas);

			DECLARE_PROPERTY_A(u32, BackgroundTextureAtlasIndex, SetBackgroundTextureAtlasIndex, GetBackgroundTextureAtlasIndex);
			DECLARE_PROPERTY_A(u32, ProgressTextureAtlasIndex, SetProgressTextureAtlasIndex, GetProgressTextureAtlasIndex);

			DECLARE_PROPERTY_A(std::string, BackgroundTextureAtlasID, SetBackgroundTextureAtlasID, GetBackgroundTextureAtlasID);
			DECLARE_PROPERTY_A(std::string, ProgressTextureAtlasID, SetProgressTextureAtlasID, GetProgressTextureAtlasID);
			
            DECLARE_PROPERTY_A(bool, HeightFromImage, EnableHeightFromImage, IsHeightFromImageEnabled);

			ImageViewSPtr mpBackgroundImage;
			ImageViewSPtr mpProgressImage;

			s32 mdwSegments;
			f32 mfSegmentSize;
		};
	}
}

#endif
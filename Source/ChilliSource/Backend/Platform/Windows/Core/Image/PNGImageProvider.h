//
//  PNGImageProvider.h
//  Chilli Source
//  Created by I Copland on 05/02/2011.
//
//  The MIT License (MIT)
//
//  Copyright (c) 2011 Tag Games Limited
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

#ifdef CS_TARGETPLATFORM_WINDOWS

#ifndef _CHILLISOURCE_BACKEND_PLATFORM_WINDOWS_CORE_IMAGE_PNGIMAGEPROVIDER_H_
#define _CHILLISOURCE_BACKEND_PLATFORM_WINDOWS_CORE_IMAGE_PNGIMAGEPROVIDER_H_

#include <ChilliSource/Backend/Platform/Windows/ForwardDeclarations.h>
#include <ChilliSource/Core/Image/Image.h>
#include <ChilliSource/Core/Image/PNGImageProvider.h>

namespace ChilliSource
{
	namespace Windows
	{
		//--------------------------------------------------------------
		/// The windows backend for the PNG Image Provider. This loads
		/// PNG images from file.
		///
		/// @author Ian Copland
		//--------------------------------------------------------------
		class PNGImageProvider final : public Core::PNGImageProvider
		{
		public:
			CS_DECLARE_NAMEDTYPE(PNGImageProvider);
			//----------------------------------------------------------
			/// Is the object of the given interface type
			///
			/// @author I Copland
			///
			/// @param Interface type to query
			///
			/// @return Whether the object is of given type
			//----------------------------------------------------------
			bool IsA(Core::InterfaceIDType in_interfaceId) const override;
			//-------------------------------------------------------
			/// @author I Copland
			///
			/// @return The resource type this provider can load
			//-------------------------------------------------------
			Core::InterfaceIDType GetResourceType() const override;
			//----------------------------------------------------------
			/// Whether or not the provider can create resources from
			/// files with the given extension.
			///
			/// @author I Copland
			///
			/// @param Extension to compare against
			///
			/// @return Whether the object can load a resource with that
			/// extension
			//----------------------------------------------------------
			bool CanCreateResourceWithFileExtension(const std::string& in_extension) const override;
			//----------------------------------------------------------
			/// Creates a new image resource from file. Check the
			/// resource load state for success or failure
			///
			/// @author I Copland
			///
			/// @param The storage location to load from
			/// @param File path to resource
			/// @param Options to customise the creation
			/// @param [Out] Resource
			//-----------------------------------------------------------
			void CreateResourceFromFile(Core::StorageLocation in_storageLocation, const std::string& in_filePath, const Core::IResourceOptionsBaseCSPtr& in_options, const Core::ResourceSPtr& out_resource) override;
			//----------------------------------------------------
			/// Creates a new resource from file asynchronously.
			/// Completion delegate is called when load is finished.
			/// Check the resource load state for success or failure
			///
			/// @author I Copland
			///
			/// @param The storage location.
			/// @param The filepath.
			/// @param Options to customise the creation
			/// @param Completion delegate
			/// @param [Out] The output resource.
			//----------------------------------------------------
			void CreateResourceFromFileAsync(Core::StorageLocation in_storageLocation, const std::string& in_filePath, const Core::IResourceOptionsBaseCSPtr& in_options, const Core::ResourceProvider::AsyncLoadDelegate& in_delegate, const Core::ResourceSPtr& out_resource) override;
		private:
			friend Core::PNGImageProviderUPtr Core::PNGImageProvider::Create();
			//-----------------------------------------------------------
			/// Private constructor to force use of factory method
			///
			/// @author I Copland
			//-----------------------------------------------------------
			PNGImageProvider() = default;
		};
	}
}

#endif

#endif

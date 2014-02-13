/*
 * File: FMODAudioLoader.cpp
 * Date: 16/11/2010 2010 
 * Description: 
 */

/*
 * Author: Scott Downie
 * Version: v 1.0
 * Copyright ©2010 Tag Games Limited - All rights reserved 
 */

#include <moFlo/Platform/iOS/FMOD/FMODAudioLoader.h>
#include <moFlo/Platform/iOS/FMOD/FMODAudioResource.h>
#include <moFlo/Platform/iOS/FileIO/FileSystem.h>

#include <moFlo/Core/Application.h>

namespace moFlo
{
	namespace iOSPlatform
	{
		const std::string kstrWAVExtension("wav");
		const std::string kstrAACExtension("aac");
		const std::string kstrOGGExtension("ogg");
		const std::string kstrAIFFExtension("aiff");
		
		//-------------------------------------------------------------------------
		/// Constructor
		///
		/// Register this object as a model provider
		//-------------------------------------------------------------------------
		CFMODAudioLoader::CFMODAudioLoader(Audio::IAudioSystem* inpFMODSystem) 
		: CAudioLoader(inpFMODSystem), mpFMODSystem(static_cast<CFMODSystem*>(inpFMODSystem))
		{
			mstrBundlePath = Core::CApplication::GetFileSystemPtr()->GetStorageLocationDirectory(Core::SL_PACKAGE) + "/";
			mstrDocumentsPath = Core::CApplication::GetFileSystemPtr()->GetStorageLocationDirectory(Core::SL_CACHE) + "/";
            mstrDLCPath = Core::CApplication::GetFileSystemPtr()->GetPackageDLCDirectory() + "/";
		}
		//----------------------------------------------------------------------------
		/// Can Create Resource From File With Extension
		///
		/// @param Type to compare
		/// @param Extension to compare
		/// @return Whether the object can create a resource with the given extension
		//----------------------------------------------------------------------------
		bool CFMODAudioLoader::CanCreateResourceFromFileWithExtension(const std::string & inExtension) const
		{
			return	(inExtension == kstrWAVExtension) || (inExtension == kstrAACExtension) || (inExtension == kstrOGGExtension) ||
					(inExtension == kstrAIFFExtension);
		}
		//----------------------------------------------------------------------------
		/// Create Resource From File
		///
        /// @param The storage location to load from
		/// @param Filename
		/// @param Out: Resource object
		/// @return Success
		//----------------------------------------------------------------------------
		bool CFMODAudioLoader::CreateResourceFromFile(Core::STORAGE_LOCATION ineStorageLocation, const std::string & inFilePath, Core::ResourcePtr& outpResource)  
		{
            std::string strFilePath;
            static_cast<iOSPlatform::CFileSystem*>(Core::CApplication::GetFileSystemPtr())->GetBestPathToFile(ineStorageLocation, inFilePath, strFilePath);
            
            if(strFilePath.empty())
            {
                ERROR_LOG("Cannot load audio from the given Storage Location.");
                return false;
            }
			
            mpFMODSystem->Create3DSound(strFilePath, (Audio::IAudioResource*)outpResource.get());
			return true;
		}
		//----------------------------------------------------------------------------
		/// Stream Resource From File
		///
        /// @param The storage location to load from
		/// @param Filename
		/// @param Out: Resource object
		/// @return Success
		//----------------------------------------------------------------------------
		bool CFMODAudioLoader::StreamResourceFromFile(Core::STORAGE_LOCATION ineStorageLocation, const std::string & inFilePath, Core::ResourcePtr& outpResource)
		{
            std::string strFilePath;
            static_cast<iOSPlatform::CFileSystem*>(Core::CApplication::GetFileSystemPtr())->GetBestPathToFile(ineStorageLocation, inFilePath, strFilePath);
            
            if(strFilePath.empty())
            {
                ERROR_LOG("Cannot load audio from the given Storage Location.");
                return false;
            }
			
			
            mpFMODSystem->CreateStream(strFilePath, (Audio::IAudioResource*)outpResource.get());
			return true;
		}
		//----------------------------------------------------------------------------
		/// Create Audio Listener
		///
		/// @return Audio listener
		//----------------------------------------------------------------------------
		Audio::AudioListenerPtr CFMODAudioLoader::CreateAudioListener()
		{
			return mpFMODSystem->CreateAudioListener();
		}
	}
}

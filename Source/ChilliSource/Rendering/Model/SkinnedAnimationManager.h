/*
 *  SkeletalAnimationManager.h
 *  MoFlowSkeleton
 *
 *  Created by Ian Copland on 17/10/2011.
 *  Copyright 2011 Tag Games ltd. All rights reserved.
 *
 */

#ifndef _MO_FLO_RENDERING_SKELETALANIMATIONMANAGER_H_
#define _MO_FLO_RENDERING_SKELETALANIMATIONMANAGER_H_

#include <ChilliSource/ChilliSource.h>
#include <ChilliSource/Core/Resource/ResourceManager.h>
#include <ChilliSource/Rendering/Model/SkinnedAnimation.h>

namespace ChilliSource
{
	namespace Rendering
	{
		//------------------------------------
		/// SkeletalAnimation manager.
		//------------------------------------
		class SkinnedAnimationManager : public Core::ResourceManager
		{
		public:
			DECLARE_NAMED_INTERFACE(SkinnedAnimationManager);
			SkinnedAnimationManager();
			virtual ~SkinnedAnimationManager();
			
			//----------------------------------------------------------------
			/// Is A
			///
			/// Query the interface type
			/// @param The interface to compare
			/// @return Whether the object implements that interface
			//----------------------------------------------------------------
			virtual bool IsA(Core::InterfaceIDType inInterfaceID) const override;
			//----------------------------------------------------------------
			/// Get Resource Type
			///
			/// @return The type of resource this manager handles
			//----------------------------------------------------------------
			virtual Core::InterfaceIDType GetResourceType() const override;
			//----------------------------------------------------------------
			/// Get Provider Type
			///
			/// @return The type of resource it consumes from resource provider
			//----------------------------------------------------------------
			virtual Core::InterfaceIDType GetProviderType() const override;
			//----------------------------------------------------------------
			/// Manages Resource Of Type
			///
			/// @return Whether this object manages the object of type
			//----------------------------------------------------------------
			virtual bool ManagesResourceOfType(Core::InterfaceIDType inInterfaceID) const override;
			//-----------------------------------------------------------------
			/// Get Resource From File
			///
			/// Generic call to get the managers resource
            /// @param The storage location to load from
			/// @param File path to resource
			/// @return Generic pointer to object type
			//-----------------------------------------------------------------
			Core::ResourceSPtr GetResourceFromFile(Core::StorageLocation ineStorageLocation, const std::string &instrFilePath) override;
			//-----------------------------------------------------------------
			/// Async Get Resource From File
			///
			/// Generic call to get the managers resource
            /// @param The storage location to load from
			/// @param File path to resource
			/// @return Generic pointer to object type
			//-----------------------------------------------------------------
			Core::ResourceSPtr AsyncGetResourceFromFile(Core::StorageLocation ineStorageLocation, const std::string &instrFilePath) override;
			//-----------------------------------------------------------------
			/// Get Skinned Animation From File
			///
			/// Loads a single skinned animation and returns it.
			///
            /// @param The storage location to load from
			/// @param File path to resource
			/// @return a pointer to the skeletal animation.
			//-----------------------------------------------------------------
			SkinnedAnimationSPtr GetSkinnedAnimationFromFile(Core::StorageLocation ineStorageLocation, const std::string &instrFilePath);
			//-----------------------------------------------------------------
			/// Async Get Skinned Animation From File
			///
			/// Loads a single skinned animation asynchroniously. This will return immediately, however the resource
			/// cannot be used until its "Loaded" flag has been set true.
			///
            /// @param The storage location to load from
			/// @param File path to resource
			/// @return a pointer to the skeletal animation.
			//-----------------------------------------------------------------
			SkinnedAnimationSPtr AsyncGetSkinnedAnimationFromFile(Core::StorageLocation ineStorageLocation, const std::string &instrFilePath);
		private:
			
		};
	}
}

#endif
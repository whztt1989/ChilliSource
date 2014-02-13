//
//  AnimatedMeshComponentUpdater.h
//  moFlow
//
//  Created by Ian Copland on 22/04/2013.
//  Copyright (c) 2013 Tag Games Ltd. All rights reserved.
//

#include <moFlo/Core/ForwardDeclarations.h>
#include <moFlo/Rendering/ForwardDeclarations.h>
#include <moFlo/Core/System.h>
#include <moFlo/Core/SystemConcepts.h>

namespace moFlo
{
    namespace Rendering
    {
        //======================================================
        /// Animated Mesh Component Updater
        ///
        /// A system for updating animation mesh components.
        //======================================================
        class CAnimatedMeshComponentUpdater : public moCore::ISystem, public moCore::IUpdateable
        {
        public:
            DECLARE_NAMED_INTERFACE(CAnimatedMeshComponentUpdater);
            //------------------------------------------------
			/// Constructor
			//------------------------------------------------
            CAnimatedMeshComponentUpdater();
            //------------------------------------------------
			/// Is A
			///
			/// @param Interface to compare
			/// @return Whether the object implements the given interface
			//------------------------------------------------
			bool IsA(Core::InterfaceIDType inInterfaceID) const;
            //------------------------------------------------
			/// Add Component
			///
			/// Adds a new component for updating to the
            /// updater.
            ///
            /// @param The component.
			//------------------------------------------------
			void AddComponent(CAnimatedMeshComponent* inpAnimatedMesh);
            //------------------------------------------------
			/// Update
			///
			/// Updates all of the registered Animated Mesh
            /// Components.
            ///
            /// @param The delta time.
			//------------------------------------------------
			void Update(f32 infDeltaTime);
            //------------------------------------------------
			/// Remove Component
			///
			/// Removes a component from being updated.
            ///
            /// @param The component.
			//------------------------------------------------
			void RemoveComponent(CAnimatedMeshComponent* inpAnimatedMesh);
        private:
            DYNAMIC_ARRAY<CAnimatedMeshComponent*> mapComponentsToUpdate;
        };
    }
}
/*
 *  Scene.h
 *  moFlo
 *
 *  Created by Scott Downie on 21/09/2010.
 *  Copyright 2010 Tag Games. All rights reserved.
 *
 */

#ifndef _MO_FLO_CORE_SCENE_H_
#define _MO_FLO_CORE_SCENE_H_

#include <ChilliSource/ChilliSource.h>
#include <ChilliSource/Core/Entity/Entity.h>
#include <ChilliSource/Core/Math/Geometry/Shapes.h>
#include <ChilliSource/Core/Container/Octree.h>
#include <ChilliSource/Core/Volume/VolumeComponent.h>

namespace ChilliSource
{
	namespace Core
	{
		//--------------------------------------------------------------------------------------------------
		/// Description:
		///
		/// Base scene graph class. Holds the game objects
		/// from a scene and feeds the renderer.
		/// Responsible for updating, culling and scene
		/// hierarchy.
		//--------------------------------------------------------------------------------------------------
		class Scene
		{
		public:
			Scene(Input::InputSystem* inpInputSystem = nullptr, f32 infWorldHalfSize = 100);
			~Scene();

			//-------------------------------------------------------
			/// Add Entity
			///
			/// Add the entity to the scene
			///
			/// @param Entity pointer
			//-------------------------------------------------------
			void AddEntity(const EntitySPtr& inpEntity);
			//-------------------------------------------------------
			/// Get Entity List
			///
			/// @return the list of all the entities in the scene.
			//-------------------------------------------------------
			const SharedEntityList& GetEntityList();
			//-------------------------------------------------------
			/// Become Active
			///
			/// Force the scene to become the active one and to
			/// receive user interaction
			//-------------------------------------------------------
			void BecomeActive();
			//-------------------------------------------------------
			/// Become Inactive
			///
			/// Set this scene to be inactive. It will no longer
			/// be interactable for the user
			//-------------------------------------------------------
			void BecomeInactive();
			
			//--------------------------------------------------------------------------------------------------
			/// Get Spatial Graph
			///
			/// @return A reference to the octree that manages the spatial relationship of the scene nodes
			//--------------------------------------------------------------------------------------------------
			//const Octree& GetSpatialGraph() const;
			
			//==================================================================================================
			// SCENE QUERYING
			//==================================================================================================
			//--------------------------------------------------------------------------------------------------
			/// Query Scene For Intersection
			///
			/// Traverses the contents of the scene and adds any objects that intersect with the ray to the
			/// list.
			/// @param Ray to check intersection
			/// @param A handle to a container to fill with intersecting components
			//--------------------------------------------------------------------------------------------------
			void QuerySceneForIntersection(const Core::Ray &inRay, std::vector<VolumeComponent*> &outIntersectComponents, bool mbIsDepthSorted = false, u32 inudwQueryMask = 0);
			//--------------------------------------------------------------------------------------------------
			/// Query Scene For Components
			///
			/// Traverse the scene for the given component type and fill the list with those components
			/// @param Empty container to be filled
			//--------------------------------------------------------------------------------------------------
			template <typename T> void QuerySceneForComponents(std::vector<T*> &outComponents, u32 inudwQueryMask = 0)
			{
				for(SharedEntityList::const_iterator it = mEntities.begin(); it != mEntities.end(); ++it)
				{
					(*it)->GetComponents<T>(outComponents, inudwQueryMask, false);
				}
			}
            //--------------------------------------------------------------------------------------------------
			/// Query Scene For Managed Components
			///
			/// Traverse the scene for the given component type and fill the list with those components
			/// @param Empty container to be filled
			//--------------------------------------------------------------------------------------------------
			template <typename T> void QuerySceneForManagedComponents(std::vector<std::shared_ptr<T> > &outComponents, u32 inudwQueryMask = 0)
			{
				for(SharedEntityList::const_iterator it = mEntities.begin(); it != mEntities.end(); ++it)
				{
					(*it)->GetManagedComponents<T>(outComponents, inudwQueryMask, false);
				}
			}
            //--------------------------------------------------------------------------------------------------
			/// Query Scene For Components
			///
			/// Traverse the scene for the given component type and fill the list with those components
            ///
			/// @param Empty container to be filled with T1
            /// @param Empty container to be filled with T2
			//--------------------------------------------------------------------------------------------------
			template <typename T1, typename T2> void QuerySceneForComponents(std::vector<T1*> &outComponents1, std::vector<T2*> &outComponents2,
                                                                             u32 inudwQueryMask = 0)
			{
				for(SharedEntityList::const_iterator it = mEntities.begin(); it != mEntities.end(); ++it)
				{
					(*it)->GetComponents<T1, T2>(outComponents1, outComponents2, inudwQueryMask, false);
				}
			}
            //--------------------------------------------------------------------------------------------------
			/// Query Scene For Managed Components
			///
			/// Traverse the scene for the given component type and fill the list with those components
            ///
            /// @param Empty container to be filled with T1
            /// @param Empty container to be filled with T2
			//--------------------------------------------------------------------------------------------------
			template <typename T1, typename T2> void QuerySceneForManagedComponents(std::vector<std::shared_ptr<T1> > &outComponents1, std::vector<std::shared_ptr<T2> > &outComponents2,
                                                                                    u32 inudwQueryMask = 0)
			{
				for(SharedEntityList::const_iterator it = mEntities.begin(); it != mEntities.end(); ++it)
				{
					(*it)->GetManagedComponents<T1, T2>(outComponents1, outComponents2, inudwQueryMask, false);
				}
			}
            //--------------------------------------------------------------------------------------------------
			/// Query Scene For Components
			///
			/// Traverse the scene for the given component type and fill the list with those components
            ///
			/// @param Empty container to be filled with T1
            /// @param Empty container to be filled with T2
            /// @param Empty container to be filled with T3
			//--------------------------------------------------------------------------------------------------
			template <typename T1, typename T2, typename T3> void QuerySceneForComponents(std::vector<T1*> &outComponents1, std::vector<T2*> &outComponents2, std::vector<T3*> &outComponents3,
                                                                                          u32 inudwQueryMask = 0)
			{
				for(SharedEntityList::const_iterator it = mEntities.begin(); it != mEntities.end(); ++it)
				{
					(*it)->GetComponents<T1, T2, T3>(outComponents1, outComponents2, outComponents3, inudwQueryMask, false);
				}
			}
            //--------------------------------------------------------------------------------------------------
			/// Query Scene For Managed Components
			///
			/// Traverse the scene for the given component type and fill the list with those components
            ///
            /// @param Empty container to be filled with T1
            /// @param Empty container to be filled with T2
            /// @param Empty container to be filled with T3
			//--------------------------------------------------------------------------------------------------
			template <typename T1, typename T2, typename T3> void QuerySceneForManagedComponents(std::vector<std::shared_ptr<T1> > &outComponents1, std::vector<std::shared_ptr<T1> > &outComponents2, std::vector<std::shared_ptr<T1> > &outComponents3,
                                                                                                 u32 inudwQueryMask = 0)
			{
				for(SharedEntityList::const_iterator it = mEntities.begin(); it != mEntities.end(); ++it)
				{
					(*it)->GetManagedComponents<T1, T2, T3>(outComponents1, outComponents2, outComponents3, inudwQueryMask, false);
				}
			}
			
			//==================================================================================================
			// USER INTERFACE
			//==================================================================================================
            //--------------------------------------------------------------------------------------------------
			/// Get Window Pointer
			///
			/// @return The main window that all the scene's UI is attached to.
			//--------------------------------------------------------------------------------------------------
			GUI::Window* GetWindowPtr();

			//--------------------------------------------------------------------------------------------------
			/// Update
			///
			/// Updates anything in the scene graph which needs to be updated (e.g. NodeAnimations)
			///
			/// @param delta time in seconds
			//--------------------------------------------------------------------------------------------------
			void Update(f32 infDT);
				
        private:
            //-------------------------------------------------------
			/// Remove Entity
			///
			/// Remove the entity from the scene
			///
			/// @param Entity pointer
			//-------------------------------------------------------
			void RemoveEntity(const EntitySPtr& inpEntity);
            //-------------------------------------------------------
			/// Remove All Entities
			///
			/// Remove all the entities from the scene
			//-------------------------------------------------------
			void RemoveAllEntities();
            
		protected:
			
			//Octree mSpatialGraph;				//Scene culling tree
			
			GUI::Window* mpRootWindow;        //Main window for attaching UI components
			
			SharedEntityList mEntities;
            
            friend class Entity;
		};		
	}
}

#endif

/*
 *  Skeleton.h
 *  MoFlowSkeleton
 *
 *  Created by Ian Copland on 13/10/2011.
 *  Copyright 2011 Tag Games Ltd. All rights reserved.
 *
 */

#ifndef _MOFLO_RENDERING_SKELETON_H_
#define _MOFLO_RENDERING_SKELETON_H_

#include <ChilliSource/ChilliSource.h>

#include <vector>

namespace ChilliSource
{
	namespace Rendering
	{
        //=========================================================================
		/// Skeleton Node
		///
		/// a struct describing a single skeleton node.
		//=========================================================================
		struct SkeletonNode
		{
			std::string mstrName;
			s32 mdwParentIndex;
		};
		//=========================================================================
		/// Skeleton
		///
		/// a simple class that describes a skeleton for skeletal animation.
		//=========================================================================
		class Skeleton
		{
		public:
			Skeleton();
			~Skeleton();
			//-------------------------------------------------------------------------
			/// Get Node By Name
			///
			/// returns the node with the given name.
			///
			/// @param the nodes name
			/// @return a smart pointer to the node
			//-------------------------------------------------------------------------
			SkeletonNodeSPtr GetNodeByName(const std::string& instrName) const;
            //-------------------------------------------------------------------------
			/// Get Node Index By Name
			///
			/// returns the index of the node with the given name. This will return
            /// -1 if no node with the given name could be found.
			///
			/// @param the nodes name
			/// @return The nodes index
			//-------------------------------------------------------------------------
			s32 GetNodeIndexByName(const std::string& instrName) const;
			//-------------------------------------------------------------------------
			/// Get Node By Index
			///
			/// returns the node at the given index.
			///
			/// @param the index.
			/// @param a smart pointer to the node.
			//-------------------------------------------------------------------------
			SkeletonNodeSPtr GetNodeByIndex(u32 indwIndex) const;
			//-------------------------------------------------------------------------
			/// Get Num Nodes
			///
			/// returns the number of nodes in the skeleton
			///
			/// @return the number of nodes
			//-------------------------------------------------------------------------
			s32 GetNumNodes() const;
            //-------------------------------------------------------------------------
			/// Get Num Joints
			///
			/// returns the number of joints in the skeleton
			///
			/// @return the number of joints.
			//-------------------------------------------------------------------------
			u32 GetNumJoints() const;
			//-------------------------------------------------------------------------
			/// Get Nodes
			///
			/// returns the array of nodes
			///
			/// @return the dynamic array of nodes
			//-------------------------------------------------------------------------
			const std::vector<SkeletonNodeSPtr>& GetNodes() const;
            //-------------------------------------------------------------------------
			/// Get Joint Indices
			///
			/// @return the array of joint indices
			//-------------------------------------------------------------------------
			const std::vector<s32>& GetJointIndices() const;
			//-------------------------------------------------------------------------
			/// Add Node
			///
			/// Adds a new node to the skeleton with the given name and parent.
			///
			/// @param the name
			/// @param the parent index
			//-------------------------------------------------------------------------
			void AddNode(const std::string& instrName, s32 indwParentIndex);
            //-------------------------------------------------------------------------
			/// Add Joint Index
			///
			/// @param An index into the skeleton node list denoting a joint.
			//-------------------------------------------------------------------------
			void AddJointIndex(s32 indwJointIndex);
			
		private:
			
			std::vector<SkeletonNodeSPtr> mapNodes;
            std::vector<s32> madwJoints;
		};
	}
}
#endif
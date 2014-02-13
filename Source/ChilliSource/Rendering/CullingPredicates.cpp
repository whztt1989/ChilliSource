//
//  CullingPredicates.cpp
//  moFlow
//
//  Created by Scott Downie on 04/10/2012.
//  Copyright (c) 2012 Tag Games. All rights reserved.
//

#include <moFlo/Rendering/CullingPredicates.h>
#include <moFlo/Rendering/Components/CameraComponent.h>
#include <moFlo/Rendering/Components/RenderComponent.h>

namespace moFlo
{
    namespace Rendering
    {
        bool CViewportCullPredicate::CullItem(CCameraComponent* inpCamera, IRenderComponent* inpItem) const
        {
            return false;
        }
        
        bool CFrustumCullPredicate::CullItem(CCameraComponent* inpCamera, IRenderComponent* inpItem) const
        {
            return !inpCamera->GetFrustumPtr()->SphereCullTest(inpItem->GetBoundingSphere());
        }
    }
}


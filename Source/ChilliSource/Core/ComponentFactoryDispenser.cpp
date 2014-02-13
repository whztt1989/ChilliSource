//
//  ResourceManagerDispenser.cpp
//  moFloTest
//
//  Created by Scott Downie on 02/05/2011.
//  Copyright 2011 Tag Games. All rights reserved.
//

#include <moFlo/Core/ComponentFactoryDispenser.h>
#include <moFlo/Core/ComponentFactory.h>

#include <moFlo/Audio/AudioComponentFactory.h>
#include <moFlo/Audio/AudioComponent.h>

#include <moFlo/Rendering/RenderComponentFactory.h>
#include <moFlo/Rendering/Components/SpriteComponent.h>

namespace moFlo
{
    namespace Core
    {
        CComponentFactoryDispenser* CComponentFactoryDispenser::pInstance = NULL;
        //----------------------------------------------------
        /// Constructor
        ///
        /// Singleton instance
        //----------------------------------------------------
        CComponentFactoryDispenser::CComponentFactoryDispenser(CApplication* inpApp) : mpApp(inpApp)
        {
            pInstance = this;
        }
        //--------------------------------------------------------------------------------------------------
        /// Get Singleton Ptr
        ///
        /// @return Singleton instance
        //--------------------------------------------------------------------------------------------------
        CComponentFactoryDispenser* CComponentFactoryDispenser::GetSingletonPtr()
        {
            return pInstance;
        }
		//--------------------------------------------------------------------------------------------------
		/// @return Singleton instance
		//--------------------------------------------------------------------------------------------------
		CComponentFactoryDispenser& CComponentFactoryDispenser::GetSingleton()
        {
			return *pInstance;
		}
        //--------------------------------------------------------------------------------------------------
		/// Register Component Factory
		///
		/// Adds a component factory to the application pool. 
		/// @param Component factory
		//--------------------------------------------------------------------------------------------------
		void CComponentFactoryDispenser::RegisterComponentFactory(IComponentFactory * inpComponentFactory)
		{
			mComponentFactories.push_back(inpComponentFactory);
		}
        //--------------------------------------------------------------------------------------------------
        /// Get Factory Producing
        ///
        /// Looks for a factory that can create the given type
        /// @param The type ID of the object you wish to create (i.e. CMesh, ITexture)
        /// @return Factory that can produce the given interface or NULL if none available
        //--------------------------------------------------------------------------------------------------
        IComponentFactory* CComponentFactoryDispenser::GetFactoryProducing(const std::string & insName)
        {
            for (DYNAMIC_ARRAY<IComponentFactory*>::iterator it = mComponentFactories.begin(); it != mComponentFactories.end(); ++it) 
			{
                if((*it)->CanProduceComponentWithTypeName(insName)) 
                {
                    return (*it);
                }
			}
			
			WARNING_LOG("Application cannot find factory producing: " + insName);
			return NULL;
        }
        //--------------------------------------------------------------------------------------------------
        /// Get Factory Producing
        ///
        /// Looks for a factory that can create the given component type
        /// @param The type ID of the object you wish to create (i.e. Sprite, Static Mesh)
        /// @return Factory that creates the given component
        //--------------------------------------------------------------------------------------------------
        IComponentFactory* CComponentFactoryDispenser::GetFactoryProducing(InterfaceIDType inInterfaceID)
        {
            for (DYNAMIC_ARRAY<IComponentFactory*>::iterator it = mComponentFactories.begin(); it != mComponentFactories.end(); ++it) 
			{
                if((*it)->CanProduceComponentWithInterface(inInterfaceID)) 
                {
                    return (*it);
                }
			}
			
			WARNING_LOG("Application cannot find factory for interface ID: " + STRING_CAST(inInterfaceID));
			return NULL;
        }
        //--------------------------------------------------------------------------------------------------
        /// Get Factory With Interface
        ///
        /// Looks for a factory with the given interface
        /// @param The type ID of the factory interface you are seeking
        /// @return Factory that implements the given interface or NULL if none available
        //--------------------------------------------------------------------------------------------------
        IComponentFactory* CComponentFactoryDispenser::GetFactoryWithInterface(InterfaceIDType inInterfaceID)
        {
            for(DYNAMIC_ARRAY<IComponentFactory*>::iterator it = mComponentFactories.begin(); it != mComponentFactories.end(); ++it) 
			{
                if((*it)->IsA(inInterfaceID)) 
                {
                    return (*it);
                }
			}
            
            WARNING_LOG("Cannot find component producer for interface ID: " + STRING_CAST(inInterfaceID));
            return NULL;
        }
        //--------------------------------------------------------------------
        /// Destructor
        //--------------------------------------------------------------------
        CComponentFactoryDispenser::~CComponentFactoryDispenser()
        {

        }
    }
}

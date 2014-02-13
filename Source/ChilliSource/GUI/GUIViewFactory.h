//
//  GUIViewFactory.h
//  moFlo
//
//  Created by Scott Downie on 21/04/2011.
//  Copyright 2011 Tag Games. All rights reserved.
//

#ifndef _MOFLO_GUI_GUIVIEWFACTORY_H_
#define _MOFLO_GUI_GUIVIEWFACTORY_H_

#include <moFlo/Core/FastDelegate.h>
#include <moFlo/Core/ParamDictionary.h>

#include <moFlo/GUI/ForwardDeclarations.h>
#include <moFlo/Core/FileIO/FileSystem.h>
#include <moFlo/Core/XML/rapidxml_forward.h>

namespace moFlo
{
    namespace GUI
    {
        //--------------------------------------------------------
        /// Create GUI
        ///
        /// Templated call to the GUI view constructor
        /// with the given params
        ///
        /// @param Param dictionary
        //--------------------------------------------------------
        template<typename T> GUIViewPtr CreateGUI(const Core::ParamDictionary & insParams)
        {
            return GUIViewPtr(new T(insParams));   
        }
        
        class CGUIViewFactory
        {
        public:  
            typedef fastdelegate::FastDelegate1<const Core::ParamDictionary&, GUIViewPtr> GUIViewCreateDelegate; 
            //--------------------------------------------------------
            /// Register Defaults
            ///
            /// Register default views with the factory
            //--------------------------------------------------------
            static void RegisterDefaults();
            //--------------------------------------------------------
            /// Create GUI View From Script
            ///
            /// Creates a widget view from the given script file
            ///
            /// @param The storage location to load from
            /// @param the file path
			/// @param Optional dynamic array to which views will be pushed
            /// @return GUI View
            //--------------------------------------------------------
            static GUIViewPtr CreateGUIViewFromScript(Core::STORAGE_LOCATION ineStorageLocation, const std::string& instrScriptFile, DYNAMIC_ARRAY<GUIViewPtr>* outpViews = NULL);
			//--------------------------------------------------------
            /// Create GUI View 
            ///
            /// Creates a widget view of the given type
            ///
            /// @return GUI View
            //--------------------------------------------------------
            static GUIViewPtr CreateGUIView(const std::string& instrTypeName, const Core::ParamDictionary& insParams);
			//--------------------------------------------------------
			/// Register 
			///
			/// Register a custom view type
			///
			/// @param View type name
			//--------------------------------------------------------
			template <typename T> static void Register(const std::string& instrName)
			{
				mmapDelegateToType.insert(std::make_pair(instrName, GUIViewCreateDelegate(&CreateGUI<T>)));
			}
			//--------------------------------------------------------
			/// Register 
			///
			/// Register a custom view type
			///
			/// @param View type name
			//--------------------------------------------------------
			template <typename T, typename BaseType> static void Register(const std::string& instrName)
			{
				mmapDelegateToType.insert(std::make_pair(instrName, GUIViewCreateDelegate(&CreateGUI<T>)));

#ifdef ENABLE_MOFLOW_REFLECTION
				T::StaticMetaClass->SetBaseClass(BaseType::StaticMetaClass);
#endif
			}
        private:
            //--------------------------------------------------------
            /// Create View
            ///
            /// Recursive function used to create subviews
            ///
            /// @param View XML element
            /// @return Created view
            //--------------------------------------------------------
            static GUIViewPtr CreateView(rapidxml::xml_node<char> * ipViewElement, DYNAMIC_ARRAY<GUIViewPtr>* outpViews = NULL);
            
        private:
            
            typedef HASH_MAP<std::string, GUIViewCreateDelegate> MapDelegateToString;
            static MapDelegateToString mmapDelegateToType;
        };
    }
}

#endif
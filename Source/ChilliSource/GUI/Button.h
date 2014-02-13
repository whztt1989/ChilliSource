//
//  Button.h
//  moFlo
//
//  Created by Scott Downie on 26/04/2011.
//  Copyright 2011 Tag Games. All rights reserved.
//

#ifndef _MOFLO_GUI_BUTTON_H_
#define _MOFLO_GUI_BUTTON_H_

#include <moFlo/GUI/GUIView.h>

#ifdef ENABLE_MOFLOW_REFLECTION
#include <moFlo/Core/Reflection/Reflection.h>
#define DECLARE_ACTION 
#else

#endif

namespace moFlo
{
    namespace GUI
    {
        typedef fastdelegate::FastDelegate1<IButton*> ButtonEventDelegate;
        
        class IButton : public CGUIView
        {
        public:

			DECLARE_META_CLASS(IButton)

            IButton(){}
            IButton(const Core::ParamDictionary& insParams) : CGUIView(insParams){}
            
            //--------------------------------------------------
            /// Get Activated Event
            ///
            /// @return Event triggered when the button is 
            /// activated
            //--------------------------------------------------
            IEvent<ButtonEventDelegate>& GetActivatedEvent();
            
        protected:
            
            CEvent1<ButtonEventDelegate> mOnButtonActivatedEvent;
        };
    }
}

#endif
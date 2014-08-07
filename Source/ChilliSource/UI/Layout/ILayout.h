//
//  ILayout.h
//  Chilli Source
//  Created by Scott Downie on 18/04/2014.
//
//  The MIT License (MIT)
//
//  Copyright (c) 2014 Tag Games Limited
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

#ifndef _CHILLISOURCE_UI_LAYOUT_ILAYOUT_H_
#define _CHILLISOURCE_UI_LAYOUT_ILAYOUT_H_

#include <ChilliSource/ChilliSource.h>
#include <ChilliSource/UI/Base/PropertyMap.h>

#include <vector>

namespace ChilliSource
{
    namespace UI
    {
        //----------------------------------------------------------------------------------------
        /// Interface for laying out widgets. Each widget has its own layout
        ///
        /// @author S Downie
        //----------------------------------------------------------------------------------------
        class ILayout
        {
        public:
            CS_DECLARE_NOCOPY(ILayout);
            //----------------------------------------------------------------------------------------
            /// Constructor
            ///
            /// @author S Downie
            //----------------------------------------------------------------------------------------
            ILayout() = default;
            //----------------------------------------------------------------------------------------
            /// @author S Downie
            ///
            /// @param Layout type
            ///
            /// @return The list of properties supported by the layout of given type
            //----------------------------------------------------------------------------------------
            static std::vector<PropertyMap::PropertyDesc> GetPropertyDescs(LayoutType in_type);
            //----------------------------------------------------------------------------------------
            /// Create the layout sizes and positions based on the current layout properties and the
            /// owning widget.
            ///
            /// @author S Downie
            //----------------------------------------------------------------------------------------
            virtual void BuildLayout() = 0;
            //----------------------------------------------------------------------------------------
            /// Get the final size of the widget that occupies the space at the given index
            ///
            /// @author S Downie
            ///
            /// @param Space index
            ///
            /// @return Final absolute screen size
            //----------------------------------------------------------------------------------------
            virtual Core::Vector2 GetSizeForIndex(u32 in_index) const = 0;
            //----------------------------------------------------------------------------------------
            /// Get the local position of the widget that occupies the space at the given index
            ///
            /// @author S Downie
            ///
            /// @param Space index
            ///
            /// @return Local position (aligned middle centre of the cell)
            //----------------------------------------------------------------------------------------
            virtual Core::Vector2 GetPositionForIndex(u32 in_index) const = 0;
            //----------------------------------------------------------------------------------------
            /// @author S Downie
            ///
            /// @param The widget that owns and uses this layout
            //----------------------------------------------------------------------------------------
            virtual void SetWidget(Widget* in_widget) = 0;
            //----------------------------------------------------------------------------------------
            /// Virtual destructor
            ///
            /// @author S Downie
            //----------------------------------------------------------------------------------------
            virtual ~ILayout(){}
        };
    }
}

#endif
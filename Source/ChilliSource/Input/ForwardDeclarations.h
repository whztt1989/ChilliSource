//
//  ForwardDeclarations.h
//  Chilli Source
//  Created by Ian Copland on 26/02/2014.
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

#ifndef _CHILLISOURCE_INPUT_FORWARDDECLARATIONS_H_
#define _CHILLISOURCE_INPUT_FORWARDDECLARATIONS_H_

#include <ChilliSource/Core/Base/StandardMacros.h>

#include <memory>

namespace CS
{
    //--------------------------------------------------
    /// Base
    //--------------------------------------------------
    CS_FORWARDDECLARE_CLASS(Filter);
    //--------------------------------------------------
    /// Accelerometer
    //--------------------------------------------------
    CS_FORWARDDECLARE_CLASS(Accelerometer);
    //--------------------------------------------------
    /// Device Buttons
    //--------------------------------------------------
    CS_FORWARDDECLARE_CLASS(DeviceButtonSystem);
    //--------------------------------------------------
    /// Gestures
    //--------------------------------------------------
    CS_FORWARDDECLARE_CLASS(DragGesture);
    CS_FORWARDDECLARE_CLASS(HoldGesture);
    CS_FORWARDDECLARE_CLASS(Gesture);
    CS_FORWARDDECLARE_CLASS(GestureSystem);
    CS_FORWARDDECLARE_CLASS(PinchGesture);
    CS_FORWARDDECLARE_CLASS(RotationGesture);
    CS_FORWARDDECLARE_CLASS(TapGesture);
    //--------------------------------------------------
    /// Keyboard
    //--------------------------------------------------
    CS_FORWARDDECLARE_CLASS(Keyboard);
    enum class KeyCode;
    enum class ModifierKeyCode;
    //--------------------------------------------------
    /// Pointer
    //--------------------------------------------------
    CS_FORWARDDECLARE_CLASS(Pointer);
    CS_FORWARDDECLARE_CLASS(PointerSystem);
    //--------------------------------------------------
    /// Text Entry
    //--------------------------------------------------
    CS_FORWARDDECLARE_CLASS(TextEntry);
}

#endif

--
--  ToggleButton.lua
--  Chilli Source
--  Created by Scott Downie on 30/08/2014.
--
--  The MIT License (MIT)
--
--  Copyright (c) 2014 Tag Games Limited
--
--  Permission is hereby granted, free of charge, to any person obtaining a copy
--  of this software and associated documentation files (the "Software"), to deal
--  in the Software without restriction, including without limitation the rights
--  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
--  copies of the Software, and to permit persons to whom the Software is
--  furnished to do so, subject to the following conditions:
--
--  The above copyright notice and this permission notice shall be included in
--  all copies or substantial portions of the Software.
--
--  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
--  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
--  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
--  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
--  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
--  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
--  THE SOFTWARE.
--

----------------------------------------------------------------
-- This is the logic that describes a simple toggle button.
-- A toggle button will be toggle between an on and off state when pressed.
-- The button only responds to the primary input type but multiple pointers
-- can interact with the button at the same time.
--
-- The on and off looks can be created either with an additional texture
-- or simply a colour change.
--
-- @author S Downie
----------------------------------------------------------------

--Caching the functions locally means we don't have to peform a lookup for each call
local setTexture = Drawable.setTexture
local setTextureAtlas = Drawable.setTextureAtlas
local setTextureAtlasId = Drawable.setTextureAtlasId
local setColour = Widget.setColour
local getDrawable = Widget.getDrawable
local getStorageLocationCustomProperty = Widget.getStorageLocationCustomProperty
local getStringCustomProperty = Widget.getStringCustomProperty
local getColourCustomProperty = Widget.getColourCustomProperty
local getPointerId = Pointer.getId
local setBoolCustomProperty = Widget.setBoolCustomProperty

local activePointerIds = {}
local highlightingPointerIds = {}
local isToggledOn = false

-----------------------------------------------------
-- Called when the widget is added to the canvas
--
-- @author S Downie
-----------------------------------------------------
function onAddedToCanvas()
    off()
end
-----------------------------------------------------
-- Called when the widget recieves an input press
-- event within its bounds. This will toggle the
-- to the opposite state.
--
-- @author S Downie
--
-- @param Pointer that triggered the event
-- @param Timestamp of the input event
-- @param Input type i.e. touch, left mouse, right mouse, etc.
-----------------------------------------------------
function onPressedInside(in_pointer, in_timeStamp, in_inputType)
    if in_inputType == InputType.Default then
        pointerId = getPointerId(in_pointer)
        activePointerIds[pointerId] = true
        highlightingPointerIds[pointerId] = true
        highlight()
    end
end
-----------------------------------------------------
-- Called when the widget recieves an input move
-- event within its bounds having previously receieved
-- one outside the bounds. This will toggle back to highlight
-- state.
--
-- @author S Downie
--
-- @param Pointer that triggered the event
-- @param Timestamp of the input event
-----------------------------------------------------
function onMoveEntered(in_pointer, in_timeStamp)
    pointerId = getPointerId(in_pointer)
    if activePointerIds[pointerId] then
        highlightingPointerIds[pointerId] = true
        highlight()
    end
end
-----------------------------------------------------
-- Called when the widget recieves an input move
-- event outside its bounds having previously receieved
-- one inside the bounds. This will toggle back to normal
-- state.
--
-- @author S Downie
--
-- @param Pointer that triggered the event
-- @param Timestamp of the input event
-----------------------------------------------------
function onMoveExited(in_pointer, in_timeStamp)
    pointerId = getPointerId(in_pointer)
    if activePointerIds[pointerId] then
        highlightingPointerIds[pointerId] = nil
        if next(highlightingPointerIds) == nil then
            unhighlight()
        end
    end
end
-----------------------------------------------------
-- Called when the widget recieves an input released
-- event within its bounds having previously receieved
-- a pressed event.
--
-- @author S Downie
--
-- @param Pointer that triggered the event
-- @param Timestamp of the input event
-- @param Input type i.e. touch, left mouse, right mouse, etc.
-----------------------------------------------------
function onReleasedInside(in_pointer, in_timeStamp, in_inputType)
    pointerId = getPointerId(in_pointer)
    if activePointerIds[pointerId] then
        activePointerIds[pointerId] = nil
        highlightingPointerIds[pointerId] = nil
        toggle()
    end
end
-----------------------------------------------------
-- Called when the widget recieves an input released
-- event outside its bounds having previously receieved
-- a pressed event.
--
-- @author S Downie
--
-- @param Pointer that triggered the event
-- @param Timestamp of the input event
-- @param Input type i.e. touch, left mouse, right mouse, etc.
-----------------------------------------------------
function onReleasedOutside(in_pointer, in_timeStamp, in_inputType)
    pointerId = getPointerId(in_pointer)
    if activePointerIds[pointerId] then
        activePointerIds[pointerId] = nil
    end
end
-----------------------------------------------------
-- Sets the look of the button to the opposite state
--
-- @author S Downie
-----------------------------------------------------
function toggle()
    if isToggledOn == true then
        off()
    else
        on()
    end
end
-----------------------------------------------------
-- Sets the look of the button to the highlight of
-- the current state
--
-- @author S Downie
-----------------------------------------------------
function highlight()
    if isToggledOn == true then
        highlightOn()
    else
        highlightOff()
    end
end
-----------------------------------------------------
-- Reverts the look back to the current on/off state
--
-- @author S Downie
-----------------------------------------------------
function unhighlight()
    if isToggledOn == true then
        on()
    else
        off()
    end
end
-----------------------------------------------------
-- Set the view of the button to on
--
-- @author S Downie
-----------------------------------------------------
function on()
    drawable = getDrawable(this)
    if drawable then
        path = getStringCustomProperty(this, "OnTexturePath")
        if path ~= "" then
            location = getStorageLocationCustomProperty(this, "OnTextureLocation")
            setTexture(drawable, location, path)
        end
        path = getStringCustomProperty(this, "OnAtlasPath")
        if path ~= "" then
            location = getStorageLocationCustomProperty(this, "OnAtlasLocation")
            setTextureAtlas(drawable, location, path)
            id = getStringCustomProperty(this, "OnAtlasId")
            setTextureAtlasId(drawable, id)
        end
    end

    r, g, b, a = getColourCustomProperty(this, "OnColour")
    setColour(this, r, g, b, a)

    isToggledOn = true
    setBoolCustomProperty(this, "isToggledOn", isToggledOn)
end
-----------------------------------------------------
-- Set the view of the button to off
--
-- @author S Downie
-----------------------------------------------------
function off()
    drawable = getDrawable(this)
    if drawable then
        path = getStringCustomProperty(this, "OffTexturePath")
        if path ~= "" then
            location = getStorageLocationCustomProperty(this, "OffTextureLocation")
            setTexture(drawable, location, path)
        end
        path = getStringCustomProperty(this, "OffAtlasPath")
        if path ~= "" then
            location = getStorageLocationCustomProperty(this, "OffAtlasLocation")
            setTextureAtlas(drawable, location, path)
            id = getStringCustomProperty(this, "OffAtlasId")
            setTextureAtlasId(drawable, id)
        end
    end

    r, g, b, a = getColourCustomProperty(this, "OffColour")
    setColour(this, r, g, b, a)

    isToggledOn = false
    setBoolCustomProperty(this, "isToggledOn", isToggledOn)
end
-----------------------------------------------------
-- Set the view of the button to be highlighted for the 
-- on state
--
-- @author S Downie
-----------------------------------------------------
function highlightOn()
    drawable = getDrawable(this)
    if drawable then
        path = getStringCustomProperty(this, "OnHighlightTexturePath")
        if path ~= "" then
            location = getStorageLocationCustomProperty(this, "OnHighlightTextureLocation")
            setTexture(drawable, location, path)
        end
        path = getStringCustomProperty(this, "OnHighlightAtlasPath")
        if path ~= "" then
            location = getStorageLocationCustomProperty(this, "OnHighlightAtlasLocation")
            setTextureAtlas(drawable, location, path)
            id = getStringCustomProperty(this, "OnHighlightAtlasId")
            setTextureAtlasId(drawable, id)
        end
    end

    r, g, b, a = getColourCustomProperty(this, "OnHighlightColour")
    setColour(this, r, g, b, a)
end
-----------------------------------------------------
-- Set the view of the button to be highlighted for the
-- off state
--
-- @author S Downie
-----------------------------------------------------
function highlightOff()
    drawable = getDrawable(this)
    if drawable then
        path = getStringCustomProperty(this, "OffHighlightTexturePath")
        if path ~= "" then
            location = getStorageLocationCustomProperty(this, "OffHighlightTextureLocation")
            setTexture(drawable, location, path)
        end
        path = getStringCustomProperty(this, "OffHighlightAtlasPath")
        if path ~= "" then
            location = getStorageLocationCustomProperty(this, "OffHighlightAtlasLocation")
            setTextureAtlas(drawable, location, path)
            id = getStringCustomProperty(this, "OffHighlightAtlasId")
            setTextureAtlasId(drawable, id)
        end
    end

    r, g, b, a = getColourCustomProperty(this, "OffHighlightColour")
    setColour(this, r, g, b, a)
end
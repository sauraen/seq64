/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.2.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_D7C02D1ED81BB932__
#define __JUCE_HEADER_D7C02D1ED81BB932__

//[Headers]     -- You can add your own extra header files here --
/*
 * ============================================================================
 *
 * IEEditor.h
 * Small component to edit the metadata in index entries
 *
 * From seq64 - Sequenced music editor for first-party N64 games
 * Copyright (C) 2014-2018 Sauraen
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * ============================================================================
*/

#include "JuceHeader.h"
#include "seq64.h"
#include "FilesPane.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class IEEditor  : public Component,
                  public ButtonListener
{
public:
    //==============================================================================
    IEEditor (SEQ64& seq64_, FilesPane& fp_, uint32 ieaddr_);
    ~IEEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    SEQ64& seq64;
    FilesPane& fp;
    uint32 ieaddr;
    int indextype;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<TextButton> btnOverride;
    ScopedPointer<Label> lblAddress;
    ScopedPointer<TextEditor> txtAddress;
    ScopedPointer<Label> lblAddress2;
    ScopedPointer<TextEditor> txtLength;
    ScopedPointer<Label> label;
    ScopedPointer<TextEditor> txtF1;
    ScopedPointer<TextEditor> txtF2;
    ScopedPointer<TextEditor> txtF3;
    ScopedPointer<TextEditor> txtF4;
    ScopedPointer<TextEditor> txtF5;
    ScopedPointer<TextEditor> txtF6;
    ScopedPointer<TextEditor> txtF7;
    ScopedPointer<TextEditor> txtF8;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IEEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_D7C02D1ED81BB932__

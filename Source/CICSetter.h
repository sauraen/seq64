/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_5107FDCBAD6A3CDC__
#define __JUCE_HEADER_5107FDCBAD6A3CDC__

//[Headers]     -- You can add your own extra header files here --
/*
 * ============================================================================
 *
 * CICSetter.h
 * Small component to get a CIC value from the user
 *
 * From seq64 - Sequenced music editor for first-party N64 games
 * Copyright (C) 2014-2017 Sauraen
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
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class CICSetter  : public Component,
                   public ComboBoxListener,
                   public ButtonListener
{
public:
    //==============================================================================
    CICSetter (SEQ64& seq64_);
    ~CICSetter();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    void buttonClicked (Button* buttonThatWasClicked);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    SEQ64& seq64;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> label;
    ScopedPointer<ComboBox> cbxCIC;
    ScopedPointer<TextButton> btnOK;
    ScopedPointer<TextButton> btnCancel;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CICSetter)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_5107FDCBAD6A3CDC__

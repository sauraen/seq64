/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.5

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
/*
 * ============================================================================
 *
 * IEEditor.h
 * Small component to edit the metadata in index entries
 *
 * From seq64 - Sequenced music editor for first-party N64 games
 * Copyright (C) 2014-2019 Sauraen
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
                  public Button::Listener
{
public:
    //==============================================================================
    IEEditor (IndexedFile& ifile_, FilesPane& fp_, int entry_);
    ~IEEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    IndexedFile& ifile;
    FilesPane& fp;
    int entry;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<TextButton> btnOverride;
    std::unique_ptr<Label> lblAddress;
    std::unique_ptr<TextEditor> txtAddress;
    std::unique_ptr<Label> lblAddress2;
    std::unique_ptr<TextEditor> txtLength;
    std::unique_ptr<Label> label;
    std::unique_ptr<TextEditor> txtF1;
    std::unique_ptr<TextEditor> txtF2;
    std::unique_ptr<TextEditor> txtF3;
    std::unique_ptr<TextEditor> txtF4;
    std::unique_ptr<TextEditor> txtF5;
    std::unique_ptr<TextEditor> txtF6;
    std::unique_ptr<TextEditor> txtF7;
    std::unique_ptr<TextEditor> txtF8;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IEEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]


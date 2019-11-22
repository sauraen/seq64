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
 * Finder.h
 * GUI component for data finder screen
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
#include "TextListModel.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class Finder  : public Component,
                public TextEditor::Listener,
                public TextListModel::Listener,
                public Button::Listener
{
public:
    //==============================================================================
    Finder (SEQ64& seq64_);
    ~Finder();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void textEditorTextChanged(TextEditor& editorThatWasChanged);
    void rowSelected(TextListModel* parent, int row);

    void findIndex(int align, bool inorder);
    void findAudiobank(int align);
    void findAudioseq(int align, int minlen);
    void findAudiotable(int align);
    void renderHex(uint32 addr, bool updateTextBox);
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    SEQ64& seq64;

    std::unique_ptr<TextListModel> lsmResults;
    std::unique_ptr<ListBox> lstResults;

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<GroupComponent> grpOptions;
    std::unique_ptr<GroupComponent> grpTarget;
    std::unique_ptr<ToggleButton> optTargetIndex;
    std::unique_ptr<ToggleButton> optTargetAudiobank;
    std::unique_ptr<ToggleButton> optTargetAudioseq;
    std::unique_ptr<ToggleButton> optTargetAudiotable;
    std::unique_ptr<ToggleButton> chkIndexUnmodded;
    std::unique_ptr<Label> label;
    std::unique_ptr<TextEditor> txtAudioseqMinLen;
    std::unique_ptr<Label> label2;
    std::unique_ptr<ToggleButton> optAlign4;
    std::unique_ptr<ToggleButton> optAlign8;
    std::unique_ptr<ToggleButton> optAlign16;
    std::unique_ptr<Label> label3;
    std::unique_ptr<TextButton> btnGo;
    std::unique_ptr<TextEditor> txtHex;
    std::unique_ptr<Label> label4;
    std::unique_ptr<TextEditor> txtHexAddr;
    std::unique_ptr<TextButton> btnUp10;
    std::unique_ptr<TextButton> btnUp100;
    std::unique_ptr<TextButton> btnUp1000;
    std::unique_ptr<TextButton> btnDn10;
    std::unique_ptr<TextButton> btnDn100;
    std::unique_ptr<TextButton> btnDn1000;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Finder)
};

//[EndFile] You can add extra defines here...
//[/EndFile]


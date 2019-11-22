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
 * AudioseqPane.h
 * GUI component for sequence editor screen
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
class AudioseqPane  : public Component,
                      public TextEditor::Listener,
                      public TextListModel::Listener,
                      public Button::Listener,
                      public ComboBox::Listener
{
public:
    //==============================================================================
    AudioseqPane (SEQ64& seq64_);
    ~AudioseqPane();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void rowSelected(TextListModel* parent, int row);
    void textEditorTextChanged(TextEditor& editorThatWasChanged);
    bool keyPressed(const KeyPress& key) override;

    String getCommandDesc(ValueTree cmd);
    void refreshCmdList();
    void refreshCmdControls();
    void refreshParamList();
    void refreshParamControls();
    void fillMeaningsBox(String action);
    void fillSeqSections();
    void fillSeqCommands();
    void refreshSeqCmdControls();
    void refreshSeqCmdParamControls();

    void seqStructureChanged();

    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;
    void visibilityChanged() override;
    void broughtToFront() override;
    void focusGained (FocusChangeType cause) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    SEQ64& seq64;

    ValueTree selcmd;
    ValueTree selparam;

    std::unique_ptr<TextListModel> lsmCommands;
    std::unique_ptr<ListBox> lstCommands;

    std::unique_ptr<TextListModel> lsmParameters;
    std::unique_ptr<ListBox> lstParameters;

    std::unique_ptr<TextListModel> lsmSeqSections;
    std::unique_ptr<ListBox> lstSeqSections;

    std::unique_ptr<TextListModel> lsmSeqCommands;
    std::unique_ptr<ListBox> lstSeqCommands;

    std::unique_ptr<TextListModel> lsmSeqCmdParams;
    std::unique_ptr<ListBox> lstSeqCmdParams;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<GroupComponent> groupComponent;
    std::unique_ptr<GroupComponent> groupComponent3;
    std::unique_ptr<GroupComponent> groupComponent6;
    std::unique_ptr<GroupComponent> groupComponent5;
    std::unique_ptr<Label> label10;
    std::unique_ptr<TextEditor> txtCmd;
    std::unique_ptr<TextButton> btnCmdAdd;
    std::unique_ptr<TextButton> btnCmdDel;
    std::unique_ptr<ToggleButton> optCmdDataFixed;
    std::unique_ptr<ToggleButton> optCmdDataVar;
    std::unique_ptr<Label> lblCmdDataSize;
    std::unique_ptr<TextEditor> txtCmdDataSize;
    std::unique_ptr<Label> label11;
    std::unique_ptr<Label> label2;
    std::unique_ptr<ComboBox> cbxAction;
    std::unique_ptr<Label> label9;
    std::unique_ptr<TextEditor> txtCmdName;
    std::unique_ptr<TextEditor> txtCmdEnd;
    std::unique_ptr<Label> label12;
    std::unique_ptr<ToggleButton> optCmdSeq;
    std::unique_ptr<ToggleButton> optCmdChn;
    std::unique_ptr<ToggleButton> optCmdTrk;
    std::unique_ptr<Label> label13;
    std::unique_ptr<TextButton> btnParamAdd;
    std::unique_ptr<TextButton> btnParamDel;
    std::unique_ptr<TextButton> btnParamUp;
    std::unique_ptr<TextButton> btnParamDn;
    std::unique_ptr<ToggleButton> optCmdOffset;
    std::unique_ptr<Label> label14;
    std::unique_ptr<Label> label15;
    std::unique_ptr<TextEditor> txtParamName;
    std::unique_ptr<Label> label16;
    std::unique_ptr<ComboBox> cbxMeaning;
    std::unique_ptr<Label> label17;
    std::unique_ptr<Label> label18;
    std::unique_ptr<TextEditor> txtParamAdd;
    std::unique_ptr<TextEditor> txtParamMult;
    std::unique_ptr<TextButton> btnCmdUp;
    std::unique_ptr<TextButton> btnCmdDn;
    std::unique_ptr<Label> label3;
    std::unique_ptr<Label> label4;
    std::unique_ptr<TextButton> btnSeqCmdAdd;
    std::unique_ptr<TextButton> btnSeqCmdDelete;
    std::unique_ptr<TextButton> btnSeqCmdUp;
    std::unique_ptr<TextButton> btnSeqCmdDn;
    std::unique_ptr<ComboBox> cbxSeqCmdType;
    std::unique_ptr<Label> label7;
    std::unique_ptr<TextEditor> txtSeqCmdValue;
    std::unique_ptr<Label> lblSeqInfo;
    std::unique_ptr<Label> lblSeqCmdAction;
    std::unique_ptr<Label> lblValueEquiv;
    std::unique_ptr<Label> lblSeqCmdAction2;
    std::unique_ptr<TextButton> btnReParse;
    std::unique_ptr<TextButton> btnSaveRaw;
    std::unique_ptr<TextButton> btnLoadRaw;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioseqPane)
};

//[EndFile] You can add extra defines here...
//[/EndFile]


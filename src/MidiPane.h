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
 * MidiPane.h
 * GUI component for the MIDI import/export screen
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
class MidiPane  : public Component,
                  public TextEditor::Listener,
                  public Button::Listener,
                  public ComboBox::Listener
{
public:
    //==============================================================================
    MidiPane (SEQ64& seq64_);
    ~MidiPane();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void textEditorTextChanged(TextEditor& editorThatWasChanged);
    void refreshMIDIControls();

    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    SEQ64& seq64;
    ValueTree midioptsnode;

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<GroupComponent> groupComponent8;
    std::unique_ptr<GroupComponent> groupComponent3;
    std::unique_ptr<GroupComponent> groupComponent7;
    std::unique_ptr<GroupComponent> groupComponent;
    std::unique_ptr<TextButton> btnMIDIExport;
    std::unique_ptr<TextButton> btnMIDIImport;
    std::unique_ptr<Label> label20;
    std::unique_ptr<TextEditor> txtMIDIBend;
    std::unique_ptr<Label> label21;
    std::unique_ptr<TextEditor> txtMIDIPPQN;
    std::unique_ptr<Label> label22;
    std::unique_ptr<Label> label23;
    std::unique_ptr<ComboBox> cbxMIDIChnVol;
    std::unique_ptr<Label> label24;
    std::unique_ptr<ComboBox> cbxMIDIMtrVol;
    std::unique_ptr<Label> label26;
    std::unique_ptr<ComboBox> cbxChnPriority;
    std::unique_ptr<ToggleButton> optSeqFormat;
    std::unique_ptr<ToggleButton> optSeqType;
    std::unique_ptr<ToggleButton> optChanBits;
    std::unique_ptr<ToggleButton> optLoopAll;
    std::unique_ptr<ToggleButton> optHeader;
    std::unique_ptr<ToggleButton> optChanReset;
    std::unique_ptr<GroupComponent> grpPtr;
    std::unique_ptr<ToggleButton> optPtrAbsolute;
    std::unique_ptr<ToggleButton> optPtrShortest;
    std::unique_ptr<ToggleButton> optPtrRelative;
    std::unique_ptr<TextEditor> txtSeqFormat;
    std::unique_ptr<TextEditor> txtSeqType;
    std::unique_ptr<ToggleButton> optCalls;
    std::unique_ptr<Label> lblStack;
    std::unique_ptr<TextEditor> txtStack;
    std::unique_ptr<ToggleButton> optLoops;
    std::unique_ptr<Label> label2;
    std::unique_ptr<TextEditor> txtMergeVels;
    std::unique_ptr<TextEditor> txtMergeGates;
    std::unique_ptr<TextEditor> txtMergeCCs;
    std::unique_ptr<Label> label3;
    std::unique_ptr<Label> label4;
    std::unique_ptr<TextEditor> txtQVolT;
    std::unique_ptr<TextEditor> txtQOtherT;
    std::unique_ptr<TextEditor> txtQVolA;
    std::unique_ptr<TextEditor> txtQOtherA;
    std::unique_ptr<Label> label5;
    std::unique_ptr<Label> label6;
    std::unique_ptr<Label> label7;
    std::unique_ptr<Label> label8;
    std::unique_ptr<Label> label9;
    std::unique_ptr<Label> label10;
    std::unique_ptr<TextEditor> txtQPitchT;
    std::unique_ptr<TextEditor> txtQPitchA;
    std::unique_ptr<Label> label11;
    std::unique_ptr<TextEditor> txtQPanT;
    std::unique_ptr<TextEditor> txtQPanA;
    std::unique_ptr<Label> label12;
    std::unique_ptr<ToggleButton> optMstrVol;
    std::unique_ptr<TextEditor> txtMstrVol;
    std::unique_ptr<GroupComponent> groupComponent2;
    std::unique_ptr<ToggleButton> optExportOrig;
    std::unique_ptr<ToggleButton> optExportGM;
    std::unique_ptr<Label> label;
    std::unique_ptr<ToggleButton> optInstDrumCh10;
    std::unique_ptr<ToggleButton> optInstDrumMulti;
    Path internalPath1;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiPane)
};

//[EndFile] You can add extra defines here...
//[/EndFile]


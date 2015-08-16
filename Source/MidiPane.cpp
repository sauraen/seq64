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

//[Headers] You can add your own extra header files here...
/*
 * ============================================================================
 *
 * MidiPane.cpp
 * GUI component for the MIDI import/export screen
 *
 * From seq64 - Sequenced music editor for first-party N64 games
 * Copyright (C) 2014-2015 Sauraen
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

#include "MainComponent.h"
#include "SeqFile.h"
//[/Headers]

#include "MidiPane.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MidiPane::MidiPane (SEQ64& seq64_)
    : seq64(seq64_)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (groupComponent8 = new GroupComponent ("new group",
                                                             TRANS("Import Settings")));

    addAndMakeVisible (groupComponent3 = new GroupComponent ("new group",
                                                             TRANS("Optimization")));

    addAndMakeVisible (groupComponent7 = new GroupComponent ("new group",
                                                             TRANS("Export Settings")));

    addAndMakeVisible (groupComponent = new GroupComponent ("new group",
                                                            TRANS("Global")));

    addAndMakeVisible (btnMIDIExport = new TextButton ("new button"));
    btnMIDIExport->setButtonText (TRANS("Export MIDI"));
    btnMIDIExport->setConnectedEdges (Button::ConnectedOnRight);
    btnMIDIExport->addListener (this);

    addAndMakeVisible (btnMIDIImport = new TextButton ("new button"));
    btnMIDIImport->setButtonText (TRANS("Import MIDI"));
    btnMIDIImport->setConnectedEdges (Button::ConnectedOnLeft);
    btnMIDIImport->addListener (this);

    addAndMakeVisible (label20 = new Label ("new label",
                                            TRANS("Bend range:")));
    label20->setFont (Font (15.00f, Font::plain));
    label20->setJustificationType (Justification::centredLeft);
    label20->setEditable (false, false, false);
    label20->setColour (TextEditor::textColourId, Colours::black);
    label20->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (txtMIDIBend = new TextEditor ("new text editor"));
    txtMIDIBend->setMultiLine (false);
    txtMIDIBend->setReturnKeyStartsNewLine (false);
    txtMIDIBend->setReadOnly (false);
    txtMIDIBend->setScrollbarsShown (true);
    txtMIDIBend->setCaretVisible (true);
    txtMIDIBend->setPopupMenuEnabled (true);
    txtMIDIBend->setText (TRANS("6"));

    addAndMakeVisible (label21 = new Label ("new label",
                                            TRANS("PPQN multiplier:")));
    label21->setFont (Font (15.00f, Font::plain));
    label21->setJustificationType (Justification::centredLeft);
    label21->setEditable (false, false, false);
    label21->setColour (TextEditor::textColourId, Colours::black);
    label21->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (txtMIDIPPQN = new TextEditor ("new text editor"));
    txtMIDIPPQN->setMultiLine (false);
    txtMIDIPPQN->setReturnKeyStartsNewLine (false);
    txtMIDIPPQN->setReadOnly (false);
    txtMIDIPPQN->setScrollbarsShown (true);
    txtMIDIPPQN->setCaretVisible (true);
    txtMIDIPPQN->setPopupMenuEnabled (true);
    txtMIDIPPQN->setText (TRANS("2"));

    addAndMakeVisible (label22 = new Label ("new label",
                                            TRANS("x48")));
    label22->setFont (Font (15.00f, Font::plain));
    label22->setJustificationType (Justification::centredLeft);
    label22->setEditable (false, false, false);
    label22->setColour (TextEditor::textColourId, Colours::black);
    label22->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label23 = new Label ("new label",
                                            TRANS("Chn volume to:")));
    label23->setFont (Font (15.00f, Font::plain));
    label23->setJustificationType (Justification::centredLeft);
    label23->setEditable (false, false, false);
    label23->setColour (TextEditor::textColourId, Colours::black);
    label23->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (cbxMIDIChnVol = new ComboBox ("new combo box"));
    cbxMIDIChnVol->setEditableText (false);
    cbxMIDIChnVol->setJustificationType (Justification::centredLeft);
    cbxMIDIChnVol->setTextWhenNothingSelected (TRANS("ERROR"));
    cbxMIDIChnVol->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    cbxMIDIChnVol->addItem (TRANS("CC7 (Volume)"), 1);
    cbxMIDIChnVol->addItem (TRANS("CC11 (Expr)"), 2);
    cbxMIDIChnVol->addListener (this);

    addAndMakeVisible (label24 = new Label ("new label",
                                            TRANS("Master volume to:")));
    label24->setFont (Font (15.00f, Font::plain));
    label24->setJustificationType (Justification::centredLeft);
    label24->setEditable (false, false, false);
    label24->setColour (TextEditor::textColourId, Colours::black);
    label24->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (cbxMIDIMtrVol = new ComboBox ("new combo box"));
    cbxMIDIMtrVol->setEditableText (false);
    cbxMIDIMtrVol->setJustificationType (Justification::centredLeft);
    cbxMIDIMtrVol->setTextWhenNothingSelected (TRANS("ERROR"));
    cbxMIDIMtrVol->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    cbxMIDIMtrVol->addItem (TRANS("CC7 (Volume)"), 1);
    cbxMIDIMtrVol->addItem (TRANS("CC11 (Expr)"), 2);
    cbxMIDIMtrVol->addItem (TRANS("CC16 (GPC1)"), 3);
    cbxMIDIMtrVol->addItem (TRANS("CC24 (None)"), 4);
    cbxMIDIMtrVol->addItem (TRANS("SysEx MstrVol"), 5);
    cbxMIDIMtrVol->addListener (this);

    addAndMakeVisible (label26 = new Label ("new label",
                                            TRANS("Chn priority to:")));
    label26->setFont (Font (15.00f, Font::plain));
    label26->setJustificationType (Justification::centredLeft);
    label26->setEditable (false, false, false);
    label26->setColour (TextEditor::textColourId, Colours::black);
    label26->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (cbxChnPriority = new ComboBox ("new combo box"));
    cbxChnPriority->setEditableText (false);
    cbxChnPriority->setJustificationType (Justification::centredLeft);
    cbxChnPriority->setTextWhenNothingSelected (TRANS("ERROR"));
    cbxChnPriority->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    cbxChnPriority->addItem (TRANS("CC17 (GPC2)"), 1);
    cbxChnPriority->addItem (TRANS("CC25 (None)"), 2);
    cbxChnPriority->addItem (TRANS("CC79 (SC10)"), 3);
    cbxChnPriority->addListener (this);

    addAndMakeVisible (optSeqFormat = new ToggleButton ("new toggle button"));
    optSeqFormat->setButtonText (TRANS("Create Seq Format cmd:"));
    optSeqFormat->addListener (this);
    optSeqFormat->setToggleState (true, dontSendNotification);

    addAndMakeVisible (optSeqType = new ToggleButton ("new toggle button"));
    optSeqType->setButtonText (TRANS("Create Seq Type cmd:"));
    optSeqType->addListener (this);
    optSeqType->setToggleState (true, dontSendNotification);

    addAndMakeVisible (optChanBits = new ToggleButton ("new toggle button"));
    optChanBits->setButtonText (TRANS("Create Channel Enable/Disable Bitfield Cmds"));
    optChanBits->addListener (this);
    optChanBits->setToggleState (true, dontSendNotification);

    addAndMakeVisible (optLoopAll = new ToggleButton ("new toggle button"));
    optLoopAll->setButtonText (TRANS("Create command to loop whole sequence"));
    optLoopAll->addListener (this);
    optLoopAll->setToggleState (true, dontSendNotification);

    addAndMakeVisible (optHeader = new ToggleButton ("new toggle button"));
    optHeader->setButtonText (TRANS("Create jump-to-sections header (if sections defined)"));
    optHeader->addListener (this);
    optHeader->setToggleState (true, dontSendNotification);

    addAndMakeVisible (optChanReset = new ToggleButton ("new toggle button"));
    optChanReset->setButtonText (TRANS("Initially reset channels"));
    optChanReset->addListener (this);
    optChanReset->setToggleState (true, dontSendNotification);

    addAndMakeVisible (groupComponent2 = new GroupComponent ("new group",
                                                             TRANS("Pointer Type")));

    addAndMakeVisible (optPtrAbsolute = new ToggleButton ("new toggle button"));
    optPtrAbsolute->setButtonText (TRANS("Absolute"));
    optPtrAbsolute->setRadioGroupId (1);
    optPtrAbsolute->addListener (this);

    addAndMakeVisible (optPtrShortest = new ToggleButton ("new toggle button"));
    optPtrShortest->setButtonText (TRANS("Shortest"));
    optPtrShortest->setRadioGroupId (1);
    optPtrShortest->addListener (this);
    optPtrShortest->setToggleState (true, dontSendNotification);

    addAndMakeVisible (optPtrRelative = new ToggleButton ("new toggle button"));
    optPtrRelative->setButtonText (TRANS("Force Relative Only"));
    optPtrRelative->setRadioGroupId (1);
    optPtrRelative->addListener (this);

    addAndMakeVisible (txtSeqFormat = new TextEditor ("new text editor"));
    txtSeqFormat->setMultiLine (false);
    txtSeqFormat->setReturnKeyStartsNewLine (false);
    txtSeqFormat->setReadOnly (false);
    txtSeqFormat->setScrollbarsShown (true);
    txtSeqFormat->setCaretVisible (true);
    txtSeqFormat->setPopupMenuEnabled (true);
    txtSeqFormat->setText (TRANS("20"));

    addAndMakeVisible (txtSeqType = new TextEditor ("new text editor"));
    txtSeqType->setMultiLine (false);
    txtSeqType->setReturnKeyStartsNewLine (false);
    txtSeqType->setReadOnly (false);
    txtSeqType->setScrollbarsShown (true);
    txtSeqType->setCaretVisible (true);
    txtSeqType->setPopupMenuEnabled (true);
    txtSeqType->setText (TRANS("32"));

    addAndMakeVisible (optCalls = new ToggleButton ("new toggle button"));
    optCalls->setButtonText (TRANS("Use Calls"));
    optCalls->addListener (this);
    optCalls->setToggleState (true, dontSendNotification);

    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("Stack height:")));
    label->setFont (Font (15.00f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (txtStack = new TextEditor ("new text editor"));
    txtStack->setMultiLine (false);
    txtStack->setReturnKeyStartsNewLine (false);
    txtStack->setReadOnly (false);
    txtStack->setScrollbarsShown (true);
    txtStack->setCaretVisible (true);
    txtStack->setPopupMenuEnabled (true);
    txtStack->setText (TRANS("4"));

    addAndMakeVisible (optLoops = new ToggleButton ("new toggle button"));
    optLoops->setButtonText (TRANS("Use Loops"));
    optLoops->addListener (this);
    optLoops->setToggleState (true, dontSendNotification);

    addAndMakeVisible (label2 = new Label ("new label",
                                           TRANS("Merge Even If Off By:")));
    label2->setFont (Font (15.00f, Font::plain));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (txtMergeVels = new TextEditor ("new text editor"));
    txtMergeVels->setMultiLine (false);
    txtMergeVels->setReturnKeyStartsNewLine (false);
    txtMergeVels->setReadOnly (false);
    txtMergeVels->setScrollbarsShown (true);
    txtMergeVels->setCaretVisible (true);
    txtMergeVels->setPopupMenuEnabled (true);
    txtMergeVels->setText (TRANS("5"));

    addAndMakeVisible (txtMergeGates = new TextEditor ("new text editor"));
    txtMergeGates->setMultiLine (false);
    txtMergeGates->setReturnKeyStartsNewLine (false);
    txtMergeGates->setReadOnly (false);
    txtMergeGates->setScrollbarsShown (true);
    txtMergeGates->setCaretVisible (true);
    txtMergeGates->setPopupMenuEnabled (true);
    txtMergeGates->setText (TRANS("3"));

    addAndMakeVisible (txtMergeCCs = new TextEditor ("new text editor"));
    txtMergeCCs->setMultiLine (false);
    txtMergeCCs->setReturnKeyStartsNewLine (false);
    txtMergeCCs->setReadOnly (false);
    txtMergeCCs->setScrollbarsShown (true);
    txtMergeCCs->setCaretVisible (true);
    txtMergeCCs->setPopupMenuEnabled (true);
    txtMergeCCs->setText (TRANS("3"));

    addAndMakeVisible (label3 = new Label ("new label",
                                           TRANS("CC Bandwidth Reduction:")));
    label3->setFont (Font (15.00f, Font::plain));
    label3->setJustificationType (Justification::centredLeft);
    label3->setEditable (false, false, false);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label4 = new Label ("new label",
                                           TRANS("Quantize in: time    ampl")));
    label4->setFont (Font (15.00f, Font::plain));
    label4->setJustificationType (Justification::centredLeft);
    label4->setEditable (false, false, false);
    label4->setColour (TextEditor::textColourId, Colours::black);
    label4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (txtQVolT = new TextEditor ("new text editor"));
    txtQVolT->setMultiLine (false);
    txtQVolT->setReturnKeyStartsNewLine (false);
    txtQVolT->setReadOnly (false);
    txtQVolT->setScrollbarsShown (true);
    txtQVolT->setCaretVisible (true);
    txtQVolT->setPopupMenuEnabled (true);
    txtQVolT->setText (TRANS("3"));

    addAndMakeVisible (txtQOtherT = new TextEditor ("new text editor"));
    txtQOtherT->setMultiLine (false);
    txtQOtherT->setReturnKeyStartsNewLine (false);
    txtQOtherT->setReadOnly (false);
    txtQOtherT->setScrollbarsShown (true);
    txtQOtherT->setCaretVisible (true);
    txtQOtherT->setPopupMenuEnabled (true);
    txtQOtherT->setText (TRANS("1"));

    addAndMakeVisible (txtQVolA = new TextEditor ("new text editor"));
    txtQVolA->setMultiLine (false);
    txtQVolA->setReturnKeyStartsNewLine (false);
    txtQVolA->setReadOnly (false);
    txtQVolA->setScrollbarsShown (true);
    txtQVolA->setCaretVisible (true);
    txtQVolA->setPopupMenuEnabled (true);
    txtQVolA->setText (TRANS("2"));

    addAndMakeVisible (txtQOtherA = new TextEditor ("new text editor"));
    txtQOtherA->setMultiLine (false);
    txtQOtherA->setReturnKeyStartsNewLine (false);
    txtQOtherA->setReadOnly (false);
    txtQOtherA->setScrollbarsShown (true);
    txtQOtherA->setCaretVisible (true);
    txtQOtherA->setPopupMenuEnabled (true);
    txtQOtherA->setText (TRANS("1"));

    addAndMakeVisible (label5 = new Label ("new label",
                                           TRANS("From/To Audioseq tab:")));
    label5->setFont (Font (15.00f, Font::plain));
    label5->setJustificationType (Justification::centredLeft);
    label5->setEditable (false, false, false);
    label5->setColour (TextEditor::textColourId, Colours::black);
    label5->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label6 = new Label ("new label",
                                           TRANS("- Volume")));
    label6->setFont (Font (15.00f, Font::plain));
    label6->setJustificationType (Justification::centredLeft);
    label6->setEditable (false, false, false);
    label6->setColour (TextEditor::textColourId, Colours::black);
    label6->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label7 = new Label ("new label",
                                           TRANS("- Other")));
    label7->setFont (Font (15.00f, Font::plain));
    label7->setJustificationType (Justification::centredLeft);
    label7->setEditable (false, false, false);
    label7->setColour (TextEditor::textColourId, Colours::black);
    label7->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label8 = new Label ("new label",
                                           TRANS("- Velocities")));
    label8->setFont (Font (15.00f, Font::plain));
    label8->setJustificationType (Justification::centredLeft);
    label8->setEditable (false, false, false);
    label8->setColour (TextEditor::textColourId, Colours::black);
    label8->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label9 = new Label ("new label",
                                           TRANS("- Gate Times")));
    label9->setFont (Font (15.00f, Font::plain));
    label9->setJustificationType (Justification::centredLeft);
    label9->setEditable (false, false, false);
    label9->setColour (TextEditor::textColourId, Colours::black);
    label9->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label10 = new Label ("new label",
                                            TRANS("- CCs")));
    label10->setFont (Font (15.00f, Font::plain));
    label10->setJustificationType (Justification::centredLeft);
    label10->setEditable (false, false, false);
    label10->setColour (TextEditor::textColourId, Colours::black);
    label10->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (txtQPitchT = new TextEditor ("new text editor"));
    txtQPitchT->setMultiLine (false);
    txtQPitchT->setReturnKeyStartsNewLine (false);
    txtQPitchT->setReadOnly (false);
    txtQPitchT->setScrollbarsShown (true);
    txtQPitchT->setCaretVisible (true);
    txtQPitchT->setPopupMenuEnabled (true);
    txtQPitchT->setText (TRANS("1"));

    addAndMakeVisible (txtQPitchA = new TextEditor ("new text editor"));
    txtQPitchA->setMultiLine (false);
    txtQPitchA->setReturnKeyStartsNewLine (false);
    txtQPitchA->setReadOnly (false);
    txtQPitchA->setScrollbarsShown (true);
    txtQPitchA->setCaretVisible (true);
    txtQPitchA->setPopupMenuEnabled (true);
    txtQPitchA->setText (TRANS("1"));

    addAndMakeVisible (label11 = new Label ("new label",
                                            TRANS("- Pitch")));
    label11->setFont (Font (15.00f, Font::plain));
    label11->setJustificationType (Justification::centredLeft);
    label11->setEditable (false, false, false);
    label11->setColour (TextEditor::textColourId, Colours::black);
    label11->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (txtQPanT = new TextEditor ("new text editor"));
    txtQPanT->setMultiLine (false);
    txtQPanT->setReturnKeyStartsNewLine (false);
    txtQPanT->setReadOnly (false);
    txtQPanT->setScrollbarsShown (true);
    txtQPanT->setCaretVisible (true);
    txtQPanT->setPopupMenuEnabled (true);
    txtQPanT->setText (TRANS("3"));

    addAndMakeVisible (txtQPanA = new TextEditor ("new text editor"));
    txtQPanA->setMultiLine (false);
    txtQPanA->setReturnKeyStartsNewLine (false);
    txtQPanA->setReadOnly (false);
    txtQPanA->setScrollbarsShown (true);
    txtQPanA->setCaretVisible (true);
    txtQPanA->setPopupMenuEnabled (true);
    txtQPanA->setText (TRANS("2"));

    addAndMakeVisible (label12 = new Label ("new label",
                                            TRANS("- Pan/FX")));
    label12->setFont (Font (15.00f, Font::plain));
    label12->setJustificationType (Justification::centredLeft);
    label12->setEditable (false, false, false);
    label12->setColour (TextEditor::textColourId, Colours::black);
    label12->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]

    txtMIDIBend->addListener(this);
    txtMIDIPPQN->addListener(this);
    txtSeqFormat->addListener(this);
    txtSeqType->addListener(this);
    txtStack->addListener(this);
    txtMergeVels->addListener(this);
    txtMergeGates->addListener(this);
    txtMergeCCs->addListener(this);
    txtQVolT->addListener(this);
    txtQVolA->addListener(this);
    txtQPitchT->addListener(this);
    txtQPitchA->addListener(this);
    txtQPanT->addListener(this);
    txtQPanA->addListener(this);
    txtQOtherT->addListener(this);
    txtQOtherA->addListener(this);

    cbxMIDIChnVol->setSelectedItemIndex(0, dontSendNotification);
    cbxMIDIMtrVol->setSelectedItemIndex(3, dontSendNotification);
    cbxChnPriority->setSelectedItemIndex(1, dontSendNotification);

    //[/UserPreSize]

    setSize (1000, 632);


    //[Constructor] You can add your own custom stuff here..
    midioptsnode = seq64.romdesc.getOrCreateChildWithName("midiopts", nullptr);

    //[/Constructor]
}

MidiPane::~MidiPane()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    groupComponent8 = nullptr;
    groupComponent3 = nullptr;
    groupComponent7 = nullptr;
    groupComponent = nullptr;
    btnMIDIExport = nullptr;
    btnMIDIImport = nullptr;
    label20 = nullptr;
    txtMIDIBend = nullptr;
    label21 = nullptr;
    txtMIDIPPQN = nullptr;
    label22 = nullptr;
    label23 = nullptr;
    cbxMIDIChnVol = nullptr;
    label24 = nullptr;
    cbxMIDIMtrVol = nullptr;
    label26 = nullptr;
    cbxChnPriority = nullptr;
    optSeqFormat = nullptr;
    optSeqType = nullptr;
    optChanBits = nullptr;
    optLoopAll = nullptr;
    optHeader = nullptr;
    optChanReset = nullptr;
    groupComponent2 = nullptr;
    optPtrAbsolute = nullptr;
    optPtrShortest = nullptr;
    optPtrRelative = nullptr;
    txtSeqFormat = nullptr;
    txtSeqType = nullptr;
    optCalls = nullptr;
    label = nullptr;
    txtStack = nullptr;
    optLoops = nullptr;
    label2 = nullptr;
    txtMergeVels = nullptr;
    txtMergeGates = nullptr;
    txtMergeCCs = nullptr;
    label3 = nullptr;
    label4 = nullptr;
    txtQVolT = nullptr;
    txtQOtherT = nullptr;
    txtQVolA = nullptr;
    txtQOtherA = nullptr;
    label5 = nullptr;
    label6 = nullptr;
    label7 = nullptr;
    label8 = nullptr;
    label9 = nullptr;
    label10 = nullptr;
    txtQPitchT = nullptr;
    txtQPitchA = nullptr;
    label11 = nullptr;
    txtQPanT = nullptr;
    txtQPanA = nullptr;
    label12 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void MidiPane::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MidiPane::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    groupComponent8->setBounds (360, 8, 352, 408);
    groupComponent3->setBounds (368, 216, 336, 192);
    groupComponent7->setBounds (0, 160, 352, 48);
    groupComponent->setBounds (0, 56, 352, 96);
    btnMIDIExport->setBounds (0, 24, 176, 24);
    btnMIDIImport->setBounds (176, 24, 176, 24);
    label20->setBounds (8, 175, 88, 24);
    txtMIDIBend->setBounds (96, 175, 32, 24);
    label21->setBounds (136, 175, 120, 24);
    txtMIDIPPQN->setBounds (248, 175, 32, 24);
    label22->setBounds (280, 175, 32, 24);
    label23->setBounds (8, 71, 120, 24);
    cbxMIDIChnVol->setBounds (128, 71, 216, 24);
    label24->setBounds (8, 95, 120, 24);
    cbxMIDIMtrVol->setBounds (128, 95, 216, 24);
    label26->setBounds (8, 119, 120, 24);
    cbxChnPriority->setBounds (128, 119, 216, 24);
    optSeqFormat->setBounds (368, 24, 184, 24);
    optSeqType->setBounds (368, 48, 184, 24);
    optChanBits->setBounds (368, 72, 336, 24);
    optLoopAll->setBounds (368, 96, 336, 24);
    optHeader->setBounds (368, 120, 336, 24);
    optChanReset->setBounds (368, 144, 336, 24);
    groupComponent2->setBounds (368, 168, 336, 48);
    optPtrAbsolute->setBounds (464, 184, 88, 24);
    optPtrShortest->setBounds (376, 184, 80, 24);
    optPtrRelative->setBounds (552, 184, 144, 24);
    txtSeqFormat->setBounds (560, 24, 40, 24);
    txtSeqType->setBounds (560, 48, 40, 24);
    optCalls->setBounds (376, 256, 144, 24);
    label->setBounds (376, 232, 104, 24);
    txtStack->setBounds (480, 232, 40, 24);
    optLoops->setBounds (376, 280, 144, 24);
    label2->setBounds (376, 304, 144, 24);
    txtMergeVels->setBounds (480, 328, 40, 24);
    txtMergeGates->setBounds (480, 352, 40, 24);
    txtMergeCCs->setBounds (480, 376, 40, 24);
    label3->setBounds (528, 232, 168, 24);
    label4->setBounds (528, 256, 168, 24);
    txtQVolT->setBounds (608, 280, 40, 24);
    txtQOtherT->setBounds (608, 352, 40, 24);
    txtQVolA->setBounds (656, 280, 40, 24);
    txtQOtherA->setBounds (656, 352, 40, 24);
    label5->setBounds (0, 0, 344, 24);
    label6->setBounds (528, 280, 72, 24);
    label7->setBounds (528, 352, 72, 24);
    label8->setBounds (376, 328, 88, 24);
    label9->setBounds (376, 352, 88, 24);
    label10->setBounds (376, 376, 88, 24);
    txtQPitchT->setBounds (608, 304, 40, 24);
    txtQPitchA->setBounds (656, 304, 40, 24);
    label11->setBounds (528, 304, 72, 24);
    txtQPanT->setBounds (608, 328, 40, 24);
    txtQPanA->setBounds (656, 328, 40, 24);
    label12->setBounds (528, 328, 72, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void MidiPane::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == btnMIDIExport)
    {
        //[UserButtonCode_btnMIDIExport] -- add your button handler code here..
        if(&*seq64.seq == nullptr) return;
		File dest = SEQ64::readFolderProperty("midifolder");
        FileChooser box("Save As", dest, "*.mid");
        if(!box.browseForFileToSave(true)) return;
        dest = box.getResult();
        if(!dest.hasWriteAccess()){
            SEQ64::say("Cannot write to " + dest.getFullPathName() + "!");
            return;
        }
        if(dest.getFileExtension() == ""){
            dest = dest.withFileExtension(".mid");
        }
        if(dest.exists()){
            dest.deleteFile();
        }
		SEQ64::writeProperty("midifolder", dest.getParentDirectory().getFullPathName());
        FileOutputStream fos(dest);
        //Do it!
        ScopedPointer<MidiFile> midi;
        midi = seq64.seq->toMIDIFile();
        midi->writeTo(fos);
        SEQ64::say("Written!");
        //[/UserButtonCode_btnMIDIExport]
    }
    else if (buttonThatWasClicked == btnMIDIImport)
    {
        //[UserButtonCode_btnMIDIImport] -- add your button handler code here..
        if(seq64.seq != nullptr){
            if(!NativeMessageBox::showOkCancelBox(AlertWindow::WarningIcon,
                    "Overwrite?", "A sequence is already loaded, overwrite it?", nullptr, nullptr)) return;
        }
        File dest = File::getSpecialLocation(File::userHomeDirectory);
        FileChooser box("Select a MIDI to load...", dest, "*.mid;*.midi;*.rmi");
        if(box.browseForFileToOpen()){
            dest = box.getResult();
            if(!dest.existsAsFile()){
                SEQ64::say("File " + dest.getFullPathName() + " does not exist!");
                return;
            }
            ScopedPointer<MidiFile> midi;
            midi = new MidiFile();
            FileInputStream fis(dest);
            midi->readFrom(fis);
            seq64.seq = new SeqFile(seq64.romdesc);
            seq64.seq->fromMidiFile(*midi);
            seq64.maincomponent->onSeqLoaded();
        }
        //[/UserButtonCode_btnMIDIImport]
    }
    else if (buttonThatWasClicked == optSeqFormat)
    {
        //[UserButtonCode_optSeqFormat] -- add your button handler code here..
        midioptsnode.setProperty("writeseqformat", optSeqFormat->getToggleState(), nullptr);
        //[/UserButtonCode_optSeqFormat]
    }
    else if (buttonThatWasClicked == optSeqType)
    {
        //[UserButtonCode_optSeqType] -- add your button handler code here..
        midioptsnode.setProperty("writeseqtype", optSeqType->getToggleState(), nullptr);
        //[/UserButtonCode_optSeqType]
    }
    else if (buttonThatWasClicked == optChanBits)
    {
        //[UserButtonCode_optChanBits] -- add your button handler code here..
        midioptsnode.setProperty("writechanbits", optChanBits->getToggleState(), nullptr);
        //[/UserButtonCode_optChanBits]
    }
    else if (buttonThatWasClicked == optLoopAll)
    {
        //[UserButtonCode_optLoopAll] -- add your button handler code here..
        midioptsnode.setProperty("writeloopall", optLoopAll->getToggleState(), nullptr);
        //[/UserButtonCode_optLoopAll]
    }
    else if (buttonThatWasClicked == optHeader)
    {
        //[UserButtonCode_optHeader] -- add your button handler code here..
        midioptsnode.setProperty("writeheader", optHeader->getToggleState(), nullptr);
        //[/UserButtonCode_optHeader]
    }
    else if (buttonThatWasClicked == optChanReset)
    {
        //[UserButtonCode_optChanReset] -- add your button handler code here..
        midioptsnode.setProperty("writechanreset", optChanReset->getToggleState(), nullptr);
        //[/UserButtonCode_optChanReset]
    }
    else if (buttonThatWasClicked == optPtrAbsolute)
    {
        //[UserButtonCode_optPtrAbsolute] -- add your button handler code here..
        midioptsnode.setProperty("ptrtype", "absolute", nullptr);
        //[/UserButtonCode_optPtrAbsolute]
    }
    else if (buttonThatWasClicked == optPtrShortest)
    {
        //[UserButtonCode_optPtrShortest] -- add your button handler code here..
        midioptsnode.setProperty("ptrtype", "shortest", nullptr);
        //[/UserButtonCode_optPtrShortest]
    }
    else if (buttonThatWasClicked == optPtrRelative)
    {
        //[UserButtonCode_optPtrRelative] -- add your button handler code here..
        midioptsnode.setProperty("ptrtype", "relative", nullptr);
        //[/UserButtonCode_optPtrRelative]
    }
    else if (buttonThatWasClicked == optCalls)
    {
        //[UserButtonCode_optCalls] -- add your button handler code here..
        midioptsnode.setProperty("usecalls", optCalls->getToggleState(), nullptr);
        //[/UserButtonCode_optCalls]
    }
    else if (buttonThatWasClicked == optLoops)
    {
        //[UserButtonCode_optLoops] -- add your button handler code here..
        midioptsnode.setProperty("useloops", optLoops->getToggleState(), nullptr);
        //[/UserButtonCode_optLoops]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void MidiPane::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == cbxMIDIChnVol)
    {
        //[UserComboBoxCode_cbxMIDIChnVol] -- add your combo box handling code here..
        midioptsnode.setProperty("chnvol", cbxMIDIChnVol->getText(), nullptr);
        //[/UserComboBoxCode_cbxMIDIChnVol]
    }
    else if (comboBoxThatHasChanged == cbxMIDIMtrVol)
    {
        //[UserComboBoxCode_cbxMIDIMtrVol] -- add your combo box handling code here..
        midioptsnode.setProperty("mtrvol", cbxMIDIMtrVol->getText(), nullptr);
        //[/UserComboBoxCode_cbxMIDIMtrVol]
    }
    else if (comboBoxThatHasChanged == cbxChnPriority)
    {
        //[UserComboBoxCode_cbxChnPriority] -- add your combo box handling code here..
        midioptsnode.setProperty("chnpriority", cbxChnPriority->getText(), nullptr);
        //[/UserComboBoxCode_cbxChnPriority]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void MidiPane::textEditorTextChanged(TextEditor& editorThatWasChanged){
    int val;
    String text = editorThatWasChanged.getText();
    if(        &editorThatWasChanged == &*txtSeqFormat
            || &editorThatWasChanged == &*txtSeqType ){
        val = text.getHexValue32();
    }else{
        val = text.getIntValue();
    }
    bool turnRed = (val <= 0);

    if(&editorThatWasChanged == &*txtMIDIBend){
        midioptsnode.setProperty("bendrange", val, nullptr);
    }else if(&editorThatWasChanged == &*txtMIDIPPQN){
        if(val <= 0) val = 1;
        midioptsnode.setProperty("ppqnmultiplier", val, nullptr);
    }else if(&editorThatWasChanged == &*txtSeqFormat){
        midioptsnode.setProperty("formatbytedefault", val, nullptr);
    }else if(&editorThatWasChanged == &*txtSeqType){
        midioptsnode.setProperty("typebytedefault", val, nullptr);
    }else if(&editorThatWasChanged == &*txtStack){
        midioptsnode.setProperty("stacksize", val, nullptr);
    }else if(&editorThatWasChanged == &*txtMergeVels){
        midioptsnode.setProperty("delta_vel", val, nullptr);
    }else if(&editorThatWasChanged == &*txtMergeGates){
        midioptsnode.setProperty("delta_gate", val, nullptr);
    }else if(&editorThatWasChanged == &*txtMergeCCs){
        midioptsnode.setProperty("delta_cc", val, nullptr);
    }else if(&editorThatWasChanged == &*txtQVolT){
        midioptsnode.setProperty("q_vol_time", val, nullptr);
    }else if(&editorThatWasChanged == &*txtQVolA){
        midioptsnode.setProperty("q_vol_amp", val, nullptr);
    }else if(&editorThatWasChanged == &*txtQPitchT){
        midioptsnode.setProperty("q_pitch_time", val, nullptr);
    }else if(&editorThatWasChanged == &*txtQPitchA){
        midioptsnode.setProperty("q_pitch_amp", val, nullptr);
    }else if(&editorThatWasChanged == &*txtQPanT){
        midioptsnode.setProperty("q_pan_time", val, nullptr);
    }else if(&editorThatWasChanged == &*txtQPanA){
        midioptsnode.setProperty("q_pan_amp", val, nullptr);
    }else if(&editorThatWasChanged == &*txtQOtherT){
        midioptsnode.setProperty("q_other_time", val, nullptr);
    }else if(&editorThatWasChanged == &*txtQOtherA){
        midioptsnode.setProperty("q_other_amp", val, nullptr);
    }
    if(turnRed){
        editorThatWasChanged.setColour(TextEditor::backgroundColourId, Colours::red);
    }else{
        editorThatWasChanged.setColour(TextEditor::backgroundColourId, Colours::white);
    }


}


void MidiPane::refreshMIDIControls(){
    midioptsnode = seq64.romdesc.getOrCreateChildWithName("midiopts", nullptr);
    txtMIDIBend->setText(midioptsnode.getProperty("bendrange", 6).toString());
    txtMIDIPPQN->setText(midioptsnode.getProperty("ppqnmultiplier", 4).toString());
    cbxMIDIChnVol->setText(midioptsnode.getProperty("chnvol", "CC7 (Volume)").toString());
    cbxMIDIMtrVol->setText(midioptsnode.getProperty("mtrvol", "CC24 (None)").toString());
    cbxChnPriority->setText(midioptsnode.getProperty("chnpriority", "CC25 (None)").toString());
    txtSeqFormat->setText(ROM::hex((uint8)(int)midioptsnode.getProperty("formatbytedefault", 0x20)));
    txtSeqType->setText(ROM::hex((uint8)(int)midioptsnode.getProperty("typebytedefault", 0x32)));
    txtStack->setText(midioptsnode.getProperty("stacksize", 4).toString());
    txtMergeVels->setText(midioptsnode.getProperty("delta_vel", 5).toString());
    txtMergeGates->setText(midioptsnode.getProperty("delta_gate", 3).toString());
    txtMergeCCs->setText(midioptsnode.getProperty("delta_cc", 3).toString());
    txtQVolT->setText(midioptsnode.getProperty("q_vol_time", 3).toString());
    txtQVolA->setText(midioptsnode.getProperty("q_vol_amp", 2).toString());
    txtQPitchT->setText(midioptsnode.getProperty("q_pitch_time", 1).toString());
    txtQPitchA->setText(midioptsnode.getProperty("q_pitch_amp", 1).toString());
    txtQPanT->setText(midioptsnode.getProperty("q_pan_time", 3).toString());
    txtQPanA->setText(midioptsnode.getProperty("q_pan_amp", 2).toString());
    txtQOtherT->setText(midioptsnode.getProperty("q_other_time", 1).toString());
    txtQOtherA->setText(midioptsnode.getProperty("q_other_amp", 1).toString());
    optSeqFormat->setToggleState((bool)midioptsnode.getProperty("writeseqformat", true), dontSendNotification);
    optSeqType->setToggleState((bool)midioptsnode.getProperty("writeseqtype", true), dontSendNotification);
    optChanBits->setToggleState((bool)midioptsnode.getProperty("writechanbits", true), dontSendNotification);
    optLoopAll->setToggleState((bool)midioptsnode.getProperty("writeloopall", true), dontSendNotification);
    optHeader->setToggleState((bool)midioptsnode.getProperty("writeheader", true), dontSendNotification);
    optChanReset->setToggleState((bool)midioptsnode.getProperty("writechanreset", true), dontSendNotification);
    optCalls->setToggleState((bool)midioptsnode.getProperty("usecalls", true), dontSendNotification);
    optLoops->setToggleState((bool)midioptsnode.getProperty("useloops", true), dontSendNotification);
    String ptrtype = midioptsnode.getProperty("ptrtype", "shortest");
    if(ptrtype == "absolute"){
        optPtrAbsolute->setToggleState(true, dontSendNotification);
    }else if(ptrtype == "relative"){
        optPtrRelative->setToggleState(true, dontSendNotification);
    }else{
        optPtrShortest->setToggleState(true, dontSendNotification);
    }
}


//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MidiPane" componentName=""
                 parentClasses="public Component, public TextEditor::Listener"
                 constructorParams="SEQ64&amp; seq64_" variableInitialisers="seq64(seq64_)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="1000" initialHeight="632">
  <BACKGROUND backgroundColour="ffffffff"/>
  <GROUPCOMPONENT name="new group" id="d6fd042ed5665f41" memberName="groupComponent8"
                  virtualName="" explicitFocusOrder="0" pos="360 8 352 408" title="Import Settings"/>
  <GROUPCOMPONENT name="new group" id="86dc1328c123b476" memberName="groupComponent3"
                  virtualName="" explicitFocusOrder="0" pos="368 216 336 192" title="Optimization"/>
  <GROUPCOMPONENT name="new group" id="425cb4d36ac8f912" memberName="groupComponent7"
                  virtualName="" explicitFocusOrder="0" pos="0 160 352 48" title="Export Settings"/>
  <GROUPCOMPONENT name="new group" id="41c7820ff71b634e" memberName="groupComponent"
                  virtualName="" explicitFocusOrder="0" pos="0 56 352 96" title="Global"/>
  <TEXTBUTTON name="new button" id="3fc9249f7191079e" memberName="btnMIDIExport"
              virtualName="" explicitFocusOrder="0" pos="0 24 176 24" buttonText="Export MIDI"
              connectedEdges="2" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="deb9b771019f9555" memberName="btnMIDIImport"
              virtualName="" explicitFocusOrder="0" pos="176 24 176 24" buttonText="Import MIDI"
              connectedEdges="1" needsCallback="1" radioGroupId="0"/>
  <LABEL name="new label" id="7ee4df75e04ec993" memberName="label20" virtualName=""
         explicitFocusOrder="0" pos="8 175 88 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Bend range:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="f6f8b6c6346a1954" memberName="txtMIDIBend"
              virtualName="" explicitFocusOrder="0" pos="96 175 32 24" initialText="6"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="678cb1b34534af2f" memberName="label21" virtualName=""
         explicitFocusOrder="0" pos="136 175 120 24" edTextCol="ff000000"
         edBkgCol="0" labelText="PPQN multiplier:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="99b9654ebd18dc1e" memberName="txtMIDIPPQN"
              virtualName="" explicitFocusOrder="0" pos="248 175 32 24" initialText="2"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="a7e744044efc1585" memberName="label22" virtualName=""
         explicitFocusOrder="0" pos="280 175 32 24" edTextCol="ff000000"
         edBkgCol="0" labelText="x48" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="695e3a0f276fa4e0" memberName="label23" virtualName=""
         explicitFocusOrder="0" pos="8 71 120 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Chn volume to:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="new combo box" id="d119e693727236bb" memberName="cbxMIDIChnVol"
            virtualName="" explicitFocusOrder="0" pos="128 71 216 24" editable="0"
            layout="33" items="CC7 (Volume)&#10;CC11 (Expr)" textWhenNonSelected="ERROR"
            textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="1dea77f54e15ecb7" memberName="label24" virtualName=""
         explicitFocusOrder="0" pos="8 95 120 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Master volume to:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="new combo box" id="21e08ae5ec6adcb7" memberName="cbxMIDIMtrVol"
            virtualName="" explicitFocusOrder="0" pos="128 95 216 24" editable="0"
            layout="33" items="CC7 (Volume)&#10;CC11 (Expr)&#10;CC16 (GPC1)&#10;CC24 (None)&#10;SysEx MstrVol"
            textWhenNonSelected="ERROR" textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="494496a2e6f332ab" memberName="label26" virtualName=""
         explicitFocusOrder="0" pos="8 119 120 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Chn priority to:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="new combo box" id="7007be4d513e8e1c" memberName="cbxChnPriority"
            virtualName="" explicitFocusOrder="0" pos="128 119 216 24" editable="0"
            layout="33" items="CC17 (GPC2)&#10;CC25 (None)&#10;CC79 (SC10)"
            textWhenNonSelected="ERROR" textWhenNoItems="(no choices)"/>
  <TOGGLEBUTTON name="new toggle button" id="bea2f7d3365308fd" memberName="optSeqFormat"
                virtualName="" explicitFocusOrder="0" pos="368 24 184 24" buttonText="Create Seq Format cmd:"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="1"/>
  <TOGGLEBUTTON name="new toggle button" id="a16780c566945959" memberName="optSeqType"
                virtualName="" explicitFocusOrder="0" pos="368 48 184 24" buttonText="Create Seq Type cmd:"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="1"/>
  <TOGGLEBUTTON name="new toggle button" id="d8406232a9779715" memberName="optChanBits"
                virtualName="" explicitFocusOrder="0" pos="368 72 336 24" buttonText="Create Channel Enable/Disable Bitfield Cmds"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="1"/>
  <TOGGLEBUTTON name="new toggle button" id="89f530c063ebc41f" memberName="optLoopAll"
                virtualName="" explicitFocusOrder="0" pos="368 96 336 24" buttonText="Create command to loop whole sequence"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="1"/>
  <TOGGLEBUTTON name="new toggle button" id="8407bc3e8b8b62f9" memberName="optHeader"
                virtualName="" explicitFocusOrder="0" pos="368 120 336 24" buttonText="Create jump-to-sections header (if sections defined)"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="1"/>
  <TOGGLEBUTTON name="new toggle button" id="ebfe7a8ea711aadd" memberName="optChanReset"
                virtualName="" explicitFocusOrder="0" pos="368 144 336 24" buttonText="Initially reset channels"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="1"/>
  <GROUPCOMPONENT name="new group" id="3f6e908675196841" memberName="groupComponent2"
                  virtualName="" explicitFocusOrder="0" pos="368 168 336 48" title="Pointer Type"/>
  <TOGGLEBUTTON name="new toggle button" id="a704eec5bbb2c46" memberName="optPtrAbsolute"
                virtualName="" explicitFocusOrder="0" pos="464 184 88 24" buttonText="Absolute"
                connectedEdges="0" needsCallback="1" radioGroupId="1" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="1bb095294dc9c19d" memberName="optPtrShortest"
                virtualName="" explicitFocusOrder="0" pos="376 184 80 24" buttonText="Shortest"
                connectedEdges="0" needsCallback="1" radioGroupId="1" state="1"/>
  <TOGGLEBUTTON name="new toggle button" id="1f703315d74170ea" memberName="optPtrRelative"
                virtualName="" explicitFocusOrder="0" pos="552 184 144 24" buttonText="Force Relative Only"
                connectedEdges="0" needsCallback="1" radioGroupId="1" state="0"/>
  <TEXTEDITOR name="new text editor" id="65923cd1adbfea89" memberName="txtSeqFormat"
              virtualName="" explicitFocusOrder="0" pos="560 24 40 24" initialText="20"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="new text editor" id="e2cfda96ec6ac80f" memberName="txtSeqType"
              virtualName="" explicitFocusOrder="0" pos="560 48 40 24" initialText="32"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TOGGLEBUTTON name="new toggle button" id="57be9c908829216a" memberName="optCalls"
                virtualName="" explicitFocusOrder="0" pos="376 256 144 24" buttonText="Use Calls"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="1"/>
  <LABEL name="new label" id="f41f0b19ef7d8015" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="376 232 104 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Stack height:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="2ab348c3ffced623" memberName="txtStack"
              virtualName="" explicitFocusOrder="0" pos="480 232 40 24" initialText="4"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TOGGLEBUTTON name="new toggle button" id="82b4adcc200b6608" memberName="optLoops"
                virtualName="" explicitFocusOrder="0" pos="376 280 144 24" buttonText="Use Loops"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="1"/>
  <LABEL name="new label" id="a0db16db13f10260" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="376 304 144 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Merge Even If Off By:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="901a724d96e98e44" memberName="txtMergeVels"
              virtualName="" explicitFocusOrder="0" pos="480 328 40 24" initialText="5"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="new text editor" id="e9c365157ee89f96" memberName="txtMergeGates"
              virtualName="" explicitFocusOrder="0" pos="480 352 40 24" initialText="3"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="new text editor" id="d3682229a2d89e65" memberName="txtMergeCCs"
              virtualName="" explicitFocusOrder="0" pos="480 376 40 24" initialText="3"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="99591c70db040217" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="528 232 168 24" edTextCol="ff000000"
         edBkgCol="0" labelText="CC Bandwidth Reduction:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="879d80b64a195ec7" memberName="label4" virtualName=""
         explicitFocusOrder="0" pos="528 256 168 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Quantize in: time    ampl" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="1c0cd46f039c823f" memberName="txtQVolT"
              virtualName="" explicitFocusOrder="0" pos="608 280 40 24" initialText="3"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="new text editor" id="edc286004a356a7" memberName="txtQOtherT"
              virtualName="" explicitFocusOrder="0" pos="608 352 40 24" initialText="1"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="new text editor" id="ca751fb5ec03f77b" memberName="txtQVolA"
              virtualName="" explicitFocusOrder="0" pos="656 280 40 24" initialText="2"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="new text editor" id="5e72039eac67ea45" memberName="txtQOtherA"
              virtualName="" explicitFocusOrder="0" pos="656 352 40 24" initialText="1"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="f28e7ff1efaecfdf" memberName="label5" virtualName=""
         explicitFocusOrder="0" pos="0 0 344 24" edTextCol="ff000000"
         edBkgCol="0" labelText="From/To Audioseq tab:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="38e2b8a24e2c4cf0" memberName="label6" virtualName=""
         explicitFocusOrder="0" pos="528 280 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="- Volume" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="a46a610ebb27cfc8" memberName="label7" virtualName=""
         explicitFocusOrder="0" pos="528 352 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="- Other" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="6743b881f0a469a8" memberName="label8" virtualName=""
         explicitFocusOrder="0" pos="376 328 88 24" edTextCol="ff000000"
         edBkgCol="0" labelText="- Velocities" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="dc9a9cb1e539d990" memberName="label9" virtualName=""
         explicitFocusOrder="0" pos="376 352 88 24" edTextCol="ff000000"
         edBkgCol="0" labelText="- Gate Times" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="ce10451244d07d82" memberName="label10" virtualName=""
         explicitFocusOrder="0" pos="376 376 88 24" edTextCol="ff000000"
         edBkgCol="0" labelText="- CCs" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="e3e7d963da09a087" memberName="txtQPitchT"
              virtualName="" explicitFocusOrder="0" pos="608 304 40 24" initialText="1"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="new text editor" id="ef6d5b29efe67c05" memberName="txtQPitchA"
              virtualName="" explicitFocusOrder="0" pos="656 304 40 24" initialText="1"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="c1807deff329fd4b" memberName="label11" virtualName=""
         explicitFocusOrder="0" pos="528 304 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="- Pitch" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="4bc5598877271b87" memberName="txtQPanT"
              virtualName="" explicitFocusOrder="0" pos="608 328 40 24" initialText="3"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="new text editor" id="591164d5daf46f21" memberName="txtQPanA"
              virtualName="" explicitFocusOrder="0" pos="656 328 40 24" initialText="2"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="7b14856ae0061bca" memberName="label12" virtualName=""
         explicitFocusOrder="0" pos="528 328 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="- Pan/FX" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

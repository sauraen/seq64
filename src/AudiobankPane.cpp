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

//[Headers] You can add your own extra header files here...
/*
 * ============================================================================
 *
 * AudiobankPane.cpp
 * GUI component for Audiobank editor screen
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

#include "BankFile.h"
//[/Headers]

#include "AudiobankPane.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
AudiobankPane::AudiobankPane (SEQ64& seq64_)
    : seq64(seq64_)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    groupComponent2.reset (new GroupComponent ("new group",
                                               TRANS("Audiobank Library")));
    addAndMakeVisible (groupComponent2.get());

    groupComponent2->setBounds (0, 344, 760, 344);

    groupComponent4.reset (new GroupComponent ("new group",
                                               TRANS("Add to Loaded Bank")));
    addAndMakeVisible (groupComponent4.get());

    groupComponent4->setBounds (504, 440, 248, 96);

    groupComponent3.reset (new GroupComponent ("new group",
                                               TRANS("Loaded Bank")));
    addAndMakeVisible (groupComponent3.get());

    groupComponent3->setBounds (448, 0, 576, 344);

    groupComponent.reset (new GroupComponent ("new group",
                                              TRANS("Audiobank File Data Structures")));
    addAndMakeVisible (groupComponent.get());

    groupComponent->setBounds (0, 0, 448, 344);

    cbxEditStruct.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (cbxEditStruct.get());
    cbxEditStruct->setEditableText (false);
    cbxEditStruct->setJustificationType (Justification::centredLeft);
    cbxEditStruct->setTextWhenNothingSelected (String());
    cbxEditStruct->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    cbxEditStruct->addItem (TRANS("ABIndexEntry"), 1);
    cbxEditStruct->addItem (TRANS("ABHeader"), 2);
    cbxEditStruct->addItem (TRANS("ABBank"), 3);
    cbxEditStruct->addItem (TRANS("ABDrumList"), 4);
    cbxEditStruct->addItem (TRANS("ABSFXList"), 5);
    cbxEditStruct->addItem (TRANS("ABInstrument"), 6);
    cbxEditStruct->addItem (TRANS("ABDrum"), 7);
    cbxEditStruct->addItem (TRANS("ABEnvelope"), 8);
    cbxEditStruct->addItem (TRANS("ABSound"), 9);
    cbxEditStruct->addItem (TRANS("ABSample"), 10);
    cbxEditStruct->addItem (TRANS("ALADPCMBook"), 11);
    cbxEditStruct->addItem (TRANS("ALADPCMPredictor"), 12);
    cbxEditStruct->addItem (TRANS("ALADPCMLoop"), 13);
    cbxEditStruct->addItem (TRANS("ALADPCMTail"), 14);
    cbxEditStruct->addListener (this);

    cbxEditStruct->setBounds (28, 160, 164, 24);

    label2.reset (new Label ("new label",
                             TRANS("Data Type:")));
    addAndMakeVisible (label2.get());
    label2->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label2->setBounds (200, 192, 80, 24);

    optPointer.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (optPointer.get());
    optPointer->setButtonText (TRANS("Ptr To:"));
    optPointer->addListener (this);

    optPointer->setBounds (8, 216, 72, 24);

    cbxDataType.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (cbxDataType.get());
    cbxDataType->setEditableText (false);
    cbxDataType->setJustificationType (Justification::centredLeft);
    cbxDataType->setTextWhenNothingSelected (String());
    cbxDataType->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    cbxDataType->addItem (TRANS("uint8"), 1);
    cbxDataType->addItem (TRANS("uint16"), 2);
    cbxDataType->addItem (TRANS("uint32"), 3);
    cbxDataType->addItem (TRANS("int8"), 4);
    cbxDataType->addItem (TRANS("int16"), 5);
    cbxDataType->addItem (TRANS("int32"), 6);
    cbxDataType->addItem (TRANS("float32"), 7);
    cbxDataType->addItem (TRANS("ABSound"), 8);
    cbxDataType->addItem (TRANS("ALADPCMPredictor"), 9);
    cbxDataType->addItem (TRANS("ALADPCMTail"), 10);
    cbxDataType->addListener (this);

    cbxDataType->setBounds (280, 192, 160, 24);

    cbxPtrTo.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (cbxPtrTo.get());
    cbxPtrTo->setEditableText (false);
    cbxPtrTo->setJustificationType (Justification::centredLeft);
    cbxPtrTo->setTextWhenNothingSelected (String());
    cbxPtrTo->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    cbxPtrTo->addItem (TRANS("ABHeader"), 1);
    cbxPtrTo->addItem (TRANS("ABDrumList"), 2);
    cbxPtrTo->addItem (TRANS("ABSFXList"), 3);
    cbxPtrTo->addItem (TRANS("ABInstrument"), 4);
    cbxPtrTo->addItem (TRANS("ABDrum"), 5);
    cbxPtrTo->addItem (TRANS("ABEnvelope"), 6);
    cbxPtrTo->addItem (TRANS("ABSample"), 7);
    cbxPtrTo->addItem (TRANS("ALADPCMBook"), 8);
    cbxPtrTo->addItem (TRANS("ALADPCMLoop"), 9);
    cbxPtrTo->addListener (this);

    cbxPtrTo->setBounds (24, 240, 168, 24);

    label3.reset (new Label ("new label",
                             TRANS("Name:")));
    addAndMakeVisible (label3.get());
    label3->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label3->setJustificationType (Justification::centredLeft);
    label3->setEditable (false, false, false);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label3->setBounds (8, 192, 56, 24);

    txtFieldName.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (txtFieldName.get());
    txtFieldName->setMultiLine (false);
    txtFieldName->setReturnKeyStartsNewLine (false);
    txtFieldName->setReadOnly (false);
    txtFieldName->setScrollbarsShown (true);
    txtFieldName->setCaretVisible (true);
    txtFieldName->setPopupMenuEnabled (true);
    txtFieldName->setText (String());

    txtFieldName->setBounds (64, 192, 128, 24);

    optArray.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (optArray.get());
    optArray->setButtonText (TRANS("Array:"));
    optArray->addListener (this);

    optArray->setBounds (200, 216, 80, 24);

    optArrayFixed.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (optArrayFixed.get());
    optArrayFixed->setButtonText (TRANS("Fixed:"));
    optArrayFixed->setRadioGroupId (1);
    optArrayFixed->addListener (this);

    optArrayFixed->setBounds (216, 240, 80, 24);

    optArrayVar.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (optArrayVar.get());
    optArrayVar->setButtonText (TRANS("Variable:"));
    optArrayVar->setRadioGroupId (1);
    optArrayVar->addListener (this);

    optArrayVar->setBounds (216, 264, 80, 24);

    txtArrayLen.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (txtArrayLen.get());
    txtArrayLen->setMultiLine (false);
    txtArrayLen->setReturnKeyStartsNewLine (false);
    txtArrayLen->setReadOnly (false);
    txtArrayLen->setScrollbarsShown (true);
    txtArrayLen->setCaretVisible (true);
    txtArrayLen->setPopupMenuEnabled (true);
    txtArrayLen->setText (String());

    txtArrayLen->setBounds (296, 240, 64, 24);

    cbxArrayLenVar.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (cbxArrayLenVar.get());
    cbxArrayLenVar->setEditableText (false);
    cbxArrayLenVar->setJustificationType (Justification::centredLeft);
    cbxArrayLenVar->setTextWhenNothingSelected (String());
    cbxArrayLenVar->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    cbxArrayLenVar->addItem (TRANS("NUM_BANK"), 1);
    cbxArrayLenVar->addItem (TRANS("NUM_INST"), 2);
    cbxArrayLenVar->addItem (TRANS("NUM_DRUM"), 3);
    cbxArrayLenVar->addItem (TRANS("NUM_SFX"), 4);
    cbxArrayLenVar->addItem (TRANS("NUM_PRED"), 5);
    cbxArrayLenVar->addItem (TRANS("HAS_TAIL"), 6);
    cbxArrayLenVar->addListener (this);

    cbxArrayLenVar->setBounds (296, 264, 144, 24);

    label4.reset (new Label ("new label",
                             TRANS("Meaning:")));
    addAndMakeVisible (label4.get());
    label4->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label4->setJustificationType (Justification::centredLeft);
    label4->setEditable (false, false, false);
    label4->setColour (TextEditor::textColourId, Colours::black);
    label4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label4->setBounds (200, 288, 80, 24);

    cbxMeaning.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (cbxMeaning.get());
    cbxMeaning->setEditableText (false);
    cbxMeaning->setJustificationType (Justification::centredLeft);
    cbxMeaning->setTextWhenNothingSelected (String());
    cbxMeaning->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    cbxMeaning->addListener (this);

    cbxMeaning->setBounds (200, 312, 240, 24);

    lblStructBegin.reset (new Label ("new label",
                                     TRANS("typedef struct {                        //Align all to:                    bytes")));
    addAndMakeVisible (lblStructBegin.get());
    lblStructBegin->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblStructBegin->setJustificationType (Justification::centredLeft);
    lblStructBegin->setEditable (false, false, false);
    lblStructBegin->setColour (TextEditor::textColourId, Colours::black);
    lblStructBegin->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblStructBegin->setBounds (8, 16, 432, 24);

    lblStructEnd.reset (new Label ("new label",
                                   TRANS("}")));
    addAndMakeVisible (lblStructEnd.get());
    lblStructEnd->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblStructEnd->setJustificationType (Justification::centredLeft);
    lblStructEnd->setEditable (false, false, false);
    lblStructEnd->setColour (TextEditor::textColourId, Colours::black);
    lblStructEnd->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblStructEnd->setBounds (8, 160, 20, 24);

    label5.reset (new Label ("new label",
                             TRANS("Default value:")));
    addAndMakeVisible (label5.get());
    label5->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label5->setJustificationType (Justification::centredLeft);
    label5->setEditable (false, false, false);
    label5->setColour (TextEditor::textColourId, Colours::black);
    label5->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label5->setBounds (8, 288, 104, 24);

    txtDefaultVal.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (txtDefaultVal.get());
    txtDefaultVal->setMultiLine (false);
    txtDefaultVal->setReturnKeyStartsNewLine (false);
    txtDefaultVal->setReadOnly (false);
    txtDefaultVal->setScrollbarsShown (true);
    txtDefaultVal->setCaretVisible (true);
    txtDefaultVal->setPopupMenuEnabled (true);
    txtDefaultVal->setText (String());

    txtDefaultVal->setBounds (32, 312, 160, 24);

    btnFieldAdd.reset (new TextButton ("new button"));
    addAndMakeVisible (btnFieldAdd.get());
    btnFieldAdd->setButtonText (TRANS("Add"));
    btnFieldAdd->setConnectedEdges (Button::ConnectedOnRight);
    btnFieldAdd->addListener (this);

    btnFieldAdd->setBounds (272, 160, 40, 24);

    btnFieldDel.reset (new TextButton ("new button"));
    addAndMakeVisible (btnFieldDel.get());
    btnFieldDel->setButtonText (TRANS("Del"));
    btnFieldDel->setConnectedEdges (Button::ConnectedOnLeft);
    btnFieldDel->addListener (this);

    btnFieldDel->setBounds (312, 160, 40, 24);

    btnFieldUp.reset (new TextButton ("new button"));
    addAndMakeVisible (btnFieldUp.get());
    btnFieldUp->setButtonText (TRANS("Up"));
    btnFieldUp->setConnectedEdges (Button::ConnectedOnRight);
    btnFieldUp->addListener (this);

    btnFieldUp->setBounds (360, 160, 40, 24);

    btnFieldDn.reset (new TextButton ("new button"));
    addAndMakeVisible (btnFieldDn.get());
    btnFieldDn->setButtonText (TRANS("Dn"));
    btnFieldDn->setConnectedEdges (Button::ConnectedOnLeft);
    btnFieldDn->addListener (this);

    btnFieldDn->setBounds (400, 160, 40, 24);

    label6.reset (new Label ("new label",
                             TRANS("(hex)")));
    addAndMakeVisible (label6.get());
    label6->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label6->setJustificationType (Justification::centredLeft);
    label6->setEditable (false, false, false);
    label6->setColour (TextEditor::textColourId, Colours::black);
    label6->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label6->setBounds (360, 240, 48, 24);

    label7.reset (new Label ("new label",
                             TRANS("0x")));
    addAndMakeVisible (label7.get());
    label7->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label7->setJustificationType (Justification::centredLeft);
    label7->setEditable (false, false, false);
    label7->setColour (TextEditor::textColourId, Colours::black);
    label7->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label7->setBounds (8, 312, 24, 24);

    lblStructSemicolon.reset (new Label ("new label",
                                         TRANS(";   //Fields:")));
    addAndMakeVisible (lblStructSemicolon.get());
    lblStructSemicolon->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblStructSemicolon->setJustificationType (Justification::centredLeft);
    lblStructSemicolon->setEditable (false, false, false);
    lblStructSemicolon->setColour (TextEditor::textColourId, Colours::black);
    lblStructSemicolon->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblStructSemicolon->setBounds (192, 160, 80, 24);

    label.reset (new Label ("new label",
                            TRANS("Banks:")));
    addAndMakeVisible (label.get());
    label->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label->setBounds (8, 360, 240, 24);

    cbxLibList.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (cbxLibList.get());
    cbxLibList->setEditableText (false);
    cbxLibList->setJustificationType (Justification::centredLeft);
    cbxLibList->setTextWhenNothingSelected (String());
    cbxLibList->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    cbxLibList->addItem (TRANS("Instruments"), 1);
    cbxLibList->addItem (TRANS("Drums"), 2);
    cbxLibList->addItem (TRANS("Sound Effects"), 3);
    cbxLibList->addListener (this);

    cbxLibList->setBounds (256, 360, 240, 24);

    btnLibAdd.reset (new TextButton ("new button"));
    addAndMakeVisible (btnLibAdd.get());
    btnLibAdd->setButtonText (TRANS("Import"));
    btnLibAdd->addListener (this);

    btnLibAdd->setBounds (512, 504, 232, 24);

    label8.reset (new Label ("new label",
                             TRANS("Name:")));
    addAndMakeVisible (label8.get());
    label8->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label8->setJustificationType (Justification::centredLeft);
    label8->setEditable (false, false, false);
    label8->setColour (TextEditor::textColourId, Colours::black);
    label8->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label8->setBounds (504, 360, 56, 24);

    txtLibItemName.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (txtLibItemName.get());
    txtLibItemName->setMultiLine (false);
    txtLibItemName->setReturnKeyStartsNewLine (false);
    txtLibItemName->setReadOnly (false);
    txtLibItemName->setScrollbarsShown (true);
    txtLibItemName->setCaretVisible (true);
    txtLibItemName->setPopupMenuEnabled (true);
    txtLibItemName->setText (String());

    txtLibItemName->setBounds (560, 360, 182, 24);

    chkLibMerge.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (chkLibMerge.get());
    chkLibMerge->setButtonText (TRANS("Merge"));
    chkLibMerge->addListener (this);
    chkLibMerge->setToggleState (true, dontSendNotification);

    chkLibMerge->setBounds (512, 456, 64, 24);

    btnBItemAdd.reset (new TextButton ("new button"));
    addAndMakeVisible (btnBItemAdd.get());
    btnBItemAdd->setButtonText (TRANS("Add"));
    btnBItemAdd->setConnectedEdges (Button::ConnectedOnBottom);
    btnBItemAdd->addListener (this);

    btnBItemAdd->setBounds (744, 48, 48, 24);

    btnBItemDupl.reset (new TextButton ("new button"));
    addAndMakeVisible (btnBItemDupl.get());
    btnBItemDupl->setButtonText (TRANS("Dupl"));
    btnBItemDupl->setConnectedEdges (Button::ConnectedOnTop | Button::ConnectedOnBottom);
    btnBItemDupl->addListener (this);

    btnBItemDupl->setBounds (744, 72, 48, 24);

    btnBItemDel.reset (new TextButton ("new button"));
    addAndMakeVisible (btnBItemDel.get());
    btnBItemDel->setButtonText (TRANS("Del"));
    btnBItemDel->setConnectedEdges (Button::ConnectedOnTop);
    btnBItemDel->addListener (this);

    btnBItemDel->setBounds (744, 96, 48, 24);

    btnBItemUp.reset (new TextButton ("new button"));
    addAndMakeVisible (btnBItemUp.get());
    btnBItemUp->setButtonText (TRANS("Up"));
    btnBItemUp->setConnectedEdges (Button::ConnectedOnBottom);
    btnBItemUp->addListener (this);

    btnBItemUp->setBounds (744, 136, 48, 24);

    btnBItemDn.reset (new TextButton ("new button"));
    addAndMakeVisible (btnBItemDn.get());
    btnBItemDn->setButtonText (TRANS("Dn"));
    btnBItemDn->setConnectedEdges (Button::ConnectedOnTop);
    btnBItemDn->addListener (this);

    btnBItemDn->setBounds (744, 160, 48, 24);

    label12.reset (new Label ("new label",
                              TRANS("Name:")));
    addAndMakeVisible (label12.get());
    label12->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label12->setJustificationType (Justification::centredLeft);
    label12->setEditable (false, false, false);
    label12->setColour (TextEditor::textColourId, Colours::black);
    label12->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label12->setBounds (800, 48, 56, 24);

    txtBItemName.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (txtBItemName.get());
    txtBItemName->setMultiLine (false);
    txtBItemName->setReturnKeyStartsNewLine (false);
    txtBItemName->setReadOnly (false);
    txtBItemName->setScrollbarsShown (true);
    txtBItemName->setCaretVisible (true);
    txtBItemName->setPopupMenuEnabled (true);
    txtBItemName->setText (String());

    txtBItemName->setBounds (856, 48, 160, 24);

    cbxAlign.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (cbxAlign.get());
    cbxAlign->setEditableText (false);
    cbxAlign->setJustificationType (Justification::centredLeft);
    cbxAlign->setTextWhenNothingSelected (String());
    cbxAlign->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    cbxAlign->addItem (TRANS("4"), 1);
    cbxAlign->addItem (TRANS("8"), 2);
    cbxAlign->addItem (TRANS("16"), 3);
    cbxAlign->addListener (this);

    cbxAlign->setBounds (272, 16, 56, 24);

    optMapProgram.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (optMapProgram.get());
    optMapProgram->setButtonText (TRANS("Program"));
    optMapProgram->setRadioGroupId (2);
    optMapProgram->addListener (this);

    optMapProgram->setBounds (504, 384, 80, 24);

    txtMapPNum.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (txtMapPNum.get());
    txtMapPNum->setMultiLine (false);
    txtMapPNum->setReturnKeyStartsNewLine (false);
    txtMapPNum->setReadOnly (false);
    txtMapPNum->setScrollbarsShown (true);
    txtMapPNum->setCaretVisible (true);
    txtMapPNum->setPopupMenuEnabled (true);
    txtMapPNum->setText (String());

    txtMapPNum->setBounds (584, 384, 40, 24);

    lblMapPNote.reset (new Label ("new label",
                                  TRANS("Note")));
    addAndMakeVisible (lblMapPNote.get());
    lblMapPNote->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblMapPNote->setJustificationType (Justification::centredLeft);
    lblMapPNote->setEditable (false, false, false);
    lblMapPNote->setColour (TextEditor::textColourId, Colours::black);
    lblMapPNote->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblMapPNote->setBounds (624, 384, 40, 24);

    txtMapPNote.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (txtMapPNote.get());
    txtMapPNote->setMultiLine (false);
    txtMapPNote->setReturnKeyStartsNewLine (false);
    txtMapPNote->setReadOnly (false);
    txtMapPNote->setScrollbarsShown (true);
    txtMapPNote->setCaretVisible (true);
    txtMapPNote->setPopupMenuEnabled (true);
    txtMapPNote->setText (String());

    txtMapPNote->setBounds (664, 384, 40, 24);

    optMapDrum.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (optMapDrum.get());
    optMapDrum->setButtonText (TRANS("Drum"));
    optMapDrum->setRadioGroupId (2);
    optMapDrum->addListener (this);

    optMapDrum->setBounds (504, 408, 64, 24);

    txtMapDS1.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (txtMapDS1.get());
    txtMapDS1->setMultiLine (false);
    txtMapDS1->setReturnKeyStartsNewLine (false);
    txtMapDS1->setReadOnly (false);
    txtMapDS1->setScrollbarsShown (true);
    txtMapDS1->setCaretVisible (true);
    txtMapDS1->setPopupMenuEnabled (true);
    txtMapDS1->setText (String());

    txtMapDS1->setBounds (584, 408, 40, 24);

    txtMapDS2.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (txtMapDS2.get());
    txtMapDS2->setMultiLine (false);
    txtMapDS2->setReturnKeyStartsNewLine (false);
    txtMapDS2->setReadOnly (false);
    txtMapDS2->setScrollbarsShown (true);
    txtMapDS2->setCaretVisible (true);
    txtMapDS2->setPopupMenuEnabled (true);
    txtMapDS2->setText (String());

    txtMapDS2->setBounds (624, 408, 40, 24);

    txtMapDS3.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (txtMapDS3.get());
    txtMapDS3->setMultiLine (false);
    txtMapDS3->setReturnKeyStartsNewLine (false);
    txtMapDS3->setReadOnly (false);
    txtMapDS3->setScrollbarsShown (true);
    txtMapDS3->setCaretVisible (true);
    txtMapDS3->setPopupMenuEnabled (true);
    txtMapDS3->setText (String());

    txtMapDS3->setBounds (664, 408, 40, 24);

    lblMapSplits.reset (new Label ("new label",
                                   TRANS("splits")));
    addAndMakeVisible (lblMapSplits.get());
    lblMapSplits->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblMapSplits->setJustificationType (Justification::centredLeft);
    lblMapSplits->setEditable (false, false, false);
    lblMapSplits->setColour (TextEditor::textColourId, Colours::black);
    lblMapSplits->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblMapSplits->setBounds (704, 408, 40, 24);

    btnBUp.reset (new TextButton ("new button"));
    addAndMakeVisible (btnBUp.get());
    btnBUp->setButtonText (TRANS("Up"));
    btnBUp->setConnectedEdges (Button::ConnectedOnRight);
    btnBUp->addListener (this);

    btnBUp->setBounds (456, 16, 40, 24);

    btnBOpen.reset (new TextButton ("new button"));
    addAndMakeVisible (btnBOpen.get());
    btnBOpen->setButtonText (TRANS("Open"));
    btnBOpen->addListener (this);

    btnBOpen->setBounds (744, 312, 48, 24);

    lblBankPath.reset (new Label ("new label",
                                  TRANS("/")));
    addAndMakeVisible (lblBankPath.get());
    lblBankPath->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblBankPath->setJustificationType (Justification::centredLeft);
    lblBankPath->setEditable (false, false, false);
    lblBankPath->setColour (TextEditor::textColourId, Colours::black);
    lblBankPath->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblBankPath->setBounds (496, 16, 520, 24);

    lblBItemType.reset (new Label ("new label",
                                   TRANS("Type:")));
    addAndMakeVisible (lblBItemType.get());
    lblBItemType->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblBItemType->setJustificationType (Justification::centredLeft);
    lblBItemType->setEditable (false, false, false);
    lblBItemType->setColour (TextEditor::textColourId, Colours::black);
    lblBItemType->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblBItemType->setBounds (800, 72, 216, 24);

    lblBItemValue.reset (new Label ("new label",
                                    TRANS("Value:")));
    addAndMakeVisible (lblBItemValue.get());
    lblBItemValue->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblBItemValue->setJustificationType (Justification::centredLeft);
    lblBItemValue->setEditable (false, false, false);
    lblBItemValue->setColour (TextEditor::textColourId, Colours::black);
    lblBItemValue->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblBItemValue->setBounds (800, 96, 56, 24);

    txtBItemValue.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (txtBItemValue.get());
    txtBItemValue->setMultiLine (false);
    txtBItemValue->setReturnKeyStartsNewLine (false);
    txtBItemValue->setReadOnly (false);
    txtBItemValue->setScrollbarsShown (true);
    txtBItemValue->setCaretVisible (true);
    txtBItemValue->setPopupMenuEnabled (true);
    txtBItemValue->setText (String());

    txtBItemValue->setBounds (856, 96, 88, 24);

    lblBItemValueEquiv.reset (new Label ("new label",
                                         TRANS("()")));
    addAndMakeVisible (lblBItemValueEquiv.get());
    lblBItemValueEquiv->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblBItemValueEquiv->setJustificationType (Justification::centredLeft);
    lblBItemValueEquiv->setEditable (false, false, false);
    lblBItemValueEquiv->setColour (TextEditor::textColourId, Colours::black);
    lblBItemValueEquiv->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblBItemValueEquiv->setBounds (856, 120, 160, 24);

    chkBItemHex.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (chkBItemHex.get());
    chkBItemHex->setButtonText (TRANS("Hex"));
    chkBItemHex->addListener (this);

    chkBItemHex->setBounds (952, 96, 56, 24);

    btnSaveXML.reset (new TextButton ("new button"));
    addAndMakeVisible (btnSaveXML.get());
    btnSaveXML->setButtonText (TRANS("Save XML"));
    btnSaveXML->setConnectedEdges (Button::ConnectedOnRight);
    btnSaveXML->addListener (this);

    btnSaveXML->setBounds (808, 176, 104, 24);

    btnLoadXML.reset (new TextButton ("new button"));
    addAndMakeVisible (btnLoadXML.get());
    btnLoadXML->setButtonText (TRANS("Load XML"));
    btnLoadXML->setConnectedEdges (Button::ConnectedOnLeft);
    btnLoadXML->addListener (this);

    btnLoadXML->setBounds (912, 176, 104, 24);

    chkLibFixAddr.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (chkLibFixAddr.get());
    chkLibFixAddr->setButtonText (TRANS("Convert Sample Addr for Table"));
    chkLibFixAddr->addListener (this);
    chkLibFixAddr->setToggleState (true, dontSendNotification);

    chkLibFixAddr->setBounds (512, 480, 232, 24);


    //[UserPreSize]

    lsmFields.reset(new TextListModel());
    lsmFields->setListener(this);

    lstFields.reset(new ListBox("Fields", lsmFields.get()));
    addAndMakeVisible(lstFields.get());
    lstFields->setMultipleSelectionEnabled(false);
    lstFields->setRowHeight(16);
    lstFields->setOutlineThickness(1);
    lstFields->setColour(ListBox::outlineColourId, Colours::lightgrey);

    lsmLibSets.reset(new TextListModel());
    lsmLibSets->setListener(this);

    lstLibSets.reset(new ListBox("LibSets", lsmLibSets.get()));
    addAndMakeVisible(lstLibSets.get());
    lstLibSets->setMultipleSelectionEnabled(false);
    lstLibSets->setRowHeight(16);
    lstLibSets->setOutlineThickness(1);
    lstLibSets->setColour(ListBox::outlineColourId, Colours::lightgrey);

    lsmLibItems.reset(new TextListModel());
    lsmLibItems->setListener(this);

    lstLibItems.reset(new ListBox("LibItems", lsmLibItems.get()));
    addAndMakeVisible(lstLibItems.get());
    lstLibItems->setMultipleSelectionEnabled(false);
    lstLibItems->setRowHeight(16);
    lstLibItems->setOutlineThickness(1);
    lstLibItems->setColour(ListBox::outlineColourId, Colours::lightgrey);

    lsmBItems.reset(new TextListModel());
    lsmBItems->setListener(this);

    lstBItems.reset(new ListBox("BItems", lsmBItems.get()));
    addAndMakeVisible(lstBItems.get());
    lstBItems->setMultipleSelectionEnabled(false);
    lstBItems->setRowHeight(16);
    lstBItems->setOutlineThickness(1);
    lstBItems->setColour(ListBox::outlineColourId, Colours::lightgrey);


    txtFieldName->addListener(this);
    txtArrayLen->addListener(this);
    txtDefaultVal->addListener(this);
    txtLibItemName->addListener(this);
    txtMapPNum->addListener(this);
    txtMapPNote->addListener(this);
    txtMapDS1->addListener(this);
    txtMapDS2->addListener(this);
    txtMapDS3->addListener(this);
    txtBItemName->addListener(this);
    txtBItemValue->addListener(this);

    //[/UserPreSize]

    setSize (1078, 713);


    //[Constructor] You can add your own custom stuff here..
    abiaddr = abaddr = -1;
    libselbankidx = libselitemidx = -1;

    cbxLibList->setText("Instruments");

    romDescLoaded();
    //[/Constructor]
}

AudiobankPane::~AudiobankPane()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    groupComponent2 = nullptr;
    groupComponent4 = nullptr;
    groupComponent3 = nullptr;
    groupComponent = nullptr;
    cbxEditStruct = nullptr;
    label2 = nullptr;
    optPointer = nullptr;
    cbxDataType = nullptr;
    cbxPtrTo = nullptr;
    label3 = nullptr;
    txtFieldName = nullptr;
    optArray = nullptr;
    optArrayFixed = nullptr;
    optArrayVar = nullptr;
    txtArrayLen = nullptr;
    cbxArrayLenVar = nullptr;
    label4 = nullptr;
    cbxMeaning = nullptr;
    lblStructBegin = nullptr;
    lblStructEnd = nullptr;
    label5 = nullptr;
    txtDefaultVal = nullptr;
    btnFieldAdd = nullptr;
    btnFieldDel = nullptr;
    btnFieldUp = nullptr;
    btnFieldDn = nullptr;
    label6 = nullptr;
    label7 = nullptr;
    lblStructSemicolon = nullptr;
    label = nullptr;
    cbxLibList = nullptr;
    btnLibAdd = nullptr;
    label8 = nullptr;
    txtLibItemName = nullptr;
    chkLibMerge = nullptr;
    btnBItemAdd = nullptr;
    btnBItemDupl = nullptr;
    btnBItemDel = nullptr;
    btnBItemUp = nullptr;
    btnBItemDn = nullptr;
    label12 = nullptr;
    txtBItemName = nullptr;
    cbxAlign = nullptr;
    optMapProgram = nullptr;
    txtMapPNum = nullptr;
    lblMapPNote = nullptr;
    txtMapPNote = nullptr;
    optMapDrum = nullptr;
    txtMapDS1 = nullptr;
    txtMapDS2 = nullptr;
    txtMapDS3 = nullptr;
    lblMapSplits = nullptr;
    btnBUp = nullptr;
    btnBOpen = nullptr;
    lblBankPath = nullptr;
    lblBItemType = nullptr;
    lblBItemValue = nullptr;
    txtBItemValue = nullptr;
    lblBItemValueEquiv = nullptr;
    chkBItemHex = nullptr;
    btnSaveXML = nullptr;
    btnLoadXML = nullptr;
    chkLibFixAddr = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    lstFields = nullptr;
    lstLibSets = nullptr;
    lstLibItems = nullptr;
    lstBItems = nullptr;
    //[/Destructor]
}

//==============================================================================
void AudiobankPane::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    {
        int x = 17, y = 240, width = 2, height = 24;
        Colour fillColour = Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
    }

    {
        int x = 209, y = 240, width = 2, height = 44;
        Colour fillColour = Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void AudiobankPane::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    lstFields->setBounds(8, 40, 432, 112);
    lstLibSets->setBounds(8, 392, 240, 288);
    lstLibItems->setBounds(256, 392, 240, 288);
    lstBItems->setBounds(456, 48, 280, 288);
    //[/UserResized]
}

void AudiobankPane::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    String text = comboBoxThatHasChanged->getText();
    bool repaintFieldEntry = false;
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == cbxEditStruct.get())
    {
        //[UserComboBoxCode_cbxEditStruct] -- add your combo box handling code here..
        selstruct = abfstructsnode.getChildWithProperty("name", text);
        if(!selstruct.isValid()){
            selstruct = ValueTree("struct");
            selstruct.setProperty("name", text, nullptr);
            abfstructsnode.addChild(selstruct, -1, nullptr);
        }
        fillFieldsList();
        fillMeaningsBox();
        //[/UserComboBoxCode_cbxEditStruct]
    }
    else if (comboBoxThatHasChanged == cbxDataType.get())
    {
        //[UserComboBoxCode_cbxDataType] -- add your combo box handling code here..
        if(!selfield.isValid()) return;
        if(text == "") text = "uint32";
        selfield.setProperty("datatype", text, nullptr);
        repaintFieldEntry = true;
        //[/UserComboBoxCode_cbxDataType]
    }
    else if (comboBoxThatHasChanged == cbxPtrTo.get())
    {
        //[UserComboBoxCode_cbxPtrTo] -- add your combo box handling code here..
        if(!selfield.isValid()) return;
        if((bool)selfield.getProperty("ispointer", false) == false) return;
        if(text == "") text = "ABDrumList";
        selfield.setProperty("ptrto", text, nullptr);
        repaintFieldEntry = true;
        //[/UserComboBoxCode_cbxPtrTo]
    }
    else if (comboBoxThatHasChanged == cbxArrayLenVar.get())
    {
        //[UserComboBoxCode_cbxArrayLenVar] -- add your combo box handling code here..
        if(!selfield.isValid()) return;
        if((bool)selfield.getProperty("isarray", false) == false) return;
        if(text == "") text = "NUM_INST";
        selfield.setProperty("arraylenvar", text, nullptr);
        selfield.removeProperty("arraylenfixed", nullptr);
        optArrayFixed->setToggleState(false, dontSendNotification);
        optArrayVar->setToggleState(true, dontSendNotification);
        repaintFieldEntry = true;
        //[/UserComboBoxCode_cbxArrayLenVar]
    }
    else if (comboBoxThatHasChanged == cbxMeaning.get())
    {
        //[UserComboBoxCode_cbxMeaning] -- add your combo box handling code here..
        if(!selfield.isValid()) return;
        if(text == "") text = "None";
        selfield.setProperty("meaning", text, nullptr);
        repaintFieldEntry = true;
        //[/UserComboBoxCode_cbxMeaning]
    }
    else if (comboBoxThatHasChanged == cbxLibList.get())
    {
        //[UserComboBoxCode_cbxLibList] -- add your combo box handling code here..
        fillLibItemsBox();
        //[/UserComboBoxCode_cbxLibList]
    }
    else if (comboBoxThatHasChanged == cbxAlign.get())
    {
        //[UserComboBoxCode_cbxAlign] -- add your combo box handling code here..
        abfstructsnode.setProperty("align", text, nullptr);
        //[/UserComboBoxCode_cbxAlign]
    }

    //[UsercomboBoxChanged_Post]
    if(repaintFieldEntry){
        int row = lstFields->getLastRowSelected();
        lsmFields->set(row, BankFile::getFieldDesc(selfield, true));
        lstFields->repaintRow(row);
    }
    //[/UsercomboBoxChanged_Post]
}

void AudiobankPane::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    bool state = buttonThatWasClicked->getToggleState();
    bool repaintFieldEntry = false;
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == optPointer.get())
    {
        //[UserButtonCode_optPointer] -- add your button handler code here..
        if(!selfield.isValid()) return;
        selfield.setProperty("ispointer", state, nullptr);
        if(state){
            if(selfield.getProperty("ptrto", "") == ""){
                selfield.setProperty("ptrto", "ABDrumList", nullptr);
            }
            cbxPtrTo->setText(selfield.getProperty("ptrto", "ABDrumList").toString());
        }else{
            cbxPtrTo->setText("");
        }
        repaintFieldEntry = true;
        //[/UserButtonCode_optPointer]
    }
    else if (buttonThatWasClicked == optArray.get())
    {
        //[UserButtonCode_optArray] -- add your button handler code here..
        if(!selfield.isValid()) return;
        selfield.setProperty("isarray", state, nullptr);
        if(state){
            selfield.setProperty("arraylenfixed", 1, nullptr);
            txtArrayLen->setText("1", false);
            optArrayFixed->setToggleState(true, dontSendNotification);
            optArrayVar->setToggleState(false, dontSendNotification);
        }else{
            selfield.removeProperty("arraylenfixed", nullptr);
            selfield.removeProperty("arraylenvar", nullptr);
            cbxArrayLenVar->setText("", dontSendNotification);
            txtArrayLen->setText("", false);
            optArrayFixed->setToggleState(false, dontSendNotification);
            optArrayVar->setToggleState(false, dontSendNotification);
        }
        repaintFieldEntry = true;
        //[/UserButtonCode_optArray]
    }
    else if (buttonThatWasClicked == optArrayFixed.get())
    {
        //[UserButtonCode_optArrayFixed] -- add your button handler code here..
        if(!selfield.isValid()) return;
        if(!state) return;
        if(!(bool)selfield.getProperty("isarray", false)) return;
        selfield.setProperty("arraylenfixed", 1, nullptr);
        selfield.removeProperty("arraylenvar", nullptr);
        cbxArrayLenVar->setText("", dontSendNotification);
        txtArrayLen->setText("1", false);
        repaintFieldEntry = true;
        //[/UserButtonCode_optArrayFixed]
    }
    else if (buttonThatWasClicked == optArrayVar.get())
    {
        //[UserButtonCode_optArrayVar] -- add your button handler code here..
        if(!selfield.isValid()) return;
        if(!state) return;
        if(!(bool)selfield.getProperty("isarray", false)) return;
        selfield.removeProperty("arraylenfixed", nullptr);
        selfield.setProperty("arraylenvar", "NUM_INST", nullptr);
        cbxArrayLenVar->setText("NUM_INST", dontSendNotification);
        txtArrayLen->setText("", false);
        repaintFieldEntry = true;
        //[/UserButtonCode_optArrayVar]
    }
    else if (buttonThatWasClicked == btnFieldAdd.get())
    {
        //[UserButtonCode_btnFieldAdd] -- add your button handler code here..
        if(!selstruct.isValid()) return;
        int addidx = selstruct.getNumChildren();
        if(selfield.isValid()){
            addidx = selstruct.indexOf(selfield) + 1;
        }
        selfield = ValueTree("field");
        selfield.setProperty("name", "unnamed", nullptr);
        selfield.setProperty("datatype", "uint32", nullptr);
        selfield.setProperty("ispointer", false, nullptr);
        selfield.setProperty("isarray", false, nullptr);
        selfield.setProperty("meaning", "None", nullptr);
        selstruct.addChild(selfield, addidx, nullptr);
        fillFieldsList();
        lstFields->selectRow(addidx);
        //[/UserButtonCode_btnFieldAdd]
    }
    else if (buttonThatWasClicked == btnFieldDel.get())
    {
        //[UserButtonCode_btnFieldDel] -- add your button handler code here..
        if(!selstruct.isValid()) return;
        if(!selfield.isValid()) return;
        int i = selstruct.indexOf(selfield);
        selstruct.removeChild(i, nullptr);
        if(i > 0) i--;
        selfield = ValueTree();
        fillFieldsList();
        lstFields->selectRow(i);
        //[/UserButtonCode_btnFieldDel]
    }
    else if (buttonThatWasClicked == btnFieldUp.get())
    {
        //[UserButtonCode_btnFieldUp] -- add your button handler code here..
        if(!selstruct.isValid()) return;
        if(!selfield.isValid()) return;
        int i = selstruct.indexOf(selfield);
        if(i <= 0) return;
        selstruct.moveChild(i, i-1, nullptr);
        i--;
        fillFieldsList();
        lstFields->selectRow(i);
        //[/UserButtonCode_btnFieldUp]
    }
    else if (buttonThatWasClicked == btnFieldDn.get())
    {
        //[UserButtonCode_btnFieldDn] -- add your button handler code here..
        if(!selstruct.isValid()) return;
        if(!selfield.isValid()) return;
        int i = selstruct.indexOf(selfield);
        if(i >= selstruct.getNumChildren() - 1) return;
        selstruct.moveChild(i, i+1, nullptr);
        i++;
        fillFieldsList();
        lstFields->selectRow(i);
        //[/UserButtonCode_btnFieldDn]
    }
    else if (buttonThatWasClicked == btnLibAdd.get())
    {
        //[UserButtonCode_btnLibAdd] -- add your button handler code here..
        if(!libselitem.isValid()) return;
        if(libselbank == nullptr) return;
        if(seq64.bank == nullptr) return;
        if(seq64.rom.getSize() == 0) return;
        String sublistname = cbxLibList->getText(), itemtype, showlist;
        if(sublistname == "Instruments"){
            itemtype = "ABInstrument";
            showlist = "instruments";
        }else if(sublistname == "Drums"){
            itemtype = "ABDrum";
            showlist = "drums";
        }else if(sublistname == "Sound Effects"){
            NativeMessageBox::showMessageBox(AlertWindow::WarningIcon, "seq64", "Import SFX not yet supported.");
            return;
        }else{
            SEQ64::say("getBankSubList error: sublistname = " + sublistname);
            return;
        }
        int itemindex = lstLibItems->getLastRowSelected();
        ValueTree res = seq64.bank->importNode(seq64.rom, *libselbank, itemtype, itemindex,
                chkLibMerge->getToggleState(), chkLibFixAddr->getToggleState());
        if(res.isValid()){
            bpath = seq64.bank->d.getChildWithName(showlist);
            fillBItemsBox();
            lstBItems->selectRow(bpath.getNumChildren() - 1);
        }
        //[/UserButtonCode_btnLibAdd]
    }
    else if (buttonThatWasClicked == chkLibMerge.get())
    {
        //[UserButtonCode_chkLibMerge] -- add your button handler code here..
        //[/UserButtonCode_chkLibMerge]
    }
    else if (buttonThatWasClicked == btnBItemAdd.get())
    {
        //[UserButtonCode_btnBItemAdd] -- add your button handler code here..
        if(seq64.bank == nullptr) return;
        if(!bpath.isValid()) return;
        bool b = seq64.bank->addNode(bpath);
        if(b){
            fillBItemsBox();
            lstBItems->selectRow(bpath.getNumChildren() - 1);
        }
        //[/UserButtonCode_btnBItemAdd]
    }
    else if (buttonThatWasClicked == btnBItemDupl.get())
    {
        //[UserButtonCode_btnBItemDupl] -- add your button handler code here..
        if(seq64.bank == nullptr) return;
        if(!bselnode.isValid()) return;
        int row = lstBItems->getLastRowSelected();
        bool b = seq64.bank->duplicateNode(bpath, bselnode);
        if(b){
            fillBItemsBox();
            lstBItems->selectRow(row+1);
        }
        //[/UserButtonCode_btnBItemDupl]
    }
    else if (buttonThatWasClicked == btnBItemDel.get())
    {
        //[UserButtonCode_btnBItemDel] -- add your button handler code here..
        if(seq64.bank == nullptr) return;
        if(!bselnode.isValid()) return;
        bool b = seq64.bank->deleteNode(bpath, bselnode);
        if(b){
            fillBItemsBox();
        }
        //[/UserButtonCode_btnBItemDel]
    }
    else if (buttonThatWasClicked == btnBItemUp.get())
    {
        //[UserButtonCode_btnBItemUp] -- add your button handler code here..
        if(seq64.bank == nullptr) return;
        if(!bselnode.isValid()) return;
        int row = lstBItems->getLastRowSelected();
        bool b = seq64.bank->moveNodeUp(bpath, bselnode);
        if(b){
            fillBItemsBox();
            lstBItems->selectRow(row-1);
        }
        //[/UserButtonCode_btnBItemUp]
    }
    else if (buttonThatWasClicked == btnBItemDn.get())
    {
        //[UserButtonCode_btnBItemDn] -- add your button handler code here..
        if(seq64.bank == nullptr) return;
        if(!bselnode.isValid()) return;
        int row = lstBItems->getLastRowSelected();
        bool b = seq64.bank->moveNodeDown(bpath, bselnode);
        if(b){
            fillBItemsBox();
            lstBItems->selectRow(row+1);
        }
        //[/UserButtonCode_btnBItemDn]
    }
    else if (buttonThatWasClicked == optMapProgram.get())
    {
        //[UserButtonCode_optMapProgram] -- add your button handler code here..
        if(!libselitem.isValid()) return;
        if(!state) return;
        libselitem.setProperty("map", "program", nullptr);
        libselitem.removeProperty("drum", nullptr);
        libselitem.removeProperty("drumsplit1", nullptr);
        libselitem.removeProperty("drumsplit2", nullptr);
        libselitem.removeProperty("drumsplit3", nullptr);
        libselbank->copyItemPropsToRDItem(getListName(cbxLibList->getText()), libselitemidx, libselitem);
        fillLibItemControls();
        //[/UserButtonCode_optMapProgram]
    }
    else if (buttonThatWasClicked == optMapDrum.get())
    {
        //[UserButtonCode_optMapDrum] -- add your button handler code here..
        if(!libselitem.isValid()) return;
        if(!state) return;
        libselitem.setProperty("map", "drum", nullptr);
        libselitem.removeProperty("note", nullptr);
        libselitem.removeProperty("transpose", nullptr);
        libselbank->copyItemPropsToRDItem(getListName(cbxLibList->getText()), libselitemidx, libselitem);
        fillLibItemControls();
        //[/UserButtonCode_optMapDrum]
    }
    else if (buttonThatWasClicked == btnBUp.get())
    {
        //[UserButtonCode_btnBUp] -- add your button handler code here..
        if(seq64.bank == nullptr) return;
        ValueTree parent = seq64.bank->getNodeParent(bpath);
        if(parent.isValid()){
            bpath = parent;
        }
        fillBItemsBox();
        //[/UserButtonCode_btnBUp]
    }
    else if (buttonThatWasClicked == btnBOpen.get())
    {
        //[UserButtonCode_btnBOpen] -- add your button handler code here..
        bOpen(lstBItems->getLastRowSelected());
        //[/UserButtonCode_btnBOpen]
    }
    else if (buttonThatWasClicked == chkBItemHex.get())
    {
        //[UserButtonCode_chkBItemHex] -- add your button handler code here..
        fillBItemsControls(true);
        //[/UserButtonCode_chkBItemHex]
    }
    else if (buttonThatWasClicked == btnSaveXML.get())
    {
        //[UserButtonCode_btnSaveXML] -- add your button handler code here..
        if(seq64.bank == nullptr) return;
        Identifier idXmlBank = "understandxmlbank";
        if(seq64.readProperty(idXmlBank) != "yes"){
            if(!NativeMessageBox::showOkCancelBox(AlertWindow::WarningIcon,
                    "Are you sure you know what you're doing?",
                    "This saves an XML file containing the entire contents of\n"
                    "the currently loaded bank, including header/metadata and\n"
                    "node labels (e.g. instrument names, etc.)--but not including\n"
                    "the actual audio sample data of course. Loading it again\n"
                    "will restore the state, but it will only be compatible with\n"
                    "ROMs that have the same sample tables (generally, different\n"
                    "hacks/edits of the same ROM are fine but different released\n"
                    "ROM versions may not be). Of course it is also dependent on\n"
                    "the Audiobank format (as defined in the RomDesc) being the\n"
                    "same between the source and destination ROM.\n\n"
                    "Are you sure you understand and want to continue?", nullptr, nullptr)) return;
            seq64.writeProperty(idXmlBank, "yes");
        }
        File savelocation = SEQ64::readFolderProperty("romfolder");
        FileChooser box("Save Bank as XML", savelocation, "*.xml", SEQ64::useNativeFileChooser());
        if(!box.browseForFileToSave(true)) return;
        savelocation = box.getResult();
        if(!seq64.bank->saveXML(savelocation)){
            NativeMessageBox::showMessageBox(AlertWindow::WarningIcon, "Oh no",
                    "Saving failed, check the command line output for details.");
        }
        //[/UserButtonCode_btnSaveXML]
    }
    else if (buttonThatWasClicked == btnLoadXML.get())
    {
        //[UserButtonCode_btnLoadXML] -- add your button handler code here..
        Identifier idXmlBank = "understandxmlbank";
        if(seq64.readProperty(idXmlBank) != "yes"){
            if(!NativeMessageBox::showOkCancelBox(AlertWindow::WarningIcon,
                    "Are you sure you know what you're doing?",
                    "This loads an XML file saved by the \"Save XML\" button\n"
                    "containing the entire contents of the currently loaded bank,\n"
                    "including header/metadata and node labels (e.g. instrument\n"
                    "names, etc.)--but not including the actual audio sample data\n"
                    "of course. Loading it will restore the state, but it will only\n"
                    "be compatible with ROMs that have the same sample tables\n"
                    "(generally, different hacks/edits of the same ROM are fine but\n"
                    "different released ROM versions may not be). Of course it is\n"
                    "also dependent on the Audiobank format (as defined in the\n"
                    "RomDesc) being the same between the source and destination ROM.\n\n"
                    "Are you sure you understand and want to continue?", nullptr, nullptr)) return;
            seq64.writeProperty(idXmlBank, "yes");
        }
        if(!seq64.romdesc.isValid() || seq64.romdesc.getOrCreateChildWithName("cmdlist", nullptr).getNumChildren() == 0){
            NativeMessageBox::showMessageBox (AlertWindow::WarningIcon, "Guess you didn't know what you were doing after all",
                "Load a RomDesc before trying to load a raw bank.");
            seq64.writeProperty(idXmlBank, "no");
            return;
        }
        if(&*seq64.bank != nullptr){
            if(!NativeMessageBox::showOkCancelBox(AlertWindow::WarningIcon,
                    "Overwrite?",
                    "A bank is already loaded, are you sure you want to overwrite it?", nullptr, nullptr)) return;
        }
        File loadlocation = SEQ64::readFolderProperty("romfolder");
        FileChooser box("Load XML as Bank", loadlocation, "*.xml", SEQ64::useNativeFileChooser());
        if(!box.browseForFileToOpen()) return;
        loadlocation = box.getResult();
        seq64.bank.reset(new BankFile(seq64.romdesc));
        if(!seq64.bank->loadXML(loadlocation)){
            NativeMessageBox::showMessageBox(AlertWindow::WarningIcon, "Oh no",
                    "Loading failed, check the command line output for details.");
        }
        bankLoaded();
        //[/UserButtonCode_btnLoadXML]
    }
    else if (buttonThatWasClicked == chkLibFixAddr.get())
    {
        //[UserButtonCode_chkLibFixAddr] -- add your button handler code here..
        //[/UserButtonCode_chkLibFixAddr]
    }

    //[UserbuttonClicked_Post]
    if(repaintFieldEntry){
        int row = lstFields->getLastRowSelected();
        lsmFields->set(row, BankFile::getFieldDesc(selfield, true));
        lstFields->repaintRow(row);
    }
    //[/UserbuttonClicked_Post]
}

void AudiobankPane::visibilityChanged()
{
    //[UserCode_visibilityChanged] -- Add your code here...
    //SEQ64::say("AudiobankPane::visibilityChanged()");
    //gotABI();
    //[/UserCode_visibilityChanged]
}

void AudiobankPane::broughtToFront()
{
    //[UserCode_broughtToFront] -- Add your code here...
    //SEQ64::say("AudiobankPane::broughtToFront()");
    gotABI();
    //[/UserCode_broughtToFront]
}

void AudiobankPane::focusGained (FocusChangeType cause)
{
    //[UserCode_focusGained] -- Add your code here...
    //SEQ64::say("AudiobankPane::focusGained()");
    //gotABI();
    //[/UserCode_focusGained]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void AudiobankPane::rowSelected(TextListModel* parent, int row){
    if(parent == &*lsmFields){
        if(!selstruct.isValid()) return;
        selfield = selstruct.getChild(row);
        fillFieldParams();
    }else if(parent == &*lsmLibSets){
        if(abiaddr < 0 || abaddr < 0) return;
        libselbankidx = row;
        libselbank.reset(new BankFile(seq64.romdesc));
        libselbank->load(seq64.rom, libselbankidx);
        fillLibItemsBox();
    }else if(parent == &*lsmLibItems){
        ValueTree list = getBankSubList(libselbankidx, cbxLibList->getText());
        if(list.isValid()){
            ValueTree temp = list.getChild(row);
            if(temp.isValid()){
                libselitemidx = row;
                libselitem = temp;
                fillLibItemControls();
                return;
            }
        }
        libselitemidx = -1;
        libselitem = ValueTree();
    }else if(parent == &*lsmBItems){
        if(!bpath.isValid()) return;
        bselnode = bpath.getChild(row);
        fillBItemsControls(true);
    }
}

void AudiobankPane::rowDoubleClicked(TextListModel* parent, int row){
    if(parent == &*lsmBItems){
        bOpen(row);
    }
}

void AudiobankPane::textEditorTextChanged(TextEditor& editorThatWasChanged){
    int val;
    String text = editorThatWasChanged.getText();
    if(        &editorThatWasChanged == &*txtMapPNum
            || &editorThatWasChanged == &*txtMapPNote
            || &editorThatWasChanged == &*txtMapDS1
            || &editorThatWasChanged == &*txtMapDS2
            || &editorThatWasChanged == &*txtMapDS3 ){
        val = text.getIntValue();
    }else{
        val = text.getHexValue32();
    }
    bool turnRed = (val <= 0);
    bool repaintFieldEntry = false;
    bool repaintBItemEntry = false;
    bool copyItemToRD = false;

    if(&editorThatWasChanged == &*txtFieldName){
        turnRed = (text == "");
        if(!selfield.isValid()) return;
        selfield.setProperty("name", text, nullptr);
        repaintFieldEntry = true;
    }else if(&editorThatWasChanged == &*txtArrayLen){
        if(!selfield.isValid()) return;
        if(!(bool)selfield.getProperty("isarray", false)){
            txtArrayLen->setText("");
            return;
        }
        selfield.setProperty("arraylenfixed", val, nullptr);
        optArrayFixed->setToggleState(true, dontSendNotification);
        optArrayVar->setToggleState(false, dontSendNotification);
        repaintFieldEntry = true;
    }else if(&editorThatWasChanged == &*txtDefaultVal){
        if(!selfield.isValid()) return;
         turnRed = false;
        if(text == ""){
            selfield.removeProperty("defaultval", nullptr);
        }else{
            selfield.setProperty("defaultval", val, nullptr);
        }
        repaintFieldEntry = true;
    }else if(&editorThatWasChanged == &*txtLibItemName){
        if(!libselitem.isValid()) return;
        turnRed = false;
        libselitem.setProperty("name", text, nullptr);
        lsmLibItems->set(libselitemidx, text);
        lstLibItems->repaintRow(libselitemidx);
        copyItemToRD = true;
    }else if(&editorThatWasChanged == &*txtMapPNum){
        if(!libselitem.isValid()) return;
        if(val >= 128) turnRed = true;
        libselitem.setProperty("program", val, nullptr);
        copyItemToRD = true;
    }else if(&editorThatWasChanged == &*txtMapPNote){
        if(!libselitem.isValid()) return;
        if(val >= 128) turnRed = true;
        if(cbxLibList->getText() == "Instruments"){
            libselitem.setProperty("transpose", val, nullptr);
            turnRed = (val < -127 || val > 127);
        }else{
            libselitem.setProperty("note", val, nullptr);
        }
        copyItemToRD = true;
    }else if(&editorThatWasChanged == &*txtMapDS1){
        if(!libselitem.isValid()) return;
        if(val >= 128) turnRed = true;
        if(cbxLibList->getText() == "Instruments"){
            libselitem.setProperty("drumsplit1", val, nullptr);
        }else{
            libselitem.setProperty("note", val, nullptr);
        }
        copyItemToRD = true;
    }else if(&editorThatWasChanged == &*txtMapDS2){
        if(!libselitem.isValid()) return;
        if(val >= 128) turnRed = true;
        if(cbxLibList->getText() == "Instruments"){
            libselitem.setProperty("drumsplit2", val, nullptr);
        }
        copyItemToRD = true;
    }else if(&editorThatWasChanged == &*txtMapDS3){
        if(!libselitem.isValid()) return;
        if(val >= 128) turnRed = true;
        if(cbxLibList->getText() == "Instruments"){
            libselitem.setProperty("drumsplit3", val, nullptr);
        }
        copyItemToRD = true;
    }else if(&editorThatWasChanged == &*txtBItemName){
        if(seq64.bank == nullptr) return;
        if(!bselnode.isValid()) return;
        turnRed = !seq64.bank->setNodeName(bselnode, text);
        if(!turnRed){
            repaintBItemEntry = true;
        }
    }else if(&editorThatWasChanged == &*txtBItemValue){
        if(seq64.bank == nullptr) return;
        if(!bselnode.isValid()) return;
        turnRed = !seq64.bank->setNodeValue(bselnode, text, chkBItemHex->getToggleState());
        if(!turnRed){
            fillBItemsControls(false);
            repaintBItemEntry = true;
        }
    }
    if(turnRed){
        editorThatWasChanged.setColour(TextEditor::backgroundColourId, Colours::red);
    }else{
        editorThatWasChanged.setColour(TextEditor::backgroundColourId, LFWidgetColor());
    }
    if(repaintFieldEntry){
        int row = lstFields->getLastRowSelected();
        lsmFields->set(row, BankFile::getFieldDesc(selfield, true));
        lstFields->repaintRow(row);
    }
    if(repaintBItemEntry){
        int row = lstBItems->getLastRowSelected();
        lsmBItems->set(row, seq64.bank->getNodeDesc(seq64.bank->getNodeChild(bpath, row)));
        lstBItems->repaintRow(row);
    }
    if(copyItemToRD){
        libselbank->copyItemPropsToRDItem(getListName(cbxLibList->getText()), libselitemidx, libselitem);
    }
}

void AudiobankPane::fillFieldsList(){
    lsmFields->clear();
    lstFields->updateContent();
    if(!selstruct.isValid()) return;
    for(int i=0; i<selstruct.getNumChildren(); i++){
        lsmFields->add(BankFile::getFieldDesc(selstruct.getChild(i), true));
    }
    lstFields->updateContent();
}

void AudiobankPane::fillFieldParams(){
    if(!selfield.isValid()) return;
    txtFieldName->setText(selfield.getProperty("name", "unnamed").toString());
    cbxDataType->setText(selfield.getProperty("datatype", "uint32").toString());
    optPointer->setToggleState((bool)selfield.getProperty("ispointer", false), dontSendNotification);
    cbxPtrTo->setText(selfield.getProperty("ptrto", "").toString());
    if((bool)selfield.getProperty("isarray", false)){
        optArray->setToggleState(true, dontSendNotification);
        if(selfield.hasProperty("arraylenfixed")){
            txtArrayLen->setText(ROM::hex((uint8)(int)selfield.getProperty("arraylenfixed", 0)));
            cbxArrayLenVar->setText("");
            optArrayFixed->setToggleState(true, dontSendNotification);
            optArrayVar->setToggleState(false, dontSendNotification);
        }else{
            txtArrayLen->setText("");
            cbxArrayLenVar->setText(selfield.getProperty("arraylenvar", "NUM_INST").toString());
            optArrayFixed->setToggleState(false, dontSendNotification);
            optArrayVar->setToggleState(true, dontSendNotification);
        }
    }else{
        optArray->setToggleState(false, dontSendNotification);
        txtArrayLen->setText("");
        cbxArrayLenVar->setText("");
        optArrayFixed->setToggleState(false, dontSendNotification);
        optArrayVar->setToggleState(false, dontSendNotification);
    }
    cbxMeaning->setText(selfield.getProperty("meaning", "None").toString());
    if(selfield.hasProperty("defaultval")){
        txtDefaultVal->setText(String::toHexString((int)selfield.getProperty("defaultval")));
    }else{
        txtDefaultVal->setText("");
    }
}

void AudiobankPane::fillMeaningsBox(){
    String editstruct = cbxEditStruct->getText();
    cbxMeaning->clear();
    cbxMeaning->addItem("None", cbxMeaning->getNumItems()+1);
    if(editstruct == "ABIndexEntry"){
        cbxMeaning->addItem("Ptr Bank (in Audiobank)", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("Bank Length", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("Sample Table number", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("NUM_INST", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("NUM_DRUM", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("NUM_SFX", cbxMeaning->getNumItems()+1);
    }else if(editstruct == "ABHeader"){
        cbxMeaning->addItem("Sample Table number", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("NUM_INST", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("NUM_DRUM", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("NUM_SFX", cbxMeaning->getNumItems()+1);
    }else if(editstruct == "ABBank"){
        cbxMeaning->addItem("Ptr Drum List", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("Ptr SFX List", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("List of Ptrs to Insts", cbxMeaning->getNumItems()+1);
        //cbxMeaning->addItem("Ptr Ch10 Drum", cbxMeaning->getNumItems()+1);
    }else if(editstruct == "ABDrumList"){
        cbxMeaning->addItem("List of Ptrs to Drums", cbxMeaning->getNumItems()+1);
    }else if(editstruct == "ABSFXList"){
        cbxMeaning->addItem("List of Sounds", cbxMeaning->getNumItems()+1);
    }else if(editstruct == "ABInstrument"){
        cbxMeaning->addItem("Split Point 1", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("Split Point 2", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("Ptr Envelope", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("List of 3 Sounds for Splits", cbxMeaning->getNumItems()+1);
    }else if(editstruct == "ABDrum"){
        cbxMeaning->addItem("Drum Sound", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("Ptr Envelope", cbxMeaning->getNumItems()+1);
    }else if(editstruct == "ABEnvelope"){
        //none
    }else if(editstruct == "ABSound"){
        cbxMeaning->addItem("Ptr Sample", cbxMeaning->getNumItems()+1);
    }else if(editstruct == "ABSample"){
        cbxMeaning->addItem("Sample Address (in Sample Table)", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("Sample Length", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("Ptr ALADPCMLoop", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("Ptr ALADPCMBook", cbxMeaning->getNumItems()+1);
    }else if(editstruct == "ALADPCMBook"){
        cbxMeaning->addItem("NUM_PRED", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("Array of Predictors", cbxMeaning->getNumItems()+1);
    }else if(editstruct == "ALADPCMPredictor"){
        //none
    }else if(editstruct == "ALADPCMLoop"){
        cbxMeaning->addItem("Loop Start", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("Loop End", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("Loop Count", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("Tail Data (if Loop Start != 0)", cbxMeaning->getNumItems()+1);
    }else if(editstruct == "ALADPCMTail"){
        //none
    }else{
        cbxMeaning->clear(dontSendNotification);
        cbxMeaning->addItem("ERROR fillMeaningsBox", cbxMeaning->getNumItems()+1);
    }
    cbxMeaning->setSelectedItemIndex(0, dontSendNotification);
}

String AudiobankPane::getListName(String cbxLibListText){
    if(cbxLibListText == "Instruments"){
        return "instruments";
    }else if(cbxLibListText == "Drums"){
        return "drums";
    }else if(cbxLibListText == "Sound Effects"){
        return "sfx";
    }else{
        return "Error";
    }
}

ValueTree AudiobankPane::getBankSubList(int banknum, String cbxLibListText){
    if(libselbank == nullptr) return ValueTree();
    ValueTree ret = libselbank->d.getChildWithName(getListName(cbxLibListText));
    if(!ret.isValid()){
        SEQ64::say("getBankSubList error: cbxLibListText = " + cbxLibListText);
        return ValueTree();
    }
    return ret;
}

void AudiobankPane::fillLibItemsBox(){
    libselitemidx = -1;
    libselitem = ValueTree();
    fillLibItemControls();
    lsmLibItems->clear();
    lstLibItems->updateContent();
    ValueTree list = getBankSubList(libselbankidx, cbxLibList->getText());
    if(!list.isValid()) return;
    int count = list.getNumChildren();
    ValueTree temp;
    for(int i=0; i<count; i++){
        temp = list.getChild(i);
        lsmLibItems->add(temp.getProperty("name", "Error").toString());
    }
    lstLibItems->updateContent();
}


void AudiobankPane::fillLibItemControls(){
    if(libselitem.isValid()){
        txtLibItemName->setText(libselitem.getProperty("name", "[unnamed]"), dontSendNotification);
        String itemtype = cbxLibList->getText();
        String maptype;
        if(itemtype == "Instruments"){
            maptype = libselitem.getProperty("map", "None").toString();
            if(maptype == "None"){
                libselitem.setProperty("map", "program", nullptr);
                maptype = "program";
            }
            lblMapPNote->setText("TP", dontSendNotification);
            optMapProgram->setEnabled(true);
            optMapDrum->setEnabled(true);
            if(maptype == "program"){
                optMapDrum->setToggleState(false, dontSendNotification);
                optMapProgram->setToggleState(true, dontSendNotification);
                txtMapPNum->setText(libselitem.getProperty("program", "0").toString(), sendNotification);
                txtMapPNote->setText(libselitem.getProperty("transpose", "0").toString(), sendNotification);
                txtMapDS1->setText("", dontSendNotification);
                txtMapDS2->setText("", dontSendNotification);
                txtMapDS3->setText("", dontSendNotification);
                txtMapPNum->setEnabled(true);
                txtMapPNote->setEnabled(true);
                lblMapPNote->setEnabled(true);
                txtMapDS1->setEnabled(false);
                txtMapDS2->setEnabled(false);
                txtMapDS3->setEnabled(false);
                lblMapSplits->setEnabled(false);
            }else{
                optMapProgram->setToggleState(false, dontSendNotification);
                optMapDrum->setToggleState(true, dontSendNotification);
                txtMapPNum->setText("", dontSendNotification);
                txtMapPNote->setText("", dontSendNotification);
                txtMapDS1->setText(libselitem.getProperty("drumsplit1", "38").toString(), sendNotification);
                txtMapDS2->setText(libselitem.getProperty("drumsplit2", "39").toString(), sendNotification);
                txtMapDS3->setText(libselitem.getProperty("drumsplit3", "40").toString(), sendNotification);
                txtMapPNum->setEnabled(false);
                txtMapPNote->setEnabled(false);
                lblMapPNote->setEnabled(false);
                txtMapDS1->setEnabled(true);
                txtMapDS2->setEnabled(true);
                txtMapDS3->setEnabled(true);
                lblMapSplits->setEnabled(true);
            }
            return;
        }else if(itemtype == "Drums"){
            maptype = libselitem.getProperty("map", "None").toString();
            if(maptype == "None"){
                libselitem.setProperty("map", "drum", nullptr);
                maptype = "drum";
            }
            lblMapPNote->setText("Note", dontSendNotification);
            optMapProgram->setEnabled(true);
            optMapDrum->setEnabled(true);
            txtMapDS2->setText("", dontSendNotification);
            txtMapDS3->setText("", dontSendNotification);
            txtMapDS2->setEnabled(false);
            txtMapDS3->setEnabled(false);
            lblMapSplits->setEnabled(false);
            if(maptype == "program"){
                optMapDrum->setToggleState(false, dontSendNotification);
                optMapProgram->setToggleState(true, dontSendNotification);
                txtMapPNum->setText(libselitem.getProperty("program", "0").toString(), sendNotification);
                txtMapPNote->setText(libselitem.getProperty("note", "60").toString(), sendNotification);
                txtMapDS1->setText("");
                txtMapPNum->setEnabled(true);
                txtMapPNote->setEnabled(true);
                lblMapPNote->setEnabled(true);
                txtMapDS1->setEnabled(false);
            }else{
                optMapProgram->setToggleState(false, dontSendNotification);
                optMapDrum->setToggleState(true, dontSendNotification);
                txtMapPNum->setText("", dontSendNotification);
                txtMapPNote->setText("", dontSendNotification);
                txtMapDS1->setText(libselitem.getProperty("drum", "38").toString(), sendNotification);
                txtMapPNum->setEnabled(false);
                txtMapPNote->setEnabled(false);
                lblMapPNote->setEnabled(false);
                txtMapDS1->setEnabled(true);
            }
            return;
        }
    }
    txtLibItemName->setText("", dontSendNotification);
    optMapProgram->setToggleState(false, dontSendNotification);
    optMapDrum->setToggleState(false, dontSendNotification);
    txtMapPNum->setText("", dontSendNotification);
    txtMapPNote->setText("", dontSendNotification);
    txtMapDS1->setText("", dontSendNotification);
    txtMapDS2->setText("", dontSendNotification);
    txtMapDS3->setText("", dontSendNotification);
    optMapProgram->setEnabled(false);
    optMapDrum->setEnabled(false);
    txtMapPNum->setEnabled(false);
    txtMapPNote->setEnabled(false);
    txtMapDS1->setEnabled(false);
    txtMapDS2->setEnabled(false);
    txtMapDS3->setEnabled(false);
    lblMapPNote->setEnabled(false);
    lblMapSplits->setEnabled(false);
}


void AudiobankPane::romDescLoaded(){
    abfstructsnode = seq64.romdesc.getOrCreateChildWithName("abfstructs", nullptr);
    cbxAlign->setText(abfstructsnode.getProperty("align", "16"));
    selstruct = ValueTree();
    selfield = ValueTree();
}

void AudiobankPane::gotABI(){
    abiaddr = -1;
    abaddr = -1;
    lsmLibSets->clear();
    lstLibSets->updateContent();
    ValueTree knownfilelist = seq64.romdesc.getChildWithName("knownfilelist");
    if(!knownfilelist.isValid()) return;
    ValueTree abinode = knownfilelist.getChildWithProperty("type", "Audiobank Index");
    if(!abinode.isValid()) return;
    int abiaddress = abinode.getProperty("address", -1);
    if(abiaddress < 0) return;
    ValueTree abnode = knownfilelist.getChildWithProperty("type", "Audiobank");
    if(!abnode.isValid()) return;
    int abaddress = abnode.getProperty("address", -1);
    if(abaddress < 0) return;
    uint16 bankcount;
    if((int)seq64.romdesc.getProperty("indextype", 1) == 2){
        bankcount = seq64.rom.readHalfWord(abiaddress);
    }else{
        bankcount = seq64.rom.readHalfWord(abiaddress+2);
    }
    if(bankcount > 1000 || bankcount <= 0) return;
    ValueTree temp;
    ValueTree abindexnode = seq64.romdesc.getChildWithName("audiobankidx");
    if(!abindexnode.isValid()) return;
    String bankname;
    for(int i=0; i<bankcount; i++){
        temp = abindexnode.getChildWithProperty("index", i);
        if(temp.isValid()){
            bankname = temp.getProperty("name", "Error");
        }else{
            bankname = "[unnamed]";
        }
        bankname = ROM::hex((uint8)i) + ": " + bankname;
        lsmLibSets->add(bankname);
    }
    lstLibSets->updateContent();
    abiaddr = abiaddress;
    abaddr = abaddress;
}

void AudiobankPane::bankLoaded(){
    if(seq64.bank == nullptr){
        bpath = ValueTree();
    }else{
        bpath = seq64.bank->d;
    }
    fillBItemsBox();
    fillBItemsControls(true);
}


void AudiobankPane::bOpen(int row){
    if(seq64.bank == nullptr) return;
    ValueTree newchild = seq64.bank->getNodeChild(bpath, row);
    if(!newchild.isValid()) return;
    if(newchild.getNumChildren() == 0) return;
    bpath = newchild;
    bselnode = ValueTree();
    fillBItemsBox();
}

void AudiobankPane::fillBListControls(){
    int nodeListFlags = 0;
    if(seq64.bank != nullptr){
        nodeListFlags = seq64.bank->getNodeListFlags(bpath, bselnode);
    }
    btnBItemAdd->setEnabled((nodeListFlags & BankFile::canAdd) != 0);
    btnBItemDupl->setEnabled((nodeListFlags & BankFile::canDupl) != 0);
    btnBItemDel->setEnabled((nodeListFlags & BankFile::canDel) != 0);
    btnBItemUp->setEnabled((nodeListFlags & BankFile::canMove) != 0);
    btnBItemDn->setEnabled((nodeListFlags & BankFile::canMove) != 0);
}

void AudiobankPane::fillBItemsBox(){
    fillBListControls();
    lsmBItems->clear();
    lstBItems->updateContent();
    bselnode = ValueTree();
    if(!bpath.isValid()) return;
    if(seq64.bank == nullptr) return;
    int count = bpath.getNumChildren();
    for(int i=0; i<count; i++){
        lsmBItems->add(seq64.bank->getNodeDesc(seq64.bank->getNodeChild(bpath, i)));
    }
    lstBItems->updateContent();
    lblBankPath->setText(seq64.bank->getNodePath(bpath), dontSendNotification);
}

void AudiobankPane::fillBItemsControls(bool setTxtBItemValue){
    fillBListControls();
    if(!bselnode.isValid() || seq64.bank == nullptr){
        txtBItemName->setText("", dontSendNotification);
        txtBItemName->setEnabled(false);
        lblBItemType->setText("", dontSendNotification);
        txtBItemValue->setText("", dontSendNotification);
        txtBItemValue->setEnabled(false);
        lblBItemValue->setText("Value:", dontSendNotification);
        lblBItemValueEquiv->setText("", dontSendNotification);
        return;
    }
    //Name
    txtBItemName->setText(seq64.bank->getNodeName(bselnode), dontSendNotification);
    txtBItemName->setEnabled(seq64.bank->isNodeNameEditable(bselnode));
    //Type
    lblBItemType->setText("Type: " + seq64.bank->getNodeType(bselnode), dontSendNotification);
    //Value and Equivalent Value
    BankFile::NodeValueInfo ni = seq64.bank->getNodeValueInfo(bselnode, chkBItemHex->getToggleState());
    lblBItemValue->setText(ni.valuereference ? "Index:" : "Value:", dontSendNotification);
    txtBItemValue->setEnabled(ni.valueeditable);
    txtBItemValue->setColour(TextEditor::backgroundColourId, LFWidgetColor());
    if(setTxtBItemValue) txtBItemValue->setText(ni.value, dontSendNotification);
    lblBItemValueEquiv->setText(ni.valueequiv, dontSendNotification);
}



//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="AudiobankPane" componentName=""
                 parentClasses="public Component, public TextEditor::Listener, public TextListModel::Listener"
                 constructorParams="SEQ64&amp; seq64_" variableInitialisers="seq64(seq64_)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="1078" initialHeight="713">
  <METHODS>
    <METHOD name="visibilityChanged()"/>
    <METHOD name="broughtToFront()"/>
    <METHOD name="focusGained (FocusChangeType cause)"/>
  </METHODS>
  <BACKGROUND backgroundColour="ff323e44">
    <RECT pos="17 240 2 24" fill="solid: ff000000" hasStroke="0"/>
    <RECT pos="209 240 2 44" fill="solid: ff000000" hasStroke="0"/>
  </BACKGROUND>
  <GROUPCOMPONENT name="new group" id="174f2978675eba2d" memberName="groupComponent2"
                  virtualName="" explicitFocusOrder="0" pos="0 344 760 344" title="Audiobank Library"/>
  <GROUPCOMPONENT name="new group" id="3ff16933e59a8658" memberName="groupComponent4"
                  virtualName="" explicitFocusOrder="0" pos="504 440 248 96" title="Add to Loaded Bank"/>
  <GROUPCOMPONENT name="new group" id="7edf637b2e2b1d8d" memberName="groupComponent3"
                  virtualName="" explicitFocusOrder="0" pos="448 0 576 344" title="Loaded Bank"/>
  <GROUPCOMPONENT name="new group" id="5c7a626fd18eb8e4" memberName="groupComponent"
                  virtualName="" explicitFocusOrder="0" pos="0 0 448 344" title="Audiobank File Data Structures"/>
  <COMBOBOX name="new combo box" id="d0dc297a3163ca7c" memberName="cbxEditStruct"
            virtualName="" explicitFocusOrder="0" pos="28 160 164 24" editable="0"
            layout="33" items="ABIndexEntry&#10;ABHeader&#10;ABBank&#10;ABDrumList&#10;ABSFXList&#10;ABInstrument&#10;ABDrum&#10;ABEnvelope&#10;ABSound&#10;ABSample&#10;ALADPCMBook&#10;ALADPCMPredictor&#10;ALADPCMLoop&#10;ALADPCMTail"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="6fa88c9721ab254d" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="200 192 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Data Type:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TOGGLEBUTTON name="new toggle button" id="cd5aa0958354bf46" memberName="optPointer"
                virtualName="" explicitFocusOrder="0" pos="8 216 72 24" buttonText="Ptr To:"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <COMBOBOX name="new combo box" id="dc9c4ee50f2e6d61" memberName="cbxDataType"
            virtualName="" explicitFocusOrder="0" pos="280 192 160 24" editable="0"
            layout="33" items="uint8&#10;uint16&#10;uint32&#10;int8&#10;int16&#10;int32&#10;float32&#10;ABSound&#10;ALADPCMPredictor&#10;ALADPCMTail"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="13ddb6d22233c898" memberName="cbxPtrTo"
            virtualName="" explicitFocusOrder="0" pos="24 240 168 24" editable="0"
            layout="33" items="ABHeader&#10;ABDrumList&#10;ABSFXList&#10;ABInstrument&#10;ABDrum&#10;ABEnvelope&#10;ABSample&#10;ALADPCMBook&#10;ALADPCMLoop"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="e3721257fc5becec" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="8 192 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Name:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="ad5984e4290af443" memberName="txtFieldName"
              virtualName="" explicitFocusOrder="0" pos="64 192 128 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TOGGLEBUTTON name="new toggle button" id="d407c06bb8ec1400" memberName="optArray"
                virtualName="" explicitFocusOrder="0" pos="200 216 80 24" buttonText="Array:"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="5845bcc7bddd2d61" memberName="optArrayFixed"
                virtualName="" explicitFocusOrder="0" pos="216 240 80 24" buttonText="Fixed:"
                connectedEdges="0" needsCallback="1" radioGroupId="1" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="82bd043ef914492b" memberName="optArrayVar"
                virtualName="" explicitFocusOrder="0" pos="216 264 80 24" buttonText="Variable:"
                connectedEdges="0" needsCallback="1" radioGroupId="1" state="0"/>
  <TEXTEDITOR name="new text editor" id="4584422efabec1d6" memberName="txtArrayLen"
              virtualName="" explicitFocusOrder="0" pos="296 240 64 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <COMBOBOX name="new combo box" id="2d1b4dd0ebb4dfc9" memberName="cbxArrayLenVar"
            virtualName="" explicitFocusOrder="0" pos="296 264 144 24" editable="0"
            layout="33" items="NUM_BANK&#10;NUM_INST&#10;NUM_DRUM&#10;NUM_SFX&#10;NUM_PRED&#10;HAS_TAIL"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="8da47d91aaa2bce" memberName="label4" virtualName=""
         explicitFocusOrder="0" pos="200 288 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Meaning:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="new combo box" id="5e05126adcbd71c6" memberName="cbxMeaning"
            virtualName="" explicitFocusOrder="0" pos="200 312 240 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="8270ae60fb0a1f08" memberName="lblStructBegin"
         virtualName="" explicitFocusOrder="0" pos="8 16 432 24" edTextCol="ff000000"
         edBkgCol="0" labelText="typedef struct {                        //Align all to:                    bytes"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
         italic="0" justification="33"/>
  <LABEL name="new label" id="339568e39a096dda" memberName="lblStructEnd"
         virtualName="" explicitFocusOrder="0" pos="8 160 20 24" edTextCol="ff000000"
         edBkgCol="0" labelText="}" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="afecf5bedea55560" memberName="label5" virtualName=""
         explicitFocusOrder="0" pos="8 288 104 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Default value:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="d0911874ebe28198" memberName="txtDefaultVal"
              virtualName="" explicitFocusOrder="0" pos="32 312 160 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTBUTTON name="new button" id="59e2f64e48e0d9e6" memberName="btnFieldAdd"
              virtualName="" explicitFocusOrder="0" pos="272 160 40 24" buttonText="Add"
              connectedEdges="2" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="b734cb1ef9ee9d71" memberName="btnFieldDel"
              virtualName="" explicitFocusOrder="0" pos="312 160 40 24" buttonText="Del"
              connectedEdges="1" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="c7142fad7c8a9b80" memberName="btnFieldUp"
              virtualName="" explicitFocusOrder="0" pos="360 160 40 24" buttonText="Up"
              connectedEdges="2" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="da1d462af9e5e099" memberName="btnFieldDn"
              virtualName="" explicitFocusOrder="0" pos="400 160 40 24" buttonText="Dn"
              connectedEdges="1" needsCallback="1" radioGroupId="0"/>
  <LABEL name="new label" id="39aac5bbbb71c644" memberName="label6" virtualName=""
         explicitFocusOrder="0" pos="360 240 48 24" edTextCol="ff000000"
         edBkgCol="0" labelText="(hex)" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="db442a9c0e2ef5b7" memberName="label7" virtualName=""
         explicitFocusOrder="0" pos="8 312 24 24" edTextCol="ff000000"
         edBkgCol="0" labelText="0x" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="ccce430366fad648" memberName="lblStructSemicolon"
         virtualName="" explicitFocusOrder="0" pos="192 160 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText=";   //Fields:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="bf0f024772c31c54" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="8 360 240 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Banks:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="new combo box" id="dc4b63bcb4d73721" memberName="cbxLibList"
            virtualName="" explicitFocusOrder="0" pos="256 360 240 24" editable="0"
            layout="33" items="Instruments&#10;Drums&#10;Sound Effects" textWhenNonSelected=""
            textWhenNoItems="(no choices)"/>
  <TEXTBUTTON name="new button" id="cc887378f0c65b1f" memberName="btnLibAdd"
              virtualName="" explicitFocusOrder="0" pos="512 504 232 24" buttonText="Import"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="new label" id="7ab82fcc4f2fe341" memberName="label8" virtualName=""
         explicitFocusOrder="0" pos="504 360 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Name:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="1107c1605bcdd6fe" memberName="txtLibItemName"
              virtualName="" explicitFocusOrder="0" pos="560 360 182 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TOGGLEBUTTON name="new toggle button" id="35162d8ea694d708" memberName="chkLibMerge"
                virtualName="" explicitFocusOrder="0" pos="512 456 64 24" buttonText="Merge"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="1"/>
  <TEXTBUTTON name="new button" id="95b805434c056546" memberName="btnBItemAdd"
              virtualName="" explicitFocusOrder="0" pos="744 48 48 24" buttonText="Add"
              connectedEdges="8" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="b4f552bc87690c64" memberName="btnBItemDupl"
              virtualName="" explicitFocusOrder="0" pos="744 72 48 24" buttonText="Dupl"
              connectedEdges="12" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="5437999e821d0f9" memberName="btnBItemDel"
              virtualName="" explicitFocusOrder="0" pos="744 96 48 24" buttonText="Del"
              connectedEdges="4" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="53c617d9b6236e17" memberName="btnBItemUp"
              virtualName="" explicitFocusOrder="0" pos="744 136 48 24" buttonText="Up"
              connectedEdges="8" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="7aa4ba34a22a9127" memberName="btnBItemDn"
              virtualName="" explicitFocusOrder="0" pos="744 160 48 24" buttonText="Dn"
              connectedEdges="4" needsCallback="1" radioGroupId="0"/>
  <LABEL name="new label" id="fedcaca14cadb7e6" memberName="label12" virtualName=""
         explicitFocusOrder="0" pos="800 48 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Name:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="789b2d42c36319de" memberName="txtBItemName"
              virtualName="" explicitFocusOrder="0" pos="856 48 160 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <COMBOBOX name="new combo box" id="624a2f6acff61c45" memberName="cbxAlign"
            virtualName="" explicitFocusOrder="0" pos="272 16 56 24" editable="0"
            layout="33" items="4&#10;8&#10;16" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <TOGGLEBUTTON name="new toggle button" id="904c1638347d6b92" memberName="optMapProgram"
                virtualName="" explicitFocusOrder="0" pos="504 384 80 24" buttonText="Program"
                connectedEdges="0" needsCallback="1" radioGroupId="2" state="0"/>
  <TEXTEDITOR name="new text editor" id="227ca9d9d19fce14" memberName="txtMapPNum"
              virtualName="" explicitFocusOrder="0" pos="584 384 40 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="854c1c31c216fbd4" memberName="lblMapPNote"
         virtualName="" explicitFocusOrder="0" pos="624 384 40 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Note" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="1b089dc42c9d6221" memberName="txtMapPNote"
              virtualName="" explicitFocusOrder="0" pos="664 384 40 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TOGGLEBUTTON name="new toggle button" id="7148b75cbf658edc" memberName="optMapDrum"
                virtualName="" explicitFocusOrder="0" pos="504 408 64 24" buttonText="Drum"
                connectedEdges="0" needsCallback="1" radioGroupId="2" state="0"/>
  <TEXTEDITOR name="new text editor" id="aa19384ec690042a" memberName="txtMapDS1"
              virtualName="" explicitFocusOrder="0" pos="584 408 40 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="new text editor" id="ba5cd49f38ff9d0a" memberName="txtMapDS2"
              virtualName="" explicitFocusOrder="0" pos="624 408 40 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="new text editor" id="2428146ebfbcaaae" memberName="txtMapDS3"
              virtualName="" explicitFocusOrder="0" pos="664 408 40 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="5cfefa37bdad5f80" memberName="lblMapSplits"
         virtualName="" explicitFocusOrder="0" pos="704 408 40 24" edTextCol="ff000000"
         edBkgCol="0" labelText="splits" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="new button" id="79caca2ca761ed63" memberName="btnBUp" virtualName=""
              explicitFocusOrder="0" pos="456 16 40 24" buttonText="Up" connectedEdges="2"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="5fca6cb4978a26b3" memberName="btnBOpen"
              virtualName="" explicitFocusOrder="0" pos="744 312 48 24" buttonText="Open"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="new label" id="526cc3ce776cdcc3" memberName="lblBankPath"
         virtualName="" explicitFocusOrder="0" pos="496 16 520 24" edTextCol="ff000000"
         edBkgCol="0" labelText="/" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="2a46dd8fc6577eaa" memberName="lblBItemType"
         virtualName="" explicitFocusOrder="0" pos="800 72 216 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Type:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="5ea115b1228245fe" memberName="lblBItemValue"
         virtualName="" explicitFocusOrder="0" pos="800 96 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Value:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="7218c1b05111775d" memberName="txtBItemValue"
              virtualName="" explicitFocusOrder="0" pos="856 96 88 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="e1fb93f0e1d42150" memberName="lblBItemValueEquiv"
         virtualName="" explicitFocusOrder="0" pos="856 120 160 24" edTextCol="ff000000"
         edBkgCol="0" labelText="()" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TOGGLEBUTTON name="new toggle button" id="c01f6d0157eac10c" memberName="chkBItemHex"
                virtualName="" explicitFocusOrder="0" pos="952 96 56 24" buttonText="Hex"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TEXTBUTTON name="new button" id="983d3e97807e0cdf" memberName="btnSaveXML"
              virtualName="" explicitFocusOrder="0" pos="808 176 104 24" buttonText="Save XML"
              connectedEdges="2" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="953560fe7e6d707e" memberName="btnLoadXML"
              virtualName="" explicitFocusOrder="0" pos="912 176 104 24" buttonText="Load XML"
              connectedEdges="1" needsCallback="1" radioGroupId="0"/>
  <TOGGLEBUTTON name="new toggle button" id="23b75b22565a0123" memberName="chkLibFixAddr"
                virtualName="" explicitFocusOrder="0" pos="512 480 232 24" buttonText="Convert Sample Addr for Table"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

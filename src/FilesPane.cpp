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
 * FilesPane.cpp
 * GUI component for N64 ROM internal files screen
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

#include "MainComponent.h"
#include "BankFile.h"
#include "SeqFile.h"
#include "IEEditor.h"
#include <cstring>
//[/Headers]

#include "FilesPane.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
FilesPane::FilesPane (SEQ64& seq64_)
    : seq64(seq64_),
      audiobank(seq64.rom, seq64.romdesc, "Audiobank"),
      audioseq(seq64.rom, seq64.romdesc, "Audioseq"),
      audiotable(seq64.rom, seq64.romdesc, "Audiotable"),
      sbm(seq64.rom, seq64.romdesc, audioseq)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    grpSeqBanks.reset (new GroupComponent ("new group",
                                           TRANS("Sequence banks:")));
    addAndMakeVisible (grpSeqBanks.get());

    grpSeqBanks->setBounds (496, 472, 336, 136);

    grpIndex.reset (new GroupComponent ("new group",
                                        TRANS("Index")));
    addAndMakeVisible (grpIndex.get());

    grpIndex->setBounds (0, 144, 496, 568);

    grpUtilitiesEntry.reset (new GroupComponent ("new group",
                                                 TRANS("Entry")));
    addAndMakeVisible (grpUtilitiesEntry.get());

    grpUtilitiesEntry->setBounds (8, 512, 480, 80);

    groupComponent.reset (new GroupComponent ("ROM Properties",
                                              TRANS("ROM Properties")));
    addAndMakeVisible (groupComponent.get());

    groupComponent->setBounds (496, 0, 336, 120);

    grpUtilitiesContents.reset (new GroupComponent ("new group",
                                                    TRANS("Contents")));
    addAndMakeVisible (grpUtilitiesContents.get());

    grpUtilitiesContents->setBounds (8, 592, 480, 112);

    grpMFT.reset (new GroupComponent ("new group",
                                      TRANS("Master File Table (dmadata)")));
    addAndMakeVisible (grpMFT.get());

    grpMFT->setBounds (496, 120, 336, 352);

    label.reset (new Label ("new label",
                            TRANS("MFT Address:")));
    addAndMakeVisible (label.get());
    label->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label->setBounds (504, 16, 96, 24);

    txtFTAddr.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (txtFTAddr.get());
    txtFTAddr->setMultiLine (false);
    txtFTAddr->setReturnKeyStartsNewLine (false);
    txtFTAddr->setReadOnly (false);
    txtFTAddr->setScrollbarsShown (true);
    txtFTAddr->setCaretVisible (true);
    txtFTAddr->setPopupMenuEnabled (true);
    txtFTAddr->setText (String());

    txtFTAddr->setBounds (600, 16, 80, 24);

    label2.reset (new Label ("new label",
                             TRANS("Name:")));
    addAndMakeVisible (label2.get());
    label2->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label2->setBounds (504, 416, 56, 24);

    txtFileName.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (txtFileName.get());
    txtFileName->setMultiLine (false);
    txtFileName->setReturnKeyStartsNewLine (false);
    txtFileName->setReadOnly (false);
    txtFileName->setScrollbarsShown (true);
    txtFileName->setCaretVisible (true);
    txtFileName->setPopupMenuEnabled (true);
    txtFileName->setText (String());

    txtFileName->setBounds (560, 416, 264, 24);

    label3.reset (new Label ("new label",
                             TRANS("Type:")));
    addAndMakeVisible (label3.get());
    label3->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label3->setJustificationType (Justification::centredLeft);
    label3->setEditable (false, false, false);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label3->setBounds (504, 440, 56, 24);

    cbxFileType.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (cbxFileType.get());
    cbxFileType->setEditableText (false);
    cbxFileType->setJustificationType (Justification::centredLeft);
    cbxFileType->setTextWhenNothingSelected (String());
    cbxFileType->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    cbxFileType->addItem (TRANS("Unknown"), 1);
    cbxFileType->addItem (TRANS("ROM Header"), 2);
    cbxFileType->addItem (TRANS("Boot Code"), 3);
    cbxFileType->addItem (TRANS("Master File Table"), 4);
    cbxFileType->addItem (TRANS("Audiobank"), 5);
    cbxFileType->addItem (TRANS("Audioseq"), 6);
    cbxFileType->addItem (TRANS("Audiotable"), 7);
    cbxFileType->addItem (TRANS("Code"), 8);
    cbxFileType->addItem (TRANS("Texture"), 9);
    cbxFileType->addItem (TRANS("Shared Assets"), 10);
    cbxFileType->addItem (TRANS("Text Data"), 11);
    cbxFileType->addItem (TRANS("Actor"), 12);
    cbxFileType->addItem (TRANS("Object"), 13);
    cbxFileType->addItem (TRANS("Scene"), 14);
    cbxFileType->addItem (TRANS("Room"), 15);
    cbxFileType->addItem (TRANS("Other"), 16);
    cbxFileType->addListener (this);

    cbxFileType->setBounds (560, 440, 264, 24);

    label4.reset (new Label ("new label",
                             TRANS("[Address information]")));
    addAndMakeVisible (label4.get());
    label4->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label4->setJustificationType (Justification::centredLeft);
    label4->setEditable (false, false, false);
    label4->setColour (TextEditor::textColourId, Colours::black);
    label4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label4->setBounds (504, 392, 320, 24);

    grpKnownFiles.reset (new GroupComponent ("new group",
                                             TRANS("Known Files")));
    addAndMakeVisible (grpKnownFiles.get());

    grpKnownFiles->setBounds (0, 0, 496, 144);

    btnKFileAdd.reset (new TextButton ("new button"));
    addAndMakeVisible (btnKFileAdd.get());
    btnKFileAdd->setButtonText (TRANS("Add"));
    btnKFileAdd->setConnectedEdges (Button::ConnectedOnRight);
    btnKFileAdd->addListener (this);

    btnKFileAdd->setBounds (248, 112, 120, 24);

    btnKFileDel.reset (new TextButton ("new button"));
    addAndMakeVisible (btnKFileDel.get());
    btnKFileDel->setButtonText (TRANS("Delete"));
    btnKFileDel->setConnectedEdges (Button::ConnectedOnLeft);
    btnKFileDel->addListener (this);

    btnKFileDel->setBounds (368, 112, 120, 24);

    label5.reset (new Label ("new label",
                             TRANS("Type:")));
    addAndMakeVisible (label5.get());
    label5->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label5->setJustificationType (Justification::centredLeft);
    label5->setEditable (false, false, false);
    label5->setColour (TextEditor::textColourId, Colours::black);
    label5->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label5->setBounds (248, 16, 47, 24);

    cbxKFileType.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (cbxKFileType.get());
    cbxKFileType->setEditableText (false);
    cbxKFileType->setJustificationType (Justification::centredLeft);
    cbxKFileType->setTextWhenNothingSelected (String());
    cbxKFileType->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    cbxKFileType->addItem (TRANS("Unsupported"), 1);
    cbxKFileType->addItem (TRANS("Audiobank"), 2);
    cbxKFileType->addItem (TRANS("Audioseq"), 3);
    cbxKFileType->addItem (TRANS("Audiotable"), 4);
    cbxKFileType->addItem (TRANS("Audiobank Index"), 5);
    cbxKFileType->addItem (TRANS("Audioseq Index"), 6);
    cbxKFileType->addItem (TRANS("Audiotable Index"), 7);
    cbxKFileType->addItem (TRANS("Sequence Banks Map"), 8);
    cbxKFileType->addListener (this);

    cbxKFileType->setBounds (296, 16, 192, 24);

    label6.reset (new Label ("new label",
                             TRANS("Address:")));
    addAndMakeVisible (label6.get());
    label6->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label6->setJustificationType (Justification::centredLeft);
    label6->setEditable (false, false, false);
    label6->setColour (TextEditor::textColourId, Colours::black);
    label6->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label6->setBounds (248, 40, 72, 24);

    txtKFileAddr.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (txtKFileAddr.get());
    txtKFileAddr->setMultiLine (false);
    txtKFileAddr->setReturnKeyStartsNewLine (false);
    txtKFileAddr->setReadOnly (false);
    txtKFileAddr->setScrollbarsShown (true);
    txtKFileAddr->setCaretVisible (true);
    txtKFileAddr->setPopupMenuEnabled (true);
    txtKFileAddr->setText (String());

    txtKFileAddr->setBounds (320, 40, 80, 24);

    label7.reset (new Label ("new label",
                             TRANS("Length:")));
    addAndMakeVisible (label7.get());
    label7->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label7->setJustificationType (Justification::centredLeft);
    label7->setEditable (false, false, false);
    label7->setColour (TextEditor::textColourId, Colours::black);
    label7->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label7->setBounds (248, 64, 72, 24);

    txtKFileLength.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (txtKFileLength.get());
    txtKFileLength->setMultiLine (false);
    txtKFileLength->setReturnKeyStartsNewLine (false);
    txtKFileLength->setReadOnly (false);
    txtKFileLength->setScrollbarsShown (true);
    txtKFileLength->setCaretVisible (true);
    txtKFileLength->setPopupMenuEnabled (true);
    txtKFileLength->setText (String());

    txtKFileLength->setBounds (320, 64, 80, 24);

    lblIndexProps.reset (new Label ("new label",
                                    TRANS("[Index length, address, etc.]")));
    addAndMakeVisible (lblIndexProps.get());
    lblIndexProps->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblIndexProps->setJustificationType (Justification::centredLeft);
    lblIndexProps->setEditable (false, false, false);
    lblIndexProps->setColour (TextEditor::textColourId, Colours::black);
    lblIndexProps->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblIndexProps->setBounds (8, 160, 480, 24);

    label11.reset (new Label ("new label",
                              TRANS("Name:")));
    addAndMakeVisible (label11.get());
    label11->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label11->setJustificationType (Justification::centredLeft);
    label11->setEditable (false, false, false);
    label11->setColour (TextEditor::textColourId, Colours::black);
    label11->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label11->setBounds (16, 528, 56, 24);

    txtIEntryName.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (txtIEntryName.get());
    txtIEntryName->setMultiLine (false);
    txtIEntryName->setReturnKeyStartsNewLine (false);
    txtIEntryName->setReadOnly (false);
    txtIEntryName->setScrollbarsShown (true);
    txtIEntryName->setCaretVisible (true);
    txtIEntryName->setPopupMenuEnabled (true);
    txtIEntryName->setText (String());

    txtIEntryName->setBounds (72, 528, 408, 24);

    lblIEntryData.reset (new Label ("new label",
                                    TRANS("[Entry data]")));
    addAndMakeVisible (lblIEntryData.get());
    lblIEntryData->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblIEntryData->setJustificationType (Justification::centredLeft);
    lblIEntryData->setEditable (false, false, false);
    lblIEntryData->setColour (TextEditor::textColourId, Colours::black);
    lblIEntryData->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblIEntryData->setBounds (8, 488, 480, 24);

    btnLoadObject.reset (new TextButton ("new button"));
    addAndMakeVisible (btnLoadObject.get());
    btnLoadObject->setButtonText (TRANS("Load Object"));
    btnLoadObject->setConnectedEdges (Button::ConnectedOnRight);
    btnLoadObject->addListener (this);

    btnLoadObject->setBounds (16, 616, 232, 24);

    btnSaveObject.reset (new TextButton ("new button"));
    addAndMakeVisible (btnSaveObject.get());
    btnSaveObject->setButtonText (TRANS("Save Object"));
    btnSaveObject->setConnectedEdges (Button::ConnectedOnLeft);
    btnSaveObject->addListener (this);

    btnSaveObject->setBounds (248, 616, 232, 24);

    optIndexType1.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (optIndexType1.get());
    optIndexType1->setButtonText (TRANS("4/8 (SM64, etc.)"));
    optIndexType1->setRadioGroupId (1);
    optIndexType1->addListener (this);
    optIndexType1->setToggleState (true, dontSendNotification);

    optIndexType1->setBounds (528, 64, 128, 24);

    optIndexType2.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (optIndexType2.get());
    optIndexType2->setButtonText (TRANS("16/16 (Zelda, etc.)"));
    optIndexType2->setRadioGroupId (1);
    optIndexType2->addListener (this);

    optIndexType2->setBounds (528, 88, 144, 24);

    label10.reset (new Label ("new label",
                              TRANS("Bank:")));
    addAndMakeVisible (label10.get());
    label10->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label10->setJustificationType (Justification::centredRight);
    label10->setEditable (false, false, false);
    label10->setColour (TextEditor::textColourId, Colours::black);
    label10->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label10->setBounds (504, 576, 56, 24);

    cbxSeqBank.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (cbxSeqBank.get());
    cbxSeqBank->setEditableText (false);
    cbxSeqBank->setJustificationType (Justification::centredLeft);
    cbxSeqBank->setTextWhenNothingSelected (String());
    cbxSeqBank->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    cbxSeqBank->addListener (this);

    cbxSeqBank->setBounds (560, 576, 264, 24);

    btnEditIE.reset (new TextButton ("new button"));
    addAndMakeVisible (btnEditIE.get());
    btnEditIE->setButtonText (TRANS("Edit Entry (Metadata)"));
    btnEditIE->addListener (this);

    btnEditIE->setBounds (312, 560, 166, 24);

    btnCompact.reset (new TextButton ("new button"));
    addAndMakeVisible (btnCompact.get());
    btnCompact->setButtonText (TRANS("Compact"));
    btnCompact->addListener (this);

    btnCompact->setBounds (400, 672, 80, 24);

    btnMakeRoom.reset (new TextButton ("new button"));
    addAndMakeVisible (btnMakeRoom.get());
    btnMakeRoom->setButtonText (TRANS("Make Room"));
    btnMakeRoom->setConnectedEdges (Button::ConnectedOnLeft);
    btnMakeRoom->addListener (this);

    btnMakeRoom->setBounds (304, 648, 88, 24);

    label8.reset (new Label ("new label",
                             TRANS("Make room for 0x")));
    addAndMakeVisible (label8.get());
    label8->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label8->setJustificationType (Justification::centredLeft);
    label8->setEditable (false, false, false);
    label8->setColour (TextEditor::textColourId, Colours::black);
    label8->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label8->setBounds (144, 648, 120, 24);

    txtMakeRoom.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (txtMakeRoom.get());
    txtMakeRoom->setMultiLine (false);
    txtMakeRoom->setReturnKeyStartsNewLine (false);
    txtMakeRoom->setReadOnly (false);
    txtMakeRoom->setScrollbarsShown (true);
    txtMakeRoom->setCaretVisible (true);
    txtMakeRoom->setPopupMenuEnabled (true);
    txtMakeRoom->setText (TRANS("1000"));

    txtMakeRoom->setBounds (264, 648, 40, 24);

    btnContentsCreate.reset (new TextButton ("new button"));
    addAndMakeVisible (btnContentsCreate.get());
    btnContentsCreate->setButtonText (TRANS("Create"));
    btnContentsCreate->setConnectedEdges (Button::ConnectedOnBottom);
    btnContentsCreate->addListener (this);

    btnContentsCreate->setBounds (16, 648, 128, 24);

    btnContentsDestroy.reset (new TextButton ("new button"));
    addAndMakeVisible (btnContentsDestroy.get());
    btnContentsDestroy->setButtonText (TRANS("Destroy/Pointerize"));
    btnContentsDestroy->setConnectedEdges (Button::ConnectedOnTop);
    btnContentsDestroy->addListener (this);

    btnContentsDestroy->setBounds (16, 672, 128, 24);

    label9.reset (new Label ("new label",
                             TRANS("Pointer to entry: 0x")));
    addAndMakeVisible (label9.get());
    label9->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label9->setJustificationType (Justification::centredLeft);
    label9->setEditable (false, false, false);
    label9->setColour (TextEditor::textColourId, Colours::black);
    label9->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label9->setBounds (144, 672, 128, 24);

    txtEntryPointer.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (txtEntryPointer.get());
    txtEntryPointer->setMultiLine (false);
    txtEntryPointer->setReturnKeyStartsNewLine (false);
    txtEntryPointer->setReadOnly (false);
    txtEntryPointer->setScrollbarsShown (true);
    txtEntryPointer->setCaretVisible (true);
    txtEntryPointer->setPopupMenuEnabled (true);
    txtEntryPointer->setText (TRANS("00"));

    txtEntryPointer->setBounds (272, 672, 32, 24);

    btnEntryInsert.reset (new TextButton ("new button"));
    addAndMakeVisible (btnEntryInsert.get());
    btnEntryInsert->setButtonText (TRANS("Insert"));
    btnEntryInsert->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
    btnEntryInsert->addListener (this);

    btnEntryInsert->setBounds (96, 560, 80, 24);

    btnEntryAdd.reset (new TextButton ("new button"));
    addAndMakeVisible (btnEntryAdd.get());
    btnEntryAdd->setButtonText (TRANS("Add"));
    btnEntryAdd->setConnectedEdges (Button::ConnectedOnRight);
    btnEntryAdd->addListener (this);

    btnEntryAdd->setBounds (16, 560, 80, 24);

    btnEntryDelete.reset (new TextButton ("new button"));
    addAndMakeVisible (btnEntryDelete.get());
    btnEntryDelete->setButtonText (TRANS("Delete"));
    btnEntryDelete->setConnectedEdges (Button::ConnectedOnLeft);
    btnEntryDelete->addListener (this);

    btnEntryDelete->setBounds (176, 560, 80, 24);

    label12.reset (new Label ("new label",
                              TRANS("Index format (hdr/entry bytes):")));
    addAndMakeVisible (label12.get());
    label12->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label12->setJustificationType (Justification::centredLeft);
    label12->setEditable (false, false, false);
    label12->setColour (TextEditor::textColourId, Colours::black);
    label12->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label12->setBounds (504, 40, 208, 24);

    btnSBMAdd.reset (new TextButton ("new button"));
    addAndMakeVisible (btnSBMAdd.get());
    btnSBMAdd->setButtonText (TRANS("Add"));
    btnSBMAdd->setConnectedEdges (Button::ConnectedOnBottom);
    btnSBMAdd->addListener (this);

    btnSBMAdd->setBounds (504, 496, 48, 24);

    btnSBMDelete.reset (new TextButton ("new button"));
    addAndMakeVisible (btnSBMDelete.get());
    btnSBMDelete->setButtonText (TRANS("Del"));
    btnSBMDelete->setConnectedEdges (Button::ConnectedOnTop);
    btnSBMDelete->addListener (this);

    btnSBMDelete->setBounds (504, 544, 48, 24);

    label13.reset (new Label ("new label",
                              TRANS("Row")));
    addAndMakeVisible (label13.get());
    label13->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label13->setJustificationType (Justification::centred);
    label13->setEditable (false, false, false);
    label13->setColour (TextEditor::textColourId, Colours::black);
    label13->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label13->setBounds (504, 520, 48, 24);


    //[UserPreSize]
    lsmFileTable.reset(new TextListModel());
    lsmFileTable->setListener(this);

    lstFileTable.reset(new ListBox("FileTable", lsmFileTable.get()));
    addAndMakeVisible(lstFileTable.get());
    lstFileTable->setMultipleSelectionEnabled(false);
    lstFileTable->setRowHeight(16);
    lstFileTable->setOutlineThickness(1);
    lstFileTable->setColour(ListBox::outlineColourId, Colours::lightgrey);

    lsmKFiles.reset(new TextListModel());
    lsmKFiles->setListener(this);

    lstKFiles.reset(new ListBox("KFiles", lsmKFiles.get()));
    addAndMakeVisible(lstKFiles.get());
    lstKFiles->setMultipleSelectionEnabled(false);
    lstKFiles->setRowHeight(16);
    lstKFiles->setOutlineThickness(1);
    lstKFiles->setColour(ListBox::outlineColourId, Colours::lightgrey);

    lsmIndex.reset(new TextListModel());
    lsmIndex->setListener(this);

    lstIndex.reset(new ListBox("Index", lsmIndex.get()));
    addAndMakeVisible(lstIndex.get());
    lstIndex->setMultipleSelectionEnabled(false);
    lstIndex->setRowHeight(16);
    lstIndex->setOutlineThickness(1);
    lstIndex->setColour(ListBox::outlineColourId, Colours::lightgrey);

    lsmSeqBanks.reset(new TextListModel());
    lsmSeqBanks->setListener(this);

    lstSeqBanks.reset(new ListBox("SeqBanks", lsmSeqBanks.get()));
    addAndMakeVisible(lstSeqBanks.get());
    lstSeqBanks->setMultipleSelectionEnabled(false);
    lstSeqBanks->setRowHeight(16);
    lstSeqBanks->setOutlineThickness(1);
    lstSeqBanks->setColour(ListBox::outlineColourId, Colours::lightgrey);

    txtFTAddr->addListener(this);
    txtFileName->addListener(this);
    txtKFileAddr->addListener(this);
    txtKFileLength->addListener(this);
    txtIEntryName->addListener(this);
    txtEntryPointer->addListener(this);

    //[/UserPreSize]

    setSize (1078, 713);


    //[Constructor] You can add your own custom stuff here..
	reloadFiles();

	selifile = nullptr;
	selkfile = ValueTree();
	ientryidx = -1;

    romDescLoaded();
    //[/Constructor]
}

FilesPane::~FilesPane()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    grpSeqBanks = nullptr;
    grpIndex = nullptr;
    grpUtilitiesEntry = nullptr;
    groupComponent = nullptr;
    grpUtilitiesContents = nullptr;
    grpMFT = nullptr;
    label = nullptr;
    txtFTAddr = nullptr;
    label2 = nullptr;
    txtFileName = nullptr;
    label3 = nullptr;
    cbxFileType = nullptr;
    label4 = nullptr;
    grpKnownFiles = nullptr;
    btnKFileAdd = nullptr;
    btnKFileDel = nullptr;
    label5 = nullptr;
    cbxKFileType = nullptr;
    label6 = nullptr;
    txtKFileAddr = nullptr;
    label7 = nullptr;
    txtKFileLength = nullptr;
    lblIndexProps = nullptr;
    label11 = nullptr;
    txtIEntryName = nullptr;
    lblIEntryData = nullptr;
    btnLoadObject = nullptr;
    btnSaveObject = nullptr;
    optIndexType1 = nullptr;
    optIndexType2 = nullptr;
    label10 = nullptr;
    cbxSeqBank = nullptr;
    btnEditIE = nullptr;
    btnCompact = nullptr;
    btnMakeRoom = nullptr;
    label8 = nullptr;
    txtMakeRoom = nullptr;
    btnContentsCreate = nullptr;
    btnContentsDestroy = nullptr;
    label9 = nullptr;
    txtEntryPointer = nullptr;
    btnEntryInsert = nullptr;
    btnEntryAdd = nullptr;
    btnEntryDelete = nullptr;
    label12 = nullptr;
    btnSBMAdd = nullptr;
    btnSBMDelete = nullptr;
    label13 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void FilesPane::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void FilesPane::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    lstFileTable->setBounds (504, 136, 320, 256);
    lstKFiles->setBounds (8, 16, 232, 120);
    lstIndex->setBounds (8, 184, 480, 304);
    lstSeqBanks->setBounds (560, 488, 264, 88);
    //[/UserResized]
}

void FilesPane::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == cbxFileType.get())
    {
        //[UserComboBoxCode_cbxFileType] -- add your combo box handling code here..
        int findex = lstFileTable->getLastRowSelected();
        if(findex < 0) return;
		uint32 ftaddr = (int)seq64.romdesc.getProperty("ftaddr", 0);
        if(ftaddr == 0) return;
        String type = cbxFileType->getText();
        //See if we are removing a known file
        ValueTree kfile = kfilelistnode.getChildWithProperty("ftindex", findex);
        if(kfile.isValid()){
            kfilelistnode.removeChild(kfile, nullptr);
			reloadFiles();
            fillKFiles();
        }
        if(isKnownFileType(type)){
            //See if we already know about this type of file
            kfile = kfilelistnode.getChildWithProperty(Identifier("type"), type);
            if(kfile.isValid()){
                SEQ64::say(type + " file already exists!");
                cbxFileType->setText("Unknown", dontSendNotification);
                return;
            }
            //Set up this known file
            kfile = ValueTree(Identifier("knownfile"));
            kfile.setProperty(Identifier("type"), type, nullptr);
            kfile.setProperty(Identifier("from_ft"), true, nullptr);
            kfile.setProperty(Identifier("ftindex"), findex, nullptr);
            uint32 a = ftaddr + 0x10*findex;
            uint32 file_addr = (int)seq64.rom.readWord(a);
            kfile.setProperty(Identifier("address"), (int)file_addr, nullptr);
            kfile.setProperty(Identifier("length"), (int)(seq64.rom.readWord(a+4) - seq64.rom.readWord(a)), nullptr);
            kfilelistnode.addChild(kfile, kfilelistnode.getNumChildren(), nullptr);
			reloadFiles();
            fillKFiles();
            lstKFiles->selectRow(lsmKFiles->getNumRows() - 1);
        }
        ValueTree file = filelistnode.getChildWithProperty(Identifier("index"), findex);
        if(!file.isValid()){
            file = ValueTree(Identifier("file"));
            file.setProperty(Identifier("index"), findex, nullptr);
            filelistnode.addChild(file, filelistnode.getNumChildren(), nullptr);
        }
        file.setProperty(Identifier("type"), type, nullptr);
        //[/UserComboBoxCode_cbxFileType]
    }
    else if (comboBoxThatHasChanged == cbxKFileType.get())
    {
        //[UserComboBoxCode_cbxKFileType] -- add your combo box handling code here..
        if(!selkfile.isValid()) return;
        if((bool)selkfile.getProperty("from_ft", false)){
            //Prevent you from changing it
            fillKFileParams();
            return;
        }
        String type = cbxKFileType->getText();
        //Check for existing file of this type
        if(type != "Unsupported"){
            ValueTree kfile = kfilelistnode.getChildWithProperty(Identifier("type"), type);
            if(kfile.isValid() && kfile != selkfile){
                SEQ64::say(type + " file already exists!");
                cbxKFileType->setText("Unsupported", dontSendNotification);
                type = "Unsupported";
            }
        }
        //Remove old index address, insert new
        selkfile.setProperty("type", type, nullptr);
		reloadFiles();
        //Refresh display
        int idx = lstKFiles->getLastRowSelected();
        lsmKFiles->set(idx, cbxKFileType->getText());
        lstKFiles->repaintRow(idx);
        //[/UserComboBoxCode_cbxKFileType]
    }
    else if (comboBoxThatHasChanged == cbxSeqBank.get())
    {
        //[UserComboBoxCode_cbxSeqBank] -- add your combo box handling code here..
        if(selifile == nullptr) return;
        if(selifile->getIName() != "Audioseq Index") return;
        if(ientryidx < 0) return;
        int idx = cbxSeqBank->getSelectedItemIndex();
        int row = lstSeqBanks->getLastRowSelected();
        if(idx < 0 || row < 0) return;
        if(!sbm.setSeqBank(ientryidx, row, idx)){
			SEQ64::say("Error setting bank!");
		}
        lsmSeqBanks->set(row, cbxSeqBank->getText());
        lstSeqBanks->repaintRow(row);
        //[/UserComboBoxCode_cbxSeqBank]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void FilesPane::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == btnKFileAdd.get())
    {
        //[UserButtonCode_btnKFileAdd] -- add your button handler code here..
        ValueTree kfile(Identifier("knownfile"));
        kfile.setProperty(Identifier("type"), "Unsupported", nullptr);
        kfile.setProperty(Identifier("from_ft"), false, nullptr);
        kfile.setProperty(Identifier("address"), 0, nullptr);
        kfile.setProperty(Identifier("length"), 0, nullptr);
        kfilelistnode.addChild(kfile, kfilelistnode.getNumChildren(), nullptr);
        fillKFiles();
        lstKFiles->selectRow(lsmKFiles->getNumRows() - 1);
        //[/UserButtonCode_btnKFileAdd]
    }
    else if (buttonThatWasClicked == btnKFileDel.get())
    {
        //[UserButtonCode_btnKFileDel] -- add your button handler code here..
        if(!selkfile.isValid()) return;
        if((bool)selkfile.getProperty("from_ft", false)){
            SEQ64::say("From file table, can't delete!");
            return;
        }
        //Remove kfile
        kfilelistnode.removeChild(selkfile, nullptr);
		reloadFiles();
        selkfile = ValueTree();
        fillKFiles();
        lstKFiles->selectRow(-1);
        //[/UserButtonCode_btnKFileDel]
    }
    else if (buttonThatWasClicked == btnLoadObject.get())
    {
        //[UserButtonCode_btnLoadObject] -- add your button handler code here..
		if(selifile == nullptr) return;
        if(ientryidx < 0) return;
        if(selifile->getIName() == "Audiobank Index"){
            if(&*seq64.bank != nullptr){
                if(!NativeMessageBox::showOkCancelBox(AlertWindow::WarningIcon,
                        "Overwrite?", "A bank is already loaded, overwrite it?", nullptr, nullptr)) return;
            }
            seq64.bank.reset(new BankFile(seq64.romdesc));
            int ret = seq64.bank->load(seq64.rom, ientryidx);
            if(ret < 0){
                NativeMessageBox::showMessageBoxAsync(AlertWindow::WarningIcon, "Oh no",
                    "Error(s) encountered when loading bank, check the terminal output for details.");
            }
            seq64.maincomponent->onBankLoaded();
        }else if(selifile->getIName() == "Audioseq Index"){
            if(&*seq64.seq != nullptr){
                if(!NativeMessageBox::showOkCancelBox(AlertWindow::WarningIcon,
                        "Overwrite?", "A sequence is already loaded, overwrite it?", nullptr, nullptr)) return;
            }
            seq64.seq.reset(new SeqFile(seq64.romdesc));
            seq64.seq->load(seq64.rom, ientryidx);
            seq64.seq->name = ROM::hex((uint8)ientryidx) + " " + txtIEntryName->getText();
            seq64.maincomponent->onSeqLoaded();
        }
        //[/UserButtonCode_btnLoadObject]
    }
    else if (buttonThatWasClicked == btnSaveObject.get())
    {
        //[UserButtonCode_btnSaveObject] -- add your button handler code here..
		if(selifile == nullptr) return;
        if(ientryidx < 0) return;
        if(selifile->getIName() == "Audiobank Index"){
            if(&*seq64.bank == nullptr){
                return;
            }
            if(!NativeMessageBox::showOkCancelBox(AlertWindow::WarningIcon,
                    "Overwrite?", "Replace bank " + String(ientryidx) + " with the currently loaded one?"
                    + "\n(This does not save the ROM to disk.)", nullptr, nullptr)) return;
            int ret = seq64.bank->save(seq64.rom, ientryidx);
            if(ret < 0){
                NativeMessageBox::showMessageBoxAsync(AlertWindow::WarningIcon, "Oh no",
                    "Saving bank failed. Check the terminal output for details.");
            }else if(ret > 0){
                NativeMessageBox::showMessageBoxAsync(AlertWindow::WarningIcon, "Oh no",
                    "Bank file is 0x" + ROM::hex((uint32)ret) + " bytes long, doesn't fit in this space!");
            }
            fillIndex();
        }else if(selifile->getIName() == "Audioseq Index"){
            if(&*seq64.seq == nullptr) return;
            uint32 availsize;
			if(!audioseq.getObjectRealSize(ientryidx, availsize)){
				SEQ64::say("Error getting target sequence real size!");
				return;
			}
			uint32 seqaddr, oldseqlen;
			audioseq.getObjectAddrLen(ientryidx, seqaddr, oldseqlen);
            uint32 loadedseqlength = seq64.seq->getLength();
            if(loadedseqlength > availsize){
                NativeMessageBox::showMessageBoxAsync(AlertWindow::WarningIcon, "Oh no",
                        "Loaded sequence is 0x" + ROM::hex(loadedseqlength, 4)
                        + " bytes, but there are only 0x" + ROM::hex((uint32)availsize, 4) + " bytes available.\n"
                        "Try using \"Make room for\" (perhaps after \"Compact\") to make room for this sequence.");
                return;
            }
            if(loadedseqlength >= 0x3800){
                if(!NativeMessageBox::showOkCancelBox(AlertWindow::WarningIcon,
                    "Size warning", "The loaded sequence is 0x" + ROM::hex(loadedseqlength, 4) + " bytes.\n"
                    + "Known games using Audioseq format cannot load sequences from the cartridge if they are"
                    + "greater than 0x3800 bytes.\n"
                    + "Are you sure you still want to save this sequence?", nullptr, nullptr)) return;
            }
            if(!NativeMessageBox::showOkCancelBox(AlertWindow::WarningIcon,
                    "Overwrite?", "Replace the sequence \"" + audioseq.getObjectName(ientryidx) + "\" (" + ROM::hex(oldseqlen, 4)
                    + " bytes)\nwith the currently loaded one \"" + seq64.seq->name + "\" (" + ROM::hex(loadedseqlength, 4) + " bytes)?"
                    + "\n(This does not save the ROM to disk.)", nullptr, nullptr)) return;
            uint32 seqfulladdr = audioseq.getFAddr() + seqaddr;
            uint8* seqdptr = &((uint8*)seq64.rom.getData())[seqfulladdr];
            memset(seqdptr, 0, oldseqlen); //Erase old sequence data
            seq64.seq->saveToROM(seq64.rom, seqfulladdr);
			audioseq.setObjectLen(ientryidx, loadedseqlength);
			audioseq.setObjectName(ientryidx, seq64.seq->name);
            fillIEntryParams();
        }
        //[/UserButtonCode_btnSaveObject]
    }
    else if (buttonThatWasClicked == optIndexType1.get())
    {
        //[UserButtonCode_optIndexType1] -- add your button handler code here..
        seq64.romdesc.setProperty("indextype", 1, nullptr);
		reloadFiles();
        //[/UserButtonCode_optIndexType1]
    }
    else if (buttonThatWasClicked == optIndexType2.get())
    {
        //[UserButtonCode_optIndexType2] -- add your button handler code here..
        seq64.romdesc.setProperty("indextype", 2, nullptr);
		reloadFiles();
        //[/UserButtonCode_optIndexType2]
    }
    else if (buttonThatWasClicked == btnEditIE.get())
    {
        //[UserButtonCode_btnEditIE] -- add your button handler code here..
        if(selifile == nullptr) return;
        Identifier idEditIE = "understandeditie";
        if(seq64.readProperty(idEditIE) != "yes"){
            if(!NativeMessageBox::showOkCancelBox(AlertWindow::WarningIcon,
                    "Are you sure you know what you're doing?",
                    "This allows you to edit the raw data of the index entry,\n"
                    "including the item address and length and, if applicable,\n"
                    "the other metadata values in the entry. Especially for\n"
                    "Audiobank, many of these fields ARE known and either editable\n"
                    "within the bank or determined at import. Obviously, changing\n"
                    "the address or length incorrectly will corrupt your ROM.\n\n"
                    "Are you sure you understand and want to continue?", nullptr, nullptr)) return;
            seq64.writeProperty(idEditIE, "yes");
        }
        DialogWindow::LaunchOptions iebox;
        iebox.dialogTitle = "Edit Index Entry";
        iebox.dialogBackgroundColour = Colours::lightgrey;
        iebox.content.setOwned(new IEEditor(*selifile, *this, ientryidx));
        iebox.resizable = false;
        iebox.launchAsync();
        //[/UserButtonCode_btnEditIE]
    }
    else if (buttonThatWasClicked == btnCompact.get())
    {
        //[UserButtonCode_btnCompact] -- add your button handler code here..
		if(selifile == nullptr) return;
        Identifier idCompact = "understandcompact";
        if(seq64.readProperty(idCompact) != "yes"){
            if(!NativeMessageBox::showOkCancelBox(AlertWindow::WarningIcon,
                    "Are you sure you know what you're doing?",
                    "This will remove empty space between items (banks/sequences)\n"
                    "by shifting all items towards the beginning of the file.\n"
                    "It will also update their addresses and lengths in the index\n"
                    "and update the Audiobank/Audioseq file length in the MFT.\n\n"
                    "Are you sure you want to do this?", nullptr, nullptr)) return;
            seq64.writeProperty(idCompact, "yes");
        }
        if(!selifile->compact()){
            NativeMessageBox::showMessageBoxAsync(AlertWindow::WarningIcon, "Oh no",
                    "Error compacting, please check the terminal output for details.");
        }else{
            NativeMessageBox::showMessageBoxAsync(AlertWindow::InfoIcon, "seq64",
                    "Compacting successful, please check the terminal output for further details.");
        }
        fillIndex();
        //[/UserButtonCode_btnCompact]
    }
    else if (buttonThatWasClicked == btnMakeRoom.get())
    {
        //[UserButtonCode_btnMakeRoom] -- add your button handler code here..
		if(selifile == nullptr) return;
        Identifier idMakeRoom = "understandmakeroom";
        if(seq64.readProperty(idMakeRoom) != "yes"){
            if(!NativeMessageBox::showOkCancelBox(AlertWindow::WarningIcon,
                    "Are you sure you know what you're doing?",
                    "This will attempt to make room for the selected item to be your\n"
                    "specified size, by shifting later items down into empty space at\n"
                    "the end of the file.\n\n"
                    "For instance if you have a sequence that is 0x300 long and you\n"
                    "click Make Room (0x500), it will try to shift all later sequences\n"
                    "down by 0x200 into empty space at the end of Audioseq. If there is\n"
                    "not 0x200 of empty space at the end of Audioseq, this will fail,\n"
                    "even if there is more than 0x200 of empty space between later sequences.\n"
                    "(So you might want to run Compact first for best results.)\n\n"
                    "Are you sure you want to do this?", nullptr, nullptr)) return;
            seq64.writeProperty(idMakeRoom, "yes");
        }
        int mrlen = txtMakeRoom->getText().getHexValue32();
        if(mrlen <= 0){
            NativeMessageBox::showMessageBoxAsync(AlertWindow::WarningIcon, "Oh no",
                    "Invalid Make Room length.");
            return;
        }
        if(!selifile->makeRoom(ientryidx, mrlen)){
            NativeMessageBox::showMessageBoxAsync(AlertWindow::WarningIcon, "Oh no",
                    "Making room failed, please check the terminal output for details.");
        }else{
            NativeMessageBox::showMessageBoxAsync(AlertWindow::InfoIcon, "seq64",
                    "Successfully made room for 0x" +  ROM::hex((uint32)mrlen, 6) + " bytes.");
        }
		fillIndex();
        //[/UserButtonCode_btnMakeRoom]
    }
    else if (buttonThatWasClicked == btnContentsCreate.get())
    {
        //[UserButtonCode_btnContentsCreate] -- add your button handler code here..
        if(selifile == nullptr) return;
        if(ientryidx < 0) return;
		uint32 addr, len;
		if(!selifile->getObjectAddrLen(ientryidx, addr, len)) return;
		if(len != 0) return;
		if(selifile->createContents(ientryidx)){
			NativeMessageBox::showMessageBoxAsync(AlertWindow::InfoIcon, "seq64",
                    "Created dummy contents.");
		}else{
			NativeMessageBox::showMessageBoxAsync(AlertWindow::WarningIcon, "Oh no",
                    "Creating dummy contents failed, please check the terminal output for details.");
		}
        fillIndex();
        //[/UserButtonCode_btnContentsCreate]
    }
    else if (buttonThatWasClicked == btnContentsDestroy.get())
    {
        //[UserButtonCode_btnContentsDestroy] -- add your button handler code here..
        if(selifile == nullptr) return;
        if(ientryidx < 0) return;
		uint32 addr, len;
		if(!selifile->getObjectAddrLen(ientryidx, addr, len)) return;
		if(len == 0) return;
        if(!NativeMessageBox::showOkCancelBox(AlertWindow::WarningIcon,
                "Are you sure you know what you're doing?",
                "This will clear the contents of the selected item and nullify\n"
                "(but not remove) its index entry.\n\n"
                "Are you sure you want to do this?", nullptr, nullptr)) return;
		if(selifile->destroyContents(ientryidx)){
			NativeMessageBox::showMessageBoxAsync(AlertWindow::InfoIcon, "seq64",
                    "Destroyed item contents.");
		}else{
			NativeMessageBox::showMessageBoxAsync(AlertWindow::WarningIcon, "Oh no",
                    "Destroying item contents failed, please check the terminal output for details.");
		}
        fillIndex();
        //[/UserButtonCode_btnContentsDestroy]
    }
    else if (buttonThatWasClicked == btnEntryInsert.get())
    {
        //[UserButtonCode_btnEntryInsert] -- add your button handler code here..
        if(ientryidx < 0) return;
        if(selifile == nullptr) return;
        if(selifile->getIName() == "Audiobank Index"){
            if(!NativeMessageBox::showOkCancelBox(AlertWindow::WarningIcon,
                    "Are you sure you know what you're doing?",
                    "This will insert an Audiobank Index entry, which will move all\n"
                    "subsequent banks down by 1 entry, changing all their indexes.\n"
                    "But, the banks map for each sequence will be updated to\n"
                    "correct for this so the sequences will still work.\n\n"
                    "Are you sure you want to do this?", nullptr, nullptr)) return;
        }else if(selifile->getIName() == "Audiotable Index"){
            if(!NativeMessageBox::showOkCancelBox(AlertWindow::WarningIcon,
                    "Are you sure you know what you're doing?",
                    "This will insert an Audiotable Index entry, which will move all\n"
                    "subsequent tables down by 1 entry, changing all their indexes.\n"
                    "But, the sample table number for each bank will be updated to\n"
                    "correct for this so the banks will still work.\n\n"
                    "Are you sure you want to do this?", nullptr, nullptr)) return;
        }else if(selifile->getIName() == "Audioseq Index"){
            if(!NativeMessageBox::showOkCancelBox(AlertWindow::WarningIcon,
                    "Are you sure you know what you're doing?",
                    "THIS WILL RUIN YOUR ROM\n\n"
                    "This will insert an Audioseq Index entry, which will move all\n"
                    "subsequent sequences down by 1 entry, changing all their indexes.\n"
                    "This means all songs in the game will be swapped around.\n"
                    "SEQ64 cannot correct for this; you will have to fix songs in\n"
                    "the scene headers and cutscenes manually.\n\n"
                    "Are you sure you want to do this?", nullptr, nullptr)) return;
			if(!sbm.canAddSeq()){
				NativeMessageBox::showMessageBoxAsync(AlertWindow::WarningIcon, "Oh no",
                    "Cannot insert a new sequence because no room to expand Sequence Banks Map.");
				return;
			}
        }
        if(!selifile->insertEntry(ientryidx)){
			NativeMessageBox::showMessageBoxAsync(AlertWindow::WarningIcon, "Oh no",
                    "Could not insert a new entry in " + selifile->getIName()
					+ ", please check the terminal output for details.");
			return;
		}
        if(selifile->getIName() == "Audiobank Index"){
            fixSBMForBankChange(true, ientryidx);
        }else if(selifile->getIName() == "Audiotable Index"){
            fixSampleTables(true, ientryidx);
        }else if(selifile->getIName() == "Audioseq Index"){
            if(!sbm.addSeq(ientryidx)){
				SEQ64::say("Internal error adding sequence to Sequence Banks Map!");
			}
        }
        NativeMessageBox::showMessageBoxAsync(AlertWindow::InfoIcon, "seq64",
                "Inserted a blank entry at index " + String(ientryidx) + " in " + selifile->getIName() + ".");
		++ientryidx;
		fillIndex();
        //[/UserButtonCode_btnEntryInsert]
    }
    else if (buttonThatWasClicked == btnEntryAdd.get())
    {
        //[UserButtonCode_btnEntryAdd] -- add your button handler code here..
        if(selifile == nullptr) return;
		if(selifile->getIName() == "Audioseq Index"){
			if(!sbm.canAddSeq()){
				NativeMessageBox::showMessageBoxAsync(AlertWindow::WarningIcon, "Oh no",
                    "Cannot add a new sequence because no room to expand Sequence Banks Map.");
				return;
			}
		}
		if(!selifile->addEntry()){
			NativeMessageBox::showMessageBoxAsync(AlertWindow::WarningIcon, "Oh no",
                    "Could not add a blank entry at the end of " + selifile->getIName()
					+ ", please check the terminal output for details.");
			return;
		}
		if(selifile->getIName() == "Audioseq Index"){
            if(!sbm.addSeq(audioseq.getICount()-1)){
				SEQ64::say("Internal error adding sequence to Sequence Banks Map!");
			}
        }
		NativeMessageBox::showMessageBoxAsync(AlertWindow::InfoIcon, "seq64",
				"Added a blank entry at the end of " + selifile->getIName() + ".");
		ientryidx = selifile->getICount() - 1;
		fillIndex();
        //[/UserButtonCode_btnEntryAdd]
    }
    else if (buttonThatWasClicked == btnEntryDelete.get())
    {
        //[UserButtonCode_btnEntryDelete] -- add your button handler code here..
        if(ientryidx < 0) return;
        if(selifile == nullptr) return;
        if(selifile->getIName() == "Audiobank Index"){
            if(!NativeMessageBox::showOkCancelBox(AlertWindow::WarningIcon,
                    "Are you sure you know what you're doing?",
                    "This will delete an Audiobank Index entry, which will move all\n"
                    "subsequent banks up by 1 entry, changing all their indexes.\n"
                    "Sequences using this bank will be changed to bank 0,\n"
                    "which will usually break them.\n"
                    "But, the banks map for the rest of the sequences will be\n"
                    "updated to correct for this so they will still work.\n\n"
                    "Are you sure you want to do this?", nullptr, nullptr)) return;
        }else if(selifile->getIName() == "Audiotable Index"){
            if(!NativeMessageBox::showOkCancelBox(AlertWindow::WarningIcon,
                    "Are you sure you know what you're doing?",
                    "This will delete an Audiotable Index entry, which will move all\n"
                    "subsequent tables up by 1 entry, changing all their indexes.\n"
                    "Banks using this sample table will be changed to table 0,\n"
                    "which will usually break them.\n"
                    "But, the sample table number for each of the other banks will be\n"
                    "updated to correct for this so those ones will still work.\n\n"
                    "Are you sure you want to do this?", nullptr, nullptr)) return;
        }else if(selifile->getIName() == "Audioseq Index"){
            if(!NativeMessageBox::showOkCancelBox(AlertWindow::WarningIcon,
                    "Are you sure you know what you're doing?",
                    "THIS WILL RUIN YOUR ROM\n\n"
                    "This will delete an Audioseq Index entry, which will move all\n"
                    "subsequent sequences up by 1 entry, changing all their indexes.\n"
                    "This means all songs in the game will be swapped around.\n"
                    "SEQ64 cannot correct for this; you will have to fix songs in\n"
                    "the scene headers and cutscenes manually.\n\n"
                    "Are you sure you want to do this?", nullptr, nullptr)) return;
			if(!sbm.canRemoveSeq(ientryidx)){
				SEQ64::say("Internal error, cannot remove seq from Sequence Banks Map!");
				return;
			}
        }
        if(!selifile->removeEntry(ientryidx)){
			NativeMessageBox::showMessageBoxAsync(AlertWindow::WarningIcon, "Oh no",
                    "Could not delete the entry in " + selifile->getIName()
					+ ", please check the terminal output for details.");
			return;
		}
        if(selifile->getIName() == "Audiobank Index"){
            fixSBMForBankChange(false, ientryidx);
        }else if(selifile->getIName() == "Audiotable Index"){
            fixSampleTables(false, ientryidx);
        }else if(selifile->getIName() == "Audioseq Index"){
            if(!sbm.removeSeq(ientryidx)){
				SEQ64::say("Internal error, could not remove seq from Sequence Banks Map!");
			}
        }
        NativeMessageBox::showMessageBoxAsync(AlertWindow::InfoIcon, "seq64",
                "Deleted entry at index " + String(ientryidx) + " in " + selifile->getIName() + ".");
		--ientryidx;
		fillIndex();
        //[/UserButtonCode_btnEntryDelete]
    }
    else if (buttonThatWasClicked == btnSBMAdd.get())
    {
        //[UserButtonCode_btnSBMAdd] -- add your button handler code here..
        if(!sbm.canAddBank(ientryidx)){
            NativeMessageBox::showMessageBoxAsync(AlertWindow::WarningIcon, "seq64",
                "Can't add new bank to Sequence Banks Index for sequence " + String(ientryidx)
                + " (usually this means there's no extra room at the end of Sequence Banks Index).");
            return;
        }
        if(!sbm.addBank(ientryidx, lstSeqBanks->getLastRowSelected(), 0)){
            NativeMessageBox::showMessageBoxAsync(AlertWindow::WarningIcon, "seq64",
                "Internal error adding bank to Sequence Banks Index!");
            return;
        }
        SEQ64::say("Successfully added bank to Sequence Banks Index");
        fillIEntryParams();
        //[/UserButtonCode_btnSBMAdd]
    }
    else if (buttonThatWasClicked == btnSBMDelete.get())
    {
        //[UserButtonCode_btnSBMDelete] -- add your button handler code here..
        int row = lstSeqBanks->getLastRowSelected();
        if(!sbm.canRemoveBank(ientryidx, row)){
            NativeMessageBox::showMessageBoxAsync(AlertWindow::WarningIcon, "seq64",
                "Can't remove bank from Sequence Banks Index for sequence " + String(ientryidx)
                + "(usually this means there's only one bank already).");
            return;
        }
        if(!sbm.removeBank(ientryidx, row)){
            NativeMessageBox::showMessageBoxAsync(AlertWindow::WarningIcon, "seq64",
                "Internal error removing bank from Sequence Banks Index!");
            return;
        }
        SEQ64::say("Successfully removed bank from Sequence Banks Index");
        fillIEntryParams();
        //[/UserButtonCode_btnSBMDelete]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void FilesPane::rowSelected(TextListModel* parent, int row){
    if(parent == &*lsmFileTable){
        ValueTree file = filelistnode.getChildWithProperty(Identifier("index"), row);
        if(file.isValid()){
            txtFileName->setText(file.getProperty("name", ""), dontSendNotification);
            cbxFileType->setText(file.getProperty("type", "Unknown"), dontSendNotification);
        }else{
            txtFileName->setText("", dontSendNotification);
            cbxFileType->setText("Unknown", dontSendNotification);
        }
    }else if(parent == &*lsmKFiles){
        selkfile = kfilelistnode.getChild(row);
        fillKFileParams();
        String type = selkfile.getProperty("type", "Unsupported");
        if(type == "Audiobank Index"){
			selifile = &audiobank;
		}else if(type == "Audioseq Index"){
			selifile = &audioseq;
		}else if(type == "Audiotable Index"){
            selifile = &audiotable;
        }else{
			selifile = nullptr;
        }
        fillIndex();
    }else if(parent == &*lsmIndex){
        ientryidx = row;
        fillIEntryParams();
    }else if(parent == &*lsmSeqBanks){
		cbxSeqBank->setSelectedItemIndex(sbm.getSeqBank(ientryidx, row), dontSendNotification);
    }
}
void FilesPane::textEditorTextChanged(TextEditor& editorThatWasChanged){
    String text = editorThatWasChanged.getText();
    //int decval = text.getIntValue();
    int hexval = text.getHexValue32();
    bool turnRed = false;
    if(&editorThatWasChanged == &*txtFTAddr){
        uint32 ftaddr = hexval;
        if(seq64.rom.getSize() == 0 || seq64.rom.getSize() <= ftaddr + 16){
            ftaddr = 0;
            turnRed = true;
        }else if(seq64.rom.readWord(ftaddr + 0x20) != ftaddr){
            SEQ64::say("Data at " + ROM::hex(ftaddr) + " is not a file table");
            ftaddr = 0;
            turnRed = true;
        }else{
            fillFileTable();
            turnRed = false;
        }
		seq64.romdesc.setProperty("ftaddr", (int)ftaddr, nullptr);
    }else if(&editorThatWasChanged == &*txtFileName){
        int findex = lstFileTable->getLastRowSelected();
        if(findex < 0) return;
		uint32 ftaddr = (int)seq64.romdesc.getProperty("ftaddr", 0);
        if(ftaddr == 0) return;
        ValueTree file = filelistnode.getChildWithProperty(Identifier("index"), findex);
        if(!file.isValid()){
            file = ValueTree(Identifier("file"));
            file.setProperty(Identifier("index"), findex, nullptr);
            filelistnode.addChild(file, filelistnode.getNumChildren(), nullptr);
        }
        file.setProperty(Identifier("name"), text, nullptr);
        uint32 a = ftaddr + 0x10*findex;
        lsmFileTable->set(findex, getFileDescription(a, findex));
        lstFileTable->repaintRow(findex);
    }else if(&editorThatWasChanged == &*txtKFileAddr){
        if(!selkfile.isValid()) return;
        if((bool)selkfile.getProperty("from_ft", false)){
            //Prevent you from changing it
            fillKFileParams();
            return;
        }
        selkfile.setProperty("address", hexval, nullptr);
		reloadFiles();
        if(hexval <= 0) turnRed = true;
        if(selifile != nullptr) fillIndex();
    }else if(&editorThatWasChanged == &*txtKFileLength){
        if(!selkfile.isValid()) return;
        if((bool)selkfile.getProperty("from_ft", false)){
            //Prevent you from changing it
            fillKFileParams();
            return;
        }
        selkfile.setProperty("length", hexval, nullptr);
		reloadFiles();
        if(hexval <= 0) turnRed = true;
    }else if(&editorThatWasChanged == &*txtIEntryName){
        if(selifile == nullptr) return;
        if(ientryidx < 0) return;
		selifile->setObjectName(ientryidx, text);
        ieNameChanged(false);
    }else if(&editorThatWasChanged == &*txtEntryPointer){
		if(selifile == nullptr) return;
        if(ientryidx < 0) return;
		uint32 addr, len;
		if(!selifile->getObjectAddrLen(ientryidx, addr, len)) return;
		if(len != 0) return;
		selifile->setObjectAddr(ientryidx, hexval);
        String newname;
        if(hexval == 0){
            newname = "(Blank entry)";
        }else if(hexval < 0 || hexval >= selifile->getICount()){
            newname = "Ptr off end of index (crash)";
        }else if(hexval == ientryidx){
            newname = "Recursive pointer AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA! (crash)";
        }else{
			newname = "Ptr to " + selifile->getObjectName(hexval);
        }
		selifile->setObjectName(ientryidx, newname);
        ieNameChanged(true);
    }
    if(turnRed){
        editorThatWasChanged.setColour(TextEditor::backgroundColourId, Colours::red);
    }else{
        editorThatWasChanged.setColour(TextEditor::backgroundColourId, LFWidgetColor());
    }
}

void FilesPane::reloadFiles(){
	audiobank.reloadFileProps();
	audioseq.reloadFileProps();
	audiotable.reloadFileProps();
	sbm.reloadFileProps();
}

void FilesPane::romDescLoaded(){
	//Globals
    filelistnode = seq64.romdesc.getOrCreateChildWithName("filelist", nullptr);
    kfilelistnode = seq64.romdesc.getOrCreateChildWithName("knownfilelist", nullptr);
	//Set up ROM properties
    txtFTAddr->setText(ROM::hex((uint32)(int)seq64.romdesc.getProperty("ftaddr", 0)), dontSendNotification);
    int indextype = (int)seq64.romdesc.getProperty("indextype", 1);
    optIndexType1->setToggleState((indextype == 1), dontSendNotification);
    optIndexType2->setToggleState((indextype == 2), dontSendNotification);
	//Refresh things
	reloadFiles();
    fillFileTable();
    fillKFiles();
}

//Files

String FilesPane::getFileDescription(uint32 a, int i){
    String desc;
    ValueTree file = filelistnode.getChildWithProperty(Identifier("index"), i);
    if(file.isValid()){
        desc = file.getProperty(Identifier("name"));
    }else{
        desc = "?";
    }
    desc += ": @" + ROM::hex(seq64.rom.readWord(a)) + " to " + ROM::hex(seq64.rom.readWord(a+4));
    if(seq64.rom.readWord(a+12) != 0){
        desc += " (*)";
    }
    return desc;
}

void FilesPane::fillFileTable(){
    lsmFileTable->clear();
    lstFileTable->updateContent();
	uint32 ftaddr = (int)seq64.romdesc.getProperty("ftaddr", 0);
    uint32 ftend = seq64.rom.readWord(ftaddr + 0x24);
    if(ftaddr == 0 || ftend <= ftaddr || ftend - ftaddr >= 0x10000){
        lstFileTable->updateContent();
        return;
    }
    //Show table
    uint32 a;
    int i;
    for(a=ftaddr, i=0; a<ftend; a += 0x10, i++){
        lsmFileTable->add(getFileDescription(a, i));
        if(i > 10000){
            SEQ64::say("More than 10,000 files, exiting!");
            break;
        }
    }
    lstFileTable->updateContent();
}

bool FilesPane::isKnownFileType(String filetype){
    for(int i=0; i<cbxKFileType->getNumItems(); i++){
        if(cbxKFileType->getItemText(i).equalsIgnoreCase(filetype)) return true;
    }
    return false;
}

//Known Files

void FilesPane::fillKFiles(){
    lsmKFiles->clear();
    for(int c=0; c<kfilelistnode.getNumChildren(); c++){
        lsmKFiles->add(kfilelistnode.getChild(c).getProperty("type", "Unsupported"));
    }
    lstKFiles->updateContent();
}

void FilesPane::fillKFileParams(){
    if(selkfile.isValid()){
        cbxKFileType->setText(selkfile.getProperty("type", "Unsupported"), dontSendNotification);
        txtKFileAddr->setText(ROM::hex((uint32)(int)selkfile.getProperty("address", 0)), dontSendNotification);
        txtKFileLength->setText(ROM::hex((uint32)(int)selkfile.getProperty("length", 0)), dontSendNotification);
    }else{
        cbxKFileType->setText("", dontSendNotification);
        txtKFileAddr->setText("", dontSendNotification);
        txtKFileLength->setText("", dontSendNotification);
    }
}

//Index

void FilesPane::fillIndex(){
    //Clear all
    int ientryidx_orig = lstIndex->getLastRowSelected();
    lsmIndex->clear();
    lstIndex->updateContent();
    lsmSeqBanks->clear();
    lstSeqBanks->updateContent();
	btnLoadObject->setButtonText("Load Object");
	btnSaveObject->setButtonText("Save Object");
	btnLoadObject->setEnabled(false);
	btnSaveObject->setEnabled(false);
	grpUtilitiesContents->setText("Object (Contents)");
	grpUtilitiesEntry->setText("Index Entry");
	lblIndexProps->setText("File selected is not an index", dontSendNotification);
	//Check params
    if(seq64.rom.getSize() == 0){
        lblIndexProps->setText("No ROM loaded", dontSendNotification);
        return;
    }
    if(selifile == nullptr){
        lblIndexProps->setText("No index file selected", dontSendNotification);
        return;
    }
	//Update controls
	if(selifile->getIName() == "Audiobank Index"){
		btnLoadObject->setButtonText("Load Bank");
		btnSaveObject->setButtonText("Save Bank");
		btnLoadObject->setEnabled(true);
		btnSaveObject->setEnabled(true);
		grpUtilitiesContents->setText("Bank (Contents)");
		grpUtilitiesEntry->setText("Audiobank Index Entry");
	}else if(selifile->getIName() == "Audioseq Index"){
		btnLoadObject->setButtonText("Load Sequence");
		btnSaveObject->setButtonText("Save Sequence");
		btnLoadObject->setEnabled(true);
		btnSaveObject->setEnabled(true);
		grpUtilitiesContents->setText("Sequence (Contents)");
		grpUtilitiesEntry->setText("Audioseq Index Entry");
	}else if(selifile->getIName() == "Audiotable Index"){
		btnLoadObject->setButtonText("Can't Load Table");
		btnSaveObject->setButtonText("Can't Save Table");
		grpUtilitiesContents->setText("Table (Contents)");
		grpUtilitiesEntry->setText("Audiotable Index Entry");
	}else{
		return;
	}
    grpIndex->setText(selifile->getIName());
    //Refresh things that may have changed with changes to index
    fillSeqBankList();
    if(selifile->getIName() == "Audiobank Index"){
        seq64.maincomponent->onGotABI();
    }
    //Fill index list box
	if(selifile->getICount() <= 0){
		lblIndexProps->setText("Invalid index address", dontSendNotification);
	}else{
		lblIndexProps->setText(String(selifile->getICount()) + " entries", dontSendNotification);
	}
	lsmIndex->clear();
    for(int i=0; i<selifile->getICount(); i++){
        lsmIndex->add(selifile->getObjectDescription(i));
    }
    lstIndex->updateContent();
	lstIndex->selectRow(ientryidx_orig);
}

void FilesPane::fillIEntryParams(){
    if(selifile == nullptr || ientryidx < 0){
        txtIEntryName->setEnabled(false);
        txtIEntryName->setText("", dontSendNotification);
        lblIEntryData->setText("[Entry data]", dontSendNotification);
        btnContentsCreate->setEnabled(false);
        btnContentsDestroy->setEnabled(false);
        txtMakeRoom->setEnabled(false);
        txtMakeRoom->setText("0000", dontSendNotification);
        btnMakeRoom->setEnabled(false);
        txtEntryPointer->setEnabled(false);
        txtEntryPointer->setText("00", dontSendNotification);
        btnEntryAdd->setEnabled(false);
        btnEntryInsert->setEnabled(false);
        btnEntryDelete->setEnabled(false);
        btnEditIE->setEnabled(false);
        return;
    }
    txtIEntryName->setEnabled(true);
    btnEntryAdd->setEnabled(true);
    btnEntryInsert->setEnabled(true);
    btnEntryDelete->setEnabled(true);
    btnEditIE->setEnabled(true);
    String data;
    uint32 addr, len;
    selifile->getObjectAddrLen(ientryidx, addr, len);
    data = "@" + ROM::hex(addr) + ", len " + ROM::hex(len);
    if((int)seq64.romdesc.getProperty("indextype", 1) == 2){
		uint32 md1, md2;
		selifile->getObjectMetadata(ientryidx, md1, md2);
        data += ": " + ROM::hex(md1);
        data += " " + ROM::hex(md2);
    }
    lblIEntryData->setText(data, dontSendNotification);
	ieNameChanged(true);
    //Utilities
    if(len == 0){
        //None/pointer entry
        btnContentsCreate->setEnabled(true);
        btnContentsDestroy->setEnabled(false);
        txtMakeRoom->setEnabled(false);
        txtMakeRoom->setText("0000", dontSendNotification);
        btnMakeRoom->setEnabled(false);
        txtEntryPointer->setEnabled(true);
        txtEntryPointer->setText(ROM::hex((uint8)addr), dontSendNotification);
    }else{
        btnContentsCreate->setEnabled(false);
        btnContentsDestroy->setEnabled(true);
        txtMakeRoom->setEnabled(true);
        txtMakeRoom->setText(ROM::hex(len, 4), dontSendNotification);
        btnMakeRoom->setEnabled(true);
        txtEntryPointer->setEnabled(false);
        txtEntryPointer->setText("00", dontSendNotification);
    }
    //Select banks
    if(selifile->getIName() != "Audioseq Index") return;
	int nbanks = sbm.getSeqNumBanks(ientryidx);
    int sel_seqbank = lstSeqBanks->getLastRowSelected();
    if(sel_seqbank < 0 || sel_seqbank >= nbanks) sel_seqbank = nbanks - 1;
    lsmSeqBanks->clear();
    lstSeqBanks->updateContent();
	for(int i=0; i<nbanks; ++i){
		uint8 b = sbm.getSeqBank(ientryidx, i);
		lsmSeqBanks->add(ROM::hex(b) + ": " + audiobank.getObjectName(b));
	}
    lstSeqBanks->updateContent();
    lstSeqBanks->selectRow(sel_seqbank);
}

void FilesPane::ieNameChanged(bool updateNameBox){
	if(selifile == nullptr) return;
	if(ientryidx < 0) return;
    lsmIndex->set(ientryidx, selifile->getObjectDescription(ientryidx));
    lstIndex->repaintRow(ientryidx);
    if(updateNameBox) txtIEntryName->setText(selifile->getObjectName(ientryidx), dontSendNotification);
}

void FilesPane::fillSeqBankList(){
    cbxSeqBank->clear();
    if(seq64.rom.getSize() == 0) return;
    if(selifile == nullptr) return;
    if(selifile->getIName() != "Audioseq Index"){
        grpSeqBanks->setText("Sequence banks (Audioseq Index only):");
        return;
    }
    grpSeqBanks->setText("Sequence banks:");
	for(int i=0; i<audiobank.getICount(); ++i){
		cbxSeqBank->addItem(ROM::hex((uint8)i) + ": " + audiobank.getObjectName(i), cbxSeqBank->getNumItems()+1);
	}
}

void FilesPane::fixSBMForBankChange(bool add, int idx){
	for(int i=0; i<audioseq.getICount(); ++i){
		int nbanks = sbm.getSeqNumBanks(i);
		for(int bi=0; bi<nbanks; ++bi){
			int b = sbm.getSeqBank(i, bi);
			if(b >= idx){
				sbm.setSeqBank(i, bi, add ? b+1 : (b == idx ? 0 : b-1));
			}
		}
	}
}

void FilesPane::fixSampleTables(bool add, int idx){
	NativeMessageBox::showMessageBoxAsync(AlertWindow::WarningIcon, "TODO",
			"Fixing bank sample table numbers is not yet implemented.\n\n"
			"Your ROM is now corrupted.");
}


//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="FilesPane" componentName=""
                 parentClasses="public Component, public TextEditor::Listener, public TextListModel::Listener"
                 constructorParams="SEQ64&amp; seq64_" variableInitialisers="seq64(seq64_),&#10;audiobank(seq64.rom, seq64.romdesc, &quot;Audiobank&quot;),&#10;audioseq(seq64.rom, seq64.romdesc, &quot;Audioseq&quot;),&#10;audiotable(seq64.rom, seq64.romdesc, &quot;Audiotable&quot;),&#10;sbm(seq64.rom, seq64.romdesc, audioseq)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="1078" initialHeight="713">
  <BACKGROUND backgroundColour="ff323e44"/>
  <GROUPCOMPONENT name="new group" id="65f54d111ed8eedd" memberName="grpSeqBanks"
                  virtualName="" explicitFocusOrder="0" pos="496 472 336 136" title="Sequence banks:"/>
  <GROUPCOMPONENT name="new group" id="a707e7b9cb5e40a2" memberName="grpIndex"
                  virtualName="" explicitFocusOrder="0" pos="0 144 496 568" title="Index"/>
  <GROUPCOMPONENT name="new group" id="e0ed18b4290a5f40" memberName="grpUtilitiesEntry"
                  virtualName="" explicitFocusOrder="0" pos="8 512 480 80" title="Entry"/>
  <GROUPCOMPONENT name="ROM Properties" id="b371dbf0a4a1b58f" memberName="groupComponent"
                  virtualName="" explicitFocusOrder="0" pos="496 0 336 120" title="ROM Properties"/>
  <GROUPCOMPONENT name="new group" id="50f8d472e934f3ad" memberName="grpUtilitiesContents"
                  virtualName="" explicitFocusOrder="0" pos="8 592 480 112" title="Contents"/>
  <GROUPCOMPONENT name="new group" id="da1838da4937cc20" memberName="grpMFT" virtualName=""
                  explicitFocusOrder="0" pos="496 120 336 352" title="Master File Table (dmadata)"/>
  <LABEL name="new label" id="feac5e6d64dda05e" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="504 16 96 24" edTextCol="ff000000"
         edBkgCol="0" labelText="MFT Address:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="b0f34b76891a115d" memberName="txtFTAddr"
              virtualName="" explicitFocusOrder="0" pos="600 16 80 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="9d8b9b46e68c2983" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="504 416 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Name:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="baf4f79779fe44c6" memberName="txtFileName"
              virtualName="" explicitFocusOrder="0" pos="560 416 264 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="5e17f0c7cbf49c52" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="504 440 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Type:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="new combo box" id="a982a2bb18b425a6" memberName="cbxFileType"
            virtualName="" explicitFocusOrder="0" pos="560 440 264 24" editable="0"
            layout="33" items="Unknown&#10;ROM Header&#10;Boot Code&#10;Master File Table&#10;Audiobank&#10;Audioseq&#10;Audiotable&#10;Code&#10;Texture&#10;Shared Assets&#10;Text Data&#10;Actor&#10;Object&#10;Scene&#10;Room&#10;Other"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="f2833c68aa3a69c3" memberName="label4" virtualName=""
         explicitFocusOrder="0" pos="504 392 320 24" edTextCol="ff000000"
         edBkgCol="0" labelText="[Address information]" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <GROUPCOMPONENT name="new group" id="f59a75502f6f9763" memberName="grpKnownFiles"
                  virtualName="" explicitFocusOrder="0" pos="0 0 496 144" title="Known Files"/>
  <TEXTBUTTON name="new button" id="20b0109f8e92d22a" memberName="btnKFileAdd"
              virtualName="" explicitFocusOrder="0" pos="248 112 120 24" buttonText="Add"
              connectedEdges="2" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="5eceeff61cabc54a" memberName="btnKFileDel"
              virtualName="" explicitFocusOrder="0" pos="368 112 120 24" buttonText="Delete"
              connectedEdges="1" needsCallback="1" radioGroupId="0"/>
  <LABEL name="new label" id="3b17daf4620f7036" memberName="label5" virtualName=""
         explicitFocusOrder="0" pos="248 16 47 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Type:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="new combo box" id="dba63b9be0a5c57" memberName="cbxKFileType"
            virtualName="" explicitFocusOrder="0" pos="296 16 192 24" editable="0"
            layout="33" items="Unsupported&#10;Audiobank&#10;Audioseq&#10;Audiotable&#10;Audiobank Index&#10;Audioseq Index&#10;Audiotable Index&#10;Sequence Banks Map"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="1756f94b14c6940f" memberName="label6" virtualName=""
         explicitFocusOrder="0" pos="248 40 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Address:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="e1d35d2b85f2de9a" memberName="txtKFileAddr"
              virtualName="" explicitFocusOrder="0" pos="320 40 80 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="29eda2beea4f4f73" memberName="label7" virtualName=""
         explicitFocusOrder="0" pos="248 64 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Length:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="f3befab09a65150a" memberName="txtKFileLength"
              virtualName="" explicitFocusOrder="0" pos="320 64 80 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="5c4f6c4947dd2650" memberName="lblIndexProps"
         virtualName="" explicitFocusOrder="0" pos="8 160 480 24" edTextCol="ff000000"
         edBkgCol="0" labelText="[Index length, address, etc.]" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="5d02266efa726b59" memberName="label11" virtualName=""
         explicitFocusOrder="0" pos="16 528 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Name:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="d2ccdddf01b27ef0" memberName="txtIEntryName"
              virtualName="" explicitFocusOrder="0" pos="72 528 408 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="750191ec030e4bcc" memberName="lblIEntryData"
         virtualName="" explicitFocusOrder="0" pos="8 488 480 24" edTextCol="ff000000"
         edBkgCol="0" labelText="[Entry data]" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="new button" id="c6f7b2138260d81d" memberName="btnLoadObject"
              virtualName="" explicitFocusOrder="0" pos="16 616 232 24" buttonText="Load Object"
              connectedEdges="2" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="93eb02f5f765bd07" memberName="btnSaveObject"
              virtualName="" explicitFocusOrder="0" pos="248 616 232 24" buttonText="Save Object"
              connectedEdges="1" needsCallback="1" radioGroupId="0"/>
  <TOGGLEBUTTON name="new toggle button" id="b9de436f2f2f8a29" memberName="optIndexType1"
                virtualName="" explicitFocusOrder="0" pos="528 64 128 24" buttonText="4/8 (SM64, etc.)"
                connectedEdges="0" needsCallback="1" radioGroupId="1" state="1"/>
  <TOGGLEBUTTON name="new toggle button" id="c28e8c6e3b30311f" memberName="optIndexType2"
                virtualName="" explicitFocusOrder="0" pos="528 88 144 24" buttonText="16/16 (Zelda, etc.)"
                connectedEdges="0" needsCallback="1" radioGroupId="1" state="0"/>
  <LABEL name="new label" id="6d5d89e6ea22ae4c" memberName="label10" virtualName=""
         explicitFocusOrder="0" pos="504 576 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Bank:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="34"/>
  <COMBOBOX name="new combo box" id="eb9c8b0efed24a37" memberName="cbxSeqBank"
            virtualName="" explicitFocusOrder="0" pos="560 576 264 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <TEXTBUTTON name="new button" id="d6765357ec4aae16" memberName="btnEditIE"
              virtualName="" explicitFocusOrder="0" pos="312 560 166 24" buttonText="Edit Entry (Metadata)"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="149a5c2bee6bc8fe" memberName="btnCompact"
              virtualName="" explicitFocusOrder="0" pos="400 672 80 24" buttonText="Compact"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="7a397ef5edfd6693" memberName="btnMakeRoom"
              virtualName="" explicitFocusOrder="0" pos="304 648 88 24" buttonText="Make Room"
              connectedEdges="1" needsCallback="1" radioGroupId="0"/>
  <LABEL name="new label" id="e875322d507e6967" memberName="label8" virtualName=""
         explicitFocusOrder="0" pos="144 648 120 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Make room for 0x" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="e3b2c158d9a94abc" memberName="txtMakeRoom"
              virtualName="" explicitFocusOrder="0" pos="264 648 40 24" initialText="1000"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTBUTTON name="new button" id="eebbc4936a2263c0" memberName="btnContentsCreate"
              virtualName="" explicitFocusOrder="0" pos="16 648 128 24" buttonText="Create"
              connectedEdges="8" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="f2d02ac2da1cc4fa" memberName="btnContentsDestroy"
              virtualName="" explicitFocusOrder="0" pos="16 672 128 24" buttonText="Destroy/Pointerize"
              connectedEdges="4" needsCallback="1" radioGroupId="0"/>
  <LABEL name="new label" id="ca1b76b48fec52a9" memberName="label9" virtualName=""
         explicitFocusOrder="0" pos="144 672 128 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Pointer to entry: 0x" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="7d6faed50a54f538" memberName="txtEntryPointer"
              virtualName="" explicitFocusOrder="0" pos="272 672 32 24" initialText="00"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTBUTTON name="new button" id="5b41d2756e95ddc0" memberName="btnEntryInsert"
              virtualName="" explicitFocusOrder="0" pos="96 560 80 24" buttonText="Insert"
              connectedEdges="3" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="35c4626e95ba90e" memberName="btnEntryAdd"
              virtualName="" explicitFocusOrder="0" pos="16 560 80 24" buttonText="Add"
              connectedEdges="2" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="77ead61af32390ed" memberName="btnEntryDelete"
              virtualName="" explicitFocusOrder="0" pos="176 560 80 24" buttonText="Delete"
              connectedEdges="1" needsCallback="1" radioGroupId="0"/>
  <LABEL name="new label" id="465eee7184dff006" memberName="label12" virtualName=""
         explicitFocusOrder="0" pos="504 40 208 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Index format (hdr/entry bytes):" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="new button" id="ea86b3b3c48cf6f7" memberName="btnSBMAdd"
              virtualName="" explicitFocusOrder="0" pos="504 496 48 24" buttonText="Add"
              connectedEdges="8" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="93a25109c887620d" memberName="btnSBMDelete"
              virtualName="" explicitFocusOrder="0" pos="504 544 48 24" buttonText="Del"
              connectedEdges="4" needsCallback="1" radioGroupId="0"/>
  <LABEL name="new label" id="665a2de3c0adb5e2" memberName="label13" virtualName=""
         explicitFocusOrder="0" pos="504 520 48 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Row" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]


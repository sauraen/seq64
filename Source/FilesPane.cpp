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
 * FilesPane.cpp
 * GUI component for N64 ROM internal files screen
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
    : seq64(seq64_)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (grpUtilities = new GroupComponent ("new group",
                                                          TRANS("Utilities")));

    addAndMakeVisible (grpUtilitiesContents = new GroupComponent ("new group",
                                                                  TRANS("Contents")));

    addAndMakeVisible (grpMFT = new GroupComponent ("new group",
                                                    TRANS("Master File Table")));

    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("Address:")));
    label->setFont (Font (15.00f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (txtFTAddr = new TextEditor ("new text editor"));
    txtFTAddr->setMultiLine (false);
    txtFTAddr->setReturnKeyStartsNewLine (false);
    txtFTAddr->setReadOnly (false);
    txtFTAddr->setScrollbarsShown (true);
    txtFTAddr->setCaretVisible (true);
    txtFTAddr->setPopupMenuEnabled (true);
    txtFTAddr->setText (String::empty);

    addAndMakeVisible (label2 = new Label ("new label",
                                           TRANS("Name:")));
    label2->setFont (Font (15.00f, Font::plain));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (txtFileName = new TextEditor ("new text editor"));
    txtFileName->setMultiLine (false);
    txtFileName->setReturnKeyStartsNewLine (false);
    txtFileName->setReadOnly (false);
    txtFileName->setScrollbarsShown (true);
    txtFileName->setCaretVisible (true);
    txtFileName->setPopupMenuEnabled (true);
    txtFileName->setText (String::empty);

    addAndMakeVisible (label3 = new Label ("new label",
                                           TRANS("Type:")));
    label3->setFont (Font (15.00f, Font::plain));
    label3->setJustificationType (Justification::centredLeft);
    label3->setEditable (false, false, false);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (cbxFileType = new ComboBox ("new combo box"));
    cbxFileType->setEditableText (false);
    cbxFileType->setJustificationType (Justification::centredLeft);
    cbxFileType->setTextWhenNothingSelected (String::empty);
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

    addAndMakeVisible (label4 = new Label ("new label",
                                           TRANS("[Address information]")));
    label4->setFont (Font (15.00f, Font::plain));
    label4->setJustificationType (Justification::centredLeft);
    label4->setEditable (false, false, false);
    label4->setColour (TextEditor::textColourId, Colours::black);
    label4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (grpKnownFiles = new GroupComponent ("new group",
                                                           TRANS("Known Files")));

    addAndMakeVisible (btnKFileAdd = new TextButton ("new button"));
    btnKFileAdd->setButtonText (TRANS("Add"));
    btnKFileAdd->setConnectedEdges (Button::ConnectedOnRight);
    btnKFileAdd->addListener (this);

    addAndMakeVisible (btnKFileDel = new TextButton ("new button"));
    btnKFileDel->setButtonText (TRANS("Del"));
    btnKFileDel->setConnectedEdges (Button::ConnectedOnLeft);
    btnKFileDel->addListener (this);

    addAndMakeVisible (label5 = new Label ("new label",
                                           TRANS("Type:")));
    label5->setFont (Font (15.00f, Font::plain));
    label5->setJustificationType (Justification::centredLeft);
    label5->setEditable (false, false, false);
    label5->setColour (TextEditor::textColourId, Colours::black);
    label5->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (cbxKFileType = new ComboBox ("new combo box"));
    cbxKFileType->setEditableText (false);
    cbxKFileType->setJustificationType (Justification::centredLeft);
    cbxKFileType->setTextWhenNothingSelected (String::empty);
    cbxKFileType->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    cbxKFileType->addItem (TRANS("Unsupported"), 1);
    cbxKFileType->addItem (TRANS("Audiobank"), 2);
    cbxKFileType->addItem (TRANS("Audioseq"), 3);
    cbxKFileType->addItem (TRANS("Audiotable"), 4);
    cbxKFileType->addItem (TRANS("Audiobank Index"), 5);
    cbxKFileType->addItem (TRANS("Audioseq Index"), 6);
    cbxKFileType->addItem (TRANS("Sample Set Index"), 7);
    cbxKFileType->addItem (TRANS("Instrument Set Index"), 8);
    cbxKFileType->addListener (this);

    addAndMakeVisible (label6 = new Label ("new label",
                                           TRANS("Address:")));
    label6->setFont (Font (15.00f, Font::plain));
    label6->setJustificationType (Justification::centredLeft);
    label6->setEditable (false, false, false);
    label6->setColour (TextEditor::textColourId, Colours::black);
    label6->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (txtKFileAddr = new TextEditor ("new text editor"));
    txtKFileAddr->setMultiLine (false);
    txtKFileAddr->setReturnKeyStartsNewLine (false);
    txtKFileAddr->setReadOnly (false);
    txtKFileAddr->setScrollbarsShown (true);
    txtKFileAddr->setCaretVisible (true);
    txtKFileAddr->setPopupMenuEnabled (true);
    txtKFileAddr->setText (String::empty);

    addAndMakeVisible (label7 = new Label ("new label",
                                           TRANS("Length:")));
    label7->setFont (Font (15.00f, Font::plain));
    label7->setJustificationType (Justification::centredLeft);
    label7->setEditable (false, false, false);
    label7->setColour (TextEditor::textColourId, Colours::black);
    label7->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (txtKFileLength = new TextEditor ("new text editor"));
    txtKFileLength->setMultiLine (false);
    txtKFileLength->setReturnKeyStartsNewLine (false);
    txtKFileLength->setReadOnly (false);
    txtKFileLength->setScrollbarsShown (true);
    txtKFileLength->setCaretVisible (true);
    txtKFileLength->setPopupMenuEnabled (true);
    txtKFileLength->setText (String::empty);

    addAndMakeVisible (grpIndex = new GroupComponent ("new group",
                                                      TRANS("Index")));

    addAndMakeVisible (lblIndexProps = new Label ("new label",
                                                  TRANS("[Index length, address, etc.]")));
    lblIndexProps->setFont (Font (15.00f, Font::plain));
    lblIndexProps->setJustificationType (Justification::centredLeft);
    lblIndexProps->setEditable (false, false, false);
    lblIndexProps->setColour (TextEditor::textColourId, Colours::black);
    lblIndexProps->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label11 = new Label ("new label",
                                            TRANS("Name:")));
    label11->setFont (Font (15.00f, Font::plain));
    label11->setJustificationType (Justification::centredLeft);
    label11->setEditable (false, false, false);
    label11->setColour (TextEditor::textColourId, Colours::black);
    label11->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (txtIEntryName = new TextEditor ("new text editor"));
    txtIEntryName->setMultiLine (false);
    txtIEntryName->setReturnKeyStartsNewLine (false);
    txtIEntryName->setReadOnly (false);
    txtIEntryName->setScrollbarsShown (true);
    txtIEntryName->setCaretVisible (true);
    txtIEntryName->setPopupMenuEnabled (true);
    txtIEntryName->setText (String::empty);

    addAndMakeVisible (lblIEntryData = new Label ("new label",
                                                  TRANS("[Entry data]")));
    lblIEntryData->setFont (Font (15.00f, Font::plain));
    lblIEntryData->setJustificationType (Justification::centredLeft);
    lblIEntryData->setEditable (false, false, false);
    lblIEntryData->setColour (TextEditor::textColourId, Colours::black);
    lblIEntryData->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (btnLoadEntry = new TextButton ("new button"));
    btnLoadEntry->setButtonText (TRANS("Load Entry"));
    btnLoadEntry->setConnectedEdges (Button::ConnectedOnBottom);
    btnLoadEntry->addListener (this);

    addAndMakeVisible (btnSaveEntry = new TextButton ("new button"));
    btnSaveEntry->setButtonText (TRANS("Save Entry"));
    btnSaveEntry->setConnectedEdges (Button::ConnectedOnTop);
    btnSaveEntry->addListener (this);

    addAndMakeVisible (groupComponent4 = new GroupComponent ("new group",
                                                             TRANS("Index Format")));

    addAndMakeVisible (optIndexType1 = new ToggleButton ("new toggle button"));
    optIndexType1->setButtonText (TRANS("Word hdr; [addr, length] (SM64, MK64)"));
    optIndexType1->setRadioGroupId (1);
    optIndexType1->addListener (this);
    optIndexType1->setToggleState (true, dontSendNotification);

    addAndMakeVisible (optIndexType2 = new ToggleButton ("new toggle button"));
    optIndexType2->setButtonText (TRANS("4-word hdr; [addr, length, 2 data] (Zelda, Yoshi)"));
    optIndexType2->setRadioGroupId (1);
    optIndexType2->addListener (this);

    addAndMakeVisible (lblInstSet = new Label ("new label",
                                               TRANS("Instrument sets:")));
    lblInstSet->setFont (Font (15.00f, Font::plain));
    lblInstSet->setJustificationType (Justification::centredLeft);
    lblInstSet->setEditable (false, false, false);
    lblInstSet->setColour (TextEditor::textColourId, Colours::black);
    lblInstSet->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label10 = new Label ("new label",
                                            TRANS("Set:")));
    label10->setFont (Font (15.00f, Font::plain));
    label10->setJustificationType (Justification::centredLeft);
    label10->setEditable (false, false, false);
    label10->setColour (TextEditor::textColourId, Colours::black);
    label10->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (cbxInstSet1 = new ComboBox ("new combo box"));
    cbxInstSet1->setEditableText (false);
    cbxInstSet1->setJustificationType (Justification::centredLeft);
    cbxInstSet1->setTextWhenNothingSelected (String::empty);
    cbxInstSet1->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    cbxInstSet1->addListener (this);

    addAndMakeVisible (btnEditIE = new TextButton ("new button"));
    btnEditIE->setButtonText (TRANS("Edit Index Entry (Metadata)"));
    btnEditIE->addListener (this);

    addAndMakeVisible (btnCompact = new TextButton ("new button"));
    btnCompact->setButtonText (TRANS("Compact"));
    btnCompact->addListener (this);

    addAndMakeVisible (btnMakeRoom = new TextButton ("new button"));
    btnMakeRoom->setButtonText (TRANS("Make Room"));
    btnMakeRoom->setConnectedEdges (Button::ConnectedOnLeft);
    btnMakeRoom->addListener (this);

    addAndMakeVisible (label8 = new Label ("new label",
                                           TRANS("Make room for 0x")));
    label8->setFont (Font (15.00f, Font::plain));
    label8->setJustificationType (Justification::centredLeft);
    label8->setEditable (false, false, false);
    label8->setColour (TextEditor::textColourId, Colours::black);
    label8->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (txtMakeRoom = new TextEditor ("new text editor"));
    txtMakeRoom->setMultiLine (false);
    txtMakeRoom->setReturnKeyStartsNewLine (false);
    txtMakeRoom->setReadOnly (false);
    txtMakeRoom->setScrollbarsShown (true);
    txtMakeRoom->setCaretVisible (true);
    txtMakeRoom->setPopupMenuEnabled (true);
    txtMakeRoom->setText (TRANS("1000"));

    addAndMakeVisible (btnContentsCreate = new TextButton ("new button"));
    btnContentsCreate->setButtonText (TRANS("Create"));
    btnContentsCreate->setConnectedEdges (Button::ConnectedOnRight);
    btnContentsCreate->addListener (this);

    addAndMakeVisible (btnContentsDestroy = new TextButton ("new button"));
    btnContentsDestroy->setButtonText (TRANS("Destroy/Pointerize"));
    btnContentsDestroy->setConnectedEdges (Button::ConnectedOnLeft);
    btnContentsDestroy->addListener (this);

    addAndMakeVisible (label9 = new Label ("new label",
                                           TRANS("Pointer to entry: 0x")));
    label9->setFont (Font (15.00f, Font::plain));
    label9->setJustificationType (Justification::centredLeft);
    label9->setEditable (false, false, false);
    label9->setColour (TextEditor::textColourId, Colours::black);
    label9->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (txtEntryPointer = new TextEditor ("new text editor"));
    txtEntryPointer->setMultiLine (false);
    txtEntryPointer->setReturnKeyStartsNewLine (false);
    txtEntryPointer->setReadOnly (false);
    txtEntryPointer->setScrollbarsShown (true);
    txtEntryPointer->setCaretVisible (true);
    txtEntryPointer->setPopupMenuEnabled (true);
    txtEntryPointer->setText (TRANS("00"));

    addAndMakeVisible (grpUtilitiesEntry = new GroupComponent ("new group",
                                                               TRANS("Entry")));

    addAndMakeVisible (btnEntryInsert = new TextButton ("new button"));
    btnEntryInsert->setButtonText (TRANS("Insert"));
    btnEntryInsert->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
    btnEntryInsert->addListener (this);

    addAndMakeVisible (btnEntryAdd = new TextButton ("new button"));
    btnEntryAdd->setButtonText (TRANS("Add"));
    btnEntryAdd->setConnectedEdges (Button::ConnectedOnRight);
    btnEntryAdd->addListener (this);

    addAndMakeVisible (btnEntryDelete = new TextButton ("new button"));
    btnEntryDelete->setButtonText (TRANS("Delete"));
    btnEntryDelete->setConnectedEdges (Button::ConnectedOnLeft);
    btnEntryDelete->addListener (this);


    //[UserPreSize]
    lsmFileTable = new TextListModel();
    lsmFileTable->setListener(this);

    addAndMakeVisible(lstFileTable = new ListBox("FileTable", lsmFileTable));
    lstFileTable->setMultipleSelectionEnabled(false);
    lstFileTable->setRowHeight(16);
    lstFileTable->setOutlineThickness(1);
    lstFileTable->setColour(ListBox::outlineColourId, Colours::lightgrey);

    lsmKFiles = new TextListModel();
    lsmKFiles->setListener(this);

    addAndMakeVisible(lstKFiles = new ListBox("KFiles", lsmKFiles));
    lstKFiles->setMultipleSelectionEnabled(false);
    lstKFiles->setRowHeight(16);
    lstKFiles->setOutlineThickness(1);
    lstKFiles->setColour(ListBox::outlineColourId, Colours::lightgrey);

    lsmIndex = new TextListModel();
    lsmIndex->setListener(this);

    addAndMakeVisible(lstIndex = new ListBox("Index", lsmIndex));
    lstIndex->setMultipleSelectionEnabled(false);
    lstIndex->setRowHeight(16);
    lstIndex->setOutlineThickness(1);
    lstIndex->setColour(ListBox::outlineColourId, Colours::lightgrey);

    lsmInstSets = new TextListModel();
    lsmInstSets->setListener(this);

    addAndMakeVisible(lstInstSets = new ListBox("InstSets", lsmInstSets));
    lstInstSets->setMultipleSelectionEnabled(false);
    lstInstSets->setRowHeight(16);
    lstInstSets->setOutlineThickness(1);
    lstInstSets->setColour(ListBox::outlineColourId, Colours::lightgrey);

    txtFTAddr->addListener(this);
    txtFileName->addListener(this);
    txtKFileAddr->addListener(this);
    txtKFileLength->addListener(this);
    txtIEntryName->addListener(this);
    txtEntryPointer->addListener(this);

    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    ftaddr = 0;
    dataaddr = -1;
    abi_addr = -1;
    asi_addr = -1;
    ssi_addr = -1;
    isi_addr = -1;
    abi_count = -1;
    asi_count = -1;
    ssi_count = -1;
    seq_lastbank = -1;

    romDescLoaded();
    //[/Constructor]
}

FilesPane::~FilesPane()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    grpUtilities = nullptr;
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
    grpIndex = nullptr;
    lblIndexProps = nullptr;
    label11 = nullptr;
    txtIEntryName = nullptr;
    lblIEntryData = nullptr;
    btnLoadEntry = nullptr;
    btnSaveEntry = nullptr;
    groupComponent4 = nullptr;
    optIndexType1 = nullptr;
    optIndexType2 = nullptr;
    lblInstSet = nullptr;
    label10 = nullptr;
    cbxInstSet1 = nullptr;
    btnEditIE = nullptr;
    btnCompact = nullptr;
    btnMakeRoom = nullptr;
    label8 = nullptr;
    txtMakeRoom = nullptr;
    btnContentsCreate = nullptr;
    btnContentsDestroy = nullptr;
    label9 = nullptr;
    txtEntryPointer = nullptr;
    grpUtilitiesEntry = nullptr;
    btnEntryInsert = nullptr;
    btnEntryAdd = nullptr;
    btnEntryDelete = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void FilesPane::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void FilesPane::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    grpUtilities->setBounds (760, 0, 272, 200);
    grpUtilitiesContents->setBounds (768, 48, 256, 96);
    grpMFT->setBounds (0, 0, 336, 448);
    label->setBounds (8, 16, 72, 24);
    txtFTAddr->setBounds (80, 16, 80, 24);
    label2->setBounds (8, 392, 56, 24);
    txtFileName->setBounds (64, 392, 264, 24);
    label3->setBounds (8, 416, 56, 24);
    cbxFileType->setBounds (64, 416, 264, 24);
    label4->setBounds (8, 368, 320, 24);
    grpKnownFiles->setBounds (0, 448, 336, 264);
    btnKFileAdd->setBounds (8, 624, 40, 24);
    btnKFileDel->setBounds (48, 624, 40, 24);
    label5->setBounds (96, 624, 47, 24);
    cbxKFileType->setBounds (144, 624, 184, 24);
    label6->setBounds (176, 656, 72, 24);
    txtKFileAddr->setBounds (248, 656, 80, 24);
    label7->setBounds (176, 680, 72, 24);
    txtKFileLength->setBounds (248, 680, 80, 24);
    grpIndex->setBounds (336, 0, 424, 712);
    lblIndexProps->setBounds (344, 88, 408, 24);
    label11->setBounds (344, 472, 56, 24);
    txtIEntryName->setBounds (400, 472, 352, 24);
    lblIEntryData->setBounds (344, 448, 408, 24);
    btnLoadEntry->setBounds (344, 504, 136, 24);
    btnSaveEntry->setBounds (344, 528, 136, 24);
    groupComponent4->setBounds (344, 16, 408, 72);
    optIndexType1->setBounds (352, 32, 392, 24);
    optIndexType2->setBounds (352, 56, 392, 24);
    lblInstSet->setBounds (344, 560, 408, 24);
    label10->setBounds (344, 680, 40, 24);
    cbxInstSet1->setBounds (384, 680, 368, 24);
    btnEditIE->setBounds (536, 504, 214, 24);
    btnCompact->setBounds (768, 16, 256, 24);
    btnMakeRoom->setBounds (936, 88, 80, 24);
    label8->setBounds (776, 88, 120, 24);
    txtMakeRoom->setBounds (896, 88, 40, 24);
    btnContentsCreate->setBounds (776, 64, 120, 24);
    btnContentsDestroy->setBounds (896, 64, 120, 24);
    label9->setBounds (776, 112, 128, 24);
    txtEntryPointer->setBounds (904, 112, 32, 24);
    grpUtilitiesEntry->setBounds (768, 144, 256, 48);
    btnEntryInsert->setBounds (856, 160, 80, 24);
    btnEntryAdd->setBounds (776, 160, 80, 24);
    btnEntryDelete->setBounds (936, 160, 80, 24);
    //[UserResized] Add your own custom resize handling here..
    lstFileTable->setBounds (8, 48, 320, 320);
    lstKFiles->setBounds (8, 464, 320, 152);
    lstIndex->setBounds (344, 120, 408, 320);
    lstInstSets->setBounds (344, 584, 408, 88);
    //[/UserResized]
}

void FilesPane::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == cbxFileType)
    {
        //[UserComboBoxCode_cbxFileType] -- add your combo box handling code here..
        int findex = lstFileTable->getLastRowSelected();
        if(findex < 0) return;
        if(ftaddr == 0) return;
        String type = cbxFileType->getText();
        //See if we are removing a known file
        ValueTree kfile = kfilelistnode.getChildWithProperty("ftindex", findex);
        if(kfile.isValid()){
            changedIndexAddress(type, -1);
            kfilelistnode.removeChild(kfile, nullptr);
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
            changedIndexAddress(type, file_addr);
            kfilelistnode.addChild(kfile, kfilelistnode.getNumChildren(), nullptr);
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
    else if (comboBoxThatHasChanged == cbxKFileType)
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
        String oldtype = selkfile.getProperty("type");
        if(oldtype.endsWith("Index")) changedIndexAddress(oldtype, -1);
        uint32 addr = (int)selkfile.getProperty("address");
        if(type.endsWith("Index")) changedIndexAddress(type, addr);
        selkfile.setProperty("type", type, nullptr);
        //Refresh display
        int idx = lstKFiles->getLastRowSelected();
        lsmKFiles->set(idx, cbxKFileType->getText());
        lstKFiles->repaintRow(idx);
        //[/UserComboBoxCode_cbxKFileType]
    }
    else if (comboBoxThatHasChanged == cbxInstSet1)
    {
        //[UserComboBoxCode_cbxInstSet1] -- add your combo box handling code here..
        if(!selindex.isValid()) return;
        if(selindex.getProperty("type", "Unsupported").toString() != "Audioseq Index") return;
        if(ientryidx < 0) return;
        if(isi_addr < 0) return;
        int idx = cbxInstSet1->getSelectedItemIndex();
        int row = lstInstSets->getLastRowSelected();
        if(idx < 0 || row < 0) return;
        uint16 ptr = seq64.rom.readHalfWord(isi_addr + (ientryidx << 1));
        seq64.rom.writeByte(isi_addr + ptr + row + 1, idx & 0x000000FF);
        lsmInstSets->set(row, cbxInstSet1->getText());
        lstInstSets->repaintRow(row);
        //[/UserComboBoxCode_cbxInstSet1]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void FilesPane::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == btnKFileAdd)
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
    else if (buttonThatWasClicked == btnKFileDel)
    {
        //[UserButtonCode_btnKFileDel] -- add your button handler code here..
        if(!selkfile.isValid()) return;
        if((bool)selkfile.getProperty("from_ft", false)){
            SEQ64::say("From file table, can't delete!");
            return;
        }
        //Remove old index address
        String oldtype = selkfile.getProperty("type");
        changedIndexAddress(oldtype, -1);
        //Remove kfile
        kfilelistnode.removeChild(selkfile, nullptr);
        selkfile = ValueTree();
        fillKFiles();
        lstKFiles->selectRow(-1);
        //[/UserButtonCode_btnKFileDel]
    }
    else if (buttonThatWasClicked == btnLoadEntry)
    {
        //[UserButtonCode_btnLoadEntry] -- add your button handler code here..
        if(!idxlistnode.isValid()) return;
        if(ientryidx < 0) return;
        if(dataaddr < 0) return;
        if(idxlistnode.hasType("audiobankidx")){
            if(&*seq64.bank != nullptr){
                if(!NativeMessageBox::showOkCancelBox(AlertWindow::WarningIcon,
                        "Overwrite?", "A bank is already loaded, overwrite it?", nullptr, nullptr)) return;
            }
            seq64.bank = new BankFile(seq64.romdesc);
            int ret = seq64.bank->load(seq64.rom, ientryidx);
            if(ret < 0){
                NativeMessageBox::showMessageBoxAsync(AlertWindow::WarningIcon, "Oh no",
                    "Error(s) encountered when loading bank, check the terminal output for details.");
            }
            //TODO debug only
            File f = File::getSpecialLocation(File::userHomeDirectory).getChildFile("audiobank.log");
            f.replaceWithText(seq64.bank->d.toXmlString());
            //^^end debug only
            seq64.maincomponent->onBankLoaded();
        }else if(idxlistnode.hasType("audioseqidx")){
            if(&*seq64.seq != nullptr){
                if(!NativeMessageBox::showOkCancelBox(AlertWindow::WarningIcon,
                        "Overwrite?", "A sequence is already loaded, overwrite it?", nullptr, nullptr)) return;
            }
            seq64.seq = new SeqFile(seq64.romdesc);
            seq64.seq->load(seq64.rom, ientryidx);
            seq64.seq->name = ROM::hex((uint8)ientryidx) + " " + txtIEntryName->getText();
            seq64.maincomponent->onSeqLoaded();
        }else{
            NativeMessageBox::showMessageBoxAsync (AlertWindow::InfoIcon, "Stop it",
                    "Loading an entry from " + idxlistnode.getType().toString() + " not supported");
        }
        //[/UserButtonCode_btnLoadEntry]
    }
    else if (buttonThatWasClicked == btnSaveEntry)
    {
        //[UserButtonCode_btnSaveEntry] -- add your button handler code here..
        if(!idxlistnode.isValid()) return;
        if(ientryidx < 0) return;
        if(dataaddr < 0) return;
        if(idxlistnode.hasType("audiobankidx")){
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
        }else if(idxlistnode.hasType("audioseqidx")){
            if(&*seq64.seq == nullptr) return;
            uint32 seqaddr, length;
            readIEAddrLen(indexaddr, ientryidx, seqaddr, length);
            seqaddr += dataaddr;
            uint32 availsize = getRealEntrySize(ientryidx);
            uint32 loadedseqlength = seq64.seq->getLength();
            if(loadedseqlength > availsize){
                NativeMessageBox::showMessageBoxAsync(AlertWindow::WarningIcon, "Oh no",
                        "Loaded sequence is 0x" + ROM::hex(loadedseqlength, 4)
                        + " bytes, but there are only 0x" + ROM::hex((uint32)availsize, 4) + " bytes available.\n"
                        "Try using \"Make room for\" (perhaps after \"Compact\") to make room for this sequence.");
                return;
            }
            if(!NativeMessageBox::showOkCancelBox(AlertWindow::WarningIcon,
                    "Overwrite?", "Replace the sequence @" + ROM::hex(seqaddr) + " (" + ROM::hex(length, 4)
                    + " bytes)\nwith the currently loaded one (" + ROM::hex(loadedseqlength, 4) + " bytes)?"
                    + "\n(This does not save the ROM to disk.)", nullptr, nullptr)) return;
            seq64.seq->saveToROM(seq64.rom, seqaddr);
            writeIELen(indexaddr, ientryidx, loadedseqlength);
            setIEntryName(seq64.seq->name, true);
            fillIEntryParams();
        }else{
            NativeMessageBox::showMessageBoxAsync (AlertWindow::InfoIcon, "Stop it",
                    "Saving an entry to " + idxlistnode.getType().toString() + " not supported");
        }
        //[/UserButtonCode_btnSaveEntry]
    }
    else if (buttonThatWasClicked == optIndexType1)
    {
        //[UserButtonCode_optIndexType1] -- add your button handler code here..
        seq64.romdesc.setProperty("indextype", 1, nullptr);
        //[/UserButtonCode_optIndexType1]
    }
    else if (buttonThatWasClicked == optIndexType2)
    {
        //[UserButtonCode_optIndexType2] -- add your button handler code here..
        seq64.romdesc.setProperty("indextype", 2, nullptr);
        //[/UserButtonCode_optIndexType2]
    }
    else if (buttonThatWasClicked == btnEditIE)
    {
        //[UserButtonCode_btnEditIE] -- add your button handler code here..
        if(!selindex.isValid()) return;
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
        uint32 ieaddr;
        if((int)seq64.romdesc.getProperty("indextype", 1) == 2){
            ieaddr = indexaddr + (16*ientryidx) + 16;
        }else{
            ieaddr = indexaddr + (8*ientryidx) + 4;
        }
        DialogWindow::LaunchOptions iebox;
        iebox.dialogTitle = "Edit Index Entry";
        iebox.dialogBackgroundColour = Colours::lightgrey;
        iebox.content.setOwned(new IEEditor(seq64, *this, ieaddr));
        iebox.resizable = false;
        iebox.launchAsync();
        //[/UserButtonCode_btnEditIE]
    }
    else if (buttonThatWasClicked == btnCompact)
    {
        //[UserButtonCode_btnCompact] -- add your button handler code here..
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
        if(!compact()){
            NativeMessageBox::showMessageBoxAsync(AlertWindow::WarningIcon, "Oh no",
                    "Error compacting, please check the terminal output for details.");
        }else{
            NativeMessageBox::showMessageBoxAsync(AlertWindow::InfoIcon, "seq64",
                    "Compacting successful, please check the terminal output for further details.");
        }
        //[/UserButtonCode_btnCompact]
    }
    else if (buttonThatWasClicked == btnMakeRoom)
    {
        //[UserButtonCode_btnMakeRoom] -- add your button handler code here..
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
        int res = makeroom(mrlen);
        if(res < 0){
            NativeMessageBox::showMessageBoxAsync(AlertWindow::WarningIcon, "Oh no",
                    "Error making room, please check the terminal output for details.");
        }else if(res == 0){
            NativeMessageBox::showMessageBoxAsync(AlertWindow::WarningIcon, "Sorry",
                    "Could not make room for 0x" + ROM::hex((uint32)mrlen, 6)
                    + " bytes, please check the terminal output for further details.");
        }else{
            NativeMessageBox::showMessageBoxAsync(AlertWindow::InfoIcon, "seq64",
                    "Successfully made room for 0x" +  ROM::hex((uint32)mrlen, 6) + " bytes.");
        }
        //[/UserButtonCode_btnMakeRoom]
    }
    else if (buttonThatWasClicked == btnContentsCreate)
    {
        //[UserButtonCode_btnContentsCreate] -- add your button handler code here..
        if(!idxlistnode.isValid()) return;
        if(ientryidx < 0) return;
        int32 ilen, faddr;
        String indexname, filename;
        if(!getIndexAndFileParams(ilen, faddr, indexname, filename)) return;
        uint32 addr, len;
        readIEAddrLen(indexaddr, ientryidx, addr, len);
        if(len != 0) return;
        int lastobjectend = getLastObjectEnd(faddr);
        int realend = getFileRealEnd(lastobjectend);
        if(realend - lastobjectend < 0x10){
            NativeMessageBox::showMessageBoxAsync(AlertWindow::WarningIcon, "Oh no",
                    "There is no room at the end of " + filename + " for a new item.");
            return;
        }
        memset(&((uint8*)seq64.rom.getData())[lastobjectend], 0, 0x10);
        writeIEAddr(indexaddr, ientryidx, lastobjectend-faddr);
        writeIELen(indexaddr, ientryidx, 0x10);
        updateFileLength(filename, faddr, lastobjectend-faddr+0x10);
        setIEntryName("New " + String(filename == "Audioseq" ? "Sequence" : "Bank"), true);
        fillIEntryParams();
        //[/UserButtonCode_btnContentsCreate]
    }
    else if (buttonThatWasClicked == btnContentsDestroy)
    {
        //[UserButtonCode_btnContentsDestroy] -- add your button handler code here..
        if(!idxlistnode.isValid()) return;
        if(ientryidx < 0) return;
        int32 ilen, faddr;
        String indexname, filename;
        if(!getIndexAndFileParams(ilen, faddr, indexname, filename)) return;
        uint32 addr, len;
        readIEAddrLen(indexaddr, ientryidx, addr, len);
        if(len == 0) return;
        if(!NativeMessageBox::showOkCancelBox(AlertWindow::WarningIcon,
                "Are you sure you know what you're doing?",
                "This will clear the contents of the selected item and nullify\n"
                "(but not remove) its index entry.\n\n"
                "Are you sure you want to do this?", nullptr, nullptr)) return;
        memset(&((uint8*)seq64.rom.getData())[faddr+addr], 0, len);
        writeIEAddr(indexaddr, ientryidx, 0);
        writeIELen(indexaddr, ientryidx, 0);
        setIEntryName("(Blank entry)", true);
        fillIEntryParams();
        //[/UserButtonCode_btnContentsDestroy]
    }
    else if (buttonThatWasClicked == btnEntryInsert)
    {
        //[UserButtonCode_btnEntryInsert] -- add your button handler code here..
        //[/UserButtonCode_btnEntryInsert]
    }
    else if (buttonThatWasClicked == btnEntryAdd)
    {
        //[UserButtonCode_btnEntryAdd] -- add your button handler code here..
        //[/UserButtonCode_btnEntryAdd]
    }
    else if (buttonThatWasClicked == btnEntryDelete)
    {
        //[UserButtonCode_btnEntryDelete] -- add your button handler code here..
        //[/UserButtonCode_btnEntryDelete]
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
        if(type == "Audiobank Index" || type == "Audioseq Index" || type == "Sample Set Index"){
            selindex = selkfile;
        }else{
            selindex = ValueTree();
        }
        fillIndex();
    }else if(parent == &*lsmIndex){
        ientryidx = row;
        fillIEntryParams();
    }else if(parent == &*lsmInstSets){
        if(isi_addr < 0) return;
        if(abi_addr < 0) return;
        if(abi_count < 0 || abi_count >= 0x100) return;
        uint16 ptr = seq64.rom.readHalfWord(isi_addr + (ientryidx << 1));
        uint8 b = seq64.rom.readByte(isi_addr + ptr + row + 1);
        if(b >= abi_count){
            cbxInstSet1->setText("Error: value " + ROM::hex(b) + "!", dontSendNotification);
        }else{
            cbxInstSet1->setSelectedItemIndex(b, dontSendNotification);
        }
    }
}
void FilesPane::textEditorTextChanged(TextEditor& editorThatWasChanged){
    String text = editorThatWasChanged.getText();
    //int decval = text.getIntValue();
    int hexval = text.getHexValue32();
    bool turnRed = false;
    if(&editorThatWasChanged == &*txtFTAddr){
        ftaddr = hexval;
        if(seq64.rom.getSize() == 0 || seq64.rom.getSize() <= ftaddr + 16){
            ftaddr = 0;
            turnRed = true;
        }else if(seq64.rom.readWord(ftaddr + 0x20) != ftaddr){
            SEQ64::say("Data at " + ROM::hex(ftaddr) + " is not a file table");
            ftaddr = 0;
            turnRed = true;
        }else{

            seq64.romdesc.setProperty("ftaddr", (int)ftaddr, nullptr);
            fillFileTable();
            turnRed = false;
        }
    }else if(&editorThatWasChanged == &*txtFileName){
        int findex = lstFileTable->getLastRowSelected();
        if(findex < 0) return;
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
        if(hexval <= 0) turnRed = true;
        if(selindex.isValid()) fillIndex();
    }else if(&editorThatWasChanged == &*txtKFileLength){
        if(!selkfile.isValid()) return;
        if((bool)selkfile.getProperty("from_ft", false)){
            //Prevent you from changing it
            fillKFileParams();
            return;
        }
        selkfile.setProperty("length", hexval, nullptr);
        if(hexval <= 0) turnRed = true;
    }else if(&editorThatWasChanged == &*txtIEntryName){
        if(!idxlistnode.isValid()) return;
        if(ientryidx < 0) return;
        setIEntryName(text, false);
    }else if(&editorThatWasChanged == &*txtEntryPointer){
        if(!idxlistnode.isValid()) return;
        if(ientryidx < 0) return;
        uint32 addr, len;
        readIEAddrLen(indexaddr, ientryidx, addr, len);
        if(len != 0) return;
        writeIEAddr(indexaddr, ientryidx, hexval);
        String newname;
        if(hexval == 0){
            newname = "(Blank entry)";
        }else if(hexval < 0 || hexval >= indexcount){
            newname = "Ptr off end of index (crash)";
        }else if(hexval == ientryidx){
            newname = "Recursive pointer AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAH! (crash)";
        }else{
            ValueTree ptrentry = idxlistnode.getChildWithProperty(Identifier("index"), hexval);
            if(!ptrentry.isValid()){
                newname = "Ptr to unnamed entry";
            }else{
                newname = "Ptr to " + ptrentry.getProperty("name", "unnamed entry").toString();
            }
        }
        setIEntryName(newname, true);
    }
    if(turnRed){
        editorThatWasChanged.setColour(TextEditor::backgroundColourId, Colours::red);
    }else{
        editorThatWasChanged.setColour(TextEditor::backgroundColourId, Colours::white);
    }
}

void FilesPane::setIEntryName(String newname, bool updateNameBox){
    if(!idxlistnode.isValid()) return;
    ValueTree thisentry = idxlistnode.getChildWithProperty(Identifier("index"), ientryidx);
    if(!thisentry.isValid()){
        if(newname == "") return;
        thisentry = ValueTree(Identifier("indexentry"));
        thisentry.setProperty("index", ientryidx, nullptr);
        idxlistnode.addChild(thisentry, idxlistnode.getNumChildren(), nullptr);
    }
    thisentry.setProperty("name", newname, nullptr);
    lsmIndex->set(ientryidx, getIEntryDescription(ientryidx));
    lstIndex->repaintRow(ientryidx);
    if(updateNameBox) txtIEntryName->setText(newname, dontSendNotification);
}

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
            a = ftend + 1;
            break;
        }
    }
    lstFileTable->updateContent();
}

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

String FilesPane::getIEntryDescription(int i){
    if(!idxlistnode.isValid()) return "";
    if(seq64.rom.getSize() == 0) return "";
    uint32 addr, len;
    readIEAddrLen(indexaddr, i, addr, len);
    String ret = ROM::hex((uint8)i) + " @" + ROM::hex(addr, 6) + " len " + ROM::hex(len, 4);
    addr += dataaddr;
    uint32 availsize = getRealEntrySize(i);
    if(availsize != len){
        ret += " (avail " + ROM::hex((uint32)availsize, 4) + ")";
    }
    ValueTree entry = idxlistnode.getChildWithProperty("index", i);
    if(entry.isValid()){
        ret += ": " + entry.getProperty("name", "[Unnamed]").toString();
    }
    return ret;
}

void FilesPane::fillIndex(){
    lsmInstSets->clear();
    lstInstSets->updateContent();
    lsmIndex->clear();
    lstIndex->updateContent();
    if(seq64.rom.getSize() == 0){
        lblIndexProps->setText("No ROM loaded", dontSendNotification);
        lstIndex->updateContent();
        return;
    }
    if(!selindex.isValid()){
        lblIndexProps->setText("No index file selected", dontSendNotification);
        lstIndex->updateContent();
        return;
    }
    String type = selindex.getProperty("type", "Unsupported");
    if(type == "Audiobank Index" || type == "Audioseq Index"){
        int temp = getFileForIndex(type).getProperty("address", -1);
        if(temp == -2){
            lblIndexProps->setText("Corresponding file not described in RomDesc", dontSendNotification);
            lstIndex->updateContent();
        }
        if(temp < 0) return;
        dataaddr = temp;
        if(type == "Audiobank Index"){
            idxlistnode = seq64.romdesc.getOrCreateChildWithName("audiobankidx", nullptr);
            btnLoadEntry->setButtonText("Load Bank");
            btnSaveEntry->setButtonText("Save Bank");
            grpUtilitiesContents->setText("Bank File");
            grpUtilitiesEntry->setText("Audiobank Index Entry");
        }else{
            idxlistnode = seq64.romdesc.getOrCreateChildWithName("audioseqidx", nullptr);
            btnLoadEntry->setButtonText("Load Sequence");
            btnSaveEntry->setButtonText("Save Sequence");
            grpUtilitiesContents->setText("Sequence File");
            grpUtilitiesEntry->setText("Audioseq Index Entry");
        }
    }else if(type == "Sample Set Index"){
        //No data associated
        idxlistnode = seq64.romdesc.getOrCreateChildWithName("samplesetidx", nullptr);
        btnLoadEntry->setButtonText("Can't load");
        btnSaveEntry->setButtonText("Can't save");
    }else{
        lblIndexProps->setText("File selected is not an index", dontSendNotification);
        btnLoadEntry->setButtonText("No");
        btnSaveEntry->setButtonText("No");
        lstIndex->updateContent();
        return;
    }
    grpIndex->setText(type);
    //
    indexaddr = (int)selindex.getProperty("address", 0);
    indexcount = getIndexCount(indexaddr);
    if(indexcount > 1000 || indexcount <= 0){
        lblIndexProps->setText(String(indexcount) + " entries, probably wrong", dontSendNotification);
        lstIndex->updateContent();
        return;
    }
    lblIndexProps->setText(String(indexcount) + " entries", dontSendNotification);
    for(int i=0; i<indexcount; i++){
        lsmIndex->add(getIEntryDescription(i));
    }
    lstIndex->updateContent();
    fillInstSetBoxes();
    if(type == "Audiobank Index"){
        seq64.maincomponent->onGotABI();
    }
}

void FilesPane::refreshIndexEntry(){
    if(!selindex.isValid()) return;
    lsmIndex->set(ientryidx, getIEntryDescription(ientryidx));
    lstIndex->repaintRow(ientryidx);
    fillIEntryParams();
}

void FilesPane::fillIEntryParams(){
    if(!selindex.isValid()){
        txtIEntryName->setText("", dontSendNotification);
        lblIEntryData->setText("[Entry data]", dontSendNotification);
        btnContentsCreate->setEnabled(false);
        btnContentsDestroy->setEnabled(false);
        txtMakeRoom->setEnabled(false);
        txtMakeRoom->setText("0000", dontSendNotification);
        btnMakeRoom->setEnabled(false);
        txtEntryPointer->setEnabled(false);
        txtEntryPointer->setText("00", dontSendNotification);
        return;
    }
    String data;
    uint32 addr, len;
    readIEAddrLen(indexaddr, ientryidx, addr, len);
    data = "@" + ROM::hex(addr) + ", len " + ROM::hex(len);
    if((int)seq64.romdesc.getProperty("indextype", 1) == 2){
        data += ": " + ROM::hex(seq64.rom.readWord(indexaddr + (16*ientryidx) + 24));
        data += " " + ROM::hex(seq64.rom.readWord(indexaddr + (16*ientryidx) + 28));
    }
    lblIEntryData->setText(data, dontSendNotification);
    ValueTree entry = idxlistnode.getChildWithProperty("index", ientryidx);
    if(entry.isValid()){
        txtIEntryName->setText(entry.getProperty("name", "[Unnamed]").toString(), dontSendNotification);
    }else{
        txtIEntryName->setText("", dontSendNotification);
    }
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
    //Select instrument sets
    if(selindex.getProperty("type", "Unsupported").toString() != "Audioseq Index") return;
    if(isi_addr < 0) return;
    if(abi_addr < 0) return;
    if(abi_count < 0 || abi_count >= 0x100) return;
    uint16 ptr = seq64.rom.readHalfWord(isi_addr + (ientryidx << 1));
    uint32 a = isi_addr + ptr;
    int seq_isetcount = seq64.rom.readByte(a);
    a++;
    int sel_seqiset = lstInstSets->getLastRowSelected();
    //Make list
    lsmInstSets->clear();
    lstInstSets->updateContent();
    uint8 b;
    ValueTree abk_names = seq64.romdesc.getOrCreateChildWithName("audiobankidx", nullptr);
    String desc;
    ValueTree bank;
    for(int i=0; i<seq_isetcount; i++){
        b = seq64.rom.readByte(a);
        a++;
        desc = ROM::hex(b);
        bank = abk_names.getChildWithProperty("index", b);
        if(bank.isValid()){
            desc += ": " + bank.getProperty("name", "[Unnamed]").toString();
        }
        lsmInstSets->add(desc);
        seq_lastbank = b;
    }
    lstInstSets->updateContent();
    lstInstSets->selectRow(sel_seqiset);
}

void FilesPane::loadIndexParams(String indexname){
    ValueTree index = kfilelistnode.getChildWithProperty("type", indexname);
    int addr = index.isValid() ? (int)index.getProperty("address", -1) : -1;
    changedIndexAddress(indexname, addr);
}

void FilesPane::romDescLoaded(){
    filelistnode = seq64.romdesc.getOrCreateChildWithName("filelist", nullptr);
    kfilelistnode = seq64.romdesc.getOrCreateChildWithName("knownfilelist", nullptr);
    ftaddr = (int)seq64.romdesc.getProperty("ftaddr", 0);
    txtFTAddr->setText(ROM::hex((uint32)ftaddr), dontSendNotification);
    int indextype = (int)seq64.romdesc.getProperty("indextype", 1);
    optIndexType1->setToggleState((indextype == 1), dontSendNotification);
    optIndexType2->setToggleState((indextype == 2), dontSendNotification);
    //Load index addresses
    loadIndexParams("Audiobank Index");
    loadIndexParams("Audioseq Index");
    loadIndexParams("Sample Set Index");
    loadIndexParams("Instrument Set Index");
    //Refresh screen
    fillFileTable();
    fillKFiles();
}

void FilesPane::fillInstSetBoxes(){
    cbxInstSet1->clear();
    if(seq64.rom.getSize() == 0) return;
    if(!selindex.isValid()) return;
    if(selindex.getProperty("type", "Unsupported").toString() != "Audioseq Index"){
        lblInstSet->setText("Instrument sets (Audioseq Index only):", dontSendNotification);
        return;
    }
    if(isi_addr < 0){
        lblInstSet->setText("No Instrument Set Index defined!", dontSendNotification);
        return;
    }
    if(abi_addr < 0){
        lblInstSet->setText("No Audiobank Index defined!", dontSendNotification);
        return;
    }
    if(abi_count < 0 || abi_count >= 0x100){
        lblInstSet->setText("Invalid inst set count, probably wrong addr for Audiobank Index", dontSendNotification);
        return;
    }
    lblInstSet->setText("Instrument sets:", dontSendNotification);
    ValueTree abk_names = seq64.romdesc.getOrCreateChildWithName("audiobankidx", nullptr);
    String desc;
    ValueTree bank;
    for(int i=0; i<abi_count; i++){
        desc = ROM::hex((uint8)i);
        bank = abk_names.getChildWithProperty("index", i);
        if(bank.isValid()){
            desc += ": " + bank.getProperty("name", "[Unnamed]").toString();
        }
        cbxInstSet1->addItem(desc, cbxInstSet1->getNumItems()+1);
    }
}

bool FilesPane::isKnownFileType(String filetype){
    for(int i=0; i<cbxKFileType->getNumItems(); i++){
        if(cbxKFileType->getItemText(i).equalsIgnoreCase(filetype)) return true;
    }
    return false;
}

void FilesPane::changedIndexAddress(String indexname, int newaddress){
    if(indexname == "Audiobank Index"){
        validateIndexParams(newaddress, abi_addr, abi_count);
    }else if(indexname == "Audioseq Index"){
        validateIndexParams(newaddress, asi_addr, asi_count);
    }else if(indexname == "Sample Set Index"){
        validateIndexParams(newaddress, ssi_addr, ssi_count);
    }else if(indexname == "Instrument Set Index"){
        int16 dummy;
        validateIndexParams(newaddress, isi_addr, dummy);
    }else{
        SEQ64::say("Internal error, asked to change unknown index " + indexname + " address");
    }
}

void FilesPane::validateIndexParams(int iaddr, int32 &addr_out, int16 &count_out){
    addr_out = iaddr;
    if(iaddr < 0 || seq64.rom.getSize() <= iaddr + 4){
        count_out = -1;
    }else{
        count_out = getIndexCount(iaddr);
    }
}

int16 FilesPane::getIndexCount(uint32 iaddr){
    if((int)seq64.romdesc.getProperty("indextype", 1) == 2){
        return seq64.rom.readHalfWord(iaddr);
    }else{
        return seq64.rom.readHalfWord(iaddr+2);
    }
}

ValueTree FilesPane::getFileForIndex(String indexname){
    if(!indexname.endsWith(" Index")){
        SEQ64::say("getFileForIndex " + indexname + " is not an index file!");
        return ValueTree("error").setProperty("address", -1, nullptr);
    }
    String filetype = indexname.dropLastCharacters(6);
    ValueTree file = kfilelistnode.getChildWithProperty("type", filetype);
    if(!file.isValid()){
        SEQ64::say("No " + filetype + " file described in RomDesc");
        return ValueTree("error").setProperty("address", -2, nullptr);
    }
    if(!file.hasProperty("address")) file.setProperty("address", -3, nullptr);
    return file;
}

void FilesPane::readIEAddrLen(uint32 iaddr, int entry, uint32 &address, uint32 &length){
    if((int)seq64.romdesc.getProperty("indextype", 1) == 2){
        address = seq64.rom.readWord(iaddr + (16*entry) + 16);
        length = seq64.rom.readWord(iaddr + (16*entry) + 20);
    }else{
        address = seq64.rom.readWord(iaddr + (8*entry) + 4);
        length = seq64.rom.readWord(iaddr + (8*entry) + 8);
    }
}

void FilesPane::writeIEAddr(uint32 iaddr, int entry, uint32 address){
    if((int)seq64.romdesc.getProperty("indextype", 1) == 2){
        seq64.rom.writeWord(iaddr + (16*entry) + 16, address);
    }else{
        seq64.rom.writeWord(iaddr + (8*entry) + 4, address);
    }
}

void FilesPane::writeIELen(uint32 iaddr, int entry, uint32 length){
    if((int)seq64.romdesc.getProperty("indextype", 1) == 2){
        seq64.rom.writeWord(iaddr + (16*entry) + 20, length);
    }else{
        seq64.rom.writeWord(iaddr + (8*entry) + 8, length);
    }
}

bool FilesPane::getIndexAndFileParams(int32 &ilen, int32 &faddr, String &indexname, String &filename){
    if(!selindex.isValid()){
        SEQ64::say("Must select index file");
        return false;
    }
    indexname = selindex.getProperty("type", "Unsupported").toString();
    filename = indexname.dropLastCharacters(6);
    if(indexname != "Audioseq Index" && indexname != "Audiobank Index"){
        SEQ64::say("Must select Audiobank Index or Audioseq Index");
        return false;
    }
    if(indexaddr < 0 || indexcount <= 0 || indexcount > 1000){
        SEQ64::say("Invalid index properties!");
        return false;
    }
    ValueTree file = getFileForIndex(indexname);
    faddr = file.getProperty("address", -1);
    if(faddr < 0){
        SEQ64::say("Invalid companion file address!");
        return false;
    }
    return true;
}

///Get address of first nonzero after the end of this file, with some caveats
int FilesPane::getFileRealEnd(int knownend){
    int realend;
    for(realend = knownend; realend < seq64.rom.getSize(); ++realend){
        if(seq64.rom.readByte(realend) != 0) break;
    }
    realend = (realend >> 4) << 4;
    if(knownend > realend) realend = knownend;
    return realend;
}

uint32 FilesPane::getRealEntrySize(int i){
    uint32 iaddr, ilen, addr, len;
    readIEAddrLen(indexaddr, i, iaddr, ilen);
    uint32 realend = getFileRealEnd(dataaddr+iaddr+ilen) - dataaddr; //Real end within the file
    for(int j=0; j<indexcount; ++j){
        if(j==i) continue;
        readIEAddrLen(indexaddr, j, addr, len);
        if(len == 0) continue;
        if(addr > iaddr && addr < realend){
            realend = addr;
        }
    }
    return realend-iaddr;
}

//TODO this assumes all objects are within their corresponding file!
//(E.g. all sequences within Audioseq rather than tacked on randomly at the end
//of the ROM)
int FilesPane::getLastObjectEnd(int32 faddr){
    int lastobjectend = faddr;
    for(int i=0; i<indexcount; ++i){
        uint32 oaddr, olen;
        readIEAddrLen(indexaddr, i, oaddr, olen);
        if(olen == 0) continue;
        int dend = oaddr + olen + faddr;
        if(dend > lastobjectend) lastobjectend = dend;
    }
    return lastobjectend;
}

void FilesPane::moveRestOfFile(uint32 faddr, int32 flen, int32 dstart, int32 delta){
    uint8* fileptr = &((uint8*)seq64.rom.getData())[faddr];
    memmove(&fileptr[dstart+delta], &fileptr[dstart], flen - dstart);
    uint32 zstart = delta > 0 ? dstart : flen+delta;
    memset(&fileptr[zstart], 0, abs(delta)); //Zero region moved out of
    //Adjust later addresses in table
    for(int i=0; i<indexcount; ++i){
        uint32 oaddr, olen;
        readIEAddrLen(indexaddr, i, oaddr, olen);
        if(olen == 0) continue;
        if(oaddr >= dstart && oaddr < flen){
            writeIEAddr(indexaddr, i, oaddr+delta);
        }
    }
}

bool FilesPane::updateFileLength(String filename, int32 faddr, int32 flen){
    ValueTree kfile = kfilelistnode.getChildWithProperty(Identifier("type"), filename);
    if(!kfile.isValid()){
        SEQ64::say("Internal error updating file length");
        return false;
    }
    //Update file length in RomDesc
    kfile.setProperty("length", (int)flen, nullptr);
    if((bool)kfile.getProperty("from_ft", false)){
        //Update file length in MFT
        if(ftaddr <= 0 || ftaddr > seq64.rom.getSize()){
            SEQ64::say("Invalid Master File Table");
            return false;
        }
        int ftindex = kfile.getProperty("ftindex", -1);
        if(ftindex < 0){
            SEQ64::say("Invalid entry in Master File Table");
            return false;
        }
        //Sanity check
        if(seq64.rom.readWord(ftaddr + 0x10*ftindex) != faddr){
            SEQ64::say("Internal error editing Master File Table");
            return false;
        }
        seq64.rom.writeWord(ftaddr + 0x10*ftindex + 0x04, faddr + flen);
        SEQ64::say("Updated file length in MFT to 0x" + ROM::hex((uint32)flen, 6));
        fillFileTable();
    }
    return true;
}

bool FilesPane::compact(){
    int possibleend, realend;
    int32 ilen, faddr, flen;
    String indexname, filename;
    int itype = (int)seq64.romdesc.getProperty("indextype", 1);
    if(!getIndexAndFileParams(ilen, faddr, indexname, filename)) return false;
    //Minimize lengths of each bank/sequence
    for(int i=0; i<indexcount; ++i){
        uint32 oaddr, olen;
        readIEAddrLen(indexaddr, i, oaddr, olen);
        if(olen == 0) continue;
        for(realend=oaddr+olen+faddr-1; realend>=0; --realend){
            if(seq64.rom.readByte(realend) != 0) break;
        }
        ++realend; //Address after nonzero byte
        realend = ((realend + 15) >> 4) << 4; //Round up to multiple of 16
        if(oaddr+olen+faddr < realend){
            //We've actually grown the object instead--make sure we didn't
            //round up over someone else's data
            for(int b=oaddr+olen+faddr; b<realend; ++b){
                if(seq64.rom.readByte(b) != 0){
                    realend = b;
                    break;
                }
            }
        }
        if(oaddr+olen+faddr != realend){
            SEQ64::say("Changed length of item " + String(i) + " from 0x"
                    + ROM::hex(olen, 6) + " to 0x" + ROM::hex(realend-oaddr-faddr, 6));
        }
        writeIELen(indexaddr, i, realend-oaddr-faddr);
    }
    //Get actual lengths of both (i.e. length until later non-zero data)
    if(itype == 2){
        possibleend = indexaddr + 16 + (16*indexcount);
    }else{
        possibleend = indexaddr + 4 + (8*indexcount);
    }
    ilen = getFileRealEnd(possibleend) - indexaddr;
    SEQ64::say(indexname + ": minimum len 0x" + ROM::hex((uint32)(possibleend - indexaddr))
            + ", maximum len 0x"+ ROM::hex((uint32)ilen));
    //
    possibleend = getLastObjectEnd(faddr); //Find end of last bank/sequence
    flen = getFileRealEnd(possibleend) - faddr;
    SEQ64::say(filename + " file: minimum len 0x" + ROM::hex((uint32)(possibleend - faddr))
            + ", maximum len 0x"+ ROM::hex((uint32)flen));
    //Compact
    int a = 0;
    if(indexaddr == faddr) a = ilen; //Mario 64 format, don't clobber the index!
    while(a < flen){
        //Move to the next space not taken by any object
        for(int i=0; i<indexcount; ++i){
            uint32 oaddr, olen;
            readIEAddrLen(indexaddr, i, oaddr, olen);
            if(olen == 0) continue;
            if(a >= oaddr && a < oaddr + olen){
                a = oaddr + olen;
                a = ((a + 15) >> 4) << 4; //round up
                i = -1; //Restart search through objects
            }
        }
        if(a >= flen) break;
        //Compute empty space to next object
        int nextoaddr = 1000000000;
        for(int i=0; i<indexcount; ++i){
            uint32 oaddr, olen;
            readIEAddrLen(indexaddr, i, oaddr, olen);
            if(olen == 0) continue;
            if(oaddr >= a && oaddr < nextoaddr){
                nextoaddr = oaddr;
            }
        }
        if(nextoaddr >= flen){
            SEQ64::say("0x" + ROM::hex((uint32)(flen - a), 6) + " bytes empty at end");
            flen = a;
            break;
        }
        int delta = nextoaddr - a;
        if(delta <= 0){
            SEQ64::say("Internal error when compacting");
            return false;
        }
        SEQ64::say("Compacting away 0x" + ROM::hex((uint32)delta, 6) + " bytes of space");
        //Move later part of file down
        moveRestOfFile(faddr, flen, nextoaddr, -delta);
    }
    fillIndex();
    if(!updateFileLength(filename, faddr, flen)) return false;
    return true;
}

int FilesPane::makeroom(int mrlen){
    int32 ilen, faddr;
    String indexname, filename;
    if(!getIndexAndFileParams(ilen, faddr, indexname, filename)) return -1;
    //Get object params
    if(ientryidx < 0){
        SEQ64::say("No index entry selected!");
        return -1;
    }
    uint32 oaddr, olen;
    readIEAddrLen(indexaddr, ientryidx, oaddr, olen);
    if(olen >= mrlen){
        SEQ64::say("Asked to make room for entry " + String(ientryidx) + " to be 0x"
                + ROM::hex((uint32)mrlen, 6) + " bytes, but it's already "
                + ROM::hex(olen, 6) + " bytes");
        return -1;
    }
    //Get file params
    int lastobjectend = getLastObjectEnd(faddr); //Find end of last bank/sequence
    int realend = getFileRealEnd(lastobjectend);
    if(realend - lastobjectend < mrlen - olen){
        SEQ64::say("Need 0x" + ROM::hex((uint32)(mrlen - olen), 6)
                + " bytes empty space to make room, but there are only 0x"
                + ROM::hex((uint32)(realend - lastobjectend), 6) + " bytes empty at the end of "
                + filename + " file");
        return 0;
    }
    //Move data
    SEQ64::say("Inserting 0x" + ROM::hex((uint32)(mrlen-olen), 6) + " bytes empty space @"
            + ROM::hex((uint32)(oaddr+olen), 6));
    moveRestOfFile(faddr, lastobjectend-faddr, oaddr+olen, mrlen-olen);
    if(!updateFileLength(filename, faddr, lastobjectend-faddr+mrlen-olen)) return -1;
    fillIndex();
    return 1;
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="FilesPane" componentName=""
                 parentClasses="public Component, public TextEditor::Listener, public TextListModel::Listener"
                 constructorParams="SEQ64&amp; seq64_" variableInitialisers="seq64(seq64_)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
  <GROUPCOMPONENT name="new group" id="cad85c65a6c70aec" memberName="grpUtilities"
                  virtualName="" explicitFocusOrder="0" pos="760 0 272 200" title="Utilities"/>
  <GROUPCOMPONENT name="new group" id="50f8d472e934f3ad" memberName="grpUtilitiesContents"
                  virtualName="" explicitFocusOrder="0" pos="768 48 256 96" title="Contents"/>
  <GROUPCOMPONENT name="new group" id="da1838da4937cc20" memberName="grpMFT" virtualName=""
                  explicitFocusOrder="0" pos="0 0 336 448" title="Master File Table"/>
  <LABEL name="new label" id="feac5e6d64dda05e" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="8 16 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Address:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="b0f34b76891a115d" memberName="txtFTAddr"
              virtualName="" explicitFocusOrder="0" pos="80 16 80 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="9d8b9b46e68c2983" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="8 392 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Name:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="baf4f79779fe44c6" memberName="txtFileName"
              virtualName="" explicitFocusOrder="0" pos="64 392 264 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="5e17f0c7cbf49c52" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="8 416 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Type:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <COMBOBOX name="new combo box" id="a982a2bb18b425a6" memberName="cbxFileType"
            virtualName="" explicitFocusOrder="0" pos="64 416 264 24" editable="0"
            layout="33" items="Unknown&#10;ROM Header&#10;Boot Code&#10;Master File Table&#10;Audiobank&#10;Audioseq&#10;Audiotable&#10;Code&#10;Texture&#10;Shared Assets&#10;Text Data&#10;Actor&#10;Object&#10;Scene&#10;Room&#10;Other"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="f2833c68aa3a69c3" memberName="label4" virtualName=""
         explicitFocusOrder="0" pos="8 368 320 24" edTextCol="ff000000"
         edBkgCol="0" labelText="[Address information]" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <GROUPCOMPONENT name="new group" id="f59a75502f6f9763" memberName="grpKnownFiles"
                  virtualName="" explicitFocusOrder="0" pos="0 448 336 264" title="Known Files"/>
  <TEXTBUTTON name="new button" id="20b0109f8e92d22a" memberName="btnKFileAdd"
              virtualName="" explicitFocusOrder="0" pos="8 624 40 24" buttonText="Add"
              connectedEdges="2" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="5eceeff61cabc54a" memberName="btnKFileDel"
              virtualName="" explicitFocusOrder="0" pos="48 624 40 24" buttonText="Del"
              connectedEdges="1" needsCallback="1" radioGroupId="0"/>
  <LABEL name="new label" id="3b17daf4620f7036" memberName="label5" virtualName=""
         explicitFocusOrder="0" pos="96 624 47 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Type:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <COMBOBOX name="new combo box" id="dba63b9be0a5c57" memberName="cbxKFileType"
            virtualName="" explicitFocusOrder="0" pos="144 624 184 24" editable="0"
            layout="33" items="Unsupported&#10;Audiobank&#10;Audioseq&#10;Audiotable&#10;Audiobank Index&#10;Audioseq Index&#10;Sample Set Index&#10;Instrument Set Index"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="1756f94b14c6940f" memberName="label6" virtualName=""
         explicitFocusOrder="0" pos="176 656 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Address:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="e1d35d2b85f2de9a" memberName="txtKFileAddr"
              virtualName="" explicitFocusOrder="0" pos="248 656 80 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="29eda2beea4f4f73" memberName="label7" virtualName=""
         explicitFocusOrder="0" pos="176 680 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Length:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="f3befab09a65150a" memberName="txtKFileLength"
              virtualName="" explicitFocusOrder="0" pos="248 680 80 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <GROUPCOMPONENT name="new group" id="a707e7b9cb5e40a2" memberName="grpIndex"
                  virtualName="" explicitFocusOrder="0" pos="336 0 424 712" title="Index"/>
  <LABEL name="new label" id="5c4f6c4947dd2650" memberName="lblIndexProps"
         virtualName="" explicitFocusOrder="0" pos="344 88 408 24" edTextCol="ff000000"
         edBkgCol="0" labelText="[Index length, address, etc.]" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="5d02266efa726b59" memberName="label11" virtualName=""
         explicitFocusOrder="0" pos="344 472 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Name:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="d2ccdddf01b27ef0" memberName="txtIEntryName"
              virtualName="" explicitFocusOrder="0" pos="400 472 352 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="750191ec030e4bcc" memberName="lblIEntryData"
         virtualName="" explicitFocusOrder="0" pos="344 448 408 24" edTextCol="ff000000"
         edBkgCol="0" labelText="[Entry data]" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="new button" id="c6f7b2138260d81d" memberName="btnLoadEntry"
              virtualName="" explicitFocusOrder="0" pos="344 504 136 24" buttonText="Load Entry"
              connectedEdges="8" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="93eb02f5f765bd07" memberName="btnSaveEntry"
              virtualName="" explicitFocusOrder="0" pos="344 528 136 24" buttonText="Save Entry"
              connectedEdges="4" needsCallback="1" radioGroupId="0"/>
  <GROUPCOMPONENT name="new group" id="9f0f9c0355363fa1" memberName="groupComponent4"
                  virtualName="" explicitFocusOrder="0" pos="344 16 408 72" title="Index Format"/>
  <TOGGLEBUTTON name="new toggle button" id="b9de436f2f2f8a29" memberName="optIndexType1"
                virtualName="" explicitFocusOrder="0" pos="352 32 392 24" buttonText="Word hdr; [addr, length] (SM64, MK64)"
                connectedEdges="0" needsCallback="1" radioGroupId="1" state="1"/>
  <TOGGLEBUTTON name="new toggle button" id="c28e8c6e3b30311f" memberName="optIndexType2"
                virtualName="" explicitFocusOrder="0" pos="352 56 392 24" buttonText="4-word hdr; [addr, length, 2 data] (Zelda, Yoshi)"
                connectedEdges="0" needsCallback="1" radioGroupId="1" state="0"/>
  <LABEL name="new label" id="52709144fcf447d1" memberName="lblInstSet"
         virtualName="" explicitFocusOrder="0" pos="344 560 408 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Instrument sets:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="6d5d89e6ea22ae4c" memberName="label10" virtualName=""
         explicitFocusOrder="0" pos="344 680 40 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Set:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <COMBOBOX name="new combo box" id="eb9c8b0efed24a37" memberName="cbxInstSet1"
            virtualName="" explicitFocusOrder="0" pos="384 680 368 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <TEXTBUTTON name="new button" id="d6765357ec4aae16" memberName="btnEditIE"
              virtualName="" explicitFocusOrder="0" pos="536 504 214 24" buttonText="Edit Index Entry (Metadata)"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="149a5c2bee6bc8fe" memberName="btnCompact"
              virtualName="" explicitFocusOrder="0" pos="768 16 256 24" buttonText="Compact"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="7a397ef5edfd6693" memberName="btnMakeRoom"
              virtualName="" explicitFocusOrder="0" pos="936 88 80 24" buttonText="Make Room"
              connectedEdges="1" needsCallback="1" radioGroupId="0"/>
  <LABEL name="new label" id="e875322d507e6967" memberName="label8" virtualName=""
         explicitFocusOrder="0" pos="776 88 120 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Make room for 0x" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="e3b2c158d9a94abc" memberName="txtMakeRoom"
              virtualName="" explicitFocusOrder="0" pos="896 88 40 24" initialText="1000"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTBUTTON name="new button" id="eebbc4936a2263c0" memberName="btnContentsCreate"
              virtualName="" explicitFocusOrder="0" pos="776 64 120 24" buttonText="Create"
              connectedEdges="2" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="f2d02ac2da1cc4fa" memberName="btnContentsDestroy"
              virtualName="" explicitFocusOrder="0" pos="896 64 120 24" buttonText="Destroy/Pointerize"
              connectedEdges="1" needsCallback="1" radioGroupId="0"/>
  <LABEL name="new label" id="ca1b76b48fec52a9" memberName="label9" virtualName=""
         explicitFocusOrder="0" pos="776 112 128 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Pointer to entry: 0x" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="7d6faed50a54f538" memberName="txtEntryPointer"
              virtualName="" explicitFocusOrder="0" pos="904 112 32 24" initialText="00"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <GROUPCOMPONENT name="new group" id="e0ed18b4290a5f40" memberName="grpUtilitiesEntry"
                  virtualName="" explicitFocusOrder="0" pos="768 144 256 48" title="Entry"/>
  <TEXTBUTTON name="new button" id="5b41d2756e95ddc0" memberName="btnEntryInsert"
              virtualName="" explicitFocusOrder="0" pos="856 160 80 24" buttonText="Insert"
              connectedEdges="3" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="35c4626e95ba90e" memberName="btnEntryAdd"
              virtualName="" explicitFocusOrder="0" pos="776 160 80 24" buttonText="Add"
              connectedEdges="2" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="77ead61af32390ed" memberName="btnEntryDelete"
              virtualName="" explicitFocusOrder="0" pos="936 160 80 24" buttonText="Delete"
              connectedEdges="1" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

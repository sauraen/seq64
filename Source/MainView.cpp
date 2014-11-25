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

//[Headers] You can add your own extra header files here...
#include "ROM.h"
#include "SeqFile.h"
#include "AppProps.h"
//[/Headers]

#include "MainView.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MainView::MainView ()
    : romdesc(Identifier("RomDesc"))
{
    addAndMakeVisible (groupComponent7 = new GroupComponent ("new group",
                                                             TRANS("MIDI File")));
    groupComponent7->setTextLabelPosition (Justification::centredRight);

    addAndMakeVisible (groupComponent4 = new GroupComponent ("new group",
                                                             TRANS("Sequence File")));
    groupComponent4->setTextLabelPosition (Justification::centredLeft);

    addAndMakeVisible (groupComponent3 = new GroupComponent ("new group",
                                                             TRANS("Command Editor")));

    addAndMakeVisible (groupComponent6 = new GroupComponent ("new group",
                                                             TRANS("Edit Parameter")));

    addAndMakeVisible (groupComponent5 = new GroupComponent ("new group",
                                                             TRANS("Valid in")));

    addAndMakeVisible (groupComponent2 = new GroupComponent ("new group",
                                                             TRANS("ROM")));

    addAndMakeVisible (groupComponent = new GroupComponent ("new group",
                                                            TRANS("ROM Description (addr hex, index dec)")));

    addAndMakeVisible (btnLoadRom = new TextButton ("Load ROM"));
    btnLoadRom->setButtonText (TRANS("Load"));
    btnLoadRom->setConnectedEdges (Button::ConnectedOnRight);
    btnLoadRom->addListener (this);

    addAndMakeVisible (btnSaveROM = new TextButton ("Save ROM"));
    btnSaveROM->setButtonText (TRANS("Save"));
    btnSaveROM->setConnectedEdges (Button::ConnectedOnLeft);
    btnSaveROM->addListener (this);

    addAndMakeVisible (btnLoadDesc = new TextButton ("Load ROM"));
    btnLoadDesc->setButtonText (TRANS("Load"));
    btnLoadDesc->setConnectedEdges (Button::ConnectedOnBottom);
    btnLoadDesc->addListener (this);

    addAndMakeVisible (btnSaveDesc = new TextButton ("Save ROM"));
    btnSaveDesc->setButtonText (TRANS("Save"));
    btnSaveDesc->setConnectedEdges (Button::ConnectedOnTop);
    btnSaveDesc->addListener (this);

    addAndMakeVisible (label2 = new Label ("new label",
                                           TRANS("File table addr:")));
    label2->setFont (Font (15.00f, Font::plain));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (txtFTAddr = new TextEditor ("new text editor"));
    txtFTAddr->setMultiLine (false);
    txtFTAddr->setReturnKeyStartsNewLine (false);
    txtFTAddr->setReadOnly (false);
    txtFTAddr->setScrollbarsShown (true);
    txtFTAddr->setCaretVisible (true);
    txtFTAddr->setPopupMenuEnabled (false);
    txtFTAddr->setText (String::empty);

    addAndMakeVisible (label3 = new Label ("new label",
                                           TRANS("Audiobank file index:")));
    label3->setFont (Font (15.00f, Font::plain));
    label3->setJustificationType (Justification::centredLeft);
    label3->setEditable (false, false, false);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (txtABFIndex = new TextEditor ("new text editor"));
    txtABFIndex->setMultiLine (false);
    txtABFIndex->setReturnKeyStartsNewLine (false);
    txtABFIndex->setReadOnly (false);
    txtABFIndex->setScrollbarsShown (true);
    txtABFIndex->setCaretVisible (true);
    txtABFIndex->setPopupMenuEnabled (false);
    txtABFIndex->setText (TRANS("0"));

    addAndMakeVisible (label4 = new Label ("new label",
                                           TRANS("Audioseq file index:")));
    label4->setFont (Font (15.00f, Font::plain));
    label4->setJustificationType (Justification::centredLeft);
    label4->setEditable (false, false, false);
    label4->setColour (TextEditor::textColourId, Colours::black);
    label4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (txtASFIndex = new TextEditor ("new text editor"));
    txtASFIndex->setMultiLine (false);
    txtASFIndex->setReturnKeyStartsNewLine (false);
    txtASFIndex->setReadOnly (false);
    txtASFIndex->setScrollbarsShown (true);
    txtASFIndex->setCaretVisible (true);
    txtASFIndex->setPopupMenuEnabled (false);
    txtASFIndex->setText (TRANS("0"));

    addAndMakeVisible (label5 = new Label ("new label",
                                           TRANS("Audiotable file index:")));
    label5->setFont (Font (15.00f, Font::plain));
    label5->setJustificationType (Justification::centredLeft);
    label5->setEditable (false, false, false);
    label5->setColour (TextEditor::textColourId, Colours::black);
    label5->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (txtATFIndex = new TextEditor ("new text editor"));
    txtATFIndex->setMultiLine (false);
    txtATFIndex->setReturnKeyStartsNewLine (false);
    txtATFIndex->setReadOnly (false);
    txtATFIndex->setScrollbarsShown (true);
    txtATFIndex->setCaretVisible (true);
    txtATFIndex->setPopupMenuEnabled (false);
    txtATFIndex->setText (TRANS("0"));

    addAndMakeVisible (lblABFAddr = new Label ("new label",
                                               TRANS("addr: ")));
    lblABFAddr->setFont (Font (15.00f, Font::plain));
    lblABFAddr->setJustificationType (Justification::centredLeft);
    lblABFAddr->setEditable (false, false, false);
    lblABFAddr->setColour (TextEditor::textColourId, Colours::black);
    lblABFAddr->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (lblASFAddr = new Label ("new label",
                                               TRANS("addr: ")));
    lblASFAddr->setFont (Font (15.00f, Font::plain));
    lblASFAddr->setJustificationType (Justification::centredLeft);
    lblASFAddr->setEditable (false, false, false);
    lblASFAddr->setColour (TextEditor::textColourId, Colours::black);
    lblASFAddr->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (lblATFAddr = new Label ("new label",
                                               TRANS("addr: ")));
    lblATFAddr->setFont (Font (15.00f, Font::plain));
    lblATFAddr->setJustificationType (Justification::centredLeft);
    lblATFAddr->setEditable (false, false, false);
    lblATFAddr->setColour (TextEditor::textColourId, Colours::black);
    lblATFAddr->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label6 = new Label ("new label",
                                           TRANS("Audiobank table addr:")));
    label6->setFont (Font (15.00f, Font::plain));
    label6->setJustificationType (Justification::centredLeft);
    label6->setEditable (false, false, false);
    label6->setColour (TextEditor::textColourId, Colours::black);
    label6->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (txtABTAddr = new TextEditor ("new text editor"));
    txtABTAddr->setMultiLine (false);
    txtABTAddr->setReturnKeyStartsNewLine (false);
    txtABTAddr->setReadOnly (false);
    txtABTAddr->setScrollbarsShown (true);
    txtABTAddr->setCaretVisible (true);
    txtABTAddr->setPopupMenuEnabled (false);
    txtABTAddr->setText (String::empty);

    addAndMakeVisible (label7 = new Label ("new label",
                                           TRANS("Audioseq table addr:")));
    label7->setFont (Font (15.00f, Font::plain));
    label7->setJustificationType (Justification::centredLeft);
    label7->setEditable (false, false, false);
    label7->setColour (TextEditor::textColourId, Colours::black);
    label7->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (txtASTAddr = new TextEditor ("new text editor"));
    txtASTAddr->setMultiLine (false);
    txtASTAddr->setReturnKeyStartsNewLine (false);
    txtASTAddr->setReadOnly (false);
    txtASTAddr->setScrollbarsShown (true);
    txtASTAddr->setCaretVisible (true);
    txtASTAddr->setPopupMenuEnabled (false);
    txtASTAddr->setText (String::empty);

    addAndMakeVisible (label8 = new Label ("new label",
                                           TRANS("Sample set table addr:")));
    label8->setFont (Font (15.00f, Font::plain));
    label8->setJustificationType (Justification::centredLeft);
    label8->setEditable (false, false, false);
    label8->setColour (TextEditor::textColourId, Colours::black);
    label8->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (txtSSTAddr = new TextEditor ("new text editor"));
    txtSSTAddr->setMultiLine (false);
    txtSSTAddr->setReturnKeyStartsNewLine (false);
    txtSSTAddr->setReadOnly (false);
    txtSSTAddr->setScrollbarsShown (true);
    txtSSTAddr->setCaretVisible (true);
    txtSSTAddr->setPopupMenuEnabled (false);
    txtSSTAddr->setText (String::empty);

    addAndMakeVisible (lblABTSize = new Label ("new label",
                                               TRANS("sz: ")));
    lblABTSize->setFont (Font (15.00f, Font::plain));
    lblABTSize->setJustificationType (Justification::centredLeft);
    lblABTSize->setEditable (false, false, false);
    lblABTSize->setColour (TextEditor::textColourId, Colours::black);
    lblABTSize->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (lblASTSize = new Label ("new label",
                                               TRANS("sz: ")));
    lblASTSize->setFont (Font (15.00f, Font::plain));
    lblASTSize->setJustificationType (Justification::centredLeft);
    lblASTSize->setEditable (false, false, false);
    lblASTSize->setColour (TextEditor::textColourId, Colours::black);
    lblASTSize->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (lblSSTSize = new Label ("new label",
                                               TRANS("sz: ")));
    lblSSTSize->setFont (Font (15.00f, Font::plain));
    lblSSTSize->setJustificationType (Justification::centredLeft);
    lblSSTSize->setEditable (false, false, false);
    lblSSTSize->setColour (TextEditor::textColourId, Colours::black);
    lblSSTSize->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (lblROMFile = new Label ("new label",
                                               TRANS("[ROM Filename]")));
    lblROMFile->setFont (Font (15.00f, Font::plain));
    lblROMFile->setJustificationType (Justification::centredLeft);
    lblROMFile->setEditable (false, false, false);
    lblROMFile->setColour (TextEditor::textColourId, Colours::black);
    lblROMFile->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (btnABTView = new TextButton ("Load ROM"));
    btnABTView->setButtonText (TRANS("View"));
    btnABTView->setConnectedEdges (Button::ConnectedOnBottom);
    btnABTView->addListener (this);

    addAndMakeVisible (btnASTView = new TextButton ("Load ROM"));
    btnASTView->setButtonText (TRANS("View"));
    btnASTView->setConnectedEdges (Button::ConnectedOnTop | Button::ConnectedOnBottom);
    btnASTView->addListener (this);

    addAndMakeVisible (btnSSTView = new TextButton ("Load ROM"));
    btnSSTView->setButtonText (TRANS("View"));
    btnSSTView->setConnectedEdges (Button::ConnectedOnTop);
    btnSSTView->addListener (this);

    addAndMakeVisible (lblTableName = new Label ("new label",
                                                 TRANS("[Name of table]")));
    lblTableName->setFont (Font (15.00f, Font::plain));
    lblTableName->setJustificationType (Justification::centredLeft);
    lblTableName->setEditable (false, false, false);
    lblTableName->setColour (TextEditor::textColourId, Colours::black);
    lblTableName->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label10 = new Label ("new label",
                                            TRANS("Command:")));
    label10->setFont (Font (15.00f, Font::plain));
    label10->setJustificationType (Justification::centredLeft);
    label10->setEditable (false, false, false);
    label10->setColour (TextEditor::textColourId, Colours::black);
    label10->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (txtCmd = new TextEditor ("new text editor"));
    txtCmd->setMultiLine (false);
    txtCmd->setReturnKeyStartsNewLine (false);
    txtCmd->setReadOnly (false);
    txtCmd->setScrollbarsShown (true);
    txtCmd->setCaretVisible (true);
    txtCmd->setPopupMenuEnabled (true);
    txtCmd->setText (String::empty);

    addAndMakeVisible (btnCmdAdd = new TextButton ("new button"));
    btnCmdAdd->setButtonText (TRANS("Add"));
    btnCmdAdd->setConnectedEdges (Button::ConnectedOnBottom);
    btnCmdAdd->addListener (this);

    addAndMakeVisible (btnCmdDel = new TextButton ("new button"));
    btnCmdDel->setButtonText (TRANS("Del"));
    btnCmdDel->setConnectedEdges (Button::ConnectedOnTop);
    btnCmdDel->addListener (this);

    addAndMakeVisible (optCmdDataFixed = new ToggleButton ("new toggle button"));
    optCmdDataFixed->setButtonText (TRANS("Fixed"));
    optCmdDataFixed->setRadioGroupId (1);
    optCmdDataFixed->addListener (this);
    optCmdDataFixed->setToggleState (true, dontSendNotification);

    addAndMakeVisible (optCmdDataVar = new ToggleButton ("new toggle button"));
    optCmdDataVar->setButtonText (TRANS("Variable"));
    optCmdDataVar->setRadioGroupId (1);
    optCmdDataVar->addListener (this);

    addAndMakeVisible (lblCmdDataSize = new Label ("new label",
                                                   TRANS("length")));
    lblCmdDataSize->setFont (Font (15.00f, Font::plain));
    lblCmdDataSize->setJustificationType (Justification::centredLeft);
    lblCmdDataSize->setEditable (false, false, false);
    lblCmdDataSize->setColour (TextEditor::textColourId, Colours::black);
    lblCmdDataSize->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (txtCmdDataSize = new TextEditor ("txtCmdDat"));
    txtCmdDataSize->setMultiLine (false);
    txtCmdDataSize->setReturnKeyStartsNewLine (false);
    txtCmdDataSize->setReadOnly (false);
    txtCmdDataSize->setScrollbarsShown (true);
    txtCmdDataSize->setCaretVisible (true);
    txtCmdDataSize->setPopupMenuEnabled (true);
    txtCmdDataSize->setText (TRANS("1"));

    addAndMakeVisible (label11 = new Label ("new label",
                                            TRANS("(dec)")));
    label11->setFont (Font (15.00f, Font::plain));
    label11->setJustificationType (Justification::centredLeft);
    label11->setEditable (false, false, false);
    label11->setColour (TextEditor::textColourId, Colours::black);
    label11->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("Action:")));
    label->setFont (Font (15.00f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (cbxAction = new ComboBox ("Action"));
    cbxAction->setEditableText (false);
    cbxAction->setJustificationType (Justification::centredLeft);
    cbxAction->setTextWhenNothingSelected (String::empty);
    cbxAction->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    cbxAction->addItem (TRANS("No Action"), 1);
    cbxAction->addItem (TRANS("End of Data"), 2);
    cbxAction->addItem (TRANS("Timestamp"), 3);
    cbxAction->addItem (TRANS("Ptr Channel Header"), 4);
    cbxAction->addItem (TRANS("Ptr Loop Start"), 5);
    cbxAction->addItem (TRANS("Ptr Track Data"), 6);
    cbxAction->addItem (TRANS("Ptr More Track Data"), 7);
    cbxAction->addItem (TRANS("Master Volume"), 8);
    cbxAction->addItem (TRANS("Tempo"), 9);
    cbxAction->addItem (TRANS("Chn Priority"), 10);
    cbxAction->addItem (TRANS("Chn Volume"), 11);
    cbxAction->addItem (TRANS("Chn Pan"), 12);
    cbxAction->addItem (TRANS("Chn Effects"), 13);
    cbxAction->addItem (TRANS("Chn Vibrato"), 14);
    cbxAction->addItem (TRANS("Chn Pitch Bend"), 15);
    cbxAction->addItem (TRANS("Chn Instrument"), 16);
    cbxAction->addItem (TRANS("Transpose"), 17);
    cbxAction->addItem (TRANS("Track Note"), 18);
    cbxAction->addListener (this);

    addAndMakeVisible (label9 = new Label ("new label",
                                           TRANS("Name:")));
    label9->setFont (Font (15.00f, Font::plain));
    label9->setJustificationType (Justification::centredLeft);
    label9->setEditable (false, false, false);
    label9->setColour (TextEditor::textColourId, Colours::black);
    label9->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (txtCmdName = new TextEditor ("new text editor"));
    txtCmdName->setMultiLine (false);
    txtCmdName->setReturnKeyStartsNewLine (false);
    txtCmdName->setReadOnly (false);
    txtCmdName->setScrollbarsShown (true);
    txtCmdName->setCaretVisible (true);
    txtCmdName->setPopupMenuEnabled (true);
    txtCmdName->setText (String::empty);

    addAndMakeVisible (txtCmdEnd = new TextEditor ("new text editor"));
    txtCmdEnd->setMultiLine (false);
    txtCmdEnd->setReturnKeyStartsNewLine (false);
    txtCmdEnd->setReadOnly (false);
    txtCmdEnd->setScrollbarsShown (true);
    txtCmdEnd->setCaretVisible (true);
    txtCmdEnd->setPopupMenuEnabled (true);
    txtCmdEnd->setText (String::empty);

    addAndMakeVisible (label12 = new Label ("new label",
                                            TRANS("to")));
    label12->setFont (Font (15.00f, Font::plain));
    label12->setJustificationType (Justification::centredLeft);
    label12->setEditable (false, false, false);
    label12->setColour (TextEditor::textColourId, Colours::black);
    label12->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (optCmdSeq = new ToggleButton ("new toggle button"));
    optCmdSeq->setButtonText (TRANS("Seq header"));
    optCmdSeq->addListener (this);

    addAndMakeVisible (optCmdChn = new ToggleButton ("new toggle button"));
    optCmdChn->setButtonText (TRANS("Chn header"));
    optCmdChn->addListener (this);

    addAndMakeVisible (optCmdTrk = new ToggleButton ("new toggle button"));
    optCmdTrk->setButtonText (TRANS("Track data"));
    optCmdTrk->addListener (this);

    addAndMakeVisible (label13 = new Label ("new label",
                                            TRANS("Parameters:")));
    label13->setFont (Font (15.00f, Font::plain));
    label13->setJustificationType (Justification::centredLeft);
    label13->setEditable (false, false, false);
    label13->setColour (TextEditor::textColourId, Colours::black);
    label13->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (btnParamAdd = new TextButton ("new button"));
    btnParamAdd->setButtonText (TRANS("Add"));
    btnParamAdd->setConnectedEdges (Button::ConnectedOnBottom);
    btnParamAdd->addListener (this);

    addAndMakeVisible (btnParamDel = new TextButton ("new button"));
    btnParamDel->setButtonText (TRANS("Del"));
    btnParamDel->setConnectedEdges (Button::ConnectedOnTop);
    btnParamDel->addListener (this);

    addAndMakeVisible (btnParamUp = new TextButton ("new button"));
    btnParamUp->setButtonText (TRANS("Up"));
    btnParamUp->setConnectedEdges (Button::ConnectedOnBottom);
    btnParamUp->addListener (this);

    addAndMakeVisible (btnParamDn = new TextButton ("new button"));
    btnParamDn->setButtonText (TRANS("Dn"));
    btnParamDn->setConnectedEdges (Button::ConnectedOnTop);
    btnParamDn->addListener (this);

    addAndMakeVisible (optCmdOffset = new ToggleButton ("new toggle button"));
    optCmdOffset->setButtonText (TRANS("Cmd Offset (no data)"));
    optCmdOffset->setRadioGroupId (1);
    optCmdOffset->addListener (this);

    addAndMakeVisible (label14 = new Label ("new label",
                                            TRANS("Data source:")));
    label14->setFont (Font (15.00f, Font::plain));
    label14->setJustificationType (Justification::centredLeft);
    label14->setEditable (false, false, false);
    label14->setColour (TextEditor::textColourId, Colours::black);
    label14->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label15 = new Label ("new label",
                                            TRANS("Meaning:")));
    label15->setFont (Font (15.00f, Font::plain));
    label15->setJustificationType (Justification::centredLeft);
    label15->setEditable (false, false, false);
    label15->setColour (TextEditor::textColourId, Colours::black);
    label15->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (txtParamName = new TextEditor ("new text editor"));
    txtParamName->setMultiLine (false);
    txtParamName->setReturnKeyStartsNewLine (false);
    txtParamName->setReadOnly (false);
    txtParamName->setScrollbarsShown (true);
    txtParamName->setCaretVisible (true);
    txtParamName->setPopupMenuEnabled (true);
    txtParamName->setText (String::empty);

    addAndMakeVisible (label16 = new Label ("new label",
                                            TRANS("Name:")));
    label16->setFont (Font (15.00f, Font::plain));
    label16->setJustificationType (Justification::centredLeft);
    label16->setEditable (false, false, false);
    label16->setColour (TextEditor::textColourId, Colours::black);
    label16->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (cbxMeaning = new ComboBox ("Meaning"));
    cbxMeaning->setEditableText (false);
    cbxMeaning->setJustificationType (Justification::centredLeft);
    cbxMeaning->setTextWhenNothingSelected (String::empty);
    cbxMeaning->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    cbxMeaning->addListener (this);

    addAndMakeVisible (label17 = new Label ("new label",
                                            TRANS("Add (dec):")));
    label17->setFont (Font (15.00f, Font::plain));
    label17->setJustificationType (Justification::centredLeft);
    label17->setEditable (false, false, false);
    label17->setColour (TextEditor::textColourId, Colours::black);
    label17->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label18 = new Label ("new label",
                                            TRANS("Multiply:")));
    label18->setFont (Font (15.00f, Font::plain));
    label18->setJustificationType (Justification::centredLeft);
    label18->setEditable (false, false, false);
    label18->setColour (TextEditor::textColourId, Colours::black);
    label18->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (txtParamAdd = new TextEditor ("new text editor"));
    txtParamAdd->setMultiLine (false);
    txtParamAdd->setReturnKeyStartsNewLine (false);
    txtParamAdd->setReadOnly (false);
    txtParamAdd->setScrollbarsShown (true);
    txtParamAdd->setCaretVisible (true);
    txtParamAdd->setPopupMenuEnabled (true);
    txtParamAdd->setText (TRANS("0"));

    addAndMakeVisible (txtParamMult = new TextEditor ("new text editor"));
    txtParamMult->setMultiLine (false);
    txtParamMult->setReturnKeyStartsNewLine (false);
    txtParamMult->setReadOnly (false);
    txtParamMult->setScrollbarsShown (true);
    txtParamMult->setCaretVisible (true);
    txtParamMult->setPopupMenuEnabled (true);
    txtParamMult->setText (TRANS("1.0"));

    addAndMakeVisible (btnCmdUp = new TextButton ("new button"));
    btnCmdUp->setButtonText (TRANS("Up"));
    btnCmdUp->setConnectedEdges (Button::ConnectedOnBottom);
    btnCmdUp->addListener (this);

    addAndMakeVisible (btnCmdDn = new TextButton ("new button"));
    btnCmdDn->setButtonText (TRANS("Dn"));
    btnCmdDn->setConnectedEdges (Button::ConnectedOnTop);
    btnCmdDn->addListener (this);

    addAndMakeVisible (btnSeq2MIDI = new TextButton ("new button"));
    btnSeq2MIDI->setButtonText (TRANS("MIDI >"));
    btnSeq2MIDI->addListener (this);

    addAndMakeVisible (btnMIDI2Seq = new TextButton ("new button"));
    btnMIDI2Seq->setButtonText (TRANS("< SEQ"));
    btnMIDI2Seq->addListener (this);

    addAndMakeVisible (btnReadSeq = new TextButton ("Read Sequence"));
    btnReadSeq->setButtonText (TRANS("Read"));
    btnReadSeq->setConnectedEdges (Button::ConnectedOnRight);
    btnReadSeq->addListener (this);

    addAndMakeVisible (btnWriteSeq = new TextButton ("Write Sequence"));
    btnWriteSeq->setButtonText (TRANS("Write"));
    btnWriteSeq->setConnectedEdges (Button::ConnectedOnLeft);
    btnWriteSeq->addListener (this);

    addAndMakeVisible (lblSeqInfo = new Label ("new label",
                                               TRANS("[File info]")));
    lblSeqInfo->setFont (Font (15.00f, Font::plain));
    lblSeqInfo->setJustificationType (Justification::centredLeft);
    lblSeqInfo->setEditable (false, false, false);
    lblSeqInfo->setColour (TextEditor::textColourId, Colours::black);
    lblSeqInfo->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (btnLoadMIDI = new TextButton ("Load MIDI"));
    btnLoadMIDI->setButtonText (TRANS("Load"));
    btnLoadMIDI->setConnectedEdges (Button::ConnectedOnRight);
    btnLoadMIDI->addListener (this);

    addAndMakeVisible (btnSaveMIDI = new TextButton ("Save MIDI"));
    btnSaveMIDI->setButtonText (TRANS("Save"));
    btnSaveMIDI->setConnectedEdges (Button::ConnectedOnLeft);
    btnSaveMIDI->addListener (this);

    addAndMakeVisible (label20 = new Label ("new label",
                                            TRANS("Placeholder")));
    label20->setFont (Font (15.00f, Font::plain));
    label20->setJustificationType (Justification::centredLeft);
    label20->setEditable (false, false, false);
    label20->setColour (TextEditor::textColourId, Colours::black);
    label20->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (cbxSeqSections = new ComboBox ("new combo box"));
    cbxSeqSections->setEditableText (false);
    cbxSeqSections->setJustificationType (Justification::centredLeft);
    cbxSeqSections->setTextWhenNothingSelected (String::empty);
    cbxSeqSections->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    cbxSeqSections->addListener (this);


    //[UserPreSize]
    lsmTable = new TextListModel();
    lsmTable->setListener(this);

    addAndMakeVisible(lstTable = new ListBox("Table", lsmTable));
    lstTable->setMultipleSelectionEnabled(false);
    lstTable->setRowHeight(16);

    lsmCommands = new TextListModel();
    lsmCommands->setListener(this);

    addAndMakeVisible(lstCommands = new ListBox("Commands", lsmCommands));
    lstCommands->setMultipleSelectionEnabled(false);
    lstCommands->setRowHeight(16);

    lsmParameters = new TextListModel();
    lsmParameters->setListener(this);

    addAndMakeVisible(lstParameters = new ListBox("Parameters", lsmParameters));
    lstParameters->setMultipleSelectionEnabled(false);
    lstParameters->setRowHeight(16);

    lsmSeq = new TextListModel();
    lsmSeq->setListener(this);

    addAndMakeVisible(lstSeq = new ListBox("Sequence", lsmSeq));
    lstSeq->setMultipleSelectionEnabled(false);
    lstSeq->setRowHeight(16);

    txtFTAddr->addListener(this);
    txtABFIndex->addListener(this);
    txtASFIndex->addListener(this);
    txtATFIndex->addListener(this);
    txtABTAddr->addListener(this);
    txtASTAddr->addListener(this);
    txtSSTAddr->addListener(this);
    txtCmdName->addListener(this);
    txtCmd->addListener(this);
    txtCmdEnd->addListener(this);
    txtParamName->addListener(this);
    txtCmdDataSize->addListener(this);
    txtParamAdd->addListener(this);
    txtParamMult->addListener(this);


    //[/UserPreSize]

    setSize (1216, 800);


    //[Constructor] You can add your own custom stuff here..

    ftaddr = 0;
    abfindex = asfindex = atfindex = 0;
    abfaddr = asfaddr = atfaddr = 0;
    abtaddr = astaddr = sstaddr = 0;
    abtsize = astsize = sstsize = 0;

    mainfolder = File(AppProps::readProperty("mainfolder"));
    DBG("Main folder " + mainfolder.getFullPathName());

    //[/Constructor]
}

MainView::~MainView()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    groupComponent7 = nullptr;
    groupComponent4 = nullptr;
    groupComponent3 = nullptr;
    groupComponent6 = nullptr;
    groupComponent5 = nullptr;
    groupComponent2 = nullptr;
    groupComponent = nullptr;
    btnLoadRom = nullptr;
    btnSaveROM = nullptr;
    btnLoadDesc = nullptr;
    btnSaveDesc = nullptr;
    label2 = nullptr;
    txtFTAddr = nullptr;
    label3 = nullptr;
    txtABFIndex = nullptr;
    label4 = nullptr;
    txtASFIndex = nullptr;
    label5 = nullptr;
    txtATFIndex = nullptr;
    lblABFAddr = nullptr;
    lblASFAddr = nullptr;
    lblATFAddr = nullptr;
    label6 = nullptr;
    txtABTAddr = nullptr;
    label7 = nullptr;
    txtASTAddr = nullptr;
    label8 = nullptr;
    txtSSTAddr = nullptr;
    lblABTSize = nullptr;
    lblASTSize = nullptr;
    lblSSTSize = nullptr;
    lblROMFile = nullptr;
    btnABTView = nullptr;
    btnASTView = nullptr;
    btnSSTView = nullptr;
    lblTableName = nullptr;
    label10 = nullptr;
    txtCmd = nullptr;
    btnCmdAdd = nullptr;
    btnCmdDel = nullptr;
    optCmdDataFixed = nullptr;
    optCmdDataVar = nullptr;
    lblCmdDataSize = nullptr;
    txtCmdDataSize = nullptr;
    label11 = nullptr;
    label = nullptr;
    cbxAction = nullptr;
    label9 = nullptr;
    txtCmdName = nullptr;
    txtCmdEnd = nullptr;
    label12 = nullptr;
    optCmdSeq = nullptr;
    optCmdChn = nullptr;
    optCmdTrk = nullptr;
    label13 = nullptr;
    btnParamAdd = nullptr;
    btnParamDel = nullptr;
    btnParamUp = nullptr;
    btnParamDn = nullptr;
    optCmdOffset = nullptr;
    label14 = nullptr;
    label15 = nullptr;
    txtParamName = nullptr;
    label16 = nullptr;
    cbxMeaning = nullptr;
    label17 = nullptr;
    label18 = nullptr;
    txtParamAdd = nullptr;
    txtParamMult = nullptr;
    btnCmdUp = nullptr;
    btnCmdDn = nullptr;
    btnSeq2MIDI = nullptr;
    btnMIDI2Seq = nullptr;
    btnReadSeq = nullptr;
    btnWriteSeq = nullptr;
    lblSeqInfo = nullptr;
    btnLoadMIDI = nullptr;
    btnSaveMIDI = nullptr;
    label20 = nullptr;
    cbxSeqSections = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void MainView::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MainView::resized()
{
    groupComponent7->setBounds (608, 480, 608, 320);
    groupComponent4->setBounds (0, 480, 608, 320);
    groupComponent3->setBounds (408, 0, 400, 480);
    groupComponent6->setBounds (560, 264, 240, 208);
    groupComponent5->setBounds (688, 160, 112, 96);
    groupComponent2->setBounds (0, 0, 400, 48);
    groupComponent->setBounds (0, 56, 400, 192);
    btnLoadRom->setBounds (8, 16, 48, 24);
    btnSaveROM->setBounds (56, 16, 48, 24);
    btnLoadDesc->setBounds (344, 72, 48, 24);
    btnSaveDesc->setBounds (344, 96, 48, 24);
    label2->setBounds (8, 72, 168, 24);
    txtFTAddr->setBounds (176, 72, 96, 24);
    label3->setBounds (32, 96, 144, 24);
    txtABFIndex->setBounds (176, 96, 40, 24);
    label4->setBounds (32, 120, 144, 24);
    txtASFIndex->setBounds (176, 120, 40, 24);
    label5->setBounds (32, 144, 144, 24);
    txtATFIndex->setBounds (176, 144, 40, 24);
    lblABFAddr->setBounds (216, 96, 128, 24);
    lblASFAddr->setBounds (216, 120, 128, 24);
    lblATFAddr->setBounds (216, 144, 128, 24);
    label6->setBounds (8, 168, 168, 24);
    txtABTAddr->setBounds (176, 168, 96, 24);
    label7->setBounds (8, 192, 168, 24);
    txtASTAddr->setBounds (176, 192, 96, 24);
    label8->setBounds (8, 216, 168, 24);
    txtSSTAddr->setBounds (176, 216, 96, 24);
    lblABTSize->setBounds (272, 168, 64, 24);
    lblASTSize->setBounds (272, 192, 64, 24);
    lblSSTSize->setBounds (272, 216, 64, 24);
    lblROMFile->setBounds (104, 16, 288, 24);
    btnABTView->setBounds (344, 168, 48, 24);
    btnASTView->setBounds (344, 192, 48, 24);
    btnSSTView->setBounds (344, 216, 48, 24);
    lblTableName->setBounds (0, 248, 352, 24);
    label10->setBounds (416, 200, 80, 24);
    txtCmd->setBounds (504, 200, 48, 24);
    btnCmdAdd->setBounds (760, 16, 40, 24);
    btnCmdDel->setBounds (760, 40, 40, 24);
    optCmdDataFixed->setBounds (568, 352, 71, 24);
    optCmdDataVar->setBounds (568, 376, 72, 24);
    lblCmdDataSize->setBounds (648, 360, 47, 24);
    txtCmdDataSize->setBounds (696, 360, 32, 24);
    label11->setBounds (728, 360, 48, 24);
    label->setBounds (416, 232, 56, 24);
    cbxAction->setBounds (472, 232, 208, 24);
    label9->setBounds (416, 168, 55, 24);
    txtCmdName->setBounds (472, 168, 208, 24);
    txtCmdEnd->setBounds (584, 200, 48, 24);
    label12->setBounds (560, 200, 23, 24);
    optCmdSeq->setBounds (696, 176, 103, 24);
    optCmdChn->setBounds (696, 200, 104, 24);
    optCmdTrk->setBounds (696, 224, 104, 24);
    label13->setBounds (416, 256, 104, 24);
    btnParamAdd->setBounds (512, 280, 40, 24);
    btnParamDel->setBounds (512, 304, 40, 24);
    btnParamUp->setBounds (512, 416, 40, 24);
    btnParamDn->setBounds (512, 440, 40, 24);
    optCmdOffset->setBounds (568, 328, 160, 24);
    label14->setBounds (568, 304, 224, 24);
    label15->setBounds (568, 400, 224, 24);
    txtParamName->setBounds (624, 280, 166, 24);
    label16->setBounds (568, 280, 55, 24);
    cbxMeaning->setBounds (640, 400, 150, 24);
    label17->setBounds (568, 432, 64, 24);
    label18->setBounds (680, 432, 64, 24);
    txtParamAdd->setBounds (632, 432, 47, 24);
    txtParamMult->setBounds (744, 432, 47, 24);
    btnCmdUp->setBounds (760, 104, 40, 24);
    btnCmdDn->setBounds (760, 128, 40, 24);
    btnSeq2MIDI->setBounds (536, 496, 62, 24);
    btnMIDI2Seq->setBounds (619, 496, 62, 24);
    btnReadSeq->setBounds (8, 496, 48, 24);
    btnWriteSeq->setBounds (56, 496, 48, 24);
    lblSeqInfo->setBounds (112, 496, 416, 24);
    btnLoadMIDI->setBounds (1112, 496, 48, 24);
    btnSaveMIDI->setBounds (1160, 496, 48, 24);
    label20->setBounds (304, 528, 150, 24);
    cbxSeqSections->setBounds (8, 528, 288, 24);
    //[UserResized] Add your own custom resize handling here..
    lstTable->setBounds (0, 272, 400, 200);
    lstCommands->setBounds (424, 16, 328, 136);
    lstParameters->setBounds (424, 280, 80, 184);
    lstSeq->setBounds (16, 560, 288, 232);
    //[/UserResized]
}

void MainView::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == btnLoadRom)
    {
        //[UserButtonCode_btnLoadRom] -- add your button handler code here..
        File lastpath = File::getSpecialLocation(File::userHomeDirectory);
        if(mainfolder.exists()){
            lastpath = mainfolder;
        }
        FileChooser box("Select a ROM to load...", lastpath, "*.z64");
        if(box.browseForFileToOpen()){
            romfile = box.getResult();
            if(!romfile.existsAsFile()){
                DBG("File " + romfile.getFullPathName() + " does not exist!");
                romfile = "";
                rom.reset();
                lblROMFile->setText("File does not exist!", dontSendNotification);
                return;
            }
            //Save what folder you're in
            mainfolder = romfile.getParentDirectory();
            AppProps::writeProperty("mainfolder", mainfolder.getFullPathName());
            //Load ROM
            DBG("Loading 0x" + ROM::hex((uint32)romfile.getSize())
                    + " bytes from " + romfile.getFullPathName());
            rom.reset();
            if(!romfile.loadFileAsData(rom)){
                DBG("Error: could not load file " + romfile.getFullPathName() + "!");
                romfile = "";
                rom.reset();
                lblROMFile->setText("Error loading file!", dontSendNotification);
                return;
            }
            DBG("Successfully loaded 0x" + ROM::hex((uint32)rom.getSize()) + " bytes");
            lblROMFile->setText(romfile.getFileName() + " (0x"
                    + ROM::hex((uint32)rom.getSize()) + " bytes)", dontSendNotification);
            recalcAddresses();
        }
        //[/UserButtonCode_btnLoadRom]
    }
    else if (buttonThatWasClicked == btnSaveROM)
    {
        //[UserButtonCode_btnSaveROM] -- add your button handler code here..
        if(!romfile.exists() || rom.getSize() == 0){
            DBG("No ROM to save!");
            return;
        }
        int ret = NativeMessageBox::showYesNoCancelBox(AlertWindow::WarningIcon,
                "Overwrite?", "Save over " + romfile.getFileName() + "?\n"
                + "(Choose 'No' to Save As)", nullptr, nullptr);
        if(ret == 0) return;
        File newsavelocation = romfile;
        if(ret == 2){
            FileChooser box("Save As", romfile.getParentDirectory(), "*.z64");
            if(box.browseForFileToSave(true)){
                newsavelocation = box.getResult();
                if(!newsavelocation.hasWriteAccess()){
                    DBG("Cannot write to " + newsavelocation.getFullPathName() + "!");
                    return;
                }
                if(newsavelocation.getFileExtension() == ""){
                    newsavelocation = newsavelocation.withFileExtension(".z64");
                }
            }else{
                return;
            }
        }
        DBG("Saving 0x" + ROM::hex((uint32)rom.getSize())
                + " bytes to " + newsavelocation.getFullPathName());
        if(!newsavelocation.replaceWithData(rom.getData(), (int)rom.getSize())){
            DBG("Error: could not write file " + newsavelocation.getFullPathName() + "!");
            return;
        }
        DBG("Successfully saved 0x" + ROM::hex((uint32)newsavelocation.getSize()) + " bytes");
        romfile = newsavelocation;
        //[/UserButtonCode_btnSaveROM]
    }
    else if (buttonThatWasClicked == btnLoadDesc)
    {
        //[UserButtonCode_btnLoadDesc] -- add your button handler code here..
        File lastpath = File::getSpecialLocation(File::userHomeDirectory);
        if(mainfolder.exists()){
            lastpath = mainfolder;
        }
        FileChooser box("Select a ROM description file to load...", lastpath, "*.xml");
        if(box.browseForFileToOpen()){
            romdescfile = box.getResult();
            if(!romdescfile.existsAsFile()){
                DBG("File " + romfile.getFullPathName() + " does not exist!");
                romdescfile = "";
                return;
            }
            //Save what folder you're in
            mainfolder = romdescfile.getParentDirectory();
            AppProps::writeProperty("mainfolder", mainfolder.getFullPathName());
            //Load XML
            DBG("Loading XML ROM description parameters");
            ScopedPointer<XmlElement> xml;
            xml = XmlDocument::parse(romdescfile);
            if(xml != nullptr){
                romdesc = ValueTree::fromXml(*xml);
                txtFTAddr->setText(ROM::hex((uint32)(int)romdesc.getProperty("ftaddr", 0)));
                txtABFIndex->setText(String((int)romdesc.getProperty("abfindex", 0)));
                txtASFIndex->setText(String((int)romdesc.getProperty("asfindex", 0)));
                txtATFIndex->setText(String((int)romdesc.getProperty("atfindex", 0)));
                txtABTAddr->setText(ROM::hex((uint32)(int)romdesc.getProperty("abtaddr", 0)));
                txtASTAddr->setText(ROM::hex((uint32)(int)romdesc.getProperty("astaddr", 0)));
                txtSSTAddr->setText(ROM::hex((uint32)(int)romdesc.getProperty("sstaddr", 0)));
                recalcAddresses();
                refreshCmdList();
                DBG("Successfully loaded");
                return;
            }
            DBG("Error: could not load file " + romfile.getFullPathName() + "!");
            romdescfile = "";
            return;
        }
        //[/UserButtonCode_btnLoadDesc]
    }
    else if (buttonThatWasClicked == btnSaveDesc)
    {
        //[UserButtonCode_btnSaveDesc] -- add your button handler code here..
        File newsavelocation = romdescfile;
        if(!romdescfile.exists()){
            newsavelocation = File::getSpecialLocation(File::userHomeDirectory);
            FileChooser box("Save As", newsavelocation, "*.xml");
            if(box.browseForFileToSave(true)){
                newsavelocation = box.getResult();
                if(!newsavelocation.hasWriteAccess()){
                    DBG("Cannot write to " + newsavelocation.getFullPathName() + "!");
                    return;
                }
                if(newsavelocation.getFileExtension() == ""){
                    newsavelocation = newsavelocation.withFileExtension(".xml");
                }
            }else{
                return;
            }
        }
        DBG("Saving XML ROM description parameters");
        ScopedPointer<XmlElement> xml;
        xml = romdesc.createXml();
        if(xml != nullptr){
            if(xml->writeToFile(newsavelocation, "<!-- seq64 ROM Description File -->")){
                DBG("Successfully saved");
                romdescfile = newsavelocation;
                return;
            }
        }
        DBG("Error: could not write file " + newsavelocation.getFullPathName() + "!");
        return;
        //[/UserButtonCode_btnSaveDesc]
    }
    else if (buttonThatWasClicked == btnABTView)
    {
        //[UserButtonCode_btnABTView] -- add your button handler code here..
        if(abtsize == 0) return;
        whichtable = 0;
        refillTable();
        //[/UserButtonCode_btnABTView]
    }
    else if (buttonThatWasClicked == btnASTView)
    {
        //[UserButtonCode_btnASTView] -- add your button handler code here..
        if(astsize == 0) return;
        whichtable = 1;
        refillTable();
        //[/UserButtonCode_btnASTView]
    }
    else if (buttonThatWasClicked == btnSSTView)
    {
        //[UserButtonCode_btnSSTView] -- add your button handler code here..
        if(sstsize == 0) return;
        whichtable = 2;
        refillTable();
        //[/UserButtonCode_btnSSTView]
    }
    else if (buttonThatWasClicked == btnCmdAdd)
    {
        //[UserButtonCode_btnCmdAdd] -- add your button handler code here..
        ValueTree cmdlistnode = romdesc.getOrCreateChildWithName("cmdlist", nullptr);
        ValueTree cmd("command");
        cmd.setProperty("cmd", 0, nullptr);
        cmd.setProperty("name", "Unnamed", nullptr);
        cmd.setProperty("action", "No Action", nullptr);
        cmdlistnode.addChild(cmd, cmdlistnode.getNumChildren(), nullptr);
        refreshCmdList();
        lstCommands->selectRow(lsmCommands->getNumRows() - 1);
        //[/UserButtonCode_btnCmdAdd]
    }
    else if (buttonThatWasClicked == btnCmdDel)
    {
        //[UserButtonCode_btnCmdDel] -- add your button handler code here..
        int pos = lstCommands->getLastRowSelected();
        if(pos >= 0){
            romdesc.getChildWithName("cmdlist").removeChild(pos, nullptr);
            refreshCmdList();
            lstCommands->selectRow(-1);
        }
        //[/UserButtonCode_btnCmdDel]
    }
    else if (buttonThatWasClicked == optCmdDataFixed)
    {
        //[UserButtonCode_optCmdDataFixed] -- add your button handler code here..
        if(selparam.isValid()){
            selparam.setProperty("datasrc", "fixed", nullptr);
            lblCmdDataSize->setText("length", dontSendNotification);
        }
        //[/UserButtonCode_optCmdDataFixed]
    }
    else if (buttonThatWasClicked == optCmdDataVar)
    {
        //[UserButtonCode_optCmdDataVar] -- add your button handler code here..
        if(selparam.isValid()){
            selparam.setProperty("datasrc", "variable", nullptr);
            lblCmdDataSize->setText("up to", dontSendNotification);
        }
        //[/UserButtonCode_optCmdDataVar]
    }
    else if (buttonThatWasClicked == optCmdSeq)
    {
        //[UserButtonCode_optCmdSeq] -- add your button handler code here..
        if(selcmd.isValid()){
            selcmd.setProperty("validinseq", optCmdSeq->getToggleState(), nullptr);
        }
        //[/UserButtonCode_optCmdSeq]
    }
    else if (buttonThatWasClicked == optCmdChn)
    {
        //[UserButtonCode_optCmdChn] -- add your button handler code here..
        if(selcmd.isValid()){
            selcmd.setProperty("validinchn", optCmdChn->getToggleState(), nullptr);
        }
        //[/UserButtonCode_optCmdChn]
    }
    else if (buttonThatWasClicked == optCmdTrk)
    {
        //[UserButtonCode_optCmdTrk] -- add your button handler code here..
        if(selcmd.isValid()){
            selcmd.setProperty("validintrk", optCmdTrk->getToggleState(), nullptr);
        }
        //[/UserButtonCode_optCmdTrk]
    }
    else if (buttonThatWasClicked == btnParamAdd)
    {
        //[UserButtonCode_btnParamAdd] -- add your button handler code here..
        if(!selcmd.isValid()) return;
        ValueTree paramlistnode = selcmd.getOrCreateChildWithName("paramlist", nullptr);
        ValueTree param("parameter");
        param.setProperty("datasrc", "fixed", nullptr);
        param.setProperty("datalen", 0, nullptr);
        param.setProperty("name", "Unnamed", nullptr);
        param.setProperty("meaning", "None", nullptr);
        param.setProperty("add", 0, nullptr);
        param.setProperty("multiply", 1.0f, nullptr);
        paramlistnode.addChild(param, paramlistnode.getNumChildren(), nullptr);
        refreshParamList();
        lstParameters->selectRow(lsmParameters->getNumRows() - 1);
        //[/UserButtonCode_btnParamAdd]
    }
    else if (buttonThatWasClicked == btnParamDel)
    {
        //[UserButtonCode_btnParamDel] -- add your button handler code here..
        int pos = lstParameters->getLastRowSelected();
        if(pos >= 0){
            selcmd.getChildWithName("paramlist").removeChild(pos, nullptr);
            refreshParamList();
            lstParameters->selectRow(-1);
        }
        //[/UserButtonCode_btnParamDel]
    }
    else if (buttonThatWasClicked == btnParamUp)
    {
        //[UserButtonCode_btnParamUp] -- add your button handler code here..
        int pos = lstParameters->getLastRowSelected();
        if(pos > 0){
            selcmd.getChildWithName("paramlist").moveChild(pos, pos-1, nullptr);
            refreshParamList();
            lstParameters->selectRow(pos-1);
        }
        //[/UserButtonCode_btnParamUp]
    }
    else if (buttonThatWasClicked == btnParamDn)
    {
        //[UserButtonCode_btnParamDn] -- add your button handler code here..
        int pos = lstParameters->getLastRowSelected();
        if(pos >= 0 && pos < lsmParameters->getNumRows() - 1){
            selcmd.getChildWithName("paramlist").moveChild(pos, pos+1, nullptr);
            refreshParamList();
            lstParameters->selectRow(pos+1);
        }
        //[/UserButtonCode_btnParamDn]
    }
    else if (buttonThatWasClicked == optCmdOffset)
    {
        //[UserButtonCode_optCmdOffset] -- add your button handler code here..
        if(selparam.isValid()){
            selparam.setProperty("datasrc", "offset", nullptr);
            txtCmdDataSize->setText("");
            lblCmdDataSize->setText("(none)", dontSendNotification);
        }
        //[/UserButtonCode_optCmdOffset]
    }
    else if (buttonThatWasClicked == btnCmdUp)
    {
        //[UserButtonCode_btnCmdUp] -- add your button handler code here..
        int pos = lstCommands->getLastRowSelected();
        if(pos > 0){
            romdesc.getChildWithName("cmdlist").moveChild(pos, pos-1, nullptr);
            refreshCmdList();
            lstCommands->selectRow(pos-1);
        }
        //[/UserButtonCode_btnCmdUp]
    }
    else if (buttonThatWasClicked == btnCmdDn)
    {
        //[UserButtonCode_btnCmdDn] -- add your button handler code here..
        int pos = lstCommands->getLastRowSelected();
        if(pos >= 0 && pos < lsmCommands->getNumRows() - 1){
            romdesc.getChildWithName("cmdlist").moveChild(pos, pos+1, nullptr);
            refreshCmdList();
            lstCommands->selectRow(pos+1);
        }
        //[/UserButtonCode_btnCmdDn]
    }
    else if (buttonThatWasClicked == btnSeq2MIDI)
    {
        //[UserButtonCode_btnSeq2MIDI] -- add your button handler code here..
        if(&*seq == nullptr) return;
        ScopedPointer<MidiFile> midi;
        midi = seq->toMIDIFile();
        File dest("/home/Sauraen/haxxorz.mid");
        dest.deleteFile();
        FileOutputStream fos(dest);
        midi->writeTo(fos);
        DBG("Written!!!!");
        //[/UserButtonCode_btnSeq2MIDI]
    }
    else if (buttonThatWasClicked == btnMIDI2Seq)
    {
        //[UserButtonCode_btnMIDI2Seq] -- add your button handler code here..
        //[/UserButtonCode_btnMIDI2Seq]
    }
    else if (buttonThatWasClicked == btnReadSeq)
    {
        //[UserButtonCode_btnReadSeq] -- add your button handler code here..
        /*
        if(rom.getSize() == 0) return;
        if(whichtable != 1) return;
        int row = lstTable->getLastRowSelected();
        if(row < 0) return;
        ValueTree cmdlistnode = romdesc.getOrCreateChildWithName("cmdlist", nullptr);
        seq = new SeqFile(rom, cmdlistnode, asfaddr, astaddr, row);
        seq->parseHeader();
        fillSeqSectionsBox();
        */
        //[/UserButtonCode_btnReadSeq]
    }
    else if (buttonThatWasClicked == btnWriteSeq)
    {
        //[UserButtonCode_btnWriteSeq] -- add your button handler code here..
        //[/UserButtonCode_btnWriteSeq]
    }
    else if (buttonThatWasClicked == btnLoadMIDI)
    {
        //[UserButtonCode_btnLoadMIDI] -- add your button handler code here..
        //[/UserButtonCode_btnLoadMIDI]
    }
    else if (buttonThatWasClicked == btnSaveMIDI)
    {
        //[UserButtonCode_btnSaveMIDI] -- add your button handler code here..
        //[/UserButtonCode_btnSaveMIDI]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void MainView::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == cbxAction)
    {
        //[UserComboBoxCode_cbxAction] -- add your combo box handling code here..
        if(selcmd.isValid()){
            String action = cbxAction->getText();
            selcmd.setProperty("action", action, nullptr);
            fillMeaningsBox(action);
            lsmCommands->set(lstCommands->getLastRowSelected(), getCommandDesc(selcmd));
            lstCommands->repaintRow(lstCommands->getLastRowSelected());
        }
        //[/UserComboBoxCode_cbxAction]
    }
    else if (comboBoxThatHasChanged == cbxMeaning)
    {
        //[UserComboBoxCode_cbxMeaning] -- add your combo box handling code here..
        if(selparam.isValid()){
            String meaning = cbxMeaning->getText();
            selparam.setProperty("meaning", meaning, nullptr);
        }
        //[/UserComboBoxCode_cbxMeaning]
    }
    else if (comboBoxThatHasChanged == cbxSeqSections)
    {
        //[UserComboBoxCode_cbxSeqSections] -- add your combo box handling code here..
        //[/UserComboBoxCode_cbxSeqSections]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void MainView::rowSelected(TextListModel* parent, int row){
    if(parent == &*lsmTable){
        //Do nothing
    }else if(parent == &*lsmCommands){
        ValueTree cmdlistnode = romdesc.getOrCreateChildWithName("cmdlist", nullptr);
        selcmd = cmdlistnode.getChild(row);
        refreshCmdControls();
    }else if(parent == &*lsmParameters){
        ValueTree paramlistnode = selcmd.getOrCreateChildWithName("paramlist", nullptr);
        selparam = paramlistnode.getChild(row);
        refreshParamControls();
    }
}

void MainView::textEditorTextChanged(TextEditor& editorThatWasChanged){
    int val;
    String text = editorThatWasChanged.getText();
    if(&editorThatWasChanged == &*txtABFIndex
            || &editorThatWasChanged == &*txtASFIndex
            || &editorThatWasChanged == &*txtATFIndex
            || &editorThatWasChanged == &*txtParamAdd
            || &editorThatWasChanged == &*txtCmdDataSize){
        val = text.getIntValue();
    }else{
        val = text.getHexValue32();
    }
    bool turnRed = (val <= 0);
    bool redrawCmdItem = false;

    if(&editorThatWasChanged == &*txtFTAddr){
        ftaddr = val;
        romdesc.setProperty("ftaddr", (int)ftaddr, nullptr);
    }else if(&editorThatWasChanged == &*txtABFIndex){
        abfindex = val;
        romdesc.setProperty("abfindex", (int)abfindex, nullptr);
    }else if(&editorThatWasChanged == &*txtASFIndex){
        asfindex = val;
        romdesc.setProperty("asfindex", (int)asfindex, nullptr);
    }else if(&editorThatWasChanged == &*txtATFIndex){
        atfindex = val;
        romdesc.setProperty("atfindex", (int)atfindex, nullptr);
    }else if(&editorThatWasChanged == &*txtABTAddr){
        abtaddr = val;
        romdesc.setProperty("abtaddr", (int)abtaddr, nullptr);
    }else if(&editorThatWasChanged == &*txtASTAddr){
        astaddr = val;
        romdesc.setProperty("astaddr", (int)astaddr, nullptr);
    }else if(&editorThatWasChanged == &*txtSSTAddr){
        sstaddr = val;
        romdesc.setProperty("sstaddr", (int)sstaddr, nullptr);
    }else if(&editorThatWasChanged == &*txtCmdName){
        if(!selcmd.isValid()) return;
        selcmd.setProperty("name", text, nullptr);
        turnRed = false;
        redrawCmdItem = true;
    }else if(&editorThatWasChanged == &*txtCmd){
        if(!selcmd.isValid()) return;
        selcmd.setProperty("cmd", val, nullptr);
        redrawCmdItem = true;
    }else if(&editorThatWasChanged == &*txtCmdEnd){
        if(!selcmd.isValid()) return;
        if(text != ""){
            selcmd.setProperty("cmdend", val, nullptr);
            if(val < (int)selcmd.getProperty("cmd", 0xFF)){
                turnRed = true;
            }
        }else{
            selcmd.removeProperty("cmdend", nullptr);
            turnRed = false;
        }
        redrawCmdItem = true;
    }else if(&editorThatWasChanged == &*txtParamName){
        if(!selparam.isValid()) return;
        selparam.setProperty("name", text, nullptr);
        turnRed = false;
    }else if(&editorThatWasChanged == &*txtParamAdd){
        if(!selparam.isValid()) return;
        selparam.setProperty("add", val, nullptr);
        turnRed = false;
    }else if(&editorThatWasChanged == &*txtParamMult){
        if(!selparam.isValid()) return;
        float v = text.getFloatValue();
        if(v <= 0.0f) v = 1.0f;
        selparam.setProperty("multiply", v, nullptr);
        turnRed = false;
    }else if(&editorThatWasChanged == &*txtCmdDataSize){
        if(!selparam.isValid()) return;
        if(val < 0) val = 0;
        selparam.setProperty("datalen", val, nullptr);
        turnRed = false;
    }
    if(turnRed){
        editorThatWasChanged.setColour(TextEditor::backgroundColourId, Colours::red);
    }else{
        editorThatWasChanged.setColour(TextEditor::backgroundColourId, Colours::white);
    }
    if(redrawCmdItem){
        lsmCommands->set(lstCommands->getLastRowSelected(), getCommandDesc(selcmd));
        lstCommands->repaintRow(lstCommands->getLastRowSelected());
    }

    recalcAddresses();
}


void MainView::recalcAddresses(){
    if(rom.getSize() == 0) return;
    //File Table
    if(ftaddr >= rom.getSize()){
        abfaddr = asfaddr = atfaddr = 0;

    }else{
        abfaddr = rom.readWord(ftaddr + (16*abfindex));
        asfaddr = rom.readWord(ftaddr + (16*asfindex));
        atfaddr = rom.readWord(ftaddr + (16*atfindex));
        lblABFAddr->setText("addr: " + ROM::hex(abfaddr), dontSendNotification);
        lblASFAddr->setText("addr: " + ROM::hex(asfaddr), dontSendNotification);
        lblATFAddr->setText("addr: " + ROM::hex(atfaddr), dontSendNotification);
    }
    //Other tables
    if(abtaddr >= rom.getSize()){
        abtsize = 0;
    }else{
        abtsize = rom.readHalfWord(abtaddr);
        int check = rom.readHalfWord(abtaddr+2);
        check |= rom.readWord(abtaddr+4);
        check |= rom.readWord(abtaddr+8);
        check |= rom.readWord(abtaddr+12);
        if(check){
            abtsize = 0;
            lblABTSize->setText("Nope", dontSendNotification);
        }else{
            lblABTSize->setText("sz: " + String(abtsize), dontSendNotification);
        }
    }
    if(astaddr >= rom.getSize()){
        astsize = 0;
    }else{
        astsize = rom.readHalfWord(astaddr);
        int check = rom.readHalfWord(astaddr+2);
        check |= rom.readWord(astaddr+4);
        check |= rom.readWord(astaddr+8);
        check |= rom.readWord(astaddr+12);
        if(check){
            astsize = 0;
            lblASTSize->setText("Nope", dontSendNotification);
        }else{
            lblASTSize->setText("sz: " + String(astsize), dontSendNotification);
        }
    }
    if(sstaddr >= rom.getSize()){
        sstsize = 0;
    }else{
        sstsize = rom.readHalfWord(sstaddr);
        int check = rom.readHalfWord(sstaddr+2);
        check |= rom.readWord(sstaddr+4);
        check |= rom.readWord(sstaddr+8);
        check |= rom.readWord(sstaddr+12);
        if(check){
            sstsize = 0;
            lblSSTSize->setText("Nope", dontSendNotification);
        }else{
            lblSSTSize->setText("sz: " + String(sstsize), dontSendNotification);
        }
    }
}


void MainView::refillTable(){
    lsmTable->clear();
    if(whichtable == 0){
        //Audiobank table
        lblTableName->setText("Audiobank Table @ 0x" + ROM::hex(abtaddr), dontSendNotification);
        if(abtsize == 0){
            lsmTable->add(String("Audiobank table addr invalid!"));
        }else{
            for(int i=0; i<abtsize; ++i){
                lsmTable->add(String(i) + ": 0x" + ROM::hex(rom.readWord(abtaddr + 16 + (16*i)))
                    + " 0x" + ROM::hex(rom.readWord(abtaddr + 20 + (16*i)))
                    + " 0x" + ROM::hex(rom.readWord(abtaddr + 24 + (16*i)))
                    + " 0x" + ROM::hex(rom.readWord(abtaddr + 28 + (16*i))) );
            }
        }
    }else if(whichtable == 1){
        //Audioseq table
        lblTableName->setText("Audioseq Table @ 0x" + ROM::hex(astaddr), dontSendNotification);
        if(astsize == 0){
            lsmTable->add(String("Audioseq table addr invalid!"));
        }else{
            for(int i=0; i<astsize; ++i){
                lsmTable->add(String(i) + ": @ 0x" + ROM::hex(rom.readWord(astaddr + 16 + (16*i)), 6)
                    + ", Size 0x" + ROM::hex(rom.readWord(astaddr + 20 + (16*i)), 6)
                    + ", Type 0x" + ROM::hex((uint32)rom.readHalfWord(astaddr + 24 + (16*i)), 4) );
            }
        }
    }else if(whichtable == 2){
        //Sample set table
        lblTableName->setText("Sample Set Table @ 0x" + ROM::hex(sstaddr), dontSendNotification);
        if(sstsize == 0){
            lsmTable->add(String("Sample set table addr invalid!"));
        }else{
            for(int i=0; i<sstsize; ++i){
                lsmTable->add(String(i) + ": 0x" + ROM::hex(rom.readWord(sstaddr + 16 + (16*i)))
                    + " 0x" + ROM::hex(rom.readWord(sstaddr + 20 + (16*i)))
                    + " 0x" + ROM::hex(rom.readWord(sstaddr + 24 + (16*i)))
                    + " 0x" + ROM::hex(rom.readWord(sstaddr + 28 + (16*i))) );
            }
        }
    }
    lstTable->updateContent();
}

void MainView::refreshCmdControls(){
    if(!selcmd.isValid()){
        txtCmdName->setText("");
        txtCmd->setText("");
        txtCmdEnd->setText("");
        optCmdSeq->setToggleState(false, dontSendNotification);
        optCmdChn->setToggleState(false, dontSendNotification);
        optCmdTrk->setToggleState(false, dontSendNotification);
        cbxAction->setText("No Action");
        fillMeaningsBox("No Action");
        refreshParamList();
        lstParameters->selectRow(0);
    }else{
        txtCmdName->setText(selcmd.getProperty("name", "Error!").toString());
        txtCmd->setText(ROM::hex((uint8)(int)selcmd.getProperty("cmd", 0)));
        if(selcmd.hasProperty("cmdend")){
            txtCmdEnd->setText(ROM::hex((uint8)(int)selcmd.getProperty("cmdend", 0)));
        }else{
            txtCmdEnd->setText("");
        }
        optCmdSeq->setToggleState((bool)selcmd.getProperty("validinseq", false), dontSendNotification);
        optCmdChn->setToggleState((bool)selcmd.getProperty("validinchn", false), dontSendNotification);
        optCmdTrk->setToggleState((bool)selcmd.getProperty("validintrk", false), dontSendNotification);
        String action = selcmd.getProperty("action", "No Action").toString();
        cbxAction->setText(action);
        fillMeaningsBox(action);
    }
    refreshParamList();
}

void MainView::refreshParamControls(){
    if(selparam.isValid()){
        String src = selparam.getProperty("datasrc", "fixed").toString();
        if(src == "variable"){
            optCmdDataVar->setToggleState(true, dontSendNotification);
            txtCmdDataSize->setText(String((int)selparam.getProperty("datalen", 0)));
            lblCmdDataSize->setText("up to", dontSendNotification);
        }else if(src == "offset"){
            optCmdOffset->setToggleState(true, dontSendNotification);
            txtCmdDataSize->setText("");
            lblCmdDataSize->setText("(none)", dontSendNotification);
        }else{
            optCmdDataFixed->setToggleState(true, dontSendNotification);
            txtCmdDataSize->setText(String((int)selparam.getProperty("datalen", 0)));
            lblCmdDataSize->setText("length", dontSendNotification);
        }
        txtParamName->setText(selparam.getProperty("name", "Unnamed").toString());
        cbxMeaning->setText(selparam.getProperty("meaning", "None").toString());
        txtParamAdd->setText(String((int)selparam.getProperty("add", 0)));
        txtParamMult->setText(String((float)selparam.getProperty("multiply", 1.0f)));
    }else{
        optCmdDataFixed->setToggleState(true, dontSendNotification);
        txtCmdDataSize->setText("0");
        lblCmdDataSize->setText("length", dontSendNotification);
        txtParamName->setText("");
        cbxMeaning->setText("None");
        txtParamAdd->setText("0");
        txtParamMult->setText("1");
    }
}

void MainView::refreshCmdList(){
    //int lastselected = getLastRowSelected();
    lsmCommands->clear();
    ValueTree cmdlistnode = romdesc.getOrCreateChildWithName("cmdlist", nullptr);
    ValueTree cmd;
    String desc;
    for(int i=0; i<cmdlistnode.getNumChildren(); i++){
        cmd = cmdlistnode.getChild(i);
        if(cmd.getType() == Identifier("command")){
            lsmCommands->add(getCommandDesc(cmd));
        }
    }
    lstCommands->updateContent();
    //lstCommands->selectRow(lastselected);
}
void MainView::refreshParamList(){
    lsmParameters->clear();
    lstParameters->updateContent();
    if(selcmd.isValid()){
        ValueTree paramlistnode = selcmd.getOrCreateChildWithName("paramlist", nullptr);
        ValueTree param;
        for(int i=0; i<paramlistnode.getNumChildren(); i++){
            param = paramlistnode.getChild(i);
            if(param.getType() == Identifier("parameter")){
                lsmParameters->add(String(i));
            }
        }
    }
    lstParameters->updateContent();
}

String MainView::getCommandDesc(ValueTree cmd){
    String desc = ROM::hex((uint8)(int)cmd.getProperty("cmd", 0));
    if(cmd.hasProperty("cmdend")){
        desc += " to " + ROM::hex((uint8)(int)cmd.getProperty("cmdend", 0));
    }
    desc += ": " + cmd.getProperty("name").toString();
    desc += " (" + cmd.getProperty("action").toString() + ")";
    return desc;
}


void MainView::fillMeaningsBox(String action){
    cbxMeaning->clear(dontSendNotification);
    cbxMeaning->addItem("None", cbxMeaning->getNumItems()+1);
    cbxMeaning->addItem("Pre-Delay", cbxMeaning->getNumItems()+1);
    cbxMeaning->addItem("Post-Delay", cbxMeaning->getNumItems()+1);
    if(action == "No Action"){
        //None
    }else if(action == "End of Data"){
        //None
    }else if(action == "Timestamp"){
        //None--use Pre-Delay or Post-Delay
    }else if(action == "Ptr Channel Header"){
        cbxMeaning->addItem("Channel", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("Address", cbxMeaning->getNumItems()+1);
    }else if(action == "Ptr Loop Start"){
        cbxMeaning->addItem("Address", cbxMeaning->getNumItems()+1);
    }else if(action == "Ptr Track Data"){
        cbxMeaning->addItem("Note Layer", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("Address", cbxMeaning->getNumItems()+1);
    }else if(action == "Ptr More Track Data"){
        cbxMeaning->addItem("Address", cbxMeaning->getNumItems()+1);
    }else if(action == "Master Volume"){
        cbxMeaning->addItem("Value", cbxMeaning->getNumItems()+1);
    }else if(action == "Tempo"){
        cbxMeaning->addItem("Value", cbxMeaning->getNumItems()+1);
    }else if(action == "Chn Priority"){
        cbxMeaning->addItem("Channel", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("Value", cbxMeaning->getNumItems()+1);
    }else if(action == "Chn Volume"){
        cbxMeaning->addItem("Channel", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("Value", cbxMeaning->getNumItems()+1);
    }else if(action == "Chn Pan"){
        cbxMeaning->addItem("Channel", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("Value", cbxMeaning->getNumItems()+1);
    }else if(action == "Chn Effects"){
        cbxMeaning->addItem("Channel", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("Value", cbxMeaning->getNumItems()+1);
    }else if(action == "Chn Vibrato"){
        cbxMeaning->addItem("Channel", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("Value", cbxMeaning->getNumItems()+1);
    }else if(action == "Chn Pitch Bend"){
        cbxMeaning->addItem("Channel", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("Value", cbxMeaning->getNumItems()+1);
    }else if(action == "Transpose"){
        cbxMeaning->addItem("Channel", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("Value", cbxMeaning->getNumItems()+1);
    }else if(action == "Chn Instrument"){
        cbxMeaning->addItem("Channel", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("Value", cbxMeaning->getNumItems()+1);
    }else if(action == "Track Note"){
        cbxMeaning->addItem("Note Layer", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("Note", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("Velocity", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("Gate Time", cbxMeaning->getNumItems()+1);
    }else{
        cbxMeaning->clear(dontSendNotification);
        cbxMeaning->addItem("ERROR fillMeaningsBox", cbxMeaning->getNumItems()+1);
    }
    cbxMeaning->setSelectedItemIndex(0, dontSendNotification);
}

void MainView::fillSeqSectionsBox(){
    /*
    cbxSeqSections->clear(dontSendNotification);
    if(&*seq != nullptr){
        cbxSeqSections->addItem("@00000 Sequence Header", 1);
        int i;
        SeqData* seqdata;
        String s;
        for(i=0; i<seq->getNumChanHdrs(); i++){
            seqdata = seq->getChanHdr(i);
            s = "@" + ROM::hex(seqdata->address, 6) + " Chan " + String(seqdata->channel) + " Hdr";
            cbxSeqSections->addItem(s, cbxSeqSections->getNumItems()+1);
        }
        for(i=0; i<seq->getNumTracks(); i++){
            seqdata = seq->getTrack(i);
            s = "@" + ROM::hex(seqdata->address, 6) + " Chan " + String(seqdata->channel)
                    + " Layer " + String(seqdata->layer);
            cbxSeqSections->addItem(s, cbxSeqSections->getNumItems()+1);
        }
    }
    */
}

void MainView::listSeqCommands(){
    lsmSeq->clear();
    if(&*seq != nullptr){

    }
    lstSeq->updateContent();
}


//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MainView" componentName=""
                 parentClasses="public Component, public TextEditor::Listener, public TextListModel::Listener"
                 constructorParams="" variableInitialisers="romdesc(Identifier(&quot;RomDesc&quot;))"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="1216" initialHeight="800">
  <BACKGROUND backgroundColour="ffffffff"/>
  <GROUPCOMPONENT name="new group" id="1425999ad9d4de4d" memberName="groupComponent7"
                  virtualName="" explicitFocusOrder="0" pos="608 480 608 320" title="MIDI File"
                  textpos="34"/>
  <GROUPCOMPONENT name="new group" id="1d6b4733da5242c5" memberName="groupComponent4"
                  virtualName="" explicitFocusOrder="0" pos="0 480 608 320" title="Sequence File"
                  textpos="33"/>
  <GROUPCOMPONENT name="new group" id="f1d4a599b3267719" memberName="groupComponent3"
                  virtualName="" explicitFocusOrder="0" pos="408 0 400 480" title="Command Editor"/>
  <GROUPCOMPONENT name="new group" id="977c50d4ba0f1784" memberName="groupComponent6"
                  virtualName="" explicitFocusOrder="0" pos="560 264 240 208" title="Edit Parameter"/>
  <GROUPCOMPONENT name="new group" id="b9f9c4c5353e7b92" memberName="groupComponent5"
                  virtualName="" explicitFocusOrder="0" pos="688 160 112 96" title="Valid in"/>
  <GROUPCOMPONENT name="new group" id="27aca3ac619b18bd" memberName="groupComponent2"
                  virtualName="" explicitFocusOrder="0" pos="0 0 400 48" title="ROM"/>
  <GROUPCOMPONENT name="new group" id="da359c2a889a9b69" memberName="groupComponent"
                  virtualName="" explicitFocusOrder="0" pos="0 56 400 192" title="ROM Description (addr hex, index dec)"/>
  <TEXTBUTTON name="Load ROM" id="65e85d822a1d61bd" memberName="btnLoadRom"
              virtualName="" explicitFocusOrder="0" pos="8 16 48 24" buttonText="Load"
              connectedEdges="2" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Save ROM" id="6408fa402953fdd4" memberName="btnSaveROM"
              virtualName="" explicitFocusOrder="0" pos="56 16 48 24" buttonText="Save"
              connectedEdges="1" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Load ROM" id="c641b8a9c7ad15aa" memberName="btnLoadDesc"
              virtualName="" explicitFocusOrder="0" pos="344 72 48 24" buttonText="Load"
              connectedEdges="8" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Save ROM" id="64777c157e6187cb" memberName="btnSaveDesc"
              virtualName="" explicitFocusOrder="0" pos="344 96 48 24" buttonText="Save"
              connectedEdges="4" needsCallback="1" radioGroupId="0"/>
  <LABEL name="new label" id="ad911e2c40ea8f61" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="8 72 168 24" edTextCol="ff000000"
         edBkgCol="0" labelText="File table addr:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="8d98b3fd9582a52d" memberName="txtFTAddr"
              virtualName="" explicitFocusOrder="0" pos="176 72 96 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="0"/>
  <LABEL name="new label" id="de898b96b7d4822" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="32 96 144 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Audiobank file index:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="eef60a1d6269ce8f" memberName="txtABFIndex"
              virtualName="" explicitFocusOrder="0" pos="176 96 40 24" initialText="0"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="0"/>
  <LABEL name="new label" id="1b1bbedbccf599d7" memberName="label4" virtualName=""
         explicitFocusOrder="0" pos="32 120 144 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Audioseq file index:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="962ba8d2bcb8d50" memberName="txtASFIndex"
              virtualName="" explicitFocusOrder="0" pos="176 120 40 24" initialText="0"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="0"/>
  <LABEL name="new label" id="ad6fece6aeb98f6e" memberName="label5" virtualName=""
         explicitFocusOrder="0" pos="32 144 144 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Audiotable file index:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="1d50102aa14a7920" memberName="txtATFIndex"
              virtualName="" explicitFocusOrder="0" pos="176 144 40 24" initialText="0"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="0"/>
  <LABEL name="new label" id="afcaa1a82c1ef095" memberName="lblABFAddr"
         virtualName="" explicitFocusOrder="0" pos="216 96 128 24" edTextCol="ff000000"
         edBkgCol="0" labelText="addr: " editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="e0cc2349d90eb4b" memberName="lblASFAddr"
         virtualName="" explicitFocusOrder="0" pos="216 120 128 24" edTextCol="ff000000"
         edBkgCol="0" labelText="addr: " editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="cc40be757ac30c9a" memberName="lblATFAddr"
         virtualName="" explicitFocusOrder="0" pos="216 144 128 24" edTextCol="ff000000"
         edBkgCol="0" labelText="addr: " editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="5b4e59fa95edba49" memberName="label6" virtualName=""
         explicitFocusOrder="0" pos="8 168 168 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Audiobank table addr:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="841b5602fcb9c216" memberName="txtABTAddr"
              virtualName="" explicitFocusOrder="0" pos="176 168 96 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="0"/>
  <LABEL name="new label" id="42a786ac7b36369e" memberName="label7" virtualName=""
         explicitFocusOrder="0" pos="8 192 168 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Audioseq table addr:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="c3268777cfdfa163" memberName="txtASTAddr"
              virtualName="" explicitFocusOrder="0" pos="176 192 96 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="0"/>
  <LABEL name="new label" id="33b80839dc810f0b" memberName="label8" virtualName=""
         explicitFocusOrder="0" pos="8 216 168 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Sample set table addr:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="710e95d29326f6d6" memberName="txtSSTAddr"
              virtualName="" explicitFocusOrder="0" pos="176 216 96 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="0"/>
  <LABEL name="new label" id="99c59e087d6aecf5" memberName="lblABTSize"
         virtualName="" explicitFocusOrder="0" pos="272 168 64 24" edTextCol="ff000000"
         edBkgCol="0" labelText="sz: " editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="7d161de22cb6adf7" memberName="lblASTSize"
         virtualName="" explicitFocusOrder="0" pos="272 192 64 24" edTextCol="ff000000"
         edBkgCol="0" labelText="sz: " editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="cfcc7e74e66cb7b2" memberName="lblSSTSize"
         virtualName="" explicitFocusOrder="0" pos="272 216 64 24" edTextCol="ff000000"
         edBkgCol="0" labelText="sz: " editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="c16cc706255e7358" memberName="lblROMFile"
         virtualName="" explicitFocusOrder="0" pos="104 16 288 24" edTextCol="ff000000"
         edBkgCol="0" labelText="[ROM Filename]" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="Load ROM" id="dfdc6944e61c75e2" memberName="btnABTView"
              virtualName="" explicitFocusOrder="0" pos="344 168 48 24" buttonText="View"
              connectedEdges="8" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Load ROM" id="ffa981f0fbc8e35f" memberName="btnASTView"
              virtualName="" explicitFocusOrder="0" pos="344 192 48 24" buttonText="View"
              connectedEdges="12" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Load ROM" id="424f6314b872a2fe" memberName="btnSSTView"
              virtualName="" explicitFocusOrder="0" pos="344 216 48 24" buttonText="View"
              connectedEdges="4" needsCallback="1" radioGroupId="0"/>
  <LABEL name="new label" id="75a318dcfddc3d7d" memberName="lblTableName"
         virtualName="" explicitFocusOrder="0" pos="0 248 352 24" edTextCol="ff000000"
         edBkgCol="0" labelText="[Name of table]" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="120e7da910b9fa36" memberName="label10" virtualName=""
         explicitFocusOrder="0" pos="416 200 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Command:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="c17bf80cbae3b9bf" memberName="txtCmd"
              virtualName="" explicitFocusOrder="0" pos="504 200 48 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTBUTTON name="new button" id="33646eda08c514f8" memberName="btnCmdAdd"
              virtualName="" explicitFocusOrder="0" pos="760 16 40 24" buttonText="Add"
              connectedEdges="8" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="4ad518eab3cf4e38" memberName="btnCmdDel"
              virtualName="" explicitFocusOrder="0" pos="760 40 40 24" buttonText="Del"
              connectedEdges="4" needsCallback="1" radioGroupId="0"/>
  <TOGGLEBUTTON name="new toggle button" id="de7cafa15549ae99" memberName="optCmdDataFixed"
                virtualName="" explicitFocusOrder="0" pos="568 352 71 24" buttonText="Fixed"
                connectedEdges="0" needsCallback="1" radioGroupId="1" state="1"/>
  <TOGGLEBUTTON name="new toggle button" id="1ac143856715712c" memberName="optCmdDataVar"
                virtualName="" explicitFocusOrder="0" pos="568 376 72 24" buttonText="Variable"
                connectedEdges="0" needsCallback="1" radioGroupId="1" state="0"/>
  <LABEL name="new label" id="5ef4448d8600da02" memberName="lblCmdDataSize"
         virtualName="" explicitFocusOrder="0" pos="648 360 47 24" edTextCol="ff000000"
         edBkgCol="0" labelText="length" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtCmdDat" id="6db88ac89d3dcd1d" memberName="txtCmdDataSize"
              virtualName="" explicitFocusOrder="0" pos="696 360 32 24" initialText="1"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="63098370e332d46f" memberName="label11" virtualName=""
         explicitFocusOrder="0" pos="728 360 48 24" edTextCol="ff000000"
         edBkgCol="0" labelText="(dec)" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="1260a931f1b77e50" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="416 232 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Action:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <COMBOBOX name="Action" id="4cabd0b9e2965ff5" memberName="cbxAction" virtualName=""
            explicitFocusOrder="0" pos="472 232 208 24" editable="0" layout="33"
            items="No Action&#10;End of Data&#10;Timestamp&#10;Ptr Channel Header&#10;Ptr Loop Start&#10;Ptr Track Data&#10;Ptr More Track Data&#10;Master Volume&#10;Tempo&#10;Chn Priority&#10;Chn Volume&#10;Chn Pan&#10;Chn Effects&#10;Chn Vibrato&#10;Chn Pitch Bend&#10;Chn Instrument&#10;Transpose&#10;Track Note"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="6d034f22b803ef0c" memberName="label9" virtualName=""
         explicitFocusOrder="0" pos="416 168 55 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Name:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="17aae1e70c35fd59" memberName="txtCmdName"
              virtualName="" explicitFocusOrder="0" pos="472 168 208 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="new text editor" id="391e87c7412baa15" memberName="txtCmdEnd"
              virtualName="" explicitFocusOrder="0" pos="584 200 48 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="2dce25261c0a7641" memberName="label12" virtualName=""
         explicitFocusOrder="0" pos="560 200 23 24" edTextCol="ff000000"
         edBkgCol="0" labelText="to" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TOGGLEBUTTON name="new toggle button" id="6760f7dd9298e144" memberName="optCmdSeq"
                virtualName="" explicitFocusOrder="0" pos="696 176 103 24" buttonText="Seq header"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="e198702d72e71f55" memberName="optCmdChn"
                virtualName="" explicitFocusOrder="0" pos="696 200 104 24" buttonText="Chn header"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="d079eea3af0c26a4" memberName="optCmdTrk"
                virtualName="" explicitFocusOrder="0" pos="696 224 104 24" buttonText="Track data"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <LABEL name="new label" id="5666e65f925f98ec" memberName="label13" virtualName=""
         explicitFocusOrder="0" pos="416 256 104 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Parameters:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="new button" id="972d79b803f377c4" memberName="btnParamAdd"
              virtualName="" explicitFocusOrder="0" pos="512 280 40 24" buttonText="Add"
              connectedEdges="8" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="1ba257bf64ce7e89" memberName="btnParamDel"
              virtualName="" explicitFocusOrder="0" pos="512 304 40 24" buttonText="Del"
              connectedEdges="4" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="2f3dd0a3ebcb78d5" memberName="btnParamUp"
              virtualName="" explicitFocusOrder="0" pos="512 416 40 24" buttonText="Up"
              connectedEdges="8" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="cee83a628d87bd1a" memberName="btnParamDn"
              virtualName="" explicitFocusOrder="0" pos="512 440 40 24" buttonText="Dn"
              connectedEdges="4" needsCallback="1" radioGroupId="0"/>
  <TOGGLEBUTTON name="new toggle button" id="3134f7ae28bcfdd3" memberName="optCmdOffset"
                virtualName="" explicitFocusOrder="0" pos="568 328 160 24" buttonText="Cmd Offset (no data)"
                connectedEdges="0" needsCallback="1" radioGroupId="1" state="0"/>
  <LABEL name="new label" id="9da40dae5b71c4cf" memberName="label14" virtualName=""
         explicitFocusOrder="0" pos="568 304 224 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Data source:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="eed9a48d3bb5e03b" memberName="label15" virtualName=""
         explicitFocusOrder="0" pos="568 400 224 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Meaning:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="b867bd3ceb8e1203" memberName="txtParamName"
              virtualName="" explicitFocusOrder="0" pos="624 280 166 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="8306c58890811511" memberName="label16" virtualName=""
         explicitFocusOrder="0" pos="568 280 55 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Name:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <COMBOBOX name="Meaning" id="5955524ab0ec02c1" memberName="cbxMeaning"
            virtualName="" explicitFocusOrder="0" pos="640 400 150 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="8d5abd7e709bfe4f" memberName="label17" virtualName=""
         explicitFocusOrder="0" pos="568 432 64 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Add (dec):" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="9a94c821168285dc" memberName="label18" virtualName=""
         explicitFocusOrder="0" pos="680 432 64 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Multiply:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="d44ee99ec4017196" memberName="txtParamAdd"
              virtualName="" explicitFocusOrder="0" pos="632 432 47 24" initialText="0"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="new text editor" id="9adbc3822f7d0ac1" memberName="txtParamMult"
              virtualName="" explicitFocusOrder="0" pos="744 432 47 24" initialText="1.0"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTBUTTON name="new button" id="5c1f23230407fcb1" memberName="btnCmdUp"
              virtualName="" explicitFocusOrder="0" pos="760 104 40 24" buttonText="Up"
              connectedEdges="8" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="98d71ec28a9ccb5f" memberName="btnCmdDn"
              virtualName="" explicitFocusOrder="0" pos="760 128 40 24" buttonText="Dn"
              connectedEdges="4" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="41d0097ce82dba7f" memberName="btnSeq2MIDI"
              virtualName="" explicitFocusOrder="0" pos="536 496 62 24" buttonText="MIDI &gt;"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="184bf88036cbb7f5" memberName="btnMIDI2Seq"
              virtualName="" explicitFocusOrder="0" pos="619 496 62 24" buttonText="&lt; SEQ"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Read Sequence" id="8dafbd47ec900af3" memberName="btnReadSeq"
              virtualName="" explicitFocusOrder="0" pos="8 496 48 24" buttonText="Read"
              connectedEdges="2" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Write Sequence" id="3691a9f678390aba" memberName="btnWriteSeq"
              virtualName="" explicitFocusOrder="0" pos="56 496 48 24" buttonText="Write"
              connectedEdges="1" needsCallback="1" radioGroupId="0"/>
  <LABEL name="new label" id="e9dec18897cc7129" memberName="lblSeqInfo"
         virtualName="" explicitFocusOrder="0" pos="112 496 416 24" edTextCol="ff000000"
         edBkgCol="0" labelText="[File info]" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="Load MIDI" id="870ebdfebadb4392" memberName="btnLoadMIDI"
              virtualName="" explicitFocusOrder="0" pos="1112 496 48 24" buttonText="Load"
              connectedEdges="2" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Save MIDI" id="8969c8c88549fe7a" memberName="btnSaveMIDI"
              virtualName="" explicitFocusOrder="0" pos="1160 496 48 24" buttonText="Save"
              connectedEdges="1" needsCallback="1" radioGroupId="0"/>
  <LABEL name="new label" id="87301ccc52b90cd3" memberName="label20" virtualName=""
         explicitFocusOrder="0" pos="304 528 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Placeholder" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="new combo box" id="df1bbb6d7c57ae2b" memberName="cbxSeqSections"
            virtualName="" explicitFocusOrder="0" pos="8 528 288 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

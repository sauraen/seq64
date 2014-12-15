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
#include "JuceHeader.h"
#include "AppProps.h"
//[/Headers]

#include "AudioseqPane.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
AudioseqPane::AudioseqPane (AppProps& props)
    : p(props)
{
    addAndMakeVisible (groupComponent = new GroupComponent ("new group",
                                                            TRANS("Loaded Sequence")));

    addAndMakeVisible (groupComponent2 = new GroupComponent ("new group",
                                                             TRANS("Section is")));

    addAndMakeVisible (groupComponent3 = new GroupComponent ("new group",
                                                             TRANS("Command Editor")));

    addAndMakeVisible (groupComponent6 = new GroupComponent ("new group",
                                                             TRANS("Edit Parameter")));

    addAndMakeVisible (groupComponent5 = new GroupComponent ("new group",
                                                             TRANS("Valid in")));

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

    addAndMakeVisible (label2 = new Label ("new label",
                                           TRANS("Action:")));
    label2->setFont (Font (15.00f, Font::plain));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (cbxAction = new ComboBox ("Action"));
    cbxAction->setEditableText (false);
    cbxAction->setJustificationType (Justification::centredLeft);
    cbxAction->setTextWhenNothingSelected (String::empty);
    cbxAction->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    cbxAction->addItem (TRANS("No Action"), 1);
    cbxAction->addItem (TRANS("End of Data"), 2);
    cbxAction->addItem (TRANS("Timestamp"), 3);
    cbxAction->addItem (TRANS("Jump Same Level"), 4);
    cbxAction->addItem (TRANS("Call Same Level"), 5);
    cbxAction->addItem (TRANS("Loop Start"), 6);
    cbxAction->addItem (TRANS("Loop End"), 7);
    cbxAction->addItem (TRANS("Ptr Channel Header"), 8);
    cbxAction->addItem (TRANS("Ptr Track Data"), 9);
    cbxAction->addItem (TRANS("Sequence Format"), 10);
    cbxAction->addItem (TRANS("Sequence Type"), 11);
    cbxAction->addItem (TRANS("Channel Enable"), 12);
    cbxAction->addItem (TRANS("Channel Disable"), 13);
    cbxAction->addItem (TRANS("Master Volume"), 14);
    cbxAction->addItem (TRANS("Tempo"), 15);
    cbxAction->addItem (TRANS("Chn Reset"), 16);
    cbxAction->addItem (TRANS("Chn Priority"), 17);
    cbxAction->addItem (TRANS("Chn Volume"), 18);
    cbxAction->addItem (TRANS("Chn Pan"), 19);
    cbxAction->addItem (TRANS("Chn Effects"), 20);
    cbxAction->addItem (TRANS("Chn Vibrato"), 21);
    cbxAction->addItem (TRANS("Chn Pitch Bend"), 22);
    cbxAction->addItem (TRANS("Chn Instrument"), 23);
    cbxAction->addItem (TRANS("Chn Transpose"), 24);
    cbxAction->addItem (TRANS("Layer Transpose"), 25);
    cbxAction->addItem (TRANS("Track Note"), 26);
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

    addAndMakeVisible (label3 = new Label ("new label",
                                           TRANS("@Addr: Typ Ch Ly Events")));
    label3->setFont (Font (Font::getDefaultMonospacedFontName(), 14.00f, Font::plain));
    label3->setJustificationType (Justification::centredLeft);
    label3->setEditable (false, false, false);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label4 = new Label ("new label",
                                           TRANS("@Addr: Data           Command")));
    label4->setFont (Font (Font::getDefaultMonospacedFontName(), 14.00f, Font::plain));
    label4->setJustificationType (Justification::centredLeft);
    label4->setEditable (false, false, false);
    label4->setColour (TextEditor::textColourId, Colours::black);
    label4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (optSecSeq = new ToggleButton ("new toggle button"));
    optSecSeq->setButtonText (TRANS("Seq Hdr"));
    optSecSeq->setRadioGroupId (2);
    optSecSeq->addListener (this);

    addAndMakeVisible (optSecChn = new ToggleButton ("new toggle button"));
    optSecChn->setButtonText (TRANS("Chn Hdr"));
    optSecChn->setRadioGroupId (2);
    optSecChn->addListener (this);

    addAndMakeVisible (optSecTrk = new ToggleButton ("new toggle button"));
    optSecTrk->setButtonText (TRANS("Trk Data"));
    optSecTrk->setRadioGroupId (2);
    optSecTrk->addListener (this);

    addAndMakeVisible (btnSeqCmdAdd = new TextButton ("new button"));
    btnSeqCmdAdd->setButtonText (TRANS("Add"));
    btnSeqCmdAdd->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
    btnSeqCmdAdd->addListener (this);

    addAndMakeVisible (btnSeqCmdDelete = new TextButton ("new button"));
    btnSeqCmdDelete->setButtonText (TRANS("Del"));
    btnSeqCmdDelete->setConnectedEdges (Button::ConnectedOnLeft);
    btnSeqCmdDelete->addListener (this);

    addAndMakeVisible (btnSeqCmdUp = new TextButton ("new button"));
    btnSeqCmdUp->setButtonText (TRANS("Up"));
    btnSeqCmdUp->setConnectedEdges (Button::ConnectedOnRight);
    btnSeqCmdUp->addListener (this);

    addAndMakeVisible (btnSeqCmdDn = new TextButton ("new button"));
    btnSeqCmdDn->setButtonText (TRANS("Dn"));
    btnSeqCmdDn->setConnectedEdges (Button::ConnectedOnLeft);
    btnSeqCmdDn->addListener (this);

    addAndMakeVisible (cbxSeqCmdType = new ComboBox ("new combo box"));
    cbxSeqCmdType->setEditableText (false);
    cbxSeqCmdType->setJustificationType (Justification::centredLeft);
    cbxSeqCmdType->setTextWhenNothingSelected (TRANS("[Command to add]"));
    cbxSeqCmdType->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    cbxSeqCmdType->addListener (this);

    addAndMakeVisible (label7 = new Label ("new label",
                                           TRANS("Value:")));
    label7->setFont (Font (15.00f, Font::plain));
    label7->setJustificationType (Justification::centredLeft);
    label7->setEditable (false, false, false);
    label7->setColour (TextEditor::textColourId, Colours::black);
    label7->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (txtSeqCmdValue = new TextEditor ("new text editor"));
    txtSeqCmdValue->setMultiLine (false);
    txtSeqCmdValue->setReturnKeyStartsNewLine (false);
    txtSeqCmdValue->setReadOnly (false);
    txtSeqCmdValue->setScrollbarsShown (true);
    txtSeqCmdValue->setCaretVisible (true);
    txtSeqCmdValue->setPopupMenuEnabled (true);
    txtSeqCmdValue->setText (String::empty);

    addAndMakeVisible (lblSeqInfo = new Label ("new label",
                                               TRANS("Sequence information")));
    lblSeqInfo->setFont (Font (15.00f, Font::plain));
    lblSeqInfo->setJustificationType (Justification::topLeft);
    lblSeqInfo->setEditable (false, false, false);
    lblSeqInfo->setColour (TextEditor::textColourId, Colours::black);
    lblSeqInfo->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (lblSeqCmdAction = new Label ("new label",
                                                    TRANS("Command Action:")));
    lblSeqCmdAction->setFont (Font (15.00f, Font::plain));
    lblSeqCmdAction->setJustificationType (Justification::centredLeft);
    lblSeqCmdAction->setEditable (false, false, false);
    lblSeqCmdAction->setColour (TextEditor::textColourId, Colours::black);
    lblSeqCmdAction->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (lblValueEquiv = new Label ("new label",
                                                  TRANS("[dec, note equiv.]")));
    lblValueEquiv->setFont (Font (15.00f, Font::plain));
    lblValueEquiv->setJustificationType (Justification::centredLeft);
    lblValueEquiv->setEditable (false, false, false);
    lblValueEquiv->setColour (TextEditor::textColourId, Colours::black);
    lblValueEquiv->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (lblSeqCmdAction2 = new Label ("new label",
                                                     TRANS("Sections:")));
    lblSeqCmdAction2->setFont (Font (15.00f, Font::plain));
    lblSeqCmdAction2->setJustificationType (Justification::centredLeft);
    lblSeqCmdAction2->setEditable (false, false, false);
    lblSeqCmdAction2->setColour (TextEditor::textColourId, Colours::black);
    lblSeqCmdAction2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (btnReParse = new TextButton ("new button"));
    btnReParse->setButtonText (TRANS("Re-Parse"));
    btnReParse->addListener (this);


    //[UserPreSize]

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

    lsmSeqSections = new TextListModel();
    lsmSeqSections->setListener(this);
    lsmSeqSections->setFont (Font (Font::getDefaultMonospacedFontName(), 14.00f, Font::plain));

    addAndMakeVisible(lstSeqSections = new ListBox("SeqSections", lsmSeqSections));
    lstSeqSections->setMultipleSelectionEnabled(false);
    lstSeqSections->setRowHeight(16);

    lsmSeqCommands = new TextListModel();
    lsmSeqCommands->setListener(this);
    lsmSeqCommands->setFont (Font (Font::getDefaultMonospacedFontName(), 14.00f, Font::plain));

    addAndMakeVisible(lstSeqCommands = new ListBox("SeqCommands", lsmSeqCommands));
    lstSeqCommands->setMultipleSelectionEnabled(false);
    lstSeqCommands->setRowHeight(16);

    lsmSeqCmdParams = new TextListModel();
    lsmSeqCmdParams->setListener(this);

    addAndMakeVisible(lstSeqCmdParams = new ListBox("SeqCmdParams", lsmSeqCmdParams));
    lstSeqCmdParams->setMultipleSelectionEnabled(false);
    lstSeqCmdParams->setRowHeight(16);


    txtCmdName->addListener(this);
    txtCmd->addListener(this);
    txtCmdEnd->addListener(this);
    txtParamName->addListener(this);
    txtCmdDataSize->addListener(this);
    txtParamAdd->addListener(this);
    txtParamMult->addListener(this);
    txtSeqCmdValue->addListener(this);


    //[/UserPreSize]

    setSize (1000, 632);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

AudioseqPane::~AudioseqPane()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    groupComponent = nullptr;
    groupComponent2 = nullptr;
    groupComponent3 = nullptr;
    groupComponent6 = nullptr;
    groupComponent5 = nullptr;
    label10 = nullptr;
    txtCmd = nullptr;
    btnCmdAdd = nullptr;
    btnCmdDel = nullptr;
    optCmdDataFixed = nullptr;
    optCmdDataVar = nullptr;
    lblCmdDataSize = nullptr;
    txtCmdDataSize = nullptr;
    label11 = nullptr;
    label2 = nullptr;
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
    label3 = nullptr;
    label4 = nullptr;
    optSecSeq = nullptr;
    optSecChn = nullptr;
    optSecTrk = nullptr;
    btnSeqCmdAdd = nullptr;
    btnSeqCmdDelete = nullptr;
    btnSeqCmdUp = nullptr;
    btnSeqCmdDn = nullptr;
    cbxSeqCmdType = nullptr;
    label7 = nullptr;
    txtSeqCmdValue = nullptr;
    lblSeqInfo = nullptr;
    lblSeqCmdAction = nullptr;
    lblValueEquiv = nullptr;
    lblSeqCmdAction2 = nullptr;
    btnReParse = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    lstCommands = nullptr;
    lstParameters = nullptr;
    lstSeqSections = nullptr;
    lstSeqCommands = nullptr;
    lstSeqCmdParams = nullptr;
    lsmCommands = nullptr;
    lsmParameters = nullptr;
    lsmSeqSections = nullptr;
    lsmSeqCommands = nullptr;
    lsmSeqCmdParams = nullptr;
    //[/Destructor]
}

//==============================================================================
void AudioseqPane::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void AudioseqPane::resized()
{
    groupComponent->setBounds (408, 0, 648, 672);
    groupComponent2->setBounds (416, 616, 272, 48);
    groupComponent3->setBounds (0, 0, 400, 672);
    groupComponent6->setBounds (152, 456, 240, 208);
    groupComponent5->setBounds (280, 352, 112, 96);
    label10->setBounds (8, 392, 80, 24);
    txtCmd->setBounds (96, 392, 48, 24);
    btnCmdAdd->setBounds (352, 16, 40, 24);
    btnCmdDel->setBounds (352, 40, 40, 24);
    optCmdDataFixed->setBounds (160, 544, 71, 24);
    optCmdDataVar->setBounds (160, 568, 72, 24);
    lblCmdDataSize->setBounds (240, 552, 47, 24);
    txtCmdDataSize->setBounds (288, 552, 32, 24);
    label11->setBounds (320, 552, 48, 24);
    label2->setBounds (8, 424, 56, 24);
    cbxAction->setBounds (64, 424, 208, 24);
    label9->setBounds (8, 360, 55, 24);
    txtCmdName->setBounds (64, 360, 208, 24);
    txtCmdEnd->setBounds (176, 392, 48, 24);
    label12->setBounds (152, 392, 23, 24);
    optCmdSeq->setBounds (288, 368, 103, 24);
    optCmdChn->setBounds (288, 392, 104, 24);
    optCmdTrk->setBounds (288, 416, 104, 24);
    label13->setBounds (8, 456, 104, 24);
    btnParamAdd->setBounds (104, 480, 40, 24);
    btnParamDel->setBounds (104, 504, 40, 24);
    btnParamUp->setBounds (104, 616, 40, 24);
    btnParamDn->setBounds (104, 640, 40, 24);
    optCmdOffset->setBounds (160, 520, 160, 24);
    label14->setBounds (160, 496, 224, 24);
    label15->setBounds (160, 592, 72, 24);
    txtParamName->setBounds (216, 472, 166, 24);
    label16->setBounds (160, 472, 55, 24);
    cbxMeaning->setBounds (232, 592, 150, 24);
    label17->setBounds (160, 624, 64, 24);
    label18->setBounds (272, 624, 64, 24);
    txtParamAdd->setBounds (224, 624, 47, 24);
    txtParamMult->setBounds (336, 624, 47, 24);
    btnCmdUp->setBounds (352, 296, 40, 24);
    btnCmdDn->setBounds (352, 320, 40, 24);
    label3->setBounds (416, 88, 296, 24);
    label4->setBounds (696, 16, 352, 24);
    optSecSeq->setBounds (424, 632, 80, 24);
    optSecChn->setBounds (512, 632, 80, 24);
    optSecTrk->setBounds (600, 632, 80, 24);
    btnSeqCmdAdd->setBounds (880, 560, 40, 24);
    btnSeqCmdDelete->setBounds (920, 560, 40, 24);
    btnSeqCmdUp->setBounds (968, 560, 40, 24);
    btnSeqCmdDn->setBounds (1008, 560, 40, 24);
    cbxSeqCmdType->setBounds (696, 560, 184, 24);
    label7->setBounds (888, 616, 64, 24);
    txtSeqCmdValue->setBounds (952, 616, 88, 24);
    lblSeqInfo->setBounds (416, 16, 272, 40);
    lblSeqCmdAction->setBounds (696, 592, 352, 24);
    lblValueEquiv->setBounds (888, 640, 152, 24);
    lblSeqCmdAction2->setBounds (416, 64, 120, 24);
    btnReParse->setBounds (536, 64, 150, 24);
    //[UserResized] Add your own custom resize handling here..

    lstCommands->setBounds (8, 16, 336, 328);
    lstParameters->setBounds (8, 480, 88, 184);
    lstSeqSections->setBounds (416, 112, 272, 496);
    lstSeqCommands->setBounds (696, 40, 352, 520);
    lstSeqCmdParams->setBounds (696, 616, 184, 48);

    //[/UserResized]
}

void AudioseqPane::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == btnCmdAdd)
    {
        //[UserButtonCode_btnCmdAdd] -- add your button handler code here..
        ValueTree cmdlistnode = p.romdesc.getOrCreateChildWithName("cmdlist", nullptr);
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
            p.romdesc.getChildWithName("cmdlist").removeChild(pos, nullptr);
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
        ValueTree param("parameter");
        param.setProperty("datasrc", "fixed", nullptr);
        param.setProperty("datalen", 0, nullptr);
        param.setProperty("name", "Unnamed", nullptr);
        param.setProperty("meaning", "None", nullptr);
        param.setProperty("add", 0, nullptr);
        param.setProperty("multiply", 1.0f, nullptr);
        selcmd.addChild(param, selcmd.getNumChildren(), nullptr);
        refreshParamList();
        lstParameters->selectRow(lsmParameters->getNumRows() - 1);
        //[/UserButtonCode_btnParamAdd]
    }
    else if (buttonThatWasClicked == btnParamDel)
    {
        //[UserButtonCode_btnParamDel] -- add your button handler code here..
        int pos = lstParameters->getLastRowSelected();
        if(pos >= 0){
            selcmd.removeChild(pos, nullptr);
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
            selcmd.moveChild(pos, pos-1, nullptr);
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
            selcmd.moveChild(pos, pos+1, nullptr);
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
            p.romdesc.getChildWithName("cmdlist").moveChild(pos, pos-1, nullptr);
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
            p.romdesc.getChildWithName("cmdlist").moveChild(pos, pos+1, nullptr);
            refreshCmdList();
            lstCommands->selectRow(pos+1);
        }
        //[/UserButtonCode_btnCmdDn]
    }
    else if (buttonThatWasClicked == optSecSeq)
    {
        //[UserButtonCode_optSecSeq] -- add your button handler code here..
        //[/UserButtonCode_optSecSeq]
    }
    else if (buttonThatWasClicked == optSecChn)
    {
        //[UserButtonCode_optSecChn] -- add your button handler code here..
        //[/UserButtonCode_optSecChn]
    }
    else if (buttonThatWasClicked == optSecTrk)
    {
        //[UserButtonCode_optSecTrk] -- add your button handler code here..
        //[/UserButtonCode_optSecTrk]
    }
    else if (buttonThatWasClicked == btnSeqCmdAdd)
    {
        //[UserButtonCode_btnSeqCmdAdd] -- add your button handler code here..
        if(&*p.seq == nullptr) return;
        int selsec = lstSeqSections->getLastRowSelected();
        if(selsec < 0 || selsec >= p.seq->getNumSections()) return;
        SeqData* section = p.seq->getSection(selsec);
        int selcmd = lstSeqCommands->getLastRowSelected();
        if(selcmd < 0 || selcmd >= section->cmdoffsets.size()) return;
        uint32 cmdaddr = section->cmdoffsets[selcmd];
        //Calculate the number of bytes to add
        ValueTree cmdlistnode = p.romdesc.getOrCreateChildWithName("cmdlist", nullptr);
        ValueTree cmd = cmdlistnode.getChildWithProperty("name", cbxSeqCmdType->getText());
        if(!cmd.isValid()){
            DBG("No command found with name " + cbxSeqCmdType->getText() + "!");
            return;
        }
        int bytesToAdd = 1;
        ValueTree param;
        String datasrc;
        int datalen;
        for(int i=0; i<cmd.getNumChildren(); i++){
            param = cmd.getChild(i);
            datasrc = param.getProperty("datasrc", "fixed");
            datalen = param.getProperty("datalen", 1);
            if(datasrc == "fixed"){
                bytesToAdd += datalen;
            }else if(datasrc == "variable"){
                bytesToAdd += datalen - 1;
            }
        }
        DBG("Adding " + String(bytesToAdd) + " bytes @" + ROM::hex(cmdaddr,4));
        p.seq->insertSpaceAt(cmdaddr, bytesToAdd, (selcmd != 0));
        p.seq->writeByte(cmdaddr, (int)cmd.getProperty("cmd", 0));
        seqStructureChanged();
        //[/UserButtonCode_btnSeqCmdAdd]
    }
    else if (buttonThatWasClicked == btnSeqCmdDelete)
    {
        //[UserButtonCode_btnSeqCmdDelete] -- add your button handler code here..
        if(&*p.seq == nullptr) return;
        int selsec = lstSeqSections->getLastRowSelected();
        if(selsec < 0 || selsec >= p.seq->getNumSections()) return;
        SeqData* section = p.seq->getSection(selsec);
        int selcmd = lstSeqCommands->getLastRowSelected();
        if(selcmd < 0 || selcmd >= section->cmdoffsets.size()) return;
        uint32 cmdaddr = section->cmdoffsets[selcmd];
        ValueTree command = p.seq->getCommand(cmdaddr, section->stype);
        int len = command.getProperty("length", 1);
        DBG("Removing " + String(len) + " bytes @" + ROM::hex(cmdaddr,4));
        p.seq->removeData(cmdaddr, len, selsec);
        seqStructureChanged();
        //[/UserButtonCode_btnSeqCmdDelete]
    }
    else if (buttonThatWasClicked == btnSeqCmdUp)
    {
        //[UserButtonCode_btnSeqCmdUp] -- add your button handler code here..
        //[/UserButtonCode_btnSeqCmdUp]
    }
    else if (buttonThatWasClicked == btnSeqCmdDn)
    {
        //[UserButtonCode_btnSeqCmdDn] -- add your button handler code here..
        //[/UserButtonCode_btnSeqCmdDn]
    }
    else if (buttonThatWasClicked == btnReParse)
    {
        //[UserButtonCode_btnReParse] -- add your button handler code here..
        seqStructureChanged();
        //[/UserButtonCode_btnReParse]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void AudioseqPane::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
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
    else if (comboBoxThatHasChanged == cbxSeqCmdType)
    {
        //[UserComboBoxCode_cbxSeqCmdType] -- add your combo box handling code here..
        //[/UserComboBoxCode_cbxSeqCmdType]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void AudioseqPane::visibilityChanged()
{
    //[UserCode_visibilityChanged] -- Add your code here...
    //[/UserCode_visibilityChanged]
}

void AudioseqPane::broughtToFront()
{
    //[UserCode_broughtToFront] -- Add your code here...
    //fillSeqSections();
    //[/UserCode_broughtToFront]
}

void AudioseqPane::focusGained (FocusChangeType cause)
{
    //[UserCode_focusGained] -- Add your code here...
    //fillSeqSections();
    //[/UserCode_focusGained]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void AudioseqPane::rowSelected(TextListModel* parent, int row){
    if(parent == &*lsmCommands){
        ValueTree cmdlistnode = p.romdesc.getOrCreateChildWithName("cmdlist", nullptr);
        selcmd = cmdlistnode.getChild(row);
        refreshCmdControls();
    }else if(parent == &*lsmParameters){
        selparam = selcmd.getChild(row);
        refreshParamControls();
    }else if(parent == &*lsmSeqSections){
        fillSeqCommands();
    }else if(parent == &*lsmSeqCommands){
        refreshSeqCmdControls();
    }else if(parent == &*lsmSeqCmdParams){
        refreshSeqCmdParamControls();
    }
}

void AudioseqPane::textEditorTextChanged(TextEditor& editorThatWasChanged){
    int val;
    String text = editorThatWasChanged.getText();
    if(        &editorThatWasChanged == &*txtParamAdd
            || &editorThatWasChanged == &*txtCmdDataSize){
        val = text.getIntValue();
    }else{
        val = text.getHexValue32();
    }
    bool turnRed = (val <= 0);
    bool redrawCmdItem = false;

    if(&editorThatWasChanged == &*txtCmdName){
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
    }else if(&editorThatWasChanged == &*txtSeqCmdValue){
        if(&*p.seq == nullptr) return;
        int selsec = lstSeqSections->getLastRowSelected();
            if(selsec < 0 || selsec >= p.seq->getNumSections()) return;
            SeqData* section = p.seq->getSection(selsec);
        int selcmd = lstSeqCommands->getLastRowSelected();
            if(selcmd < 0 || selcmd >= section->cmdoffsets.size()) return;
            uint32 cmdaddr = section->cmdoffsets[selcmd];
            ValueTree cmd = p.seq->getCommand(cmdaddr, section->stype);
        int selparam = lstSeqCmdParams->getLastRowSelected();
            if(selparam < 0 || selparam >= cmd.getNumChildren()) return;
            ValueTree param = cmd.getChild(selparam);
        int ret = p.seq->editCmdParam(selsec, cmdaddr, section->stype, param.getProperty("meaning", "None"), val);
        turnRed = (ret < 0);
        if(ret > 0){
            seqStructureChanged();
        }else if(ret == 0){
            lsmSeqCommands->set(selcmd, p.seq->getCommandDescription(selsec, selcmd));
            lstSeqCommands->repaintRow(selcmd);
        }
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

}


void AudioseqPane::refreshCmdControls(){
    if(selcmd.isValid()){
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
    }else{
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
    }
    refreshParamList();
}

void AudioseqPane::refreshParamControls(){
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

void AudioseqPane::refreshCmdList(){
    lsmCommands->clear();
    lstCommands->updateContent();
    ValueTree cmdlistnode = p.romdesc.getOrCreateChildWithName("cmdlist", nullptr);
    ValueTree cmd;
    String desc;
    for(int i=0; i<cmdlistnode.getNumChildren(); i++){
        cmd = cmdlistnode.getChild(i);
        if(cmd.getType() == Identifier("command")){
            lsmCommands->add(getCommandDesc(cmd));
        }
    }
    lstCommands->updateContent();
}
void AudioseqPane::refreshParamList(){
    lsmParameters->clear();
    lstParameters->updateContent();
    if(selcmd.isValid()){
        ValueTree param;
        for(int i=0; i<selcmd.getNumChildren(); i++){
            param = selcmd.getChild(i);
            if(param.getType() == Identifier("parameter")){
                lsmParameters->add(String(i));
            }
        }
    }
    lstParameters->updateContent();
}

String AudioseqPane::getCommandDesc(ValueTree cmd){
    String desc = ROM::hex((uint8)(int)cmd.getProperty("cmd", 0));
    if(cmd.hasProperty("cmdend")){
        desc += " to " + ROM::hex((uint8)(int)cmd.getProperty("cmdend", 0));
    }
    desc += ": " + cmd.getProperty("name").toString();
    desc += " (" + cmd.getProperty("action").toString() + ")";
    return desc;
}


void AudioseqPane::fillMeaningsBox(String action){
    cbxMeaning->clear(dontSendNotification);
    cbxMeaning->addItem("None", cbxMeaning->getNumItems()+1);
    cbxMeaning->addItem("Delay", cbxMeaning->getNumItems()+1);
    if(action == "No Action"){
        //None
    }else if(action == "End of Data"){
        //None
    }else if(action == "Timestamp"){
        //None--use Delay
    }else if(action == "Jump Same Level"){
        cbxMeaning->addItem("Absolute Address", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("Relative Address", cbxMeaning->getNumItems()+1);
    }else if(action == "Call Same Level"){
        cbxMeaning->addItem("Absolute Address", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("Relative Address", cbxMeaning->getNumItems()+1);
    }else if(action == "Loop Start"){
        cbxMeaning->addItem("Loop Count", cbxMeaning->getNumItems()+1);
    }else if(action == "Loop End"){
        //None
    }else if(action == "Ptr Channel Header"){
        cbxMeaning->addItem("Channel", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("Absolute Address", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("Relative Address", cbxMeaning->getNumItems()+1);
    }else if(action == "Ptr Track Data"){
        cbxMeaning->addItem("Note Layer", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("Absolute Address", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("Relative Address", cbxMeaning->getNumItems()+1);
    }else if(action == "Sequence Format"){
        cbxMeaning->addItem("Value", cbxMeaning->getNumItems()+1);
    }else if(action == "Sequence Type"){
        cbxMeaning->addItem("Value", cbxMeaning->getNumItems()+1);
    }else if(action == "Channel Enable"){
        cbxMeaning->addItem("Bitfield", cbxMeaning->getNumItems()+1);
    }else if(action == "Channel Disable"){
        cbxMeaning->addItem("Bitfield", cbxMeaning->getNumItems()+1);
    }else if(action == "Master Volume"){
        cbxMeaning->addItem("Value", cbxMeaning->getNumItems()+1);
    }else if(action == "Tempo"){
        cbxMeaning->addItem("Value", cbxMeaning->getNumItems()+1);
    }else if(action == "Chn Reset"){
        //None
    }else if(action == "Chn Priority"){
        cbxMeaning->addItem("Value", cbxMeaning->getNumItems()+1);
    }else if(action == "Chn Volume"){
        cbxMeaning->addItem("Value", cbxMeaning->getNumItems()+1);
    }else if(action == "Chn Pan"){
        cbxMeaning->addItem("Value", cbxMeaning->getNumItems()+1);
    }else if(action == "Chn Effects"){
        cbxMeaning->addItem("Value", cbxMeaning->getNumItems()+1);
    }else if(action == "Chn Vibrato"){
        cbxMeaning->addItem("Value", cbxMeaning->getNumItems()+1);
    }else if(action == "Chn Pitch Bend"){
        cbxMeaning->addItem("Value", cbxMeaning->getNumItems()+1);
    }else if(action == "Chn Transpose"){
        cbxMeaning->addItem("Value", cbxMeaning->getNumItems()+1);
    }else if(action == "Layer Transpose"){
        cbxMeaning->addItem("Value", cbxMeaning->getNumItems()+1);
    }else if(action == "Chn Instrument"){
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

void AudioseqPane::fillSeqSections(){
    if(&*p.seq == nullptr) return;
    lsmSeqSections->clear();
    lstSeqSections->updateContent();
    for(int s=0; s<p.seq->getNumSections(); s++){
        lsmSeqSections->add(p.seq->getSectionDescription(s));
    }
    String seqinfo = "Sequence ";
    if(p.seq->name != ""){
        seqinfo += "\"" + p.seq->name + "\"";
    }
    seqinfo += ": length " + ROM::hex(p.seq->getLength(), 4);
    seqinfo += " (" + String(p.seq->getNumSections()) + " sections)";
    lblSeqInfo->setText(seqinfo, dontSendNotification);
    lstSeqSections->updateContent();
}

void AudioseqPane::fillSeqCommands(){
    int selcmd = lstSeqCommands->getLastRowSelected();
    lsmSeqCommands->clear();
    lstSeqCommands->updateContent();
    if(&*p.seq == nullptr) return;
    int selsec = lstSeqSections->getLastRowSelected();
    if(selsec < 0 || selsec >= p.seq->getNumSections()) return;
    int cmds = p.seq->getSection(selsec)->cmdoffsets.size();
    for(int c=0; c<cmds; c++){
        lsmSeqCommands->add(p.seq->getCommandDescription(selsec, c));
    }
    lstSeqCommands->updateContent();
    lstSeqCommands->selectRow(selcmd);
    //Fill New Command box
    cbxSeqCmdType->clear(dontSendNotification);
    int stype = p.seq->getSection(selsec)->stype;
    ValueTree cmdlistnode = p.romdesc.getOrCreateChildWithName("cmdlist", nullptr);
    ValueTree cmd;
    String desc;
    for(int i=0; i<cmdlistnode.getNumChildren(); i++){
        cmd = cmdlistnode.getChild(i);
        if(cmd.getType() == Identifier("command")){
            if((stype == 0 && (bool)cmd.getProperty("validinseq", false))
                    || (stype == 1 && (bool)cmd.getProperty("validinchn", false))
                    || (stype == 2 && (bool)cmd.getProperty("validintrk", false))){
                cbxSeqCmdType->addItem(cmd.getProperty("name", "ERROR").toString(), cbxSeqCmdType->getNumItems()+1);
            }
        }
    }
    cbxMeaning->setSelectedItemIndex(0, dontSendNotification);
}


void AudioseqPane::refreshSeqCmdControls(){
    if(&*p.seq == nullptr) return;
    int selparam = lstSeqCmdParams->getLastRowSelected();
    int selsec = lstSeqSections->getLastRowSelected();
    if(selsec < 0 || selsec >= p.seq->getNumSections()) return;
    SeqData* section = p.seq->getSection(selsec);
    int selcmd = lstSeqCommands->getLastRowSelected();
    if(selcmd < 0 || selcmd >= section->cmdoffsets.size()) return;
    uint32 cmdaddr = section->cmdoffsets[selcmd];
    ValueTree cmd = p.seq->getCommand(cmdaddr, section->stype);
    lblSeqCmdAction->setText("Command Action: " + cmd.getProperty("action", "No Action").toString(), dontSendNotification);
    ValueTree param;
    lsmSeqCmdParams->clear();
    lstSeqCmdParams->updateContent();
    int params = cmd.getNumChildren();
    for(int i=0; i<params; i++){
        param = cmd.getChild(i);
        lsmSeqCmdParams->add(param.getProperty("name", "Unnamed"));
    }
    lstSeqCmdParams->updateContent();
    lstSeqCmdParams->selectRow(selparam);
}

void AudioseqPane::refreshSeqCmdParamControls(){
    if(&*p.seq == nullptr) return;
    int selsec = lstSeqSections->getLastRowSelected();
        if(selsec < 0 || selsec >= p.seq->getNumSections()){
            txtSeqCmdValue->setText("", dontSendNotification);
            return;
        }
        SeqData* section = p.seq->getSection(selsec);
    int selcmd = lstSeqCommands->getLastRowSelected();
        if(selcmd < 0 || selcmd >= section->cmdoffsets.size()){
            txtSeqCmdValue->setText("", dontSendNotification);
            return;
        }
        uint32 cmdaddr = section->cmdoffsets[selcmd];
        ValueTree cmd = p.seq->getCommand(cmdaddr, section->stype);
    int selparam = lstSeqCmdParams->getLastRowSelected();
        if(selparam < 0 || selparam >= cmd.getNumChildren()){
            txtSeqCmdValue->setText("", dontSendNotification);
            return;
        }
        ValueTree param = cmd.getChild(selparam);
    int len = (int)param.getProperty("datalen", 1) * 2;
    if(len <= 0) len = 2;
    txtSeqCmdValue->setText(ROM::hex((uint32)(int)param.getProperty("value", 0),
            len), dontSendNotification);
}

void AudioseqPane::seqStructureChanged(){
    if(&*p.seq == nullptr) return;
    int selsec = lstSeqSections->getLastRowSelected();
    p.seq->parse();
    fillSeqSections();
    lstSeqSections->selectRow(selsec);
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="AudioseqPane" componentName=""
                 parentClasses="public Component, public TextEditor::Listener, public TextListModel::Listener"
                 constructorParams="AppProps&amp; props" variableInitialisers="p(props)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="1000" initialHeight="632">
  <METHODS>
    <METHOD name="focusGained (FocusChangeType cause)"/>
    <METHOD name="visibilityChanged()"/>
    <METHOD name="broughtToFront()"/>
  </METHODS>
  <BACKGROUND backgroundColour="ffffffff"/>
  <GROUPCOMPONENT name="new group" id="b3355c52e381c7e5" memberName="groupComponent"
                  virtualName="" explicitFocusOrder="0" pos="408 0 648 672" title="Loaded Sequence"/>
  <GROUPCOMPONENT name="new group" id="6e58ac86762caa1" memberName="groupComponent2"
                  virtualName="" explicitFocusOrder="0" pos="416 616 272 48" title="Section is"/>
  <GROUPCOMPONENT name="new group" id="f1d4a599b3267719" memberName="groupComponent3"
                  virtualName="" explicitFocusOrder="0" pos="0 0 400 672" title="Command Editor"/>
  <GROUPCOMPONENT name="new group" id="977c50d4ba0f1784" memberName="groupComponent6"
                  virtualName="" explicitFocusOrder="0" pos="152 456 240 208" title="Edit Parameter"/>
  <GROUPCOMPONENT name="new group" id="b9f9c4c5353e7b92" memberName="groupComponent5"
                  virtualName="" explicitFocusOrder="0" pos="280 352 112 96" title="Valid in"/>
  <LABEL name="new label" id="120e7da910b9fa36" memberName="label10" virtualName=""
         explicitFocusOrder="0" pos="8 392 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Command:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="c17bf80cbae3b9bf" memberName="txtCmd"
              virtualName="" explicitFocusOrder="0" pos="96 392 48 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTBUTTON name="new button" id="33646eda08c514f8" memberName="btnCmdAdd"
              virtualName="" explicitFocusOrder="0" pos="352 16 40 24" buttonText="Add"
              connectedEdges="8" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="4ad518eab3cf4e38" memberName="btnCmdDel"
              virtualName="" explicitFocusOrder="0" pos="352 40 40 24" buttonText="Del"
              connectedEdges="4" needsCallback="1" radioGroupId="0"/>
  <TOGGLEBUTTON name="new toggle button" id="de7cafa15549ae99" memberName="optCmdDataFixed"
                virtualName="" explicitFocusOrder="0" pos="160 544 71 24" buttonText="Fixed"
                connectedEdges="0" needsCallback="1" radioGroupId="1" state="1"/>
  <TOGGLEBUTTON name="new toggle button" id="1ac143856715712c" memberName="optCmdDataVar"
                virtualName="" explicitFocusOrder="0" pos="160 568 72 24" buttonText="Variable"
                connectedEdges="0" needsCallback="1" radioGroupId="1" state="0"/>
  <LABEL name="new label" id="5ef4448d8600da02" memberName="lblCmdDataSize"
         virtualName="" explicitFocusOrder="0" pos="240 552 47 24" edTextCol="ff000000"
         edBkgCol="0" labelText="length" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtCmdDat" id="6db88ac89d3dcd1d" memberName="txtCmdDataSize"
              virtualName="" explicitFocusOrder="0" pos="288 552 32 24" initialText="1"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="63098370e332d46f" memberName="label11" virtualName=""
         explicitFocusOrder="0" pos="320 552 48 24" edTextCol="ff000000"
         edBkgCol="0" labelText="(dec)" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="1260a931f1b77e50" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="8 424 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Action:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <COMBOBOX name="Action" id="4cabd0b9e2965ff5" memberName="cbxAction" virtualName=""
            explicitFocusOrder="0" pos="64 424 208 24" editable="0" layout="33"
            items="No Action&#10;End of Data&#10;Timestamp&#10;Jump Same Level&#10;Call Same Level&#10;Loop Start&#10;Loop End&#10;Ptr Channel Header&#10;Ptr Track Data&#10;Sequence Format&#10;Sequence Type&#10;Channel Enable&#10;Channel Disable&#10;Master Volume&#10;Tempo&#10;Chn Reset&#10;Chn Priority&#10;Chn Volume&#10;Chn Pan&#10;Chn Effects&#10;Chn Vibrato&#10;Chn Pitch Bend&#10;Chn Instrument&#10;Chn Transpose&#10;Layer Transpose&#10;Track Note"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="6d034f22b803ef0c" memberName="label9" virtualName=""
         explicitFocusOrder="0" pos="8 360 55 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Name:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="17aae1e70c35fd59" memberName="txtCmdName"
              virtualName="" explicitFocusOrder="0" pos="64 360 208 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="new text editor" id="391e87c7412baa15" memberName="txtCmdEnd"
              virtualName="" explicitFocusOrder="0" pos="176 392 48 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="2dce25261c0a7641" memberName="label12" virtualName=""
         explicitFocusOrder="0" pos="152 392 23 24" edTextCol="ff000000"
         edBkgCol="0" labelText="to" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TOGGLEBUTTON name="new toggle button" id="6760f7dd9298e144" memberName="optCmdSeq"
                virtualName="" explicitFocusOrder="0" pos="288 368 103 24" buttonText="Seq header"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="e198702d72e71f55" memberName="optCmdChn"
                virtualName="" explicitFocusOrder="0" pos="288 392 104 24" buttonText="Chn header"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="d079eea3af0c26a4" memberName="optCmdTrk"
                virtualName="" explicitFocusOrder="0" pos="288 416 104 24" buttonText="Track data"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <LABEL name="new label" id="5666e65f925f98ec" memberName="label13" virtualName=""
         explicitFocusOrder="0" pos="8 456 104 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Parameters:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="new button" id="972d79b803f377c4" memberName="btnParamAdd"
              virtualName="" explicitFocusOrder="0" pos="104 480 40 24" buttonText="Add"
              connectedEdges="8" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="1ba257bf64ce7e89" memberName="btnParamDel"
              virtualName="" explicitFocusOrder="0" pos="104 504 40 24" buttonText="Del"
              connectedEdges="4" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="2f3dd0a3ebcb78d5" memberName="btnParamUp"
              virtualName="" explicitFocusOrder="0" pos="104 616 40 24" buttonText="Up"
              connectedEdges="8" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="cee83a628d87bd1a" memberName="btnParamDn"
              virtualName="" explicitFocusOrder="0" pos="104 640 40 24" buttonText="Dn"
              connectedEdges="4" needsCallback="1" radioGroupId="0"/>
  <TOGGLEBUTTON name="new toggle button" id="3134f7ae28bcfdd3" memberName="optCmdOffset"
                virtualName="" explicitFocusOrder="0" pos="160 520 160 24" buttonText="Cmd Offset (no data)"
                connectedEdges="0" needsCallback="1" radioGroupId="1" state="0"/>
  <LABEL name="new label" id="9da40dae5b71c4cf" memberName="label14" virtualName=""
         explicitFocusOrder="0" pos="160 496 224 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Data source:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="eed9a48d3bb5e03b" memberName="label15" virtualName=""
         explicitFocusOrder="0" pos="160 592 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Meaning:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="b867bd3ceb8e1203" memberName="txtParamName"
              virtualName="" explicitFocusOrder="0" pos="216 472 166 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="8306c58890811511" memberName="label16" virtualName=""
         explicitFocusOrder="0" pos="160 472 55 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Name:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <COMBOBOX name="Meaning" id="5955524ab0ec02c1" memberName="cbxMeaning"
            virtualName="" explicitFocusOrder="0" pos="232 592 150 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="8d5abd7e709bfe4f" memberName="label17" virtualName=""
         explicitFocusOrder="0" pos="160 624 64 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Add (dec):" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="9a94c821168285dc" memberName="label18" virtualName=""
         explicitFocusOrder="0" pos="272 624 64 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Multiply:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="d44ee99ec4017196" memberName="txtParamAdd"
              virtualName="" explicitFocusOrder="0" pos="224 624 47 24" initialText="0"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="new text editor" id="9adbc3822f7d0ac1" memberName="txtParamMult"
              virtualName="" explicitFocusOrder="0" pos="336 624 47 24" initialText="1.0"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTBUTTON name="new button" id="5c1f23230407fcb1" memberName="btnCmdUp"
              virtualName="" explicitFocusOrder="0" pos="352 296 40 24" buttonText="Up"
              connectedEdges="8" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="98d71ec28a9ccb5f" memberName="btnCmdDn"
              virtualName="" explicitFocusOrder="0" pos="352 320 40 24" buttonText="Dn"
              connectedEdges="4" needsCallback="1" radioGroupId="0"/>
  <LABEL name="new label" id="cfb894eaf50ddd48" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="416 88 296 24" edTextCol="ff000000"
         edBkgCol="0" labelText="@Addr: Typ Ch Ly Events" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default monospaced font"
         fontsize="14" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="eafcae42c6686b48" memberName="label4" virtualName=""
         explicitFocusOrder="0" pos="696 16 352 24" edTextCol="ff000000"
         edBkgCol="0" labelText="@Addr: Data           Command" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default monospaced font"
         fontsize="14" bold="0" italic="0" justification="33"/>
  <TOGGLEBUTTON name="new toggle button" id="cf47b7f68371eb95" memberName="optSecSeq"
                virtualName="" explicitFocusOrder="0" pos="424 632 80 24" buttonText="Seq Hdr"
                connectedEdges="0" needsCallback="1" radioGroupId="2" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="a6c764d49706b110" memberName="optSecChn"
                virtualName="" explicitFocusOrder="0" pos="512 632 80 24" buttonText="Chn Hdr"
                connectedEdges="0" needsCallback="1" radioGroupId="2" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="653c215535bfa70a" memberName="optSecTrk"
                virtualName="" explicitFocusOrder="0" pos="600 632 80 24" buttonText="Trk Data"
                connectedEdges="0" needsCallback="1" radioGroupId="2" state="0"/>
  <TEXTBUTTON name="new button" id="cf3f95690aa55b7c" memberName="btnSeqCmdAdd"
              virtualName="" explicitFocusOrder="0" pos="880 560 40 24" buttonText="Add"
              connectedEdges="3" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="9661fb86a4ef0a7c" memberName="btnSeqCmdDelete"
              virtualName="" explicitFocusOrder="0" pos="920 560 40 24" buttonText="Del"
              connectedEdges="1" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="322ab17ff1c48b0f" memberName="btnSeqCmdUp"
              virtualName="" explicitFocusOrder="0" pos="968 560 40 24" buttonText="Up"
              connectedEdges="2" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="24ae8e838a4add93" memberName="btnSeqCmdDn"
              virtualName="" explicitFocusOrder="0" pos="1008 560 40 24" buttonText="Dn"
              connectedEdges="1" needsCallback="1" radioGroupId="0"/>
  <COMBOBOX name="new combo box" id="91d638859dfe0501" memberName="cbxSeqCmdType"
            virtualName="" explicitFocusOrder="0" pos="696 560 184 24" editable="0"
            layout="33" items="" textWhenNonSelected="[Command to add]" textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="1ef07cd6fece0549" memberName="label7" virtualName=""
         explicitFocusOrder="0" pos="888 616 64 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Value:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="28b2ef3b6fe44f9a" memberName="txtSeqCmdValue"
              virtualName="" explicitFocusOrder="0" pos="952 616 88 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="a69b237684dc0a0d" memberName="lblSeqInfo"
         virtualName="" explicitFocusOrder="0" pos="416 16 272 40" edTextCol="ff000000"
         edBkgCol="0" labelText="Sequence information" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="9"/>
  <LABEL name="new label" id="4b6f4c5b150b8e9" memberName="lblSeqCmdAction"
         virtualName="" explicitFocusOrder="0" pos="696 592 352 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Command Action:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="44ea1cfa0e02c008" memberName="lblValueEquiv"
         virtualName="" explicitFocusOrder="0" pos="888 640 152 24" edTextCol="ff000000"
         edBkgCol="0" labelText="[dec, note equiv.]" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="e7b46dfed4aed5ba" memberName="lblSeqCmdAction2"
         virtualName="" explicitFocusOrder="0" pos="416 64 120 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Sections:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="new button" id="45d2e07ee4fefabe" memberName="btnReParse"
              virtualName="" explicitFocusOrder="0" pos="536 64 150 24" buttonText="Re-Parse"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

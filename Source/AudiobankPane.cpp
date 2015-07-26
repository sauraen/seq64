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

#include "AudiobankPane.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
AudiobankPane::AudiobankPane (AppProps& props)
    : p(props)
{
    addAndMakeVisible (groupComponent2 = new GroupComponent ("new group",
                                                             TRANS("Audiobank Library")));

    addAndMakeVisible (groupComponent3 = new GroupComponent ("new group",
                                                             TRANS("Loaded Bank")));

    addAndMakeVisible (groupComponent = new GroupComponent ("new group",
                                                            TRANS("Audiobank File Data Structures")));

    addAndMakeVisible (cbxEditStruct = new ComboBox ("new combo box"));
    cbxEditStruct->setEditableText (false);
    cbxEditStruct->setJustificationType (Justification::centredLeft);
    cbxEditStruct->setTextWhenNothingSelected (String::empty);
    cbxEditStruct->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    cbxEditStruct->addItem (TRANS("ABIndexEntry"), 1);
    cbxEditStruct->addItem (TRANS("ABHeader"), 2);
    cbxEditStruct->addItem (TRANS("ABBank"), 3);
    cbxEditStruct->addItem (TRANS("ABDrumList"), 4);
    cbxEditStruct->addItem (TRANS("ABSFXList"), 5);
    cbxEditStruct->addItem (TRANS("ABInstrument"), 6);
    cbxEditStruct->addItem (TRANS("ABDrum"), 7);
    cbxEditStruct->addItem (TRANS("ABPatchProps"), 8);
    cbxEditStruct->addItem (TRANS("ABSound"), 9);
    cbxEditStruct->addItem (TRANS("ABSample"), 10);
    cbxEditStruct->addItem (TRANS("ALADPCMBook"), 11);
    cbxEditStruct->addItem (TRANS("ALADPCMPredictor"), 12);
    cbxEditStruct->addItem (TRANS("ALADPCMLoop"), 13);
    cbxEditStruct->addItem (TRANS("ALADPCMTail"), 14);
    cbxEditStruct->addListener (this);

    addAndMakeVisible (label2 = new Label ("new label",
                                           TRANS("Data Type:")));
    label2->setFont (Font (15.00f, Font::plain));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (optPointer = new ToggleButton ("new toggle button"));
    optPointer->setButtonText (TRANS("Ptr To:"));
    optPointer->addListener (this);

    addAndMakeVisible (cbxDataType = new ComboBox ("new combo box"));
    cbxDataType->setEditableText (false);
    cbxDataType->setJustificationType (Justification::centredLeft);
    cbxDataType->setTextWhenNothingSelected (String::empty);
    cbxDataType->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    cbxDataType->addItem (TRANS("uint8"), 1);
    cbxDataType->addItem (TRANS("uint16"), 2);
    cbxDataType->addItem (TRANS("uint32"), 3);
    cbxDataType->addItem (TRANS("int8"), 4);
    cbxDataType->addItem (TRANS("int16"), 5);
    cbxDataType->addItem (TRANS("int32"), 6);
    cbxDataType->addItem (TRANS("ABSound"), 7);
    cbxDataType->addItem (TRANS("ALADPCMPredictor"), 8);
    cbxDataType->addItem (TRANS("ALADPCMTail"), 9);
    cbxDataType->addListener (this);

    addAndMakeVisible (cbxPtrTo = new ComboBox ("new combo box"));
    cbxPtrTo->setEditableText (false);
    cbxPtrTo->setJustificationType (Justification::centredLeft);
    cbxPtrTo->setTextWhenNothingSelected (String::empty);
    cbxPtrTo->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    cbxPtrTo->addItem (TRANS("ABHeader"), 1);
    cbxPtrTo->addItem (TRANS("ABDrumList"), 2);
    cbxPtrTo->addItem (TRANS("ABSFXList"), 3);
    cbxPtrTo->addItem (TRANS("ABInstrument"), 4);
    cbxPtrTo->addItem (TRANS("ABDrum"), 5);
    cbxPtrTo->addItem (TRANS("ABPatchProps"), 6);
    cbxPtrTo->addItem (TRANS("ABSample"), 7);
    cbxPtrTo->addItem (TRANS("ATSample"), 8);
    cbxPtrTo->addItem (TRANS("ALADPCMBook"), 9);
    cbxPtrTo->addItem (TRANS("ALADPCMLoop"), 10);
    cbxPtrTo->addListener (this);

    addAndMakeVisible (label3 = new Label ("new label",
                                           TRANS("Name:")));
    label3->setFont (Font (15.00f, Font::plain));
    label3->setJustificationType (Justification::centredLeft);
    label3->setEditable (false, false, false);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (txtFieldName = new TextEditor ("new text editor"));
    txtFieldName->setMultiLine (false);
    txtFieldName->setReturnKeyStartsNewLine (false);
    txtFieldName->setReadOnly (false);
    txtFieldName->setScrollbarsShown (true);
    txtFieldName->setCaretVisible (true);
    txtFieldName->setPopupMenuEnabled (true);
    txtFieldName->setText (String::empty);

    addAndMakeVisible (optArray = new ToggleButton ("new toggle button"));
    optArray->setButtonText (TRANS("Array:"));
    optArray->addListener (this);

    addAndMakeVisible (optArrayFixed = new ToggleButton ("new toggle button"));
    optArrayFixed->setButtonText (TRANS("Fixed:"));
    optArrayFixed->setRadioGroupId (1);
    optArrayFixed->addListener (this);

    addAndMakeVisible (optArrayVar = new ToggleButton ("new toggle button"));
    optArrayVar->setButtonText (TRANS("Variable:"));
    optArrayVar->setRadioGroupId (1);
    optArrayVar->addListener (this);

    addAndMakeVisible (txtArrayLen = new TextEditor ("new text editor"));
    txtArrayLen->setMultiLine (false);
    txtArrayLen->setReturnKeyStartsNewLine (false);
    txtArrayLen->setReadOnly (false);
    txtArrayLen->setScrollbarsShown (true);
    txtArrayLen->setCaretVisible (true);
    txtArrayLen->setPopupMenuEnabled (true);
    txtArrayLen->setText (String::empty);

    addAndMakeVisible (cbxArrayLenVar = new ComboBox ("new combo box"));
    cbxArrayLenVar->setEditableText (false);
    cbxArrayLenVar->setJustificationType (Justification::centredLeft);
    cbxArrayLenVar->setTextWhenNothingSelected (String::empty);
    cbxArrayLenVar->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    cbxArrayLenVar->addItem (TRANS("NUM_BANK"), 1);
    cbxArrayLenVar->addItem (TRANS("NUM_INST"), 2);
    cbxArrayLenVar->addItem (TRANS("NUM_DRUM"), 3);
    cbxArrayLenVar->addItem (TRANS("NUM_SFX"), 4);
    cbxArrayLenVar->addItem (TRANS("NUM_PRED"), 5);
    cbxArrayLenVar->addItem (TRANS("HAS_TAIL"), 6);
    cbxArrayLenVar->addListener (this);

    addAndMakeVisible (label4 = new Label ("new label",
                                           TRANS("Meaning:")));
    label4->setFont (Font (15.00f, Font::plain));
    label4->setJustificationType (Justification::centredLeft);
    label4->setEditable (false, false, false);
    label4->setColour (TextEditor::textColourId, Colours::black);
    label4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (cbxMeaning = new ComboBox ("new combo box"));
    cbxMeaning->setEditableText (false);
    cbxMeaning->setJustificationType (Justification::centredLeft);
    cbxMeaning->setTextWhenNothingSelected (String::empty);
    cbxMeaning->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    cbxMeaning->addListener (this);

    addAndMakeVisible (lblStructBegin = new Label ("new label",
                                                   TRANS("typedef struct {                        //Align all to:                bytes")));
    lblStructBegin->setFont (Font (15.00f, Font::plain));
    lblStructBegin->setJustificationType (Justification::centredLeft);
    lblStructBegin->setEditable (false, false, false);
    lblStructBegin->setColour (TextEditor::textColourId, Colours::black);
    lblStructBegin->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (lblStructEnd = new Label ("new label",
                                                 TRANS("}")));
    lblStructEnd->setFont (Font (15.00f, Font::plain));
    lblStructEnd->setJustificationType (Justification::centredLeft);
    lblStructEnd->setEditable (false, false, false);
    lblStructEnd->setColour (TextEditor::textColourId, Colours::black);
    lblStructEnd->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label5 = new Label ("new label",
                                           TRANS("Default value:")));
    label5->setFont (Font (15.00f, Font::plain));
    label5->setJustificationType (Justification::centredLeft);
    label5->setEditable (false, false, false);
    label5->setColour (TextEditor::textColourId, Colours::black);
    label5->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (txtDefaultVal = new TextEditor ("new text editor"));
    txtDefaultVal->setMultiLine (false);
    txtDefaultVal->setReturnKeyStartsNewLine (false);
    txtDefaultVal->setReadOnly (false);
    txtDefaultVal->setScrollbarsShown (true);
    txtDefaultVal->setCaretVisible (true);
    txtDefaultVal->setPopupMenuEnabled (true);
    txtDefaultVal->setText (String::empty);

    addAndMakeVisible (btnFieldAdd = new TextButton ("new button"));
    btnFieldAdd->setButtonText (TRANS("Add"));
    btnFieldAdd->setConnectedEdges (Button::ConnectedOnRight);
    btnFieldAdd->addListener (this);

    addAndMakeVisible (btnFieldDel = new TextButton ("new button"));
    btnFieldDel->setButtonText (TRANS("Del"));
    btnFieldDel->setConnectedEdges (Button::ConnectedOnLeft);
    btnFieldDel->addListener (this);

    addAndMakeVisible (btnFieldUp = new TextButton ("new button"));
    btnFieldUp->setButtonText (TRANS("Up"));
    btnFieldUp->setConnectedEdges (Button::ConnectedOnRight);
    btnFieldUp->addListener (this);

    addAndMakeVisible (btnFieldDn = new TextButton ("new button"));
    btnFieldDn->setButtonText (TRANS("Dn"));
    btnFieldDn->setConnectedEdges (Button::ConnectedOnLeft);
    btnFieldDn->addListener (this);

    addAndMakeVisible (label6 = new Label ("new label",
                                           TRANS("(hex)")));
    label6->setFont (Font (15.00f, Font::plain));
    label6->setJustificationType (Justification::centredLeft);
    label6->setEditable (false, false, false);
    label6->setColour (TextEditor::textColourId, Colours::black);
    label6->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label7 = new Label ("new label",
                                           TRANS("0x")));
    label7->setFont (Font (15.00f, Font::plain));
    label7->setJustificationType (Justification::centredLeft);
    label7->setEditable (false, false, false);
    label7->setColour (TextEditor::textColourId, Colours::black);
    label7->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (lblStructSemicolon = new Label ("new label",
                                                       TRANS(";   //Fields:")));
    lblStructSemicolon->setFont (Font (15.00f, Font::plain));
    lblStructSemicolon->setJustificationType (Justification::centredLeft);
    lblStructSemicolon->setEditable (false, false, false);
    lblStructSemicolon->setColour (TextEditor::textColourId, Colours::black);
    lblStructSemicolon->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("Instrument sets:")));
    label->setFont (Font (15.00f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (textEditor = new TextEditor ("new text editor"));
    textEditor->setMultiLine (false);
    textEditor->setReturnKeyStartsNewLine (false);
    textEditor->setReadOnly (false);
    textEditor->setScrollbarsShown (true);
    textEditor->setCaretVisible (true);
    textEditor->setPopupMenuEnabled (true);
    textEditor->setText (String::empty);

    addAndMakeVisible (cbxLibList = new ComboBox ("new combo box"));
    cbxLibList->setEditableText (false);
    cbxLibList->setJustificationType (Justification::centredLeft);
    cbxLibList->setTextWhenNothingSelected (String::empty);
    cbxLibList->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    cbxLibList->addItem (TRANS("Instruments"), 1);
    cbxLibList->addItem (TRANS("Drums"), 2);
    cbxLibList->addItem (TRANS("Sound Effects"), 3);
    cbxLibList->addListener (this);

    addAndMakeVisible (textEditor2 = new TextEditor ("new text editor"));
    textEditor2->setMultiLine (false);
    textEditor2->setReturnKeyStartsNewLine (false);
    textEditor2->setReadOnly (false);
    textEditor2->setScrollbarsShown (true);
    textEditor2->setCaretVisible (true);
    textEditor2->setPopupMenuEnabled (true);
    textEditor2->setText (String::empty);

    addAndMakeVisible (textButton = new TextButton ("new button"));
    textButton->setButtonText (TRANS("Add to Loaded Inst Set"));
    textButton->addListener (this);

    addAndMakeVisible (label8 = new Label ("new label",
                                           TRANS("Name:")));
    label8->setFont (Font (15.00f, Font::plain));
    label8->setJustificationType (Justification::centredLeft);
    label8->setEditable (false, false, false);
    label8->setColour (TextEditor::textColourId, Colours::black);
    label8->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (txtLibItemName = new TextEditor ("new text editor"));
    txtLibItemName->setMultiLine (false);
    txtLibItemName->setReturnKeyStartsNewLine (false);
    txtLibItemName->setReadOnly (false);
    txtLibItemName->setScrollbarsShown (true);
    txtLibItemName->setCaretVisible (true);
    txtLibItemName->setPopupMenuEnabled (true);
    txtLibItemName->setText (String::empty);

    addAndMakeVisible (toggleButton = new ToggleButton ("new toggle button"));
    toggleButton->setButtonText (TRANS("Merge"));
    toggleButton->addListener (this);
    toggleButton->setToggleState (true, dontSendNotification);

    addAndMakeVisible (cbxBItems = new ComboBox ("new combo box"));
    cbxBItems->setEditableText (false);
    cbxBItems->setJustificationType (Justification::centredLeft);
    cbxBItems->setTextWhenNothingSelected (String::empty);
    cbxBItems->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    cbxBItems->addItem (TRANS("List of Instruments"), 1);
    cbxBItems->addItem (TRANS("List of Drums"), 2);
    cbxBItems->addItem (TRANS("List of SFX"), 3);
    cbxBItems->addItem (TRANS("List of PatchProps"), 4);
    cbxBItems->addItem (TRANS("List of Samples"), 5);
    cbxBItems->addItem (TRANS("List of ALADPCMBooks"), 6);
    cbxBItems->addItem (TRANS("List of ALADPCMLoops"), 7);
    cbxBItems->addItem (TRANS("Bank\'s ABIndexEntry"), 8);
    cbxBItems->addItem (TRANS("Bank\'s ABHeader"), 9);
    cbxBItems->addItem (TRANS("Bank\'s ABBank"), 10);
    cbxBItems->addItem (TRANS("Bank\'s ABDrumList"), 11);
    cbxBItems->addItem (TRANS("Bank\'s ABSFXList"), 12);
    cbxBItems->addListener (this);

    addAndMakeVisible (label9 = new Label ("new label",
                                           TRANS("Edit:")));
    label9->setFont (Font (15.00f, Font::plain));
    label9->setJustificationType (Justification::centredLeft);
    label9->setEditable (false, false, false);
    label9->setColour (TextEditor::textColourId, Colours::black);
    label9->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (lblBSize = new Label ("new label",
                                             TRANS("Size XXXX bytes")));
    lblBSize->setFont (Font (15.00f, Font::plain));
    lblBSize->setJustificationType (Justification::centredLeft);
    lblBSize->setEditable (false, false, false);
    lblBSize->setColour (TextEditor::textColourId, Colours::black);
    lblBSize->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (PH_lstBItems = new TextEditor ("new text editor"));
    PH_lstBItems->setMultiLine (false);
    PH_lstBItems->setReturnKeyStartsNewLine (false);
    PH_lstBItems->setReadOnly (false);
    PH_lstBItems->setScrollbarsShown (true);
    PH_lstBItems->setCaretVisible (true);
    PH_lstBItems->setPopupMenuEnabled (true);
    PH_lstBItems->setText (String::empty);

    addAndMakeVisible (btnBItemAdd = new TextButton ("new button"));
    btnBItemAdd->setButtonText (TRANS("Add"));
    btnBItemAdd->setConnectedEdges (Button::ConnectedOnRight);
    btnBItemAdd->addListener (this);

    addAndMakeVisible (btnBItemDel = new TextButton ("new button"));
    btnBItemDel->setButtonText (TRANS("Del"));
    btnBItemDel->setConnectedEdges (Button::ConnectedOnLeft);
    btnBItemDel->addListener (this);

    addAndMakeVisible (btnBItemUp = new TextButton ("new button"));
    btnBItemUp->setButtonText (TRANS("Up"));
    btnBItemUp->setConnectedEdges (Button::ConnectedOnRight);
    btnBItemUp->addListener (this);

    addAndMakeVisible (btnBItemDn = new TextButton ("new button"));
    btnBItemDn->setButtonText (TRANS("Dn"));
    btnBItemDn->setConnectedEdges (Button::ConnectedOnLeft);
    btnBItemDn->addListener (this);

    addAndMakeVisible (label11 = new Label ("new label",
                                            TRANS("Item Fields:")));
    label11->setFont (Font (15.00f, Font::plain));
    label11->setJustificationType (Justification::centredLeft);
    label11->setEditable (false, false, false);
    label11->setColour (TextEditor::textColourId, Colours::black);
    label11->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label12 = new Label ("new label",
                                            TRANS("Name:")));
    label12->setFont (Font (15.00f, Font::plain));
    label12->setJustificationType (Justification::centredLeft);
    label12->setEditable (false, false, false);
    label12->setColour (TextEditor::textColourId, Colours::black);
    label12->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (txtBItemName = new TextEditor ("new text editor"));
    txtBItemName->setMultiLine (false);
    txtBItemName->setReturnKeyStartsNewLine (false);
    txtBItemName->setReadOnly (false);
    txtBItemName->setScrollbarsShown (true);
    txtBItemName->setCaretVisible (true);
    txtBItemName->setPopupMenuEnabled (true);
    txtBItemName->setText (String::empty);

    addAndMakeVisible (cbxAlign = new ComboBox ("new combo box"));
    cbxAlign->setEditableText (false);
    cbxAlign->setJustificationType (Justification::centredLeft);
    cbxAlign->setTextWhenNothingSelected (String::empty);
    cbxAlign->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    cbxAlign->addItem (TRANS("4"), 1);
    cbxAlign->addItem (TRANS("8"), 2);
    cbxAlign->addItem (TRANS("16"), 3);
    cbxAlign->addListener (this);

    addAndMakeVisible (btnBMergeAll = new TextButton ("new button"));
    btnBMergeAll->setButtonText (TRANS("Merge All"));
    btnBMergeAll->addListener (this);

    addAndMakeVisible (btnBItemDupl = new TextButton ("new button"));
    btnBItemDupl->setButtonText (TRANS("Dupl"));
    btnBItemDupl->addListener (this);


    //[UserPreSize]

    lsmFields = new TextListModel();
    lsmFields->setListener(this);

    addAndMakeVisible(lstFields = new ListBox("Fields", lsmFields));
    lstFields->setMultipleSelectionEnabled(false);
    lstFields->setRowHeight(16);


    txtFieldName->addListener(this);
    txtArrayLen->addListener(this);
    txtDefaultVal->addListener(this);

    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    romDescLoaded();
    //[/Constructor]
}

AudiobankPane::~AudiobankPane()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    groupComponent2 = nullptr;
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
    textEditor = nullptr;
    cbxLibList = nullptr;
    textEditor2 = nullptr;
    textButton = nullptr;
    label8 = nullptr;
    txtLibItemName = nullptr;
    toggleButton = nullptr;
    cbxBItems = nullptr;
    label9 = nullptr;
    lblBSize = nullptr;
    PH_lstBItems = nullptr;
    btnBItemAdd = nullptr;
    btnBItemDel = nullptr;
    btnBItemUp = nullptr;
    btnBItemDn = nullptr;
    label11 = nullptr;
    label12 = nullptr;
    txtBItemName = nullptr;
    cbxAlign = nullptr;
    btnBMergeAll = nullptr;
    btnBItemDupl = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void AudiobankPane::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    g.setColour (Colours::black);
    g.fillRect (17, 240, 2, 24);

    g.setColour (Colours::black);
    g.fillRect (209, 240, 2, 44);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void AudiobankPane::resized()
{
    groupComponent2->setBounds (448, 0, 504, 344);
    groupComponent3->setBounds (0, 344, 952, 344);
    groupComponent->setBounds (0, 0, 448, 344);
    cbxEditStruct->setBounds (28, 160, 164, 24);
    label2->setBounds (200, 192, 80, 24);
    optPointer->setBounds (8, 216, 72, 24);
    cbxDataType->setBounds (280, 192, 160, 24);
    cbxPtrTo->setBounds (24, 240, 168, 24);
    label3->setBounds (8, 192, 56, 24);
    txtFieldName->setBounds (64, 192, 128, 24);
    optArray->setBounds (200, 216, 80, 24);
    optArrayFixed->setBounds (216, 240, 80, 24);
    optArrayVar->setBounds (216, 264, 80, 24);
    txtArrayLen->setBounds (296, 240, 64, 24);
    cbxArrayLenVar->setBounds (296, 264, 144, 24);
    label4->setBounds (200, 288, 80, 24);
    cbxMeaning->setBounds (200, 312, 240, 24);
    lblStructBegin->setBounds (8, 16, 432, 24);
    lblStructEnd->setBounds (8, 160, 20, 24);
    label5->setBounds (8, 288, 104, 24);
    txtDefaultVal->setBounds (32, 312, 160, 24);
    btnFieldAdd->setBounds (272, 160, 40, 24);
    btnFieldDel->setBounds (312, 160, 40, 24);
    btnFieldUp->setBounds (360, 160, 40, 24);
    btnFieldDn->setBounds (400, 160, 40, 24);
    label6->setBounds (360, 240, 48, 24);
    label7->setBounds (8, 312, 24, 24);
    lblStructSemicolon->setBounds (192, 160, 80, 24);
    label->setBounds (456, 16, 240, 24);
    textEditor->setBounds (456, 40, 240, 296);
    cbxLibList->setBounds (704, 16, 240, 24);
    textEditor2->setBounds (704, 40, 240, 248);
    textButton->setBounds (704, 312, 168, 24);
    label8->setBounds (704, 288, 56, 24);
    txtLibItemName->setBounds (760, 288, 182, 24);
    toggleButton->setBounds (880, 312, 64, 24);
    cbxBItems->setBounds (48, 384, 200, 24);
    label9->setBounds (8, 384, 40, 24);
    lblBSize->setBounds (8, 360, 128, 24);
    PH_lstBItems->setBounds (8, 408, 240, 224);
    btnBItemAdd->setBounds (8, 632, 40, 24);
    btnBItemDel->setBounds (48, 632, 40, 24);
    btnBItemUp->setBounds (168, 632, 40, 24);
    btnBItemDn->setBounds (208, 632, 40, 24);
    label11->setBounds (256, 360, 240, 24);
    label12->setBounds (8, 656, 56, 24);
    txtBItemName->setBounds (64, 656, 184, 24);
    cbxAlign->setBounds (304, 16, 56, 24);
    btnBMergeAll->setBounds (144, 360, 104, 24);
    btnBItemDupl->setBounds (104, 632, 48, 24);
    //[UserResized] Add your own custom resize handling here..
    lstFields->setBounds(8, 40, 432, 112);
    //[/UserResized]
}

void AudiobankPane::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    String text = comboBoxThatHasChanged->getText();
    bool repaintFieldEntry = false;
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == cbxEditStruct)
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
    else if (comboBoxThatHasChanged == cbxDataType)
    {
        //[UserComboBoxCode_cbxDataType] -- add your combo box handling code here..
        if(!selfield.isValid()) return;
        if(text == "") text = "uint32";
        selfield.setProperty("datatype", text, nullptr);
        repaintFieldEntry = true;
        //[/UserComboBoxCode_cbxDataType]
    }
    else if (comboBoxThatHasChanged == cbxPtrTo)
    {
        //[UserComboBoxCode_cbxPtrTo] -- add your combo box handling code here..
        if(!selfield.isValid()) return;
        if(text == "") text = "ABDrumList";
        selfield.setProperty("ptrto", text, nullptr);
        repaintFieldEntry = true;
        //[/UserComboBoxCode_cbxPtrTo]
    }
    else if (comboBoxThatHasChanged == cbxArrayLenVar)
    {
        //[UserComboBoxCode_cbxArrayLenVar] -- add your combo box handling code here..
        if(!selfield.isValid()) return;
        if(text == "") text = "NUM_INST";
        selfield.setProperty("arraylenvar", text, nullptr);
        selfield.removeProperty("arraylenfixed", nullptr);
        optArrayFixed->setToggleState(false, dontSendNotification);
        optArrayVar->setToggleState(true, dontSendNotification);
        repaintFieldEntry = true;
        //[/UserComboBoxCode_cbxArrayLenVar]
    }
    else if (comboBoxThatHasChanged == cbxMeaning)
    {
        //[UserComboBoxCode_cbxMeaning] -- add your combo box handling code here..
        if(!selfield.isValid()) return;
        if(text == "") text = "None";
        selfield.setProperty("meaning", text, nullptr);
        repaintFieldEntry = true;
        //[/UserComboBoxCode_cbxMeaning]
    }
    else if (comboBoxThatHasChanged == cbxLibList)
    {
        //[UserComboBoxCode_cbxLibList] -- add your combo box handling code here..
        //[/UserComboBoxCode_cbxLibList]
    }
    else if (comboBoxThatHasChanged == cbxBItems)
    {
        //[UserComboBoxCode_cbxBItems] -- add your combo box handling code here..
        //[/UserComboBoxCode_cbxBItems]
    }
    else if (comboBoxThatHasChanged == cbxAlign)
    {
        //[UserComboBoxCode_cbxAlign] -- add your combo box handling code here..
        abfstructsnode.setProperty("align", text, nullptr);
        //[/UserComboBoxCode_cbxAlign]
    }

    //[UsercomboBoxChanged_Post]
    if(repaintFieldEntry){
        int row = lstFields->getLastRowSelected();
        lsmFields->set(row, getFieldDesc(selfield));
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

    if (buttonThatWasClicked == optPointer)
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
    else if (buttonThatWasClicked == optArray)
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
            cbxArrayLenVar->setText("", dontSendNotification);
            txtArrayLen->setText("", false);
            optArrayFixed->setToggleState(false, dontSendNotification);
            optArrayVar->setToggleState(false, dontSendNotification);
        }
        repaintFieldEntry = true;
        //[/UserButtonCode_optArray]
    }
    else if (buttonThatWasClicked == optArrayFixed)
    {
        //[UserButtonCode_optArrayFixed] -- add your button handler code here..
        if(!selfield.isValid()) return;
        if(!(bool)selfield.getProperty("isarray", false)) return;
        selfield.setProperty("arraylenfixed", 1, nullptr);
        selfield.removeProperty("arraylenvar", nullptr);
        cbxArrayLenVar->setText("", dontSendNotification);
        txtArrayLen->setText("1", false);
        repaintFieldEntry = true;
        //[/UserButtonCode_optArrayFixed]
    }
    else if (buttonThatWasClicked == optArrayVar)
    {
        //[UserButtonCode_optArrayVar] -- add your button handler code here..
        if(!selfield.isValid()) return;
        if(!(bool)selfield.getProperty("isarray", false)) return;
        selfield.removeProperty("arraylenfixed", nullptr);
        selfield.setProperty("arraylenvar", "NUM_INST", nullptr);
        cbxArrayLenVar->setText("NUM_INST", dontSendNotification);
        txtArrayLen->setText("", false);
        repaintFieldEntry = true;
        //[/UserButtonCode_optArrayVar]
    }
    else if (buttonThatWasClicked == btnFieldAdd)
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
    else if (buttonThatWasClicked == btnFieldDel)
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
    else if (buttonThatWasClicked == btnFieldUp)
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
    else if (buttonThatWasClicked == btnFieldDn)
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
    else if (buttonThatWasClicked == textButton)
    {
        //[UserButtonCode_textButton] -- add your button handler code here..
        //[/UserButtonCode_textButton]
    }
    else if (buttonThatWasClicked == toggleButton)
    {
        //[UserButtonCode_toggleButton] -- add your button handler code here..
        //[/UserButtonCode_toggleButton]
    }
    else if (buttonThatWasClicked == btnBItemAdd)
    {
        //[UserButtonCode_btnBItemAdd] -- add your button handler code here..
        //[/UserButtonCode_btnBItemAdd]
    }
    else if (buttonThatWasClicked == btnBItemDel)
    {
        //[UserButtonCode_btnBItemDel] -- add your button handler code here..
        //[/UserButtonCode_btnBItemDel]
    }
    else if (buttonThatWasClicked == btnBItemUp)
    {
        //[UserButtonCode_btnBItemUp] -- add your button handler code here..
        //[/UserButtonCode_btnBItemUp]
    }
    else if (buttonThatWasClicked == btnBItemDn)
    {
        //[UserButtonCode_btnBItemDn] -- add your button handler code here..
        //[/UserButtonCode_btnBItemDn]
    }
    else if (buttonThatWasClicked == btnBMergeAll)
    {
        //[UserButtonCode_btnBMergeAll] -- add your button handler code here..
        //[/UserButtonCode_btnBMergeAll]
    }
    else if (buttonThatWasClicked == btnBItemDupl)
    {
        //[UserButtonCode_btnBItemDupl] -- add your button handler code here..
        //[/UserButtonCode_btnBItemDupl]
    }

    //[UserbuttonClicked_Post]
    if(repaintFieldEntry){
        int row = lstFields->getLastRowSelected();
        lsmFields->set(row, getFieldDesc(selfield));
        lstFields->repaintRow(row);
    }
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void AudiobankPane::rowSelected(TextListModel* parent, int row){
    if(parent == &*lsmFields){
        if(!selstruct.isValid()) return;
        selfield = selstruct.getChild(row);
        fillFieldParams();
    }
}

void AudiobankPane::textEditorTextChanged(TextEditor& editorThatWasChanged){
    int val;
    String text = editorThatWasChanged.getText();
    if(      /*&editorThatWasChanged == &*txtParamAdd
            || &editorThatWasChanged == &*txtCmdDataSize*/ false){
        val = text.getIntValue();
    }else{
        val = text.getHexValue32();
    }
    bool turnRed = (val <= 0);
    bool repaintFieldEntry = false;

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
    }
    if(turnRed){
        editorThatWasChanged.setColour(TextEditor::backgroundColourId, Colours::red);
    }else{
        editorThatWasChanged.setColour(TextEditor::backgroundColourId, Colours::white);
    }
    if(repaintFieldEntry){
        int row = lstFields->getLastRowSelected();
        lsmFields->set(row, getFieldDesc(selfield));
        lstFields->repaintRow(row);
    }
}











void AudiobankPane::romDescLoaded(){
    abfstructsnode = p.romdesc.getOrCreateChildWithName("abfstructs", nullptr);
    cbxAlign->setText(abfstructsnode.getProperty("align", "16"));
    selstruct = ValueTree();
    selfield = ValueTree();
}

String AudiobankPane::getFieldDesc(ValueTree field){
    if(!field.isValid()) return "Error!";
    String desc = "  ";
    String datatype = field.getProperty("datatype", "ErrorType");
    if((bool)field.getProperty("ispointer", false)){
        String ptrto = field.getProperty("ptrto", "ErrorType");
        if(datatype == "uint32" || datatype == "int32"){
            desc += ptrto + "*";
        }else{
            desc += "(" + datatype + ")(" + ptrto + "*)";
        }
    }else{
        desc += datatype;
    }
    desc += " ";
    desc += field.getProperty("name", "ErrorName").toString();
    if((bool)field.getProperty("isarray", false)){
        if(field.hasProperty("arraylenfixed")){
            desc += "[0x" + ROM::hex((uint8)(int)field.getProperty("arraylenfixed", 0)) + "]";
        }else{
            desc += "[" + field.getProperty("arraylenvar", "Error").toString() + "]";
        }
    }
    if(field.hasProperty("defaultval")){
        desc += " = 0x" + String::toHexString((int)field.getProperty("defaultval"));
    }
    desc += ";";
    String meaning = field.getProperty("meaning", "None").toString();
    if(meaning != "None"){
        desc += " //" + meaning;
    }
    return desc;
}

void AudiobankPane::fillFieldsList(){
    lsmFields->clear();
    lstFields->updateContent();
    if(!selstruct.isValid()) return;
    for(int i=0; i<selstruct.getNumChildren(); i++){
        lsmFields->add(getFieldDesc(selstruct.getChild(i)));
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
        cbxMeaning->addItem("Sample Set Index number", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("NUM_INST", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("NUM_DRUM", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("NUM_SFX", cbxMeaning->getNumItems()+1);
    }else if(editstruct == "ABHeader"){
        cbxMeaning->addItem("NUM_INST", cbxMeaning->getNumItems()+1);
    }else if(editstruct == "ABBank"){
        cbxMeaning->addItem("Ptr Drum List", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("Ptr SFX List", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("List of Ptrs to Insts", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("Ptr Ch10 Drum", cbxMeaning->getNumItems()+1);
    }else if(editstruct == "ABDrumList"){
        cbxMeaning->addItem("List of Ptrs to Drums", cbxMeaning->getNumItems()+1);
    }else if(editstruct == "ABSFXList"){
        cbxMeaning->addItem("List of Sounds", cbxMeaning->getNumItems()+1);
    }else if(editstruct == "ABInstrument"){
        cbxMeaning->addItem("Ptr Patch Props", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("List of 3 Sounds for Splits", cbxMeaning->getNumItems()+1);
    }else if(editstruct == "ABDrum"){
        cbxMeaning->addItem("Drum Sound", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("Ptr Patch Props", cbxMeaning->getNumItems()+1);
    }else if(editstruct == "ABPatchProps"){
        //none
    }else if(editstruct == "ABSound"){
        cbxMeaning->addItem("Ptr Sample", cbxMeaning->getNumItems()+1);
    }else if(editstruct == "ABSample"){
        cbxMeaning->addItem("Sample Address (+offset)", cbxMeaning->getNumItems()+1);
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



//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="AudiobankPane" componentName=""
                 parentClasses="public Component, public TextEditor::Listener, public TextListModel::Listener"
                 constructorParams="AppProps&amp; props" variableInitialisers="p(props)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff">
    <RECT pos="17 240 2 24" fill="solid: ff000000" hasStroke="0"/>
    <RECT pos="209 240 2 44" fill="solid: ff000000" hasStroke="0"/>
  </BACKGROUND>
  <GROUPCOMPONENT name="new group" id="174f2978675eba2d" memberName="groupComponent2"
                  virtualName="" explicitFocusOrder="0" pos="448 0 504 344" title="Audiobank Library"/>
  <GROUPCOMPONENT name="new group" id="7edf637b2e2b1d8d" memberName="groupComponent3"
                  virtualName="" explicitFocusOrder="0" pos="0 344 952 344" title="Loaded Bank"/>
  <GROUPCOMPONENT name="new group" id="5c7a626fd18eb8e4" memberName="groupComponent"
                  virtualName="" explicitFocusOrder="0" pos="0 0 448 344" title="Audiobank File Data Structures"/>
  <COMBOBOX name="new combo box" id="d0dc297a3163ca7c" memberName="cbxEditStruct"
            virtualName="" explicitFocusOrder="0" pos="28 160 164 24" editable="0"
            layout="33" items="ABIndexEntry&#10;ABHeader&#10;ABBank&#10;ABDrumList&#10;ABSFXList&#10;ABInstrument&#10;ABDrum&#10;ABPatchProps&#10;ABSound&#10;ABSample&#10;ALADPCMBook&#10;ALADPCMPredictor&#10;ALADPCMLoop&#10;ALADPCMTail"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="6fa88c9721ab254d" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="200 192 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Data Type:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TOGGLEBUTTON name="new toggle button" id="cd5aa0958354bf46" memberName="optPointer"
                virtualName="" explicitFocusOrder="0" pos="8 216 72 24" buttonText="Ptr To:"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <COMBOBOX name="new combo box" id="dc9c4ee50f2e6d61" memberName="cbxDataType"
            virtualName="" explicitFocusOrder="0" pos="280 192 160 24" editable="0"
            layout="33" items="uint8&#10;uint16&#10;uint32&#10;int8&#10;int16&#10;int32&#10;ABSound&#10;ALADPCMPredictor&#10;ALADPCMTail"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="13ddb6d22233c898" memberName="cbxPtrTo"
            virtualName="" explicitFocusOrder="0" pos="24 240 168 24" editable="0"
            layout="33" items="ABHeader&#10;ABDrumList&#10;ABSFXList&#10;ABInstrument&#10;ABDrum&#10;ABPatchProps&#10;ABSample&#10;ATSample&#10;ALADPCMBook&#10;ALADPCMLoop"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="e3721257fc5becec" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="8 192 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Name:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
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
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <COMBOBOX name="new combo box" id="5e05126adcbd71c6" memberName="cbxMeaning"
            virtualName="" explicitFocusOrder="0" pos="200 312 240 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="8270ae60fb0a1f08" memberName="lblStructBegin"
         virtualName="" explicitFocusOrder="0" pos="8 16 432 24" edTextCol="ff000000"
         edBkgCol="0" labelText="typedef struct {                        //Align all to:                bytes"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="339568e39a096dda" memberName="lblStructEnd"
         virtualName="" explicitFocusOrder="0" pos="8 160 20 24" edTextCol="ff000000"
         edBkgCol="0" labelText="}" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="afecf5bedea55560" memberName="label5" virtualName=""
         explicitFocusOrder="0" pos="8 288 104 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Default value:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
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
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="db442a9c0e2ef5b7" memberName="label7" virtualName=""
         explicitFocusOrder="0" pos="8 312 24 24" edTextCol="ff000000"
         edBkgCol="0" labelText="0x" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="ccce430366fad648" memberName="lblStructSemicolon"
         virtualName="" explicitFocusOrder="0" pos="192 160 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText=";   //Fields:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="bf0f024772c31c54" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="456 16 240 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Instrument sets:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="af42cc8c5364c322" memberName="textEditor"
              virtualName="" explicitFocusOrder="0" pos="456 40 240 296" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <COMBOBOX name="new combo box" id="dc4b63bcb4d73721" memberName="cbxLibList"
            virtualName="" explicitFocusOrder="0" pos="704 16 240 24" editable="0"
            layout="33" items="Instruments&#10;Drums&#10;Sound Effects" textWhenNonSelected=""
            textWhenNoItems="(no choices)"/>
  <TEXTEDITOR name="new text editor" id="1d4c699033842e31" memberName="textEditor2"
              virtualName="" explicitFocusOrder="0" pos="704 40 240 248" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTBUTTON name="new button" id="cc887378f0c65b1f" memberName="textButton"
              virtualName="" explicitFocusOrder="0" pos="704 312 168 24" buttonText="Add to Loaded Inst Set"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="new label" id="7ab82fcc4f2fe341" memberName="label8" virtualName=""
         explicitFocusOrder="0" pos="704 288 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Name:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="1107c1605bcdd6fe" memberName="txtLibItemName"
              virtualName="" explicitFocusOrder="0" pos="760 288 182 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TOGGLEBUTTON name="new toggle button" id="35162d8ea694d708" memberName="toggleButton"
                virtualName="" explicitFocusOrder="0" pos="880 312 64 24" buttonText="Merge"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="1"/>
  <COMBOBOX name="new combo box" id="fdc8bf6df2be26a5" memberName="cbxBItems"
            virtualName="" explicitFocusOrder="0" pos="48 384 200 24" editable="0"
            layout="33" items="List of Instruments&#10;List of Drums&#10;List of SFX&#10;List of PatchProps&#10;List of Samples&#10;List of ALADPCMBooks&#10;List of ALADPCMLoops&#10;Bank's ABIndexEntry&#10;Bank's ABHeader&#10;Bank's ABBank&#10;Bank's ABDrumList&#10;Bank's ABSFXList"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="fca8e093e749e72d" memberName="label9" virtualName=""
         explicitFocusOrder="0" pos="8 384 40 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Edit:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="5b9ec0c75821be89" memberName="lblBSize"
         virtualName="" explicitFocusOrder="0" pos="8 360 128 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Size XXXX bytes" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="d41cc744fa0fe0f0" memberName="PH_lstBItems"
              virtualName="" explicitFocusOrder="0" pos="8 408 240 224" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTBUTTON name="new button" id="95b805434c056546" memberName="btnBItemAdd"
              virtualName="" explicitFocusOrder="0" pos="8 632 40 24" buttonText="Add"
              connectedEdges="2" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="5437999e821d0f9" memberName="btnBItemDel"
              virtualName="" explicitFocusOrder="0" pos="48 632 40 24" buttonText="Del"
              connectedEdges="1" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="53c617d9b6236e17" memberName="btnBItemUp"
              virtualName="" explicitFocusOrder="0" pos="168 632 40 24" buttonText="Up"
              connectedEdges="2" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="7aa4ba34a22a9127" memberName="btnBItemDn"
              virtualName="" explicitFocusOrder="0" pos="208 632 40 24" buttonText="Dn"
              connectedEdges="1" needsCallback="1" radioGroupId="0"/>
  <LABEL name="new label" id="ede4922f8220d0ea" memberName="label11" virtualName=""
         explicitFocusOrder="0" pos="256 360 240 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Item Fields:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="fedcaca14cadb7e6" memberName="label12" virtualName=""
         explicitFocusOrder="0" pos="8 656 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Name:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="789b2d42c36319de" memberName="txtBItemName"
              virtualName="" explicitFocusOrder="0" pos="64 656 184 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <COMBOBOX name="new combo box" id="624a2f6acff61c45" memberName="cbxAlign"
            virtualName="" explicitFocusOrder="0" pos="304 16 56 24" editable="0"
            layout="33" items="4&#10;8&#10;16" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <TEXTBUTTON name="new button" id="b2b74c8108c51241" memberName="btnBMergeAll"
              virtualName="" explicitFocusOrder="0" pos="144 360 104 24" buttonText="Merge All"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="b4f552bc87690c64" memberName="btnBItemDupl"
              virtualName="" explicitFocusOrder="0" pos="104 632 48 24" buttonText="Dupl"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

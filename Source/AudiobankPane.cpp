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
                                                             TRANS("Loaded Instrument Set")));

    addAndMakeVisible (groupComponent = new GroupComponent ("new group",
                                                            TRANS("Audiobank File Data Structures")));

    addAndMakeVisible (cbxEditStruct = new ComboBox ("new combo box"));
    cbxEditStruct->setEditableText (false);
    cbxEditStruct->setJustificationType (Justification::centredLeft);
    cbxEditStruct->setTextWhenNothingSelected (String::empty);
    cbxEditStruct->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    cbxEditStruct->addItem (TRANS("ABI_Entry"), 1);
    cbxEditStruct->addItem (TRANS("ABF_Header"), 2);
    cbxEditStruct->addItem (TRANS("ABF_Main"), 3);
    cbxEditStruct->addItem (TRANS("ABF_DrumList"), 4);
    cbxEditStruct->addItem (TRANS("ABF_SFXList"), 5);
    cbxEditStruct->addItem (TRANS("ABF_Instrument"), 6);
    cbxEditStruct->addItem (TRANS("ABF_Drum"), 7);
    cbxEditStruct->addItem (TRANS("ABF_PatchProps"), 8);
    cbxEditStruct->addItem (TRANS("ABF_PPEntry"), 9);
    cbxEditStruct->addItem (TRANS("ABF_Sound"), 10);
    cbxEditStruct->addItem (TRANS("ABF_Sample"), 11);
    cbxEditStruct->addItem (TRANS("ABF_SampleStruct1"), 12);
    cbxEditStruct->addItem (TRANS("ABF_SS1Block"), 13);
    cbxEditStruct->addItem (TRANS("ABF_SampleStruct2"), 14);
    cbxEditStruct->addItem (TRANS("ABF_SS2Block"), 15);
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
    cbxDataType->addItem (TRANS("ABF_PPEntry"), 7);
    cbxDataType->addItem (TRANS("ABF_Sound"), 8);
    cbxDataType->addItem (TRANS("ABF_SS1Block"), 9);
    cbxDataType->addItem (TRANS("ABF_SS2Block"), 10);
    cbxDataType->addListener (this);

    addAndMakeVisible (cbxPtrTo = new ComboBox ("new combo box"));
    cbxPtrTo->setEditableText (false);
    cbxPtrTo->setJustificationType (Justification::centredLeft);
    cbxPtrTo->setTextWhenNothingSelected (String::empty);
    cbxPtrTo->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    cbxPtrTo->addItem (TRANS("ABF_DrumList"), 1);
    cbxPtrTo->addItem (TRANS("ABF_SFXList"), 2);
    cbxPtrTo->addItem (TRANS("ABF_Instrument"), 3);
    cbxPtrTo->addItem (TRANS("ABF_Drum"), 4);
    cbxPtrTo->addItem (TRANS("ABF_PatchProps"), 5);
    cbxPtrTo->addItem (TRANS("ABF_Sample"), 6);
    cbxPtrTo->addItem (TRANS("ABF_SampleStruct1"), 7);
    cbxPtrTo->addItem (TRANS("ABF_SampleStruct2"), 8);
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
    optArrayFixed->setToggleState (true, dontSendNotification);

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
    cbxArrayLenVar->addItem (TRANS("NUM_INST"), 1);
    cbxArrayLenVar->addItem (TRANS("NUM_DRUM"), 2);
    cbxArrayLenVar->addItem (TRANS("NUM_SFX"), 3);
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
                                                   TRANS("typedef struct {")));
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

    addAndMakeVisible (cbxISItems = new ComboBox ("new combo box"));
    cbxISItems->setEditableText (false);
    cbxISItems->setJustificationType (Justification::centredLeft);
    cbxISItems->setTextWhenNothingSelected (String::empty);
    cbxISItems->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    cbxISItems->addItem (TRANS("List of Instruments"), 1);
    cbxISItems->addItem (TRANS("List of Drums"), 2);
    cbxISItems->addItem (TRANS("List of SFX"), 3);
    cbxISItems->addItem (TRANS("List of PatchProps"), 4);
    cbxISItems->addItem (TRANS("List of Samples"), 5);
    cbxISItems->addItem (TRANS("List of SampleStruct1s"), 6);
    cbxISItems->addItem (TRANS("List of SampleStruct2s"), 7);
    cbxISItems->addItem (TRANS("ABI_Entry"), 8);
    cbxISItems->addItem (TRANS("ABF_Header"), 9);
    cbxISItems->addItem (TRANS("ABF_Main"), 10);
    cbxISItems->addItem (TRANS("ABF_DrumList"), 11);
    cbxISItems->addItem (TRANS("ABF_SFXList"), 12);
    cbxISItems->addListener (this);

    addAndMakeVisible (label9 = new Label ("new label",
                                           TRANS("Edit:")));
    label9->setFont (Font (15.00f, Font::plain));
    label9->setJustificationType (Justification::centredLeft);
    label9->setEditable (false, false, false);
    label9->setColour (TextEditor::textColourId, Colours::black);
    label9->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label10 = new Label ("new label",
                                            TRANS("Size XXXX bytes")));
    label10->setFont (Font (15.00f, Font::plain));
    label10->setJustificationType (Justification::centredLeft);
    label10->setEditable (false, false, false);
    label10->setColour (TextEditor::textColourId, Colours::black);
    label10->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (PH_lstISItems = new TextEditor ("new text editor"));
    PH_lstISItems->setMultiLine (false);
    PH_lstISItems->setReturnKeyStartsNewLine (false);
    PH_lstISItems->setReadOnly (false);
    PH_lstISItems->setScrollbarsShown (true);
    PH_lstISItems->setCaretVisible (true);
    PH_lstISItems->setPopupMenuEnabled (true);
    PH_lstISItems->setText (String::empty);

    addAndMakeVisible (btnISItemAdd = new TextButton ("new button"));
    btnISItemAdd->setButtonText (TRANS("Add"));
    btnISItemAdd->setConnectedEdges (Button::ConnectedOnRight | Button::ConnectedOnBottom);
    btnISItemAdd->addListener (this);

    addAndMakeVisible (btnISItemDel = new TextButton ("new button"));
    btnISItemDel->setButtonText (TRANS("Del"));
    btnISItemDel->setConnectedEdges (Button::ConnectedOnRight | Button::ConnectedOnTop);
    btnISItemDel->addListener (this);

    addAndMakeVisible (btnISItemUp = new TextButton ("new button"));
    btnISItemUp->setButtonText (TRANS("Up"));
    btnISItemUp->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnBottom);
    btnISItemUp->addListener (this);

    addAndMakeVisible (btnISItemDn = new TextButton ("new button"));
    btnISItemDn->setButtonText (TRANS("Dn"));
    btnISItemDn->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnTop);
    btnISItemDn->addListener (this);

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

    addAndMakeVisible (txtISItemName = new TextEditor ("new text editor"));
    txtISItemName->setMultiLine (false);
    txtISItemName->setReturnKeyStartsNewLine (false);
    txtISItemName->setReadOnly (false);
    txtISItemName->setScrollbarsShown (true);
    txtISItemName->setCaretVisible (true);
    txtISItemName->setPopupMenuEnabled (true);
    txtISItemName->setText (String::empty);

    addAndMakeVisible (label13 = new Label ("new label",
                                            TRANS("This tab is under development")));
    label13->setFont (Font (24.20f, Font::plain));
    label13->setJustificationType (Justification::centredLeft);
    label13->setEditable (false, false, false);
    label13->setColour (Label::textColourId, Colours::red);
    label13->setColour (TextEditor::textColourId, Colours::black);
    label13->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


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
    cbxISItems = nullptr;
    label9 = nullptr;
    label10 = nullptr;
    PH_lstISItems = nullptr;
    btnISItemAdd = nullptr;
    btnISItemDel = nullptr;
    btnISItemUp = nullptr;
    btnISItemDn = nullptr;
    label11 = nullptr;
    label12 = nullptr;
    txtISItemName = nullptr;
    label13 = nullptr;


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
    lblStructBegin->setBounds (8, 16, 424, 24);
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
    cbxISItems->setBounds (48, 384, 200, 24);
    label9->setBounds (8, 384, 40, 24);
    label10->setBounds (8, 360, 240, 24);
    PH_lstISItems->setBounds (8, 408, 240, 224);
    btnISItemAdd->setBounds (168, 632, 40, 24);
    btnISItemDel->setBounds (168, 656, 40, 24);
    btnISItemUp->setBounds (208, 632, 40, 24);
    btnISItemDn->setBounds (208, 656, 40, 24);
    label11->setBounds (256, 360, 240, 24);
    label12->setBounds (8, 632, 64, 24);
    txtISItemName->setBounds (16, 656, 144, 24);
    label13->setBounds (416, 448, 240, 24);
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
        if(text == "") text = "ABF_DrumList";
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
    else if (comboBoxThatHasChanged == cbxISItems)
    {
        //[UserComboBoxCode_cbxISItems] -- add your combo box handling code here..
        //[/UserComboBoxCode_cbxISItems]
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
                selfield.setProperty("ptrto", "ABF_DrumList", nullptr);
            }
            cbxPtrTo->setText(selfield.getProperty("ptrto", "ABF_DrumList").toString());
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
    else if (buttonThatWasClicked == btnISItemAdd)
    {
        //[UserButtonCode_btnISItemAdd] -- add your button handler code here..
        //[/UserButtonCode_btnISItemAdd]
    }
    else if (buttonThatWasClicked == btnISItemDel)
    {
        //[UserButtonCode_btnISItemDel] -- add your button handler code here..
        //[/UserButtonCode_btnISItemDel]
    }
    else if (buttonThatWasClicked == btnISItemUp)
    {
        //[UserButtonCode_btnISItemUp] -- add your button handler code here..
        //[/UserButtonCode_btnISItemUp]
    }
    else if (buttonThatWasClicked == btnISItemDn)
    {
        //[UserButtonCode_btnISItemDn] -- add your button handler code here..
        //[/UserButtonCode_btnISItemDn]
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
        if(selfield.hasProperty("arraylenfixed")){
            optArrayFixed->setToggleState(true, dontSendNotification);
            optArrayVar->setToggleState(false, dontSendNotification);
            txtArrayLen->setText(ROM::hex((uint8)(int)selfield.getProperty("arraylenfixed", 0)));
            cbxArrayLenVar->setText("");
        }else{
            optArrayFixed->setToggleState(false, dontSendNotification);
            optArrayVar->setToggleState(true, dontSendNotification);
            txtArrayLen->setText("");
            cbxArrayLenVar->setText(selfield.getProperty("arraylenvar", "NUM_INST").toString());
        }
    }else{
        optArrayFixed->setToggleState(false, dontSendNotification);
        optArrayVar->setToggleState(false, dontSendNotification);
        txtArrayLen->setText("");
        cbxArrayLenVar->setText("");
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
    if(editstruct == "ABI_Entry"){
        cbxMeaning->addItem("Ptr Inst Set (in Audiobank)", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("Instrument Set Length", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("Sample Set Index number", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("NUM_INST", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("NUM_DRUM", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("NUM_SFX", cbxMeaning->getNumItems()+1);
    }else if(editstruct == "ABF_Header"){
        cbxMeaning->addItem("NUM_INST", cbxMeaning->getNumItems()+1);
    }else if(editstruct == "ABF_Main"){
        cbxMeaning->addItem("Ptr Drum List", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("Ptr SFX List", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("List of Ptrs to Insts", cbxMeaning->getNumItems()+1);
    }else if(editstruct == "ABF_DrumList"){
        cbxMeaning->addItem("List of Ptrs to Drums", cbxMeaning->getNumItems()+1);
    }else if(editstruct == "ABF_SFXList"){
        cbxMeaning->addItem("List of Sounds", cbxMeaning->getNumItems()+1);
    }else if(editstruct == "ABF_Instrument"){
        cbxMeaning->addItem("Ptr Patch Props", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("List of 3 Sounds for Splits", cbxMeaning->getNumItems()+1);
    }else if(editstruct == "ABF_Drum"){
        cbxMeaning->addItem("Drum Sound", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("Ptr Patch Props", cbxMeaning->getNumItems()+1);
    }else if(editstruct == "ABF_PatchProps"){
        cbxMeaning->addItem("List of 4 PPEntries", cbxMeaning->getNumItems()+1);
    }else if(editstruct == "ABF_PPEntry"){

    }else if(editstruct == "ABF_Sound"){
        cbxMeaning->addItem("Ptr Sample", cbxMeaning->getNumItems()+1);
    }else if(editstruct == "ABF_Sample"){
        cbxMeaning->addItem("Sample Address (+offset)", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("Ptr SampleStruct2", cbxMeaning->getNumItems()+1);
        cbxMeaning->addItem("Ptr SampleStruct1", cbxMeaning->getNumItems()+1);
    }else if(editstruct == "ABF_SampleStruct1"){

    }else if(editstruct == "ABF_SS1Block"){

    }else if(editstruct == "ABF_SampleStruct2"){

    }else if(editstruct == "ABF_SS2Block"){

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
                  virtualName="" explicitFocusOrder="0" pos="0 344 952 344" title="Loaded Instrument Set"/>
  <GROUPCOMPONENT name="new group" id="5c7a626fd18eb8e4" memberName="groupComponent"
                  virtualName="" explicitFocusOrder="0" pos="0 0 448 344" title="Audiobank File Data Structures"/>
  <COMBOBOX name="new combo box" id="d0dc297a3163ca7c" memberName="cbxEditStruct"
            virtualName="" explicitFocusOrder="0" pos="28 160 164 24" editable="0"
            layout="33" items="ABI_Entry&#10;ABF_Header&#10;ABF_Main&#10;ABF_DrumList&#10;ABF_SFXList&#10;ABF_Instrument&#10;ABF_Drum&#10;ABF_PatchProps&#10;ABF_PPEntry&#10;ABF_Sound&#10;ABF_Sample&#10;ABF_SampleStruct1&#10;ABF_SS1Block&#10;ABF_SampleStruct2&#10;ABF_SS2Block"
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
            layout="33" items="uint8&#10;uint16&#10;uint32&#10;int8&#10;int16&#10;int32&#10;ABF_PPEntry&#10;ABF_Sound&#10;ABF_SS1Block&#10;ABF_SS2Block"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="13ddb6d22233c898" memberName="cbxPtrTo"
            virtualName="" explicitFocusOrder="0" pos="24 240 168 24" editable="0"
            layout="33" items="ABF_DrumList&#10;ABF_SFXList&#10;ABF_Instrument&#10;ABF_Drum&#10;ABF_PatchProps&#10;ABF_Sample&#10;ABF_SampleStruct1&#10;ABF_SampleStruct2"
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
                connectedEdges="0" needsCallback="1" radioGroupId="1" state="1"/>
  <TOGGLEBUTTON name="new toggle button" id="82bd043ef914492b" memberName="optArrayVar"
                virtualName="" explicitFocusOrder="0" pos="216 264 80 24" buttonText="Variable:"
                connectedEdges="0" needsCallback="1" radioGroupId="1" state="0"/>
  <TEXTEDITOR name="new text editor" id="4584422efabec1d6" memberName="txtArrayLen"
              virtualName="" explicitFocusOrder="0" pos="296 240 64 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <COMBOBOX name="new combo box" id="2d1b4dd0ebb4dfc9" memberName="cbxArrayLenVar"
            virtualName="" explicitFocusOrder="0" pos="296 264 144 24" editable="0"
            layout="33" items="NUM_INST&#10;NUM_DRUM&#10;NUM_SFX" textWhenNonSelected=""
            textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="8da47d91aaa2bce" memberName="label4" virtualName=""
         explicitFocusOrder="0" pos="200 288 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Meaning:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <COMBOBOX name="new combo box" id="5e05126adcbd71c6" memberName="cbxMeaning"
            virtualName="" explicitFocusOrder="0" pos="200 312 240 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="8270ae60fb0a1f08" memberName="lblStructBegin"
         virtualName="" explicitFocusOrder="0" pos="8 16 424 24" edTextCol="ff000000"
         edBkgCol="0" labelText="typedef struct {" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
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
  <COMBOBOX name="new combo box" id="fdc8bf6df2be26a5" memberName="cbxISItems"
            virtualName="" explicitFocusOrder="0" pos="48 384 200 24" editable="0"
            layout="33" items="List of Instruments&#10;List of Drums&#10;List of SFX&#10;List of PatchProps&#10;List of Samples&#10;List of SampleStruct1s&#10;List of SampleStruct2s&#10;ABI_Entry&#10;ABF_Header&#10;ABF_Main&#10;ABF_DrumList&#10;ABF_SFXList"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="fca8e093e749e72d" memberName="label9" virtualName=""
         explicitFocusOrder="0" pos="8 384 40 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Edit:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="5b9ec0c75821be89" memberName="label10" virtualName=""
         explicitFocusOrder="0" pos="8 360 240 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Size XXXX bytes" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="d41cc744fa0fe0f0" memberName="PH_lstISItems"
              virtualName="" explicitFocusOrder="0" pos="8 408 240 224" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTBUTTON name="new button" id="95b805434c056546" memberName="btnISItemAdd"
              virtualName="" explicitFocusOrder="0" pos="168 632 40 24" buttonText="Add"
              connectedEdges="10" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="5437999e821d0f9" memberName="btnISItemDel"
              virtualName="" explicitFocusOrder="0" pos="168 656 40 24" buttonText="Del"
              connectedEdges="6" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="53c617d9b6236e17" memberName="btnISItemUp"
              virtualName="" explicitFocusOrder="0" pos="208 632 40 24" buttonText="Up"
              connectedEdges="9" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="7aa4ba34a22a9127" memberName="btnISItemDn"
              virtualName="" explicitFocusOrder="0" pos="208 656 40 24" buttonText="Dn"
              connectedEdges="5" needsCallback="1" radioGroupId="0"/>
  <LABEL name="new label" id="ede4922f8220d0ea" memberName="label11" virtualName=""
         explicitFocusOrder="0" pos="256 360 240 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Item Fields:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="fedcaca14cadb7e6" memberName="label12" virtualName=""
         explicitFocusOrder="0" pos="8 632 64 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Name:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="789b2d42c36319de" memberName="txtISItemName"
              virtualName="" explicitFocusOrder="0" pos="16 656 144 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="c62c5e2e3b6fc24c" memberName="label13" virtualName=""
         explicitFocusOrder="0" pos="416 448 240 24" textCol="ffff0000"
         edTextCol="ff000000" edBkgCol="0" labelText="This tab is under development"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="24.199999999999999289" bold="0"
         italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

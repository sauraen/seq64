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
#include "n64checksum.h"
#include "AppProps.h"
//[/Headers]

#include "CICSetter.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
CICSetter::CICSetter (AppProps& props)
    : p(props)
{
    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("Choose the CIC chip ID:")));
    label->setFont (Font (15.00f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (cbxCIC = new ComboBox ("new combo box"));
    cbxCIC->setEditableText (false);
    cbxCIC->setJustificationType (Justification::centredLeft);
    cbxCIC->setTextWhenNothingSelected (String::empty);
    cbxCIC->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    cbxCIC->addListener (this);

    addAndMakeVisible (btnOK = new TextButton ("new button"));
    btnOK->setButtonText (TRANS("OK"));
    btnOK->addListener (this);

    addAndMakeVisible (btnCancel = new TextButton ("new button"));
    btnCancel->setButtonText (TRANS("Cancel"));
    btnCancel->addListener (this);


    //[UserPreSize]
    cbxCIC->addItem("None", 1);
    for(int i=0; i<getNumCICs(); i++){
        cbxCIC->addItem(String(getCICName(i)), i+2);
    }
    cbxCIC->setSelectedItemIndex(0, dontSendNotification);

    //[/UserPreSize]

    setSize (176, 88);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

CICSetter::~CICSetter()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    label = nullptr;
    cbxCIC = nullptr;
    btnOK = nullptr;
    btnCancel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CICSetter::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void CICSetter::resized()
{
    label->setBounds (0, 0, 176, 24);
    cbxCIC->setBounds (8, 24, 160, 24);
    btnOK->setBounds (8, 56, 72, 24);
    btnCancel->setBounds (96, 56, 72, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void CICSetter::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == cbxCIC)
    {
        //[UserComboBoxCode_cbxCIC] -- add your combo box handling code here..
        //[/UserComboBoxCode_cbxCIC]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void CICSetter::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == btnOK)
    {
        //[UserButtonCode_btnOK] -- add your button handler code here..
        int idx = cbxCIC->getSelectedItemIndex()-1;
        DBG("Setting CIC index to " + String(idx));
        p.rom.cic_index = idx;
        //[/UserButtonCode_btnOK]
    }
    else if (buttonThatWasClicked == btnCancel)
    {
        //[UserButtonCode_btnCancel] -- add your button handler code here..

        //[/UserButtonCode_btnCancel]
    }

    //[UserbuttonClicked_Post]
    DialogWindow* dw = findParentComponentOfClass<DialogWindow>();
    if (dw != nullptr)
        dw->exitModalState (0);
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="CICSetter" componentName=""
                 parentClasses="public Component" constructorParams="AppProps&amp; props"
                 variableInitialisers="p(props)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="176"
                 initialHeight="88">
  <BACKGROUND backgroundColour="ffffffff"/>
  <LABEL name="new label" id="31e441cb1f090d89" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="0 0 176 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Choose the CIC chip ID:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="new combo box" id="483e4438e06ce31c" memberName="cbxCIC"
            virtualName="" explicitFocusOrder="0" pos="8 24 160 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <TEXTBUTTON name="new button" id="225a83dacfbbfc7d" memberName="btnOK" virtualName=""
              explicitFocusOrder="0" pos="8 56 72 24" buttonText="OK" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="27e295161967d54c" memberName="btnCancel"
              virtualName="" explicitFocusOrder="0" pos="96 56 72 24" buttonText="Cancel"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

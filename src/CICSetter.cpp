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
 * CICSetter.cpp
 * Small component to get a CIC value from the user
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

#include "n64checksum.h"
//[/Headers]

#include "CICSetter.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
CICSetter::CICSetter (SEQ64& seq64_)
    : seq64(seq64_)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    label.reset (new Label ("new label",
                            TRANS("Choose the CIC chip ID:")));
    addAndMakeVisible (label.get());
    label->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label->setBounds (0, 0, 176, 24);

    cbxCIC.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (cbxCIC.get());
    cbxCIC->setEditableText (false);
    cbxCIC->setJustificationType (Justification::centredLeft);
    cbxCIC->setTextWhenNothingSelected (String());
    cbxCIC->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    cbxCIC->addListener (this);

    cbxCIC->setBounds (8, 24, 160, 24);

    btnOK.reset (new TextButton ("new button"));
    addAndMakeVisible (btnOK.get());
    btnOK->setButtonText (TRANS("OK"));
    btnOK->addListener (this);

    btnOK->setBounds (8, 56, 72, 24);

    btnCancel.reset (new TextButton ("new button"));
    addAndMakeVisible (btnCancel.get());
    btnCancel->setButtonText (TRANS("Cancel"));
    btnCancel->addListener (this);

    btnCancel->setBounds (96, 56, 72, 24);


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

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void CICSetter::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void CICSetter::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == cbxCIC.get())
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

    if (buttonThatWasClicked == btnOK.get())
    {
        //[UserButtonCode_btnOK] -- add your button handler code here..
        int idx = cbxCIC->getSelectedItemIndex()-1;
        SEQ64::say("Setting CIC index to " + String(idx));
        seq64.rom.cic_index = idx;
        //[/UserButtonCode_btnOK]
    }
    else if (buttonThatWasClicked == btnCancel.get())
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
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="CICSetter" componentName=""
                 parentClasses="public Component" constructorParams="SEQ64&amp; seq64_"
                 variableInitialisers="seq64(seq64_)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="176"
                 initialHeight="88">
  <BACKGROUND backgroundColour="ff323e44"/>
  <LABEL name="new label" id="31e441cb1f090d89" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="0 0 176 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Choose the CIC chip ID:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
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


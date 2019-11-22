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
 * IEEditor.cpp
 * Small component to edit the metadata in index entries
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
//[/Headers]

#include "IEEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
IEEditor::IEEditor (IndexedFile& ifile_, FilesPane& fp_, int entry_)
    : ifile(ifile_), fp(fp_), entry(entry_)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    btnOverride.reset (new TextButton ("new button"));
    addAndMakeVisible (btnOverride.get());
    btnOverride->setButtonText (TRANS("Override"));
    btnOverride->addListener (this);
    btnOverride->setColour (TextButton::buttonColourId, Colour (0xffff9797));
    btnOverride->setColour (TextButton::buttonOnColourId, Colour (0xfff52307));
    btnOverride->setColour (TextButton::textColourOffId, Colours::black);
    btnOverride->setColour (TextButton::textColourOnId, Colours::black);

    btnOverride->setBounds (8, 144, 152, 24);

    lblAddress.reset (new Label ("new label",
                                 TRANS("Address:")));
    addAndMakeVisible (lblAddress.get());
    lblAddress->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblAddress->setJustificationType (Justification::centredRight);
    lblAddress->setEditable (false, false, false);
    lblAddress->setColour (TextEditor::textColourId, Colours::black);
    lblAddress->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblAddress->setBounds (8, 8, 80, 24);

    txtAddress.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (txtAddress.get());
    txtAddress->setMultiLine (false);
    txtAddress->setReturnKeyStartsNewLine (false);
    txtAddress->setReadOnly (false);
    txtAddress->setScrollbarsShown (true);
    txtAddress->setCaretVisible (true);
    txtAddress->setPopupMenuEnabled (true);
    txtAddress->setText (String());

    txtAddress->setBounds (88, 8, 72, 24);

    lblAddress2.reset (new Label ("new label",
                                  TRANS("Length:")));
    addAndMakeVisible (lblAddress2.get());
    lblAddress2->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblAddress2->setJustificationType (Justification::centredRight);
    lblAddress2->setEditable (false, false, false);
    lblAddress2->setColour (TextEditor::textColourId, Colours::black);
    lblAddress2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lblAddress2->setBounds (8, 32, 80, 24);

    txtLength.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (txtLength.get());
    txtLength->setMultiLine (false);
    txtLength->setReturnKeyStartsNewLine (false);
    txtLength->setReadOnly (false);
    txtLength->setScrollbarsShown (true);
    txtLength->setCaretVisible (true);
    txtLength->setPopupMenuEnabled (true);
    txtLength->setText (String());

    txtLength->setBounds (88, 32, 72, 24);

    label.reset (new Label ("new label",
                            TRANS("Fields:")));
    addAndMakeVisible (label.get());
    label->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label->setJustificationType (Justification::centred);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label->setBounds (8, 56, 152, 24);

    txtF1.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (txtF1.get());
    txtF1->setMultiLine (false);
    txtF1->setReturnKeyStartsNewLine (false);
    txtF1->setReadOnly (false);
    txtF1->setScrollbarsShown (true);
    txtF1->setCaretVisible (true);
    txtF1->setPopupMenuEnabled (true);
    txtF1->setText (String());

    txtF1->setBounds (8, 80, 31, 24);

    txtF2.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (txtF2.get());
    txtF2->setMultiLine (false);
    txtF2->setReturnKeyStartsNewLine (false);
    txtF2->setReadOnly (false);
    txtF2->setScrollbarsShown (true);
    txtF2->setCaretVisible (true);
    txtF2->setPopupMenuEnabled (true);
    txtF2->setText (String());

    txtF2->setBounds (48, 80, 31, 24);

    txtF3.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (txtF3.get());
    txtF3->setMultiLine (false);
    txtF3->setReturnKeyStartsNewLine (false);
    txtF3->setReadOnly (false);
    txtF3->setScrollbarsShown (true);
    txtF3->setCaretVisible (true);
    txtF3->setPopupMenuEnabled (true);
    txtF3->setText (String());

    txtF3->setBounds (88, 80, 31, 24);

    txtF4.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (txtF4.get());
    txtF4->setMultiLine (false);
    txtF4->setReturnKeyStartsNewLine (false);
    txtF4->setReadOnly (false);
    txtF4->setScrollbarsShown (true);
    txtF4->setCaretVisible (true);
    txtF4->setPopupMenuEnabled (true);
    txtF4->setText (String());

    txtF4->setBounds (128, 80, 31, 24);

    txtF5.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (txtF5.get());
    txtF5->setMultiLine (false);
    txtF5->setReturnKeyStartsNewLine (false);
    txtF5->setReadOnly (false);
    txtF5->setScrollbarsShown (true);
    txtF5->setCaretVisible (true);
    txtF5->setPopupMenuEnabled (true);
    txtF5->setText (String());

    txtF5->setBounds (8, 112, 31, 24);

    txtF6.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (txtF6.get());
    txtF6->setMultiLine (false);
    txtF6->setReturnKeyStartsNewLine (false);
    txtF6->setReadOnly (false);
    txtF6->setScrollbarsShown (true);
    txtF6->setCaretVisible (true);
    txtF6->setPopupMenuEnabled (true);
    txtF6->setText (String());

    txtF6->setBounds (48, 112, 31, 24);

    txtF7.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (txtF7.get());
    txtF7->setMultiLine (false);
    txtF7->setReturnKeyStartsNewLine (false);
    txtF7->setReadOnly (false);
    txtF7->setScrollbarsShown (true);
    txtF7->setCaretVisible (true);
    txtF7->setPopupMenuEnabled (true);
    txtF7->setText (String());

    txtF7->setBounds (88, 112, 31, 24);

    txtF8.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (txtF8.get());
    txtF8->setMultiLine (false);
    txtF8->setReturnKeyStartsNewLine (false);
    txtF8->setReadOnly (false);
    txtF8->setScrollbarsShown (true);
    txtF8->setCaretVisible (true);
    txtF8->setPopupMenuEnabled (true);
    txtF8->setText (String());

    txtF8->setBounds (128, 112, 31, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (168, 176);


    //[Constructor] You can add your own custom stuff here..
    uint32 addr, len;
    ifile.getObjectAddrLen(entry, addr, len);
    txtAddress->setText(ROM::hex(addr));
    txtLength->setText(ROM::hex(len));
    if(ifile.hasMetadata()){
        uint32 md1, md2;
        ifile.getObjectMetadata(entry, md1, md2);
        txtF1->setText(ROM::hex((uint8)((md1 >> 24) & 0xFF)));
        txtF2->setText(ROM::hex((uint8)((md1 >> 16) & 0xFF)));
        txtF3->setText(ROM::hex((uint8)((md1 >>  8) & 0xFF)));
        txtF4->setText(ROM::hex((uint8)((md1      ) & 0xFF)));
        txtF5->setText(ROM::hex((uint8)((md2 >> 24) & 0xFF)));
        txtF6->setText(ROM::hex((uint8)((md2 >> 16) & 0xFF)));
        txtF7->setText(ROM::hex((uint8)((md2 >>  8) & 0xFF)));
        txtF8->setText(ROM::hex((uint8)((md2      ) & 0xFF)));
    }else{
        txtF1->setEnabled(false);
        txtF2->setEnabled(false);
        txtF3->setEnabled(false);
        txtF4->setEnabled(false);
        txtF5->setEnabled(false);
        txtF6->setEnabled(false);
        txtF7->setEnabled(false);
        txtF8->setEnabled(false);
    }
    //[/Constructor]
}

IEEditor::~IEEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    btnOverride = nullptr;
    lblAddress = nullptr;
    txtAddress = nullptr;
    lblAddress2 = nullptr;
    txtLength = nullptr;
    label = nullptr;
    txtF1 = nullptr;
    txtF2 = nullptr;
    txtF3 = nullptr;
    txtF4 = nullptr;
    txtF5 = nullptr;
    txtF6 = nullptr;
    txtF7 = nullptr;
    txtF8 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void IEEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void IEEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void IEEditor::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == btnOverride.get())
    {
        //[UserButtonCode_btnOverride] -- add your button handler code here..
        ifile.setObjectAddr(entry, txtAddress->getText().getHexValue32());
        ifile.setObjectLen(entry, txtLength->getText().getHexValue32());
        if(ifile.hasMetadata()){
            uint32 md1, md2;
            md1 = 0;
            md1 |= (uint8)txtF1->getText().getHexValue32();
            md1 <<= 8;
            md1 |= (uint8)txtF2->getText().getHexValue32();
            md1 <<= 8;
            md1 |= (uint8)txtF3->getText().getHexValue32();
            md1 <<= 8;
            md1 |= (uint8)txtF4->getText().getHexValue32();
            md2 = 0;
            md2 |= (uint8)txtF5->getText().getHexValue32();
            md2 <<= 8;
            md2 |= (uint8)txtF6->getText().getHexValue32();
            md2 <<= 8;
            md2 |= (uint8)txtF7->getText().getHexValue32();
            md2 <<= 8;
            md2 |= (uint8)txtF8->getText().getHexValue32();
            ifile.setObjectMetadata(entry, md1, md2);
        }
        fp.fillIEntryParams();
        //[/UserButtonCode_btnOverride]
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

<JUCER_COMPONENT documentType="Component" className="IEEditor" componentName=""
                 parentClasses="public Component" constructorParams="IndexedFile&amp; ifile_, FilesPane&amp; fp_, int entry_"
                 variableInitialisers="ifile(ifile_), fp(fp_), entry(entry_)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="168" initialHeight="176">
  <BACKGROUND backgroundColour="ff323e44"/>
  <TEXTBUTTON name="new button" id="f9678002aca585d6" memberName="btnOverride"
              virtualName="" explicitFocusOrder="0" pos="8 144 152 24" bgColOff="ffff9797"
              bgColOn="fff52307" textCol="ff000000" textColOn="ff000000" buttonText="Override"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="new label" id="815b4f636ecb5265" memberName="lblAddress"
         virtualName="" explicitFocusOrder="0" pos="8 8 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Address:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="34"/>
  <TEXTEDITOR name="new text editor" id="301b2658b376f44c" memberName="txtAddress"
              virtualName="" explicitFocusOrder="0" pos="88 8 72 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="961cca68d4f60e6a" memberName="lblAddress2"
         virtualName="" explicitFocusOrder="0" pos="8 32 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Length:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="34"/>
  <TEXTEDITOR name="new text editor" id="a5a470e76ba5609b" memberName="txtLength"
              virtualName="" explicitFocusOrder="0" pos="88 32 72 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="7d4ba418b8fda751" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="8 56 152 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Fields:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="36"/>
  <TEXTEDITOR name="new text editor" id="e339b8d2400b663d" memberName="txtF1"
              virtualName="" explicitFocusOrder="0" pos="8 80 31 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="new text editor" id="bd47cd5a7c823d8e" memberName="txtF2"
              virtualName="" explicitFocusOrder="0" pos="48 80 31 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="new text editor" id="e3d9ae95cf9ea130" memberName="txtF3"
              virtualName="" explicitFocusOrder="0" pos="88 80 31 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="new text editor" id="40d20325de5325d4" memberName="txtF4"
              virtualName="" explicitFocusOrder="0" pos="128 80 31 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="new text editor" id="9b24e5efd2a4c099" memberName="txtF5"
              virtualName="" explicitFocusOrder="0" pos="8 112 31 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="new text editor" id="a9b7880f5fb69938" memberName="txtF6"
              virtualName="" explicitFocusOrder="0" pos="48 112 31 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="new text editor" id="52c2b5fb378b1255" memberName="txtF7"
              virtualName="" explicitFocusOrder="0" pos="88 112 31 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="new text editor" id="ef60ae9f95c8318" memberName="txtF8"
              virtualName="" explicitFocusOrder="0" pos="128 112 31 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]


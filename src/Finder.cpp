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
 * AudiobankPane.h
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

#include "IndexedFile.h"
//[/Headers]

#include "Finder.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
Finder::Finder (SEQ64& seq64_)
    : seq64(seq64_)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    grpOptions.reset (new GroupComponent ("new group",
                                          TRANS("Options:")));
    addAndMakeVisible (grpOptions.get());

    grpOptions->setBounds (144, 0, 296, 96);

    grpTarget.reset (new GroupComponent ("new group",
                                         TRANS("Find:")));
    addAndMakeVisible (grpTarget.get());

    grpTarget->setBounds (0, 0, 144, 120);

    optTargetIndex.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (optTargetIndex.get());
    optTargetIndex->setButtonText (TRANS("Indexes"));
    optTargetIndex->setRadioGroupId (1);
    optTargetIndex->addListener (this);
    optTargetIndex->setToggleState (true, dontSendNotification);

    optTargetIndex->setBounds (8, 16, 72, 24);

    optTargetAudiobank.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (optTargetAudiobank.get());
    optTargetAudiobank->setButtonText (TRANS("Audiobank Data"));
    optTargetAudiobank->setRadioGroupId (1);
    optTargetAudiobank->addListener (this);

    optTargetAudiobank->setBounds (8, 40, 128, 24);

    optTargetAudioseq.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (optTargetAudioseq.get());
    optTargetAudioseq->setButtonText (TRANS("Audioseq Data"));
    optTargetAudioseq->setRadioGroupId (1);
    optTargetAudioseq->addListener (this);

    optTargetAudioseq->setBounds (8, 64, 120, 24);

    optTargetAudiotable.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (optTargetAudiotable.get());
    optTargetAudiotable->setButtonText (TRANS("Audiotable Data"));
    optTargetAudiotable->setRadioGroupId (1);
    optTargetAudiotable->addListener (this);

    optTargetAudiotable->setBounds (8, 88, 128, 24);

    chkIndexUnmodded.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (chkIndexUnmodded.get());
    chkIndexUnmodded->setButtonText (TRANS("Assume index in order (unmodded ROM)"));
    chkIndexUnmodded->addListener (this);
    chkIndexUnmodded->setToggleState (true, dontSendNotification);

    chkIndexUnmodded->setBounds (152, 16, 280, 24);

    label.reset (new Label ("new label",
                            TRANS("Min seq len w/o errors:")));
    addAndMakeVisible (label.get());
    label->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label->setBounds (152, 64, 160, 24);

    txtAudioseqMinLen.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (txtAudioseqMinLen.get());
    txtAudioseqMinLen->setMultiLine (false);
    txtAudioseqMinLen->setReturnKeyStartsNewLine (false);
    txtAudioseqMinLen->setReadOnly (false);
    txtAudioseqMinLen->setScrollbarsShown (true);
    txtAudioseqMinLen->setCaretVisible (true);
    txtAudioseqMinLen->setPopupMenuEnabled (true);
    txtAudioseqMinLen->setText (TRANS("16"));

    txtAudioseqMinLen->setBounds (312, 64, 32, 24);

    label2.reset (new Label ("new label",
                             TRANS("Object align:")));
    addAndMakeVisible (label2.get());
    label2->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label2->setBounds (152, 40, 88, 24);

    optAlign4.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (optAlign4.get());
    optAlign4->setButtonText (TRANS("4"));
    optAlign4->setRadioGroupId (2);
    optAlign4->addListener (this);

    optAlign4->setBounds (240, 40, 40, 24);

    optAlign8.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (optAlign8.get());
    optAlign8->setButtonText (TRANS("8"));
    optAlign8->setRadioGroupId (2);
    optAlign8->addListener (this);

    optAlign8->setBounds (288, 40, 40, 24);

    optAlign16.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (optAlign16.get());
    optAlign16->setButtonText (TRANS("16"));
    optAlign16->setRadioGroupId (2);
    optAlign16->addListener (this);
    optAlign16->setToggleState (true, dontSendNotification);

    optAlign16->setBounds (336, 40, 40, 24);

    label3.reset (new Label ("new label",
                             TRANS("Results:")));
    addAndMakeVisible (label3.get());
    label3->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label3->setJustificationType (Justification::centredLeft);
    label3->setEditable (false, false, false);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label3->setBounds (0, 152, 440, 24);

    btnGo.reset (new TextButton ("new button"));
    addAndMakeVisible (btnGo.get());
    btnGo->setButtonText (TRANS("Go"));
    btnGo->addListener (this);

    btnGo->setBounds (8, 128, 424, 24);

    txtHex.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (txtHex.get());
    txtHex->setMultiLine (true);
    txtHex->setReturnKeyStartsNewLine (true);
    txtHex->setReadOnly (true);
    txtHex->setScrollbarsShown (false);
    txtHex->setCaretVisible (false);
    txtHex->setPopupMenuEnabled (false);
    txtHex->setText (String());

    txtHex->setBounds (448, 32, 576, 424);

    label4.reset (new Label ("new label",
                             TRANS("Hex view:")));
    addAndMakeVisible (label4.get());
    label4->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label4->setJustificationType (Justification::centredLeft);
    label4->setEditable (false, false, false);
    label4->setColour (TextEditor::textColourId, Colours::black);
    label4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label4->setBounds (448, 8, 72, 24);

    txtHexAddr.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (txtHexAddr.get());
    txtHexAddr->setMultiLine (false);
    txtHexAddr->setReturnKeyStartsNewLine (false);
    txtHexAddr->setReadOnly (false);
    txtHexAddr->setScrollbarsShown (true);
    txtHexAddr->setCaretVisible (true);
    txtHexAddr->setPopupMenuEnabled (true);
    txtHexAddr->setText (TRANS("00000000"));

    txtHexAddr->setBounds (520, 8, 72, 24);

    btnUp10.reset (new TextButton ("new button"));
    addAndMakeVisible (btnUp10.get());
    btnUp10->setButtonText (TRANS("^"));
    btnUp10->setConnectedEdges (Button::ConnectedOnTop | Button::ConnectedOnBottom);
    btnUp10->addListener (this);

    btnUp10->setBounds (1032, 208, 40, 24);

    btnUp100.reset (new TextButton ("new button"));
    addAndMakeVisible (btnUp100.get());
    btnUp100->setButtonText (TRANS("^^"));
    btnUp100->setConnectedEdges (Button::ConnectedOnTop | Button::ConnectedOnBottom);
    btnUp100->addListener (this);

    btnUp100->setBounds (1032, 184, 40, 24);

    btnUp1000.reset (new TextButton ("new button"));
    addAndMakeVisible (btnUp1000.get());
    btnUp1000->setButtonText (TRANS("^^^"));
    btnUp1000->setConnectedEdges (Button::ConnectedOnBottom);
    btnUp1000->addListener (this);

    btnUp1000->setBounds (1032, 160, 40, 24);

    btnDn10.reset (new TextButton ("new button"));
    addAndMakeVisible (btnDn10.get());
    btnDn10->setButtonText (TRANS("v"));
    btnDn10->setConnectedEdges (Button::ConnectedOnTop | Button::ConnectedOnBottom);
    btnDn10->addListener (this);

    btnDn10->setBounds (1032, 256, 40, 24);

    btnDn100.reset (new TextButton ("new button"));
    addAndMakeVisible (btnDn100.get());
    btnDn100->setButtonText (TRANS("vv"));
    btnDn100->setConnectedEdges (Button::ConnectedOnTop | Button::ConnectedOnBottom);
    btnDn100->addListener (this);

    btnDn100->setBounds (1032, 280, 40, 24);

    btnDn1000.reset (new TextButton ("new button"));
    addAndMakeVisible (btnDn1000.get());
    btnDn1000->setButtonText (TRANS("vvv"));
    btnDn1000->setConnectedEdges (Button::ConnectedOnTop);
    btnDn1000->addListener (this);

    btnDn1000->setBounds (1032, 304, 40, 24);


    //[UserPreSize]

    lsmResults.reset(new TextListModel());
    lsmResults->setListener(this);

    lstResults.reset(new ListBox("Results", lsmResults.get()));
    addAndMakeVisible(lstResults.get());
    lstResults->setMultipleSelectionEnabled(false);
    lstResults->setRowHeight(16);
    lstResults->setOutlineThickness(1);
    lstResults->setColour(ListBox::outlineColourId, Colours::lightgrey);

    txtAudioseqMinLen->addListener(this);
    txtHexAddr->addListener(this);

    txtHex->setFont (Font (Font::getDefaultMonospacedFontName(), 14.00f, Font::plain));

    //[/UserPreSize]

    setSize (1078, 713);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

Finder::~Finder()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    grpOptions = nullptr;
    grpTarget = nullptr;
    optTargetIndex = nullptr;
    optTargetAudiobank = nullptr;
    optTargetAudioseq = nullptr;
    optTargetAudiotable = nullptr;
    chkIndexUnmodded = nullptr;
    label = nullptr;
    txtAudioseqMinLen = nullptr;
    label2 = nullptr;
    optAlign4 = nullptr;
    optAlign8 = nullptr;
    optAlign16 = nullptr;
    label3 = nullptr;
    btnGo = nullptr;
    txtHex = nullptr;
    label4 = nullptr;
    txtHexAddr = nullptr;
    btnUp10 = nullptr;
    btnUp100 = nullptr;
    btnUp1000 = nullptr;
    btnDn10 = nullptr;
    btnDn100 = nullptr;
    btnDn1000 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    lstResults = nullptr;
    lsmResults = nullptr;
    //[/Destructor]
}

//==============================================================================
void Finder::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void Finder::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    lstResults->setBounds(8, 176, 424, 296);
    //[/UserResized]
}

void Finder::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    uint32 hexaddr = txtHexAddr->getText().getHexValue32();
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == optTargetIndex.get())
    {
        //[UserButtonCode_optTargetIndex] -- add your button handler code here..
        //[/UserButtonCode_optTargetIndex]
    }
    else if (buttonThatWasClicked == optTargetAudiobank.get())
    {
        //[UserButtonCode_optTargetAudiobank] -- add your button handler code here..
        //[/UserButtonCode_optTargetAudiobank]
    }
    else if (buttonThatWasClicked == optTargetAudioseq.get())
    {
        //[UserButtonCode_optTargetAudioseq] -- add your button handler code here..
        //[/UserButtonCode_optTargetAudioseq]
    }
    else if (buttonThatWasClicked == optTargetAudiotable.get())
    {
        //[UserButtonCode_optTargetAudiotable] -- add your button handler code here..
        //[/UserButtonCode_optTargetAudiotable]
    }
    else if (buttonThatWasClicked == chkIndexUnmodded.get())
    {
        //[UserButtonCode_chkIndexUnmodded] -- add your button handler code here..
        //[/UserButtonCode_chkIndexUnmodded]
    }
    else if (buttonThatWasClicked == optAlign4.get())
    {
        //[UserButtonCode_optAlign4] -- add your button handler code here..
        //[/UserButtonCode_optAlign4]
    }
    else if (buttonThatWasClicked == optAlign8.get())
    {
        //[UserButtonCode_optAlign8] -- add your button handler code here..
        //[/UserButtonCode_optAlign8]
    }
    else if (buttonThatWasClicked == optAlign16.get())
    {
        //[UserButtonCode_optAlign16] -- add your button handler code here..
        //[/UserButtonCode_optAlign16]
    }
    else if (buttonThatWasClicked == btnGo.get())
    {
        //[UserButtonCode_btnGo] -- add your button handler code here..
        if(seq64.rom.getSize() <= 0){
            NativeMessageBox::showMessageBox(AlertWindow::WarningIcon, "seq64",
                    "You must have a ROM loaded before trying to find data in it!");
            return;
        }
        lsmResults->clear();
        lstResults->updateContent();
        int align = optAlign4->getToggleState() ? 4 :
                    (optAlign8->getToggleState() ? 8 : 16);
        if(optTargetIndex->getToggleState()){
            findIndex(align, chkIndexUnmodded->getToggleState());
        }else if(optTargetAudiobank->getToggleState()){
            findAudiobank(align);
        }else if(optTargetAudioseq->getToggleState()){
            int minlen = txtAudioseqMinLen->getText().getIntValue();
            if(minlen <= 1){
                NativeMessageBox::showMessageBox(AlertWindow::WarningIcon, "Stop it",
                        "Minimum sequence length must be at least 2.");
                return;
            }
            findAudioseq(align, minlen);
        }else if(optTargetAudiotable->getToggleState()){
            findAudiotable(align);
        }
        //[/UserButtonCode_btnGo]
    }
    else if (buttonThatWasClicked == btnUp10.get())
    {
        //[UserButtonCode_btnUp10] -- add your button handler code here..
        hexaddr < 0x10 ? hexaddr = 0 : hexaddr -= 0x10;
        renderHex(hexaddr, true);
        //[/UserButtonCode_btnUp10]
    }
    else if (buttonThatWasClicked == btnUp100.get())
    {
        //[UserButtonCode_btnUp100] -- add your button handler code here..
        hexaddr < 0x100 ? hexaddr = 0 : hexaddr -= 0x100;
        renderHex(hexaddr, true);
        //[/UserButtonCode_btnUp100]
    }
    else if (buttonThatWasClicked == btnUp1000.get())
    {
        //[UserButtonCode_btnUp1000] -- add your button handler code here..
        hexaddr < 0x1000 ? hexaddr = 0 : hexaddr -= 0x1000;
        renderHex(hexaddr, true);
        //[/UserButtonCode_btnUp1000]
    }
    else if (buttonThatWasClicked == btnDn10.get())
    {
        //[UserButtonCode_btnDn10] -- add your button handler code here..
        uint32 endpos = seq64.rom.getSize() - 0x10;
        hexaddr >= endpos ? hexaddr = endpos : hexaddr += 0x10;
        renderHex(hexaddr, true);
        //[/UserButtonCode_btnDn10]
    }
    else if (buttonThatWasClicked == btnDn100.get())
    {
        //[UserButtonCode_btnDn100] -- add your button handler code here..
        uint32 endpos = seq64.rom.getSize() - 0x10;
        hexaddr >= endpos ? hexaddr = endpos : hexaddr += 0x100;
        renderHex(hexaddr, true);
        //[/UserButtonCode_btnDn100]
    }
    else if (buttonThatWasClicked == btnDn1000.get())
    {
        //[UserButtonCode_btnDn1000] -- add your button handler code here..
        uint32 endpos = seq64.rom.getSize() - 0x10;
        hexaddr >= endpos ? hexaddr = endpos : hexaddr += 0x1000;
        renderHex(hexaddr, true);
        //[/UserButtonCode_btnDn1000]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void Finder::textEditorTextChanged(TextEditor& editorThatWasChanged)
{
    if(&editorThatWasChanged == &*txtAudioseqMinLen){
        //do nothing
    }else if(&editorThatWasChanged == &*txtHexAddr){
        uint32 addr = txtHexAddr->getText().getHexValue32();
        renderHex(addr, false);
    }
}

void Finder::rowSelected(TextListModel* parent, int row)
{
    if(parent == &*lsmResults){
        uint32 addr = lsmResults->get(lstResults->getLastRowSelected()).getHexValue32();
        renderHex(addr, true);
    }
}

void Finder::findIndex(int align, bool inorder){
    int indextype = seq64.romdesc.getProperty("indextype", 1);
    std::cout << "00000000";
    for(uint32 a=0; a<seq64.rom.getSize(); a += align){
        if((a & 0xFFF) == 0) std::cout << "\b\b\b\b\b\b\b\b" << ROM::hex(a);
        if(IndexedFile::couldBeIndex(seq64.rom, indextype, inorder, a)){
            lsmResults->add(ROM::hex(a));
        }
    }
    SEQ64::say("\nDone");
    lstResults->updateContent();
}

void Finder::findAudiobank(int align){
    NativeMessageBox::showMessageBox(AlertWindow::InfoIcon, "seq64",
            "Not implemented yet.");
}

void Finder::findAudioseq(int align, int minlen){
    NativeMessageBox::showMessageBox(AlertWindow::InfoIcon, "seq64",
            "Not implemented yet.");
}

void Finder::findAudiotable(int align){
    NativeMessageBox::showMessageBox(AlertWindow::InfoIcon, "seq64",
            "Not implemented yet.");
}

void Finder::renderHex(uint32 addr, bool updateTextBox){
    addr = addr & ~0xFu;
    if(updateTextBox) txtHexAddr->setText(ROM::hex(addr), dontSendNotification);
    String t;
    const int numLines = 25;
    uint32 a = addr;
    for(int l=0; l<numLines && a < seq64.rom.getSize(); ++l, a+=16){
        t += ROM::hex(a) + " ";
        for(int offset=0; offset<16; offset+=4){
            if(a+offset+3 < seq64.rom.getSize()){
                t += ROM::hex(seq64.rom.readWord(a+offset)) + " ";
            }else{
                t += "---- ";
            }
        }
        for(int offset=0; offset<16; offset++){
            if(a+offset < seq64.rom.getSize()){
                char b = seq64.rom.readByte(a+offset);
                t += (b == 0) ? ' ' : ((b < ' ' || b == 127 || b == 255) ? '.' : b);
            }else{
                t += ' ';
            }
        }
        t += '\n';
    }
    if(a >= seq64.rom.getSize()){
        t += "         [End of ROM]";
    }
    txtHex->setText(t);
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Finder" componentName=""
                 parentClasses="public Component, public TextEditor::Listener, public TextListModel::Listener"
                 constructorParams="SEQ64&amp; seq64_" variableInitialisers="seq64(seq64_)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="1078" initialHeight="713">
  <BACKGROUND backgroundColour="ff323e44"/>
  <GROUPCOMPONENT name="new group" id="22cce9cd82f610fd" memberName="grpOptions"
                  virtualName="" explicitFocusOrder="0" pos="144 0 296 96" title="Options:"/>
  <GROUPCOMPONENT name="new group" id="c5c17d99528e698a" memberName="grpTarget"
                  virtualName="" explicitFocusOrder="0" pos="0 0 144 120" title="Find:"/>
  <TOGGLEBUTTON name="new toggle button" id="cb1f215d61ddac60" memberName="optTargetIndex"
                virtualName="" explicitFocusOrder="0" pos="8 16 72 24" buttonText="Indexes"
                connectedEdges="0" needsCallback="1" radioGroupId="1" state="1"/>
  <TOGGLEBUTTON name="new toggle button" id="bc0b2e7e740ba5d2" memberName="optTargetAudiobank"
                virtualName="" explicitFocusOrder="0" pos="8 40 128 24" buttonText="Audiobank Data"
                connectedEdges="0" needsCallback="1" radioGroupId="1" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="4b684836a6ecdec8" memberName="optTargetAudioseq"
                virtualName="" explicitFocusOrder="0" pos="8 64 120 24" buttonText="Audioseq Data"
                connectedEdges="0" needsCallback="1" radioGroupId="1" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="475949fb38a1325" memberName="optTargetAudiotable"
                virtualName="" explicitFocusOrder="0" pos="8 88 128 24" buttonText="Audiotable Data"
                connectedEdges="0" needsCallback="1" radioGroupId="1" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="a17322784e3d9e3a" memberName="chkIndexUnmodded"
                virtualName="" explicitFocusOrder="0" pos="152 16 280 24" buttonText="Assume index in order (unmodded ROM)"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="1"/>
  <LABEL name="new label" id="6800672903d6ba7b" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="152 64 160 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Min seq len w/o errors:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="e0d619049c848874" memberName="txtAudioseqMinLen"
              virtualName="" explicitFocusOrder="0" pos="312 64 32 24" initialText="16"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="b836e57c0b3bb6ac" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="152 40 88 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Object align:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TOGGLEBUTTON name="new toggle button" id="69a979403cc9ca8a" memberName="optAlign4"
                virtualName="" explicitFocusOrder="0" pos="240 40 40 24" buttonText="4"
                connectedEdges="0" needsCallback="1" radioGroupId="2" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="43fa4f8150a49082" memberName="optAlign8"
                virtualName="" explicitFocusOrder="0" pos="288 40 40 24" buttonText="8"
                connectedEdges="0" needsCallback="1" radioGroupId="2" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="911cc7b065753fe5" memberName="optAlign16"
                virtualName="" explicitFocusOrder="0" pos="336 40 40 24" buttonText="16"
                connectedEdges="0" needsCallback="1" radioGroupId="2" state="1"/>
  <LABEL name="new label" id="21ba8591f5265c2b" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="0 152 440 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Results:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="new button" id="6c78697d573b0ec7" memberName="btnGo" virtualName=""
              explicitFocusOrder="0" pos="8 128 424 24" buttonText="Go" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTEDITOR name="new text editor" id="12969d9fb3228896" memberName="txtHex"
              virtualName="" explicitFocusOrder="0" pos="448 32 576 424" initialText=""
              multiline="1" retKeyStartsLine="1" readonly="1" scrollbars="0"
              caret="0" popupmenu="0"/>
  <LABEL name="new label" id="4983ab390b322332" memberName="label4" virtualName=""
         explicitFocusOrder="0" pos="448 8 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Hex view:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="1e6c67edb21dd1b1" memberName="txtHexAddr"
              virtualName="" explicitFocusOrder="0" pos="520 8 72 24" initialText="00000000"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTBUTTON name="new button" id="dc80c4e60c28659d" memberName="btnUp10"
              virtualName="" explicitFocusOrder="0" pos="1032 208 40 24" buttonText="&#94;"
              connectedEdges="12" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="18975ab9e0afff1f" memberName="btnUp100"
              virtualName="" explicitFocusOrder="0" pos="1032 184 40 24" buttonText="&#94;&#94;"
              connectedEdges="12" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="ed72bd7d0915afa3" memberName="btnUp1000"
              virtualName="" explicitFocusOrder="0" pos="1032 160 40 24" buttonText="&#94;&#94;&#94;"
              connectedEdges="8" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="d11d533ed581de1b" memberName="btnDn10"
              virtualName="" explicitFocusOrder="0" pos="1032 256 40 24" buttonText="v"
              connectedEdges="12" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="7b283e2da9fd6fc8" memberName="btnDn100"
              virtualName="" explicitFocusOrder="0" pos="1032 280 40 24" buttonText="vv"
              connectedEdges="12" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="bc152feabefe6963" memberName="btnDn1000"
              virtualName="" explicitFocusOrder="0" pos="1032 304 40 24" buttonText="vvv"
              connectedEdges="4" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]


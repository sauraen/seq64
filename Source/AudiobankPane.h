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

#ifndef __JUCE_HEADER_96A217B8C2302D5C__
#define __JUCE_HEADER_96A217B8C2302D5C__

//[Headers]     -- You can add your own extra header files here --
/*
 * ============================================================================
 *
 * AudiobankPane.h
 * GUI component for Audiobank editor screen
 *
 * From seq64 - Sequenced music editor for first-party N64 games
 * Copyright (C) 2014-2015 Sauraen
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

#include "JuceHeader.h"
#include "seq64.h"
#include "TextListModel.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class AudiobankPane  : public Component,
                       public TextEditor::Listener,
                       public TextListModel::Listener,
                       public ComboBoxListener,
                       public ButtonListener
{
public:
    //==============================================================================
    AudiobankPane (SEQ64& seq64_);
    ~AudiobankPane();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void rowSelected(TextListModel* parent, int row) override;
    void rowDoubleClicked(TextListModel* parent, int row) override;
    void textEditorTextChanged(TextEditor& editorThatWasChanged) override;

    void romDescLoaded();
    void gotABI();
    void bankLoaded();

    String getFieldDesc(ValueTree field);
    void fillFieldsList();
    void fillFieldParams();
    void fillMeaningsBox();

    void fillLibItemsBox();
    void fillLibItemControls();

    void fillBItemsBox();
    void fillBItemsControls();

    ValueTree getBankSubList(int banknum, String sublistname);

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    void buttonClicked (Button* buttonThatWasClicked);
    void visibilityChanged();
    void broughtToFront();
    void focusGained (FocusChangeType cause);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    SEQ64& seq64;

    ScopedPointer<TextListModel> lsmFields;
    ScopedPointer<ListBox> lstFields;

    ScopedPointer<TextListModel> lsmLibSets;
    ScopedPointer<ListBox> lstLibSets;

    ScopedPointer<TextListModel> lsmLibItems;
    ScopedPointer<ListBox> lstLibItems;

    ScopedPointer<TextListModel> lsmBItems;
    ScopedPointer<ListBox> lstBItems;

    ValueTree abfstructsnode;
    ValueTree selstruct;
    ValueTree selfield;

    int abiaddr, abaddr;

    int libselbankidx;
    ScopedPointer<BankFile> libselbank;
    int libselitemidx;
    ValueTree libselitem;

    ValueTree bpath;
    ValueTree bselnode;

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<GroupComponent> groupComponent2;
    ScopedPointer<GroupComponent> groupComponent3;
    ScopedPointer<GroupComponent> groupComponent;
    ScopedPointer<ComboBox> cbxEditStruct;
    ScopedPointer<Label> label2;
    ScopedPointer<ToggleButton> optPointer;
    ScopedPointer<ComboBox> cbxDataType;
    ScopedPointer<ComboBox> cbxPtrTo;
    ScopedPointer<Label> label3;
    ScopedPointer<TextEditor> txtFieldName;
    ScopedPointer<ToggleButton> optArray;
    ScopedPointer<ToggleButton> optArrayFixed;
    ScopedPointer<ToggleButton> optArrayVar;
    ScopedPointer<TextEditor> txtArrayLen;
    ScopedPointer<ComboBox> cbxArrayLenVar;
    ScopedPointer<Label> label4;
    ScopedPointer<ComboBox> cbxMeaning;
    ScopedPointer<Label> lblStructBegin;
    ScopedPointer<Label> lblStructEnd;
    ScopedPointer<Label> label5;
    ScopedPointer<TextEditor> txtDefaultVal;
    ScopedPointer<TextButton> btnFieldAdd;
    ScopedPointer<TextButton> btnFieldDel;
    ScopedPointer<TextButton> btnFieldUp;
    ScopedPointer<TextButton> btnFieldDn;
    ScopedPointer<Label> label6;
    ScopedPointer<Label> label7;
    ScopedPointer<Label> lblStructSemicolon;
    ScopedPointer<Label> label;
    ScopedPointer<ComboBox> cbxLibList;
    ScopedPointer<TextButton> txtLibAdd;
    ScopedPointer<Label> label8;
    ScopedPointer<TextEditor> txtLibItemName;
    ScopedPointer<ToggleButton> chkLibMerge;
    ScopedPointer<TextButton> btnBItemAdd;
    ScopedPointer<TextButton> btnBItemDel;
    ScopedPointer<TextButton> btnBItemUp;
    ScopedPointer<TextButton> btnBItemDn;
    ScopedPointer<Label> label12;
    ScopedPointer<TextEditor> txtBItemName;
    ScopedPointer<ComboBox> cbxAlign;
    ScopedPointer<TextButton> btnBItemDupl;
    ScopedPointer<ToggleButton> optMapProgram;
    ScopedPointer<TextEditor> txtMapPNum;
    ScopedPointer<Label> lblMapPNote;
    ScopedPointer<TextEditor> txtMapPNote;
    ScopedPointer<ToggleButton> optMapDrum;
    ScopedPointer<TextEditor> txtMapDS1;
    ScopedPointer<TextEditor> txtMapDS2;
    ScopedPointer<TextEditor> txtMapDS3;
    ScopedPointer<Label> lblMapSplits;
    ScopedPointer<TextButton> btnBUp;
    ScopedPointer<TextButton> btnBOpen;
    ScopedPointer<Label> lblBankPath;
    ScopedPointer<Label> lblBItemType;
    ScopedPointer<Label> label10;
    ScopedPointer<TextEditor> txtBItemValue;
    ScopedPointer<Label> lblBItemValueEquiv;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudiobankPane)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_96A217B8C2302D5C__

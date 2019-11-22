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

#pragma once

//[Headers]     -- You can add your own extra header files here --
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
                       public ComboBox::Listener,
                       public Button::Listener
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

    void fillFieldsList();
    void fillFieldParams();
    void fillMeaningsBox();

    void fillLibItemsBox();
    void fillLibItemControls();

    void bOpen(int row);
    void fillBListControls();
    void fillBItemsBox();
    void fillBItemsControls(bool setTxtBItemValue);

    String getListName(String cbxLibListText);
    ValueTree getBankSubList(int banknum, String cbxLibListText);

    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void visibilityChanged() override;
    void broughtToFront() override;
    void focusGained (FocusChangeType cause) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    SEQ64& seq64;

    std::unique_ptr<TextListModel> lsmFields;
    std::unique_ptr<ListBox> lstFields;

    std::unique_ptr<TextListModel> lsmLibSets;
    std::unique_ptr<ListBox> lstLibSets;

    std::unique_ptr<TextListModel> lsmLibItems;
    std::unique_ptr<ListBox> lstLibItems;

    std::unique_ptr<TextListModel> lsmBItems;
    std::unique_ptr<ListBox> lstBItems;

    ValueTree abfstructsnode;
    ValueTree selstruct;
    ValueTree selfield;

    int abiaddr, abaddr;

    int libselbankidx;
    std::unique_ptr<BankFile> libselbank;
    int libselitemidx;
    ValueTree libselitem;

    ValueTree bpath;
    ValueTree bselnode;

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<GroupComponent> groupComponent2;
    std::unique_ptr<GroupComponent> groupComponent4;
    std::unique_ptr<GroupComponent> groupComponent3;
    std::unique_ptr<GroupComponent> groupComponent;
    std::unique_ptr<ComboBox> cbxEditStruct;
    std::unique_ptr<Label> label2;
    std::unique_ptr<ToggleButton> optPointer;
    std::unique_ptr<ComboBox> cbxDataType;
    std::unique_ptr<ComboBox> cbxPtrTo;
    std::unique_ptr<Label> label3;
    std::unique_ptr<TextEditor> txtFieldName;
    std::unique_ptr<ToggleButton> optArray;
    std::unique_ptr<ToggleButton> optArrayFixed;
    std::unique_ptr<ToggleButton> optArrayVar;
    std::unique_ptr<TextEditor> txtArrayLen;
    std::unique_ptr<ComboBox> cbxArrayLenVar;
    std::unique_ptr<Label> label4;
    std::unique_ptr<ComboBox> cbxMeaning;
    std::unique_ptr<Label> lblStructBegin;
    std::unique_ptr<Label> lblStructEnd;
    std::unique_ptr<Label> label5;
    std::unique_ptr<TextEditor> txtDefaultVal;
    std::unique_ptr<TextButton> btnFieldAdd;
    std::unique_ptr<TextButton> btnFieldDel;
    std::unique_ptr<TextButton> btnFieldUp;
    std::unique_ptr<TextButton> btnFieldDn;
    std::unique_ptr<Label> label6;
    std::unique_ptr<Label> label7;
    std::unique_ptr<Label> lblStructSemicolon;
    std::unique_ptr<Label> label;
    std::unique_ptr<ComboBox> cbxLibList;
    std::unique_ptr<TextButton> btnLibAdd;
    std::unique_ptr<Label> label8;
    std::unique_ptr<TextEditor> txtLibItemName;
    std::unique_ptr<ToggleButton> chkLibMerge;
    std::unique_ptr<TextButton> btnBItemAdd;
    std::unique_ptr<TextButton> btnBItemDupl;
    std::unique_ptr<TextButton> btnBItemDel;
    std::unique_ptr<TextButton> btnBItemUp;
    std::unique_ptr<TextButton> btnBItemDn;
    std::unique_ptr<Label> label12;
    std::unique_ptr<TextEditor> txtBItemName;
    std::unique_ptr<ComboBox> cbxAlign;
    std::unique_ptr<ToggleButton> optMapProgram;
    std::unique_ptr<TextEditor> txtMapPNum;
    std::unique_ptr<Label> lblMapPNote;
    std::unique_ptr<TextEditor> txtMapPNote;
    std::unique_ptr<ToggleButton> optMapDrum;
    std::unique_ptr<TextEditor> txtMapDS1;
    std::unique_ptr<TextEditor> txtMapDS2;
    std::unique_ptr<TextEditor> txtMapDS3;
    std::unique_ptr<Label> lblMapSplits;
    std::unique_ptr<TextButton> btnBUp;
    std::unique_ptr<TextButton> btnBOpen;
    std::unique_ptr<Label> lblBankPath;
    std::unique_ptr<Label> lblBItemType;
    std::unique_ptr<Label> lblBItemValue;
    std::unique_ptr<TextEditor> txtBItemValue;
    std::unique_ptr<Label> lblBItemValueEquiv;
    std::unique_ptr<ToggleButton> chkBItemHex;
    std::unique_ptr<TextButton> btnSaveXML;
    std::unique_ptr<TextButton> btnLoadXML;
    std::unique_ptr<ToggleButton> chkLibFixAddr;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudiobankPane)
};

//[EndFile] You can add extra defines here...
//[/EndFile]


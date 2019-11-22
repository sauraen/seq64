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
 * FilesPane.h
 * GUI component for N64 ROM internal files screen
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
#include "IndexedFile.h"
#include "SequenceBanksMap.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class FilesPane  : public Component,
                   public TextEditor::Listener,
                   public TextListModel::Listener,
                   public ComboBox::Listener,
                   public Button::Listener
{
public:
    //==============================================================================
    FilesPane (SEQ64& seq64_);
    ~FilesPane();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void rowSelected(TextListModel* parent, int row);
    void textEditorTextChanged(TextEditor& editorThatWasChanged);

    void reloadFiles();
	void romDescLoaded();
	String getFileDescription(uint32 a, int i);
	void fillFileTable();
	bool isKnownFileType(String filetype);
	void fillKFiles();
	void fillKFileParams();
	void fillIndex();
	void fillIEntryParams();
	void ieNameChanged(bool updateNameBox);
	void fillSeqBankList();
	void fixSBMForBankChange(bool add, int idx);
    void fixSampleTables(bool add, int idx);

    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;
    void buttonClicked (Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    SEQ64& seq64;

    ValueTree filelistnode;
    ValueTree kfilelistnode;

	IndexedFile audiobank;
	IndexedFile audioseq;
	IndexedFile audiotable;
	SequenceBanksMap sbm;

	IndexedFile *selifile;
    ValueTree selkfile;
    int ientryidx;

    std::unique_ptr<TextListModel> lsmFileTable;
    std::unique_ptr<ListBox> lstFileTable;

    std::unique_ptr<TextListModel> lsmKFiles;
    std::unique_ptr<ListBox> lstKFiles;

    std::unique_ptr<TextListModel> lsmIndex;
    std::unique_ptr<ListBox> lstIndex;

    std::unique_ptr<TextListModel> lsmSeqBanks;
    std::unique_ptr<ListBox> lstSeqBanks;

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<GroupComponent> grpSeqBanks;
    std::unique_ptr<GroupComponent> grpIndex;
    std::unique_ptr<GroupComponent> grpUtilitiesEntry;
    std::unique_ptr<GroupComponent> groupComponent;
    std::unique_ptr<GroupComponent> grpUtilitiesContents;
    std::unique_ptr<GroupComponent> grpMFT;
    std::unique_ptr<Label> label;
    std::unique_ptr<TextEditor> txtFTAddr;
    std::unique_ptr<Label> label2;
    std::unique_ptr<TextEditor> txtFileName;
    std::unique_ptr<Label> label3;
    std::unique_ptr<ComboBox> cbxFileType;
    std::unique_ptr<Label> label4;
    std::unique_ptr<GroupComponent> grpKnownFiles;
    std::unique_ptr<TextButton> btnKFileAdd;
    std::unique_ptr<TextButton> btnKFileDel;
    std::unique_ptr<Label> label5;
    std::unique_ptr<ComboBox> cbxKFileType;
    std::unique_ptr<Label> label6;
    std::unique_ptr<TextEditor> txtKFileAddr;
    std::unique_ptr<Label> label7;
    std::unique_ptr<TextEditor> txtKFileLength;
    std::unique_ptr<Label> lblIndexProps;
    std::unique_ptr<Label> label11;
    std::unique_ptr<TextEditor> txtIEntryName;
    std::unique_ptr<Label> lblIEntryData;
    std::unique_ptr<TextButton> btnLoadObject;
    std::unique_ptr<TextButton> btnSaveObject;
    std::unique_ptr<ToggleButton> optIndexType1;
    std::unique_ptr<ToggleButton> optIndexType2;
    std::unique_ptr<Label> label10;
    std::unique_ptr<ComboBox> cbxSeqBank;
    std::unique_ptr<TextButton> btnEditIE;
    std::unique_ptr<TextButton> btnCompact;
    std::unique_ptr<TextButton> btnMakeRoom;
    std::unique_ptr<Label> label8;
    std::unique_ptr<TextEditor> txtMakeRoom;
    std::unique_ptr<TextButton> btnContentsCreate;
    std::unique_ptr<TextButton> btnContentsDestroy;
    std::unique_ptr<Label> label9;
    std::unique_ptr<TextEditor> txtEntryPointer;
    std::unique_ptr<TextButton> btnEntryInsert;
    std::unique_ptr<TextButton> btnEntryAdd;
    std::unique_ptr<TextButton> btnEntryDelete;
    std::unique_ptr<Label> label12;
    std::unique_ptr<TextButton> btnSBMAdd;
    std::unique_ptr<TextButton> btnSBMDelete;
    std::unique_ptr<Label> label13;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilesPane)
};

//[EndFile] You can add extra defines here...
//[/EndFile]


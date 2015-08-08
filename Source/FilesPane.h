/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.2.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_D435D114E1D83102__
#define __JUCE_HEADER_D435D114E1D83102__

//[Headers]     -- You can add your own extra header files here --
/*
 * ============================================================================
 *
 * FilesPane.h
 * GUI component for N64 ROM internal files screen
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
class FilesPane  : public Component,
                   public TextEditor::Listener,
                   public TextListModel::Listener,
                   public ComboBoxListener,
                   public ButtonListener
{
public:
    //==============================================================================
    FilesPane (SEQ64& seq64_);
    ~FilesPane();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void rowSelected(TextListModel* parent, int row);
    void textEditorTextChanged(TextEditor& editorThatWasChanged);

    bool isKnownFileType(String filetype);
    void changedIndexAddress(String indextype, int newaddress);
    String getFileDescription(uint32 a, int i);
    void fillFileTable();

    void fillKFiles();
    void fillKFileParams();
    void fillCodeRefs();

    void fillIndex();
    String getIEntryDescription(int i);
    void fillIEntryParams();
    void fillInstSetBoxes();

    void romDescLoaded();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    void buttonClicked (Button* buttonThatWasClicked);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    SEQ64& seq64;

    uint32 ftaddr, ftend;
    ValueTree filelistnode;
    ValueTree kfilelistnode;
    ValueTree idxlistnode;
    ValueTree selkfile;
    uint32 indexaddr;
    uint32 dataaddr;
    int ientryidx;
    ValueTree selindex;
    ValueTree seldata;

    int abi_addr;
    int asi_addr;
    int ssi_addr;
    int isi_addr;

    int abi_count;
    int asi_count;
    int ssi_count;

    ScopedPointer<TextListModel> lsmFileTable;
    ScopedPointer<ListBox> lstFileTable;

    ScopedPointer<TextListModel> lsmKFiles;
    ScopedPointer<ListBox> lstKFiles;

    ScopedPointer<TextListModel> lsmCodeRefs;
    ScopedPointer<ListBox> lstCodeRefs;

    ScopedPointer<TextListModel> lsmIndex;
    ScopedPointer<ListBox> lstIndex;

    ScopedPointer<TextListModel> lsmInstSets;
    ScopedPointer<ListBox> lstInstSets;

    int seq_lastbank;

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<GroupComponent> groupComponent;
    ScopedPointer<Label> label;
    ScopedPointer<TextEditor> txtFTAddr;
    ScopedPointer<Label> label2;
    ScopedPointer<TextEditor> txtFileName;
    ScopedPointer<Label> label3;
    ScopedPointer<ComboBox> cbxFileType;
    ScopedPointer<Label> label4;
    ScopedPointer<GroupComponent> groupComponent2;
    ScopedPointer<TextButton> btnKFileAdd;
    ScopedPointer<TextButton> btnKFileDel;
    ScopedPointer<GroupComponent> groupComponent3;
    ScopedPointer<Label> label5;
    ScopedPointer<ComboBox> cbxKFileType;
    ScopedPointer<Label> label6;
    ScopedPointer<TextEditor> txtKFileAddr;
    ScopedPointer<Label> label7;
    ScopedPointer<TextEditor> txtKFileLength;
    ScopedPointer<TextButton> btnCodeRefAdd;
    ScopedPointer<TextButton> btnCodeRefDel;
    ScopedPointer<TextButton> btnCodeRefFind;
    ScopedPointer<Label> label8;
    ScopedPointer<TextEditor> txtKFileMoveAddr;
    ScopedPointer<Label> label9;
    ScopedPointer<Label> lblMoveFree;
    ScopedPointer<TextButton> btnMoveKFile;
    ScopedPointer<GroupComponent> grpIndex;
    ScopedPointer<Label> lblIndexProps;
    ScopedPointer<Label> label11;
    ScopedPointer<TextEditor> txtIEntryName;
    ScopedPointer<Label> lblIEntryData;
    ScopedPointer<TextButton> btnLoadEntry;
    ScopedPointer<TextButton> btnSaveEntry;
    ScopedPointer<GroupComponent> groupComponent4;
    ScopedPointer<ToggleButton> optIndexType1;
    ScopedPointer<ToggleButton> optIndexType2;
    ScopedPointer<Label> lblInstSet;
    ScopedPointer<Label> label10;
    ScopedPointer<ComboBox> cbxInstSet1;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilesPane)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_D435D114E1D83102__

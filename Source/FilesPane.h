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
 * Copyright (C) 2014-2018 Sauraen
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

    void fillFileTable();
    void fillKFiles();
    void fillKFileParams();
    void fillIndex();
    void refreshIndexEntry();
    void fillIEntryParams();
    void fillInstSetBoxes();

    void romDescLoaded();

    bool isKnownFileType(String filetype);
    ValueTree getFileForIndex(String indexname);
    String getFileDescription(uint32 a, int i);
    String getIEntryDescription(int i);

    void setIEntryName(String newname, bool updateNameBox);
    void changedIndexAddress(String indextype, int newaddress);
    void loadIndexParams(String indexname);
    void validateIndexParams(int iaddr, int32 &addr_out, int16 &count_out);
    int16 getIndexCount(uint32 iaddr);
    void readIEAddrLen(uint32 iaddr, int entry, uint32 &address, uint32 &length);
    void writeIEAddr(uint32 iaddr, int entry, uint32 address);
    void writeIELen(uint32 iaddr, int entry, uint32 length);
    bool getIndexAndFileParams(int32 &ilen, int32 &faddr, String &indexname, String &filename);
    int getFileRealEnd(int knownend);
    uint32 getRealEntrySize(int i);
    int getLastObjectEnd(int32 faddr);
    void moveRestOfFile(uint32 faddr, int32 flen, int32 dstart, int32 delta);
    bool updateFileLength(String filename, int32 faddr, int32 flen);


    bool compact();
    int makeroom(int mrlen);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    void buttonClicked (Button* buttonThatWasClicked);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    SEQ64& seq64;

    uint32 ftaddr;
    ValueTree filelistnode;
    ValueTree kfilelistnode;
    ValueTree idxlistnode;
    ValueTree selkfile;
    uint32 dataaddr;
    int ientryidx;
    ValueTree selindex;
    ValueTree seldata;

    uint32 indexaddr;
    int32 abi_addr;
    int32 asi_addr;
    int32 ssi_addr;
    int32 isi_addr;

    int16 indexcount;
    int16 abi_count;
    int16 asi_count;
    int16 ssi_count;

    ScopedPointer<TextListModel> lsmFileTable;
    ScopedPointer<ListBox> lstFileTable;

    ScopedPointer<TextListModel> lsmKFiles;
    ScopedPointer<ListBox> lstKFiles;

    ScopedPointer<TextListModel> lsmIndex;
    ScopedPointer<ListBox> lstIndex;

    ScopedPointer<TextListModel> lsmInstSets;
    ScopedPointer<ListBox> lstInstSets;

    int seq_lastbank;

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<GroupComponent> grpUtilities;
    ScopedPointer<GroupComponent> grpUtilitiesContents;
    ScopedPointer<GroupComponent> grpMFT;
    ScopedPointer<Label> label;
    ScopedPointer<TextEditor> txtFTAddr;
    ScopedPointer<Label> label2;
    ScopedPointer<TextEditor> txtFileName;
    ScopedPointer<Label> label3;
    ScopedPointer<ComboBox> cbxFileType;
    ScopedPointer<Label> label4;
    ScopedPointer<GroupComponent> grpKnownFiles;
    ScopedPointer<TextButton> btnKFileAdd;
    ScopedPointer<TextButton> btnKFileDel;
    ScopedPointer<Label> label5;
    ScopedPointer<ComboBox> cbxKFileType;
    ScopedPointer<Label> label6;
    ScopedPointer<TextEditor> txtKFileAddr;
    ScopedPointer<Label> label7;
    ScopedPointer<TextEditor> txtKFileLength;
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
    ScopedPointer<TextButton> btnEditIE;
    ScopedPointer<TextButton> btnCompact;
    ScopedPointer<TextButton> btnMakeRoom;
    ScopedPointer<Label> label8;
    ScopedPointer<TextEditor> txtMakeRoom;
    ScopedPointer<TextButton> btnContentsCreate;
    ScopedPointer<TextButton> btnContentsDestroy;
    ScopedPointer<Label> label9;
    ScopedPointer<TextEditor> txtEntryPointer;
    ScopedPointer<GroupComponent> grpUtilitiesEntry;
    ScopedPointer<TextButton> btnEntryInsert;
    ScopedPointer<TextButton> btnEntryAdd;
    ScopedPointer<TextButton> btnEntryDelete;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilesPane)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_D435D114E1D83102__

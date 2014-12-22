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

#ifndef __JUCE_HEADER_D435D114E1D83102__
#define __JUCE_HEADER_D435D114E1D83102__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "AppProps.h"
#include "TextListModel.h"
#include "MainComponent.h"
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
    FilesPane (AppProps& props);
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
    AppProps& p;

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

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

#ifndef __JUCE_HEADER_56393DD1B7734788__
#define __JUCE_HEADER_56393DD1B7734788__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "ROM.h"
#include "SeqFile.h"
#include "TextListModel.h"
#include "AppProps.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class MainView  : public Component,
                  public TextEditor::Listener,
                  public TextListModel::Listener,
                  public ButtonListener,
                  public ComboBoxListener
{
public:
    //==============================================================================
    MainView ();
    ~MainView();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void rowSelected(TextListModel* parent, int row);
    void textEditorTextChanged(TextEditor& editorThatWasChanged);
    void recalcAddresses();
    void refillTable();
    void refreshCmdList();
    void refreshCmdControls();
    void refreshParamList();
    void refreshParamControls();
    void fillMeaningsBox(String action);
    void fillSeqSectionsBox();
    void listSeqCommands();

    String getCommandDesc(ValueTree cmd);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    File mainfolder;
    File romfile;
    File romdescfile;

    ROM rom;
    ValueTree romdesc;

    uint32 ftaddr;
    uint32 abfindex, asfindex, atfindex;
    uint32 abfaddr, asfaddr, atfaddr;
    uint32 abtaddr, astaddr, sstaddr;
    uint32 abtsize, astsize, sstsize;

    int whichtable;

    ValueTree selcmd;
    ValueTree selparam;

    ScopedPointer<SeqFile> seq;


    ScopedPointer<ListBox> lstTable;
    ScopedPointer<TextListModel> lsmTable;

    ScopedPointer<ListBox> lstCommands;
    ScopedPointer<TextListModel> lsmCommands;

    ScopedPointer<ListBox> lstParameters;
    ScopedPointer<TextListModel> lsmParameters;

    ScopedPointer<ListBox> lstSeq;
    ScopedPointer<TextListModel> lsmSeq;

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<GroupComponent> groupComponent7;
    ScopedPointer<GroupComponent> groupComponent4;
    ScopedPointer<GroupComponent> groupComponent3;
    ScopedPointer<GroupComponent> groupComponent6;
    ScopedPointer<GroupComponent> groupComponent5;
    ScopedPointer<GroupComponent> groupComponent2;
    ScopedPointer<GroupComponent> groupComponent;
    ScopedPointer<TextButton> btnLoadRom;
    ScopedPointer<TextButton> btnSaveROM;
    ScopedPointer<TextButton> btnLoadDesc;
    ScopedPointer<TextButton> btnSaveDesc;
    ScopedPointer<Label> label2;
    ScopedPointer<TextEditor> txtFTAddr;
    ScopedPointer<Label> label3;
    ScopedPointer<TextEditor> txtABFIndex;
    ScopedPointer<Label> label4;
    ScopedPointer<TextEditor> txtASFIndex;
    ScopedPointer<Label> label5;
    ScopedPointer<TextEditor> txtATFIndex;
    ScopedPointer<Label> lblABFAddr;
    ScopedPointer<Label> lblASFAddr;
    ScopedPointer<Label> lblATFAddr;
    ScopedPointer<Label> label6;
    ScopedPointer<TextEditor> txtABTAddr;
    ScopedPointer<Label> label7;
    ScopedPointer<TextEditor> txtASTAddr;
    ScopedPointer<Label> label8;
    ScopedPointer<TextEditor> txtSSTAddr;
    ScopedPointer<Label> lblABTSize;
    ScopedPointer<Label> lblASTSize;
    ScopedPointer<Label> lblSSTSize;
    ScopedPointer<Label> lblROMFile;
    ScopedPointer<TextButton> btnABTView;
    ScopedPointer<TextButton> btnASTView;
    ScopedPointer<TextButton> btnSSTView;
    ScopedPointer<Label> lblTableName;
    ScopedPointer<Label> label10;
    ScopedPointer<TextEditor> txtCmd;
    ScopedPointer<TextButton> btnCmdAdd;
    ScopedPointer<TextButton> btnCmdDel;
    ScopedPointer<ToggleButton> optCmdDataFixed;
    ScopedPointer<ToggleButton> optCmdDataVar;
    ScopedPointer<Label> lblCmdDataSize;
    ScopedPointer<TextEditor> txtCmdDataSize;
    ScopedPointer<Label> label11;
    ScopedPointer<Label> label;
    ScopedPointer<ComboBox> cbxAction;
    ScopedPointer<Label> label9;
    ScopedPointer<TextEditor> txtCmdName;
    ScopedPointer<TextEditor> txtCmdEnd;
    ScopedPointer<Label> label12;
    ScopedPointer<ToggleButton> optCmdSeq;
    ScopedPointer<ToggleButton> optCmdChn;
    ScopedPointer<ToggleButton> optCmdTrk;
    ScopedPointer<Label> label13;
    ScopedPointer<TextButton> btnParamAdd;
    ScopedPointer<TextButton> btnParamDel;
    ScopedPointer<TextButton> btnParamUp;
    ScopedPointer<TextButton> btnParamDn;
    ScopedPointer<ToggleButton> optCmdOffset;
    ScopedPointer<Label> label14;
    ScopedPointer<Label> label15;
    ScopedPointer<TextEditor> txtParamName;
    ScopedPointer<Label> label16;
    ScopedPointer<ComboBox> cbxMeaning;
    ScopedPointer<Label> label17;
    ScopedPointer<Label> label18;
    ScopedPointer<TextEditor> txtParamAdd;
    ScopedPointer<TextEditor> txtParamMult;
    ScopedPointer<TextButton> btnCmdUp;
    ScopedPointer<TextButton> btnCmdDn;
    ScopedPointer<TextButton> btnSeq2MIDI;
    ScopedPointer<TextButton> btnMIDI2Seq;
    ScopedPointer<TextButton> btnReadSeq;
    ScopedPointer<TextButton> btnWriteSeq;
    ScopedPointer<Label> lblSeqInfo;
    ScopedPointer<TextButton> btnLoadMIDI;
    ScopedPointer<TextButton> btnSaveMIDI;
    ScopedPointer<Label> label20;
    ScopedPointer<ComboBox> cbxSeqSections;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainView)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_56393DD1B7734788__

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

#ifndef __JUCE_HEADER_20165588C3365AE__
#define __JUCE_HEADER_20165588C3365AE__

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
class AudioseqPane  : public Component,
                      public TextEditor::Listener,
                      public TextListModel::Listener,
                      public ButtonListener,
                      public ComboBoxListener
{
public:
    //==============================================================================
    AudioseqPane (AppProps& props);
    ~AudioseqPane();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void rowSelected(TextListModel* parent, int row);
    void textEditorTextChanged(TextEditor& editorThatWasChanged);

    String getCommandDesc(ValueTree cmd);
    void refreshCmdList();
    void refreshCmdControls();
    void refreshParamList();
    void refreshParamControls();
    void fillMeaningsBox(String action);
    void fillSeqSections();
    void fillSeqCommands();
    void refreshSeqCmdControls();
    void refreshSeqCmdParamControls();

    void seqStructureChanged();

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    void visibilityChanged();
    void broughtToFront();
    void focusGained (FocusChangeType cause);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    AppProps& p;

    ValueTree selcmd;
    ValueTree selparam;

    ScopedPointer<TextListModel> lsmCommands;
    ScopedPointer<ListBox> lstCommands;

    ScopedPointer<TextListModel> lsmParameters;
    ScopedPointer<ListBox> lstParameters;

    ScopedPointer<TextListModel> lsmSeqSections;
    ScopedPointer<ListBox> lstSeqSections;

    ScopedPointer<TextListModel> lsmSeqCommands;
    ScopedPointer<ListBox> lstSeqCommands;

    ScopedPointer<TextListModel> lsmSeqCmdParams;
    ScopedPointer<ListBox> lstSeqCmdParams;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<GroupComponent> groupComponent;
    ScopedPointer<GroupComponent> groupComponent2;
    ScopedPointer<GroupComponent> groupComponent3;
    ScopedPointer<GroupComponent> groupComponent6;
    ScopedPointer<GroupComponent> groupComponent5;
    ScopedPointer<Label> label10;
    ScopedPointer<TextEditor> txtCmd;
    ScopedPointer<TextButton> btnCmdAdd;
    ScopedPointer<TextButton> btnCmdDel;
    ScopedPointer<ToggleButton> optCmdDataFixed;
    ScopedPointer<ToggleButton> optCmdDataVar;
    ScopedPointer<Label> lblCmdDataSize;
    ScopedPointer<TextEditor> txtCmdDataSize;
    ScopedPointer<Label> label11;
    ScopedPointer<Label> label2;
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
    ScopedPointer<Label> label3;
    ScopedPointer<Label> label4;
    ScopedPointer<ToggleButton> optSecSeq;
    ScopedPointer<ToggleButton> optSecChn;
    ScopedPointer<ToggleButton> optSecTrk;
    ScopedPointer<TextButton> btnSeqCmdAdd;
    ScopedPointer<TextButton> btnSeqCmdDelete;
    ScopedPointer<TextButton> btnSeqCmdUp;
    ScopedPointer<TextButton> btnSeqCmdDn;
    ScopedPointer<ComboBox> cbxSeqCmdType;
    ScopedPointer<Label> label7;
    ScopedPointer<TextEditor> txtSeqCmdValue;
    ScopedPointer<Label> lblSeqInfo;
    ScopedPointer<Label> lblSeqCmdAction;
    ScopedPointer<Label> lblValueEquiv;
    ScopedPointer<Label> lblSeqCmdAction2;
    ScopedPointer<TextButton> btnReParse;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioseqPane)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_20165588C3365AE__

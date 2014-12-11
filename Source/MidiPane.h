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

#ifndef __JUCE_HEADER_521D5B2FDC85DAAE__
#define __JUCE_HEADER_521D5B2FDC85DAAE__

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
class MidiPane  : public Component,
                  public TextEditor::Listener,
                  public ButtonListener,
                  public ComboBoxListener
{
public:
    //==============================================================================
    MidiPane (AppProps& props);
    ~MidiPane();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void textEditorTextChanged(TextEditor& editorThatWasChanged);
    void refreshMIDIControls();

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    AppProps& p;
    ValueTree midioptsnode;

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<GroupComponent> groupComponent8;
    ScopedPointer<GroupComponent> groupComponent3;
    ScopedPointer<GroupComponent> groupComponent7;
    ScopedPointer<GroupComponent> groupComponent;
    ScopedPointer<TextButton> btnMIDIExport;
    ScopedPointer<TextButton> btnMIDIImport;
    ScopedPointer<Label> label20;
    ScopedPointer<TextEditor> txtMIDIBend;
    ScopedPointer<Label> label21;
    ScopedPointer<TextEditor> txtMIDIPPQN;
    ScopedPointer<Label> label22;
    ScopedPointer<Label> label23;
    ScopedPointer<ComboBox> cbxMIDIChnVol;
    ScopedPointer<Label> label24;
    ScopedPointer<ComboBox> cbxMIDIMtrVol;
    ScopedPointer<Label> label26;
    ScopedPointer<ComboBox> cbxChnPriority;
    ScopedPointer<ToggleButton> optSeqFormat;
    ScopedPointer<ToggleButton> optSeqType;
    ScopedPointer<ToggleButton> optChanBits;
    ScopedPointer<ToggleButton> optLoopAll;
    ScopedPointer<ToggleButton> optHeader;
    ScopedPointer<ToggleButton> optChanReset;
    ScopedPointer<GroupComponent> groupComponent2;
    ScopedPointer<ToggleButton> optPtrAbsolute;
    ScopedPointer<ToggleButton> optPtrShortest;
    ScopedPointer<ToggleButton> optPtrRelative;
    ScopedPointer<TextEditor> txtSeqFormat;
    ScopedPointer<TextEditor> txtSeqType;
    ScopedPointer<ToggleButton> optCalls;
    ScopedPointer<Label> label;
    ScopedPointer<TextEditor> txtStack;
    ScopedPointer<ToggleButton> optLoops;
    ScopedPointer<Label> label2;
    ScopedPointer<TextEditor> txtMergeVels;
    ScopedPointer<TextEditor> txtMergeGates;
    ScopedPointer<TextEditor> txtMergeCCs;
    ScopedPointer<Label> label3;
    ScopedPointer<Label> label4;
    ScopedPointer<TextEditor> txtQVolT;
    ScopedPointer<TextEditor> txtQOtherT;
    ScopedPointer<TextEditor> txtQVolA;
    ScopedPointer<TextEditor> txtQOtherA;
    ScopedPointer<Label> label5;
    ScopedPointer<Label> label6;
    ScopedPointer<Label> label7;
    ScopedPointer<Label> label8;
    ScopedPointer<Label> label9;
    ScopedPointer<Label> label10;
    ScopedPointer<TextEditor> txtQPitchT;
    ScopedPointer<TextEditor> txtQPitchA;
    ScopedPointer<Label> label11;
    ScopedPointer<TextEditor> txtQPanT;
    ScopedPointer<TextEditor> txtQPanA;
    ScopedPointer<Label> label12;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiPane)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_521D5B2FDC85DAAE__

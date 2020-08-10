/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.0.1

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include <JuceHeader.h>
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class SeqEditor  : public juce::Component,
                   public juce::Button::Listener
{
public:
    //==============================================================================
    SeqEditor ();
    ~SeqEditor() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void buttonClicked (juce::Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::TextButton> btnImportCom;
    std::unique_ptr<juce::TextButton> btnExportCom;
    std::unique_ptr<juce::TextButton> btnImportMus;
    std::unique_ptr<juce::TextButton> btnExportMus;
    std::unique_ptr<juce::GroupComponent> grpMusDialect;
    std::unique_ptr<juce::ToggleButton> optMusCommunity;
    std::unique_ptr<juce::ToggleButton> optMusCanon;
    std::unique_ptr<juce::ToggleButton> optMusCanonOld;
    std::unique_ptr<juce::TextButton> btnImportMIDI;
    std::unique_ptr<juce::TextButton> btnExportMIDI;
    std::unique_ptr<juce::GroupComponent> grpImportMIDI;
    std::unique_ptr<juce::ToggleButton> chkLoopSeq;
    std::unique_ptr<juce::GroupComponent> grpOptimizer;
    std::unique_ptr<juce::ToggleButton> chkUseCalls;
    std::unique_ptr<juce::TextEditor> txtMasterVol;
    std::unique_ptr<juce::Label> lblMasterVol;
    std::unique_ptr<juce::ToggleButton> chkUseLoops;
    std::unique_ptr<juce::TextEditor> txtMergeVel;
    std::unique_ptr<juce::Label> lblMergeVel;
    std::unique_ptr<juce::TextEditor> txtMergeGates;
    std::unique_ptr<juce::Label> lblMergeGates;
    std::unique_ptr<juce::TextEditor> txtMergeCCs;
    std::unique_ptr<juce::Label> lblMergeCCs;
    std::unique_ptr<juce::TextEditor> txtQuantVolPan;
    std::unique_ptr<juce::Label> lblQuantVolPan;
    std::unique_ptr<juce::TextEditor> txtQuantPitch;
    std::unique_ptr<juce::Label> lblQuantPitch;
    std::unique_ptr<juce::TextEditor> txtQuantOther;
    std::unique_ptr<juce::Label> lblQuantOther;
    std::unique_ptr<juce::Label> lblMerge;
    std::unique_ptr<juce::Label> lblQuant;
    std::unique_ptr<juce::GroupComponent> grpExportMIDI;
    std::unique_ptr<juce::ToggleButton> optInstOrig;
    std::unique_ptr<juce::ToggleButton> optInstGM10;
    std::unique_ptr<juce::ToggleButton> optInstGMMulti;
    std::unique_ptr<juce::Label> lblBend;
    std::unique_ptr<juce::TextEditor> txtBend;
    std::unique_ptr<juce::Label> lblPPQN;
    std::unique_ptr<juce::TextEditor> txtPPQN;
    std::unique_ptr<juce::TextEditor> juce__textEditor;
    std::unique_ptr<juce::Label> lblInternal;
    std::unique_ptr<juce::Label> lblDebug;
    std::unique_ptr<juce::TextEditor> juce__textEditor2;
    std::unique_ptr<juce::GroupComponent> grpComFormat;
    std::unique_ptr<juce::TextButton> btnFormatEdit;
    std::unique_ptr<juce::ToggleButton> chkRel;
    juce::Path internalPath1;
    juce::Path internalPath2;
    juce::Path internalPath3;
    juce::Path internalPath4;
    juce::Path internalPath5;
    juce::Path internalPath6;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SeqEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]


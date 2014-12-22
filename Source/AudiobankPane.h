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
class AudiobankPane  : public Component,
                       public TextEditor::Listener,
                       public TextListModel::Listener,
                       public ComboBoxListener,
                       public ButtonListener
{
public:
    //==============================================================================
    AudiobankPane (AppProps& props);
    ~AudiobankPane();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void rowSelected(TextListModel* parent, int row);
    void textEditorTextChanged(TextEditor& editorThatWasChanged);

    void romDescLoaded();

    String getFieldDesc(ValueTree field);
    void fillFieldsList();
    void fillFieldParams();
    void fillMeaningsBox();

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    void buttonClicked (Button* buttonThatWasClicked);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    AppProps& p;

    ScopedPointer<TextListModel> lsmFields;
    ScopedPointer<ListBox> lstFields;

    ValueTree abfstructsnode;
    ValueTree selstruct;
    ValueTree selfield;

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
    ScopedPointer<TextEditor> textEditor;
    ScopedPointer<ComboBox> cbxLibList;
    ScopedPointer<TextEditor> textEditor2;
    ScopedPointer<TextButton> textButton;
    ScopedPointer<Label> label8;
    ScopedPointer<TextEditor> txtLibItemName;
    ScopedPointer<ToggleButton> toggleButton;
    ScopedPointer<ComboBox> cbxISItems;
    ScopedPointer<Label> label9;
    ScopedPointer<Label> label10;
    ScopedPointer<TextEditor> PH_lstISItems;
    ScopedPointer<TextButton> btnISItemAdd;
    ScopedPointer<TextButton> btnISItemDel;
    ScopedPointer<TextButton> btnISItemUp;
    ScopedPointer<TextButton> btnISItemDn;
    ScopedPointer<Label> label11;
    ScopedPointer<Label> label12;
    ScopedPointer<TextEditor> txtISItemName;
    ScopedPointer<Label> label13;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudiobankPane)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_96A217B8C2302D5C__

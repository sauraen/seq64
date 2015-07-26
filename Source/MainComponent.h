/*
  ==============================================================================

    MainComponent.h
    Created: 13 Nov 2014 9:25:30am
    Author:  Sauraen

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "JuceHeader.h"
#include "AppProps.h"
#include "yaz0_yay0.h"

class FilesPane;
class AudioseqPane;
class MidiPane;
class AudiobankPane;

//==============================================================================
/*
*/


class MainComponent    : public Component,
                         public MenuBarModel
{
public:
    MainComponent(DocumentWindow& window_);
    ~MainComponent();
    
    StringArray getMenuBarNames() override;
    PopupMenu getMenuForIndex(int topLevelMenuIndex, const String &menuName) override;
    void menuItemSelected(int menuItemID, int topLevelMenuIndex) override;

    void queryByteOrdering();
    void doCodecOperation(int operation);
    
    void paint (Graphics&);
    void resized();
    
    void actuallySaveROM();
    void actuallySaveRomDesc();
    
    void onROMLoaded();
    void onRomDescLoaded();
    void onSeqLoaded();
    void onBankLoaded();

private:
    DocumentWindow& window;
    AppProps p;
    File mainfolder;
    File romfile;
    File romdescfile;
    
    StringArray menunames;
    OwnedArray<PopupMenu> menus;
    OwnedArray<PopupMenu> submenus;

    ScopedPointer<MenuBarComponent> mnuBar;
    ScopedPointer<TabbedComponent> tabbox;
    
    ScopedPointer<FilesPane> filespane;
    ScopedPointer<AudioseqPane> audioseqpane;
    ScopedPointer<MidiPane> midipane;
    ScopedPointer<AudiobankPane> audiobankpane;

    int menuBarHeight;
    
    const static String helpText1, helpText2, helpText2b, helpText3;
    
    ScopedPointer<Yax0Codec> codec;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED

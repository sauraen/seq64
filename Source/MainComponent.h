/*
 * ============================================================================
 *
 * MainComponent.h
 * GUI component that holds the menus, tabs, etc. and performs menu functions
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

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "JuceHeader.h"
#include "seq64.h"
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
    MainComponent(SEQ64& seq64_, DocumentWindow& window_);
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
    void onGotABI();

private:
    SEQ64& seq64;
    DocumentWindow& window;
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

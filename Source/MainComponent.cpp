/*
 * ============================================================================
 *
 * MainComponent.cpp
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

#include "MainComponent.h"
#include "FilesPane.h"
#include "AudioseqPane.h"
#include "MidiPane.h"
#include "AudiobankPane.h"
#include "CICSetter.h"
#include "n64checksum.h"

//==============================================================================

MainComponent::MainComponent(SEQ64& seq64_, DocumentWindow& window_) : seq64(seq64_), window(window_)
{
    seq64.maincomponent = this;
    
    //Menus
    menuBarHeight = 24;
    
    PopupMenu* menu;
    PopupMenu* submenu;
    
    menunames.add("ROM");
    menu = new PopupMenu();
    menu->addItem(1, "Load...");
    menu->addSeparator();
    menu->addItem(4, "Byte Ordering...");
    menu->addSeparator();
    menu->addItem(2, "Save");
    menu->addItem(3, "Save As...");
    menus.add(menu);
    
    menunames.add("RomDesc");
    menu = new PopupMenu();
    menu->addItem(11, "Load...");
    menu->addSeparator();
    menu->addItem(12, "Save");
    menu->addItem(13, "Save As...");
    menus.add(menu);
    
    menunames.add("Tools");
    menu = new PopupMenu();
        submenu = new PopupMenu();
        submenu->addItem(61, "Decompress Yay0...");
        submenu->addItem(62, "Decompress Yaz0...");
        submenu->addSeparator();
        submenu->addItem(63, "Compress Yay0...");
        submenu->addItem(64, "Compress Yaz0...");
        submenus.add(submenu);
    menu->addSubMenu("Compression", *submenu);
    menus.add(menu);
    
    menunames.add("Help");
    menu = new PopupMenu();
    menu->addItem(91, "How do I even?");
    menu->addSeparator();
    menu->addItem(92, "Waaaah! Da thingy not working!");
    menu->addItem(93, "I can haz haxxorz?");
    menus.add(menu);
    
    mnuBar = new MenuBarComponent(this);
    addAndMakeVisible(*mnuBar);
    
    //Tabbed Panes
    filespane = new FilesPane(seq64);
    audioseqpane = new AudioseqPane(seq64);
    midipane = new MidiPane(seq64);
    audiobankpane = new AudiobankPane(seq64);
    
    tabbox = new TabbedComponent(TabbedButtonBar::TabsAtTop);
    tabbox->addTab("Files", Colours::white, &*filespane, false);
    tabbox->addTab("Audioseq", Colours::white, &*audioseqpane, false);
    tabbox->addTab("MIDI File", Colours::white, &*midipane, false);
    tabbox->addTab("Audiobank", Colours::white, &*audiobankpane, false);
    addAndMakeVisible(*tabbox);
    
    //Other
    setSize(1080, 768);
    
    onROMLoaded();
    onRomDescLoaded();
}

MainComponent::~MainComponent()
{
}

StringArray MainComponent::getMenuBarNames(){
    return menunames;
}
PopupMenu MainComponent::getMenuForIndex(int topLevelMenuIndex, const String &menuName){
    return *menus[topLevelMenuIndex];
}

void MainComponent::actuallySaveROM(){
    if(!romfile.hasWriteAccess()) return;
    UpdateCRC(seq64.rom);
    SEQ64::say("Saving 0x" + ROM::hex((uint32)seq64.rom.getSize())
            + " bytes to " + romfile.getFullPathName());
    if(!romfile.replaceWithData(seq64.rom.getData(), (int)seq64.rom.getSize())){
        SEQ64::say("Error: could not write file " + romfile.getFullPathName() + "!");
        return;
    }
    SEQ64::say("Successfully saved 0x" + ROM::hex((uint32)romfile.getSize()) + " bytes");
}
void MainComponent::actuallySaveRomDesc(){
    SEQ64::say("Saving XML ROM description parameters");
    ScopedPointer<XmlElement> xml;
    xml = seq64.romdesc.createXml();
    if(xml != nullptr){
        if(xml->writeToFile(romdescfile, "<!-- seq64 ROM Description File -->")){
            SEQ64::say("Successfully saved");
            return;
        }
    }
    SEQ64::say("Error: could not write file " + romdescfile.getFullPathName() + "!");
    return;
}

void MainComponent::menuItemSelected(int menuItemID, int topLevelMenuIndex){
    if(menuItemID == 1){
        //ROM::Load...
        FileChooser box("Select a ROM to load...", SEQ64::readFolderProperty("romfolder"), "*.z64;*.v64;*.n64");
        if(box.browseForFileToOpen()){
            romfile = box.getResult();
            if(!romfile.existsAsFile()){
                SEQ64::say("File " + romfile.getFullPathName() + " does not exist!");
                romfile = "";
                seq64.rom.reset();
                return;
            }
            //Save what folder you're in
            SEQ64::writeProperty("romfolder", romfile.getParentDirectory().getFullPathName());
            //Load ROM
            if(!seq64.loadROM(romfile)){
                romfile = File::nonexistent;
                return;
            }
            while(FindCIC(seq64.rom) < 0){
                int res = NativeMessageBox::showYesNoCancelBox(AlertWindow::WarningIcon,
                        "CRC Check", "ROM CRCs did not match according to any known CIC!\n"
                        "\n"
                        "Your options:\n"
                        "Click Yes: Select a different byte ordering, then check CRC again\n"
                        "Click No: Select CIC manually\n"
                        "Click Cancel: No change, but CIC will not be updated when ROM is saved", nullptr, nullptr);
                if(res == 1){
                    queryByteOrdering();
                }else if(res == 2){
                    DialogWindow::LaunchOptions cicbox;
                    cicbox.dialogTitle = "Set CIC";
                    cicbox.dialogBackgroundColour = Colours::lightgrey;
                    cicbox.content.setOwned(new CICSetter(seq64));
                    cicbox.resizable = false;
                    cicbox.launchAsync();
                    break;
                }else{
                    break;
                }
            }
            onROMLoaded();
        }
        return;
    }else if(menuItemID == 2){
        //ROM::Save
        if(seq64.rom.getSize() == 0){
            SEQ64::say("No ROM to save!");
            return;
        }
        if(!romfile.exists()){
            menuItemID = 3; //Save As instead!
        }else{
            if(!NativeMessageBox::showOkCancelBox(AlertWindow::WarningIcon,
                    "Overwrite?", "Save over " + romfile.getFileName() + "?", nullptr, nullptr)) return;
            actuallySaveROM();
            return;
        }
    }
    if(menuItemID == 3){
        //ROM::Save As...
        if(seq64.rom.getSize() == 0){
            SEQ64::say("No ROM to save!");
            return;
        }
        File newsavelocation = (romfile.exists() ? romfile : SEQ64::readFolderProperty("romfolder"));
        String extension;
        if(romfile.exists()){
            extension = romfile.getFileExtension();
        }else{
            switch(seq64.rom.byteOrdering){
                case ROM::ABCD: extension = ".z64"; break;
                case ROM::BADC: extension = ".n64"; break;
                case ROM::DCBA: extension = ".r64"; break;
                default: extension = ".rom"; break;
            }
        }
        FileChooser box("Save As", newsavelocation, "*" + extension);
        if(box.browseForFileToSave(true)){
            newsavelocation = box.getResult();
            if(!newsavelocation.hasWriteAccess()){
                SEQ64::say("Cannot write to " + newsavelocation.getFullPathName() + "!");
                return;
            }
            if(newsavelocation.getFileExtension() == ""){
                newsavelocation = newsavelocation.withFileExtension(extension);
            }
        }else{
            return;
        }
        romfile = newsavelocation;
        actuallySaveROM();
        return;
    }else if(menuItemID == 4){
        //ROM::Byte Ordering...
        queryByteOrdering();
        return;
    }else if(menuItemID == 11){
        //RomDesc::Load...
        FileChooser box("Select a ROM description file to load...", SEQ64::readFolderProperty("romdescfolder"), "*.xml");
        if(box.browseForFileToOpen()){
            romdescfile = box.getResult();
            if(!romdescfile.existsAsFile()){
                SEQ64::say("File " + romdescfile.getFullPathName() + " does not exist!");
                romdescfile = File::nonexistent;
                return;
            }
            //Save what folder you're in
            SEQ64::writeProperty("romdescfolder", romdescfile.getParentDirectory().getFullPathName());
            //Load XML
            if(!seq64.loadRomDesc(romdescfile)){
                romdescfile = File::nonexistent;
                return;
            }
            onRomDescLoaded();
            return;
        }
        return;
    }else if(menuItemID == 12){
        //RomDesc::Save
        if(romdescfile.exists()){
            actuallySaveRomDesc();
        }else{
            SEQ64::say("No file to save to!");
        }
        return;
    }else if(menuItemID == 13){
        //RomDesc::Save As...
        File newsavelocation = File::getSpecialLocation(File::userHomeDirectory);
        if(romdescfile.exists()){
            newsavelocation = romdescfile.getParentDirectory();
        }
        FileChooser box("Save As", newsavelocation, "*.xml");
        if(box.browseForFileToSave(true)){
            newsavelocation = box.getResult();
            if(!newsavelocation.hasWriteAccess()){
                SEQ64::say("Cannot write to " + newsavelocation.getFullPathName() + "!");
                return;
            }
            if(newsavelocation.getFileExtension() == ""){
                newsavelocation = newsavelocation.withFileExtension(".xml");
            }
            romdescfile = newsavelocation;
            actuallySaveRomDesc();
        }else{
            return;
        }
        return;
    }else if(menuItemID == 61){
        //Tools::Compression::Decompress Yay0...
        doCodecOperation(0);
        return;
    }else if(menuItemID == 62){
        //Tools::Compression::Decompress Yaz0...
        doCodecOperation(1);
        return;
    }else if(menuItemID == 63){
        //Tools::Compression::Compress Yay0...
        doCodecOperation(2);
        return;
    }else if(menuItemID == 64){
        //Tools::Compression::Compress Yaz0...
        doCodecOperation(3);
        return;
    }else if(menuItemID == 91){
        //Help::How do I even?
        NativeMessageBox::showMessageBox (AlertWindow::NoIcon, "Help Topics", helpText1);
        return;
    }else if(menuItemID == 92){
        //Help::Waaaah! Da thingy not working!
        int res = NativeMessageBox::showYesNoCancelBox(AlertWindow::QuestionIcon, "You called?", 
            "Are you REALLY sure the software is broken, and it's not just that you don't know how to use it?", nullptr, nullptr);
        if(res != 1){
            NativeMessageBox::showMessageBox (AlertWindow::InfoIcon, "n00b", 
                "Click Help > How do I even? for links to information about how to use seq64.");
        }else{
            
            NativeMessageBox::showMessageBox (AlertWindow::InfoIcon, "Report a Bug", 
                helpText2 
                + (char)('A'-1)
                  + (char)('j'-3)
                    + (char)('p'-3)
                      + (char)('h'-7)
                + (char)('m'-4)
                  + (char)('n'-2)
                    + (char)('.'-0)
                + (char)('i'-6)
                  + (char)('x'-9)
                    + (char)('s'-6)
                      + (char)(')'-9) 
                + helpText2b);
        }
        return;
    }else if(menuItemID == 93){
        //Help::I can haz haxxorz?
        NativeMessageBox::showMessageBox (AlertWindow::NoIcon, "About seq64", helpText3);
        return;
    }
    SEQ64::say("Bad menu item selected, " + String(menuItemID));
}

void MainComponent::queryByteOrdering(){
    if(!romfile.exists() || seq64.rom.getSize() == 0){
        SEQ64::say("No ROM loaded!");
        NativeMessageBox::showMessageBox (AlertWindow::InfoIcon, "Byte Ordering",
                "No ROM loaded!");
        return;
    }
    ROM::BYTEORDERING orig_order = seq64.rom.byteOrdering;
    String orig_order_name;
    switch(orig_order){
        case ROM::ABCD: orig_order_name = "ABCD"; break;
        case ROM::BADC: orig_order_name = "BADC"; break;
        case ROM::DCBA: orig_order_name = "DCBA"; break;
        default: orig_order_name = "ERROR"; jassertfalse;
    }
    String name_cur  = seq64.rom.getROMName();
    seq64.rom.byteOrdering = ROM::ABCD;
    String name_abcd = seq64.rom.getROMName();
    seq64.rom.byteOrdering = ROM::BADC;
    String name_badc = seq64.rom.getROMName();
    seq64.rom.byteOrdering = ROM::DCBA;
    String name_dcba = seq64.rom.getROMName();
    
    int res = NativeMessageBox::showYesNoCancelBox(AlertWindow::QuestionIcon, "Byte Ordering", 
            "To determine the correct byte ordering, select\n"
            "which option below looks like the correct ROM name.\n"
            "(Currently " + orig_order_name + " with name " + name_cur + ")\n"
            "\n"
            "Click 'Yes' for ABCD order: " + name_abcd + "\n"
            "Click 'No' for BADC order: " + name_badc + "\n"
            "Click 'Cancel' for DCBA order: " + name_dcba, nullptr, nullptr);
    
    String new_order_name;
    switch(res){
        case 1: seq64.rom.byteOrdering = ROM::ABCD; new_order_name = "ABCD"; break;
        case 2: seq64.rom.byteOrdering = ROM::BADC; new_order_name = "BADC"; break;
        case 0: seq64.rom.byteOrdering = ROM::DCBA; new_order_name = "DCBA"; break;
        default: jassertfalse; new_order_name = "ERROR";
    }
    if(orig_order != seq64.rom.byteOrdering){
        NativeMessageBox::showMessageBox(AlertWindow::InfoIcon, "Byte Ordering", 
                "Changed from " + orig_order_name + " to " + new_order_name + " byte ordering.");
        onROMLoaded();
    }
}

void MainComponent::doCodecOperation(int operation){
    String conv_desc, op_desc;
    switch(operation){
    case 0: conv_desc = "Yay0 compressed"; op_desc = "Decompressing from Yay0..."; break;
    case 1: conv_desc = "Yaz0 compressed"; op_desc = "Decompressing from Yaz0..."; break;
    case 2: conv_desc = "uncompressed"; op_desc = "Compressing as Yay0..."; break;
    case 3: conv_desc = "uncompressed"; op_desc = "Compressing as Yaz0..."; break;
    default: SEQ64::say("Error"); return;
    };
    FileChooser box("Choose input " + conv_desc + " file...", SEQ64::readFolderProperty("codecfolder"), "");
    if(!box.browseForFileToOpen()) return;
    File inputfile = box.getResult();
    if(!inputfile.existsAsFile()){
        SEQ64::say("File does not exist!");
        return;
    }
    SEQ64::writeProperty("codecfolder", inputfile.getParentDirectory().getFullPathName());
    codec = nullptr;
    codec = new Yax0Codec(operation, inputfile, conv_desc);
    codec->setStatusMessage(op_desc);
    codec->launchThread();
}

void MainComponent::paint (Graphics& g)
{
    
}

void MainComponent::resized()
{
    mnuBar->setBounds(0, 0, getWidth(), menuBarHeight);
    tabbox->setBounds(0, menuBarHeight, getWidth(), getHeight() - menuBarHeight);
}

void MainComponent::onROMLoaded(){
    window.setName(seq64.rom.getROMName() + "- seq64");
}
void MainComponent::onRomDescLoaded(){
    filespane->romDescLoaded();
    audiobankpane->romDescLoaded();
    audioseqpane->refreshCmdList();
    midipane->refreshMIDIControls();
    onGotABI();
}
void MainComponent::onSeqLoaded(){
    audioseqpane->fillSeqSections();
    audioseqpane->fillSeqCommands();
}
void MainComponent::onBankLoaded(){
    audiobankpane->bankLoaded();
}
void MainComponent::onGotABI(){
    audiobankpane->gotABI();
}

const String MainComponent::helpText1 = String(
    "We understand you might be confused. seq64 is a complex program\n"
    "and intends you to have some knowledge of n64 music and ROM\n"
    "hacking in general.\n"
    "\n"
    "There are resources available to help you get started with seq64.\n"
    "First is the online documentation at https://code.google.com/p/seq-64/w/list,\n"
    "which includes a Quick Start guide and some information about the file\n"
    "formats used in these games.\n"
    "\n"
    "The development thread is at http://www.romhacking.net/forum/index.php/topic,18891.0.html\n"
    "and gives some other information.\n"
    "\n"
    "If seq64 gives errors when using a RomDesc, check that the RomDesc\n"
    "is for the same version of the ROM that you're using, and that your ROM\n"
    "is decompressed (if applicable)."
);

const String MainComponent::helpText2 = String(
    "Post bug reports in the development thread at\n"
    "http://www.romhacking.net/forum/index.php/topic,18891.0.html\n"
    "or send Sauraen a private message at that forum\n"
    "or send Sauraen an email at sauraen"
);

const String MainComponent::helpText2b = String(
    ".\n"
    "\n"
    "Do NOT send or post links to ROMs, your message/post will be deleted.\n"
    "Do NOT ask me for sets of MIDIs exported from one of these games.\n"
    "I haven't made any--if you want to do the tedious work of extracting\n"
    "hundreds of songs one-by-one, not to mention changing the instruments\n"
    "so they are correct, be my guest."
);

const String MainComponent::helpText3 = String(
    "Yes! You CAN haz haxxorz.\n"
    "\n"
    "seq64 is licensed under the GNU General Public License version 3.0.\n"
    "This means you can distribute and modify it under certain conditions;\n"
    "see the license for details.\n"
    "\n"
    "seq64 - sequenced music editor for first-party N64 games\n"
    "Copyright (C) 2015 Sauraen; components under other copyrights\n"
    "(but all GPL licensed), see their source files for details.\n"
    "\n"
    "This program is free software: you can redistribute it and/or modify\n"
    "it under the terms of the GNU General Public License as published by\n"
    "the Free Software Foundation, either version 3 of the License, or\n"
    "(at your option) any later version.\n"
    "\n"
    "This program is distributed in the hope that it will be useful,\n"
    "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
    "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
    "GNU General Public License for more details.\n"
    "\n"
    "You should have received a copy of the GNU General Public License\n"
    "along with this program.  If not, see <http://www.gnu.org/licenses/>.\n"
);



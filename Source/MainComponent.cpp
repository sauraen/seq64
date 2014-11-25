/*
  ==============================================================================

    MainComponent.cpp
    Created: 13 Nov 2014 9:25:30am
    Author:  Sauraen

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "MainComponent.h"
#include "AppProps.h"
#include "FilesPane.h"
#include "AudioseqPane.h"
#include "AudiobankPane.h"

//==============================================================================

MainComponent::MainComponent(DocumentWindow& window_) : window(window_)
{
    p.maincomponent = this;
    
    //Menus
    menuBarHeight = 24;
    
    PopupMenu* menu;
    
    menunames.add("ROM");
    menu = new PopupMenu();
    menu->addItem(1, "Load...");
    menu->addSeparator();
    menu->addItem(4, "Byte-Swap");
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
    
    mnuBar = new MenuBarComponent(this);
    addAndMakeVisible(*mnuBar);
    
    //Tabbed Panes
    filespane = new FilesPane(p);
    audioseqpane = new AudioseqPane(p);
    audiobankpane = new AudiobankPane(p);
    
    tabbox = new TabbedComponent(TabbedButtonBar::TabsAtTop);
    tabbox->addTab("Files", Colours::white, &*filespane, false);
    tabbox->addTab("Audioseq", Colours::white, &*audioseqpane, false);
    tabbox->addTab("Audiobank", Colours::white, &*audiobankpane, false);
    addAndMakeVisible(*tabbox);
    
    //Other
    setSize(1300, 850);
        
    mainfolder = File(AppProps::readProperty("mainfolder"));
    DBG("Main folder " + mainfolder.getFullPathName());

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
    DBG("Saving 0x" + ROM::hex((uint32)p.rom.getSize())
            + " bytes to " + romfile.getFullPathName());
    if(!romfile.replaceWithData(p.rom.getData(), (int)p.rom.getSize())){
        DBG("Error: could not write file " + romfile.getFullPathName() + "!");
        return;
    }
    DBG("Successfully saved 0x" + ROM::hex((uint32)romfile.getSize()) + " bytes");
}
void MainComponent::actuallySaveRomDesc(){
    DBG("Saving XML ROM description parameters");
    ScopedPointer<XmlElement> xml;
    xml = p.romdesc.createXml();
    if(xml != nullptr){
        if(xml->writeToFile(romdescfile, "<!-- seq64 ROM Description File -->")){
            DBG("Successfully saved");
            return;
        }
    }
    DBG("Error: could not write file " + romdescfile.getFullPathName() + "!");
    return;
}

void MainComponent::menuItemSelected(int menuItemID, int topLevelMenuIndex){
    if(menuItemID == 1){
        //ROM::Load...
        File lastpath = File::getSpecialLocation(File::userHomeDirectory);
        if(mainfolder.exists()){
            lastpath = mainfolder;
        }
        FileChooser box("Select a ROM to load...", lastpath, "*.z64;*.v64");
        if(box.browseForFileToOpen()){
            romfile = box.getResult();
            if(!romfile.existsAsFile()){
                DBG("File " + romfile.getFullPathName() + " does not exist!");
                romfile = "";
                p.rom.reset();
                return;
            }
            //Save what folder you're in
            mainfolder = romfile.getParentDirectory();
            AppProps::writeProperty("mainfolder", mainfolder.getFullPathName());
            //Load ROM
            DBG("Loading 0x" + ROM::hex((uint32)romfile.getSize())
                    + " bytes from " + romfile.getFullPathName());
            p.rom.reset();
            if(!romfile.loadFileAsData(p.rom)){
                DBG("Error: could not load file " + romfile.getFullPathName() + "!");
                romfile = "";
                p.rom.reset();
                return;
            }
            if(romfile.getFileExtension() == ".v64"){
                p.rom.isByteSwapped = true;
                DBG("Interpreting .v64 file as byte-swapped (BADC order)");
            }else{
                p.rom.isByteSwapped = false;
                DBG("Interpreting .z64 file as not byte-swapped (ABCD order)");
            }
            DBG("Successfully loaded 0x" + ROM::hex((uint32)p.rom.getSize()) + " bytes");
            onROMLoaded();
        }
        return;
    }else if(menuItemID == 2){
        //ROM::Save
        if(p.rom.getSize() == 0){
            DBG("No ROM to save!");
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
        if(p.rom.getSize() == 0){
            DBG("No ROM to save!");
            return;
        }
        File newsavelocation = (romfile.exists() ? romfile : mainfolder);
        String extension = (p.rom.isByteSwapped ? ".v64" : ".z64");
        FileChooser box("Save As", newsavelocation, "*" + extension);
        if(box.browseForFileToSave(true)){
            newsavelocation = box.getResult();
            if(!newsavelocation.hasWriteAccess()){
                DBG("Cannot write to " + newsavelocation.getFullPathName() + "!");
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
        //Rom::ByteSwap
        if(!romfile.exists() || p.rom.getSize() == 0){
            DBG("No ROM loaded!");
            return;
        }
        p.rom.doByteSwap();
        romfile = File();
        if(p.rom.isByteSwapped){
            NativeMessageBox::showMessageBoxAsync (AlertWindow::InfoIcon, "Byte-Swap",
                    "Swapped from ABCD to BADC ordering.");
        }else{
            NativeMessageBox::showMessageBoxAsync (AlertWindow::InfoIcon, "Byte-Swap", 
                    "Swapped from BADC to ABCD ordering.");
        }
        return;
    }else if(menuItemID == 11){
        //RomDesc::Load...
        File lastpath = File::getSpecialLocation(File::userHomeDirectory);
        if(mainfolder.exists()){
            lastpath = mainfolder;
        }
        FileChooser box("Select a ROM description file to load...", lastpath, "*.xml");
        if(box.browseForFileToOpen()){
            romdescfile = box.getResult();
            if(!romdescfile.existsAsFile()){
                DBG("File " + romfile.getFullPathName() + " does not exist!");
                romdescfile = "";
                return;
            }
            //Save what folder you're in
            mainfolder = romdescfile.getParentDirectory();
            AppProps::writeProperty("mainfolder", mainfolder.getFullPathName());
            //Load XML
            DBG("Loading XML ROM description parameters");
            ScopedPointer<XmlElement> xml;
            xml = XmlDocument::parse(romdescfile);
            if(xml == nullptr){
                DBG("Error: could not load file " + romfile.getFullPathName() + "!");
                romdescfile = "";
                return;
            }
            p.romdesc = ValueTree::fromXml(*xml);
            DBG("Successfully loaded");
            onRomDescLoaded();
            return;
        }
        return;
    }else if(menuItemID == 12){
        //RomDesc::Save
        if(romdescfile.exists()){
            actuallySaveRomDesc();
        }else{
            DBG("No file to save to!");
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
                DBG("Cannot write to " + newsavelocation.getFullPathName() + "!");
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
    }
    DBG("Bad menu item selected, " + String(menuItemID));
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
    window.setName(p.rom.getROMName() + "- seq64");
}
void MainComponent::onRomDescLoaded(){
    filespane->romDescLoaded();
    audioseqpane->refreshCmdList();
    audioseqpane->refreshMIDIControls();
}
void MainComponent::onSeqLoaded(){
    audioseqpane->fillSeqSections();
    audioseqpane->fillSeqCommands();
}
void MainComponent::onBankLoaded(){
    
}

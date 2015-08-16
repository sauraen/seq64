/*
 * ============================================================================
 *
 * seq64.cpp
 * Application initialization and command-line interface for seq64
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

#include "seq64.h"
#include "MainComponent.h"
#include "SeqFile.h"
#include "BankFile.h"
#include "n64checksum.h"

void SEQ64::say(const String& text){
    std::cout << text.toRawUTF8() << "\n";
    /*fputs(text.toRawUTF8(), stdout);
    fputs("\n", stdout);
    fflush(stdout);*/
}

void SEQ64::writeProperty(Identifier name, String value){
    File appfolder = File::getSpecialLocation(File::userApplicationDataDirectory);
    appfolder = appfolder.getChildFile(".seq64");
    if(!appfolder.isDirectory()){
        appfolder.createDirectory();
    }
    File apppropsfile = appfolder.getChildFile("seq64.cfg");
    ScopedPointer<XmlElement> xml;
    ValueTree appprops("ApplicationProperties");
    if(apppropsfile.existsAsFile()){
        xml = XmlDocument::parse(apppropsfile);
        if(xml != nullptr){
            appprops = ValueTree::fromXml(*xml);
        }else{
            say("Invalid XML in " + apppropsfile.getFullPathName());
        }
    }
    appprops.setProperty(name, value, nullptr);
    xml = appprops.createXml();
    if(xml != nullptr){
        if(xml->writeToFile(apppropsfile, "<!-- Application Properties -->")){
            return;
        }
    }
    say("Error saving XML to " + apppropsfile.getFullPathName());
    return;
}

String SEQ64::readProperty(Identifier name){
    File appfolder = File::getSpecialLocation(File::userApplicationDataDirectory);
    appfolder = appfolder.getChildFile(".seq64");
    if(!appfolder.isDirectory()){
        return "";
    }
    File apppropsfile = appfolder.getChildFile("seq64.cfg");
    if(apppropsfile.existsAsFile()){
        ScopedPointer<XmlElement> xml;
        xml = XmlDocument::parse(apppropsfile);
        if(xml != nullptr){
            ValueTree appprops = ValueTree::fromXml(*xml);
            return appprops.getProperty(name, "");
        }else{
            say("Invalid XML in " + apppropsfile.getFullPathName());
            return "";
        }
    }
    return "";
}

File SEQ64::readFolderProperty(const String& name){
    String fpath = SEQ64::readProperty(name);
	File f = (fpath != "") ? File(fpath) : File::getSpecialLocation(File::userHomeDirectory);
	if(!f.isDirectory()) f = File::getSpecialLocation(File::userHomeDirectory);
	return f;
}

SEQ64::SEQ64() : rom(0, false), romdesc(Identifier("RomDesc")) {
    //do nothing
}

void SEQ64::initialise (const String& commandLine) {
    StringArray cmdparams = StringArray::fromTokens(commandLine, " \n", "\"\'");
    String rompath = String::empty, romdescpath = String::empty, outputpath = String::empty;
    int seqnumber = -1;
    bool forceoverwrite = false;
    String param;
    bool alldone = false;
    for(int i=0; i<cmdparams.size(); i++){
        param = cmdparams[i].unquoted();
        if(param.startsWithIgnoreCase("--rom=")){
            rompath = param.substring(6);
        }else if(param.startsWithIgnoreCase("-rom=")){
            rompath = param.substring(5);
        }else if(param.startsWithIgnoreCase("--romdesc=")){
            romdescpath = param.substring(10);
        }else if(param.startsWithIgnoreCase("-romdesc=")){
            romdescpath = param.substring(9);
        }else if(param.startsWithIgnoreCase("--export_midi=")){
            seqnumber = param.substring(14).getIntValue();
        }else if(param.startsWithIgnoreCase("-export_midi=")){
            seqnumber = param.substring(13).getIntValue();
        }else if(param.startsWithIgnoreCase("--output=")){
            outputpath = param.substring(9);
        }else if(param.startsWithIgnoreCase("-output=")){
            outputpath = param.substring(8);
        }else if(param.startsWithIgnoreCase("-f")){
            forceoverwrite = true;
        }else if(param.startsWithIgnoreCase("--force-overwrite")){
            forceoverwrite = true;
        }else{
            say("Unrecognized option " + param);
            alldone = true;
        }
    }
    if(alldone){
        say("seq64 command-line parameters:");
        say("--rom=<path_to_rom_file>");
        say("--romdesc=<path_to_romdesc_file>");
        say("--export_midi=<midi_number_to_export> (requires other three options)");
        say("--output=<path_to_exported_file>");
        say("(Above options may begin with 1 or 2 hyphens)");
        say("-f or --force-overwrite (overwrite existing output file)");
        quit();
        return;
    }
    //Check parameters
    romfile = File::getCurrentWorkingDirectory().getChildFile(rompath);
    romdescfile = File::getCurrentWorkingDirectory().getChildFile(romdescpath);
    File outputfile = File::getCurrentWorkingDirectory().getChildFile(outputpath);
    if(rompath != "" && !romfile.existsAsFile()){
        say("Could not find ROM file " + rompath);
        quit();
        return;
    }
    if(romdescpath != "" && !romdescfile.existsAsFile()){
        say("Could not find RomDesc file " + romdescpath);
        quit();
        return;
    }
    if(outputpath != ""){
        if(seqnumber >= 0 && outputfile.getFileExtension() == ""){
            outputfile = outputfile.withFileExtension(".mid");
        }
        if(outputfile.exists()){
            if(!forceoverwrite){
                say("Will not overwrite existing output file " + outputfile.getFullPathName());
                quit();
                return;
            }
        }else{
            Result r = outputfile.create();
            if(r.failed()){
                say("Could not create output file " + outputfile.getFullPathName());
                quit();
                return;
            }
        }
        outputfile.deleteFile();
        if(seqnumber < 0){
            say("Specified output file " + outputfile.getFullPathName() + ",");
            say("but nothing to output. Use --export_midi=<n>. Continuing...");
        }
    }
    if(seqnumber >= 0){
        if(rompath == ""){
            say("ROM path must be specified for command-line MIDI export!");
            quit();
            return;
        }
        if(romdescpath == ""){
            say("RomDesc path must be specified for command-line MIDI export!");
            quit();
            return;
        }
        if(outputpath == ""){
            say("Output file must be specified for command-line MIDI export!");
            quit();
            return;
        }
    }
    //Load ROM and RomDesc
    if(rompath != ""){
        if(!loadROM()){
            quit();
            return;
        }
        if(FindCIC(rom) < 0){
            say("ROM CICs did not match, wrong byte ordering or corrupted ROM");
            quit();
            return;
        }
    }
    if(romdescpath != ""){
        if(!loadRomDesc()){
            quit();
            return;
        }
    }
    if(seqnumber >= 0){
        seq = new SeqFile(romdesc);
        seq->load(rom, seqnumber);
        FileOutputStream fos(outputfile);
        ScopedPointer<MidiFile> midi;
        midi = seq->toMIDIFile();
        midi->writeTo(fos);
        fos.flush();
        SEQ64::say("Wrote MIDI file to " + outputfile.getFullPathName() + "!");
        quit();
        return;
    }
    
    mainWindow = new MainWindow(*this);
}

bool SEQ64::loadROM(){
    say("Loading 0x" + ROM::hex((uint32)romfile.getSize())
            + " bytes from " + romfile.getFullPathName());
    rom.reset();
    if(!romfile.loadFileAsData(rom)){
        say("Error: could not load file " + romfile.getFullPathName() + "!");
        rom.reset();
        return false;
    }
    String extension = romfile.getFileExtension();
    if(extension == ".n64" || extension == ".v64"){
        rom.byteOrdering = ROM::BADC;
        say("Interpreting " + extension + " file as BADC order");
    }else if(extension == ".r64"){
        rom.byteOrdering = ROM::DCBA;
        say("Interpreting " + extension + " file as DCBA order");
    }else{
        rom.byteOrdering = ROM::ABCD;
        say("Interpreting " + extension + " file as ABCD order");
    }
    say("Successfully loaded 0x" + ROM::hex((uint32)rom.getSize()) + " bytes");
    return true;
}

bool SEQ64::loadRomDesc(){
    say("Loading XML ROM description parameters (RomDesc)");
    ScopedPointer<XmlElement> xml;
    xml = XmlDocument::parse(romdescfile);
    if(xml == nullptr){
        say("Error: could not load file " + romdescfile.getFullPathName() + "!");
        return false;
    }
    romdesc = ValueTree::fromXml(*xml);
    say("Successfully loaded RomDesc");
    return true;
}

SEQ64::MainWindow::MainWindow(SEQ64& seq64) 
        : DocumentWindow ("MainWindow", Colours::lightgrey, DocumentWindow::allButtons){
    
    setContentOwned (new MainComponent(seq64, *this), true);
    centreWithSize (getWidth(), getHeight());
    setVisible (true);
}
void SEQ64::MainWindow::closeButtonPressed() {
    JUCEApplication::getInstance()->systemRequestedQuit();
}

    
    
START_JUCE_APPLICATION (SEQ64)

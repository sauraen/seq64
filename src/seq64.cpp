/*
 * ============================================================================
 *
 * seq64.cpp
 * Application initialization and command-line interface for seq64
 * 
 * From seq64 - Sequenced music editor for first-party N64 games
 * Copyright (C) 2014-2019 Sauraen
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
void SEQ64::sayNoNewline(const String& text){
    std::cout << text.toRawUTF8();
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
    std::unique_ptr<XmlElement> xml;
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
        std::unique_ptr<XmlElement> xml;
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
bool SEQ64::useNativeFileChooser(){
    Identifier idNFC = "usenativefilechooser";
    String prop = readProperty(idNFC);
    if(prop == ""){
#if (defined(JUCE_LINUX) || defined(JUCE_BSD))
            prop = "no";
#else
            prop = "yes";
#endif
        writeProperty(idNFC, prop);
    }
    return (prop == "yes");
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
    String rompath = "", romdescpath = "", outputpath = "";
    int seqnumber = -1;
    bool forceoverwrite = false, replacename = false, numberhex = false;
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
        }else if(param.startsWith("-ND")){
            replacename = true;
        }else if(param.startsWith("-NX")){
            replacename = true;
            numberhex = true;
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
        say("-ND (replace output MIDI name with sequence number (decimal) & name)");
        say("-NX (replace output MIDI name with sequence number (hex) & name)");
        quit();
        return;
    }
    //Check parameters
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
        if(outputpath == "" && !replacename){
            say("Output file must be specified for command-line MIDI export!");
            quit();
            return;
        }
    }
    romfile = File::getCurrentWorkingDirectory().getChildFile(rompath);
    romdescfile = File::getCurrentWorkingDirectory().getChildFile(romdescpath);
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
    //Load ROM and RomDesc
    if(rompath != ""){
        if(!loadROM()){
            quit();
            return;
        }
        if(rom.cic_index < 0){
            say("Warning, ROM CICs did not match, wrong byte ordering or corrupted ROM!");
            say("Saving the ROM may corrupt it further!");
        }
    }
    if(romdescpath != ""){
        if(!loadRomDesc()){
            quit();
            return;
        }
    }
    if(seqnumber >= 0){
        //Get sequence name
        ValueTree idxentry = romdesc.getChildWithName("audioseqidx").getChildWithProperty("index", seqnumber);
        String seqname("Unknown");
        if(idxentry.isValid()){
            seqname = idxentry.getProperty("name");
        }
        if(numberhex){
            seqname = ROM::hex((uint8)seqnumber) + " " + seqname;
        }else{
            seqname = String(seqnumber) + " " + seqname;
        }
        say("Sequence \"" + seqname + "\"");
        //Get file to write to
        File outputfile;
        if(outputpath == ""){
            outputfile = File::getCurrentWorkingDirectory().getChildFile(seqname + ".mid");
        }else if(replacename){
            outputfile = File(outputpath);
            if(outputfile.isDirectory()){
                outputfile = outputfile.getChildFile(seqname + ".mid");
            }else{
                outputfile = outputfile.getSiblingFile(seqname + ".mid");
            }
        }else{
            outputfile = File::getCurrentWorkingDirectory().getChildFile(outputpath);
            if(outputfile.getFileExtension() == ""){
                outputfile = outputfile.withFileExtension(".mid");
            }
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
        //Load sequence
        seq.reset(new SeqFile(romdesc));
        seq->load(rom, seqnumber);
        FileOutputStream fos(outputfile);
        std::unique_ptr<MidiFile> midi;
        midi.reset(seq->toMIDIFile(rom));
        midi->writeTo(fos);
        fos.flush();
        SEQ64::say("Wrote MIDI file to " + outputfile.getFullPathName() + "!");
        quit();
        return;
    }
    
    mainWindow.reset(new MainWindow(*this));
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
    if(extension == ".ndd" || extension == ".ndr"){
        say("Interpreting " + extension + " as N64DD image, no CIC/CRC");
        rom.cic_index = 0;
    }else{
        FindCIC(rom);
    }
    return true;
}

bool SEQ64::loadRomDesc(){
    say("Loading XML ROM description parameters (RomDesc)");
    std::unique_ptr<XmlElement> xml;
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

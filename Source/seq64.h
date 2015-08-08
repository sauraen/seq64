/*
 * ============================================================================
 *
 * seq64.h
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

#ifndef SEQ64_H_INCLUDED
#define SEQ64_H_INCLUDED

#include "JuceHeader.h"
#include "ROM.h"

class MainComponent;
class SeqFile;
class BankFile;

class SEQ64 : public JUCEApplication {
public:
    static void say(const String& text);
    static void writeProperty(Identifier name, String value);
    static String readProperty(Identifier name);
    static File readFolderProperty(const String& name);
    
    SEQ64();
    
    bool loadROM();
    bool loadRomDesc();

    const String getApplicationName() override { return ProjectInfo::projectName; }
    const String getApplicationVersion() override { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override { return true; }
    
    void shutdown() override { mainWindow = nullptr; }
    void systemRequestedQuit() override { quit(); }
    void anotherInstanceStarted (const String& commandLine) override {}

    void initialise (const String& commandLine) override;
    
    class MainWindow : public DocumentWindow {
    public:
        MainWindow(SEQ64& seq64);
        void closeButtonPressed() override;
    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
    };
    
    //Public fields
    ROM rom;
    ValueTree romdesc;
    File romfile;
    File romdescfile;
    ScopedPointer<SeqFile> seq;
    ScopedPointer<BankFile> bank;
    MainComponent* maincomponent;
    
private:
    ScopedPointer<MainWindow> mainWindow;
};


#endif  // SEQ64_H_INCLUDED

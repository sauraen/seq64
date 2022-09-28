/*
 * ============================================================================
 *
 * SeqFile.hpp
 * Class to hold/import/export a Nintendo 64 Music Macro Language (Audioseq) 
 * format sequence file
 * 
 * From seq64 - Sequenced music editor for first-party N64 games
 * Copyright (C) 2014-2021 Sauraen
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

#pragma once

#include "Common.hpp"

class SeqFile{
public:
    SeqFile(ValueTree abi_);
    ~SeqFile();
    
    static StringArray getAvailABIs();
    static ValueTree loadABI(String name);
    static bool saveABI(String name, ValueTree abi_);
    
    static bool isValidCC(int cc);
    
    //Results are 0 okay, 1 warnings, 2+ errors.
    int importMIDI(File midifile, ValueTree midiopts);
    int exportMIDI(File midifile, ValueTree midiopts);
    int importMus(File musfile, bool canon);
    int exportMus(File musfile, int dialect, bool sfxstyle);
    int importCom(File comfile);
    int exportCom(File comfile);
    
    String getInternalString();
    String getDebugOutput();
    
    String seqname;
    
private:
    //For all
    ValueTree abi;
    ValueTree structure;
    StringArray tsecnames;
    bool tsecnames_generated;
    int importresult;
    
    bool isCanon, oldCanon, isSfx;
    
    String debug_messages;
    CriticalSection debug_mutex;
    void dbgmsg(String s, bool newline = true);
    
    static const int max_layers;
    
    //For importMIDI
    void prefSetBool(ValueTree midiopts, Identifier opt, String value, String prefline);
    void prefSetInt(ValueTree midiopts, Identifier opt, int max, String value, String prefline);
    void prefSetHex(ValueTree midiopts, Identifier opt, int max, String value, String prefline);
    
    MidiMessageSequence* ensureSimulMsgsInOrder(MidiMessageSequence &in);
    
    void getCommandRange(ValueTree command, String meaning, int &range_min, int &range_max);
    int getLargestCommandRange(int stype, String action, String meaning);
    bool isCommandValidIn(ValueTree command, int stype);
    
    ValueTree wantAction(String action, int stype);
    void wantProperty(ValueTree want, String meaning, int value);
    ValueTree createCommand(ValueTree want, bool warnIfImpossible = true);
    void advanceToTimestamp(ValueTree section, int stype, int &cmd, int &t, int newt);
    ValueTree createMarker();
    int getNewCommandLength(ValueTree command); //For a command that was just created, not one read from an existing sequence
    
    bool isCloseEnough(ValueTree command1, ValueTree command2, bool allowCCMerge, ValueTree midiopts);
    int getTotalSectionTime(ValueTree section);
    void deleteSection(int sectodelete);
    void getExtendedCC(MidiMessage msg, int &cc, int &value);
    
    void optimize(ValueTree midiopts);
    void reduceTrackNotes();
    
    //For importMus
    struct MusLine {
        SeqFile *parent;
        String l;
        StringArray toks;
        String file;
        int linenum;
        bool used, dataforce2;
        MusLine(SeqFile *p, String l_, String file_, int linenum_) 
                : parent(p), l(l_), file(file_), linenum(linenum_), used(false),
                  dataforce2(false) {
            //Remove comments
            dataforce2 = l.contains("; FORCE LEN 2");
            l = l.upToFirstOccurrenceOf(";", false, false);
            l = l.upToFirstOccurrenceOf("//", false, false);
            l = l.trim();
            //TODO: will need to parse block/tsec names
        }
        void Tokenize(){
            if(l.isEmpty()) return;
            l = l.replace(",", " , ");
            l = l.replace(":", " : ");
            while(l.contains("+ ")) l = l.replace("+ ", "+");
            while(l.contains(" +")) l = l.replace(" +", "+");
            toks = StringArray::fromTokens(l, " \t", "");
            toks.trim();
            toks.removeEmptyStrings();
        }
        void Print() const{
            parent->dbgmsg("> " + file + " (" + String(linenum) + "): " + l);
        }
        void Info(String s) const{
            Print();
            parent->dbgmsg("  " + s);
        }
        void Warning(String s) const{
            Print();
            parent->dbgmsg("  Warning: " + s);
            parent->importresult |= 1;
        }
        ValueTree Error(String s) const{
            Print();
            parent->dbgmsg("  Error: " + s);
            parent->importresult |= 2;
            return ValueTree(); //optional to use in parseMusCommand
        }
    };
    
    enum ShortMode {
        SM_unspecified,
        SM_long,
        SM_short,
        SM_conflict
    };
    String GetShortModeLetter(ShortMode sm){
        switch(sm){
        case SM_unspecified: return "U";
        case SM_long:        return "L";
        case SM_short:       return "S";
        case SM_conflict:    return "C";
        default:             return "?";
        }
    }
    String GetShortModeDesc(ShortMode sm){
        switch(sm){
        case SM_unspecified: return "unspecified short/long notes";
        case SM_long:        return "long notes";
        case SM_short:       return "short notes";
        case SM_conflict:    return "conflicting short/long notes";
        default:             return "Error";
        }
    }
    
    struct FutureSection {
        String label;
        int stype;
        bool questionable;
        ShortMode shortmode;
    };
    StringPairArray altnames;
    
    static const StringArray sTypeNames;
    static const StringArray communitySTypeNames;

    String xl(Identifier base); //"Translate" base name to community or canon
    String xlspc(Identifier base); //Translate with canon unique spaces after
    void loadMusFileLines(OwnedArray<MusLine> &lines, String path, int insertIdx,
        MusLine *includeLine);
    bool parseCanonNoteName(String s, int &noteValue);
    bool isValidLabel(String s);
    bool isValidDefineKey(String s);
    bool isValidDefineValue(String s);
    void substituteDefines(const StringPairArray &defs, MusLine *line);
    bool getMusHex(String s, int &value);
    bool getMusInt(String s, int &value);
    int parseNormalParam(const MusLine *line, String s, String datasrc, 
        int datalen, bool allowNoteName = false,
        bool twoByteDelay = false, bool *dataforce2 = nullptr);
    ValueTree parseMusCommand(const MusLine *line, int stype, int dtstype,
        ShortMode shortmode, bool wrongSTypeErrors);
    void checkAddFutureSection(const MusLine *line, Array<FutureSection> &fs, 
        ValueTree section, ValueTree command, ShortMode shortmode);
    
    //For importMus and importCom
    
    struct DynTableSettings {
        int stype;
        ShortMode shortmode;
    };
    
    ValueTree createBlankSectionVT(int stype);
    void handleShortNoteChanges(ValueTree command, int stype, ShortMode &shortmode);
    ValueTree makeDynTableCommand(uint32_t address, var target, int dtstype, 
            int dtdynstype);
    ValueTree makeEnvelopeCommand(uint32_t address, int16_t rate, uint16_t level);
    ValueTree makeBasicDataCommand(uint32_t address, int value, 
            String datasrc, int datalen);
    void clearRecurVisited();
    bool findDynTableSettings(int dtsec, const StringArray &refs);
    DynTableSettings findNextDynTableSettings(int s, int c);
    bool getSectionAndCmd(ValueTree command, int &s, int &c);
    
    //For exportMus
    StringArray alllabelnames;
    void assignTSection(ValueTree sec, int tsecnum);
    int assignAllTSections();
    void generateTSecNames(int num_tsections, int dialect);
    String getSecNamePrefix(int dialect, ValueTree section);
    void registerExistingLabelName(ValueTree section);
    void setLabelNameAuto(ValueTree target, String name, String extra = "_");
    void nameSections(int dialect);
    void nameTargetCommands(int dialect);
    int countTicks(ValueTree sec, int starthash, int *lastdelay);
    String getCommandMusLine(int sec, ValueTree section, ValueTree command, 
        int dialect, int stype, int secticks);
    int findDynTableIndex(int sec);
    
    //For importCom
    ValueTree getDescription(uint8_t firstbyte, int stype, ShortMode shortmode);
    ValueTree getCommand(const Array<uint8_t> &data, uint32_t address, int stype, ShortMode shortmode);
    ValueTree initCommand(uint32_t address);
    ValueTree getDynTableCommand(const Array<uint8_t> &data, uint32_t address, ValueTree section);
    ValueTree getEnvelopeCommand(const Array<uint8_t> &data, uint32_t address);
    ValueTree getStringCommand(const Array<uint8_t> &data, uint32_t address, ValueTree section);
    ValueTree getOtherTableCommand(const Array<uint8_t> &data, uint32_t address);
    
    //<0: error, 1: section escape, 2: restart_parsing
    int checkRanIntoOtherSection(int parse_stype, int &parse_s, uint32_t &parse_addr, 
        ValueTree parse_cmd);
    //<0: error, 0: not found, 1: found
    int findTargetCommand(String action, uint32_t parse_addr, int tgt_addr, int tgt_stype, ValueTree parse_cmd);
    //<0: error, 0: okay
    int createSection(String src_action, int tgt_addr, int tgt_stype, ValueTree parse_cmd,
        ValueTree parse_section, bool forceContinue);
    
    int getPtrAddress(ValueTree command, uint32_t currentAddr, int seqlen);
    bool removeSection(int remove, int &replace, int hash, int cmdbyte);
    int actionTargetSType(String action, int stype, uint32_t a);
    void convertPtrsFirstCmd();
    bool findTableEnd(int s, const Array<uint8_t> &data);
    int parseComSection(int s, const Array<uint8_t> &data, Array<uint8_t> &datause,
        bool forceContinue);
    void parseTableSection(int s, const Array<uint8_t> &data, Array<uint8_t> &datause);
    bool findFirstUnusedData(const Array<uint8_t> &data, const Array<uint8_t> &datause, 
        int &start, int &end, bool &zeroes, bool &ismsg);
    bool checkUnusedIsAlign(int unusedstart, int unusedend, bool zeroes, 
        Array<uint8_t> &datause);
    void unusedToTableOrMsg(const Array<uint8_t> &data, Array<uint8_t> &datause,
        int unusedstart, int unusedend, bool zeroes, bool ismsg);
    
    struct SectionSorter {
        static int compareElements(const ValueTree &first, const ValueTree &second){
            int one = first.getProperty(idAddress, -1);
            int two = second.getProperty(idAddress, -1);
            jassert(one != two && one >= 0 && two >= 0);
            return one - two;
        }
    };

    //For exportCom
    void writeCommand(Array<uint8_t> &data, uint32_t address, ValueTree command);
    
    //Identifiers
    
    static Identifier idName;
    static Identifier idCName;
    static Identifier idOName;
    static Identifier idCmd;
    static Identifier idCmdEnd;
    static Identifier idAction;
    static Identifier idMeaning;
    static Identifier idValue;
    static Identifier idCC;
    static Identifier idLength;
    static Identifier idAddress;
    static Identifier idAddressEnd;
    static Identifier idDataSrc;
    static Identifier idDataLen;
    static Identifier idDataForce2;
    static Identifier idDataAddr;
    //static Identifier idDataActualLen;
    static Identifier idSType;
    static Identifier idValidInSeq;
    static Identifier idValidInChn;
    static Identifier idValidInTrk;
    static Identifier idChannel;
    static Identifier idLayer;
    static Identifier idShortMode;
    static Identifier idTSection;
    static Identifier idSection;
    static Identifier idSectionName;
    static Identifier idOldSectionIdx;
    static Identifier idSecDone;
    static Identifier idTicks;
    static Identifier idLastDelay;
    static Identifier idLabelName;
    static Identifier idLabelNameAuto;
    static Identifier idSrcCmdRef;
    static Identifier idHash;
    static Identifier idTargetSection;
    static Identifier idTargetHash;
    static Identifier idTargetCmdByte;
    static Identifier idTargetSType;
    static Identifier idWillDrop;
    static Identifier idDynTableSType;
    static Identifier idDynTableDynSType;
    //static Identifier idCurDynTableSec;
    static Identifier idMessage;
    static Identifier idRecurVisited;
    static Identifier idQuestionableSection;
    
    static Identifier idInclude;
    static Identifier idDefine;
    static Identifier idEntry;
    static Identifier idString;
    static Identifier idPad;
    static Identifier idu8;
    static Identifier idVariable;
    static Identifier idu16;
    static Identifier idAlign2;
    static Identifier idAlign16;
    static Identifier idLPrintOn;
    static Identifier idLPrintOff;
    static Identifier idBug;
    
};

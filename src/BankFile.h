/*
 * ============================================================================
 *
 * BankFile.h
 * Class to hold/import/export a single bank (Audiobank format)
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

#ifndef BANKFILE_H_INCLUDED
#define BANKFILE_H_INCLUDED

#include "JuceHeader.h"

class ROM;

class BankFile {
public:
    ValueTree d; //Data
    
    BankFile(ValueTree romdesc_);
    void reset();
    
    //Returns number of bytes read/written, -1 on error
    int readStruct(ROM& rom, uint32 addr, ValueTree stru); //stru has been just copied from the template
    int getStructLength(ValueTree stru);
    int writeStruct(ROM& rom, uint32 addr, ValueTree stru);
    
    ValueTree getCopyOfTemplate(String name);
    bool loadElementList(ROM& rom, uint32 baseaddr, uint32 bank_length, String listname, String elementname);
    void checkAddListItem(ValueTree list, int addressval, ValueTree node);
    ValueTree getListForPointer(String pointertype);
    
    bool load(ROM& rom, int banknum);
    int save(ROM& rom, int banknum);
    bool loadXML(File xmlfile);
    bool saveXML(File xmlfile);
    
    void loadRDNamesNode(int banknum);
    void clearRDNamesNode();
    void copyRDItemPropsToItem(String listname, int itemindex, ValueTree dest);
    void copyItemPropsToRDItem(String listname, int itemindex, ValueTree source);
    
    //For nodes within d
    class NodeValueInfo{
    public:
        String value;
        String valueequiv;
        bool valueeditable;
        bool valuereference;
        NodeValueInfo(){
            value = valueequiv = "";
            valueeditable = valuereference = false;
        }
    };
    enum NodeListFlags{
        canAdd = 1,
        canDupl = 2,
        canDel = 4,
        canMove = 8
    };
    static String getFieldDesc(ValueTree field, bool cformatting);
    String getNodeDesc(ValueTree node);
    String getNodeName(ValueTree node);
    bool isNodeNameEditable(ValueTree node);
    bool setNodeName(ValueTree node, String name);
    String getNodeType(ValueTree node);
    NodeValueInfo getNodeValueInfo(ValueTree node, bool hex);
    bool setNodeValue(ValueTree node, String input, bool hex);
    int getNodeListFlags(ValueTree nodein, ValueTree nodeselected); //see NodeListInfo above
    String getNodePath(ValueTree node);
    ValueTree getNodeChild(ValueTree node, int childidx);
    ValueTree getNodeParent(ValueTree node);
    bool addNode(ValueTree parent);
    bool duplicateNode(ValueTree parent, ValueTree child);
    bool deleteNode(ValueTree parent, ValueTree child);
    bool moveNodeUp(ValueTree parent, ValueTree child);
    bool moveNodeDown(ValueTree parent, ValueTree child);
    
    ValueTree importNode(ROM& rom, BankFile& sourcebank, String itemtype, int itemindex, 
            bool merge, bool fixsampleaddr);
    
private:
    ValueTree romdesc;
    ValueTree abfstructsnode;
    ValueTree rdnamesnode;
    
    //Audiobank Index Entry Properties
    class ABIEProps{
    public:
        uint32 abiaddr;
        uint32 abfaddr;
        uint32 abientryaddr;
        uint32 ptr_bank;
        uint32 bank_length;
        uint16 bank_count;
        bool valid;
        ValueTree abiestru;
        ABIEProps(){
            abiaddr = abfaddr = abientryaddr = 0;
            ptr_bank = bank_length = 0;
            bank_count = 0;
            valid = false;
            abiestru = ValueTree();
        }
    };
    ABIEProps getABIEProps(ROM& rom, int banknum);
    
    static bool isMeaningDeterminedAtImport(String meaning);
    static void swapReferences(ValueTree parent, String pointername, int swapFrom, int swapTo);
    static void insertReferences(ValueTree parent, String pointername, int index);
    static void deleteReferences(ValueTree parent, String pointername, int index);
    static bool deepCompareItems(String itemtype, BankFile& banka, int itemindexa, 
            BankFile& bankb, int itemindexb);
    static bool deepCompareNodes(BankFile& banka, ValueTree nodea, 
            BankFile& bankb, ValueTree nodeb);
    static bool compareProperty(ValueTree nodea, ValueTree nodeb, String name);
    ValueTree importNodeRecurse(ROM& rom, BankFile& sourcebank, bool merge, bool fixsampleaddr,
            ValueTree sourcenode, ValueTree destparent);
    void getAllStructLengths(String pointertype, uint32* a, int align);
    void setAllReferencesAddress(ValueTree parent, String pointername, int index, uint32 address);
    bool validatePointerIndexes(ValueTree node);
    void fixAllStructImportValues(ValueTree parent);
    void writeAllItems(ROM& bank, ValueTree parent, uint32* a, int align);
    void copyAllItemProps(String listname);
    
};



#endif  // BANKFILE_H_INCLUDED

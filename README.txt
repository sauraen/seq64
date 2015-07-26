seq64 - Sequenced music editor for first-party N64 games.
Created by and Copyright (C) 2015 Sauraen, sauraen@gmail.com
Licensed under the GNU General Public License - see LICENSE.txt
Made using Juce Cross-Platform C++ Library (free for GPL use) - http://www.juce.com/

SEQ64 is a full-featured editor for sequenced music in first-party Nintendo 64 games.

Click the Wiki tab for more information. Click Source > Browse and find the "bin" folder to download, or compile from source.

Features:

- Full MIDI import/export of sequences in Audioseq format
- User-editable definition of Audioseq format
- Edit sequence data directly (e.g. to add commands not supported by MIDI)
- Edit and tag Audiobank instrument definitions
- User-editable definition of Audiobank format
- Move files in ROM while maintaining system integrity
- Seamlessly recalculates CRC/CIC upon saving ROM
- Supports all versions of games that use similar sequence formats
- All ROM description data saved in human-editable format
- Supports all three ROM bytes orderings
- Yay0/Yaz0 compressor/decompressor tool
- Mature, comprehensible GUI
- GPL licensed, cross-platform (Juce C++, full-speed on Windows, Mac, Linux) 

Current project state:

- MIDI export complete
- MIDI import mostly complete, some bugs with call-based optimization
- Editing which instrument set(s) are used with each sequence is complete
- Audiobank parsing in progress 

Available versions:

- 32-bit Windows (compiled and tested on Windows 7)
- 64-bit Windows (compiled and tested on Windows 7)
- 64-bit Linux (compiled and tested on Ubuntu 14.04) 

Games known to use sequenced music formats compatible with SEQ64:

- Super Mario 64 (+)
- Mario Kart 64 (+)
- Yoshi's Story (+)
- Legend of Zelda: Ocarina of Time: v1.0 (+)(*), Debug ROM (+)
- Legend of Zelda: Majora's Mask (+)(*)
- 1080 Snowboarding
- F-ZERO X
- Lylat Wars
- Pokemon Stadium
- Pokemon Stadium 2
- Wave Race 64

(+: RomDesc included) (*: Relevant data is stored in compressed format; must be decompressed before use) 


Tips/How To:

I recommend running seq64 from a terminal, lots of useful information is 
printed!

If you already have a ROM and ROM Description File (RomDesc), load each from 
their respective menus and some of the lists should start filling in. Keep in 
mind that some of the RomDescs provided here are for the uncompressed versions
of the games; data may be at different places in compressed ROMs.

If you don't have an existing RomDesc for the game, the first step is to find 
the addresses of the Audioseq file (the first sequence) and of the Audioseq 
Index (a list of pointers to sequences). If a file table is present, you can 
use the file table to help locate these items; if not, you can enter their 
addresses manually. These are both "Known Files" (i.e. files that seq64 knows 
how to handle).

Click on your Audioseq Index entry in the Known Files list to show its contents 
in the index list. You can rename sequences (all properties like this are stored
in the RomDesc file). Click Load Sequence to load it from the ROM. Go to the 
Audioseq tab to work with the loaded sequence.

If you're starting working with a new game, start making a RomDesc for it, then
save it and open it in a text editor. Copy the whole "cmdlist" node from an
existing RomDesc so you have a starting point for the file format. Make sure you
get the XML right! (At least it's human-readable!)

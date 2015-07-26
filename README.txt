seq64 - Sequenced music editor for first-party N64 games.
Created by and Copyright (C) 2015 Sauraen, sauraen@gmail.com
Licensed under the GNU General Public License - see LICENSE.txt
Made using Juce Cross-Platform C++ Library (free for GPL use) - http://www.juce.com/

Contents:
---------
- Pre-built executables in bin folder for 32-bit Windows and 64-bit Linux (built
 on Ubuntu 14.04 LTS 64-bit, if it doesn't work download Juce and build it
  yourself!)
- Some sample ROM Description Files in the romdesc folder
- Source code and Juce project files

What's Working:
---------------
- ROM and RomDesc loading and saving (works directly on ABCD and BADC byte
  ordering, with option to actually perform the swap)
- Definition of Audioseq format
- Loading sequence files from ROM according to table; viewing sequence data
- Exporting loaded sequence as MIDI

Coming Soon:
------------
- Importing MIDI to loaded sequence
- Editing sequence commands
- Saving sequence to ROM (without overwriting other data!)
- Editing/tagging Audiobank files so MIDIs are imported/exported with the 
  correct instruments

Tips/How To:
------------
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

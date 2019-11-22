/*
 * ============================================================================
 * 
 * Yaz0 / Yay0 Compression/Decompression Algorithms
 * 
 * Code (C) 2014-2019 Sauraen, released in seq64
 *     (https://github.com/sauraen/seq64/)
 * Heavily based on documentation and code (C) 2005 thakis
 *     (http://www.amnoid.de/gc/)
 * and documentation and code (C) 2005 shevious
 *     (http://www.amnoid.de/gc/, shevious@yahoo.com)
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

#include "yaz0_yay0.h"
#include "ROM.h"

//Functions for Yax0Codec runner class
Yax0Codec::Yax0Codec(int operation, File infile, String cv_desc) 
        : ThreadWithProgressWindow("seq64", true, true), 
        op(operation), inputfile(infile), conv_desc(cv_desc){}
void Yax0Codec::run(){
    std::unique_ptr<ROM> in;
    in.reset(new ROM(0, false));
    if(!inputfile.loadFileAsData(*in)){
        SEQ64::say("Error: could not load file " + inputfile.getFullPathName() + "!");
        return;
    }
    SEQ64::say("Loaded " + String((int)in->getSize()) + " bytes");
    switch(op){
    case 0: out.reset(yay0_decompress(*in, 0, in->getSize())); break;
    case 1: out.reset(yaz0_decompress(*in, 0, in->getSize())); break;
    case 2: out.reset(yay0_compress(*in, 0, in->getSize())); break;
    case 3: out.reset(yaz0_compress(*in, 0, in->getSize())); break;
    }
}
void Yax0Codec::threadComplete(bool userPressedCancel){
    if(userPressedCancel){
        NativeMessageBox::showMessageBox (AlertWindow::WarningIcon, "seq64", 
                "Operation cancelled.");
        return;
    }
    if(out == nullptr){
        NativeMessageBox::showMessageBox (AlertWindow::WarningIcon, "seq64", 
                "File could not be read as " + conv_desc + " data.");
        return;
    }
    File outputfile = inputfile.getSiblingFile(
            inputfile.getFileNameWithoutExtension() + "_out" + inputfile.getFileExtension());
    FileChooser box2("Success! Save result as...", outputfile, "", SEQ64::useNativeFileChooser());
    if(!box2.browseForFileToSave(true)) return;
    outputfile = box2.getResult();
    if(!outputfile.hasWriteAccess()){
        SEQ64::say("Cannot write to " + outputfile.getFullPathName() + "!");
        return;
    }
    if(!outputfile.replaceWithData(out->getData(), (int)out->getSize())){
        SEQ64::say("Error: could not write file " + outputfile.getFullPathName() + "!");
        return;
    }
    SEQ64::say("Successfully saved 0x" + ROM::hex((uint32)outputfile.getSize()) + " bytes");
}


/**
 * Decompresses a block of data compressed with Yay0.
 * Returns: a new block of data that is the decompressed data, or nullptr
 * if the decompression failed. Put this into a std::unique_ptr<ROM>.
 * Parameters:
 *   - input: A block of data containing the original data.
 *   - inputaddress: The address within input at which the Yay0 block starts.
 *   - inputlength: The expected length of the Yay0 block (compressed). In all cases,
 *     the parsing will stop when the decompressed data is filled. If the input
 *     length is known, put the length, and if the parsing reads past this length, the
 *     decompression fails. No error if the input does not fill up the inputlength,
 *     as the block can be padded with 0s (or anything else). If the input length is
 *     unknown, put -1.
 * In all cases all length parameters will be checked against the total
 * size of the input, to prevent segfaults.
 */
ROM* Yax0Codec::yay0_decompress(ROM& input, int inputaddress, int inputlength){
    //Check parameters of input
    int inputsize = input.getSize();
    if(inputaddress + 17 >= inputsize){
        SEQ64::say("yay0_decompress: Input address is out of bounds on input data!");
        return nullptr;
    }
    if(inputaddress + inputlength > inputsize){
        SEQ64::say("yay0_decompress: Input length runs off the end of input data!");
        return nullptr;
    }
    int cmdaddr, cmdend, countaddr, countend, dataaddr, dataend;
    int outputlength, outputaddr = 0;
    uint8 cmd; int cmd_counter;
    uint8 count1, count2, count3;
    int comp_offset, comp_count;
    //Read header
    const uint32 Yay0 = 'Y'<<24 | 'a'<<16 | 'y'<<8 | '0';
    if(input.readWord(inputaddress) != Yay0){
        SEQ64::say("yay0_decompress: Data is not Yay0 format (illegal header)!");
        return nullptr;
    }
    outputlength = input.readWord(inputaddress+4);
    cmdaddr = inputaddress + 16;
    countaddr = inputaddress + input.readWord(inputaddress+8);
    cmdend = countaddr;
    dataaddr = inputaddress + input.readWord(inputaddress+12);
    countend = dataaddr;
    dataend = (inputlength >= 0) ? (inputaddress + inputlength) : inputsize;
    //Check header parameters
    if(        outputlength == 0 
            || countaddr >= inputsize 
            || dataaddr >= inputsize 
            || countaddr >= dataaddr
            || cmdaddr >= countaddr 
            || cmdaddr >= dataaddr){
        SEQ64::say("yay0_decompress: Invalid header parameters!");
        return nullptr;
    }
    //Create return data
    ROM* output = new ROM(outputlength, true);
    //Start decompression
    cmd_counter = 0;
    while(true){
        if(threadShouldExit()){
            SEQ64::say("yay0_decompress: Asked to stop decompression");
            break;
        }
        if(cmd_counter == 0){
            if(cmdaddr >= cmdend){
                SEQ64::say("yay0_decompress: Commands ran off end!");
                break;
            }
            cmd = input.readByte(cmdaddr++);
            cmd_counter = 7;
        }else{
            cmd <<= 1;
            cmd_counter--;
        }
        //Determine read mode
        if(cmd & 0x80){
            //Copy input byte to output
            //Check that we're not reading off the end of input data 
            if(dataaddr >= dataend){
                SEQ64::say("yay0_decompress: Data ran off end!");
                break;
            }
            //Write byte
            output->writeByte(outputaddr++, input.readByte(dataaddr++));
        }else{
            //Copy specific data from output to output
            if(countaddr+1 >= countend){
                SEQ64::say("yay0_decompress: Counts (2 byte) ran off end!");
                break;
            }
            count1 = input.readByte(countaddr++);
            count2 = input.readByte(countaddr++);
            //Create comp_count
            if(!(count1 & 0xF0)){
                //Read a third byte
                if(countaddr >= countend){
                    SEQ64::say("yay0_decompress: Counts (3 byte) ran off end!");
                    break;
                }
                count3 = input.readByte(countaddr++);
                comp_count = (int)count3 + 0x12;
            }else{
                comp_count = (count1 >> 4) + 2;
            }
            //Create comp_offset
            comp_offset = (count1 & 0x0F);
            comp_offset = ((comp_offset << 8) | count2) + 1;
            //Check to make sure we can read this many bytes
            if(comp_offset > outputaddr){
                SEQ64::say("yay0_decompress: Tried to read from before beginning of output!");
                break;
            }
            //Check to make sure we can write this many bytes
            if(outputaddr + comp_count > outputlength){
                SEQ64::say("yay0_decompress: Tried to write past end of output!");
                break;
            }
            //Copy data
            comp_offset = outputaddr - comp_offset;
            for(; comp_count >= 1; comp_count--){
                output->writeByte(outputaddr++, output->readByte(comp_offset++));
            }
        }
        setProgress((double)outputaddr / (double)outputlength);
        //Check if we filled up the output
        if(outputaddr == outputlength){
            SEQ64::say("yay0_decompress: Success");
            return output;
        }
    }
    //Error occurred
    delete output;
    return nullptr;
}

/**
 * Decompresses a block of data compressed with Yaz0.
 * Returns: a new block of data that is the decompressed data, or nullptr
 * if the decompression failed. Put this into a std::unique_ptr<ROM>.
 * Parameters:
 *   - input: A block of data containing the original data.
 *   - inputaddress: The address within input at which the Yaz0 block starts.
 *   - inputlength: The expected length of the Yaz0 block (compressed). In all cases,
 *     the parsing will stop when the decompressed data is filled. If the input
 *     length is known, put the length, and if the parsing reads past this length, the
 *     decompression fails. No error if the input does not fill up the inputlength,
 *     as the block can be padded with 0s (or anything else). If the input length is
 *     unknown, put -1.
 * In all cases all length parameters will be checked against the total
 * size of the input, to prevent segfaults.
 */
ROM* Yax0Codec::yaz0_decompress(ROM& input, int inputaddress, int inputlength){
    //Check parameters of input
    int inputsize = input.getSize();
    if(inputaddress + 17 >= inputsize){
        SEQ64::say("yaz0_decompress: Input address is out of bounds on input data!");
        return nullptr;
    }
    if(inputaddress + inputlength > inputsize){
        SEQ64::say("yaz0_decompress: Input length runs off the end of input data!");
        return nullptr;
    }
    int dataaddr, dataend;
    int outputlength, outputaddr = 0;
    uint8 cmd; int cmd_counter;
    uint8 count1, count2, count3;
    int comp_offset, comp_count;
    //Read header
    const uint32 Yaz0 = 'Y'<<24 | 'a'<<16 | 'z'<<8 | '0';
    if(input.readWord(inputaddress) != Yaz0
            || input.readWord(inputaddress+8) != 0
            || input.readWord(inputaddress+12) != 0){
        SEQ64::say("yaz0_decompress: Data is not Yaz0 format (illegal header)!");
        return nullptr;
    }
    outputlength = input.readWord(inputaddress+4);
    dataaddr = inputaddress + 16;
    dataend = (inputlength >= 0) ? (inputaddress + inputlength) : inputsize;
    //Check header parameters
    if(outputlength == 0){
        SEQ64::say("yaz0_decompress: Invalid header parameters!");
        return nullptr;
    }
    //Create return data
    ROM* output = new ROM(outputlength, true);
    //Start decompression
    cmd_counter = 0;
    while(true){
        if(threadShouldExit()){
            SEQ64::say("yaz0_decompress: Asked to stop decompression");
            break;
        }
        if(cmd_counter == 0){
            if(dataaddr >= dataend){
                SEQ64::say("yaz0_decompress: Input ran off end when reading command!");
                break;
            }
            cmd = input.readByte(dataaddr++);
            cmd_counter = 7;
        }else{
            cmd <<= 1;
            cmd_counter--;
        }
        //Determine read mode
        if(cmd & 0x80){
            //Copy input byte to output
            //Check that we're not reading off the end of input data 
            if(dataaddr >= dataend){
                SEQ64::say("yaz0_decompress: Input ran off end when reading data!");
                break;
            }
            //Write byte
            output->writeByte(outputaddr++, input.readByte(dataaddr++));
        }else{
            //Copy specific data from output to output
            if(dataaddr+1 >= dataend){
                SEQ64::say("yaz0_decompress: Input ran off end when reading counts (2 byte)!");
                break;
            }
            count1 = input.readByte(dataaddr++);
            count2 = input.readByte(dataaddr++);
            //Create comp_count
            if(!(count1 & 0xF0)){
                //Read a third byte
                if(dataaddr >= dataend){
                    SEQ64::say("yaz0_decompress: Input ran off end when reading counts (3 byte)!");
                    break;
                }
                count3 = input.readByte(dataaddr++);
                comp_count = (int)count3 + 0x12;
            }else{
                comp_count = (count1 >> 4) + 2;
            }
            //Create comp_offset
            comp_offset = (count1 & 0x0F);
            comp_offset = ((comp_offset << 8) | count2) + 1;
            //Check to make sure we can read this many bytes
            if(comp_offset > outputaddr){
                SEQ64::say("yaz0_decompress: Tried to read from before beginning of output!");
                break;
            }
            //Check to make sure we can write this many bytes
            if(outputaddr + comp_count > outputlength){
                SEQ64::say("yaz0_decompress: Tried to write past end of output!");
                break;
            }
            //Copy data
            comp_offset = outputaddr - comp_offset;
            for(; comp_count >= 1; comp_count--){
                output->writeByte(outputaddr++, output->readByte(comp_offset++));
            }
        }
        setProgress((double)outputaddr / (double)outputlength);
        //Check if we filled up the output
        if(outputaddr == outputlength){
            SEQ64::say("yaz0_decompress: Success");
            return output;
        }
    }
    //Error occurred
    delete output;
    return nullptr;
}

typedef struct{
    int16 count;
    int16 dist;
} yax0_result;

/**
 * For internal use of yay0_compress and yaz0_compress.
 */
yax0_result yax0_kernel(ROM& input, int position, int lowbound, int upbound){
    //Find the longest string (in bounds) earlier in input that is identical to that at position.
    yax0_result res;
    res.count = 2; //Don't take anything less than 2 long
    res.dist = 0;
    if(lowbound > position || upbound < position){
        SEQ64::say("yax0_kernel bounds error");
        return res;
    }
    int lookback, lookforward;
    if(position - 0x1000 > lowbound){
        lowbound = position - 0x1000;
    }
    upbound = (0x111 < upbound - position) ? 0x111 : (upbound - position);
    for(lookback=position-1; lookback>=lowbound; lookback--){
        for(lookforward=0; lookforward<upbound; lookforward++){
            if(input.readByte(lookback+lookforward) != input.readByte(position+lookforward)){
                break;
            }
        }
        if(lookforward > res.count){
            res.count = lookforward;
            res.dist = position-lookback-1;
            if(lookforward == upbound){
                //Not going to do any better
                break;
            }
        }
    }
    return res;
}

/**
 * Compresses a block of data with Yay0.
 * Returns: a new block of data that is the compressed data, or nullptr
 * if the compression failed. Put this into a std::unique_ptr<ROM>.
 * Parameters:
 *   - input: A block of data containing the original data.
 *   - inputaddress: The address within input at which the original data starts.
 *   - inputlength: The length of the data to compress.
 * In all cases all length parameters will be checked against the total
 * size of the input, to prevent segfaults.
 * 
 * There is no guarantee that the compressed data will be shorter than
 * the uncompressed data; and also, keep in mind that compression is MUCH
 * slower than decompression. There's a lot of brute-force searching.
 */
ROM* Yax0Codec::yay0_compress(ROM& input, int inputaddress, int inputlength){
    //Check parameters of input
    int inputsize = input.getSize();
    int upbound = inputaddress + inputlength;
    if(inputaddress >= inputsize){
        SEQ64::say("yay0_compress: Input address is out of bounds on input data!");
        return nullptr;
    }
    if(upbound > inputsize){
        SEQ64::say("yay0_compress: Input length runs off the end of input data!");
        return nullptr;
    }
    //Create arrays
    Array<uint8> commands;
    Array<uint8> counts;
    Array<uint8> data;
    //Create variables
    int a = inputaddress;
    uint8 count1, count2, count3;
    uint8 cmd; int cmd_counter;
    yax0_result simpleres, lookaheadres;
    //Start compression
    cmd_counter = 7; cmd = 0;
    while(a < upbound){
        if(threadShouldExit()){
            SEQ64::say("yay0_compress: Asked to stop decompression");
            break;
        }
        simpleres = yax0_kernel(input, a, inputaddress, upbound);
        if(simpleres.count <= 2){
            //No match, just copy one byte
            data.add(input.readByte(a));
            cmd |= (1 << cmd_counter);
            if(cmd_counter == 0){
                commands.add(cmd);
                cmd = 0;
                cmd_counter = 7;
            }else{
                cmd_counter--;
            }
            a++;
        }else{
            //Compare to lookahead result
            lookaheadres = yax0_kernel(input, a+1, inputaddress, upbound);
            if(lookaheadres.count >= simpleres.count + 2){
                //Lookahead result is better
                //Copy one byte
                data.add(input.readByte(a));
                cmd |= (1 << cmd_counter);
                if(cmd_counter == 0){
                    commands.add(cmd);
                    cmd = 0;
                    cmd_counter = 7;
                }else{
                    cmd_counter--;
                }
                a++;
                //Continue with simple result
                simpleres.count = lookaheadres.count;
                simpleres.dist = lookaheadres.dist;
            }
            //Write copy command
            count1 = (simpleres.dist >> 8) & 0x0F;
            count2 = simpleres.dist & 0xFF;
            if(simpleres.count < 0x12){
                count1 |= (simpleres.count - 0x02) << 4;
            }else{
                count3 = simpleres.count - 0x12;
            }
            counts.add(count1);
            counts.add(count2);
            if(simpleres.count >= 0x12) counts.add(count3);
            if(cmd_counter == 0){
                commands.add(cmd);
                cmd = 0;
                cmd_counter = 7;
            }else{
                cmd_counter--;
            }
            a += simpleres.count;
        }
        setProgress((double)(a - inputaddress) / (double)inputlength);
    }
    //Finish command
    if(cmd_counter <= 6){
        //Partially completed command needs to be added
        for(; cmd_counter >= 0; cmd_counter--){
            cmd |= (1 << cmd_counter); //Write "copy single byte" commands
        }
        commands.add(cmd);
    }
    //Produce output memory block
    int outputlength = 0x10 + commands.size() + counts.size() + data.size();
    ROM* output = new ROM(outputlength, true);
    const uint32 Yay0 = 'Y'<<24 | 'a'<<16 | 'y'<<8 | '0';
    output->writeWord(0x0, Yay0);
    output->writeWord(0x4, inputlength);
    output->writeWord(0x8, 0x10 + commands.size());
    output->writeWord(0xC, 0x10 + commands.size() + counts.size());
    a = 0x10;
    for(int i=0; i<commands.size(); i++){
        output->writeByte(a++, commands[i]);
    }
    for(int i=0; i<counts.size(); i++){
        output->writeByte(a++, counts[i]);
    }
    for(int i=0; i<data.size(); i++){
        output->writeByte(a++, data[i]);
    }
    SEQ64::say("yay0_compress: success");
    return output;
}

/**
 * Compresses a block of data with Yaz0.
 * Returns: a new block of data that is the compressed data, or nullptr
 * if the compression failed. Put this into a std::unique_ptr<ROM>.
 * Parameters:
 *   - input: A block of data containing the original data.
 *   - inputaddress: The address within input at which the original data starts.
 *   - inputlength: The length of the data to compress.
 * In all cases all length parameters will be checked against the total
 * size of the input, to prevent segfaults.
 * 
 * There is no guarantee that the compressed data will be shorter than
 * the uncompressed data; and also, keep in mind that compression is MUCH
 * slower than decompression. There's a lot of brute-force searching.
 */
ROM* Yax0Codec::yaz0_compress(ROM& input, int inputaddress, int inputlength){
    //Check parameters of input
    int inputsize = input.getSize();
    int upbound = inputaddress + inputlength;
    if(inputaddress >= inputsize){
        SEQ64::say("yaz0_compress: Input address is out of bounds on input data!");
        return nullptr;
    }
    if(upbound > inputsize){
        SEQ64::say("yaz0_compress: Input length runs off the end of input data!");
        return nullptr;
    }
    //Create array
    Array<uint8> data;
    //Create variables
    int a = inputaddress;
    uint8 count1, count2, count3;
    uint8 cmd; int cmd_counter; int cmd_address; bool just_added_cmd;
    yax0_result simpleres, lookaheadres;
    //Start compression
    cmd_counter = 7; cmd = 0; cmd_address = 0;
    data.add(0); just_added_cmd = true; //Space for first command
    while(a < upbound){
        if(threadShouldExit()){
            SEQ64::say("yaz0_compress: Asked to stop decompression");
            break;
        }
        simpleres = yax0_kernel(input, a, inputaddress, upbound);
        if(simpleres.count <= 2){
            //No match, just copy one byte
            data.add(input.readByte(a)); just_added_cmd = false;
            cmd |= (1 << cmd_counter);
            if(cmd_counter == 0){
                data.set(cmd_address, cmd); //Write now-complete command
                cmd_address = data.size();
                data.add(0); just_added_cmd = true; //Make room for new one
                cmd = 0;
                cmd_counter = 7;
            }else{
                cmd_counter--;
            }
            a++;
        }else{
            //Compare to lookahead result
            lookaheadres = yax0_kernel(input, a+1, inputaddress, upbound);
            if(lookaheadres.count >= simpleres.count + 2){
                //Lookahead result is better
                //Copy one byte
                data.add(input.readByte(a)); just_added_cmd = false;
                cmd |= (1 << cmd_counter);
                if(cmd_counter == 0){
                    data.set(cmd_address, cmd); //Write now-complete command
                    cmd_address = data.size();
                    data.add(0); just_added_cmd = true; //Make room for new one
                    cmd = 0;
                    cmd_counter = 7;
                }else{
                    cmd_counter--;
                }
                a++;
                //Continue with simple result
                simpleres.count = lookaheadres.count;
                simpleres.dist = lookaheadres.dist;
            }
            //Write copy command
            count1 = (simpleres.dist >> 8) & 0x0F;
            count2 = simpleres.dist & 0xFF;
            if(simpleres.count < 0x12){
                count1 |= (simpleres.count - 0x02) << 4;
            }else{
                count3 = simpleres.count - 0x12;
            }
            data.add(count1);
            data.add(count2);
            if(simpleres.count >= 0x12) data.add(count3);
            just_added_cmd = false;
            if(cmd_counter == 0){
                data.set(cmd_address, cmd); //Write now-complete command
                cmd_address = data.size();
                data.add(0); just_added_cmd = true; //Make room for new one
                cmd = 0;
                cmd_counter = 7;
            }else{
                cmd_counter--;
            }
            a += simpleres.count;
        }
        setProgress((double)(a - inputaddress) / (double)inputlength);
    }
    //Finish command
    if(just_added_cmd){
        //Remove last (empty command) byte
        data.remove(data.size() - 1);
    }else{
        for(; cmd_counter >= 0; cmd_counter--){
            cmd |= (1 << cmd_counter); //Write "copy single byte" commands
        }
        data.set(cmd_address, cmd);
    }
    //Produce output memory block
    int outputlength = 0x10 + data.size();
    ROM* output = new ROM(outputlength, true);
    const uint32 Yaz0 = 'Y'<<24 | 'a'<<16 | 'z'<<8 | '0';
    output->writeWord(0x0, Yaz0);
    output->writeWord(0x4, inputlength);
    output->writeWord(0x8, 0);
    output->writeWord(0xC, 0);
    a = 0x10;
    for(int i=0; i<data.size(); i++){
        output->writeByte(a++, data[i]);
    }
    SEQ64::say("yaz0_compress: success");
    return output;
}

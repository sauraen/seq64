/*
 * ============================================================================
 * 
 * Yaz0 / Yay0 Compression/Decompression Algorithms
 * 
 * Code (C) 2017 Sauraen, released in seq64
 *     (http://code.google.com/p/seq-64/)
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

#ifndef YAZ0_YAY0_H_INCLUDED
#define YAZ0_YAY0_H_INCLUDED

#include "JuceHeader.h"
#include "seq64.h"

class ROM;

class Yax0Codec : public ThreadWithProgressWindow {
public:
    Yax0Codec(int operation, File infile, String cv_desc);
    void run() override;
    void threadComplete(bool userPressedCancel) override;
    
    ROM* yay0_decompress(ROM& input, int inputaddress, int inputlength);
    ROM* yaz0_decompress(ROM& input, int inputaddress, int inputlength);

    ROM* yay0_compress(ROM& input, int inputaddress, int inputlength);
    ROM* yaz0_compress(ROM& input, int inputaddress, int inputlength);

private:
    int op;
    ScopedPointer<ROM> out;
    File inputfile;
    String conv_desc;
};



#endif  // YAZ0_YAY0_H_INCLUDED

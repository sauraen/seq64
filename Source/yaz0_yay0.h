/*
 * See yaz0_yay0.cpp for header information.
 */

#ifndef YAZ0_YAY0_H_INCLUDED
#define YAZ0_YAY0_H_INCLUDED

#include "ROM.h"

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

/*
  ==============================================================================

    AppProps.h
    Created: 1 Nov 2014 11:03:37pm
    Author:  Sauraen

  ==============================================================================
*/

#ifndef APPPROPS_H_INCLUDED
#define APPPROPS_H_INCLUDED

#include "JuceHeader.h"
#include "ROM.h"
#include "SeqFile.h"

class MainComponent;

class AppProps{
    public:
    
    static void writeProperty(Identifier name, String value);
    static String readProperty(Identifier name);
    
    AppProps();
    
    ROM rom;
    ValueTree romdesc;
    ScopedPointer<SeqFile> seq;
    MainComponent* maincomponent;
    //BankFile bank;
};



#endif  // APPPROPS_H_INCLUDED

/*
  ==============================================================================

    AppProps.cpp
    Created: 1 Nov 2014 11:03:37pm
    Author:  Sauraen

  ==============================================================================
*/

#include "AppProps.h"
#include "JuceHeader.h"

void AppProps::writeProperty(Identifier name, String value){
    File appfolder = File::getSpecialLocation(File::userApplicationDataDirectory);
    appfolder = appfolder.getChildFile(".seq64");
    if(!appfolder.isDirectory()){
        appfolder.createDirectory();
    }
    File apppropsfile = appfolder.getChildFile("seq64.cfg");
    ScopedPointer<XmlElement> xml;
    ValueTree appprops("ApplicationProperties");
    if(apppropsfile.existsAsFile()){
        xml = XmlDocument::parse(apppropsfile);
        if(xml != nullptr){
            appprops = ValueTree::fromXml(*xml);
        }else{
            DBG("Invalid XML in " + apppropsfile.getFullPathName());
        }
    }
    appprops.setProperty(name, value, nullptr);
    xml = appprops.createXml();
    if(xml != nullptr){
        if(xml->writeToFile(apppropsfile, "<!-- Application Properties -->")){
            return;
        }
    }
    DBG("Error saving XML to " + apppropsfile.getFullPathName());
    return;
}
String AppProps::readProperty(Identifier name){
    File appfolder = File::getSpecialLocation(File::userApplicationDataDirectory);
    appfolder = appfolder.getChildFile(".seq64");
    if(!appfolder.isDirectory()){
        return "";
    }
    File apppropsfile = appfolder.getChildFile("seq64.cfg");
    if(apppropsfile.existsAsFile()){
        ScopedPointer<XmlElement> xml;
        xml = XmlDocument::parse(apppropsfile);
        if(xml != nullptr){
            ValueTree appprops = ValueTree::fromXml(*xml);
            return appprops.getProperty(name, "");
        }else{
            DBG("Invalid XML in " + apppropsfile.getFullPathName());
            return "";
        }
    }
    return "";
}

AppProps::AppProps() : romdesc(Identifier("RomDesc")){
    //do nothing
}

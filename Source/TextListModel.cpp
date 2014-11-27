/*
  ==============================================================================

    TextListModel.cpp
    Created: 31 Oct 2014 10:00:34pm
    Author:  Sauraen

  ==============================================================================
*/

#include "JuceHeader.h"
#include "TextListModel.h"

TextListModel::TextListModel() : font(15){
    
}
TextListModel::~TextListModel(){
    
}

void TextListModel::add(String s){
    strings.add(s);
}
void TextListModel::insert(int i, String s){
    strings.insert(i, s);
}
void TextListModel::remove(int i){
    strings.remove(i);
}
void TextListModel::clear(){
    strings.clear();
}
String TextListModel::get(int i){
    return strings[i];
}
void TextListModel::set(int i, String s){
    strings.set(i, s);
}

int TextListModel::getNumRows(){
    return strings.size();
}
void TextListModel::paintListBoxItem(int rowNumber, Graphics &g, int width, int height, bool rowIsSelected){
    if(rowNumber >= strings.size()) return;
    if(rowIsSelected){
        g.setColour(Colours::lightblue);
    }else{
        g.setColour(Colours::white);
    }
    g.fillRect(0, 0, width, height);
    g.setColour(Colours::black);
    g.setFont(font);
    g.drawText(strings[rowNumber], 4, 0, width, height, Justification::left, true);
}

void TextListModel::selectedRowsChanged(int lastRowSelected){
    if(listener != nullptr){
        listener->rowSelected(this, lastRowSelected);
    }
}

void TextListModel::setListener(Listener* l){
    listener = l;
}
void TextListModel::setFont(Font newfont){
    font = newfont;
}
    

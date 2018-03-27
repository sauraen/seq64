/*
 * ============================================================================
 *
 * TextListModel.cpp
 * A ListBoxModel subclass that makes a standard list box of strings
 * 
 * From seq64 - Sequenced music editor for first-party N64 games
 * Copyright (C) 2014-2018 Sauraen
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

#include "TextListModel.h"

void TextListModel::Listener::rowDoubleClicked(TextListModel* parent, int row){}

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

void TextListModel::listBoxItemDoubleClicked(int row, const MouseEvent& e){
    if(listener != nullptr){
        listener->rowDoubleClicked(this, row);
    }
}

void TextListModel::setListener(Listener* l){
    listener = l;
}
void TextListModel::setFont(Font newfont){
    font = newfont;
}
    

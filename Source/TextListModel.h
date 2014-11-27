/*
  ==============================================================================

    TextListModel.h
    Created: 14 Nov 2014 5:49:00pm
    Author:  Sauraen

  ==============================================================================
*/

#ifndef TEXTLISTMODEL_H_INCLUDED
#define TEXTLISTMODEL_H_INCLUDED

class TextListModel : public ListBoxModel {
    public:
    class Listener{
        public:
        virtual void rowSelected(TextListModel* parent, int row)=0;
    };
    
    TextListModel();
    ~TextListModel();
    
    void add(String s);
    void insert(int i, String s);
    void remove(int i);
    void clear();
    String get(int i);
    void set(int i, String s);
    
    int getNumRows();
    void paintListBoxItem(int rowNumber, Graphics &g, int width, int height, bool rowIsSelected);
    
    void selectedRowsChanged(int lastRowSelected);
    
    void setListener(Listener* l);
    void setFont(Font newfont);
    
    private:
    StringArray strings;
    Listener* listener;
    Font font;
};



#endif  // TEXTLISTMODEL_H_INCLUDED

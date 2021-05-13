#ifndef LISTBOXWIDGET_H
#define LISTBOXWIDGET_H

#include "Widget.h"
#include <vector>
#include <string>


class ListBoxWidget : public Widget
{
public:
    ListBoxWidget() : Widget()
    {
        //widgettype = (char*) "ListBox";
        strcpy( widgettype, (char*) "ListBox");
    };
    ListBoxWidget( char *l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : Widget( l, x, y, w, h, p )
    {
        //widgettype = (char*) "ListBox";
        strcpy( widgettype, (char*) "ListBox");
    };

    virtual ~ListBoxWidget()
    {
        /*
        std::vector<std::string>::iterator it1;
        while (listitems.size()!=0)
        {
            it1 = listitems.begin();
            listitems.erase( it1 );
        }
        */

        listitems.clear();

    };

    virtual void flush()
    {
       /*std::vector<std::string>::iterator it1;
        while (listitems.size()!=0)
        {
            it1 = listitems.begin();
            listitems.erase( it1 );
        }
        */

        listitems.clear();

        nbitem = 0;
        selected = 0;
        scroll = 0;
        nbvisible = 0;
    };

    virtual bool ispressed();

    virtual void logic( CursorTask *mouse, KeyboardTask *keyboard ) override;

    virtual void render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts ) override;

    virtual void additem( char *item )
    {
        listitems.push_back( std::string(item) );
        nbitem++;
    };

    virtual unsigned int getnbitem()
    {
        return listitems.size();
    };

    virtual char* getitem( int itemnumber )
    {
        return (char*)  listitems[itemnumber].c_str();
    };

    virtual int getselected()
    {
        return selected;
    };

    virtual char* getselecteditem()
    {
        return (char*) listitems[selected].c_str();
    };

    bool validated = false;
    bool escaped = false;

protected:

    unsigned int nbitem = 0;
    std::vector<std::string> listitems;
    unsigned int selected = 0;


private:
    unsigned int scroll = 0;
    unsigned int nbvisible = 0;
    unsigned int heightline = 0;
    bool is_pressed = false;
};

#endif // LISTBOXWIDGET_H

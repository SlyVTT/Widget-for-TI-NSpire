#ifndef LISTBOXWIDGET_H
#define LISTBOXWIDGET_H

#include "Widget.h"
#include <vector>
#include <string>


class ListBoxWidget : public Widget
{
public:
    ListBoxWidget();
    ListBoxWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p );
    virtual ~ListBoxWidget();

    virtual void flush();
    virtual bool ispressed();

    virtual void logic( CursorTask *mouse, KeyboardTask *keyboard ) override;
    virtual void render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts ) override;

    virtual void additem( std::string item );
    virtual unsigned int getnbitem();
    virtual std::string getitem( int itemnumber );
    virtual int getselected();
    virtual std::string getselecteditem();

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

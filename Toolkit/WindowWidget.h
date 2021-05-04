#ifndef WINDOWWIDGET_H
#define WINDOWWIDGET_H

#include "Widget.h"


class WindowWidget : public Widget
{
public:
    WindowWidget( )
    {
        //widgettype = (char*) "Window";
        strcpy( widgettype, (char*) "Window");
    };
    WindowWidget( char *l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : Widget( l, x, y, w, h, p )
    {
        //widgettype = (char*) "Window";
        strcpy( widgettype, (char*) "Window");
        xposback = x;
        yposback = y;
        widthback = w;
        heightback = h;
    };
    virtual ~WindowWidget() { };

    virtual void logic( CursorTask *mouse, KeyboardTask *keyboard ) override;

    virtual void render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts ) override;

    virtual void maximize();
    virtual void minimize();
    virtual void restore();

    virtual void setminimaldimensions( unsigned int widmin, unsigned int heimin)
    {
        minwidth = widmin;
        minheight = heimin;
    };

    virtual void setmenubar()
    {
        hasmenubar = true;
    };
    virtual void seticonbar()
    {
        hasiconbar = true;
    };
    virtual bool getmenubar()
    {
        return hasmenubar;
    };
    virtual bool geticonbar()
    {
        return hasiconbar;
    };

    // These methods must be override cause window geometry is a bit different with the title bar
    virtual unsigned int getuseablexpos() override;
    virtual unsigned int getuseableypos() override;
    virtual unsigned int getuseablewidth() override;
    virtual unsigned int getuseableheight() override;

protected:
    //virtual bool cursoron( CursorTask *mouse ) override;
    bool is_developped = true;

    virtual bool ismouseatleftborder(CursorTask *mouse);
    virtual bool ismouseatrightborder(CursorTask *mouse);
    virtual bool ismouseattopborder(CursorTask *mouse);
    virtual bool ismouseatbottomborder(CursorTask *mouse);
    virtual bool ismouseontitlebar(CursorTask *mouse);
    virtual bool ismouseonmaximisebutton(CursorTask *mouse);
    virtual bool ismouseonminimisebutton(CursorTask *mouse);
    virtual bool ismouseonrestorebutton(CursorTask *mouse);

    bool hasmenubar=false;
    bool hasiconbar=false;

    int clickX = 0;
    int clickY = 0;

    bool resizemode = false;
    bool movemode = false;
    bool startmove = false;

    bool isminimized = false;
    bool ismaximized = false;

    unsigned int xposback = 0;
    unsigned int yposback = 0;
    unsigned int widthback = 0;
    unsigned int heightback = 0;

    unsigned int minwidth;
    unsigned int minheight;

};

#endif // WINDOWWIDGET_H

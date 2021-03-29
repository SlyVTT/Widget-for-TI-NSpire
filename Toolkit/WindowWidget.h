#ifndef WINDOWWIDGET_H
#define WINDOWWIDGET_H

#include "Widget.h"


class WindowWidget : public Widget
{
public:
    WindowWidget( )
    {
        widgettype = (char*) "Window";
    };
    WindowWidget( char *l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : Widget( l, x, y, w, h, p )
    {
        widgettype = (char*) "Window";
    };
    virtual ~WindowWidget() { };

    virtual void logic( CursorTask *mouse, KeyboardTask *keyboard ) override;

    virtual void render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts ) override;


    // These methods must be override cause window geometry is a bit different with the title bar
    virtual unsigned int getuseablexpos() override;
    virtual unsigned int getuseableypos() override;
    virtual unsigned int getuseablewidth() override;
    virtual unsigned int getuseableheight() override;

protected:
    //virtual bool cursoron( CursorTask *mouse ) override;
    bool is_developped = true;

private:
    virtual bool ismouseatleftborder(CursorTask *mouse);
    virtual bool ismouseatrightborder(CursorTask *mouse);
    virtual bool ismouseattopborder(CursorTask *mouse);
    virtual bool ismouseatbottomborder(CursorTask *mouse);
    virtual bool ismouseontitlebar(CursorTask *mouse);

    unsigned int clickX;
    unsigned int clickY;

    bool resizemode = false;
    bool movemode = false;
    bool startmove = false;
};

#endif // WINDOWWIDGET_H

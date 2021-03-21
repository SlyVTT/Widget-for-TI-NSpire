#ifndef FRAMEWIDGET_H
#define FRAMEWIDGET_H

#include "Widget.h"


class FrameWidget : public Widget
{
public:
    FrameWidget()
    {
        widgettype = (char*) "Frame";
    };
    FrameWidget( char *l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : Widget( l, x, y, w, h, p )
    {
        widgettype = (char*) "Frame";
    };
    ~FrameWidget() { };


    virtual void logic( CursorTask *mouse, KeyboardTask *keyboard ) override;
    virtual void render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts ) override;

    // These methods must be override cause frame geometry is a bit different with the title bar
    virtual unsigned int getuseablexpos() override;
    virtual unsigned int getuseableypos() override;
    virtual unsigned int getuseablewidth() override;
    virtual unsigned int getuseableheight() override;

protected:
    bool is_pressed = false;

private:
};

#endif // FRAMEWIDGET_H

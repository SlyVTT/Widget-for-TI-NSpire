#ifndef FRAMEWIDGET_H
#define FRAMEWIDGET_H

#include "Widget.h"


class FrameWidget : public Widget
{
    public:
        FrameWidget() { widgettype = "Frame"; };
        FrameWidget( char *l, int x, int y, int w, int h, Widget *p ) : Widget( l, x, y, w, h, p ) { widgettype = "Frame"; };
        ~FrameWidget() { };


        virtual void logic( CursorTask *mouse, KeyboardTask *keyboard ) override;
        virtual void render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts ) override;

        // These methods must be override cause frame geometry is a bit different with the title bar
        virtual int getuseablexpos() override;
        virtual int getuseableypos() override;
        virtual int getuseablewidth() override;
        virtual int getuseableheight() override;

    protected:
        bool is_pressed = false;

    private:
};

#endif // FRAMEWIDGET_H

#ifndef FRAMEWIDGET_H
#define FRAMEWIDGET_H

#include "Widget.h"


class FrameWidget : public Widget
{
    public:
        FrameWidget() { widgettype = "Frame"; };
        FrameWidget( char *l, int x, int y, int w, int h, Widget *p ) : Widget( l, x, y, w, h, p ) {};
        ~FrameWidget() { };


        virtual void logic( CursorTask *mouse, KeyboardTask *keyboard ) override;
        virtual void render( SDL_Surface *screen, nSDL_Font *currentfont ) override;

    protected:
        bool is_pressed = false;

    private:
};

#endif // FRAMEWIDGET_H

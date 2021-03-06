#ifndef WINDOWWIDGET_H
#define WINDOWWIDGET_H

#include "Widget.h"


class WindowWidget : public Widget
{
    public:
        WindowWidget( ) { widgettype = "Window"; };
        WindowWidget( char *l, int x, int y, int w, int h, Widget *p ) : Widget( l, x, y, w, h, p ) { widgettype = "Window"; };
        virtual ~WindowWidget() { };


        virtual void logic( CursorTask *mouse, KeyboardTask *keyboard ) override;
        virtual void render( SDL_Surface *screen, nSDL_Font *currentfont ) override;

    protected:
        //virtual bool cursoron( CursorTask *mouse ) override;
        bool is_developped = true;


};

#endif // WINDOWWIDGET_H

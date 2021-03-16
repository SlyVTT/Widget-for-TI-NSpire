#ifndef BUTTONWIDGET_H
#define BUTTONWIDGET_H

#include "Widget.h"


class ButtonWidget : public Widget
{
    public:
        ButtonWidget() { widgettype = (char*) "Button"; };
        ButtonWidget( char *l, int x, int y, int w, int h, Widget *p ) : Widget( l, x, y, w, h, p ) { widgettype = (char*) "Button"; };
        ~ButtonWidget() {};

        virtual bool ispressed();
        virtual void logic( CursorTask *mouse, KeyboardTask *keyboard ) override;
        virtual void render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts ) override;

    protected:
        bool is_pressed = false;

    private:
};

#endif // BUTTONWIDGET_H

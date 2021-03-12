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
        virtual void render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts ) override;


        // These methods must be override cause window geometry is a bit different with the title bar
        virtual int getuseablexpos() override;
        virtual int getuseableypos() override;
        virtual int getuseablewidth() override;
        virtual int getuseableheight() override;

    protected:
        //virtual bool cursoron( CursorTask *mouse ) override;
        bool is_developped = true;


};

#endif // WINDOWWIDGET_H

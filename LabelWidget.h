#ifndef LABELWIDGET_H
#define LABELWIDGET_H

#include "Widget.h"


enum align
{
    centered = 0,
    left = 1,
    right = 2
};


class LabelWidget : public Widget
{
    public:
        LabelWidget() { widgettype = "Label"; };
        LabelWidget( char *l, int x, int y, int w, int h, Widget *p ) : Widget( l, x, y, w, h, p ) { widgettype = "Label"; };
        virtual ~LabelWidget() { };

        virtual void logic( CursorTask *mouse, KeyboardTask *keyboard ) override;
        virtual void render( SDL_Surface *screen, nSDL_Font *currentfont ) override;

        virtual void setalignment( align type ) { alignment = type; };
        virtual align getalignement() { return alignment; };

    protected:
        bool is_pressed = false;
        align alignment = centered;

    private:
};

#endif // LABELWIDGET_H

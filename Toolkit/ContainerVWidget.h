#ifndef CONTAINERVWIDGET_H
#define CONTAINERVWIDGET_H

#include "Widget.h"


class ContainerVWidget : public Widget
{
    public:
        ContainerVWidget() { widgettype = "ContainerV"; };
        ContainerVWidget( char *l, int x, int y, int w, int h, Widget *p ) : Widget( l, x, y, w, h, p ) { widgettype = "ContainerV"; };
        virtual ~ContainerVWidget() { };

        virtual void adjust() override;

        virtual int getsize() { return nbchildren; };

        virtual void logic( CursorTask *mouse, KeyboardTask *keyboard ) override;
        virtual void render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts ) override;

    protected:
//        int sizevgrid;
  //      std::vector<Widget*> gridvwidget;


    private:
};

#endif// CONTAINERVWIDGET_H

#ifndef CONTAINERHWIDGET_H
#define CONTAINERHWIDGET_H

#include "Widget.h"


class ContainerHWidget : public Widget
{
    public:
        ContainerHWidget() { widgettype = (char*) "ContainerH"; };
        ContainerHWidget( char *l, int x, int y, int w, int h, Widget *p ) : Widget( l, x, y, w, h, p ) { widgettype = (char*) "ContainerH"; };
        virtual ~ContainerHWidget() { };

        virtual void adjust() override;

        virtual int getsize() { return nbchildren; };

        virtual void logic( CursorTask *mouse, KeyboardTask *keyboard ) override;
        virtual void render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts ) override;

    protected:
//        int sizehgrid;
//        std::vector<Widget*> gridhwidget;


    private:
};

#endif // CONTAINERHWIDGET_H

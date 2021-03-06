#ifndef DESKTOPWIDGET_H
#define DESKTOPWIDGET_H

#include "Widget.h"


class DesktopWidget : public Widget
{
    public:
        DesktopWidget() { widgettype = "Desktop"; };
        DesktopWidget( char *l, int x, int y, int w, int h, Widget *p ) : Widget( l, x, y, w, h, p ) { widgettype = "Desktop"; };
        virtual ~DesktopWidget() { };

        virtual void logic( CursorTask *mouse, KeyboardTask *keyboard ) override;
        virtual void render( SDL_Surface *screen, nSDL_Font *currentfont ) override;

    protected:

    private:
};

#endif // DESKTOPWIDGET_H

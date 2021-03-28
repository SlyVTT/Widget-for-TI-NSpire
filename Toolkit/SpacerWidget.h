#ifndef SPACERWIDGET_H
#define SPACERWIDGET_H

#include "Widget.h"


class SpacerWidget : public Widget
{
public:
    SpacerWidget()
    {
        widgettype = (char*) "Spacer";
    };

    SpacerWidget( char *l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : Widget( l, x, y, w, h, p )
    {
        widgettype = (char*) "Spacer";
    };

    virtual ~SpacerWidget() {};

    virtual void logic( CursorTask *mouse, KeyboardTask *keyboard ) override;

    virtual void render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts ) override;


protected:

private:
};

#endif // SPACERWIDGET_H

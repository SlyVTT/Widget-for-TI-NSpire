#ifndef RADIOCONTROLWIDGET_H
#define RADIOCONTROLWIDGET_H

#include "ButtonWidget.h"


class RadioControlWidget : public ButtonWidget
{
public:
    RadioControlWidget()
    {
        widgettype = (char*) "RadioControl";
    };

    RadioControlWidget( char *l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : ButtonWidget( l, x, y, w, h, p )
    {
        widgettype = (char*) "CheckBox";
    };

    virtual ~RadioControlWidget() { };

    virtual void logic( CursorTask *mouse, KeyboardTask *keyboard ) override;

    virtual void render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts ) override;

    virtual void invert()
    {
        is_ticked = !is_ticked;
    };

    virtual bool isticked( void )
    {
        return is_ticked;
    };

protected:

private:

    bool is_ticked = false;

    bool mouse_hold_down = false;

};

#endif // RADIOCONTROLWIDGET_H

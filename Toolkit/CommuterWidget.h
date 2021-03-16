#ifndef COMMUTERWIDGET_H
#define COMMUTERWIDGET_H

#include "ButtonWidget.h"


enum commutertype
{
    style1 = 0,
    style2 = 1,
    style3 = 2,
    style4 = 3
};

class CommuterWidget : public ButtonWidget
{
    public:
        CommuterWidget() { widgettype = (char*) "Commuter"; };
        CommuterWidget( char *l, int x, int y, int w, int h, Widget *p ) : ButtonWidget( l, x, y, w, h, p ) { widgettype = (char*) "Commuter"; };
        virtual ~CommuterWidget() { };

        virtual void logic( CursorTask *mouse, KeyboardTask *keyboard ) override;
        virtual void render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts ) override;

        virtual void invert() { is_ticked = !is_ticked; };
        virtual bool isticked( void ) { return is_ticked; };

        virtual void settype( commutertype type ) { typetick = type; };

        virtual void setnormal() { is_reversed = false; };
        virtual void setreversed() { is_reversed = true; };

    protected:
        bool is_ticked = false;
        bool is_reversed = false;

    private:
        bool mouse_hold_down = false;
        commutertype typetick = style1;
};

#endif // COMMUTERWIDGET_H

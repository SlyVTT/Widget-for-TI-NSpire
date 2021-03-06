#ifndef CHECKBOXWIDGET_H
#define CHECKBOXWIDGET_H

#include "ButtonWidget.h"


enum tick
{
    Square_Tick = 0,
    Cross_Tick = 1
};

class CheckBoxWidget : public ButtonWidget
{
    public:
        CheckBoxWidget() { widgettype = "CheckBox"; };
        CheckBoxWidget( char *l, int x, int y, int w, int h, Widget *p ) : ButtonWidget( l, x, y, w, h, p ) { widgettype = "CheckBox"; };
        virtual ~CheckBoxWidget() { };

        virtual void logic( CursorTask *mouse, KeyboardTask *keyboard ) override;
        virtual void render( SDL_Surface *screen, nSDL_Font *currentfont ) override;

        virtual void invert() { is_ticked = !is_ticked; };
        virtual bool isticked( void ) { return is_ticked; };

        virtual void settype( tick type ) { typetick = type; };

    protected:
        bool is_ticked = false;

    private:
        bool mouse_hold_down = false;
        tick typetick = Square_Tick;
};

#endif // CHECKBOXWIDGET_H

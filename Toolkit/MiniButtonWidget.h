#ifndef MINIBUTTONWIDGET_H
#define MINIBUTTONWIDGET_H

#include "ButtonWidget.h"

enum typesymbol
{
    Bottom_Arrow = 0,
    Up_Arrow = 1,
    Left_Arrow = 2,
    Right_Arrow = 3,
    Close_Symbol = 4,
    Question_Symbol = 5,
    Exclamation_Symbol = 6
};

class MiniButtonWidget : public ButtonWidget
{
public:
    MiniButtonWidget()
    {
        widgettype = (char*) "MiniButton";
    };

    MiniButtonWidget( char *l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : ButtonWidget( l, x, y, w, h, p )
    {
        widgettype = (char*) "MiniButton";
    };

    virtual ~MiniButtonWidget() { };

    virtual bool ispressed() override;

    virtual bool isticked( void )
    {
        return is_ticked;
    };

    virtual void invert( void )
    {
        is_ticked = !is_ticked;
    };

    virtual void logic( CursorTask *mouse, KeyboardTask *keyboard ) override;

    virtual void render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts ) override;

    virtual void settype( typesymbol type );



protected:

private:

    friend class DropBoxWidget;

    bool is_ticked = false;
    bool mouse_hold_down = false;

};

#endif // MINIBUTTONWIDGET_H

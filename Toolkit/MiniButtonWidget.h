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
        MiniButtonWidget()  { widgettype = "MiniButton"; };
        MiniButtonWidget( char *l, int x, int y, int w, int h, Widget *p ) : ButtonWidget( l, x, y, w, h, p ) { widgettype = "MiniButton"; };
        virtual ~MiniButtonWidget() { };

        virtual bool ispressed() override;
        virtual void logic( CursorTask *mouse, KeyboardTask *keyboard ) override;
        virtual void render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts ) override;

        virtual void settype( typesymbol type );

    protected:

    private:
};

#endif // MINIBUTTONWIDGET_H

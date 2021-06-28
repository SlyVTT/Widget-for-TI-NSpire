#ifndef MINIBUTTONWIDGET_H
#define MINIBUTTONWIDGET_H

#include "ButtonWidget.h"



class MiniButtonWidget : public ButtonWidget
{
public:
    MiniButtonWidget();
    MiniButtonWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p );
    virtual ~MiniButtonWidget();


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

    virtual bool ispressed() override;
    virtual bool isticked( void );
    virtual void invert( void );

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

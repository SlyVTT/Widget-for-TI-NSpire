#ifndef MENUITEMWIDGET_H
#define MENUITEMWIDGET_H

#include "ButtonWidget.h"


class MenuItemWidget : public ButtonWidget
{
    public:

    MenuItemWidget()
    {
        widgettype = (char*) "MenuItem";
    };

    MenuItemWidget( char *l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : ButtonWidget( l, x, y, w, h, p )
    {
        widgettype = (char*) "MenuItem";
    };

    virtual ~MenuItemWidget();


    virtual bool ispressed();


    virtual void logic( CursorTask *mouse, KeyboardTask *keyboard ) override;


    virtual void render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts ) override;


    protected:

    private:
        bool is_pressed = false;

};

#endif // MENUITEMWIDGET_H

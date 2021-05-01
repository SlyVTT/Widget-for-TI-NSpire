#ifndef MENUITEMWIDGET_H
#define MENUITEMWIDGET_H

#include "MiniButtonWidget.h"


class MenuItemWidget : public MiniButtonWidget
{
public:

    MenuItemWidget()
    {
        //widgettype = (char*) "MenuItem";
        strcpy( widgettype, (char*) "MenuItem");
    };

    MenuItemWidget( char *l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : MiniButtonWidget( l, x, y, w, h, p )
    {
        //widgettype = (char*) "MenuItem";
        strcpy( widgettype, (char*) "MenuItem");
    };

    virtual ~MenuItemWidget();

    virtual bool ispressed();

    virtual void logic( CursorTask *mouse, KeyboardTask *keyboard ) override;

    virtual void render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts ) override;

    virtual unsigned int getfulltextwidth()
    {
        return width_full_text;
    }

    virtual void drop( )
    {
        is_dropped = true;
        is_visible = true;
    }

    virtual void undrop( )
    {
        is_dropped = false;
        is_visible = false;
    }


protected:

private:
    char labelarrow[100];
    bool is_pressed = false;
    bool is_dropped = false;
    bool has_child_menu_open = false;
    unsigned int width_full_text = 0;
};

#endif // MENUITEMWIDGET_H

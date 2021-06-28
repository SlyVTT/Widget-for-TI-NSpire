#ifndef MENUITEMWIDGET_H
#define MENUITEMWIDGET_H

#include "MiniButtonWidget.h"


class MenuItemWidget : public MiniButtonWidget
{
public:

    MenuItemWidget();
    MenuItemWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p );
    virtual ~MenuItemWidget();

    virtual bool ispressed();

    virtual void logic( CursorTask *mouse, KeyboardTask *keyboard ) override;
    virtual void render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts ) override;

    virtual unsigned int getfulltextwidth();
    virtual void drop( );
    virtual void undrop( );

protected:

private:
    std::string labelarrow;
    bool is_pressed = false;
    bool is_dropped = false;
    bool has_child_menu_open = false;
    unsigned int width_full_text = 0;
};

#endif // MENUITEMWIDGET_H

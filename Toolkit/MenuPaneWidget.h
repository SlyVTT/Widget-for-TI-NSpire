#ifndef MENUPANEWIDGET_H
#define MENUPANEWIDGET_H

#include "ContainerVWidget.h"


class MenuPaneWidget : public ContainerVWidget
{
public:
    MenuPaneWidget();
    MenuPaneWidget(char *l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p );
    virtual ~MenuPaneWidget();

    virtual void adjust() override;

    virtual void logic( CursorTask *mouse, KeyboardTask *keyboard ) override;

    virtual void render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts ) override;

    virtual void drop( )
    {
        is_dropped = true;
        is_visible = true;
    }

    virtual void undrop( )
    {
        if (!has_child_menu_open)
        {
            is_dropped = false;
            is_visible = false;
        }
    }

    virtual void setchilddropped()
    {
        has_child_menu_open = true;
        is_visible = true;
    }

        virtual void unsetchilddropped()
    {
        has_child_menu_open = false;
    }


protected:

private:
    bool is_dropped = false;
    bool has_child_menu_open = false;
};

#endif // MENUPANEWIDGET_H

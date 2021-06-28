#ifndef MENUBARWIDGET_H
#define MENUBARWIDGET_H

#include "ContainerHWidget.h"


class MenuBarWidget : public ContainerHWidget
{
public:
    MenuBarWidget();
    MenuBarWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p );
    ~MenuBarWidget();

    virtual void adjust() override;

    virtual unsigned int getuseableheight() override;

    virtual void logic( CursorTask *mouse, KeyboardTask *keyboard ) override;

    virtual void render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts ) override;


protected:

private:
    bool has_child_menu_open = false;
    int child_menu_opened = -1;
};

#endif // MENUBARWIDGET_H

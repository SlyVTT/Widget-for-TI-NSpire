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

protected:

private:
};

#endif // MENUPANEWIDGET_H

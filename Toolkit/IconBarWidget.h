#ifndef ICONBARWIDGET_H
#define ICONBARWIDGET_H

#include "ContainerHWidget.h"


class IconBarWidget : public ContainerHWidget
{
public:
    IconBarWidget();
    IconBarWidget(char *l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p );
    ~IconBarWidget();

    virtual void adjust() override;

    virtual void logic( CursorTask *mouse, KeyboardTask *keyboard ) override;

    virtual void render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts ) override;

protected:

private:
};

#endif // ICONBARWIDGET_H

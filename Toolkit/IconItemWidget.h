#ifndef ICONITEMWIDGET_H
#define ICONITEMWIDGET_H

#include "ButtonWidget.h"


class IconItemWidget : public ButtonWidget
{
public:

    IconItemWidget();
    IconItemWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p );
    virtual ~IconItemWidget();

    void disable( void ) override;
    void enable(void ) override;

    virtual bool ispressed() override;

    virtual void logic( CursorTask *mouse, KeyboardTask *keyboard ) override;
    virtual void render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts ) override;

    virtual void assigniconenable( std::string filename );
    virtual void assignicondisable( std::string filename );

protected:

    std::string iconnameenable;
    int iconenableset = -1;
    std::string iconnamedisable;
    int icondisableset = -1;

    SDL_Surface *icon = nullptr;

private:
    bool is_ticked = false;
    bool mouse_hold_down = false;
};

#endif // ICONITEMWIDGET_H

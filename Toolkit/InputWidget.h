#ifndef INPUTWIDGET_H
#define INPUTWIDGET_H

#include "Widget.h"
#include <string>


class InputWidget : public Widget
{
public:
    InputWidget();
    InputWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p );
    virtual ~InputWidget();

    virtual void logic( CursorTask *mouse, KeyboardTask *keyboard ) override;
    virtual void render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts ) override;

    virtual std::string getcontent();
    virtual void setcontent(std::string str);

private:
    void updateScroll();

    std::string text = "";

    unsigned int cursor_pos = 0;
    unsigned int scroll = 0;
    unsigned int mousex,mousey;
    bool mouses;

    FontEngine *nfontwidget = nullptr;

    bool key_hold_down = false;
};

#endif // INPUTWIDGET_H

#ifndef INPUTWIDGET_H
#define INPUTWIDGET_H

#include "Widget.h"
#include <string>


class InputWidget : public Widget
{
public:
    InputWidget()
    {
        //widgettype = (char*) "Input";
        strcpy( widgettype, (char*) "Input");
    };
    InputWidget( char *l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : Widget( l, x, y, w, h, p )
    {
        //widgettype = (char*) "Input";
        strcpy( widgettype, (char*) "Input");
    };

    virtual ~InputWidget() {};

    virtual void logic( CursorTask *mouse, KeyboardTask *keyboard ) override;
    virtual void render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts ) override;

    virtual const char* getcontent()
    {
        return text.c_str();
    }

    virtual void setcontent(std::string str)
    {
        text = str;
        cursor_pos = 0;
        scroll = 0;
    }


private:
    void updateScroll();
    std::string text = "Empty string !!";
    unsigned int cursor_pos = 0;
    unsigned int scroll = 0;
    unsigned int mousex,mousey;
    bool mouses;

    FontEngine *nfontwidget = nullptr;

    bool key_hold_down = false;
};

#endif // INPUTWIDGET_H

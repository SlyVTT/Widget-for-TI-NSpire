#ifndef MULTILINETEXTBOXWIDGET_H
#define MULTILINETEXTBOXWIDGET_H

#include "InputWidget.h"


class MultiLineTextBoxWidget : public InputWidget
{
public:
    MultiLineTextBoxWidget()
    {
        //widgettype = (char*) "Input";
        strcpy( widgettype, (char*) "MultiLineTextBox");
    };
    MultiLineTextBoxWidget( char *l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : InputWidget( l, x, y, w, h, p )
    {
        //widgettype = (char*) "Input";
        strcpy( widgettype, (char*) "MultiLineTextBox");
    };

    virtual ~MultiLineTextBoxWidget() {};

    virtual void logic( CursorTask *mouse, KeyboardTask *keyboard ) override;

    virtual void render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts ) override;

protected:


private:
    void updateScroll();
    std::string text = "Empty string !!";

    std::vector<std::string> content;
    unsigned int nblinevisible = 0;
    unsigned int nbcharvisible = 0;

    unsigned int cursor_posX = 0;
    unsigned int cursor_posY = 0;
    unsigned int scrollX = 0;
    unsigned int scrollY = 0;

    unsigned int mousex,mousey;
    bool mouses;

    FontEngine *nfontwidget = nullptr;

    bool key_hold_down = false;
};

#endif // MULTILINETEXTBOXWIDGET_H

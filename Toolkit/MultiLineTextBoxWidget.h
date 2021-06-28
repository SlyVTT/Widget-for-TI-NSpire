#ifndef MULTILINETEXTBOXWIDGET_H
#define MULTILINETEXTBOXWIDGET_H

#include "Widget.h"


class MultiLineTextBoxWidget : public Widget
{
public:
    MultiLineTextBoxWidget();
    MultiLineTextBoxWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p );
    virtual ~MultiLineTextBoxWidget();

    virtual void logic( CursorTask *mouse, KeyboardTask *keyboard ) override;
    virtual void render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts ) override;

    virtual void loadcontentfromfile( std::string filename );
    virtual void savecontenttofile( std::string filename );
    virtual void flush();

    virtual void copyselection();
    virtual void cutselection();
    virtual void pasteselection();
    virtual void eraseselection();

    virtual void setnoneditable();
    virtual void seteditable();

    virtual std::string getcontent();
    virtual void setcontent( std::string str );

    virtual void appendcontent(std::string str);

protected:


private:
    void updateScroll();

    std::vector<std::string> content;

    KeyboardTask *keybclip = nullptr;

    unsigned int selectstart;
    unsigned int selectend;
    std::string selection;
    bool isselected;

    bool iseditable = true;

    unsigned int nblinetotal = 0;
    unsigned int firstlinevisible = 0;
    unsigned int currentline = 0;

    unsigned int currentlinecursor = 0;

    unsigned int nblinevisible = 0;
    unsigned int nbcharvisibleperline = 0;

    unsigned int cursor_posX = 0;

    unsigned int scrollX = 0;

    unsigned int mousex,mousey;
    bool mouses;

    FontEngine *nfontwidget = nullptr;

    bool key_hold_down = false;
};

#endif // MULTILINETEXTBOXWIDGET_H

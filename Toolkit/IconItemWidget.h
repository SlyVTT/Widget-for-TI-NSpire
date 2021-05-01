#ifndef ICONITEMWIDGET_H
#define ICONITEMWIDGET_H

#include "ButtonWidget.h"


class IconItemWidget : public ButtonWidget
{
public:

    IconItemWidget()
    {
        //widgettype = (char*) "IconItem";
        strcpy( widgettype, (char*) "IconItem");
    };

    IconItemWidget( char *l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : ButtonWidget( l, x, y, w, h, p )
    {
        //widgettype = (char*) "IconItem";
        strcpy( widgettype, (char*) "IconItem");
    };

    virtual ~IconItemWidget();


    void disable( void ) override;
    void enable(void ) override;

    virtual bool ispressed();


    virtual void logic( CursorTask *mouse, KeyboardTask *keyboard ) override;


    virtual void render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts ) override;

    virtual void assigniconenable( char* filename );
    virtual void assignicondisable( char* filename );

protected:

    char iconnameenable[100];
    int iconenableset = -1;
    char iconnamedisable[100];
    int icondisableset = -1;

    SDL_Surface *icon = nullptr;
    //SDL_Surface *icon_enable = nullptr;
    //SDL_Surface *icon_disable = nullptr;


private:
    bool is_pressed = false;

};

#endif // ICONITEMWIDGET_H

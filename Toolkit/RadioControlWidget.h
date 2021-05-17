#ifndef RADIOCONTROLWIDGET_H
#define RADIOCONTROLWIDGET_H

#include "ButtonWidget.h"


class RadioControlWidget : public ButtonWidget
{
public:
    RadioControlWidget();
    RadioControlWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p );
    virtual ~RadioControlWidget();

    virtual void logic( CursorTask *mouse, KeyboardTask *keyboard ) override;
    virtual void render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts ) override;

    virtual void invert();
    virtual bool isticked( void );

protected:

private:

    bool is_ticked = false;

    bool mouse_hold_down = false;

};

#endif // RADIOCONTROLWIDGET_H

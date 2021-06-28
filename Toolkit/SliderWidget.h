#ifndef SLIDERWIDGET_H
#define SLIDERWIDGET_H

#include "Widget.h"


class SliderWidget : public Widget
{
public:
    SliderWidget();
    SliderWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p );
    ~SliderWidget();

    int getvalueint();
    float getvaluefloat();
    void setrangeint( int minvalue, int maxvalue);
    void setrangefloat( float minvalue, float maxvalue );

    virtual void logic( CursorTask *mouse, KeyboardTask *keyboard ) override;
    virtual void render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts ) override;

protected:
    bool is_pressed = false;
    int length_pixels = 0;
    int position_cursor_pixels = 0;

    int intmin=0;
    int intmax=100;

    float floatmin=0.0;
    float floatmax=1.0;

};

#endif // SLIDERWIDGET_H

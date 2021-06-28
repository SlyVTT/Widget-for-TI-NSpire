#include "SliderWidget.h"

SliderWidget::SliderWidget()
{
    widgettype =  "Slider";
    //strcpy( widgettype, (char*) "Slider");
};

SliderWidget::SliderWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : Widget( l, x, y, w, h, p )
{
    length_pixels = w-8;
    widgettype =  "Slider";
    //strcpy( widgettype, (char*) "Slider");
};

SliderWidget::~SliderWidget()
{

};


void SliderWidget::setrangeint( int minvalue, int maxvalue)
{
    intmin = minvalue;
    intmax=maxvalue;
};


void SliderWidget::setrangefloat( float minvalue, float maxvalue )
{
    floatmin = minvalue;
    floatmax=maxvalue;
};


int SliderWidget::getvalueint()
{
    int temp = (int) (intmin + (intmax-intmin)*position_cursor_pixels/length_pixels);
    return temp;
}


float SliderWidget::getvaluefloat()
{
    float temp = (float) (floatmin + (floatmax-floatmin)*position_cursor_pixels/length_pixels);
    return temp;
}



void SliderWidget::logic( CursorTask *mouse, KeyboardTask *keyboard )
{
    if (is_enabled && is_visible)
    {

        is_hovering = cursoron( mouse );
        bool currently_pressed = (mouse->state || keyboard->kbSCRATCH) && is_hovering;

        length_pixels = width - 10;
        if (currently_pressed)
        {
            unsigned int x=mouse->x;
            if ((x>=xpos+5) && (x<=xpos+width-5))
            {
                position_cursor_pixels = x-(xpos+5);
            }
            else if ((x>=xpos) && (x<=xpos+5))
            {
                position_cursor_pixels = 0;
            }
            else if ((x>=xpos+width-5) && (x<=xpos+width))
            {
                position_cursor_pixels = length_pixels;
            }
        }

        if(currently_pressed && !is_pressed)
        {
            if (clickfunction)
                clickfunction( (char*) "test" );
        }
        else if(!currently_pressed && is_pressed)
        {
            if (releasefunction)
                releasefunction( (char*) "test" );
        }
        else if(is_hovering)
        {
            if (hoverfunction)
                hoverfunction( (char*) "test" );
        }

        is_pressed = currently_pressed;

        for (auto& c : children )
            c->logic( mouse, keyboard );
    }
}

void SliderWidget::render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts )
{
    if (is_visible)
    {



        if (is_enabled)
        {
            roundedBoxRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_filling_enable.R, colors->widget_filling_enable.G, colors->widget_filling_enable.B, colors->widget_filling_enable.A);

            //int sl = nSDL_GetStringWidth( currentfont, label );
            //int sh = nSDL_GetStringHeight( currentfont, label );

            if (!is_hovering)
            {
                roundedRectangleRGBA( screen, xpos+5, ypos+height/2-2, xpos+width-5, ypos+height/2+2, 2, colors->widget_border_enable.R, colors->widget_border_enable.G, colors->widget_border_enable.B, colors->widget_border_enable.A);
                filledCircleRGBA( screen, xpos+5+position_cursor_pixels, ypos+height/2, 5, colors->widget_filling_enable.R, colors->widget_filling_enable.G, colors->widget_filling_enable.B, colors->widget_filling_enable.A);
                circleRGBA( screen, xpos+5+position_cursor_pixels, ypos+height/2, 5, colors->widget_border_enable.R, colors->widget_border_enable.G, colors->widget_border_enable.B, colors->widget_border_enable.A);
            }
            else
            {
                roundedRectangleRGBA( screen, xpos+5, ypos+height/2-2, xpos+width-5, ypos+height/2+2, 2, colors->widget_border_cursoron.R, colors->widget_border_cursoron.G, colors->widget_border_cursoron.B, colors->widget_border_cursoron.A);
                filledCircleRGBA( screen, xpos+5+position_cursor_pixels, ypos+height/2, 5, colors->widget_filling_enable.R, colors->widget_filling_enable.G, colors->widget_filling_enable.B, colors->widget_filling_enable.A);
                circleRGBA( screen, xpos+5+position_cursor_pixels, ypos+height/2, 5, colors->widget_border_cursoron.R, colors->widget_border_cursoron.G, colors->widget_border_cursoron.B, colors->widget_border_cursoron.A);
            }

            //nSDL_DrawString( screen, currentfont, xpos+3 , ypos+sh/2, "%s", label );
        }
        else
        {
            roundedBoxRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_filling_disable.R, colors->widget_filling_disable.G, colors->widget_filling_disable.B, colors->widget_filling_disable.A);

            roundedRectangleRGBA( screen, xpos+5, ypos+height/2-2, xpos+width-5, ypos+height/2+2, 2, colors->widget_border_disable.R, colors->widget_border_disable.G, colors->widget_border_disable.B, colors->widget_border_disable.A);
            filledCircleRGBA( screen, xpos+5+position_cursor_pixels, ypos+height/2, 5, colors->widget_filling_disable.R, colors->widget_filling_disable.G, colors->widget_filling_disable.B, colors->widget_filling_disable.A);
            circleRGBA( screen, xpos+5+position_cursor_pixels, ypos+height/2, 5, colors->widget_border_disable.R, colors->widget_border_disable.G, colors->widget_border_disable.B, colors->widget_border_disable.A);
        }

        for (auto& c : children )
            c->render( screen, colors, fonts );

    }
}

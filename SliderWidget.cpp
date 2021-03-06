#include "SliderWidget.h"




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
        bool currently_pressed = mouse->state && is_hovering;

        if (currently_pressed)
        {
            int x=mouse->x;
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
                clickfunction( "test" );
        }
        else if(!currently_pressed && is_pressed)
        {
            if (releasefunction)
                releasefunction( "test" );
        }
        else if(is_hovering)
        {
            if (hoverfunction)
                hoverfunction( "test" );
        }

        is_pressed = currently_pressed;

        for (auto& c : children )
            c->logic( mouse, keyboard );
    }
}

void SliderWidget::render( SDL_Surface *screen, nSDL_Font *currentfont )
{
    if (is_visible)
    {

        roundedBoxRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, 255, 255, 255, 255);

        if (is_enabled)
        {
            //int sl = nSDL_GetStringWidth( currentfont, label );
            //int sh = nSDL_GetStringHeight( currentfont, label );

            if (!is_hovering)
            {
                roundedRectangleRGBA( screen, xpos+5, ypos+height/2-2, xpos+width-5, ypos+height/2+2, 2, 255, 0, 0, 255);
                filledCircleRGBA( screen, xpos+5+position_cursor_pixels, ypos+height/2, 5, 255, 255, 255, 255 );
                circleRGBA( screen, xpos+5+position_cursor_pixels, ypos+height/2, 5, 255, 0, 0, 255 );
            }
            else
            {
                roundedRectangleRGBA( screen, xpos+5, ypos+height/2-2, xpos+width-5, ypos+height/2+2, 2, 0, 255, 0, 255);
                filledCircleRGBA( screen, xpos+5+position_cursor_pixels, ypos+height/2, 5, 255, 255, 255, 255 );
                circleRGBA( screen, xpos+5+position_cursor_pixels, ypos+height/2, 5, 0, 255, 0, 255 );
            }

            //nSDL_DrawString( screen, currentfont, xpos+3 , ypos+sh/2, "%s", label );
        }
        else
        {
            roundedRectangleRGBA( screen, xpos+5, ypos+height/2-2, xpos+width-5, ypos+height/2+2, 2, 0, 0, 0, 255);
            filledCircleRGBA( screen, xpos+5+position_cursor_pixels, ypos+height/2, 5, 255, 255, 255, 255 );
            circleRGBA( screen, xpos+5+position_cursor_pixels, ypos+height/2, 5, 0, 0, 0, 255 );
        }

        for (auto& c : children )
            c->render( screen, currentfont );

    }
}

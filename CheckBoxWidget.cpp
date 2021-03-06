#include "CheckBoxWidget.h"


void CheckBoxWidget::logic( CursorTask *mouse, KeyboardTask *keyboard )
{
    if (is_enabled && is_visible)
    {
        is_hovering = cursoron( mouse );
        bool currently_pressed = mouse->state && is_hovering;

        if(mouse_hold_down)
        {
            mouse_hold_down = currently_pressed;
        }
        else if (currently_pressed && !is_ticked )
        {
            invert();

            if (clickfunction)
                clickfunction( "test" );

            mouse_hold_down = true;
        }
        else if (currently_pressed && is_ticked )
        {
            invert();

            if (releasefunction)
                releasefunction( "test" );

            mouse_hold_down = true;
        }
        else if (is_hovering)
        {
            if (hoverfunction)
                hoverfunction( "test" );
        }

        for (auto& c : children )
            c->logic( mouse, keyboard );
    }
}

void CheckBoxWidget::render( SDL_Surface *screen, nSDL_Font *currentfont )
{
    if (is_visible)
    {

        roundedBoxRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, 255, 255, 255, 255);

        if (is_enabled)
        {

            if (!is_hovering)
            {
                roundedRectangleRGBA( screen, xpos, ypos+height/2-6, xpos+12, ypos+height/2+6, 3, 255, 0, 0, 255);
            }
            else
            {
                roundedRectangleRGBA( screen, xpos, ypos+height/2-6, xpos+12, ypos+height/2+6, 3, 0, 255, 0, 255);
            }
        }
        else
        {
            roundedRectangleRGBA( screen, xpos, ypos+height/2-6, xpos+12, ypos+height/2+6, 3, 0, 0, 0, 255);
        }

        int sl = nSDL_GetStringWidth( currentfont, label );
        int sh = nSDL_GetStringHeight( currentfont, label );

        nSDL_DrawString( screen, currentfont, xpos+15 , ypos+(height-sh)/2, "%s", label );

        if (is_ticked && (typetick == Square_Tick ))
        {
            roundedBoxRGBA( screen, xpos+3, ypos+height/2-3, xpos+9, ypos+height/2+3, 1, 0, 0, 0, 255);
        }
        else if (is_ticked && (typetick == Cross_Tick ))
        {
            lineRGBA( screen, xpos+3, ypos+height/2-3, xpos+9, ypos+height/2+3, 0, 0, 0, 255);
            lineRGBA( screen, xpos+4, ypos+height/2-3, xpos+9, ypos+height/2+2, 0, 0, 0, 255);
            lineRGBA( screen, xpos+3, ypos+height/2-2, xpos+8, ypos+height/2+3, 0, 0, 0, 255);

            lineRGBA( screen, xpos+3, ypos+height/2+3, xpos+9, ypos+height/2-3, 0, 0, 0, 255);
            lineRGBA( screen, xpos+3, ypos+height/2+2, xpos+8, ypos+height/2-3, 0, 0, 0, 255);
            lineRGBA( screen, xpos+4, ypos+height/2+3, xpos+9, ypos+height/2-2, 0, 0, 0, 255);
        }


        for (auto& c : children )
            c->render( screen, currentfont );

    }
}

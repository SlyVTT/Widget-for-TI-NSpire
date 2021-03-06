#include "FrameWidget.h"



void FrameWidget::logic( CursorTask *mouse, KeyboardTask *keyboard )
{
    if (is_enabled && is_visible)
    {

        is_hovering = cursoron( mouse );
        bool currently_pressed = mouse->state && is_hovering;


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

void FrameWidget::render( SDL_Surface *screen, nSDL_Font *currentfont )
{
    if (is_visible)
    {

        roundedBoxRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, 255, 255, 255, 255);

        if (is_enabled)
        {
            int sl = nSDL_GetStringWidth( currentfont, label );
            int sh = nSDL_GetStringHeight( currentfont, label );

            if (!is_hovering)
            {
                roundedRectangleRGBA( screen, xpos, ypos+sh, xpos+width, ypos+height, 3, 255, 0, 0, 255);
            }
            else
            {
                roundedRectangleRGBA( screen, xpos, ypos+sh, xpos+width, ypos+height, 3, 0, 255, 0, 255);
            }

            boxRGBA( screen, xpos+3, ypos, xpos+3+sl, ypos+sh, 255, 255, 255, 255);
            nSDL_DrawString( screen, currentfont, xpos+3 , ypos+sh/2, "%s", label );
        }
        else
        {
            int sl = nSDL_GetStringWidth( currentfont, label );
            int sh = nSDL_GetStringHeight( currentfont, label );

            //Border of the button is black cause it is disabled
            roundedRectangleRGBA( screen, xpos, ypos+sh, xpos+width, ypos+height, 3, 0, 0, 0, 255);

            boxRGBA( screen, xpos+3, ypos, xpos+3+sl, ypos+sh, 255, 255, 255, 255);
            nSDL_DrawString( screen, currentfont, xpos+3 , ypos+sh/2, "%s", label );
        }

        for (auto& c : children )
            c->render( screen, currentfont );

    }
}

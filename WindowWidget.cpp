#include "WindowWidget.h"



void WindowWidget::logic( CursorTask *mouse, KeyboardTask *keyboard )
{

    is_hovering = cursoron( mouse );
    bool currently_pressed = mouse->state && is_hovering;
/*
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
*/
    for (auto& c : children )
        c->logic( mouse, keyboard );

}


void WindowWidget::render( SDL_Surface *screen, nSDL_Font *currentfont )
{

    if (is_visible)
    {

        if (is_enabled)
        {
            roundedBoxRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, 255, 255, 255, 255);
            roundedBoxRGBA( screen, xpos, ypos, xpos+width, ypos+12, 3, 0, 155, 255, 255);

            if (!is_hovering)
            {
                roundedRectangleRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, 255, 0, 0, 255);
            }
            else
            {
                roundedRectangleRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, 0, 255, 0, 255);
            }

            int sl = nSDL_GetStringWidth( currentfont, label );
            int sh = nSDL_GetStringHeight( currentfont, label );

            nSDL_DrawString( screen, currentfont, xpos+(width-sl)/2 , ypos+sh/2, "%s", label );
        }
        else
        {
            roundedBoxRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, 255, 255, 255, 255);
            roundedBoxRGBA( screen, xpos, ypos, xpos+width, ypos+12, 3, 200, 200, 200, 255);
            roundedRectangleRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, 0, 0, 0, 255);

            int sl = nSDL_GetStringWidth( currentfont, label );
            int sh = nSDL_GetStringHeight( currentfont, label );

            nSDL_DrawString( screen, currentfont, xpos+(width-sl)/2 , ypos+sh/2, "%s", label );
        }

        for (auto& c : children )
            c->render( screen, currentfont );

    }

}

/*
bool WindowWidget::cursoron( CursorTask *mouse )
{
    return (mouse->x >= xpos) && (mouse->y >= ypos) && (mouse->x <= xpos+width) && (mouse->y <= ypos+height);
}
*/

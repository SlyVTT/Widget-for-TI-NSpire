#include "LabelWidget.h"



void LabelWidget::logic( CursorTask *mouse, KeyboardTask *keyboard )
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

void LabelWidget::render( SDL_Surface *screen, nSDL_Font *currentfont )
{
    if (is_visible)
    {

        roundedBoxRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, 255, 255, 255, 255);

        if (is_enabled)
        {
            int sl = nSDL_GetStringWidth( currentfont, label );
            int sh = nSDL_GetStringHeight( currentfont, label );
            if (alignment==centered) nSDL_DrawString( screen, currentfont, xpos+(width-sl)/2 , ypos+(height-sh)/2, "%s", label );
            if (alignment==left) nSDL_DrawString( screen, currentfont, xpos, ypos+(height-sh)/2, "%s", label );
            if (alignment==right) nSDL_DrawString( screen, currentfont, xpos+(width-sl), ypos+(height-sh)/2, "%s", label );
        }
        else
        {
            int sl = nSDL_GetStringWidth( currentfont, label );
            int sh = nSDL_GetStringHeight( currentfont, label );
            if (alignment==centered) nSDL_DrawString( screen, currentfont, xpos+(width-sl)/2 , ypos+(height-sh)/2, "%s", label );
            if (alignment==left) nSDL_DrawString( screen, currentfont, xpos, ypos+(height-sh)/2, "%s", label );
            if (alignment==right) nSDL_DrawString( screen, currentfont, xpos+(width-sl), ypos+(height-sh)/2, "%s", label );
        }

        for (auto& c : children )
            c->render( screen, currentfont );

    }
}

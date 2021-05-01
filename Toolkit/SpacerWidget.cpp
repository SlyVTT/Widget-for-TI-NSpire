#include "SpacerWidget.h"

void SpacerWidget::logic( CursorTask *mouse, KeyboardTask *keyboard )
{
    if (is_enabled && is_visible)
    {
        for (auto& c : children )
            c->logic( mouse, keyboard );
    }
}

void SpacerWidget::render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts )
{
    if (is_visible)
    {

        if (is_enabled)
        {

        }
        else
        {

        }

        for (auto& c : children )
            c->render( screen, colors, fonts );
    }
}

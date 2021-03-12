#include "DesktopWidget.h"

void DesktopWidget::logic( CursorTask *mouse, KeyboardTask *keyboard )
{
    for (auto& c : children )
        c->logic( mouse, keyboard );
}

void DesktopWidget::render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts )
{
    for (auto& c : children )
        c->render( screen, colors, fonts );
}

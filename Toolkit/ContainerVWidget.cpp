#include "ContainerVWidget.h"




void ContainerVWidget::adjust( )
{
    if (parent)
    {
        if ((strcmp( parent->getwidgettype(),(char*) "ContainerV" )==0) || (strcmp( parent->getwidgettype(),(char*) "ContainerH" )==0))
        {
            // nothing to do, it comes from the parent
        }
        else
        {
            xpos = parent->getuseablexpos();
            ypos = parent->getuseableypos();
            width = parent->getuseablewidth();
            height = parent->getuseableheight();
        }
    }

    int i=0;
    nbchildren = children.size();

    for (auto& c : children )
    {
        c->setdimensions( xpos, ypos+1 + height/nbchildren*i, width, height/nbchildren-2 );
        i++;
    }

    for (auto& c : children )
        c->adjust();
}

void ContainerVWidget::logic( CursorTask *mouse, KeyboardTask *keyboard )
{
    if (is_enabled && is_visible)
    {
        for (auto& c : children )
            c->logic( mouse, keyboard );
    }
}

void ContainerVWidget::render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts )
{
    if (is_visible)
    {
        for (auto& c : children )
            c->render( screen, colors, fonts );
    }
}

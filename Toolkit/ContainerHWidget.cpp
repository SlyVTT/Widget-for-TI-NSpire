#include "ContainerHWidget.h"




void ContainerHWidget::adjust( )
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
        c->setdimensions( xpos+1 + width/nbchildren*i, ypos, width/nbchildren-2, height );
        i++;
    }

    for (auto& c : children )
        c->adjust();
}

void ContainerHWidget::logic( CursorTask *mouse, KeyboardTask *keyboard )
{
    if (is_enabled && is_visible)
    {
        for (auto& c : children )
            c->logic( mouse, keyboard );
    }
}

void ContainerHWidget::render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts )
{
    if (is_visible)
    {
        for (auto& c : children )
            c->render( screen, colors, fonts );
    }
}

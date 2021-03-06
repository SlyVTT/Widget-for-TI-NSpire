#include "ContainerVWidget.h"




void ContainerVWidget::adjust( )
{
    if (parent)
    {
        if (parent->getwidgettype()=="Window")
        {
            //remove 3 pixels all around the window borders and title bar to get the actual size
            xpos = parent->getxpos() +3;
            ypos = parent->getypos() +15;
            width = parent->getwidth() -6;
            height = parent->getheight() -18;
        }
        else if (parent->getwidgettype()=="Frame")
        {
            //remove 3 pixels all around the window borders and title bar to get the actual size
            xpos = parent->getxpos() +3;
            ypos = parent->getypos() +8;
            width = parent->getwidth() -6;
            height = parent->getheight() -11;
        }
        else if (parent->getwidgettype()=="ContainerH")
        {
            // size is coming from Parent and is cascaded to childrens

            //if parent is a container, no need for extra space around the widgets
            //xpos = parent->getxpos();
            //ypos = parent->getypos();
            //width = parent->getwidth();
            //height = parent->getheight();
        }
        else if (parent->getwidgettype()=="ContainerV")
        {
            // size is coming from Parent and is cascaded to childrens

            //if parent is a container, no need for extra space around the widgets
            //xpos = parent->getxpos();
            //ypos = parent->getypos();
            //width = parent->getwidth();
            //height = parent->getheight();
        }
    }

    int i=0;
    nbchildren = children.size();

    for (auto& c : children )
    {
        c->setdimensions( xpos+2, ypos+2 + height/nbchildren*i, width-4, height/nbchildren-4 );
        i++;
    }
}

void ContainerVWidget::logic( CursorTask *mouse, KeyboardTask *keyboard )
{
    if (is_enabled && is_visible)
    {
        for (auto& c : children )
            c->logic( mouse, keyboard );
    }
}

void ContainerVWidget::render( SDL_Surface *screen, nSDL_Font *currentfont )
{
    if (is_visible)
    {
        for (auto& c : children )
            c->render( screen, currentfont );
    }
}

#include "MenuPaneWidget.h"

#include "FontEngine.h"


MenuPaneWidget::MenuPaneWidget() : ContainerVWidget ()
{
    //widgettype = (char*) "MenuPane";
    strcpy( widgettype, (char*) "MenuPane");
};


MenuPaneWidget::MenuPaneWidget(char *l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : ContainerVWidget( l, x, y, w, h, p )
{
    //widgettype = (char*) "MenuPane";
    strcpy( widgettype, (char*) "MenuPane");

    strcpy(label,l);
    xrel=x;
    yrel=y;
    widrel=w;
    heirel=h;
    parent=p;

    if (parent)
    {
        xpos = parent->getuseablexpos();
        ypos = parent->getuseableypos()+12;

        int tempw = 0;
        int temph = 0;
        for (auto& c : children )
        {
            // TODO : need to retrieve the dimension of the item of the menu

            //if (FontEngine::getstringwidth( (char*) c->getlabel() ) >= tempw) tempw = FontEngine::getstringwidth( (char*) c->getlabel() );
            tempw = 50;
            temph += 14;
        }
        width = tempw;
        height = temph;


        parent->addpopupchild( this );

    }
    else
    {
        xpos=xrel;
        ypos=yrel;
        width=widrel;
        height=heirel;
    }

    int i=0;
    nbchildren = children.size();

    for (auto& c : children )
    {
        c->setdimensions( xpos+1, ypos+1 + 14*i, width-2, 12 );
        i++;
    }

    for (auto& c : children )
        c->adjust();

};



MenuPaneWidget::~MenuPaneWidget()
{
    //dtor
}


void MenuPaneWidget::adjust()
{

    if (parent)
    {
        if(parent->getparent())
        {
            //if the parent of the parent is a MenuPane, we shift on the right of the parent menu (this is a submenu
            if (strcmp(parent->getparent()->getwidgettype(), (char*) "MenuPane") ==0)
            {
                if (parent->getxpos()+parent->getwidth()+width<=SCREEN_WIDTH) // si on ne dépasse pas le bord droit de l'écran, on met à droite
                    xpos = parent->getxpos()+parent->getwidth();
                else
                    xpos = parent->getxpos() - width;    // sinon on met à gauche
            }
            else
            {
                xpos = parent->getxpos();   // else we just put below
            }

            ypos = parent->getypos() + parent->getheight();

            int tempw = 0;
            int temph = 0;

            for (auto& c : children )
            {
                //if (FontEngine::getstringwidth( (char*) c->getlabel() ) >= tempw) tempw = FontEngine::getstringwidth( (char*) c->getlabel() );
                tempw = 50;
                temph += 14;
            }

            width = tempw;
            height = temph;

        }
    }
    else
    {
        xpos=xrel;
        ypos=yrel;
        width=widrel;
        height=heirel;
    }


    int i=0;
    nbchildren = children.size();

    for (auto& c : children )
    {
        c->setdimensions( xpos+1, ypos+1 + 14*i, width-2, 12 );
        i++;
    }

    for (auto& c : children )
        c->adjust();

}



void MenuPaneWidget::logic( CursorTask *mouse, KeyboardTask *keyboard )
{
    if (is_enabled && is_visible)
    {
        for (auto& c : children )
            c->logic( mouse, keyboard );
    }
}



void MenuPaneWidget::render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts )
{
    if (is_visible)
    {

        if (is_enabled)
        {
            boxRGBA( screen, xpos, ypos, xpos+width, ypos+height, colors->widget_filling_enable.R, colors->widget_filling_enable.G, colors->widget_filling_enable.B, colors->widget_filling_enable.A);

            if (!is_hovering)
            {
                roundedRectangleRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_border_enable.R, colors->widget_border_enable.G, colors->widget_border_enable.B, colors->widget_border_enable.A);
            }
            else
            {
                roundedRectangleRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_border_cursoron.R, colors->widget_border_cursoron.G, colors->widget_border_cursoron.B, colors->widget_border_cursoron.A);
            }

        }
        else
        {
            boxRGBA( screen, xpos, ypos, xpos+width, ypos+height, colors->widget_filling_disable.R, colors->widget_filling_disable.G, colors->widget_filling_disable.B, colors->widget_filling_disable.A);
            roundedRectangleRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_border_disable.R, colors->widget_border_disable.G, colors->widget_border_disable.B, colors->widget_border_disable.A);

        }

        for (auto& c : children )
        {
            if (c->isvisible())
                c->render( screen, colors, fonts );
        }

    }
}

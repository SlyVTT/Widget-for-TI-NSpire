#include "MenuBarWidget.h"

#include "WindowWidget.h"
#include "DesktopWidget.h"

MenuBarWidget::MenuBarWidget() : ContainerHWidget ()
{
    strcpy( widgettype, (char*) "MenuBar");
};


MenuBarWidget::MenuBarWidget(char *l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : ContainerHWidget( l, x, y, w, h, p )
{
    strcpy( widgettype, (char*) "MenuBar");

    strcpy(label,l);
    xrel=x;
    yrel=y;
    widrel=w;
    heirel=h;
    parent=p;

    if (parent)
    {
        if (strcmp( parent->getwidgettype(),(char*) "Desktop" )==0)
        {
            dynamic_cast<DesktopWidget*>(parent)->setmenubar();

            xpos = parent->getuseablexpos();

            if (dynamic_cast<DesktopWidget*>(parent)->geticonbar() == true)
            {
                ypos = parent->getuseableypos()-12-20;
            }
            else
            {
                ypos = parent->getuseableypos()-12;
            }

            width = parent->getuseablewidth();
            height = 12;
        }
        else if (strcmp( parent->getwidgettype(),(char*) "Window" )==0)
        {
            dynamic_cast<WindowWidget*>(parent)->setmenubar();

            xpos = parent->getuseablexpos();

            if (dynamic_cast<WindowWidget*>(parent)->geticonbar() == true)
            {
                ypos = parent->getuseableypos()-12-20;
            }
            else
            {
                ypos = parent->getuseableypos()-12;
            }

            width = parent->getuseablewidth();
            height = 12;
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
        c->setdimensions( xpos+1 + width/nbchildren*i, ypos, width/nbchildren-2, height-1 );
        i++;
    }

    for (auto& c : children )
        c->adjust();

};



MenuBarWidget::~MenuBarWidget()
{
    //dtor
}


void MenuBarWidget::adjust()
{

    if (parent)
    {
        if (strcmp( parent->getwidgettype(),(char*) "Desktop" )==0)
        {
            xpos = parent->getuseablexpos();

            if (dynamic_cast<DesktopWidget*>(parent)->geticonbar() == true)
            {
                ypos = parent->getuseableypos()-12-20;
            }
            else
            {
                ypos = parent->getuseableypos()-12;
            }

            width = parent->getuseablewidth();
            height = 12;
        }
        else if (strcmp( parent->getwidgettype(),(char*) "Window" )==0)
        {
            xpos = parent->getuseablexpos();

            if (dynamic_cast<WindowWidget*>(parent)->geticonbar() == true)
            {
                ypos = parent->getuseableypos()-12-20;
            }
            else
            {
                ypos = parent->getuseableypos()-12;
            }

            width = parent->getuseablewidth();
            height = 12;
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
        c->setdimensions( xpos+1 + width/nbchildren*i, ypos, width/nbchildren-2, height );
        i++;
    }

    for (auto& c : children )
        c->adjust();

}

unsigned int MenuBarWidget::getuseableheight()
{
    return height - 2;
};


void MenuBarWidget::logic( CursorTask *mouse, KeyboardTask *keyboard )
{
    if (is_enabled && is_visible)
    {
        for (auto& c : children )
            c->logic( mouse, keyboard );
    }
}



void MenuBarWidget::render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts )
{
    if (is_visible)
    {

        if (is_enabled)
        {
            boxRGBA( screen, xpos, ypos, xpos+width, ypos+height, colors->widget_filling_enable.R, colors->widget_filling_enable.G, colors->widget_filling_enable.B, colors->widget_filling_enable.A);

            if (!is_hovering)
            {
                lineRGBA( screen, xpos, ypos+height-1, xpos+width, ypos+height-1, colors->widget_border_enable.R, colors->widget_border_enable.G, colors->widget_border_enable.B, colors->widget_border_enable.A);
            }
            else
            {
                lineRGBA( screen, xpos, ypos+height-1, xpos+width, ypos+height-1, colors->widget_border_cursoron.R, colors->widget_border_cursoron.G, colors->widget_border_cursoron.B, colors->widget_border_cursoron.A);
            }

        }
        else
        {
            boxRGBA( screen, xpos, ypos, xpos+width, ypos+height, colors->widget_filling_disable.R, colors->widget_filling_disable.G, colors->widget_filling_disable.B, colors->widget_filling_disable.A);
            lineRGBA( screen, xpos, ypos+height-1, xpos+width, ypos+height-1, colors->widget_border_disable.R, colors->widget_border_disable.G, colors->widget_border_disable.B, colors->widget_border_disable.A);
        }

        for (auto& c : children )
        {
            if (c->isvisible())
                c->render( screen, colors, fonts );
        }

    }
}

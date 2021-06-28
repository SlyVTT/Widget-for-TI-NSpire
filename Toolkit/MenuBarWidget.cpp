#include "MenuBarWidget.h"
#include "MenuItemWidget.h"
#include "WindowWidget.h"
#include "DesktopWidget.h"


MenuBarWidget::MenuBarWidget() : ContainerHWidget ()
{
    widgettype = "MenuBar";
}


MenuBarWidget::MenuBarWidget(std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : ContainerHWidget( l, x, y, w, h, p )
{
    widgettype = "MenuBar";

    label = l;
    xrel=x;
    yrel=y;
    widrel=w;
    heirel=h;
    parent=p;

    if (parent)
    {
        if (parent->getwidgettype() == "Desktop")
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
        else if (parent->getwidgettype() == "Window" )
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

    unsigned int currentpositionX = xpos+1;
    unsigned int currentwidth=0;

    for (auto& c : children )   // this code has been updated to have a homogeneous spacing of MenuItemsWidgets
    {
        //c->setdimensions( xpos+1 + width/nbchildren*i, ypos, width/nbchildren-2, height );
        //i++;
        currentwidth = dynamic_cast<MenuItemWidget*>(c)->getfulltextwidth() + 10;
        c->setdimensions( currentpositionX, ypos, currentwidth, height );
        currentpositionX += currentwidth;
    }

    for (auto& c : children )
        c->adjust();

}



MenuBarWidget::~MenuBarWidget()
{
    //dtor
}


void MenuBarWidget::adjust()
{

    if (parent)
    {
        if (parent->getwidgettype() == "Desktop" )
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
        else if (parent->getwidgettype() == "Window" )
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

    unsigned int currentpositionx = xpos+1;
    unsigned int widthchildren;

    for (auto& c : children )  // this code has been updated to have a homogeneous spacing of MenuItemsWidgets
    {
        //c->setdimensions( xpos+1 + width/nbchildren*i, ypos, width/nbchildren-2, height );
        //i++;
        widthchildren = dynamic_cast<MenuItemWidget*>(c)->getfulltextwidth() + 10;
        c->setdimensions( currentpositionx, ypos, widthchildren, height );
        currentpositionx += widthchildren;
    }

    for (auto& c : children ) c->adjust();
}


unsigned int MenuBarWidget::getuseableheight()
{
    return height - 2;
}


void MenuBarWidget::logic( CursorTask *mouse, KeyboardTask *keyboard )
{
    if (is_enabled && is_visible)
    {
        for (auto& c : children )
            c->logic( mouse, keyboard );
    }
    else
    {
        // DEBUG : test to see if it actually works
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
            c->render( screen, colors, fonts );
    }
}

#include "IconBarWidget.h"
#include "WindowWidget.h"
#include "DesktopWidget.h"


IconBarWidget::IconBarWidget() : ContainerHWidget ()
{
    widgettype =  "IconBar";
};


IconBarWidget::IconBarWidget(std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : ContainerHWidget( l, x, y, w, h, p )
{
    widgettype = "IconBar";

    label = l;
    xrel=x;
    yrel=y;
    widrel=w;
    heirel=h;
    parent=p;

    if (parent)
    {
        if (parent->getwidgettype() == "Desktop" )
        {
            dynamic_cast<DesktopWidget*>(parent)->seticonbar();

            xpos = parent->getuseablexpos();

            if (dynamic_cast<DesktopWidget*>(parent)->getmenubar() == true)
            {
                ypos = parent->getuseableypos()-20; //-12-20
            }
            else
            {
                ypos = parent->getuseableypos()-20; //-20
            }

            width = parent->getuseablewidth();
            height = 20;
        }
        else if (parent->getwidgettype() == "Window" )
        {
            dynamic_cast<WindowWidget*>(parent)->seticonbar();

            xpos = parent->getuseablexpos();

            if (dynamic_cast<WindowWidget*>(parent)->getmenubar() == true)
            {
                ypos = parent->getuseableypos()-20; //-12-20
            }
            else
            {
                ypos = parent->getuseableypos()-20; //-20
            }

            width = parent->getuseablewidth();
            height = 20;
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
        c->setdimensions( xpos+1 + 22*i, ypos, 20, 20 );
        i++;
    }

    for (auto& c : children )
        c->adjust();

};

IconBarWidget::~IconBarWidget()
{
    //dtor
}




void IconBarWidget::adjust()
{

    if (parent)
    {
        if (parent->getwidgettype() == "Desktop" )
        {
            xpos = parent->getuseablexpos();

            if (dynamic_cast<DesktopWidget*>(parent)->getmenubar() == true)
            {
                ypos = parent->getuseableypos()-20;  // -12-20
            }
            else
            {
                ypos = parent->getuseableypos()-20; //-20
            }

            width = parent->getuseablewidth();
            height = 20;
        }
        else if (parent->getwidgettype() == "Window" )
        {
            xpos = parent->getuseablexpos();

            if (dynamic_cast<WindowWidget*>(parent)->getmenubar() == true)
            {
                ypos = parent->getuseableypos()-20; //-12-20
            }
            else
            {
                ypos = parent->getuseableypos()-20; //-20
            }
            width = parent->getuseablewidth();
            height = 20;
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
        c->setdimensions( xpos+1 + 22*i, ypos, 20, 20 );
        i++;
    }

    for (auto& c : children )
        c->adjust();

}



void IconBarWidget::logic( CursorTask *mouse, KeyboardTask *keyboard )
{
    if (is_enabled && is_visible)
    {
        for (auto& c : children )
            c->logic( mouse, keyboard );
    }
}



void IconBarWidget::render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts )
{
    if (is_visible)
    {
        if (is_enabled)
        {
            boxRGBA( screen, xpos, ypos, xpos+width, ypos+height, colors->widget_filling_enable.R, colors->widget_filling_enable.G, colors->widget_filling_enable.B, colors->widget_filling_enable.A);

            if (!is_hovering)
            {
                lineRGBA( screen, xpos, ypos+height, xpos+width, ypos+height, colors->widget_border_enable.R, colors->widget_border_enable.G, colors->widget_border_enable.B, colors->widget_border_enable.A);
            }
            else
            {
                lineRGBA( screen, xpos, ypos+height, xpos+width, ypos+height, colors->widget_border_cursoron.R, colors->widget_border_cursoron.G, colors->widget_border_cursoron.B, colors->widget_border_cursoron.A);
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

#include "MenuBarWidget.h"

#include "WindowWidget.h"
#include "DesktopWidget.h"

MenuBarWidget::MenuBarWidget() : ContainerHWidget ()
{
    widgettype = (char*) "MenuBar";
};


MenuBarWidget::MenuBarWidget(char *l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : ContainerHWidget( l, x, y, w, h, p )
{
    widgettype = (char*) "MenuBar";

    label=l;
    xrel=x;
    yrel=y;
    widrel=w;
    heirel=h;
    parent=p;

    if (parent)
    {
        if (parent->getwidgettype() == (char*) "Desktop")
        {
            xpos = 0;
            ypos = 0;
            width = SCREEN_WIDTH;
            height = 12;

            dynamic_cast<DesktopWidget*>(parent)->setmenubar();

        }
        else if (parent->getwidgettype() == (char*) "Window")
        {
            xpos = parent->getuseablexpos();
            ypos = parent->getuseableypos();
            width = parent->getuseablewidth();
            height = 12;

            dynamic_cast<WindowWidget*>(parent)->setmenubar();
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

};

MenuBarWidget::~MenuBarWidget()
{
    //dtor
}




void MenuBarWidget::adjust()
{

    if (parent)
    {
        if (parent->getwidgettype() == (char*) "Desktop")
        {
            xpos = 0;
            ypos = 0;
            width = SCREEN_WIDTH;
            height = 12;
        }
        else if (parent->getwidgettype() == (char*) "Window")
        {
            xpos = parent->getuseablexpos();
            ypos = parent->getuseableypos();
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

        }
        else
        {
            boxRGBA( screen, xpos, ypos, xpos+width, ypos+height, colors->widget_filling_disable.R, colors->widget_filling_disable.G, colors->widget_filling_disable.B, colors->widget_filling_disable.A);
        }

        for (auto& c : children )
            c->render( screen, colors, fonts );

    }
}

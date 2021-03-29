#include "WindowWidget.h"



unsigned int WindowWidget::getuseablexpos()
{
    return xpos + 2;
}


unsigned int WindowWidget::getuseableypos()
{
    return ypos + 14;
}


unsigned int WindowWidget::getuseablewidth()
{
    return width - 4;
}


unsigned int WindowWidget::getuseableheight()
{
    return height - 16;
}


bool WindowWidget::ismouseatleftborder(CursorTask *mouse)
{
    return ((unsigned int) mouse->x >= xpos-2) && ((unsigned int) mouse->y >= ypos+2) && ((unsigned int) mouse->x <= xpos+2) && ((unsigned int) mouse->y <= ypos+height-2);
}


bool WindowWidget::ismouseatrightborder(CursorTask *mouse)
{
    return ((unsigned int) mouse->x >= xpos+width-2) && ((unsigned int) mouse->y >= ypos+2) && ((unsigned int) mouse->x <= xpos+width+2) && ((unsigned int) mouse->y <= ypos+height-2);
}


bool WindowWidget::ismouseattopborder(CursorTask *mouse)
{
    return ((unsigned int) mouse->x >= xpos+2) && ((unsigned int) mouse->y >= ypos-2) && ((unsigned int) mouse->x <= xpos+width-2) && ((unsigned int) mouse->y <= ypos+2);
}


bool WindowWidget::ismouseatbottomborder(CursorTask *mouse)
{
    return ((unsigned int) mouse->x >= xpos+2) && ((unsigned int) mouse->y >= ypos+height-2) && ((unsigned int) mouse->x <= xpos+width-2) && ((unsigned int) mouse->y <= ypos+height+2);
}


bool WindowWidget::ismouseontitlebar(CursorTask *mouse)
{
    return ((unsigned int) mouse->x >= xpos+2) && ((unsigned int) mouse->y >= ypos+2) && ((unsigned int) mouse->x <= xpos+width-2) && ((unsigned int) mouse->y <= ypos+12);
}


void WindowWidget::logic( CursorTask *mouse, KeyboardTask *keyboard )
{

    is_hovering = cursoron( mouse );

    if(is_hovering)
    {
        if (hoverfunction)
            hoverfunction( (char*) "test" );
    }

    bool atborder = false;
    bool ontitle = false;

    if (ismouseatleftborder( mouse ))
    {
        mouse->setcursortype( CursorTask::leftrightresize );
        atborder = true;
    }
    else if (ismouseatrightborder( mouse ))
    {
        mouse->setcursortype( CursorTask::leftrightresize );
        atborder = true;
    }
    else if (ismouseattopborder( mouse ))
    {
        mouse->setcursortype( CursorTask::topbottomresize );
        atborder = true;
    }
    else if (ismouseatbottomborder( mouse ))
    {
        mouse->setcursortype( CursorTask::topbottomresize );
        atborder = true;
    }
    else if (ismouseontitlebar( mouse ))
    {
        mouse->setcursortype( CursorTask::roundclock );
        ontitle = true;
    }
    else
    {
        mouse->setcursortype( CursorTask::triangle );
    }


    if (atborder && keyboard->kbSCRATCH)
    {
        resizemode = true;
    }
    else
    {
        resizemode = false;
    }

    if (ontitle && keyboard->kbSCRATCH && !startmove)
    {
        movemode = true;
        startmove = true;
        clickX = mouse->x;
        clickY = mouse->y;
    }
    else if (ontitle && keyboard->kbSCRATCH && startmove)
    {
        movemode = true;
    }
    else
    {
        movemode = false;
        startmove = false;
    }


    if (resizemode && ismouseatleftborder( mouse ))
    {
        unsigned int xposold = xpos;
        mouse->logic();
        xpos = mouse->x;
        width += (xposold - xpos);
        adjust();
    }

    if (resizemode && ismouseatrightborder( mouse ))
    {
        mouse->logic();
        width = mouse->x - xpos;
        adjust();
    }

    if (resizemode && ismouseattopborder( mouse ))
    {
        unsigned int yposold = ypos;
        mouse->logic();
        ypos = mouse->y;
        height += (yposold - ypos);
        adjust();
    }

    if (resizemode && ismouseatbottomborder( mouse ))
    {
        height = mouse->y - ypos;
        mouse->logic();
        adjust();
    }


    // Here comes the move logic ...
    // How can we
    if (movemode && ismouseontitlebar( mouse ))
    {
        mouse->logic();
        xpos += mouse->x - clickX;
        ypos += mouse->y - clickY;
        adjust();
    }




    for (auto& c : children )
        c->logic( mouse, keyboard );


    for (auto& d : popupchildren )
    {
        if (d->isvisible())
            d->logic( mouse, keyboard );
    }

}


void WindowWidget::render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts )
{

    if (is_visible)
    {

        if (is_enabled)
        {
            roundedBoxRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_filling_enable.R, colors->widget_filling_enable.G, colors->widget_filling_enable.B, colors->widget_filling_enable.A);
            roundedBoxRGBA( screen, xpos, ypos, xpos+width, ypos+12, 3, colors->window_titlebar_enable.R, colors->window_titlebar_enable.G, colors->window_titlebar_enable.B, colors->window_titlebar_enable.A);

            if (!is_hovering)
            {
                roundedRectangleRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_border_enable.R, colors->widget_border_enable.G, colors->widget_border_enable.B, colors->widget_border_enable.A);
            }
            else
            {
                roundedRectangleRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_border_cursoron.R, colors->widget_border_cursoron.G, colors->widget_border_cursoron.B, colors->widget_border_cursoron.A);
            }

            fonts->setcurrentfont( fonts->window_titlebartext_enable.name );
            fonts->setmodifiertypo( fonts->window_titlebartext_enable.typo );
            fonts->setmodifierunder( fonts->window_titlebartext_enable.under );
            fonts->setmodifierstrike( fonts->window_titlebartext_enable.strike );

            int sl = fonts->getstringwidth( label );
            int sh = fonts->getstringheight( label );

            fonts->drawstringleft( screen, label, xpos+(width-sl)/2, ypos+sh/2, colors->window_titlebartext_enable.R, colors->window_titlebartext_enable.G, colors->window_titlebartext_enable.B, colors->window_titlebartext_enable.A );
        }
        else
        {
            roundedBoxRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_filling_disable.R, colors->widget_filling_disable.G, colors->widget_filling_disable.B, colors->widget_filling_disable.A);
            roundedBoxRGBA( screen, xpos, ypos, xpos+width, ypos+12, 3, colors->window_titlebar_disable.R, colors->window_titlebar_disable.G, colors->window_titlebar_disable.B, colors->window_titlebar_disable.A);
            roundedRectangleRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_border_disable.R, colors->widget_border_disable.G, colors->widget_border_disable.B, colors->widget_border_disable.A);

            fonts->setcurrentfont( fonts->window_titlebartext_disable.name );
            fonts->setmodifiertypo( fonts->window_titlebartext_disable.typo );
            fonts->setmodifierunder( fonts->window_titlebartext_disable.under );
            fonts->setmodifierstrike( fonts->window_titlebartext_disable.strike );


            int sl = fonts->getstringwidth( label );
            int sh = fonts->getstringheight( label );

            fonts->drawstringleft( screen, label, xpos+(width-sl)/2, ypos+sh/2, colors->window_titlebartext_disable.R, colors->window_titlebartext_disable.G, colors->window_titlebartext_disable.B, colors->window_titlebartext_disable.A );
        }

        for (auto& c : children )
            c->render( screen, colors, fonts );

        for (auto& d : popupchildren )
        {
            if (d->isvisible())
                d->render( screen, colors, fonts );
        }
    }

}

/*
bool WindowWidget::cursoron( CursorTask *mouse )
{
    return (mouse->x >= xpos) && (mouse->y >= ypos) && (mouse->x <= xpos+width) && (mouse->y <= ypos+height);
}
*/

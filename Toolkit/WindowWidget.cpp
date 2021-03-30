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
    return ((unsigned int) mouse->x >= xpos+12) && ((unsigned int) mouse->y >= ypos+2) && ((unsigned int) mouse->x <= xpos+width-22) && ((unsigned int) mouse->y <= ypos+12);
}


bool WindowWidget::ismouseonmaximisebutton(CursorTask *mouse)
{
    return ((unsigned int) mouse->x >= xpos+2) && ((unsigned int) mouse->y >= ypos+2) && ((unsigned int) mouse->x <= xpos+12) && ((unsigned int) mouse->y <= ypos+12);
}


bool WindowWidget::ismouseonminimisebutton(CursorTask *mouse)
{
    return ((unsigned int) mouse->x >= xpos+width-12) && ((unsigned int) mouse->y >= ypos+2) && ((unsigned int) mouse->x <= xpos+width-2) && ((unsigned int) mouse->y <= ypos+12);
}


bool WindowWidget::ismouseonrestorebutton(CursorTask *mouse)
{
    return ((unsigned int) mouse->x >= xpos+width-22) && ((unsigned int) mouse->y >= ypos+2) && ((unsigned int) mouse->x <= xpos+width-12) && ((unsigned int) mouse->y <= ypos+12);
}

void WindowWidget::maximize()
{
    if (ismaximized)
    {
        xpos = xposback;
        ypos = yposback;
        width = widthback;
        height = heightback;

        for (auto& c : children )
            c->setvisible();

        ismaximized = false;
        isminimized = false;

        adjust();
    }
    else
    {
        xposback = xpos;
        yposback = ypos;
        widthback = width;
        heightback = height;

        xpos = 0;
        ypos = 0;
        width = SCREEN_WIDTH;
        height = SCREEN_HEIGHT;

        for (auto& c : children )
            c->setvisible();

        ismaximized = true;
        isminimized = false;

        adjust();
    }
}

void WindowWidget::minimize()
{
    if (isminimized)
    {
        xpos = xposback;
        ypos = yposback;
        width = widthback;
        height = heightback;

        for (auto& c : children )
            c->setvisible();

        ismaximized = false;
        isminimized = false;

        adjust();
    }
    else
    {
        xposback = xpos;
        yposback = ypos;
        widthback = width;
        heightback = height;

        xpos = 0;
        ypos = 0;
        width = SCREEN_WIDTH;
        height = 12;

         for (auto& c : children )
            c->setinvisible();

        ismaximized = false;
        isminimized = true;

        adjust();
    }
}

void WindowWidget::restore()
{
    if (!ismaximized && !isminimized)
    {
        xposback = xpos;
        yposback = ypos;
        widthback = width;
        heightback = height;
    }
    else
    {
            xpos = xposback;
        ypos = yposback;
        width = widthback;
        height = heightback;

        for (auto& c : children )
            c->setvisible();

        ismaximized = false;
        isminimized = false;

        adjust();
    }
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
    bool onmax = false;
    bool onmin = false;
    bool onres = false;

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
        mouse->setcursortype( CursorTask::handfinger );
        ontitle = true;
    }
    else if (ismouseonmaximisebutton( mouse ))
    {
        mouse->setcursortype( CursorTask::triangle );
        onmax = true;
    }
    else if (ismouseonminimisebutton( mouse ))
    {
        mouse->setcursortype( CursorTask::triangle );
        onmin = true;
    }
    else if (ismouseonrestorebutton( mouse ))
    {
        mouse->setcursortype( CursorTask::triangle );
        onres = true;
    }
    else
    {
        mouse->setcursortype( CursorTask::pointer );
    }


    if (atborder && keyboard->kbSCRATCH)
    {
        resizemode = true;
    }
    else
    {
        resizemode = false;
    }

    if (onmax && keyboard->kbSCRATCH)
    {
        maximize();
        onmax = false;
    }

    if (onmin && keyboard->kbSCRATCH)
    {
        minimize();
        onmin = false;
    }

    if (onres && keyboard->kbSCRATCH)
    {
        restore();
        onres = false;
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
        if (mouse->x > 2) xpos = mouse->x;
        width += (xposold - xpos);
        adjust();
    }

    if (resizemode && ismouseatrightborder( mouse ))
    {
        mouse->logic();
        if (mouse->x < SCREEN_WIDTH-2) width = mouse->x - xpos;
        adjust();
    }

    if (resizemode && ismouseattopborder( mouse ))
    {
        unsigned int yposold = ypos;
        mouse->logic();
        if (mouse->y > 2) ypos = mouse->y;
        height += (yposold - ypos);
        adjust();
    }

    if (resizemode && ismouseatbottomborder( mouse ))
    {
        height = mouse->y - ypos;
        if (mouse->y < SCREEN_HEIGHT-2) mouse->logic();
        adjust();
    }


    // Here comes the move logic ...
    if (movemode && ismouseontitlebar( mouse ))
    {
        mouse->logic();

        int deltax = (int) mouse->x - (int) clickX;
        int deltay = (int) mouse->y - (int) clickY;

        //we go left
        if (deltax < 0)
        {
            if ((int) xpos > (int) (-1 * deltax))   xpos += deltax;
        }
        //we go up
        if (deltay < 0)
        {
            if ((int) ypos > (int) (-1 * deltay))   ypos += deltay;
        }

        //we go right
        if (deltax > 0)
        {
            if ((int) (SCREEN_WIDTH - xpos - width) > (int) (deltax))   xpos += deltax;
        }
        //we go down
        if (deltay > 0)
        {
            if ((int) (SCREEN_HEIGHT - ypos - height) > (int) (deltay))   ypos += deltay;
        }

        adjust();

        clickX = mouse->x;
        clickY = mouse->y;

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

            filledCircleRGBA( screen, xpos+7, ypos+6, 4, 0, 255, 0, 255 );
            filledCircleRGBA( screen, xpos+width-7, ypos+6, 4, 255, 0, 0, 255 );
            filledCircleRGBA( screen, xpos+width-17, ypos+6, 4, 255, 125, 0, 255 );

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

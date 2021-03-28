#include "MiniButtonWidget.h"




void MiniButtonWidget::settype( typesymbol type )
{
    switch(type)
    {
    case Bottom_Arrow:
        label = (char*) "\u001f";
        break;
    case Up_Arrow:
        label = (char*) "\u001e";
        break;
    case Left_Arrow:
        label = (char*) "\u0011";
        break;
    case Right_Arrow:
        label = (char*) "\u0010";
        break;
    case Close_Symbol:
        label = (char*) "\u0009";
        break;
    case Question_Symbol:
        label = (char*) "\u003f";
        break;
    case Exclamation_Symbol:
        label = (char*) "\u0021";
        break;
    }
}


bool MiniButtonWidget::ispressed()
{
    return is_pressed;
}

void MiniButtonWidget::logic( CursorTask *mouse, KeyboardTask *keyboard )
{
    if (is_enabled && is_visible)
    {
        is_hovering = cursoron( mouse );
        bool currently_pressed = mouse->state && is_hovering;

        if(mouse_hold_down)
        {
            mouse_hold_down = currently_pressed;
        }
        else if (currently_pressed && !is_ticked )
        {
            invert();

            if (clickfunction)
                clickfunction( (char*) "test" );

            mouse_hold_down = true;
        }
        else if (currently_pressed && is_ticked )
        {
            invert();

            if (releasefunction)
                releasefunction( (char*) "test" );

            mouse_hold_down = true;
        }
        else if (is_hovering)
        {
            if (hoverfunction)
                hoverfunction( (char*) "test" );
        }

        for (auto& c : children )
            c->logic( mouse, keyboard );
    }

/*    if (is_enabled && is_visible)
    {

        is_hovering = cursoron( mouse );
        bool currently_pressed = mouse->state && is_hovering;


        if(currently_pressed && !is_pressed)
        {
            if (clickfunction)
                clickfunction( (char*) "test" );
        }
        else if(!currently_pressed && is_pressed)
        {
            if (releasefunction)
                releasefunction( (char*) "test" );
        }
        else if(is_hovering)
        {
            if (hoverfunction)
                hoverfunction( (char*) "test" );
        }

        is_pressed = currently_pressed;

        for (auto& c : children )
            c->logic( mouse, keyboard );
    }
*/
}


void MiniButtonWidget::render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts )
{
    if (is_visible)
    {

        if (is_enabled)
        {
            roundedBoxRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_filling_enable.R, colors->widget_filling_enable.G, colors->widget_filling_enable.B, colors->widget_filling_enable.A);

            if (!is_hovering)
            {
                roundedRectangleRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_border_enable.R, colors->widget_border_enable.G, colors->widget_border_enable.B, colors->widget_border_enable.A);
            }
            else if (is_pressed)
            {
                roundedRectangleRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, 0, 0, 255, 0);
            }
            else
            {
                roundedRectangleRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_border_cursoron.R, colors->widget_border_cursoron.G, colors->widget_border_cursoron.B, colors->widget_border_cursoron.A);
            }

            fonts->setcurrentfont( fonts->widget_text_enable.name );
            fonts->setmodifiertypo( fonts->widget_text_enable.typo );
            fonts->setmodifierunder( fonts->widget_text_enable.under );
            fonts->setmodifierstrike( fonts->widget_text_enable.strike );

            int sl = fonts->getstringwidth( label );
            int sh = fonts->getstringheight( label );

            fonts->drawstringleft( screen, label, xpos+(width-sl)/2, ypos+(height-sh)/2, colors->widget_text_enable.R, colors->widget_text_enable.G, colors->widget_text_enable.B, colors->widget_text_enable.A );
        }
        else
        {
            roundedBoxRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_filling_disable.R, colors->widget_filling_disable.G, colors->widget_filling_disable.B, colors->widget_filling_disable.A);
            //Border of the button is black cause it is disabled
            roundedRectangleRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_border_disable.R, colors->widget_border_disable.G, colors->widget_border_disable.B, colors->widget_border_disable.A);

            fonts->setcurrentfont( fonts->widget_text_disable.name );
            fonts->setmodifiertypo( fonts->widget_text_disable.typo );
            fonts->setmodifierunder( fonts->widget_text_disable.under );
            fonts->setmodifierstrike( fonts->widget_text_disable.strike );

            int sl = fonts->getstringwidth( label );
            int sh = fonts->getstringheight( label );

            fonts->drawstringleft( screen, label, xpos+(width-sl)/2, ypos+(height-sh)/2, colors->widget_text_disable.R, colors->widget_text_disable.G, colors->widget_text_disable.B, colors->widget_text_disable.A );
        }

        for (auto& c : children )
            c->render( screen, colors, fonts );

    }
}

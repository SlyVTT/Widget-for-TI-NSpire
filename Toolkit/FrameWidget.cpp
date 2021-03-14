#include "FrameWidget.h"



int FrameWidget::getuseablexpos()
{
 return xpos + 2;
}


int FrameWidget::getuseableypos()
{
 return ypos + 14;
}


int FrameWidget::getuseablewidth()
{
 return width - 4;
}


int FrameWidget::getuseableheight()
{
 return height - 16;
}


void FrameWidget::logic( CursorTask *mouse, KeyboardTask *keyboard )
{
    if (is_enabled && is_visible)
    {

        is_hovering = cursoron( mouse );
        bool currently_pressed = mouse->state && is_hovering;


        if(currently_pressed && !is_pressed)
        {
            if (clickfunction)
                clickfunction( "test" );
        }
        else if(!currently_pressed && is_pressed)
        {
            if (releasefunction)
                releasefunction( "test" );
        }
        else if(is_hovering)
        {
            if (hoverfunction)
                hoverfunction( "test" );
        }

        is_pressed = currently_pressed;

        for (auto& c : children )
            c->logic( mouse, keyboard );
    }
}

void FrameWidget::render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts )
{
    if (is_visible)
    {



        if (is_enabled)
        {
            roundedBoxRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_filling_enable.R, colors->widget_filling_enable.G, colors->widget_filling_enable.B, colors->widget_filling_enable.A);

            fonts->setcurrentfont( THIN_FONT );
            fonts->setmodifiertypo( Normal );

            int sl = fonts->getstringwidth( label );
            int sh = fonts->getstringheight( label );

            if (!is_hovering)
            {
                roundedRectangleRGBA( screen, xpos, ypos+sh, xpos+width, ypos+height, 3, colors->widget_border_enable.R, colors->widget_border_enable.G, colors->widget_border_enable.B, colors->widget_border_enable.A);
            }
            else
            {
                roundedRectangleRGBA( screen, xpos, ypos+sh, xpos+width, ypos+height, 3, colors->widget_border_cursoron.R, colors->widget_border_cursoron.G, colors->widget_border_cursoron.B, colors->widget_border_cursoron.A);
            }

            boxRGBA( screen, xpos+3, ypos, xpos+3+sl, ypos+sh, colors->widget_filling_enable.R, colors->widget_filling_enable.G, colors->widget_filling_enable.B, colors->widget_filling_enable.A);

            fonts->drawstringleft( screen, label, xpos+3 , ypos+sh/2, colors->widget_text_enable.R, colors->widget_text_enable.G, colors->widget_text_enable.B, colors->widget_text_enable.A );

        }
        else
        {
            roundedBoxRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_filling_disable.R, colors->widget_filling_disable.G, colors->widget_filling_disable.B, colors->widget_filling_disable.A);

            fonts->setcurrentfont( THIN_FONT );
            fonts->setmodifiertypo( Normal );

            int sl = fonts->getstringwidth( label );
            int sh = fonts->getstringheight( label );

            //Border of the button is black cause it is disabled
            roundedRectangleRGBA( screen, xpos, ypos+sh, xpos+width, ypos+height, 3, colors->widget_border_disable.R, colors->widget_border_disable.G, colors->widget_border_disable.B, colors->widget_border_disable.A);

            boxRGBA( screen, xpos+3, ypos, xpos+3+sl, ypos+sh, colors->widget_filling_disable.R, colors->widget_filling_disable.G, colors->widget_filling_disable.B, colors->widget_filling_disable.A);

            fonts->drawstringleft( screen, label, xpos+3 , ypos+sh/2, colors->widget_text_disable.R, colors->widget_text_disable.G, colors->widget_text_disable.B, colors->widget_text_disable.A );
        }

        for (auto& c : children )
            c->render( screen, colors, fonts );

    }
}
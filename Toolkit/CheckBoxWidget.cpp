#include "CheckBoxWidget.h"


void CheckBoxWidget::logic( CursorTask *mouse, KeyboardTask *keyboard )
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
                clickfunction( "test" );

            mouse_hold_down = true;
        }
        else if (currently_pressed && is_ticked )
        {
            invert();

            if (releasefunction)
                releasefunction( "test" );

            mouse_hold_down = true;
        }
        else if (is_hovering)
        {
            if (hoverfunction)
                hoverfunction( "test" );
        }

        for (auto& c : children )
            c->logic( mouse, keyboard );
    }
}

void CheckBoxWidget::render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts )
{
    if (is_visible)
    {

        if (is_enabled)
        {
            roundedBoxRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_filling_enable.R, colors->widget_filling_enable.G, colors->widget_filling_enable.B, colors->widget_filling_enable.A);

            if (!is_hovering)
            {
                roundedRectangleRGBA( screen, xpos, ypos+height/2-6, xpos+12, ypos+height/2+6, 3, colors->widget_border_enable.R, colors->widget_border_enable.G, colors->widget_border_enable.B, colors->widget_border_enable.A);
            }
            else
            {
                roundedRectangleRGBA( screen, xpos, ypos+height/2-6, xpos+12, ypos+height/2+6, 3, colors->widget_border_cursoron.R, colors->widget_border_cursoron.G, colors->widget_border_cursoron.B, colors->widget_border_cursoron.A);
            }


            fonts->setcurrentfont( THIN_FONT );
            fonts->setmodifiertypo( Normal );

            int sl = fonts->getstringwidth( label );
            int sh = fonts->getstringheight( label );

            fonts->drawstringleft( screen, label, xpos+15 , ypos+(height-sh)/2, colors->widget_text_enable.R, colors->widget_text_enable.G, colors->widget_text_enable.B, colors->widget_text_enable.A );


            if (is_ticked && (typetick == Square_Tick ))
            {
                roundedBoxRGBA( screen, xpos+3, ypos+height/2-3, xpos+9, ypos+height/2+3, 1, colors->widget_tickmark_enable.R, colors->widget_tickmark_enable.G, colors->widget_tickmark_enable.B, colors->widget_tickmark_enable.A);
            }
            else if (is_ticked && (typetick == Cross_Tick ))
            {
                lineRGBA( screen, xpos+3, ypos+height/2-3, xpos+9, ypos+height/2+3, colors->widget_tickmark_enable.R, colors->widget_tickmark_enable.G, colors->widget_tickmark_enable.B, colors->widget_tickmark_enable.A);
                lineRGBA( screen, xpos+4, ypos+height/2-3, xpos+9, ypos+height/2+2, colors->widget_tickmark_enable.R, colors->widget_tickmark_enable.G, colors->widget_tickmark_enable.B, colors->widget_tickmark_enable.A);
                lineRGBA( screen, xpos+3, ypos+height/2-2, xpos+8, ypos+height/2+3, colors->widget_tickmark_enable.R, colors->widget_tickmark_enable.G, colors->widget_tickmark_enable.B, colors->widget_tickmark_enable.A);

                lineRGBA( screen, xpos+3, ypos+height/2+3, xpos+9, ypos+height/2-3, colors->widget_tickmark_enable.R, colors->widget_tickmark_enable.G, colors->widget_tickmark_enable.B, colors->widget_tickmark_enable.A);
                lineRGBA( screen, xpos+3, ypos+height/2+2, xpos+8, ypos+height/2-3, colors->widget_tickmark_enable.R, colors->widget_tickmark_enable.G, colors->widget_tickmark_enable.B, colors->widget_tickmark_enable.A);
                lineRGBA( screen, xpos+4, ypos+height/2+3, xpos+9, ypos+height/2-2, colors->widget_tickmark_enable.R, colors->widget_tickmark_enable.G, colors->widget_tickmark_enable.B, colors->widget_tickmark_enable.A);
            }
        }
        else
        {
            roundedBoxRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_filling_disable.R, colors->widget_filling_disable.G, colors->widget_filling_disable.B, colors->widget_filling_disable.A);

            roundedRectangleRGBA( screen, xpos, ypos+height/2-6, xpos+12, ypos+height/2+6, 3, colors->widget_border_disable.R, colors->widget_border_disable.G, colors->widget_border_disable.B, colors->widget_border_disable.A);

            fonts->setcurrentfont( THIN_FONT );
            fonts->setmodifiertypo( Normal );

            int sl = fonts->getstringwidth( label );
            int sh = fonts->getstringheight( label );

            fonts->drawstringleft( screen, label, xpos+15 , ypos+(height-sh)/2, colors->widget_text_disable.R, colors->widget_text_disable.G, colors->widget_text_disable.B, colors->widget_text_disable.A );


            if (is_ticked && (typetick == Square_Tick ))
            {
                roundedBoxRGBA( screen, xpos+3, ypos+height/2-3, xpos+9, ypos+height/2+3, 1, colors->widget_tickmark_disable.R, colors->widget_tickmark_disable.G, colors->widget_tickmark_disable.B, colors->widget_tickmark_disable.A);
            }
            else if (is_ticked && (typetick == Cross_Tick ))
            {
                lineRGBA( screen, xpos+3, ypos+height/2-3, xpos+9, ypos+height/2+3, colors->widget_tickmark_disable.R, colors->widget_tickmark_disable.G, colors->widget_tickmark_disable.B, colors->widget_tickmark_disable.A);
                lineRGBA( screen, xpos+4, ypos+height/2-3, xpos+9, ypos+height/2+2, colors->widget_tickmark_disable.R, colors->widget_tickmark_disable.G, colors->widget_tickmark_disable.B, colors->widget_tickmark_disable.A);
                lineRGBA( screen, xpos+3, ypos+height/2-2, xpos+8, ypos+height/2+3, colors->widget_tickmark_disable.R, colors->widget_tickmark_disable.G, colors->widget_tickmark_disable.B, colors->widget_tickmark_disable.A);

                lineRGBA( screen, xpos+3, ypos+height/2+3, xpos+9, ypos+height/2-3, colors->widget_tickmark_disable.R, colors->widget_tickmark_disable.G, colors->widget_tickmark_disable.B, colors->widget_tickmark_disable.A);
                lineRGBA( screen, xpos+3, ypos+height/2+2, xpos+8, ypos+height/2-3, colors->widget_tickmark_disable.R, colors->widget_tickmark_disable.G, colors->widget_tickmark_disable.B, colors->widget_tickmark_disable.A);
                lineRGBA( screen, xpos+4, ypos+height/2+3, xpos+9, ypos+height/2-2, colors->widget_tickmark_disable.R, colors->widget_tickmark_disable.G, colors->widget_tickmark_disable.B, colors->widget_tickmark_disable.A);
            }

        }




        for (auto& c : children )
            c->render( screen, colors, fonts );

    }
}
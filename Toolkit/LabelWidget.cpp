#include "LabelWidget.h"



void LabelWidget::logic( CursorTask *mouse, KeyboardTask *keyboard )
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

void LabelWidget::render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts )
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

            if (alignment==centered) fonts->drawstringleft( screen, label, xpos+(width-sl)/2 , ypos+(height-sh)/2, colors->widget_text_enable.R, colors->widget_text_enable.G, colors->widget_text_enable.B, colors->widget_text_enable.A );

            if (alignment==left) fonts->drawstringleft( screen, label, xpos, ypos+(height-sh)/2, colors->widget_text_enable.R, colors->widget_text_enable.G, colors->widget_text_enable.B, colors->widget_text_enable.A );

            if (alignment==right) fonts->drawstringleft( screen, label, xpos+(width-sl), ypos+(height-sh)/2, colors->widget_text_enable.R, colors->widget_text_enable.G, colors->widget_text_enable.B, colors->widget_text_enable.A );
        }
        else
        {
            roundedBoxRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_filling_disable.R, colors->widget_filling_disable.G, colors->widget_filling_disable.B, colors->widget_filling_disable.A);

            fonts->setcurrentfont( THIN_FONT );
            fonts->setmodifiertypo( Normal );

            int sl = fonts->getstringwidth( label );
            int sh = fonts->getstringheight( label );

            if (alignment==centered) fonts->drawstringleft( screen, label, xpos+(width-sl)/2 , ypos+(height-sh)/2, colors->widget_text_disable.R, colors->widget_text_disable.G, colors->widget_text_disable.B, colors->widget_text_disable.A );

            if (alignment==left) fonts->drawstringleft( screen, label, xpos, ypos+(height-sh)/2, colors->widget_text_disable.R, colors->widget_text_disable.G, colors->widget_text_disable.B, colors->widget_text_disable.A );

            if (alignment==right) fonts->drawstringleft( screen, label, xpos+(width-sl), ypos+(height-sh)/2, colors->widget_text_disable.R, colors->widget_text_disable.G, colors->widget_text_disable.B, colors->widget_text_disable.A );

        }

        for (auto& c : children )
            c->render( screen, colors, fonts );

    }
}

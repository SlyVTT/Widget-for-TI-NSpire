#include "MultiLineTextBoxWidget.h"

extern "C" char nio_ascii_get(int *a);



void MultiLineTextBoxWidget::logic( CursorTask *mouse, KeyboardTask *keyboard )
{

    if (is_enabled && is_visible)
    {
        is_hovering = cursoron( mouse );
        mousex=mouse->x;
        mousey=mouse->y;
        mouses=mouse->state;

        if(is_hovering)
        {
            if (hoverfunction)
                hoverfunction( (char*) "test" );
        }

        if ( is_hovering && (mouse->state || keyboard->kbSCRATCH) && !has_focus )
        {
            focus( this );
        }

        if( (mouse->state || keyboard->kbSCRATCH) && is_hovering )
        {
            nfontwidget->setcurrentfont( nfontwidget->widget_text_disable.name );
            nfontwidget->setmodifiertypo( nfontwidget->widget_text_disable.typo );
            nfontwidget->setmodifierunder( nfontwidget->widget_text_disable.under );
            nfontwidget->setmodifierstrike( nfontwidget->widget_text_disable.strike );

            unsigned int x_rel = mousex - xpos - 2;
            const char *str = text.c_str() + scrollX;
            unsigned int pos = scrollX;

            while(x_rel > 0 && *str)
            {
                unsigned int temp = nfontwidget->getcharwidth( (char) *str++ );
                x_rel -= temp;
                ++pos;
            }

            cursor_posX = pos;

        }

        if(!has_focus)
            return;

        int i;
        char c = nio_ascii_get(&i);
        if(c >= 0x80 || c == '\n')
            return;


        if (key_hold_down)
        {
            key_hold_down = any_key_pressed();
        }
        else if (isKeyPressed(KEY_NSPIRE_CTRL) && isKeyPressed(KEY_NSPIRE_LEFT))
        {
            cursor_posX = 0;
            updateScroll();
        }
        else if (isKeyPressed(KEY_NSPIRE_CTRL) && isKeyPressed(KEY_NSPIRE_RIGHT))
        {
            cursor_posX = text.length();
            updateScroll();
        }
        else if(isKeyPressed(KEY_NSPIRE_LEFT))
        {
            if(cursor_posX > 0) --cursor_posX;
            updateScroll();
        }
        else if(isKeyPressed(KEY_NSPIRE_RIGHT))
        {
            if(cursor_posX < text.length()) ++cursor_posX;
            updateScroll();
        }

        static char old_char = 0;
        if(c != old_char && c != 0)
        {
            if(c == '\b')
            {
                if(cursor_posX > 0)
                {
                    text.erase(text.begin() + (cursor_posX - 1));
                    --cursor_posX;

                    updateScroll();
                }
            }
            else
            {
                text.insert(text.begin() + cursor_posX, c);
                ++cursor_posX;

                updateScroll();
            }
        }

        old_char = c;

        if(!any_key_pressed())
        {
            old_char = 0;
        }

        for (auto& c : children )
            c->logic( mouse, keyboard );

    }
}


void MultiLineTextBoxWidget::render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts )
{
    if (is_visible)
    {

        // if the current font has not been defined for the widget, we use the current fontengine
        if (nfontwidget ==nullptr)
            nfontwidget = fonts;

        if (is_enabled)
        {
            roundedBoxRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_filling_enable.R, colors->widget_filling_enable.G, colors->widget_filling_enable.B, colors->widget_filling_enable.A);

            if (!is_hovering)
            {
                roundedRectangleRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_border_enable.R, colors->widget_border_enable.G, colors->widget_border_enable.B, colors->widget_border_enable.A);
            }
            else
            {
                roundedRectangleRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_border_cursoron.R, colors->widget_border_cursoron.G, colors->widget_border_cursoron.B, colors->widget_border_cursoron.A);
            }

            const char *str = text.c_str() + scrollX;
            const char *cursor = text.c_str() + cursor_posX;
            unsigned int x1 = xpos + 5;

            fonts->setcurrentfont( fonts->widget_text_enable.name );
            fonts->setmodifiertypo( fonts->widget_text_enable.typo );
            fonts->setmodifierunder( fonts->widget_text_enable.under );
            fonts->setmodifierstrike( fonts->widget_text_enable.strike );
            char* tpstr = (char*) str;
            int sh = fonts->getstringheight( tpstr );

            while(*str && x1 - xpos + fonts->getcharwidth( (char) *str) < width)
            {
                if(has_focus && str == cursor)
                {
                    vlineRGBA( screen, x1, ypos + height/4, ypos + 3*height/4, colors->widget_border_enable.R, colors->widget_border_enable.G, colors->widget_border_enable.B, colors->widget_border_enable.A);
                    vlineRGBA( screen, x1+1, ypos + height/4, ypos + 3*height/4, colors->widget_border_enable.R, colors->widget_border_enable.G, colors->widget_border_enable.B, colors->widget_border_enable.A);
                    x1+=2;
                }

                fonts->drawcharleft( screen, *str, x1, ypos + height/2 - sh/2, colors->widget_text_enable.R, colors->widget_text_enable.G, colors->widget_text_enable.B, colors->widget_text_enable.A );
                x1 += fonts->getcharwidth( (char) *str );

                ++str;
            }

            if(str == cursor)
            {
                vlineRGBA( screen, x1, ypos + height/4, ypos + 3*height/4, colors->widget_border_enable.R, colors->widget_border_enable.G, colors->widget_border_enable.B, colors->widget_border_enable.A);
                vlineRGBA( screen, x1+1, ypos + height/4, ypos + 3*height/4, colors->widget_border_enable.R, colors->widget_border_enable.G, colors->widget_border_enable.B, colors->widget_border_enable.A);
                x1+=2;
            }


        }
        else
        {
            roundedBoxRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_filling_disable.R, colors->widget_filling_disable.G, colors->widget_filling_disable.B, colors->widget_filling_disable.A);

            roundedRectangleRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_border_disable.R, colors->widget_border_disable.G, colors->widget_border_disable.B, colors->widget_border_disable.A);

            const char *str = text.c_str() + scrollX;
            const char *cursor = text.c_str() + cursor_posX;
            unsigned int x1 = xpos + 5;

            fonts->setcurrentfont( fonts->widget_text_disable.name );
            fonts->setmodifiertypo( fonts->widget_text_disable.typo );
            fonts->setmodifierunder( fonts->widget_text_disable.under );
            fonts->setmodifierstrike( fonts->widget_text_disable.strike );

            char* tpstr = (char*) str;
            int sh = fonts->getstringheight( tpstr );


            while(*str && x1 - xpos + fonts->getcharwidth( (char) *str) < width)
            {
                if(has_focus && str == cursor)
                {
                    vlineRGBA( screen, x1, ypos + height/4, ypos + 3*height/4, colors->widget_border_disable.R, colors->widget_border_disable.G, colors->widget_border_disable.B, colors->widget_border_disable.A);
                    vlineRGBA( screen, x1+1, ypos + height/4, ypos + 3*height/4, colors->widget_border_disable.R, colors->widget_border_disable.G, colors->widget_border_disable.B, colors->widget_border_disable.A);
                    x1+=2;
                }

                fonts->drawcharleft( screen, *str, x1, ypos + height/2 - sh/2, colors->widget_text_disable.R, colors->widget_text_disable.G, colors->widget_text_disable.B, colors->widget_text_disable.A );
                x1 += fonts->getcharwidth( (char) *str );

                ++str;
            }

            if(str == cursor)
            {
                vlineRGBA( screen, x1, ypos + height/4, ypos + 3*height/4, colors->widget_border_disable.R, colors->widget_border_disable.G, colors->widget_border_disable.B, colors->widget_border_disable.A);
                vlineRGBA( screen, x1+1, ypos + height/4, ypos + 3*height/4, colors->widget_border_disable.R, colors->widget_border_disable.G, colors->widget_border_disable.B, colors->widget_border_disable.A);
                x1+=2;
            }


        }

        for (auto& c : children )
            c->render( screen, colors, fonts );
    }
}

void MultiLineTextBoxWidget::updateScroll()
{
    if(scrollX != 0 && cursor_posX <= scrollX)
        --scrollX;

    if(cursor_posX <= scrollX)
        return;

    nfontwidget->setcurrentfont( nfontwidget->widget_text_disable.name );
    nfontwidget->setmodifiertypo( nfontwidget->widget_text_disable.typo );
    nfontwidget->setmodifierunder( nfontwidget->widget_text_disable.under );
    nfontwidget->setmodifierstrike( nfontwidget->widget_text_disable.strike );

    const char *str = text.c_str() + scrollX;
    unsigned int cur_x = 0, len = cursor_posX - scrollX;

    while(len--)
        cur_x += nfontwidget->getcharwidth( *str++ );

    if(cur_x >= width - 5)
        ++scrollX;
}

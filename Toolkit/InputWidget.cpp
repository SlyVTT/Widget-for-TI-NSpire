#include "InputWidget.h"

//#include <string>
//#include <libndls.h>
//#include <nucleus.h>


extern "C" char nio_ascii_get(int *a);


int getwidthfont( nSDL_Font *font, char c )
{
    char text[2];
    sprintf( text, "%c", c );
    return nSDL_GetStringWidth( font, text );
}


int drawchar( SDL_Surface * screen, int x, int y, nSDL_Font *font, char c )
{
    int width = getwidthfont( font, c );
    char text[2];
    sprintf( text, "%c", c );

    nSDL_DrawString( screen, font, x, y, text );

    return width;
}


void InputWidget::logic( CursorTask *mouse, KeyboardTask *keyboard )
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

        if ( is_hovering && mouses && !has_focus )
        {
            focus( this );
        }

        if( mouses && is_hovering )
        {
            nSDL_Font *tempfont = nSDL_LoadFont(NSDL_FONT_THIN, 0, 0, 0);

            unsigned int x_rel = mousex - xpos - 2;
            const char *str = text.c_str() + scroll;
            unsigned int pos = scroll;

            while(x_rel > 0 && *str)
            {
                unsigned int temp = getwidthfont( tempfont, (char) *str++);
                x_rel -= temp;
                ++pos;
            }

            cursor_pos = pos;

            nSDL_FreeFont( tempfont );

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
            cursor_pos = 0;
            updateScroll();
        }
        else if (isKeyPressed(KEY_NSPIRE_CTRL) && isKeyPressed(KEY_NSPIRE_RIGHT))
        {
            cursor_pos = text.length();
            updateScroll();
        }
        else if(isKeyPressed(KEY_NSPIRE_LEFT))
        {
            if(cursor_pos > 0) --cursor_pos;
            updateScroll();
        }
        else if(isKeyPressed(KEY_NSPIRE_RIGHT))
        {
            if(cursor_pos < text.length()) ++cursor_pos;
            updateScroll();
        }

        static char old_char = 0;
        if(c != old_char && c != 0)
        {
            if(c == '\b')
            {
                if(cursor_pos > 0)
                {
                    text.erase(text.begin() + (cursor_pos - 1));
                    --cursor_pos;

                    updateScroll();
                }
            }
            else
            {
                text.insert(text.begin() + cursor_pos, c);
                ++cursor_pos;

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


void InputWidget::render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts )
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
            else
            {
                roundedRectangleRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_border_cursoron.R, colors->widget_border_cursoron.G, colors->widget_border_cursoron.B, colors->widget_border_cursoron.A);
            }

            const char *str = text.c_str() + scroll;
            const char *cursor = text.c_str() + cursor_pos;
            unsigned int x1 = xpos + 5;

            nSDL_Font *tempfont = nSDL_LoadFont(NSDL_FONT_THIN, colors->widget_text_enable.R, colors->widget_text_enable.G, colors->widget_text_enable.B);

            int sh = nSDL_GetStringHeight( tempfont, text.c_str() );
            //int dx = 0;



            while(*str && x1 - xpos + getwidthfont( tempfont, (char) *str) < width)
            {
                if(has_focus && str == cursor)
                {
                    vlineRGBA( screen, x1, ypos + height/4, ypos + 3*height/4, colors->widget_border_enable.R, colors->widget_border_enable.G, colors->widget_border_enable.B, colors->widget_border_enable.A);
                    vlineRGBA( screen, x1+1, ypos + height/4, ypos + 3*height/4, colors->widget_border_enable.R, colors->widget_border_enable.G, colors->widget_border_enable.B, colors->widget_border_enable.A);
                    x1+=2;
                }
                //fonts->drawcharleft( screen, *str, x1, ypos + height/2 - sh/2, colors->widget_text_enable.R, colors->widget_text_enable.G, colors->widget_text_enable.B, colors->widget_text_enable.A );
                nSDL_DrawString( screen, tempfont, x1, ypos + height/2 - sh/2, "%c", *str );
                x1 += getwidthfont( tempfont, (char) *str );

                ++str;
            }

            if(str == cursor)
            {
                vlineRGBA( screen, x1, ypos + height/4, ypos + 3*height/4, colors->widget_border_enable.R, colors->widget_border_enable.G, colors->widget_border_enable.B, colors->widget_border_enable.A);
                vlineRGBA( screen, x1+1, ypos + height/4, ypos + 3*height/4, colors->widget_border_enable.R, colors->widget_border_enable.G, colors->widget_border_enable.B, colors->widget_border_enable.A);
                x1+=2;
            }

            nSDL_FreeFont( tempfont );



        }
        else
        {
            roundedBoxRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_filling_disable.R, colors->widget_filling_disable.G, colors->widget_filling_disable.B, colors->widget_filling_disable.A);

            roundedRectangleRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_border_disable.R, colors->widget_border_disable.G, colors->widget_border_disable.B, colors->widget_border_disable.A);


            const char *str = text.c_str() + scroll;
            const char *cursor = text.c_str() + cursor_pos;
            unsigned int x1 = xpos + 5;

            nSDL_Font *tempfont = nSDL_LoadFont(NSDL_FONT_THIN, colors->widget_text_disable.R, colors->widget_text_disable.G, colors->widget_text_disable.B);

            int sh = nSDL_GetStringHeight( tempfont, text.c_str() );
            //int dx = 0;



            while(*str && x1 - xpos + getwidthfont( tempfont, (char) *str) < width)
            {
                if(has_focus && str == cursor)
                {
                    vlineRGBA( screen, x1, ypos + height/4, ypos + 3*height/4, colors->widget_border_enable.R, colors->widget_border_enable.G, colors->widget_border_enable.B, colors->widget_border_enable.A);
                    vlineRGBA( screen, x1+1, ypos + height/4, ypos + 3*height/4, colors->widget_border_enable.R, colors->widget_border_enable.G, colors->widget_border_enable.B, colors->widget_border_enable.A);
                    x1+=2;
                }
                //fonts->drawcharleft( screen, *str, x1, ypos + height/2 - sh/2, colors->widget_text_enable.R, colors->widget_text_enable.G, colors->widget_text_enable.B, colors->widget_text_enable.A );
                nSDL_DrawString( screen, tempfont, x1, ypos + height/2 - sh/2, "%c", *str );
                x1 += getwidthfont( tempfont, (char) *str );

                ++str;
            }

            if(str == cursor)
            {
                vlineRGBA( screen, x1, ypos + height/4, ypos + 3*height/4, colors->widget_border_enable.R, colors->widget_border_enable.G, colors->widget_border_enable.B, colors->widget_border_enable.A);
                vlineRGBA( screen, x1+1, ypos + height/4, ypos + 3*height/4, colors->widget_border_enable.R, colors->widget_border_enable.G, colors->widget_border_enable.B, colors->widget_border_enable.A);
                x1+=2;
            }

            nSDL_FreeFont( tempfont );


        }

        /*        if (has_focus)
                {
                    roundedRectangleRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_border_hasfocus.R, colors->widget_border_hasfocus.G, colors->widget_border_hasfocus.B, colors->widget_border_hasfocus.A);
                }
        */


        for (auto& c : children )
            c->render( screen, colors, fonts );
    }


}


void InputWidget::updateScroll()
{
    if(scroll != 0 && cursor_pos <= scroll)
        --scroll;

    if(cursor_pos <= scroll)
        return;

    nSDL_Font *tempfont = nSDL_LoadFont(NSDL_FONT_THIN, 0, 0, 0);

    const char *str = text.c_str() + scroll;
    unsigned int cur_x = 0, len = cursor_pos - scroll;

    while(len--)
        cur_x += getwidthfont( tempfont, *str++);

    if(cur_x >= width - 5)
        ++scroll;

    nSDL_FreeFont( tempfont );
}

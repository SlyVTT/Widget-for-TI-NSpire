#include "CommuterWidget.h"

void CommuterWidget::logic( CursorTask *mouse, KeyboardTask *keyboard )
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
}

void CommuterWidget::render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts )
{
    unsigned short R=0,G=0,B=0,A=0;
    unsigned short Rc=0,Gc=0,Bc=0,Ac=0;

    if (is_ticked && (typetick == style1 ))
    {
        R = colors->widget_commuter_active_filling_style1.R;
        G = colors->widget_commuter_active_filling_style1.G;
        B = colors->widget_commuter_active_filling_style1.B;
        A = colors->widget_commuter_active_filling_style1.A;

        Rc = colors->widget_commuter_active_cursor_style1.R;
        Gc = colors->widget_commuter_active_cursor_style1.G;
        Bc = colors->widget_commuter_active_cursor_style1.B;
        Ac = colors->widget_commuter_active_cursor_style1.A;
    }
    if (!is_ticked && (typetick == style1 ))
    {
        R = colors->widget_commuter_inactive_filling_style1.R;
        G = colors->widget_commuter_inactive_filling_style1.G;
        B = colors->widget_commuter_inactive_filling_style1.B;
        A = colors->widget_commuter_inactive_filling_style1.A;

        Rc = colors->widget_commuter_inactive_cursor_style1.R;
        Gc = colors->widget_commuter_inactive_cursor_style1.G;
        Bc = colors->widget_commuter_inactive_cursor_style1.B;
        Ac = colors->widget_commuter_inactive_cursor_style1.A;
    }

    if (is_ticked && (typetick == style2 ))
    {
        R = colors->widget_commuter_active_filling_style2.R;
        G = colors->widget_commuter_active_filling_style2.G;
        B = colors->widget_commuter_active_filling_style2.B;
        A = colors->widget_commuter_active_filling_style2.A;

        Rc = colors->widget_commuter_active_cursor_style2.R;
        Gc = colors->widget_commuter_active_cursor_style2.G;
        Bc = colors->widget_commuter_active_cursor_style2.B;
        Ac = colors->widget_commuter_active_cursor_style2.A;
    }
    if (!is_ticked && (typetick == style2 ))
    {
        R = colors->widget_commuter_inactive_filling_style2.R;
        G = colors->widget_commuter_inactive_filling_style2.G;
        B = colors->widget_commuter_inactive_filling_style2.B;
        A = colors->widget_commuter_inactive_filling_style2.A;

        Rc = colors->widget_commuter_inactive_cursor_style2.R;
        Gc = colors->widget_commuter_inactive_cursor_style2.G;
        Bc = colors->widget_commuter_inactive_cursor_style2.B;
        Ac = colors->widget_commuter_inactive_cursor_style2.A;
    }

    if (is_ticked && (typetick == style3 ))
    {
        R = colors->widget_commuter_active_filling_style3.R;
        G = colors->widget_commuter_active_filling_style3.G;
        B = colors->widget_commuter_active_filling_style3.B;
        A = colors->widget_commuter_active_filling_style3.A;

        Rc = colors->widget_commuter_active_cursor_style3.R;
        Gc = colors->widget_commuter_active_cursor_style3.G;
        Bc = colors->widget_commuter_active_cursor_style3.B;
        Ac = colors->widget_commuter_active_cursor_style3.A;
    }
    if (!is_ticked && (typetick == style3 ))
    {
        R = colors->widget_commuter_inactive_filling_style3.R;
        G = colors->widget_commuter_inactive_filling_style3.G;
        B = colors->widget_commuter_inactive_filling_style3.B;
        A = colors->widget_commuter_inactive_filling_style3.A;

        Rc = colors->widget_commuter_inactive_cursor_style3.R;
        Gc = colors->widget_commuter_inactive_cursor_style3.G;
        Bc = colors->widget_commuter_inactive_cursor_style3.B;
        Ac = colors->widget_commuter_inactive_cursor_style3.A;
    }

    if (is_ticked && (typetick == style4 ))
    {
        R = colors->widget_commuter_active_filling_style4.R;
        G = colors->widget_commuter_active_filling_style4.G;
        B = colors->widget_commuter_active_filling_style4.B;
        A = colors->widget_commuter_active_filling_style4.A;

        Rc = colors->widget_commuter_active_cursor_style4.R;
        Gc = colors->widget_commuter_active_cursor_style4.G;
        Bc = colors->widget_commuter_active_cursor_style4.B;
        Ac = colors->widget_commuter_active_cursor_style4.A;
    }
    if (!is_ticked && (typetick == style4 ))
    {
        R = colors->widget_commuter_inactive_filling_style4.R;
        G = colors->widget_commuter_inactive_filling_style4.G;
        B = colors->widget_commuter_inactive_filling_style4.B;
        A = colors->widget_commuter_inactive_filling_style4.A;

        Rc = colors->widget_commuter_inactive_cursor_style4.R;
        Gc = colors->widget_commuter_inactive_cursor_style4.G;
        Bc = colors->widget_commuter_inactive_cursor_style4.B;
        Ac = colors->widget_commuter_inactive_cursor_style4.A;
    }


    if (is_visible)
    {

        if (is_enabled)
        {
            roundedBoxRGBA( screen, xpos+6, ypos+height/2-6, xpos+30, ypos+height/2+6, 6, R, G, B, A);
            if (!is_hovering)
            {
                roundedRectangleRGBA( screen, xpos+6, ypos+height/2-6, xpos+30, ypos+height/2+6, 6, colors->widget_border_enable.R, colors->widget_border_enable.G, colors->widget_border_enable.B, colors->widget_border_enable.A);
            }
            else
            {
                roundedRectangleRGBA( screen, xpos+6, ypos+height/2-6, xpos+30, ypos+height/2+6, 6, colors->widget_border_cursoron.R, colors->widget_border_cursoron.G, colors->widget_border_cursoron.B, colors->widget_border_cursoron.A);
            }

            if ((is_ticked && !is_reversed) || (!is_ticked && is_reversed))
            {
                filledCircleRGBA( screen, xpos+12, ypos+height/2, 4, Rc, Gc, Bc, Ac);
                if (!is_hovering)
                {
                    circleRGBA( screen, xpos+12, ypos+height/2, 4, colors->widget_border_enable.R, colors->widget_border_enable.G, colors->widget_border_enable.B, colors->widget_border_enable.A);
                }
                else
                {
                    circleRGBA( screen, xpos+12, ypos+height/2, 4, colors->widget_border_cursoron.R, colors->widget_border_cursoron.G, colors->widget_border_cursoron.B, colors->widget_border_cursoron.A);
                }
            }
            else
            {
                filledCircleRGBA( screen, xpos+24, ypos+height/2, 4, Rc, Gc, Bc, Ac);
                if (!is_hovering)
                {
                    circleRGBA( screen, xpos+24, ypos+height/2, 4, colors->widget_border_enable.R, colors->widget_border_enable.G, colors->widget_border_enable.B, colors->widget_border_enable.A);
                }
                else
                {
                    circleRGBA( screen, xpos+24, ypos+height/2, 4, colors->widget_border_cursoron.R, colors->widget_border_cursoron.G, colors->widget_border_cursoron.B, colors->widget_border_cursoron.A);
                }
            }


            fonts->setcurrentfont( fonts->widget_text_enable.name );
            fonts->setmodifiertypo( fonts->widget_text_enable.typo );
            fonts->setmodifierunder( fonts->widget_text_enable.under );
            fonts->setmodifierstrike( fonts->widget_text_enable.strike );

            //We check if the titel can be written in the titlebar (with 2px on each side of the title + 15 pixels for the buttons on the left
            drawablecharlabel = fonts->assertstringlength( label, width-17-2 );

            strcpy( drawablelabel, label );
            if ((drawablecharlabel < strlen(label)) && (drawablecharlabel >=2)) drawablelabel[drawablecharlabel-2] = '\u0010';
            if ((drawablecharlabel < strlen(label)) && (drawablecharlabel >=1)) drawablelabel[drawablecharlabel-1] = '\0';

            if (drawablecharlabel!=0)
            {
                int sl = fonts->getstringwidth( drawablelabel );
                int sh = fonts->getstringheight( drawablelabel );
                fonts->drawstringleft( screen, drawablelabel, xpos+35, ypos+(height-sh)/2, colors->widget_text_enable.R, colors->widget_text_enable.G, colors->widget_text_enable.B, colors->widget_text_enable.A );
            }

        }
        else
        {

            roundedBoxRGBA( screen, xpos+6, ypos+height/2-6, xpos+30, ypos+height/2+6, 6, colors->widget_filling_disable.R, colors->widget_filling_disable.G, colors->widget_filling_disable.B, colors->widget_filling_disable.A);

            roundedRectangleRGBA( screen, xpos+6, ypos+height/2-6, xpos+30, ypos+height/2+6, 3, colors->widget_border_disable.R, colors->widget_border_disable.G, colors->widget_border_disable.B, colors->widget_border_disable.A);

            if ((is_ticked && !is_reversed) || (!is_ticked && is_reversed))
            {
                filledCircleRGBA( screen, xpos+12, ypos+height/2, 4, colors->widget_filling_disable.R, colors->widget_filling_disable.G, colors->widget_filling_disable.B, colors->widget_filling_disable.A);
                circleRGBA( screen, xpos+12, ypos+height/2, 4, colors->widget_border_disable.R, colors->widget_border_disable.G, colors->widget_border_disable.B, colors->widget_border_disable.A);
            }
            else
            {
                filledCircleRGBA( screen, xpos+24, ypos+height/2, 4, colors->widget_filling_disable.R, colors->widget_filling_disable.G, colors->widget_filling_disable.B, colors->widget_filling_disable.A);
                circleRGBA( screen, xpos+24, ypos+height/2, 4, colors->widget_border_disable.R, colors->widget_border_disable.G, colors->widget_border_disable.B, colors->widget_border_disable.A);
            }

            fonts->setcurrentfont( fonts->widget_text_disable.name );
            fonts->setmodifiertypo( fonts->widget_text_disable.typo );
            fonts->setmodifierunder( fonts->widget_text_disable.under );
            fonts->setmodifierstrike( fonts->widget_text_disable.strike );

            //We check if the titel can be written in the titlebar (with 2px on each side of the title + 15 pixels for the buttons on the left
            drawablecharlabel = fonts->assertstringlength( label, width-17-2 );

            strcpy( drawablelabel, label );
            if ((drawablecharlabel < strlen(label)) && (drawablecharlabel >=2)) drawablelabel[drawablecharlabel-2] = '\u0010';
            if ((drawablecharlabel < strlen(label)) && (drawablecharlabel >=1)) drawablelabel[drawablecharlabel-1] = '\0';

            if (drawablecharlabel!=0)
            {
                int sl = fonts->getstringwidth( drawablelabel );
                int sh = fonts->getstringheight( drawablelabel );
                fonts->drawstringleft( screen, drawablelabel, xpos+35, ypos+(height-sh)/2, colors->widget_text_disable.R, colors->widget_text_disable.G, colors->widget_text_disable.B, colors->widget_text_disable.A );
            }

        }


        for (auto& c : children )
            c->render( screen, colors, fonts );

    }
}

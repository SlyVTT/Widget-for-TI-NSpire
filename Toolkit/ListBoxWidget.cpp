#include "ListBoxWidget.h"
#include "DropBoxWidget.h"

//#include <math.h>


bool ListBoxWidget::ispressed()
{
    return is_pressed;
}

void ListBoxWidget::logic( CursorTask *mouse, KeyboardTask *keyboard )
{
    if (is_enabled && is_visible)
    {

        if (keyboard->kbESC)
        {
            DropBoxWidget *temp = dynamic_cast<DropBoxWidget*>(parent);
            temp->escape();

            //parent->escape();

            is_visible = false;
            return;
        }

        if (keyboard->kbRET || keyboard->kbENTER)
        {
            DropBoxWidget *temp = dynamic_cast<DropBoxWidget*>(parent);
            temp->validate();

            //parent->validate;

            is_visible = false;
            return;
        }


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

        if (keyboard->kbDOWN && keyboard->iskeypressevent())
        {
            if ( selected < this->getnbitem()-1)
            {
                selected++;
            }

            if ((selected>=0) && (selected<=nbvisible-1))
            {
                scroll=0;
            }
            else //((selected>=nbvisible) && (selected<=getnbitem()-1))
            {
                scroll=selected-nbvisible+1;
            }

            SDL_Delay( 300 );
        }

        if (keyboard->kbUP && keyboard->iskeypressevent())
        {
            if (selected>0)
            {
                selected--;
            }

            if ((selected>=0) && (selected<=nbvisible-1))
            {
                scroll=0;
            }
            else //((selected>=nbvisible) && (selected<=getnbitem()-1))
            {
                scroll=selected-nbvisible+1;
            }

            SDL_Delay( 300 );
        }



        for (auto& c : children )
            c->logic( mouse, keyboard );
    }
}

void ListBoxWidget::render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts )
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

            fonts->setcurrentfont( THIN_FONT );
            fonts->setmodifiertypo( Normal );

            int sl = fonts->getstringwidth( label );
            int sh = fonts->getstringheight( label );

            nbvisible = (unsigned int) ((height-10) / (sh*2));

            for(int i=scroll; i<=scroll+nbvisible-1; i++)
            {
                //Ongoing - to be optimised
                if (i!=selected)
                {
                    fonts->drawstringleft( screen, (char*) listitems[i], xpos+5, ypos+5+(unsigned int) ((i-scroll)*(sh*2)), colors->widget_text_enable.R, colors->widget_text_enable.G, colors->widget_text_enable.B, colors->widget_text_enable.A );
                }
                else
                {
                    roundedBoxRGBA( screen, xpos, ypos+3+(unsigned int) ((i-scroll)*(sh*2)), xpos+width, ypos+15+(unsigned int) ((i-scroll)*(sh*2)), 3, 255, 0, 125, 255);
                    fonts->drawstringleft( screen, (char*) listitems[i], xpos+5, ypos+5+(unsigned int) ((i-scroll)*(sh*2)), 255, 255, 255, 255 );
                }

            }
        }
        else
        {
            roundedBoxRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_filling_disable.R, colors->widget_filling_disable.G, colors->widget_filling_disable.B, colors->widget_filling_disable.A);
            //Border of the button is black cause it is disabled
            roundedRectangleRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_border_disable.R, colors->widget_border_disable.G, colors->widget_border_disable.B, colors->widget_border_disable.A);

            fonts->setcurrentfont( THIN_FONT );
            fonts->setmodifiertypo( Normal );

            int sl = fonts->getstringwidth( label );
            int sh = fonts->getstringheight( label );

            fonts->drawstringleft( screen, label, xpos+(width-sl)/2, ypos+(height-sh)/2, colors->widget_text_disable.R, colors->widget_text_disable.G, colors->widget_text_disable.B, colors->widget_text_disable.A );
        }

        for (auto& c : children )
            c->render( screen, colors, fonts );

    }
}

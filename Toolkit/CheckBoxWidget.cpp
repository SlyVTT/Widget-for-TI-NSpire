#include "CheckBoxWidget.h"


CheckBoxWidget::CheckBoxWidget()
{
    widgettype = "CheckBox";
    //strcpy( widgettype, (char*) "CheckBox");
};


CheckBoxWidget::CheckBoxWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : ButtonWidget( l, x, y, w, h, p )
{
    widgettype = "CheckBox";
    //strcpy( widgettype, (char*) "CheckBox");
};

CheckBoxWidget::~CheckBoxWidget()
{

};

void CheckBoxWidget::invert()
{
    is_ticked = !is_ticked;
};

bool CheckBoxWidget::isticked( void )
{
    return is_ticked;
};

void CheckBoxWidget::settype( tick type )
{
    typetick = type;
};

CheckBoxWidget::tick CheckBoxWidget::gettype()
{
    return typetick;
};

void CheckBoxWidget::logic( CursorTask *mouse, KeyboardTask *keyboard )
{
    if (is_enabled && is_visible)
    {
        is_hovering = cursoron( mouse );
        bool currently_pressed = (mouse->state || keyboard->kbSCRATCH) && is_hovering;

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


            fonts->setcurrentfont( fonts->widget_text_enable.name );
            fonts->setmodifiertypo( fonts->widget_text_enable.typo );
            fonts->setmodifierunder( fonts->widget_text_enable.under );
            fonts->setmodifierstrike( fonts->widget_text_enable.strike );

            drawablecharlabel = fonts->assertstringlength( label, width-17-2 );

            if (drawablecharlabel!=0)
            {
                drawablelabel = fonts->reducestringtovisible( label, width-17 -2  );

                //int sl = fonts->getstringwidth( drawablelabel );
                int sh = fonts->getstringheight( drawablelabel );
                fonts->drawstringleft( screen, drawablelabel, xpos+15, ypos+(height-sh)/2, colors->widget_text_enable.R, colors->widget_text_enable.G, colors->widget_text_enable.B, colors->widget_text_enable.A );
            }

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

            fonts->setcurrentfont( fonts->widget_text_disable.name );
            fonts->setmodifiertypo( fonts->widget_text_disable.typo );
            fonts->setmodifierunder( fonts->widget_text_disable.under );
            fonts->setmodifierstrike( fonts->widget_text_disable.strike );

            drawablecharlabel = fonts->assertstringlength( label, width-17-2 );

            if (drawablecharlabel!=0)
            {
                drawablelabel = fonts->reducestringtovisible( label, width-17 -2  );

                //int sl = fonts->getstringwidth( drawablelabel );
                int sh = fonts->getstringheight( drawablelabel );
                fonts->drawstringleft( screen, drawablelabel, xpos+15, ypos+(height-sh)/2, colors->widget_text_disable.R, colors->widget_text_disable.G, colors->widget_text_disable.B, colors->widget_text_disable.A );
            }

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

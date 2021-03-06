#include "IconItemWidget.h"

#include <SDL/SDL_image.h>

IconItemWidget::IconItemWidget()
{
    widgettype =  "IconItem";
    //strcpy( widgettype, (char*) "IconItem");
};

IconItemWidget::IconItemWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : ButtonWidget( l, x, y, w, h, p )
{
    widgettype = "IconItem";
    //strcpy( widgettype, (char*) "IconItem");
};

IconItemWidget::~IconItemWidget()
{
    SDL_FreeSurface( this->icon );
}


bool IconItemWidget::ispressed()
{
    return is_pressed;
}

void IconItemWidget::disable( void )
{
    is_enabled = false;

    if (icondisableset == 1)
    {
        SDL_FreeSurface( icon );
        icon = IMG_Load( iconnamedisable.c_str() );
    }

    for (auto& c : children ) c->disable( );
}


void IconItemWidget::enable( void )
{
    is_enabled = true;

    if (iconenableset == 1)
    {
        SDL_FreeSurface( icon );
        icon = IMG_Load( iconnameenable.c_str() );
    }

    for (auto& c : children ) c->enable( );
}

void IconItemWidget::assigniconenable( std::string filename )
{
    iconnameenable = filename;
    iconenableset = 1;
    icon = IMG_Load( iconnameenable.c_str() );
}


void IconItemWidget::assignicondisable( std::string filename )
{
    iconnamedisable = filename;
    icondisableset = 1;
}


void IconItemWidget::logic( CursorTask *mouse, KeyboardTask *keyboard )
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
            if (clickfunction)
                clickfunction( (char*) "test" );

            mouse_hold_down = true;
        }
        else if (currently_pressed && is_ticked )
        {
            if (releasefunction)
                releasefunction( (char*) "test" );

            mouse_hold_down = true;
        }
        else if (is_hovering)
        {
            if (hoverfunction)
                hoverfunction( (char*) "test" );
        }

        is_pressed = currently_pressed;

        for (auto& c : children ) c->logic( mouse, keyboard );
    }
}

void IconItemWidget::render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts )
{
    if (is_visible)
    {
        if (is_enabled)
        {
            roundedBoxRGBA( screen, xpos+1, ypos+1, xpos+width-2, ypos+height-2, 3-1, colors->widget_filling_enable.R, colors->widget_filling_enable.G, colors->widget_filling_enable.B, colors->widget_filling_enable.A);

            if (!is_hovering)
            {
                roundedRectangleRGBA( screen, xpos+1, ypos+1, xpos+width-2, ypos+height-2, 3-1, colors->widget_border_enable.R, colors->widget_border_enable.G, colors->widget_border_enable.B, colors->widget_border_enable.A);
            }
            else
            {
                roundedRectangleRGBA( screen, xpos+1, ypos+1, xpos+width-2, ypos+height-2, 3-1, colors->widget_border_cursoron.R, colors->widget_border_cursoron.G, colors->widget_border_cursoron.B, colors->widget_border_cursoron.A);
            }

            //if (icon_enable)
            if (icon)
            {
                SDL_Rect src_rect, screen_pos;
                src_rect.x = 0;
                src_rect.y = 0;
                src_rect.w = 16;
                src_rect.h = 16;
                screen_pos.x = xpos+2;
                screen_pos.y = ypos+2;
                SDL_BlitSurface(icon, &src_rect, screen, &screen_pos);
            }
            else
            {
                fonts->setcurrentfont( fonts->widget_text_enable.name );
                fonts->setmodifiertypo( fonts->widget_text_enable.typo );
                fonts->setmodifierunder( fonts->widget_text_enable.under );
                fonts->setmodifierstrike( fonts->widget_text_enable.strike );

                //We check if the titel can be written in the titlebar (with 5px on each side of the title + 30 pixels for the buttons on the right
                drawablecharlabel = fonts->assertstringlength( label, width-2-2 );

                if (drawablecharlabel!=0)
                {
                    drawablelabel = fonts->reducestringtovisible( label, width-2 -2  );
                    int sl = fonts->getstringwidth( drawablelabel );
                    int sh = fonts->getstringheight( drawablelabel );
                    fonts->drawstringleft( screen, drawablelabel, xpos+(width-sl)/2, ypos+(height-sh)/2, colors->widget_text_enable.R, colors->widget_text_enable.G, colors->widget_text_enable.B, colors->widget_text_enable.A );
                }
            }
        }
        else
        {
            roundedBoxRGBA( screen, xpos+1, ypos+1, xpos+width-2, ypos+height-2, 3-1, colors->widget_filling_disable.R, colors->widget_filling_disable.G, colors->widget_filling_disable.B, colors->widget_filling_disable.A);
            //Border of the button is black cause it is disabled
            roundedRectangleRGBA( screen, xpos+1, ypos+1, xpos+width-2, ypos+height-2, 3-1, colors->widget_border_disable.R, colors->widget_border_disable.G, colors->widget_border_disable.B, colors->widget_border_disable.A);

            //if (icon_disable)
            if (icon)
            {
                SDL_Rect src_rect, screen_pos;
                src_rect.x = 0;
                src_rect.y = 0;
                src_rect.w = 16;
                src_rect.h = 16;
                screen_pos.x = xpos+2;
                screen_pos.y = ypos+2;
                SDL_BlitSurface(icon, &src_rect, screen, &screen_pos);
            }
            else
            {
                fonts->setcurrentfont( fonts->widget_text_disable.name );
                fonts->setmodifiertypo( fonts->widget_text_disable.typo );
                fonts->setmodifierunder( fonts->widget_text_disable.under );
                fonts->setmodifierstrike( fonts->widget_text_disable.strike );

                //We check if the titel can be written in the titlebar (with 2px on each side of the label
                drawablecharlabel = fonts->assertstringlength( label, width-2-2 );

                if (drawablecharlabel!=0)
                {
                    drawablelabel = fonts->reducestringtovisible( label, width-2 -2  );
                    int sl = fonts->getstringwidth( drawablelabel );
                    int sh = fonts->getstringheight( drawablelabel );
                    fonts->drawstringleft( screen, drawablelabel, xpos+(width-sl)/2, ypos+(height-sh)/2, colors->widget_text_disable.R, colors->widget_text_disable.G, colors->widget_text_disable.B, colors->widget_text_disable.A );
                }
            }
        }

        for (auto& c : children ) c->render( screen, colors, fonts );
    }
}

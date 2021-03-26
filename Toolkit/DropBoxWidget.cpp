#include "DropBoxWidget.h"



DropBoxWidget::DropBoxWidget() : Widget()
{
    widgettype = (char*) "DropBox";

    dropbutton = new MiniButtonWidget();
    dropbutton->settype( Bottom_Arrow );

    listbox = new ListBoxWidget();

    listbox->setparent( this );

    listbox->setlabel( (char*) "Hello Listbox" );
    listbox->setinvisible();

    parent->addpopupchild( listbox );
};

DropBoxWidget::DropBoxWidget(char *l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : Widget( l, x, y, w, h, p )
{
    widgettype = (char*) "DropBox";

    this->setdimensions( x, y, w-h, h );

    MiniButtonWidget *tempbutton = new MiniButtonWidget();
    dropbutton = tempbutton;
    dropbutton->setdimensions( x+w, y, h, h );
    dropbutton->settype( Bottom_Arrow );

    ListBoxWidget *templist = new ListBoxWidget();
    listbox = templist;
    listbox->setdimensions( x, y+h, w+h, 5*h );

    listbox->setparent( this );

    listbox->setlabel( (char*) "Hello Listbox" );
    listbox->setinvisible();

    parent->addpopupchild( listbox );
};


bool DropBoxWidget::ispressed()
{
    return is_pressed;
}

void DropBoxWidget::validate()
{
    this->selected_item = this->listbox->getselected();
    this->selected_item_value = this->listbox->getselecteditem();

    this->setlabel( (char*) selected_item_value );

    //this->dropbutton->settype( Bottom_Arrow );
    this->dropbutton->invert();
    //this->listbox->setinvisible();
    this->undrop();

    SDL_Delay( 300 );
}

void DropBoxWidget::escape()
{
    this->selected_item = -1;
    this->selected_item_value = (char *) " ";

    this->setlabel( (char*) " " );

    //this->dropbutton->settype( Bottom_Arrow );
    this->dropbutton->invert();
    //this->listbox->setinvisible();
    this->undrop();

    SDL_Delay( 300 );
}

void DropBoxWidget::adjust()
{

    this->setdimensions( xpos, ypos, width-height, height );

    dropbutton->setdimensions( xpos+width, ypos, height, height );

    listbox->setdimensions( xpos, ypos+height, width+height, 5*height );

    for (auto& c : children )
        c->adjust();
}

void DropBoxWidget::logic( CursorTask *mouse, KeyboardTask *keyboard )
{
    if (is_enabled && is_visible)
    {

        is_hovering = cursoron( mouse );
        bool currently_pressed = (mouse->state || keyboard->kbSCRATCH) && is_hovering;


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

        dropbutton->logic( mouse, keyboard );




        //if (dropbutton->ispressed() && !is_dropped )
        //if ((is_pressed && !is_dropped) || (dropbutton->ispressed() && !is_dropped ))
        if (dropbutton->isticked())
        {
            dropbutton->settype( Up_Arrow );
            this->drop();
        }
        else //if ((is_pressed && is_dropped) || (dropbutton->ispressed() && is_dropped ))
        {
            dropbutton->settype( Bottom_Arrow );
            this->undrop();
        }

        for (auto& c : children )
            c->logic( mouse, keyboard );

    }
}

void DropBoxWidget::render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts )
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

            fonts->drawstringleft( screen, label, xpos+(width-sl)/2, ypos+(height-sh)/2, colors->widget_text_enable.R, colors->widget_text_enable.G, colors->widget_text_enable.B, colors->widget_text_enable.A );
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

        dropbutton->render( screen, colors, fonts );

        for (auto& c : children )
            c->render( screen, colors, fonts );

    }
}

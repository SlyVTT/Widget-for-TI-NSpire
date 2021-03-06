#include "DropBoxWidget.h"



DropBoxWidget::DropBoxWidget() : Widget()
{
    widgettype = "DropBox";

    dropbutton = new MiniButtonWidget();
    dropbutton->settype( MiniButtonWidget::Bottom_Arrow );
    addchild(dropbutton);

    listbox = new ListBoxWidget();
    addchild( listbox );
    listbox->setparent( this );

    listbox->setlabel( "Hello Listbox" );
    listbox->setinvisible();

    parent->addpopupchild( listbox );
};


DropBoxWidget::DropBoxWidget(std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : Widget( l, x, y, w, h, p )
{
    widgettype = "DropBox";

    this->setdimensions( x, y, w-h, h );

    MiniButtonWidget *tempbutton = new MiniButtonWidget();
    dropbutton = tempbutton;
    dropbutton->setdimensions( x+w, y, h, h );
    dropbutton->settype( MiniButtonWidget::Bottom_Arrow );
    addchild(dropbutton);

    ListBoxWidget *templist = new ListBoxWidget();
    listbox = templist;
    listbox->setdimensions( x, y+h, w+h, 5*h );
    addchild( listbox );
    listbox->setparent( this );

    listbox->setlabel( "Hello Listbox" );
    listbox->setinvisible();

    parent->addpopupchild( listbox );
}

DropBoxWidget::~DropBoxWidget()
{
    delete dropbutton;
    delete listbox;
}

void DropBoxWidget::drop()
{
    is_dropped = true;
    this->listbox->setvisible();
    has_been_updated = false;
};


void DropBoxWidget::undrop()
{
    is_dropped = false;
    this->listbox->setinvisible();
};


void DropBoxWidget::additem( std::string item )
{
    listbox->additem( item );
};


int DropBoxWidget::getnbitem()
{
    return listbox->getnbitem();
};

std::string DropBoxWidget::getitem( int itemnumber )
{
    return listbox->getitem( itemnumber );
};

int DropBoxWidget::getselected()
{
    return listbox->getselected();
};

std::string DropBoxWidget::getselecteditem()
{
    return listbox->getselecteditem();
};


bool DropBoxWidget::isupdated()
{
    return has_been_updated;
};


bool DropBoxWidget::ispressed()
{
    return is_pressed;
}

void DropBoxWidget::validate()
{
    this->selected_item = this->listbox->getselected();
    this->selected_item_value = this->listbox->getselecteditem();

    this->setlabel( selected_item_value );

    this->dropbutton->invert();
    this->undrop();

    has_been_updated = true;
}

void DropBoxWidget::escape()
{
    this->selected_item = -1;
    this->selected_item_value = " ";

    this->setlabel( " " );

    this->dropbutton->invert();
    this->undrop();

    has_been_updated = false;
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
            if (clickfunction) clickfunction( (char*) "test" );
        }
        else if(!currently_pressed && is_pressed)
        {
            if (releasefunction) releasefunction( (char*) "test" );
        }
        else if(is_hovering)
        {
            if (hoverfunction) hoverfunction( (char*) "test" );
        }

        is_pressed = currently_pressed;

        dropbutton->logic( mouse, keyboard );

        if (dropbutton->isticked())
        {
            dropbutton->settype( MiniButtonWidget::Up_Arrow );
            this->drop();
        }
        else
        {
            dropbutton->settype( MiniButtonWidget::Bottom_Arrow );
            this->undrop();
        }

        //for (auto& c : children )
        //    c->logic( mouse, keyboard );
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

            fonts->setcurrentfont( fonts->widget_text_enable.name );
            fonts->setmodifiertypo( fonts->widget_text_enable.typo );
            fonts->setmodifierunder( fonts->widget_text_enable.under );
            fonts->setmodifierstrike( fonts->widget_text_enable.strike );

            drawablecharlabel = fonts->assertstringlength( label, width-5-5 );

            if ((drawablecharlabel!=0) && (selected_item!=-1))
            {
                drawablelabel = fonts->reducestringtovisible( label, width-5 -5  );

                int sh = fonts->getstringheight( drawablelabel );
                fonts->drawstringleft( screen, drawablelabel, xpos+5, ypos+(height-sh)/2, colors->widget_text_enable.R, colors->widget_text_enable.G, colors->widget_text_enable.B, colors->widget_text_enable.A );
            }
        }
        else
        {
            roundedBoxRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_filling_disable.R, colors->widget_filling_disable.G, colors->widget_filling_disable.B, colors->widget_filling_disable.A);

            roundedRectangleRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_border_disable.R, colors->widget_border_disable.G, colors->widget_border_disable.B, colors->widget_border_disable.A);

            fonts->setcurrentfont( fonts->widget_text_disable.name );
            fonts->setmodifiertypo( fonts->widget_text_disable.typo );
            fonts->setmodifierunder( fonts->widget_text_disable.under );
            fonts->setmodifierstrike( fonts->widget_text_disable.strike );

            drawablecharlabel = fonts->assertstringlength( label, width-5-5 );

            if ((drawablecharlabel!=0) && (selected_item!=-1))
            {
                drawablelabel = fonts->reducestringtovisible( label, width-5 -5  );

                int sh = fonts->getstringheight( drawablelabel );
                fonts->drawstringleft( screen, drawablelabel, xpos+5, ypos+(height-sh)/2, colors->widget_text_disable.R, colors->widget_text_disable.G, colors->widget_text_disable.B, colors->widget_text_disable.A );
            }
        }

        dropbutton->render( screen, colors, fonts );

        for (auto& c : children ) c->render( screen, colors, fonts );

    }
}

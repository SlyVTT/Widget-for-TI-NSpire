#include "Widget.h"


extern unsigned int GlobalWdidgetIDCounter;


Widget::Widget( )
{



}

Widget::Widget( char *l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p )
{
    label=l;
    xrel=x;
    yrel=y;
    widrel=w;
    heirel=h;
    parent=p;

    WidgetID = GlobalWdidgetIDCounter;
    GlobalWdidgetIDCounter++;


    if (parent)
    {
        parent->addchild( this );

        // if the widget has a parent, then we have to compute relative coordinates
        // if the parent is directly the desktop, we are free to position the widget as we want
        if (parent->getwidgettype() == (char*) "Desktop")
        {
            xpos = xrel;
            ypos = yrel;
            width = widrel;
            height = heirel;
        }
        else
        {
            // else we need to take care of the useable dimension of the parent widget
            xpos = parent->getuseablexpos() + xrel;
            ypos = parent->getuseableypos() + yrel;

            if ((xpos+widrel) > (parent->getuseablexpos()+parent->getuseablewidth()))
            {
                width = parent->getuseablexpos()+parent->getuseablewidth() -xpos;
            }
            else
            {
                width = widrel;
            }

            if ((ypos+heirel) > (parent->getuseableypos()+parent->getuseableheight()))
            {
                height = parent->getuseableypos()+parent->getuseableheight() -ypos;
            }
            else
            {
                height = heirel;
            }
        }
    }
    else
    {
        xpos = xrel;
        ypos = yrel;
        width = widrel;
        height = heirel;
    }

}

Widget::~Widget()
{
    children.clear();
}

void Widget::adjust()
{
    for (auto& c : children )
        c->adjust();
}

void Widget::logic( CursorTask *mouse, KeyboardTask *keyboard )
{

    for (auto& c : children )
        c->logic( mouse, keyboard );
}

void Widget::focus( Widget *emitter)
{


    // We go up to the first parent==nullptr (root of the tree
    if (parent)
    {
        parent->unfocusup( emitter );
    }
    /*    else //and then if parent is nullptr, we cascade down to the final leafs
        {
            for (auto& c : children )
            {
                if (c!=emitter)
                    c->unfocusdown( emitter );
            }
        }
    */
    has_focus = true;
}

void Widget::unfocusup( Widget *emitter)
{
    has_focus = false;


    // We go up to the first parent==nullptr (root of the tree
    if (parent)
    {
        parent->unfocusup( emitter );
    }
    else  //and then if parent is nullptr, we cascade down to the final leafs
    {
        for (auto& c : children )
        {
//            if (c!=emitter)
            c->unfocusdown( emitter );
        }
    }
}

void Widget::unfocusdown( Widget *emitter)
{
    has_focus = false;

    for (auto& c : children )
    {
//        if (c!=emitter)
        c->unfocusdown( emitter );
    }
}



void Widget::render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts )
{
    for (auto& c : children )
        c->render( screen, colors, fonts );
}


void Widget::renderdepth( SDL_Surface *depthbuffer )
{

    //if the widget is a window, then we plot the corresponding zone in the depth buttfer with a color representing its ID
    if ((this->getwidgettype() == (char*) "Window") || ((this->getwidgettype() == (char*) "MenuBar") && (this->parent->getwidgettype() == (char*) "Desktop")))
    {
        //This part of the routine convert the Wedgit ID into a color code 0xRRGGBBAA (with AA always equal to 0XFF)
        //It assumes a maximum number of widget limited to 249 per desktop

        //The number of units codes the BB component
        unsigned int B=0;
        unsigned int u = WidgetID % 10;
        B = u*25;

        //The number of tens codes the GG component
        unsigned int G=0;
        unsigned int d=((WidgetID-u)/10) % 10;
        G = d*25;

        //The number of hundreds codes the RR component
        unsigned int R=0;
        unsigned int c=(WidgetID-u-10*d) / 100;
        R = c*25;


        //Draw the corresponding shape in the Depth Buffer Image
        roundedBoxRGBA( depthbuffer, xpos, ypos, xpos+width, ypos+height, 3, R, G, B, 255 );

    }

    for (auto& c : children )
        c->renderdepth( depthbuffer );
}



void Widget::enable( )
{
    is_enabled = true;
    for (auto& c : children )
        c->enable( );
}

void Widget::disable( )
{
    is_enabled = false;
    for (auto& c : children )
        c->disable( );
}

void Widget::setvisible( )
{
    is_visible = true;
    for (auto& c : children )
        c->setvisible( );
}

void Widget::setinvisible( )
{
    is_visible = false;
    for (auto& c : children )
        c->setinvisible( );
}


void Widget::addchild( Widget *child )
{
    children.push_back( child );
    child->setparent( this );
}


void Widget::addpopupchild( Widget *child )
{
    if (getwidgettype() == (char*) "Window")
    {
        popupchildren.push_back( child );
    }
    else if (parent)
    {
        parent->addpopupchild( child );
    }
}


void Widget::setparent( Widget *p )
{
    parent = p;
};

bool Widget::cursoron( CursorTask *mouse )
{
    return ((unsigned int) mouse->x >= xpos) && ((unsigned int) mouse->y >= ypos) && ((unsigned int) mouse->x <= xpos+width) && ((unsigned int) mouse->y <= ypos+height);
}

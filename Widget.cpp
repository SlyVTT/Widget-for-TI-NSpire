#include "Widget.h"



Widget::Widget( )
{

}

Widget::Widget( char *l, int x, int y, int w, int h, Widget *p )
{
    label=l;
    xpos=x;
    ypos=y;
    width=w;
    height=h;
    parent=p;

    if (parent)
        parent->addchild( this );
}

Widget::~Widget()
{
    children.clear();
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



void Widget::render( SDL_Surface *screen, nSDL_Font *currentfont )
{
    for (auto& c : children )
        c->render( screen, currentfont );
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

bool Widget::cursoron( CursorTask *mouse )
{
    return (mouse->x >= xpos) && (mouse->y >= ypos) && (mouse->x <= xpos+width) && (mouse->y <= ypos+height);
}

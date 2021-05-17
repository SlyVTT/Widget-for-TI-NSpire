#include "Widget.h"


extern unsigned int GlobalWdidgetIDCounter;




Widget* Widget::getclosestmainparent()
{


    Widget* temp = this;
    Widget* temp2=nullptr;

    /*
        FILE *pFile;

        pFile = fopen( "/documents/Widget/closepar.txt.tns", "a" );
        fprintf( pFile, "Enter the GetClosestParent Loop \n" );
        fprintf( pFile, "widgetID = %ld \n", this->WidgetID );
    */


    if (( this->getwidgettype() == "Desktop" ) || ( this->getwidgettype() == "Window" ))
    {
        //     fprintf( pFile, "This is me = %ld \n", this->WidgetID );
        //     fclose( pFile );
        return this;
    }
    else
    {
        //    fprintf( pFile, "go to my parent \n" );
        temp = this->parent;
        while (temp!=nullptr)
        {
            if (( temp->getwidgettype() == "Desktop" ) || (temp->getwidgettype() == "Window" ))
            {
                //            fprintf( pFile, "This is me = %ld \n", temp->WidgetID );
                //            fclose( pFile );
                return temp;
            }
            else
            {
                //            fprintf( pFile, "go to my grand-parent \n" );
                temp2=temp;
                temp = temp2->parent;
            }
        }

        //    fprintf( pFile, "Houston, we have a problem !! \n" );
        //    fclose( pFile );

        return nullptr;
    }
};


Widget* Widget::getwidgetbyID( Uint32 IDsearched )
{
    if (IDsearched>=GlobalWdidgetIDCounter)  return nullptr;
    if (this->WidgetID == IDsearched)
    {
        // we are lucky, we are on the widget we are looking for
        return this;
    }
    else
    {
        if (children.size()!=0)
            for( auto&c : children)
                c->getwidgetbyID( IDsearched );
    }
    return nullptr;
};

/*
void Widget::DEBUG_draw_widget_tree_structure( int level, char* filename )
{

    FILE *pFile;

    pFile = fopen( filename, "a" );
    if (pFile==NULL)
    {
        return;
    }

    for( int i=0; i<level; i++ )
    {
        fprintf( pFile, "| " );
    }

    fprintf( pFile, "_ " );

    if (parent!=nullptr)
        fprintf( pFile, " ID = %ld : Type = %s : Name = %s | Parent (ID= %ld , Tp= %s) | Nb Children = %d | Nb PopUpChildren = %d | Ultimate Patent : ID = %ld - Type = %s \n", WidgetID, getwidgettype(), getlabel(), parent->WidgetID, parent->getwidgettype(), children.size(), popupchildren.size(), getclosestmainparent()->WidgetID, getclosestmainparent()->getwidgettype() );
    else
        fprintf( pFile, " ID = %ld : Type = %s : Name = %s | Parent (ID= %ld , Tp= %s) | Nb Children = %d | Nb PopUpChildren = %d | Ultimate Patent : ID = %ld - Type = %s \n", WidgetID, getwidgettype(), getlabel(), -1, (char*) "NULL_NOP", children.size(), popupchildren.size(), getclosestmainparent()->WidgetID,  (char*) "NULL_NOP" );

    fclose( pFile );


    if (children.size()!=0)
        for( auto& c : children )
            c->DEBUG_draw_widget_tree_structure( level+1, filename );

    if (popupchildren.size()!=0)
        for( auto& c : popupchildren )
            c->DEBUG_draw_widget_tree_structure( level+1, filename );

}
*/


void Widget::setdimensions( unsigned int mx, unsigned int my, unsigned int mw, unsigned int mh )
{
    xpos=mx;
    ypos=my;
    width=mw;
    height=mh;
};

void Widget::setxpos( unsigned int mx )
{
    xpos=mx;
};

void Widget::setypos( unsigned int my )
{
    ypos=my;
};

void Widget::setwidth( unsigned int mw )
{
    width=mw;
};

void Widget::setheight( unsigned int mh )
{
    height=mh;
};

void Widget::setlabel(std::string l)
{
    label = l;
};

void Widget::setcontainerstatus( bool status )
{
    is_container = status;
};

unsigned int Widget::getxpos()
{
    return xpos;
};

unsigned int Widget::getypos()
{
    return ypos;
};

unsigned int Widget::getwidth()
{
    return width;
};

unsigned int Widget::getheight()
{
    return height;
};

unsigned int Widget::getuseablexpos()
{
    return xpos + 2 ;
};

unsigned int Widget::getuseableypos()
{
    return ypos + 2 ;
};

unsigned int Widget::getuseablewidth()
{
    return width - 4;
};

unsigned int Widget::getuseableheight()
{
    return height - 4;
};

std::string Widget::getlabel()
{
    return label;
};

bool Widget::getcontainerstatus()
{
    return is_container;
};

Widget* Widget::getparent()
{
    return parent;
};

bool Widget::isenabled()
{
    return is_enabled;
};

bool Widget::isvisible()
{
    return is_visible;
};

std::string Widget::getwidgettype()
{
    return widgettype;
};

void Widget::linkonclick( void(*func)(char*) )
{
    clickfunction = func;
};

void Widget::linkonrelease( void(*func)(char*) )
{
    releasefunction = func;
};

void Widget::linkonhover( void(*func)(char*) )
{
    hoverfunction = func;
};

void Widget::activate()
{
    is_activated = true;
};

void Widget::desactivate()
{
    is_activated = false;
};

bool Widget::isactivated()
{
    return is_activated;
};

void Widget::lock()
{
    is_locked = true;
};

void Widget::unlock()
{
    is_locked = false;
};

bool Widget::islocked()
{
    return is_locked;
};



Widget::Widget( )
{

    WidgetID = GlobalWdidgetIDCounter;
    GlobalWdidgetIDCounter++;

}

Widget::Widget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p )
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
        if (parent->getwidgettype() == "Desktop" )
            //if (parent->getwidgettype() == (char*) "Desktop")
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
        if (c->isvisible()) c->render( screen, colors, fonts );
}


void Widget::renderdepth( SDL_Surface *depthbuffer )
{

    if (is_visible)
    {
        //if the widget is a Window or a DialogBox or the Desktop, then we plot the corresponding zone in the depth buttfer with a color representing its ID

        if ((getwidgettype() == "Desktop") || (getwidgettype() == "Window") || (getwidgettype() == "DialogBox") || (getwidgettype() == "FileDialogBox")) // || (strcmp( getwidgettype(),(char*) "MenuBar" )==0) || (strcmp( getwidgettype(),(char*) "MenuPane" )==0) )
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
        else if (((getwidgettype() == "MenuBar") || (getwidgettype() == "MenuPane") || (getwidgettype() == "IconBar")) && (getclosestmainparent()->getwidgettype() == "Desktop" ))
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
            if (c->isvisible()) c->renderdepth( depthbuffer );

    }
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
}

void Widget::setinvisible( )
{
    is_visible = false;
}


void Widget::addchild( Widget *child )
{
    children.push_back( child );
    nbchildren++;
    child->setparent( this );
}


void Widget::addpopupchild( Widget *child )
{
    if ((getwidgettype() == "Window" ) || (getwidgettype() == "Desktop" ))
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
    return ((unsigned int) mouse->x >= xpos)
                    && ((unsigned int) mouse->y >= ypos)
                    && ((unsigned int) mouse->x <= xpos+width)
                    && ((unsigned int) mouse->y <= ypos+height);
}

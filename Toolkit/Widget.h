#ifndef WIDGET_H
#define WIDGET_H

//#include <vector>
#include <list>

#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

#include "CursorTask.h"
#include "KeyboardTask.h"
#include "ColorEngine.h"
#include "FontEngine.h"



class Widget
{
public:
    Widget( );
    Widget( char *l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p );
    virtual ~Widget();

    Uint32 WidgetID = -1;

//    virtual void DEBUG_draw_widget_tree_structure( int level, char* filename );


    virtual void logic( CursorTask *mouse, KeyboardTask *keyboard );
    virtual void focus( Widget *emitter );
    virtual void unfocusup( Widget *emitter );
    virtual void unfocusdown( Widget *emitter );
    virtual void render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts );
    virtual void renderdepth( SDL_Surface *depthbuffer );
    virtual void addchild( Widget *child );
    virtual void addpopupchild( Widget *child );


    virtual Widget* getclosestmainparent();
    virtual Widget* getwidgetbyID( Uint32 IDsearched );

    virtual void activate();
    virtual void desactivate();
    virtual bool isactivated();

    virtual void lock();
    virtual void unlock();
    virtual bool islocked();

    //SETTERs
    virtual void setdimensions( unsigned int mx, unsigned int my, unsigned int mw, unsigned int mh );
    virtual void setxpos( unsigned int mx );
    virtual void setypos( unsigned int my );
    virtual void setwidth( unsigned int mw );
    virtual void setheight( unsigned int mh );
    virtual void setlabel(char *l);
    virtual void setcontainerstatus( bool status );
    virtual void setparent( Widget *p );
    virtual void setvisible();
    virtual void setinvisible();
    virtual void enable();
    virtual void disable();
    virtual void adjust();

    //GETTERs
    virtual unsigned int getxpos();
    virtual unsigned int getypos();
    virtual unsigned int getwidth();
    virtual unsigned int getheight();

    virtual unsigned int getuseablexpos();
    virtual unsigned int getuseableypos();
    virtual unsigned int getuseablewidth();
    virtual unsigned int getuseableheight();

    virtual char* getlabel();
    virtual bool getcontainerstatus();
    virtual Widget* getparent();
    virtual bool isenabled();
    virtual bool isvisible();
    virtual char* getwidgettype();

    //ACTION Linker
    virtual void linkonclick( void(*func)(char*) );
    virtual void linkonrelease( void(*func)(char*) );
    virtual void linkonhover( void(*func)(char*) );


protected:
    bool has_focus = false;
    bool is_enabled = true;
    bool is_visible = true;
    bool is_activated = false;
    bool is_locked = false;

    char widgettype[25];

    char label[100];                // text content of the label
    char drawablelabel[100];    // text content that can be drawn (may be shorter that full label depending on size of the widget and on the used font
    unsigned int drawablecharlabel;

    unsigned int xpos; // absolute coordinate vs screen
    unsigned int xrel; // relative coodinate to parent

    unsigned int ypos; // absolute coordinate vs screen
    unsigned int yrel; // relative coodinate to parent

    unsigned int width;
    unsigned int widrel;

    unsigned int height;
    unsigned int heirel;

    bool is_container = false;
    bool is_hovering = false;

    Widget *parent = nullptr;
    int nbchildren;
    //std::vector< Widget* > children;
    //std::vector< Widget* > popupchildren;
    std::list< Widget* > children;
    std::list< Widget* > popupchildren;

    void(*clickfunction)(char*) = nullptr;
    void(*releasefunction)(char*) = nullptr;
    void(*hoverfunction)(char*) = nullptr;

    virtual bool cursoron(CursorTask *mouse );
};

#endif // WIDGET_H

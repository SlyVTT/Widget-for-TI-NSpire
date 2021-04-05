#ifndef WIDGET_H
#define WIDGET_H

#include <vector>

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


    virtual void logic( CursorTask *mouse, KeyboardTask *keyboard );
    virtual void focus( Widget *emitter );
    virtual void unfocusup( Widget *emitter );
    virtual void unfocusdown( Widget *emitter );
    virtual void render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts );
    virtual void renderdepth( SDL_Surface *depthbuffer );
    virtual void addchild( Widget *child );
    virtual void addpopupchild( Widget *child );

    virtual void activate() { is_activated = true; };
    virtual void desactivate() { is_activated = false; };
    virtual bool isactivated() {return is_activated; };

    virtual void lock() { is_locked = true; }
    virtual void unlock() { is_locked = false; };
    virtual bool islocked() {return is_locked; };

    //SETTERs
    virtual void setdimensions( unsigned int mx, unsigned int my, unsigned int mw, unsigned int mh )
    {
        xpos=mx;
        ypos=my;
        width=mw;
        height=mh;
    };
    virtual void setxpos( unsigned int mx )
    {
        xpos=mx;
    };
    virtual void setypos( unsigned int my )
    {
        ypos=my;
    };
    virtual void setwidth( unsigned int mw )
    {
        width=mw;
    };
    virtual void setheight( unsigned int mh )
    {
        height=mh;
    };
    virtual void setlabel(char *l)
    {
        label=l;
    };
    virtual void setcontainerstatus( bool status )
    {
        is_container = status;
    };
    virtual void setparent( Widget *p );
    virtual void setvisible();
    virtual void setinvisible();
    virtual void enable();
    virtual void disable();
    virtual void adjust();

    //GETTERs
    virtual unsigned int getxpos()
    {
        return xpos;
    };
    virtual unsigned int getypos()
    {
        return ypos;
    };
    virtual unsigned int getwidth()
    {
        return width;
    };
    virtual unsigned int getheight()
    {
        return height;
    };

    virtual unsigned int getuseablexpos()
    {
        return xpos + 2 ;
    };
    virtual unsigned int getuseableypos()
    {
        return ypos + 2 ;
    };
    virtual unsigned int getuseablewidth()
    {
        return width - 4;
    };
    virtual unsigned int getuseableheight()
    {
        return height - 4;
    };

    virtual char* getlabel()
    {
        return label;
    };
    virtual bool getcontainerstatus()
    {
        return is_container;
    };
    virtual Widget* getparent()
    {
        return parent;
    };
    virtual bool getisenabled()
    {
        return is_enabled;
    };
    virtual bool isvisible()
    {
        return is_visible;
    };
    virtual char* getwidgettype()
    {
        return widgettype;
    };

    //ACTION Linker
    virtual void linkonclick( void(*func)(char*) )
    {
        clickfunction = func;
    };
    virtual void linkonrelease( void(*func)(char*) )
    {
        releasefunction = func;
    };
    virtual void linkonhover( void(*func)(char*) )
    {
        hoverfunction = func;
    };


protected:
    bool has_focus = false;
    bool is_enabled = true;
    bool is_visible = true;
    bool is_activated = false;
    bool is_locked = false;

    char *widgettype;

    char *label;                // text content of the label
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
    std::vector< Widget* > children;
    std::vector< Widget* > popupchildren;

    void(*clickfunction)(char*) = nullptr;
    void(*releasefunction)(char*) = nullptr;
    void(*hoverfunction)(char*) = nullptr;

    virtual bool cursoron(CursorTask *mouse );
};

#endif // WIDGET_H

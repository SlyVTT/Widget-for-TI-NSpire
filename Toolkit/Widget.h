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
        Widget( char *l, int x, int y, int w, int h, Widget *p );
        virtual ~Widget();

/*
        enum Event
        {
            Button_Press = 0,
            Button_Release = 1
        };
*/

        virtual void logic( CursorTask *mouse, KeyboardTask *keyboard );
        virtual void focus( Widget *emitter );
        virtual void unfocusup( Widget *emitter );
        virtual void unfocusdown( Widget *emitter );
        virtual void render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts );
//        virtual void event( Widget *source, Event event ) {};
        virtual void addchild( Widget *child );

        //SETTERs
        virtual void setdimensions( int mx, int my, int mw, int mh ) { xpos=mx; ypos=my; width=mw; height=mh; };
        virtual void setxpos( int mx ) { xpos=mx; };
        virtual void setypos( int my ) { ypos=my; };
        virtual void setwidth( int mw ) { width=mw; };
        virtual void setheight( int mh ) { height=mh; };
        virtual void setlabel(char *l) { label=l; };
        virtual void setcontainerstatus( bool status ) { is_container = status; };
        virtual void setparent( Widget *p ) { parent = p; };
        virtual void setvisible();
        virtual void setinvisible();
        virtual void enable();
        virtual void disable();
        virtual void adjust();

        //GETTERs
        virtual int getxpos() { return xpos; };
        virtual int getypos() { return ypos; };
        virtual int getwidth() { return width; };
        virtual int getheight() { return height; };

        virtual int getuseablexpos() { return xpos + 2 ; };
        virtual int getuseableypos() { return ypos + 2 ; };
        virtual int getuseablewidth() { return width - 4; };
        virtual int getuseableheight() { return height - 4; };

        virtual char* getlabel() { return label; };
        virtual bool getiscontainer() { return is_container; };
        virtual Widget* getparent() { return parent; };
        virtual bool getisenabled() { return is_enabled; };
        virtual bool getisvisible() { return is_visible; };
        virtual char* getwidgettype() {return widgettype; };

        //ACTION Linker
        virtual void linkonclick( void(*func)(char*) ) { clickfunction = func; };
        virtual void linkonrelease( void(*func)(char*) ) { releasefunction = func; };
        virtual void linkonhover( void(*func)(char*) ) { hoverfunction = func; };


    protected:
        bool has_focus = false;
        bool is_enabled = true;
        bool is_visible = true;

        char *widgettype;

        char *label;

        int xpos; // absolute coordinate vs screen
        int xrel; // relative coodinate to parent

        int ypos; // absolute coordinate vs screen
        int yrel; // relative coodinate to parent

        int width;
        int widrel;

        int height;
        int heirel;

        bool is_container = false;
        bool is_hovering = false;

        Widget *parent = nullptr;
        int nbchildren;
        std::vector< Widget* > children;

        void(*clickfunction)(char*) = nullptr;
        void(*releasefunction)(char*) = nullptr;
        void(*hoverfunction)(char*) = nullptr;

        virtual bool cursoron(CursorTask *mouse );
};

#endif // WIDGET_H

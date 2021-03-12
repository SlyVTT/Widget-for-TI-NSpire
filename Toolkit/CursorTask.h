#ifndef CURSORTASK_H
#define CURSORTASK_H

#include <SDL/SDL_video.h>


class CursorTask
{
    public:
        virtual ~CursorTask() {};

        virtual void logic();
        virtual void render( SDL_Surface *screen );
        virtual void showmouse() { show=true; };
        virtual void hidemouse() { show=false; };
        virtual bool ismousevisible() { return show; };
        virtual bool ismoouveevent() { return mouseevent; };
        virtual bool ismousemoveevent() { return mousemoveevent; };
        virtual bool ismouseclickevent() { return mouseclickevent; };
        virtual bool ismousereleaseevent() { return mousereleaseevent; };


        int x = 0;
        int y = 0;
        bool state = false;
        bool show = true;

        bool mouseevent = false;
        bool mousemoveevent = false;
        bool mouseclickevent = false;
        bool mousereleaseevent = false;
};

#endif // CURSORTASK_H

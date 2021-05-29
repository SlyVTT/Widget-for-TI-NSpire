#ifndef SPLASHSCREENWIDGET_H
#define SPLASHSCREENWIDGET_H

#include "Widget.h"


class SplashScreenWidget : public Widget
{
    public:
        SplashScreenWidget();
        SplashScreenWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p );
        virtual ~SplashScreenWidget();

        virtual void assignimage(std::string);

        virtual void logic( CursorTask *mouse, KeyboardTask *keyboard );
        virtual void render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts );

        virtual void setduration( Uint32 duration );
        virtual void start( void );

    protected:

        Uint32 timerstart = 0;
        Uint32 currenttimer = 0;
        Uint32 durationsplash = 0;

    private:
        SDL_Surface *image = nullptr;
};

#endif // SPLASHSCREENWIDGET_H

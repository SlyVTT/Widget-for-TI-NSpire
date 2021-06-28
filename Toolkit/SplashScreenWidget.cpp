#include "SplashScreenWidget.h"
#include <SDL/SDL_rotozoom.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL.h>


SplashScreenWidget::SplashScreenWidget() : Widget()
{
    widgettype = "SplashScreen";
    filereference = "";
    setinvisible();
}

SplashScreenWidget::SplashScreenWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : Widget( l, x, y, w, h, p )
{
    widgettype = "SplashScreen";
    filereference = "";
    setinvisible();
}

SplashScreenWidget::~SplashScreenWidget()
{
    SDL_FreeSurface( image );
}

void SplashScreenWidget::setduration( Uint32 duration )
{
    durationsplash = duration;
}

void SplashScreenWidget::start( void )
{
    if (image==nullptr)  assignimage( filereference );
    timerstart =SDL_GetTicks();
    setvisible();
}

void SplashScreenWidget::assignimage( std::string filename )
{
    if (image) SDL_FreeSurface( image);

    image = IMG_Load( filename.c_str() );
    filereference = filename;

    width = image->w + 6;
    height = image->h + 6;

    xpos = (SCREEN_WIDTH-image->w) /2 - 3;
    ypos = (SCREEN_HEIGHT-image->h)/2 - 3;
}

void SplashScreenWidget::logic( CursorTask *mouse, KeyboardTask *keyboard )
{
    if (is_enabled && is_visible)
    {

        is_hovering = cursoron( mouse );

        currenttimer = SDL_GetTicks();

        if ((currenttimer-timerstart) >= durationsplash)
        {
            setinvisible();
            SDL_FreeSurface( image );  // this is to save a lot of memory when SplashScreen is not used anymore
        }

        for (auto& c : children) c->logic( mouse, keyboard );     // Very few chance to occur, SplashScreen with children widgets is a bit strange
    }
}

void SplashScreenWidget::render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts )
{
    if (is_visible)
    {

        if (image)
        {
            SDL_Rect src_rect, screen_pos;

            src_rect.x = 0;
            src_rect.y = 0;

            src_rect.w = image->w;
            src_rect.h = image->h;

            screen_pos.x = (SCREEN_WIDTH-image->w) /2;
            screen_pos.y = (SCREEN_HEIGHT-image->h)/2;


            roundedBoxRGBA( screen, screen_pos.x-3, screen_pos.y-3, screen_pos.x+src_rect.w+3, screen_pos.y+ src_rect.h+3, 3, colors->widget_filling_enable.R, colors->widget_filling_enable.G, colors->widget_filling_enable.B, colors->widget_filling_enable.A);

            if (!is_hovering)
            {
                roundedRectangleRGBA( screen, screen_pos.x-3, screen_pos.y-3, screen_pos.x+src_rect.w+3, screen_pos.y+ src_rect.h+3, 3, colors->widget_border_enable.R, colors->widget_border_enable.G, colors->widget_border_enable.B, colors->widget_border_enable.A);
            }
            else
            {
                roundedRectangleRGBA( screen, screen_pos.x-3, screen_pos.y-3, screen_pos.x+src_rect.w+3, screen_pos.y+ src_rect.h+3, 3, colors->widget_border_cursoron.R, colors->widget_border_cursoron.G, colors->widget_border_cursoron.B, colors->widget_border_cursoron.A);
            }

            SDL_BlitSurface( image, &src_rect, screen, &screen_pos);
        }

        for (auto& c : children) c->render( screen, colors, fonts );
    }
    else  // CODE TO BE APPLIED WHEN THE WIDGET IS VISIBLE BUT DISABLED
    {

    }
}

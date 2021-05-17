#ifndef PROGRESSBARWIDGET_H
#define PROGRESSBARWIDGET_H

#include "Widget.h"



class ProgressBarWidget : public Widget
{
public:
       ProgressBarWidget();
       ProgressBarWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p );
       ~ProgressBarWidget();


       enum barstyle
       {
              Continuous = 0,
              Bricks = 1,
              Rainbow = 2,
              RainbowBrick = 3
       };


       virtual void logic( CursorTask *mouse, KeyboardTask *keyboard ) override;
       virtual void render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts ) override;

       virtual void setcurrentpercentage( float percent );
       virtual float getcurrentpercentage( );

       virtual void setstyle( barstyle st );
       virtual void setnumberbricks( int nb );
       virtual void setprintvalue( bool setter );


protected:
       float percentfilled = 0.0;
       barstyle style = Continuous;
       int nbbricks = 10;
       bool drawvalue = false;


private:
};

#endif // PROGRESSBARWIDGET_H

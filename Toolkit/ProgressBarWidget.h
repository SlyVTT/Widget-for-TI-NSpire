#ifndef PROGRESSBARWIDGET_H
#define PROGRESSBARWIDGET_H

#include "Widget.h"


enum barstyle
{
    Continuous = 0,
    Bricks = 1,
    Rainbow = 2,
    RainbowBrick = 3
};

class ProgressBarWidget : public Widget
{
    public:
        ProgressBarWidget() { widgettype = (char*) "ProgressBar"; };
        ProgressBarWidget( char *l, int x, int y, int w, int h, Widget *p ) : Widget( l, x, y, w, h, p ) { widgettype = (char*) "ProgressBar"; };
        ~ProgressBarWidget() { };

        virtual void logic( CursorTask *mouse, KeyboardTask *keyboard ) override;
        virtual void render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts ) override;

        virtual void setcurrentpercentage( float percent ) { percentfilled = percent; };
        virtual float getcurrentpercentage( ) { return percentfilled; };

        virtual void setstyle( barstyle st ) { style = st; };
        virtual void setnumberbricks( int nb ) { nbbricks = nb; };

        virtual void setprintvalue( bool setter ) { drawvalue = setter; };


    protected:
        float percentfilled = 0.0;
        barstyle style = Continuous;
        int nbbricks = 10;
        bool drawvalue = false;


    private:
};

#endif // PROGRESSBARWIDGET_H

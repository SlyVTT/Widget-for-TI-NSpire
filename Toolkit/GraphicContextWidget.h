#ifndef GRAPHICCONTEXTWIDGET_H
#define GRAPHICCONTEXTWIDGET_H

#include "Widget.h"


class GraphicContextWidget : public Widget
{
public:
       GraphicContextWidget();
       GraphicContextWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p );
       virtual ~GraphicContextWidget();

       virtual void logic( CursorTask *mouse, KeyboardTask *keyboard ) override;
       virtual void render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts ) override;

       enum drawmode
       {
           normal = 0,              // zoomx = zoomy = 1
           fitX = 1,                     // zoomx is based on image width and widget width and applied to Y
           fitY = 2,                     // zoomy is based on image height and widget height and applied to X
           fitbest = 3,                // both zoomx and zoomy are calculated and then min (fitX, fitY)
           userzoom = 4           // user defined zoom is applied to X and Y
       };

       virtual void assignsurface( SDL_Surface *surface );
       virtual void setmode( drawmode mode );

protected:
        SDL_Surface *surfacetobedrawn = nullptr;

        drawmode currentmode = normal;

        double zoomx = 1.0f;
        double zoomy = 1.0f;

        double userzoomfactor = 1.0f;

private:


};

#endif // GRAPHICCONTEXTWIDGET_H

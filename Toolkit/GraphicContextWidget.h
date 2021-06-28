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

    SDL_Surface *createemptyimage( unsigned int width, unsigned int height );
    SDL_Surface *createemptyimagecolor( unsigned int width, unsigned int height, unsigned short R, unsigned short G, unsigned short B, unsigned short A  );

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

    void setuserzoomlevel( float level );
    void update( void );

    void adjust() override;

protected:
    SDL_Surface *surfacetobedrawn = nullptr;
    SDL_Surface *transformedimage = nullptr;

    drawmode currentmode = normal;

    unsigned int posviewX = 0;
    unsigned int posviewY = 0;

    unsigned int shiftposX = 0;
    unsigned int shiftposY = 0;

    unsigned int widthuseableGC = 0;            // this correspond to the actual width of the widget that can be used (equals width but can be reduce by 15pixels if escalators are drawn)
    unsigned int heightuseableGC = 0;         // this correspond to the actual height of the widget that can be used (equals height but can be reduce by 15pixels if escalators are drawn)

    bool escalatorH = false;
    bool escalatorV = false;

    bool scrollableX = false;
    bool scrollableY = false;

    double zoomx = 1.0f;
    double zoomy = 1.0f;

    double userzoomfactor = 1.0f;

private:


};

#endif // GRAPHICCONTEXTWIDGET_H

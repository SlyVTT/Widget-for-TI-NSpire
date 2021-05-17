#include "GraphicContextWidget.h"
#include <SDL/SDL_rotozoom.h>


GraphicContextWidget::GraphicContextWidget() : Widget()
{
       widgettype = "GraphicContext";
}


GraphicContextWidget::GraphicContextWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : Widget( l, x, y, w, h, p )
{
       widgettype = "GraphicContext";
}


GraphicContextWidget::~GraphicContextWidget()
{
       surfacetobedrawn = nullptr;
}


void GraphicContextWidget::assignsurface( SDL_Surface *surface )
{
       surfacetobedrawn = surface;
}


void GraphicContextWidget::setmode( drawmode mode )
{

       if (mode == normal)
       {
              zoomx = 1.0;
              zoomy = 1.0;
       }
       else if (mode == fitX)
       {
              if (surfacetobedrawn)
              {
                     zoomx = (double) ((double) width / (double) surfacetobedrawn->w);
                     zoomy = zoomx;
              }
       }
       else if (mode == fitY)
       {
              if (surfacetobedrawn)
              {
                     zoomy = (double) ((double) height / (double) surfacetobedrawn->h);
                     zoomx = zoomy;
              }
       }
       else if (mode == fitbest)
       {
              if (surfacetobedrawn)
              {
                     zoomx = (double) ((double) width / (double) surfacetobedrawn->w);
                     zoomy = (double) ((double) height / (double) surfacetobedrawn->h);
                     double zoomtobeused = std::min(zoomx, zoomy);
                     zoomx=zoomtobeused;
                     zoomy=zoomtobeused;
              }
       }
       else if (mode == userzoom)
       {
              zoomx = userzoomfactor;
              zoomy = userzoomfactor;
       }

}


void GraphicContextWidget::logic( CursorTask *mouse, KeyboardTask *keyboard )
{
       if (is_enabled && is_visible)
       {
              is_hovering = cursoron( mouse );
              bool currently_pressed = (mouse->state || keyboard->kbSCRATCH) && is_hovering;

              if(currently_pressed)
              {
                     if (clickfunction) clickfunction( (char*) "test" );
              }
              else if(is_hovering)
              {
                     if (hoverfunction) hoverfunction( (char*) "test" );
              }

              if (currently_pressed &&!has_focus)
                     focus( this );

              if (!has_focus)
                     return;

              for (auto& c : children) c->logic( mouse, keyboard );
       }
}


void GraphicContextWidget::render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts )
{
       if (is_visible)
       {
              if (is_enabled)  // CODE TO BE APPLIED WHEN THE WIDGET IS VISIBLE AND ENABLED
              {
                     roundedBoxRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_filling_enable.R, colors->widget_filling_enable.G, colors->widget_filling_enable.B, colors->widget_filling_enable.A);

                     if (!is_hovering)
                     {
                            roundedRectangleRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_border_enable.R, colors->widget_border_enable.G, colors->widget_border_enable.B, colors->widget_border_enable.A);
                     }
                     else
                     {
                            roundedRectangleRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_border_cursoron.R, colors->widget_border_cursoron.G, colors->widget_border_cursoron.B, colors->widget_border_cursoron.A);
                     }

                     if (surfacetobedrawn)
                     {
                            SDL_Rect src_rect, screen_pos;
                            src_rect.x = 0;
                            src_rect.y = 0;
                            src_rect.w = width-4;
                            src_rect.h = height-4;
                            screen_pos.x = xpos+2;
                            screen_pos.y = ypos+2;
                            SDL_BlitSurface( surfacetobedrawn, &src_rect, screen, &screen_pos);
                     }

              }
              else  // CODE TO BE APPLIED WHEN THE WIDGET IS VISIBLE BUT DISABLED
              {
                     roundedBoxRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_filling_disable.R, colors->widget_filling_disable.G, colors->widget_filling_disable.B, colors->widget_filling_disable.A);

                     roundedRectangleRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_border_disable.R, colors->widget_border_disable.G, colors->widget_border_disable.B, colors->widget_border_disable.A);
              }

              if (surfacetobedrawn)
              {
                     SDL_Rect src_rect, screen_pos;
                     src_rect.x = 0;
                     src_rect.y = 0;
                     src_rect.w = width-4;
                     src_rect.h = height-4;
                     screen_pos.x = xpos+2;
                     screen_pos.y = ypos+2;
                     SDL_BlitSurface( surfacetobedrawn, &src_rect, screen, &screen_pos);
              }

              for (auto& c : children) c->render( screen, colors, fonts );
       }
}

#include "GraphicContextWidget.h"
#include <SDL/SDL_rotozoom.h>


GraphicContextWidget::GraphicContextWidget() : Widget()
{
       widgettype = "GraphicContext";
       widthuseableGC = width;
       heightuseableGC = height;
       posviewX = 0;
       posviewY = 0;
       shiftposX = 0;
       shiftposY = 0;
}


GraphicContextWidget::GraphicContextWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : Widget( l, x, y, w, h, p )
{
       widgettype = "GraphicContext";
       widthuseableGC = width;
       heightuseableGC = height;
       posviewX = 0;
       posviewY = 0;
       shiftposX = 0;
       shiftposY = 0;
}


GraphicContextWidget::~GraphicContextWidget()
{
       surfacetobedrawn = nullptr;
       SDL_FreeSurface( transformedimage );
}


void GraphicContextWidget::assignsurface( SDL_Surface *surface )
{
       surfacetobedrawn = surface;
       setuserzoomlevel( 1.0f );
       update();
}


void GraphicContextWidget::setmode( drawmode mode )
{

       if (mode == normal)
       {
              zoomx = 1.0;
              zoomy = 1.0;
              userzoomfactor = 1.0;
       }
       else if (mode == fitX)
       {
              if (surfacetobedrawn)
              {
                     zoomx = (double) ((double) width / (double) surfacetobedrawn->w);
                     userzoomfactor= zoomy = zoomx;
              }
       }
       else if (mode == fitY)
       {
              if (surfacetobedrawn)
              {
                     zoomy = (double) ((double) height / (double) surfacetobedrawn->h);
                     userzoomfactor = zoomx = zoomy;
              }
       }
       else if (mode == fitbest)
       {
              if (surfacetobedrawn)
              {
                     zoomx = (double) ((double) width / (double) surfacetobedrawn->w);
                     zoomy = (double) ((double) height / (double) surfacetobedrawn->h);
                     double zoomtobeused = std::min(zoomx, zoomy);
                     userzoomfactor = zoomx = zoomy = zoomtobeused;
              }
       }
       else if (mode == userzoom)
       {
              zoomx = userzoomfactor;
              zoomy = userzoomfactor;
       }

       update();
}


void GraphicContextWidget::setuserzoomlevel( float level )
{
       userzoomfactor = level;
       setmode( userzoom );
       update();
}


void GraphicContextWidget::adjust( void )
{
       update();
}


void GraphicContextWidget::update( void )
{
       if (transformedimage)
       {
              SDL_FreeSurface( transformedimage);
              transformedimage = rotozoomSurfaceXY( surfacetobedrawn, 0, zoomx, zoomy, 0);
       }
       else
       {
              transformedimage = rotozoomSurfaceXY( surfacetobedrawn, 0, zoomx, zoomy, 0);
       }


       if ((unsigned int) transformedimage->w <= width )
       {
              shiftposX = (widthuseableGC - transformedimage->w) /2;
              posviewX = 0;
              escalatorH = false;
              scrollableX = false;
              heightuseableGC = height;
       }
       else
       {
              shiftposX = 0;
              posviewX = 0;
              escalatorH = true;
              scrollableX = true;
              heightuseableGC = height - 15;
       }


       if ((unsigned int) transformedimage->h <= height )
       {
              shiftposY = (heightuseableGC - transformedimage->h) /2;
              posviewY = 0;
              escalatorV = false;
              scrollableY = false;
              widthuseableGC = width;
       }
       else
       {
              shiftposY = 0;
              posviewY = 0;
              escalatorV = true;
              scrollableY = true;
              widthuseableGC = width - 15;
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

              // if the picture to be displayed is smaller than the size of the widget, we need to compute the centered position
              if (transformedimage)
              {
                     if ((unsigned int) transformedimage->w <= width )
                     {
                            shiftposX = (widthuseableGC - transformedimage->w) /2;
                            posviewX = 0;
                            escalatorH = false;
                            scrollableX = false;
                            heightuseableGC = height;
                     }
                     else
                     {
                            shiftposX=0;
                            escalatorH = true;
                            scrollableX = true;
                            heightuseableGC = height - 15;
                     }

                     if ((unsigned int) transformedimage->h <= height )
                     {
                            shiftposY = (heightuseableGC - transformedimage->h) /2;
                            posviewY = 0;
                            escalatorV = false;
                            scrollableY = false;
                            widthuseableGC = width;
                     }
                     else
                     {
                            shiftposY=0;
                            escalatorV = true;
                            scrollableY = true;
                            widthuseableGC = width - 15;
                     }


                     if (!has_focus)
                            return;



                     if (keyboard->kbPLUS && (userzoomfactor <= 5.0f))
                     {
                            userzoomfactor += 0.1f;
                            zoomx += 0.1f;
                            zoomy += 0.1f;
                            update();
                     }

                     if (keyboard->kbMINUS && (userzoomfactor >= 0.1f))
                     {
                            userzoomfactor -= 0.1f;
                            zoomx -= 0.1f;
                            zoomy -= 0.1f;
                            update();
                     }



                     if (scrollableX && keyboard->kbLEFT)
                     {
                            if (posviewX > 5) posviewX -= 5;
                            else posviewX = 0;
                     }

                     if (scrollableX && keyboard->kbRIGHT)
                     {
                            if (posviewX < transformedimage->w - widthuseableGC - 5) posviewX += 5;
                            else posviewX = transformedimage->w - widthuseableGC;
                     }

                     if (scrollableY && keyboard->kbUP)
                     {
                            if (posviewY > 5) posviewY -= 5;
                            else posviewY = 0;
                     }

                     if (scrollableY && keyboard->kbDOWN)
                     {
                            if (posviewY < transformedimage->h - heightuseableGC - 5) posviewY += 5;
                            else posviewY = transformedimage->h - heightuseableGC;
                     }


                     if (posviewX<=0) posviewX=0;

                     if (posviewY<=0) posviewY=0;

                     if (posviewX>transformedimage->w-widthuseableGC)    posviewX=transformedimage->w-widthuseableGC;

                     if (posviewY>transformedimage->h-heightuseableGC)    posviewY=transformedimage->w-heightuseableGC;

              }

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

                            if (transformedimage)
                            {
                                   SDL_Rect src_rect, screen_pos;

                                   src_rect.x = posviewX;
                                   src_rect.y = posviewY;

                                   src_rect.w = widthuseableGC;
                                   src_rect.h = heightuseableGC;

                                   if (escalatorV)
                                   {
                                          roundedRectangleRGBA( screen, xpos+width-12, ypos+4, xpos+width-4, ypos+height-12, 3, colors->widget_border_enable.R, colors->widget_border_enable.G, colors->widget_border_enable.B, colors->widget_border_enable.A);
                                          roundedRectangleRGBA( screen, xpos+width-12, ypos+height-12, xpos+width-4, ypos+height-4, 3, colors->widget_border_enable.R, colors->widget_border_enable.G, colors->widget_border_enable.B, colors->widget_border_enable.A);

                                          unsigned int y = ((height-7-15)*posviewY / (transformedimage->h - heightuseableGC));

                                          filledCircleRGBA( screen, xpos+width-8, ypos+7+y, 3, colors->widget_border_enable.R, colors->widget_border_enable.G, colors->widget_border_enable.B, colors->widget_border_enable.A);
                                   }

                                   if (escalatorH)
                                   {
                                          roundedRectangleRGBA( screen, xpos+4, ypos+height-12, xpos+width-12, ypos+height-4, 3, colors->widget_border_enable.R, colors->widget_border_enable.G, colors->widget_border_enable.B, colors->widget_border_enable.A);
                                          roundedRectangleRGBA( screen, xpos+width-12, ypos+height-12, xpos+width-4, ypos+height-4, 3, colors->widget_border_enable.R, colors->widget_border_enable.G, colors->widget_border_enable.B, colors->widget_border_enable.A);

                                          unsigned int x = ((width-7-15)*posviewX / (transformedimage->w - widthuseableGC));

                                          filledCircleRGBA( screen, xpos+7+x, ypos+height-8, 3, colors->widget_border_enable.R, colors->widget_border_enable.G, colors->widget_border_enable.B, colors->widget_border_enable.A);
                                   }

                                   screen_pos.x = xpos+shiftposX;
                                   screen_pos.y = ypos+shiftposY;

                                   SDL_BlitSurface( transformedimage, &src_rect, screen, &screen_pos);
                            }
                     }
                     else
                     {
                            roundedRectangleRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_border_cursoron.R, colors->widget_border_cursoron.G, colors->widget_border_cursoron.B, colors->widget_border_cursoron.A);


                            // TO BE UPDATED WITH THE RIGHT COLORS
                            if (transformedimage)
                            {
                                   SDL_Rect src_rect, screen_pos;

                                   src_rect.x = posviewX;
                                   src_rect.y = posviewY;

                                   src_rect.w = widthuseableGC;
                                   src_rect.h = heightuseableGC;

                                   if (escalatorV)
                                   {
                                          roundedRectangleRGBA( screen, xpos+width-12, ypos+4, xpos+width-4, ypos+height-12, 3, colors->widget_border_cursoron.R, colors->widget_border_cursoron.G, colors->widget_border_cursoron.B, colors->widget_border_cursoron.A);
                                          roundedRectangleRGBA( screen, xpos+width-12, ypos+height-12, xpos+width-4, ypos+height-4, 3, colors->widget_border_cursoron.R, colors->widget_border_cursoron.G, colors->widget_border_cursoron.B, colors->widget_border_cursoron.A);

                                          unsigned int y = ((height-7-15)*posviewY / (transformedimage->h - heightuseableGC));

                                          filledCircleRGBA( screen, xpos+width-8, ypos+7+y, 3, colors->widget_border_cursoron.R, colors->widget_border_cursoron.G, colors->widget_border_cursoron.B, colors->widget_border_cursoron.A);
                                   }

                                   if (escalatorH)
                                   {
                                          roundedRectangleRGBA( screen, xpos+4, ypos+height-12, xpos+width-12, ypos+height-4, 3, colors->widget_border_cursoron.R, colors->widget_border_cursoron.G, colors->widget_border_cursoron.B, colors->widget_border_cursoron.A);
                                          roundedRectangleRGBA( screen, xpos+width-12, ypos+height-12, xpos+width-4, ypos+height-4, 3, colors->widget_border_cursoron.R, colors->widget_border_cursoron.G, colors->widget_border_cursoron.B, colors->widget_border_cursoron.A);

                                          unsigned int x = ((width-7-15)*posviewX / (transformedimage->w - widthuseableGC));

                                          filledCircleRGBA( screen, xpos+7+x, ypos+height-8, 3, colors->widget_border_cursoron.R, colors->widget_border_cursoron.G, colors->widget_border_cursoron.B, colors->widget_border_cursoron.A);
                                   }

                                   screen_pos.x = xpos+shiftposX;
                                   screen_pos.y = ypos+shiftposY;

                                   SDL_BlitSurface( transformedimage, &src_rect, screen, &screen_pos);

                            }

                     }
              }
              else  // CODE TO BE APPLIED WHEN THE WIDGET IS VISIBLE BUT DISABLED
              {
                     roundedBoxRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_filling_disable.R, colors->widget_filling_disable.G, colors->widget_filling_disable.B, colors->widget_filling_disable.A);

                     roundedRectangleRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_border_disable.R, colors->widget_border_disable.G, colors->widget_border_disable.B, colors->widget_border_disable.A);

                     // TO BE UPDATED WITH THE RIGHT COLORS
                     if (transformedimage)
                     {
                            SDL_Rect src_rect, screen_pos;

                            src_rect.x = posviewX;
                            src_rect.y = posviewY;

                            src_rect.w = widthuseableGC;
                            src_rect.h = heightuseableGC;

                            if (escalatorV)
                            {
                                   roundedRectangleRGBA( screen, xpos+width-12, ypos+4, xpos+width-4, ypos+height-12, 3, colors->widget_border_disable.R, colors->widget_border_disable.G, colors->widget_border_disable.B, colors->widget_border_disable.A);
                                   roundedRectangleRGBA( screen, xpos+width-12, ypos+height-12, xpos+width-4, ypos+height-4, 3, colors->widget_border_disable.R, colors->widget_border_disable.G, colors->widget_border_disable.B, colors->widget_border_disable.A);

                                   unsigned int y = ((height-7-15)*posviewY / (transformedimage->h - heightuseableGC));

                                   filledCircleRGBA( screen, xpos+width-8, ypos+7+y, 3, colors->widget_border_disable.R, colors->widget_border_disable.G, colors->widget_border_disable.B, colors->widget_border_disable.A);
                            }

                            if (escalatorH)
                            {
                                   roundedRectangleRGBA( screen, xpos+4, ypos+height-12, xpos+width-12, ypos+height-4, 3, colors->widget_border_disable.R, colors->widget_border_disable.G, colors->widget_border_disable.B, colors->widget_border_disable.A);
                                   roundedRectangleRGBA( screen, xpos+width-12, ypos+height-12, xpos+width-4, ypos+height-4, 3, colors->widget_border_disable.R, colors->widget_border_disable.G, colors->widget_border_disable.B, colors->widget_border_disable.A);

                                   unsigned int x = ((width-7-15)*posviewX / (transformedimage->w - widthuseableGC));

                                   filledCircleRGBA( screen, xpos+7+x, ypos+height-8, 3, colors->widget_border_disable.R, colors->widget_border_disable.G, colors->widget_border_disable.B, colors->widget_border_disable.A);
                            }

                            screen_pos.x = xpos+shiftposX;
                            screen_pos.y = ypos+shiftposY;

                            SDL_BlitSurface( transformedimage, &src_rect, screen, &screen_pos);

                     }

              }

              for (auto& c : children) c->render( screen, colors, fonts );
       }
}

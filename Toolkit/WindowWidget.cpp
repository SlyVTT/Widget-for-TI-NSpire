#include "WindowWidget.h"

WindowWidget::WindowWidget( )
{
       widgettype = "Window";
       //strcpy( widgettype, (char*) "Window");
};

WindowWidget::WindowWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : Widget( l, x, y, w, h, p )
{
       widgettype = "Window";
       //strcpy( widgettype, (char*) "Window");
       xposback = x;
       yposback = y;
       widthback = w;
       heightback = h;
};

WindowWidget::~WindowWidget()
{

};

void WindowWidget::setminimaldimensions( unsigned int widmin, unsigned int heimin)
{
       minwidth = widmin;
       minheight = heimin;
};

void WindowWidget::setmenubar()
{
       hasmenubar = true;
};

void WindowWidget::seticonbar()
{
       hasiconbar = true;
};

bool WindowWidget::getmenubar()
{
       return hasmenubar;
};

bool WindowWidget::geticonbar()
{
       return hasiconbar;
};


unsigned int WindowWidget::getuseablexpos()
{
       return xpos + 2;
}


unsigned int WindowWidget::getuseableypos()
{
       if (!hasmenubar && !hasiconbar) return ypos + 14;               // we just remove the size of the title bar (12px+2px = 14px)
       else if (hasmenubar && !hasiconbar) return ypos + 14 + 12;            // we remove the size of the title bar and of the menu bar (14px + 12px)
       else if (hasmenubar && hasiconbar) return ypos + 14 + 12 + 20;        // we remove the size of the title bar, of the menu bar and of the icon bar (14px + 12px + 20px)
       else return ypos + 14 + 20;        // we remove the size of the title bar, of the menu bar and of the icon bar (14px + 12px + 20px)
}


unsigned int WindowWidget::getuseablewidth()
{
       return width - 4;
}


unsigned int WindowWidget::getuseableheight()
{
       if (!hasmenubar && !hasiconbar) return height - 16;                // we just remove the size of the title bar (12px + 2px + 2px = 16px)
       else if (hasmenubar && !hasiconbar) return height - 16 - 12;            // we remove the size of the title bar and of the menu bar (16px + 12px)
       else if (hasmenubar && hasiconbar) return height - 16 - 12 - 20;        // we remove the size of the title bar, of the menu bar and of the icon bar (16px + 12px + 20px)
       else return height - 16 - 20;            // we remove the size of the title bar, of the menu bar and of the icon bar (16px + 12px + 20px)
}


bool WindowWidget::ismouseatleftborder(CursorTask *mouse)
{
       return ((unsigned int) mouse->x >= xpos-2) && ((unsigned int) mouse->y >= ypos+2) && ((unsigned int) mouse->x <= xpos+2) && ((unsigned int) mouse->y <= ypos+height-2);
}


bool WindowWidget::ismouseatrightborder(CursorTask *mouse)
{
       return ((unsigned int) mouse->x >= xpos+width-2) && ((unsigned int) mouse->y >= ypos+2) && ((unsigned int) mouse->x <= xpos+width+2) && ((unsigned int) mouse->y <= ypos+height-2);
}


bool WindowWidget::ismouseattopborder(CursorTask *mouse)
{
       return ((unsigned int) mouse->x >= xpos+2) && ((unsigned int) mouse->y >= ypos-2) && ((unsigned int) mouse->x <= xpos+width-2) && ((unsigned int) mouse->y <= ypos+2);
}


bool WindowWidget::ismouseatbottomborder(CursorTask *mouse)
{
       return ((unsigned int) mouse->x >= xpos+2) && ((unsigned int) mouse->y >= ypos+height-2) && ((unsigned int) mouse->x <= xpos+width-2) && ((unsigned int) mouse->y <= ypos+height+2);
}


bool WindowWidget::ismouseontitlebar(CursorTask *mouse)
{
       return ((unsigned int) mouse->x >= xpos+2) && ((unsigned int) mouse->y >= ypos+2) && ((unsigned int) mouse->x <= xpos+width-32) && ((unsigned int) mouse->y <= ypos+12);
}


bool WindowWidget::ismouseonminimisebutton(CursorTask *mouse)
{
       return ((unsigned int) mouse->x >= xpos+width-32) && ((unsigned int) mouse->y >= ypos+2) && ((unsigned int) mouse->x <= xpos+width-22) && ((unsigned int) mouse->y <= ypos+12);
}


bool WindowWidget::ismouseonrestorebutton(CursorTask *mouse)
{
       return ((unsigned int) mouse->x >= xpos+width-22) && ((unsigned int) mouse->y >= ypos+2) && ((unsigned int) mouse->x <= xpos+width-12) && ((unsigned int) mouse->y <= ypos+12);
}


bool WindowWidget::ismouseonmaximisebutton(CursorTask *mouse)
{
       return ((unsigned int) mouse->x >= xpos+width-12) && ((unsigned int) mouse->y >= ypos+2) && ((unsigned int) mouse->x <= xpos+width-2) && ((unsigned int) mouse->y <= ypos+12);
}



void WindowWidget::maximize()
{
       if (ismaximized)
       {
              xpos = xposback;
              ypos = yposback;
              width = widthback;
              height = heightback;

              for (auto& c : children )
                     c->setvisible();

              ismaximized = false;
              isminimized = false;

              adjust();
       }
       else if (isminimized)
       {
              restore();
       }
       else
       {
              xposback = xpos;
              yposback = ypos;
              widthback = width;
              heightback = height;

              //xpos = 0;
              //ypos = 0;
              //width = SCREEN_WIDTH;
              //height = SCREEN_HEIGHT;

              xpos = parent->getuseablexpos();
              ypos = parent->getuseableypos();
              width = parent->getuseablewidth();
              height = parent->getuseableheight();


              for (auto& c : children )
                     c->setvisible();

              ismaximized = true;
              isminimized = false;

              adjust();
       }
}

void WindowWidget::minimize()
{
       if (isminimized)
       {
              xpos = xposback;
              ypos = yposback;
              width = widthback;
              height = heightback;

              for (auto& c : children )
                     c->setvisible();

              ismaximized = false;
              isminimized = false;

              adjust();
       }
       else if (ismaximized)
       {
              restore();
       }
       else
       {
              xposback = xpos;
              yposback = ypos;
              widthback = width;
              heightback = height;

              //xpos = 0;
              //ypos = 0;
              //width = SCREEN_WIDTH;
              //height = 12;

              xpos = parent->getuseablexpos();
              ypos = parent->getuseableypos();
              width = parent->getuseablewidth();
              height = 12;

              for (auto& c : children )
                     c->setinvisible();

              ismaximized = false;
              isminimized = true;

              adjust();
       }
}

void WindowWidget::restore()
{
       if (!ismaximized && !isminimized)
       {
              xposback = xpos;
              yposback = ypos;
              widthback = width;
              heightback = height;
       }
       else
       {
              xpos = xposback;
              ypos = yposback;
              width = widthback;
              height = heightback;

              for (auto& c : children )
                     c->setvisible();

              ismaximized = false;
              isminimized = false;

              adjust();
       }
}

void WindowWidget::logic( CursorTask *mouse, KeyboardTask *keyboard )
{
       unsigned int nbpopupvisible = 0;
       for (auto& d : popupchildren )
              if (d->isvisible())
              {
                     nbpopupvisible++;
                     d->logic( mouse, keyboard );
              }

       if (nbpopupvisible==0)
       {
              if (is_activated)
              {

                     is_hovering = cursoron( mouse );

                     if(is_hovering)
                     {
                            if (hoverfunction)
                                   hoverfunction( (char*) "test" );
                     }

                     bool atborder = false;
                     bool ontitle = false;
                     bool onmax = false;
                     bool onmin = false;
                     bool onres = false;

                     if (ismouseatleftborder( mouse ))
                     {
                            mouse->setcursortype( CursorTask::leftrightresize );
                            atborder = true;
                     }
                     else if (ismouseatrightborder( mouse ))
                     {
                            mouse->setcursortype( CursorTask::leftrightresize );
                            atborder = true;
                     }
                     else if (ismouseattopborder( mouse ))
                     {
                            mouse->setcursortype( CursorTask::topbottomresize );
                            atborder = true;
                     }
                     else if (ismouseatbottomborder( mouse ))
                     {
                            mouse->setcursortype( CursorTask::topbottomresize );
                            atborder = true;
                     }
                     else if (ismouseontitlebar( mouse ))
                     {
                            mouse->setcursortype( CursorTask::handfinger );
                            ontitle = true;
                     }
                     else if (ismouseonmaximisebutton( mouse ))
                     {
                            mouse->setcursortype( CursorTask::triangle );
                            onmax = true;
                     }
                     else if (ismouseonminimisebutton( mouse ))
                     {
                            mouse->setcursortype( CursorTask::triangle );
                            onmin = true;
                     }
                     else if (ismouseonrestorebutton( mouse ))
                     {
                            mouse->setcursortype( CursorTask::triangle );
                            onres = true;
                     }
                     else
                     {
                            mouse->setcursortype( CursorTask::pointer );
                     }


                     if (atborder && keyboard->kbSCRATCH)
                     {
                            resizemode = true;
                     }
                     else
                     {
                            resizemode = false;
                     }

                     if (onmax && keyboard->kbSCRATCH)
                     {
                            maximize();
                            onmax = false;
                     }

                     if (onmin && keyboard->kbSCRATCH)
                     {
                            minimize();
                            onmin = false;
                     }

                     if (onres && keyboard->kbSCRATCH)
                     {
                            restore();
                            onres = false;
                     }

                     if (ontitle && keyboard->kbSCRATCH && !startmove)
                     {
                            movemode = true;
                            startmove = true;
                            clickX = mouse->x;
                            clickY = mouse->y;
                     }
                     else if (ontitle && keyboard->kbSCRATCH && startmove)
                     {
                            movemode = true;
                     }
                     else
                     {
                            movemode = false;
                            startmove = false;
                     }

                     // Here comes the resize logic
                     if (resizemode && ismouseatleftborder( mouse ))
                     {
                            unsigned int xposold = xpos;
                            mouse->logic();
                            //if ((mouse->x > 2) && (width + xposold - mouse->x >= minwidth)) xpos = mouse->x;
                            if (((unsigned int) mouse->x > parent->getuseablexpos()) && (width + xposold - mouse->x >= minwidth)) xpos = mouse->x;
                            width += (xposold - xpos);
                            adjust();
                     }

                     if (resizemode && ismouseatrightborder( mouse ))
                     {
                            mouse->logic();
                            //if ((mouse->x < SCREEN_WIDTH-2) && (mouse->x - xpos >= minwidth)) width = mouse->x - xpos;
                            if (((unsigned int) mouse->x < parent->getuseablexpos()+parent->getuseablewidth()) && (mouse->x - xpos >= minwidth)) width = mouse->x - xpos;
                            adjust();
                     }

                     if (resizemode && ismouseattopborder( mouse ))
                     {
                            unsigned int yposold = ypos;
                            mouse->logic();
                            //if ((mouse->y > 2) && (height + yposold - mouse->y >= minheight)) ypos = mouse->y;
                            if (((unsigned int) mouse->y > parent->getuseableypos()) && (height + yposold - mouse->y >= minheight)) ypos = mouse->y;
                            height += (yposold - ypos);
                            adjust();
                     }

                     if (resizemode && ismouseatbottomborder( mouse ))
                     {
                            mouse->logic();
                            //if ((mouse->y < SCREEN_HEIGHT-2) && (mouse->y - ypos >= minheight)) height = mouse->y - ypos;
                            if (((unsigned int) mouse->y < parent->getuseableypos()+parent->getuseableheight()) && (mouse->y - ypos >= minheight)) height = mouse->y - ypos;
                            adjust();
                     }

                     // Here comes the move logic ...
                     if (movemode && ismouseontitlebar( mouse ))
                     {
                            mouse->logic();

                            int deltax = (int) mouse->x - (int) clickX;
                            int deltay = (int) mouse->y - (int) clickY;

                            //we go left
                            if (deltax < 0)
                            {
                                   //if ((int) xpos > (int) (-1 * deltax))   xpos += deltax;
                                   if ((int) (xpos + deltax) > (int) parent->getuseablexpos() )   xpos += deltax;
                            }
                            //we go up
                            if (deltay < 0)
                            {
                                   //if ((int) ypos > (int) (-1 * deltay))   ypos += deltay;
                                   if ((int) (ypos + deltay) > (int) parent->getuseableypos() )   ypos += deltay;
                            }

                            //we go right
                            if (deltax > 0)
                            {
                                   //if ((int) (SCREEN_WIDTH - xpos - width) > (int) (deltax))   xpos += deltax;
                                   if ((int) (parent->getuseablexpos() + parent->getuseablewidth() - xpos - width) > (int) (deltax))   xpos += deltax;
                            }
                            //we go down
                            if (deltay > 0)
                            {
                                   //if ((int) (SCREEN_HEIGHT - ypos - height) > (int) (deltay))   ypos += deltay;
                                   if ((int) (parent->getuseableypos() + parent->getuseableheight() - ypos - height) > (int) (deltay))   ypos += deltay;
                            }

                            adjust();

                            clickX = mouse->x;
                            clickY = mouse->y;
                     }

                     for (auto& c : children )
                            c->logic( mouse, keyboard );
              }

              //PUT ON TOP TO START WITH POPUPCHILD LOGIC
              //for (auto& d : popupchildren )
              //              d->logic( mouse, keyboard );

       }
}


void WindowWidget::render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts )
{

       if (is_visible)
       {

              if (is_enabled)
              {
                     roundedBoxRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_filling_enable.R, colors->widget_filling_enable.G, colors->widget_filling_enable.B, colors->widget_filling_enable.A);
                     roundedBoxRGBA( screen, xpos, ypos, xpos+width, ypos+12, 3, colors->window_titlebar_enable.R, colors->window_titlebar_enable.G, colors->window_titlebar_enable.B, colors->window_titlebar_enable.A);

                     if (!is_hovering)
                     {
                            roundedRectangleRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_border_enable.R, colors->widget_border_enable.G, colors->widget_border_enable.B, colors->widget_border_enable.A);
                     }
                     else
                     {
                            roundedRectangleRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_border_cursoron.R, colors->widget_border_cursoron.G, colors->widget_border_cursoron.B, colors->widget_border_cursoron.A);
                     }

                     // Draw the minimize round button
                     filledCircleRGBA( screen, xpos+width-27, ypos+6, 3, colors->window_titlebar_minimize.R, colors->window_titlebar_minimize.G, colors->window_titlebar_minimize.B, colors->window_titlebar_minimize.A);
                     // Draw the restore round button
                     filledCircleRGBA( screen, xpos+width-17, ypos+6, 3, colors->window_titlebar_restore.R, colors->window_titlebar_restore.G, colors->window_titlebar_restore.B, colors->window_titlebar_restore.A);
                     // Draw the maximize round button
                     filledCircleRGBA( screen, xpos+width-7, ypos+6, 3, colors->window_titlebar_maximize.R, colors->window_titlebar_maximize.G, colors->window_titlebar_maximize.B, colors->window_titlebar_maximize.A);

                     fonts->setcurrentfont( fonts->window_titlebartext_enable.name );
                     fonts->setmodifiertypo( fonts->window_titlebartext_enable.typo );
                     fonts->setmodifierunder( fonts->window_titlebartext_enable.under );
                     fonts->setmodifierstrike( fonts->window_titlebartext_enable.strike );

                     drawablecharlabel = fonts->assertstringlength( label, width-5-5-30 );

                     if (drawablecharlabel!=0)
                     {
                            drawablelabel = fonts->reducestringtovisible( label, width-5 -5 -30 );

                            //int sl = fonts->getstringwidth( drawablelabel );
                            int sh = fonts->getstringheight( drawablelabel );
                            fonts->drawstringleft( screen, drawablelabel, xpos+5, ypos+sh/2, colors->window_titlebartext_enable.R, colors->window_titlebartext_enable.G, colors->window_titlebartext_enable.B, colors->window_titlebartext_enable.A );
                     }
              }
              else
              {
                     roundedBoxRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_filling_disable.R, colors->widget_filling_disable.G, colors->widget_filling_disable.B, colors->widget_filling_disable.A);
                     roundedBoxRGBA( screen, xpos, ypos, xpos+width, ypos+12, 3, colors->window_titlebar_disable.R, colors->window_titlebar_disable.G, colors->window_titlebar_disable.B, colors->window_titlebar_disable.A);
                     roundedRectangleRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_border_disable.R, colors->widget_border_disable.G, colors->widget_border_disable.B, colors->widget_border_disable.A);

                     fonts->setcurrentfont( fonts->window_titlebartext_disable.name );
                     fonts->setmodifiertypo( fonts->window_titlebartext_disable.typo );
                     fonts->setmodifierunder( fonts->window_titlebartext_disable.under );
                     fonts->setmodifierstrike( fonts->window_titlebartext_disable.strike );

                     drawablecharlabel = fonts->assertstringlength( label, width-5-5-30 );

                     if (drawablecharlabel!=0)
                     {
                            drawablelabel = fonts->reducestringtovisible( label, width-5 -5 -30 );

                            //int sl = fonts->getstringwidth( drawablelabel );
                            int sh = fonts->getstringheight( drawablelabel );
                            fonts->drawstringleft( screen, drawablelabel, xpos+5, ypos+sh/2, colors->window_titlebartext_disable.R, colors->window_titlebartext_disable.G, colors->window_titlebartext_disable.B, colors->window_titlebartext_disable.A );
                     }
              }

              /*
              // THIS IS FOR DEBUGGING THE DEPTH BUFFER PORTION OF THE CODE
              char* tempID;
              sprintf( tempID, "ID = %ld", WidgetID );
              fonts->setcurrentfont( THIN_FONT );
              fonts->setmodifiertypo( Bold );
              fonts->drawstringleft( screen, tempID, xpos+2, ypos+4, 255, 0, 0, 255 );
              */

              for (auto& c : children )
              {
                     if (c->isvisible())
                     {
                            c->render( screen, colors, fonts );
                     }
              }

              for (auto& d : popupchildren )
              {
                     //if (d->isvisible())
                     {
                            d->render( screen, colors, fonts );
                     }
              }
       }

}

/*
bool WindowWidget::cursoron( CursorTask *mouse )
{
    return (mouse->x >= xpos) && (mouse->y >= ypos) && (mouse->x <= xpos+width) && (mouse->y <= ypos+height);
}
*/

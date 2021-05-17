#include "ListBoxWidget.h"
#include "DropBoxWidget.h"



ListBoxWidget::ListBoxWidget() : Widget()
{
       widgettype = "ListBox";
};

ListBoxWidget::ListBoxWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : Widget( l, x, y, w, h, p )
{
       widgettype = "ListBox";
};

ListBoxWidget::~ListBoxWidget()
{
       listitems.clear();
};

void ListBoxWidget::flush()
{
       listitems.clear();

       nbitem = 0;
       selected = 0;
       scroll = 0;
       nbvisible = 0;
};


void ListBoxWidget::additem( std::string item )
{
       listitems.push_back( item);
       nbitem++;
};

unsigned int ListBoxWidget::getnbitem()
{
       return listitems.size();
};

std::string ListBoxWidget::getitem( int itemnumber )
{
       return listitems[itemnumber];
};

int ListBoxWidget::getselected()
{
       return selected;
};

std::string ListBoxWidget::getselecteditem()
{
       return listitems[selected];
};

bool ListBoxWidget::ispressed()
{
       return is_pressed;
}

void ListBoxWidget::logic( CursorTask *mouse, KeyboardTask *keyboard )
{
       if (is_enabled && is_visible)
       {
              is_hovering = cursoron( mouse );
              bool currently_pressed = (mouse->state || keyboard->kbSCRATCH) && is_hovering;

              if (currently_pressed)
              {
                     focus(this);
              }

              if(currently_pressed && !is_pressed)
              {
                     if (clickfunction) clickfunction( (char*) "test" );
              }
              else if(!currently_pressed && is_pressed)
              {
                     if (releasefunction) releasefunction( (char*) "test" );
              }
              else if(is_hovering)
              {
                     if (hoverfunction) hoverfunction( (char*) "test" );
              }

              is_pressed = currently_pressed;

              if (!has_focus) return;

              if (currently_pressed)
              {
                     // Here is the code when the user click inside the listbox

                     // First we check if there is a escalator and if we clicked on the escalator
                     // as we are inside the widget (wue to previous cursoron() call, we just need to check if the mouse x is > right border-15px
                     if ((nbvisible<nbitem) && ((int) mouse->x >= ((int) xpos+ (int) width-15)) && ((int) mouse->y > (int) ypos +6) && ((int) mouse->y < (int) ypos+(int) height-6))
                     {
                            //so we are on the escalator
                            selected = (int) ((mouse->y-ypos-3)*nbitem/(height-12));
                            if (selected<1)
                            {
                                   selected = 0;
                                   scroll = 0;
                            }
                            else if (selected<scroll) scroll=selected;
                            else if (selected>scroll+nbvisible) scroll=selected;
                            if (selected>nbitem) selected=nbitem;
                     }
                     else if (((int) mouse->y > (int) ypos +3) && ((int) mouse->y < (int) ypos+(int) height-3))
                     {
                            //we clicked on the main part of the widget and then we have to calculated which line is clicked and add the scroll to adjsut the selected line
                            int clickedline = (int) ((int)(mouse->y-ypos-3)/ (int) heightline);
                            selected = scroll + clickedline;
                     }
              }


              if (keyboard->kbESC)
              {
                     if(parent)
                     {
                            if (parent->getwidgettype() == "DropBox")
                            {
                                   DropBoxWidget *temp = dynamic_cast<DropBoxWidget*>(parent);
                                   temp->escape();
                                   is_visible = false;
                                   return;
                            }
                            else
                            {
                                   validated = false;
                                   escaped = true;
                            }
                     }
              }


              if (keyboard->kbRET || keyboard->kbENTER)
              {
                     if(parent)
                     {
                            if (parent->getwidgettype() == "DropBox")
                            {
                                   DropBoxWidget *temp = dynamic_cast<DropBoxWidget*>(parent);
                                   temp->validate();
                                   is_visible = false;
                                   return;
                            }
                            else
                            {
                                   validated = true;
                                   escaped = false;
                            }
                     }
              }


              if (keyboard->kbDOWN && keyboard->iskeypressevent())
              {
                     if ( selected < this->getnbitem()-1)
                     {
                            selected++;
                     }

                     // selected is an unsigned int so always>=0
                     //if ((selected>=0) && (selected<=nbvisible-1))
                     if (selected<=nbvisible-1)
                     {
                            scroll=0;
                     }
                     else
                     {
                            scroll=selected-nbvisible+1;
                     }

                     SDL_Delay( 150 );
              }

              if (keyboard->kbUP && keyboard->iskeypressevent())
              {
                     if (selected>0)
                     {
                            selected--;
                     }

                     // selected is an unsigned int so always>=0
                     //if ((selected>=0) && (selected<=nbvisible-1))
                     if (selected<=nbvisible-1)
                     {
                            scroll=0;
                     }
                     else
                     {
                            scroll=selected-nbvisible+1;
                     }

                     SDL_Delay( 150 );
              }

              for (auto& c : children )
                     c->logic( mouse, keyboard );
       }
}

void ListBoxWidget::render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts )
{
       if (is_visible)
       {
              if (is_enabled)
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

                     fonts->setcurrentfont( fonts->widget_text_enable.name );
                     fonts->setmodifiertypo( fonts->widget_text_enable.typo );
                     fonts->setmodifierunder( fonts->widget_text_enable.under );
                     fonts->setmodifierstrike( fonts->widget_text_enable.strike );

                     int sh = fonts->getstringheight( label );
                     heightline = sh*2;

                     nbvisible = (unsigned int) ((height-0) / (sh*2));

                     for(unsigned int i=scroll; i<=scroll+nbvisible-1; i++)
                     {
                            //Ongoing - to be optimised
                            if(i<nbitem)
                            {
                                   if (i!=selected)
                                   {
                                          fonts->setcurrentfont( fonts->widget_text_enable.name );
                                          fonts->setmodifiertypo( fonts->widget_text_enable.typo );
                                          fonts->setmodifierunder( fonts->widget_text_enable.under );
                                          fonts->setmodifierstrike( fonts->widget_text_enable.strike );

                                          //We check if the titel can be written in the titlebar (with 5px on each side of the title
                                          if (nbvisible>=nbitem) drawablecharlabel = fonts->assertstringlength( getitem(i), width-5-25 );
                                          if (nbvisible<nbitem) drawablecharlabel = fonts->assertstringlength( getitem(i), width-5-25 );

                                          if (drawablecharlabel!=0)
                                          {
                                                 drawablelabel = fonts->reducestringtovisible( getitem(i), width-5 -25  );
                                                 int sh = fonts->getstringheight( drawablelabel );
                                                 fonts->drawstringleft( screen, drawablelabel, xpos+8, ypos+5+(unsigned int) ((i-scroll)*(sh*2)), colors->widget_text_enable.R, colors->widget_text_enable.G, colors->widget_text_enable.B, colors->widget_text_enable.A );
                                          }


                                          //int sh = fonts->getstringheight( (char*) listitems[i] );

                                          //fonts->drawstringleft( screen, (char*) listitems[i], xpos+8, ypos+5+(unsigned int) ((i-scroll)*(sh*2)), colors->widget_text_enable.R, colors->widget_text_enable.G, colors->widget_text_enable.B, colors->widget_text_enable.A );
                                   }
                                   else
                                   {
                                          fonts->setcurrentfont( fonts->widget_text_selected.name );
                                          fonts->setmodifiertypo( fonts->widget_text_selected.typo );
                                          fonts->setmodifierunder( fonts->widget_text_selected.under );
                                          fonts->setmodifierstrike( fonts->widget_text_selected.strike );


                                          //We check if the titel can be written in the titlebar (with 5px on each side of the title
                                          if (nbvisible>=nbitem) drawablecharlabel = fonts->assertstringlength( getitem(i), width-5-25 );
                                          if (nbvisible<nbitem) drawablecharlabel = fonts->assertstringlength( getitem(i), width-5-25 );


                                          if (drawablecharlabel!=0)
                                          {
                                                 drawablelabel = fonts->reducestringtovisible( getitem(i), width-5 -25  );
                                                 int sh = fonts->getstringheight( drawablelabel );

                                                 // if we can see all the item, no need for space for the escalator on the right
                                                 if (nbvisible>=nbitem) roundedBoxRGBA( screen, xpos+3, ypos+3+(unsigned int) ((i-scroll)*(sh*2)), xpos+width-3, ypos+15+(unsigned int) ((i-scroll)*(sh*2)), 3, colors->widget_selection.R, colors->widget_selection.G, colors->widget_selection.B, colors->widget_selection.A );
                                                 //else we draw the selection line a bit shorter not to cover the escalator
                                                 if (nbvisible<nbitem) roundedBoxRGBA( screen, xpos+3, ypos+3+(unsigned int) ((i-scroll)*(sh*2)), xpos+width-18, ypos+15+(unsigned int) ((i-scroll)*(sh*2)), 3, colors->widget_selection.R, colors->widget_selection.G, colors->widget_selection.B, colors->widget_selection.A );


                                                 fonts->drawstringleft( screen, drawablelabel, xpos+8, ypos+5+(unsigned int) ((i-scroll)*(sh*2)), colors->widget_text_selected.R, colors->widget_text_selected.G, colors->widget_text_selected.B, colors->widget_text_selected.A );
                                          }



                                          /*
                                          int sh = fonts->getstringheight( (char*) listitems[i] );

                                          // if we can see all the item, no need for space for the escalator on the right
                                          if (nbvisible>=nbitem) roundedBoxRGBA( screen, xpos+3, ypos+3+(unsigned int) ((i-scroll)*(sh*2)), xpos+width-3, ypos+15+(unsigned int) ((i-scroll)*(sh*2)), 3, colors->widget_selection.R, colors->widget_selection.G, colors->widget_selection.B, colors->widget_selection.A );
                                          //else we draw the selection line a bit shorter not to cover the escalator
                                          if (nbvisible<nbitem) roundedBoxRGBA( screen, xpos+3, ypos+3+(unsigned int) ((i-scroll)*(sh*2)), xpos+width-18, ypos+15+(unsigned int) ((i-scroll)*(sh*2)), 3, colors->widget_selection.R, colors->widget_selection.G, colors->widget_selection.B, colors->widget_selection.A );

                                          fonts->drawstringleft( screen, (char*) listitems[i], xpos+8, ypos+5+(unsigned int) ((i-scroll)*(sh*2)), colors->widget_text_selected.R, colors->widget_text_selected.G, colors->widget_text_selected.B, colors->widget_text_selected.A );
                                          */
                                   }
                            }
                     }

                     if (nbvisible<nbitem)
                     {
                            unsigned int escalator = (height-12)*selected/nbitem;

                            if (!is_hovering)
                            {
                                   roundedRectangleRGBA( screen, xpos+width-15, ypos+3, xpos+width-3, ypos+height-3, 3, colors->widget_border_enable.R, colors->widget_border_enable.G, colors->widget_border_enable.B, colors->widget_border_enable.A);
                                   filledCircleRGBA( screen, xpos+width-9, ypos+9+escalator, 4, colors->widget_border_enable.R, colors->widget_border_enable.G, colors->widget_border_enable.B, colors->widget_border_enable.A);
                            }
                            else
                            {
                                   roundedRectangleRGBA( screen, xpos+width-15, ypos+3, xpos+width-3, ypos+height-3, 3, colors->widget_border_cursoron.R, colors->widget_border_cursoron.G, colors->widget_border_cursoron.B, colors->widget_border_cursoron.A);
                                   filledCircleRGBA( screen, xpos+width-9, ypos+9+escalator, 4, colors->widget_border_cursoron.R, colors->widget_border_cursoron.G, colors->widget_border_cursoron.B, colors->widget_border_cursoron.A);
                            }
                     }
              }
              else
              {
                     roundedBoxRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_filling_disable.R, colors->widget_filling_disable.G, colors->widget_filling_disable.B, colors->widget_filling_disable.A);
                     //Border of the button is black cause it is disabled
                     roundedRectangleRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_border_disable.R, colors->widget_border_disable.G, colors->widget_border_disable.B, colors->widget_border_disable.A);

                     fonts->setcurrentfont( fonts->widget_text_disable.name );
                     fonts->setmodifiertypo( fonts->widget_text_disable.typo );
                     fonts->setmodifierunder( fonts->widget_text_disable.under );
                     fonts->setmodifierstrike( fonts->widget_text_disable.strike );

                     int sh = fonts->getstringheight( label );

                     nbvisible = (unsigned int) ((height-10) / (sh*2));

                     for(unsigned int i=scroll; i<=scroll+nbvisible-1; i++)
                     {
                            //Ongoing - to be optimised and to be tested when using ListBoxWidget as a standalone Widget
                            if(i<nbitem)
                            {
                                   if (i!=selected)
                                   {
                                          fonts->setcurrentfont( fonts->widget_text_enable.name );
                                          fonts->setmodifiertypo( fonts->widget_text_enable.typo );
                                          fonts->setmodifierunder( fonts->widget_text_enable.under );
                                          fonts->setmodifierstrike( fonts->widget_text_enable.strike );

                                          int sh = fonts->getstringheight( getitem(i) );

                                          fonts->drawstringleft( screen, getitem(i), xpos+8, ypos+5+(unsigned int) ((i-scroll)*(sh*2)), colors->widget_text_disable.R, colors->widget_text_disable.G, colors->widget_text_disable.B, colors->widget_text_disable.A );
                                   }
                                   else
                                   {
                                          fonts->setcurrentfont( fonts->widget_text_selected.name );
                                          fonts->setmodifiertypo( fonts->widget_text_selected.typo );
                                          fonts->setmodifierunder( fonts->widget_text_selected.under );
                                          fonts->setmodifierstrike( fonts->widget_text_selected.strike );

                                          int sh = fonts->getstringheight( getitem(i) );

                                          // if we can see all the item, no need for space for the escalator on the right
                                          if (nbvisible>=nbitem) roundedRectangleRGBA( screen, xpos+3, ypos+3+(unsigned int) ((i-scroll)*(sh*2)), xpos+width-3, ypos+15+(unsigned int) ((i-scroll)*(sh*2)), 3, colors->widget_border_disable.R, colors->widget_border_disable.G, colors->widget_border_disable.B, colors->widget_border_disable.A );
                                          //else we draw the selection line a bit shorter not to cover the escalator
                                          if (nbvisible<nbitem) roundedRectangleRGBA( screen, xpos+3, ypos+3+(unsigned int) ((i-scroll)*(sh*2)), xpos+width-18, ypos+15+(unsigned int) ((i-scroll)*(sh*2)), 3, colors->widget_border_disable.R, colors->widget_border_disable.G, colors->widget_border_disable.B, colors->widget_border_disable.A );

                                          fonts->drawstringleft( screen, getitem(i), xpos+5, ypos+5+(unsigned int) ((i-scroll)*(sh*2)), colors->widget_text_disable.R, colors->widget_text_disable.G, colors->widget_text_disable.B, colors->widget_text_disable.A );
                                   }
                            }
                     }

                     if (nbvisible<nbitem)
                     {
                            unsigned int escalator = (height-12)*selected/nbitem;

                            roundedRectangleRGBA( screen, xpos+width-15, ypos+3, xpos+width-3, ypos+height-3, 3, colors->widget_border_disable.R, colors->widget_border_disable.G, colors->widget_border_disable.B, colors->widget_border_disable.A );
                            filledCircleRGBA( screen, xpos+width-9, ypos+9+escalator, 4, colors->widget_border_disable.R, colors->widget_border_disable.G, colors->widget_border_disable.B, colors->widget_border_disable.A );
                     }

              }

              for (auto& c : children )
                     c->render( screen, colors, fonts );

       }
}

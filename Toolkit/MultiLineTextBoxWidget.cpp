#include "MultiLineTextBoxWidget.h"

#include <fstream>

MultiLineTextBoxWidget::MultiLineTextBoxWidget()
{
       widgettype =  "MultiLineTextBox";
       content.push_back( "abcdefghijklmnopqrstuvwxyz0123456789/*-+ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789/*-+&~{([])}=");
}


MultiLineTextBoxWidget::MultiLineTextBoxWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : Widget( l, x, y, w, h, p )
{
       widgettype =  "MultiLineTextBox";
       content.push_back( "abcdefghijklmnopqrstuvwxyz0123456789/*-+ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789/*-+&~{([])}=");
}


MultiLineTextBoxWidget::~MultiLineTextBoxWidget()
{
       content.clear();
}


void MultiLineTextBoxWidget::flush()
{
       content.clear();
}


void MultiLineTextBoxWidget::loadcontentfromfile( std::string filename )
{
       flush();

       /*
       std::ifstream ifs( filename );

       std::string contenttoadd( (std::istreambuf_iterator<char>(ifs) ), (std::istreambuf_iterator<char>()    ) );

       content.push_back(contenttoadd);
        */

           FILE* pFile;
           char c;

           std::string filecontent;

           pFile = fopen (filename.c_str(), "r");
           if (pFile!=NULL)
           {
                   while (!feof(pFile))
                   {
                       fscanf( pFile, "%c",  &c);
                       filecontent += c;
                   }

           fclose(pFile);
           }

       content.push_back( filecontent );
}


void MultiLineTextBoxWidget::appendcontent(std::string str)
{
       content.push_back(str);
}


void MultiLineTextBoxWidget::logic( CursorTask *mouse, KeyboardTask *keyboard )
{
       if (is_enabled && is_visible)
       {
              is_hovering = cursoron( mouse );
              mousex=mouse->x;
              mousey=mouse->y;
              mouses=mouse->state;

              if(is_hovering)
              {
                     if (hoverfunction)
                            hoverfunction( (char*) "test" );
              }

              if ( is_hovering && (mouse->state || keyboard->kbSCRATCH) && !has_focus )
              {
                     focus( this );
              }

              if( (mouse->state || keyboard->kbSCRATCH) && is_hovering )
              {
                     nfontwidget->setcurrentfont( nfontwidget->widget_text_disable.name );
                     nfontwidget->setmodifiertypo( nfontwidget->widget_text_disable.typo );
                     nfontwidget->setmodifierunder( nfontwidget->widget_text_disable.under );
                     nfontwidget->setmodifierstrike( nfontwidget->widget_text_disable.strike );

                     unsigned int x_rel = mousex - xpos - 2;
                     const char *str = content[0].c_str() + scrollX;
                     unsigned int pos = scrollX;

                     while(x_rel > 0 && *str)
                     {
                            unsigned int temp = nfontwidget->getcharwidth( (char) *str++ );
                            x_rel -= temp;
                            ++pos;
                     }

                     cursor_posX = pos;

              }

              if(!has_focus)
                     return;

              char c = keyboard->asciiget();

              //if(c >= 0x80 || c == '\n')

              if (c>=0x80)
                     return;


              if (key_hold_down)
              {
                     key_hold_down = any_key_pressed();
              }
              else if (keyboard->kbCTRL && keyboard->kbLEFT)
              {
                     cursor_posX = 0;

                     updateScroll();
              }
              else if (keyboard->kbCTRL && keyboard->kbRIGHT)
              {
                     cursor_posX = content[0].length();

                     updateScroll();
              }
              else if (keyboard->kbCTRL && keyboard->kbUP)
              {
                     cursor_posX = 0;

                     updateScroll();
              }
              else if (keyboard->kbCTRL && keyboard->kbDOWN)
              {
                     cursor_posX = content[0].length();

                     updateScroll();
              }
              else if (keyboard->kbLEFT)
              {
                     if(cursor_posX > 0)
                            --cursor_posX;

                     updateScroll();
              }
              else if (keyboard->kbRIGHT)
              {
                     if(cursor_posX < content[0].length())
                            ++cursor_posX;

                     updateScroll();
              }
              else if (keyboard->kbDOWN)
              {
                     if(cursor_posX < content[0].length()-nbcharvisibleperline)
                            cursor_posX += nbcharvisibleperline;
                     else
                            cursor_posX = content[0].length();

                     updateScroll();
              }
              else if (keyboard->kbUP)
              {
                     if(cursor_posX > nbcharvisibleperline)
                            cursor_posX -= nbcharvisibleperline;
                     else
                            cursor_posX = 0;

                     updateScroll();
              }
              // TO BE ADDED : THe CODE for the BOTTOM / UP and CTRL + BT/UP keys

              static char old_char = 0;
              if(c != old_char && c != 0)
              {
                     if(c == '\b')
                     {
                            if(cursor_posX > 0)
                            {
                                   content[0].erase(content[0].begin() + (cursor_posX - 1));
                                   --cursor_posX;

                                   updateScroll();
                            }
                     }
                     else
                     {
                            content[0].insert(content[0].begin() + cursor_posX, c);
                            ++cursor_posX;

                            updateScroll();
                     }
              }

              old_char = c;

              if(!any_key_pressed())
              {
                     old_char = 0;
              }

              for (auto& c : children ) c->logic( mouse, keyboard );

       }
}


void MultiLineTextBoxWidget::render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts )
{
       // We check how many characters can be drawn on each line;
       fonts->setcurrentfont( fonts->widget_text_enable.name );
       nblinevisible = height /  (fonts->getcharheight( 'O' )+ fonts->getvspacing());

       if (nblinetotal>nblinevisible)
       {

              nbcharvisibleperline = (width - 25) / (fonts->getcharwidth( 'O' ) + fonts->gethspacing()) -1 ;           // 15 pixels reserved for escalator on the right part of the widget to draw the escalator
       }                                                                                                                                                                           // 10 more pixels removed on each side of the box --> total removed 25 pixels
       else
       {
              nbcharvisibleperline = (width - 10) / (fonts->getcharwidth( 'O' ) + fonts->gethspacing()) - 1 ;
       }                                                                                                                                                                           // 10 more pixels removed on each side of the box --> total removed 10 pixels

       // TODO : ADD the possibility to have an escalator

       if (is_visible)
       {
              // if the current font has not been defined for the widget, we use the current fontengine
              if (nfontwidget ==nullptr)
                     nfontwidget = fonts;

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

                     const char *str = content[0].c_str() + scrollX;
                     const char *cursor = content[0].c_str() + cursor_posX;
                     unsigned int x1 = xpos + 5;

                     fonts->setcurrentfont( fonts->widget_text_enable.name );
                     fonts->setmodifiertypo( fonts->widget_text_enable.typo );
                     fonts->setmodifierunder( fonts->widget_text_enable.under );
                     fonts->setmodifierstrike( fonts->widget_text_enable.strike );
                     char* tpstr = (char*) str;
                     int sh = fonts->getstringheight( tpstr );
                     int sp = fonts->getvspacing();

                     currentline = 0;
                     //while(*str && x1 - xpos + fonts->getcharwidth( (char) *str) < width)
                     while (*str)
                     {
                            if(has_focus && str == cursor)
                            {
                                   vlineRGBA( screen, x1, ypos + 1+ currentline * (sh+sp), ypos + sh + 1+ currentline * (sh+sp), colors->widget_border_enable.R, colors->widget_border_enable.G, colors->widget_border_enable.B, colors->widget_border_enable.A);
                                   vlineRGBA( screen, x1+1, ypos + 1+ currentline * (sh+sp), ypos + sh + 1+ currentline * (sh+sp), colors->widget_border_enable.R, colors->widget_border_enable.G, colors->widget_border_enable.B, colors->widget_border_enable.A);
                                   x1+=2;
                            }

                            if (*str == '\n' )
                            {
                                   // if the current char is "RETURN" we go to the next line
                                   x1 = xpos + 5;
                                   currentline++;
                            }
                            else if (*str == '\t')
                            {
                                   // if the current char is a "TAB", we replace it with 5 SPACES
                                   for(unsigned int u=0; u<5; u++)
                                   {
                                          fonts->drawcharleft( screen, ' ', x1, ypos + 2 + currentline * (sh+sp),colors->widget_text_enable.R, colors->widget_text_enable.G, colors->widget_text_enable.B, colors->widget_text_enable.A);
                                          x1 += fonts->getcharwidth( ' ' ) + fonts->gethspacing();
                                   }
                            }
                            else
                            {
                                   fonts->drawcharleft( screen, *str, x1, ypos + 2+ currentline * (sh+sp), colors->widget_text_enable.R, colors->widget_text_enable.G, colors->widget_text_enable.B, colors->widget_text_enable.A);
                                   x1 += fonts->getcharwidth( (char) *str ) + fonts->gethspacing();
                            }

                            if (x1-xpos > width)
                            {
                                   x1 = xpos + 5;
                                   currentline++;
                            }

                            ++str;
                     }

                     if(str == cursor)
                     {
                            vlineRGBA( screen, x1, ypos + 1+ currentline * (sh+sp), ypos + sh + 1+ currentline * (sh+sp), colors->widget_border_enable.R, colors->widget_border_enable.G, colors->widget_border_enable.B, colors->widget_border_enable.A);
                            vlineRGBA( screen, x1+1, ypos + 1+ currentline * (sh+sp), ypos + sh + 1+ currentline * (sh+sp), colors->widget_border_enable.R, colors->widget_border_enable.G, colors->widget_border_enable.B, colors->widget_border_enable.A);
                            x1+=2;
                     }

              }
              else
              {
                     roundedBoxRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_filling_disable.R, colors->widget_filling_disable.G, colors->widget_filling_disable.B, colors->widget_filling_disable.A);

                     roundedRectangleRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_border_disable.R, colors->widget_border_disable.G, colors->widget_border_disable.B, colors->widget_border_disable.A);

                     const char *str = content[0].c_str() + scrollX;
                     const char *cursor = content[0].c_str() + cursor_posX;
                     unsigned int x1 = xpos + 5;

                     fonts->setcurrentfont( fonts->widget_text_disable.name );
                     fonts->setmodifiertypo( fonts->widget_text_disable.typo );
                     fonts->setmodifierunder( fonts->widget_text_disable.under );
                     fonts->setmodifierstrike( fonts->widget_text_disable.strike );

                     char* tpstr = (char*) str;
                     int sh = fonts->getstringheight( tpstr );
                     int sp = fonts->getvspacing();

                     //while(*str && x1 - xpos + fonts->getcharwidth( (char) *str) < width)
                     while (*str)
                     {

                            if(has_focus && str == cursor)
                            {
                                   vlineRGBA( screen, x1, ypos + 1+ currentline * (sh+sp), ypos + sh + 1+ currentline * (sh+sp), colors->widget_border_disable.R, colors->widget_border_disable.G, colors->widget_border_disable.B, colors->widget_border_disable.A);
                                   vlineRGBA( screen, x1+1, ypos + 1+ currentline * (sh+sp), ypos + sh + 1+ currentline * (sh+sp), colors->widget_border_disable.R, colors->widget_border_disable.G, colors->widget_border_disable.B, colors->widget_border_disable.A);
                                   x1+=2;
                            }

                            if (*str == '\n' )
                            {
                                   // if the current char is "RETURN" we go to the next line
                                   x1 = xpos + 5;
                                   currentline++;
                            }
                            else if (*str == '\t')
                            {
                                   // if the current char is a "TAB", we replace it with 5 SPACES
                                   for(unsigned int u=0; u<5; u++)
                                   {
                                          fonts->drawcharleft( screen, ' ', x1, ypos + 2+ currentline * (sh+sp), colors->widget_text_disable.R, colors->widget_text_disable.G, colors->widget_text_disable.B, colors->widget_text_disable.A );
                                          x1 += fonts->getcharwidth( ' ' ) + fonts->gethspacing();
                                   }
                            }
                            else
                            {
                                   fonts->drawcharleft( screen, *str, x1, ypos + 2+ currentline * (sh+sp), colors->widget_text_disable.R, colors->widget_text_disable.G, colors->widget_text_disable.B, colors->widget_text_disable.A );
                                   x1 += fonts->getcharwidth( (char) *str ) + fonts->gethspacing();
                            }

                            if (x1-xpos > width)
                            {
                                   x1 = xpos + 5;
                                   currentline++;
                            }

                            ++str;
                     }

                     if(str == cursor)
                     {
                            vlineRGBA( screen, x1, ypos + 1+ currentline * (sh+sp), ypos + sh + 1+ currentline * (sh+sp), colors->widget_border_disable.R, colors->widget_border_disable.G, colors->widget_border_disable.B, colors->widget_border_disable.A);
                            vlineRGBA( screen, x1+1, ypos + 1+ currentline * (sh+sp), ypos + sh + 1+ currentline * (sh+sp), colors->widget_border_disable.R, colors->widget_border_disable.G, colors->widget_border_disable.B, colors->widget_border_disable.A);
                            x1+=2;
                     }


              }

              for (auto& c : children )
                     c->render( screen, colors, fonts );
       }
}

void MultiLineTextBoxWidget::updateScroll()
{
       /*
              if(scrollX != 0 && cursor_posX <= scrollX)
                     --scrollX;

              if(cursor_posX <= scrollX)
                     return;

              nfontwidget->setcurrentfont( nfontwidget->widget_text_enable.name );

              const char *str = content[0].c_str() + scrollX;
              unsigned int cur_x = 0;
              unsigned int len = cursor_posX - scrollX;

              while(len--)
                     cur_x += nfontwidget->getcharwidth( *str++ ) + nfontwidget->gethspacing();

              if(cur_x >= width - 5)
                     ++scrollX;
       */
}

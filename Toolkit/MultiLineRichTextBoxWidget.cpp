#include "MultiLineRichTextBoxWidget.h"

#include <fstream>

MultiLineRichTextBoxWidget::MultiLineRichTextBoxWidget()
{
       widgettype =  "MultiLineRichTextBox";
       content.push_back( " ");
}


MultiLineRichTextBoxWidget::MultiLineRichTextBoxWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : Widget( l, x, y, w, h, p )
{
       widgettype =  "MultiLineRichTextBox";
       content.push_back( " ");
}


MultiLineRichTextBoxWidget::~MultiLineRichTextBoxWidget()
{
       content.clear();
}


void MultiLineRichTextBoxWidget::flush()
{
       content.clear();
}


void MultiLineRichTextBoxWidget::loadcontentfromfile( std::string filename )
{
       flush();

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


void MultiLineRichTextBoxWidget::appendcontent(std::string str)
{
       content.push_back(str);
}


void MultiLineRichTextBoxWidget::setcontent( std::string str )
{
       flush();
       content.push_back(str);
}


std::string MultiLineRichTextBoxWidget::getcontent()
{
       return content[0];
}


void MultiLineRichTextBoxWidget::logic( CursorTask *mouse, KeyboardTask *keyboard )
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

              if (c>=0x80)
                     return;


              if (key_hold_down)
              {
                     key_hold_down = any_key_pressed();
              }
              else if (keyboard->kbSHIFT && keyboard->kbUP)
              {
                     if (firstlinevisible>0) firstlinevisible--;
              }
              else if (keyboard->kbSHIFT && keyboard->kbDOWN)
              {
                     if (firstlinevisible<nblinetotal) firstlinevisible++;
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


void MultiLineRichTextBoxWidget::setstyle( char mode, unsigned short *R, unsigned short *G, unsigned short *B, unsigned short *A, ColorEngine *colors, FontEngine *fonts )
{
       switch(mode)
       {
       case '0':    // This is choosen as the default write mode
              fonts->setcurrentfont( fonts->widget_text_enable.name );
              fonts->setmodifiertypo( fonts->widget_text_enable.typo );
              fonts->setmodifierunder( fonts->widget_text_enable.under );
              fonts->setmodifierstrike( fonts->widget_text_enable.strike );
              *R = colors->widget_text_enable.R;
              *G = colors->widget_text_enable.G;
              *B = colors->widget_text_enable.B;
              *A = colors->widget_text_enable.A;
              break;

       case '1':    //This is the title level 1
              fonts->setcurrentfont( FontEngine::VGA_FONT );
              fonts->setmodifiertypo( FontEngine::Bold );
              fonts->setmodifierunder( FontEngine::UnderSimple );
              fonts->setmodifierstrike( FontEngine::NoStrike );
              *R = 255;
              *G = 0;
              *B = 0;
              *A = 255;
              break;

       case '2':
              fonts->setcurrentfont( FontEngine::VGA_FONT );
              fonts->setmodifiertypo( FontEngine::Normal );
              fonts->setmodifierunder( FontEngine::UnderSimple );
              fonts->setmodifierstrike( FontEngine::NoStrike );
              *R = 0;
              *G = 255;
              *B = 0;
              *A = 255;
              break;

       case '3':
              fonts->setcurrentfont( FontEngine::VGA_FONT );
              fonts->setmodifiertypo( FontEngine::Normal );
              fonts->setmodifierunder( FontEngine::UnderSimple );
              fonts->setmodifierstrike( FontEngine::NoStrike );
              *R = 0;
              *G = 0;
              *B = 255;
              *A = 255;
              break;

       case '4':
              fonts->setcurrentfont( FontEngine::THIN_FONT );
              fonts->setmodifiertypo( FontEngine::Italic );
              fonts->setmodifierunder( FontEngine::NoUnder );
              fonts->setmodifierstrike( FontEngine::NoStrike );
              *R = 64;
              *G = 64;
              *B = 64;
              *A = 255;
              break;

       case '5':

              break;

       case '6':

              break;

       case '7':

              break;

       case '8':

              break;

       case '9':

              break;

       default:
              fonts->setcurrentfont( fonts->widget_text_enable.name );
              fonts->setmodifiertypo( fonts->widget_text_enable.typo );
              fonts->setmodifierunder( fonts->widget_text_enable.under );
              fonts->setmodifierstrike( fonts->widget_text_enable.strike );
              *R = colors->widget_text_enable.R;
              *G = colors->widget_text_enable.G;
              *B = colors->widget_text_enable.B;
              *A = colors->widget_text_enable.A;
              break;
       }
}


void MultiLineRichTextBoxWidget::render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts )
{
       fonts->setcurrentfont( fonts->widget_text_enable.name );
       nblinevisible = (height-5) /  (fonts->getcharheight( 'O' )+ fonts->getvspacing());

       bool escalator = false;

       if (nblinetotal>nblinevisible)
       {
              escalator = true;
              nbcharvisibleperline = (width - 25) / (fonts->getcharwidth( 'O' ) + fonts->gethspacing()) -1 ;
       }
       else
       {
              escalator = false;
              nbcharvisibleperline = (width - 10) / (fonts->getcharwidth( 'O' ) + fonts->gethspacing()) - 1 ;
       }

       int currentnblinetotal = 0;


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

                            if (escalator==true)
                            {
                                   roundedRectangleRGBA( screen, xpos+width-12, ypos+4, xpos+width-4, ypos+height-4, 3, colors->widget_border_enable.R, colors->widget_border_enable.G, colors->widget_border_enable.B, colors->widget_border_enable.A);
                                   unsigned int y = ((height-7-7)*firstlinevisible / nblinetotal);
                                   filledCircleRGBA( screen, xpos+width-8, ypos+7+y, 3, colors->widget_border_enable.R, colors->widget_border_enable.G, colors->widget_border_enable.B, colors->widget_border_enable.A);
                            }

                     }
                     else
                     {
                            roundedRectangleRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_border_cursoron.R, colors->widget_border_cursoron.G, colors->widget_border_cursoron.B, colors->widget_border_cursoron.A);

                            if (escalator==true)
                            {
                                   roundedRectangleRGBA( screen, xpos+width-12, ypos+4, xpos+width-4, ypos+height-4, 3, colors->widget_border_cursoron.R, colors->widget_border_cursoron.G, colors->widget_border_cursoron.B, colors->widget_border_enable.A);
                                   unsigned int y = ((height-7-7)*firstlinevisible / nblinetotal);
                                   filledCircleRGBA( screen, xpos+width-8, ypos+7+y, 3, colors->widget_border_cursoron.R, colors->widget_border_cursoron.G, colors->widget_border_cursoron.B, colors->widget_border_cursoron.A);
                            }

                     }

                     unsigned short R,G,B,A;

                     const char *str = content[0].c_str() + scrollX;
                     const char *cursor = content[0].c_str() + cursor_posX;
                     unsigned int x1 = xpos + 5;

                     //fonts->setcurrentfont( fonts->widget_text_enable.name );
                     //fonts->setmodifiertypo( fonts->widget_text_enable.typo );
                     //fonts->setmodifierunder( fonts->widget_text_enable.under );
                     //fonts->setmodifierstrike( fonts->widget_text_enable.strike );

                     setstyle( '0', &R, &G, &B, &A, colors, fonts );

                     char* tpstr = (char*) str;
                     int sh = fonts->getstringheight( tpstr );
                     int sp = fonts->getvspacing();

                     currentline = 0;
                     //while(*str && x1 - xpos + fonts->getcharwidth( (char) *str) < width)
                     while (*str)
                     {

                            if(has_focus && str == cursor)
                            {
                                   vlineRGBA( screen, x1, ypos + 1+ (currentline-firstlinevisible) * (sh+sp), ypos + sh + 1+ (currentline-firstlinevisible) * (sh+sp), colors->widget_border_enable.R, colors->widget_border_enable.G, colors->widget_border_enable.B, colors->widget_border_enable.A);
                                   vlineRGBA( screen, x1+1, ypos + 1+ (currentline-firstlinevisible) * (sh+sp), ypos + sh + 1+ (currentline-firstlinevisible) * (sh+sp), colors->widget_border_enable.R, colors->widget_border_enable.G, colors->widget_border_enable.B, colors->widget_border_enable.A);
                                   x1+=2;
                            }


                            if ((str[0]=='#') && (str[1]=='0')) // This corresponds to the normal style
                            {
                                   setstyle( str[1], &R, &G, &B, &A, colors, fonts );
                                   str++;
                            }
                            else if ((str[0]=='#') && (str[1]=='1'))
                            {
                                   setstyle( str[1], &R, &G, &B, &A, colors, fonts );
                                   str++;
                            }
                            else if ((str[0]=='#') && (str[1]=='2'))
                            {
                                   setstyle( str[1], &R, &G, &B, &A, colors, fonts );
                                   str++;
                            }
                            else if ((str[0]=='#') && (str[1]=='3'))
                            {
                                   setstyle( str[1], &R, &G, &B, &A, colors, fonts );
                                   str++;
                            }
                            else if ((str[0]=='#') && (str[1]=='4'))
                            {
                                   setstyle( str[1], &R, &G, &B, &A, colors, fonts );
                                   str++;
                            }
                            else if ((str[0]=='#') && (str[1]=='5'))
                            {
                                   setstyle( str[1], &R, &G, &B, &A, colors, fonts );
                                   str++;
                            }
                            else if ((str[0]=='#') && (str[1]=='6'))
                            {
                                   setstyle( str[1], &R, &G, &B, &A, colors, fonts );
                                   str++;
                            }
                            else if ((str[0]=='#') && (str[1]=='7'))
                            {
                                   setstyle( str[1], &R, &G, &B, &A, colors, fonts );
                                   str++;
                            }
                            else if ((str[0]=='#') && (str[1]=='8'))
                            {
                                   setstyle( str[1], &R, &G, &B, &A, colors, fonts );
                                   str++;
                            }
                            else if ((str[0]=='#') && (str[1]=='9'))
                            {
                                   setstyle( str[1], &R, &G, &B, &A, colors, fonts );
                                   str++;
                            }
                            else if (*str == '\n' )
                            {
                                   // if the current char is "RETURN" we go to the next line
                                   x1 = xpos + 2;
                                   currentline++;
                            }
                            else if (*str == '\t')
                            {
                                   // if the current char is a "TAB", we replace it with 5 SPACES
                                   for(unsigned int u=0; u<5; u++)
                                   {
                                          if ((currentline>=firstlinevisible) && (currentline<firstlinevisible+nblinevisible))
                                          {
                                                 fonts->drawcharleft( screen, ' ', x1, ypos + 2 + (currentline-firstlinevisible) * (sh+sp), R, G, B, A);
                                          }
                                          x1 += fonts->getcharwidth( ' ' ) + fonts->gethspacing();
                                   }
                            }
                            else
                            {
                                   if ((currentline>=firstlinevisible) && (currentline<firstlinevisible+nblinevisible))
                                   {
                                          fonts->drawcharleft( screen, *str, x1, ypos + 2 + (currentline-firstlinevisible) * (sh+sp), R, G, B, A);
                                   }
                                   x1 += fonts->getcharwidth( (char) *str ) + fonts->gethspacing();
                            }

                            if ((escalator==false) && (x1-xpos > width-10))
                            {
                                   x1 = xpos + 2;
                                   currentline++;
                                   if (currentline>currentnblinetotal) currentnblinetotal=currentline;
                            }

                            if ((escalator==true) && (x1-xpos > width-25))
                            {
                                   x1 = xpos + 2;
                                   currentline++;
                                   if (currentline>currentnblinetotal) currentnblinetotal=currentline;
                            }


                            ++str;
                     }

                     if(str == cursor)
                     {
                            vlineRGBA( screen, x1, ypos + 1+ (currentline-firstlinevisible) * (sh+sp), ypos + sh + 1+ (currentline-firstlinevisible) * (sh+sp), colors->widget_border_enable.R, colors->widget_border_enable.G, colors->widget_border_enable.B, colors->widget_border_enable.A);
                            vlineRGBA( screen, x1+1, ypos + 1+ (currentline-firstlinevisible) * (sh+sp), ypos + sh + 1+ (currentline-firstlinevisible) * (sh+sp), colors->widget_border_enable.R, colors->widget_border_enable.G, colors->widget_border_enable.B, colors->widget_border_enable.A);
                            x1+=2;
                     }

              }
              else
              {
                     roundedBoxRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_filling_disable.R, colors->widget_filling_disable.G, colors->widget_filling_disable.B, colors->widget_filling_disable.A);

                     roundedRectangleRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_border_disable.R, colors->widget_border_disable.G, colors->widget_border_disable.B, colors->widget_border_disable.A);

                     if (escalator==true)
                     {
                            roundedRectangleRGBA( screen, xpos+width-12, ypos+4, xpos+width-4, ypos+height-4, 3, colors->widget_border_disable.R, colors->widget_border_disable.G, colors->widget_border_disable.B, colors->widget_border_disable.A);
                            unsigned int y = ((height-7-7)*firstlinevisible / nblinetotal);
                            filledCircleRGBA( screen, xpos+width-8, ypos+7+y, 3, colors->widget_border_disable.R, colors->widget_border_disable.G, colors->widget_border_disable.B, colors->widget_border_disable.A);
                     }

                     unsigned short R,G,B,A;

                     const char *str = content[0].c_str() + scrollX;
                     const char *cursor = content[0].c_str() + cursor_posX;
                     unsigned int x1 = xpos + 5;

                     //fonts->setcurrentfont( fonts->widget_text_enable.name );
                     //fonts->setmodifiertypo( fonts->widget_text_enable.typo );
                     //fonts->setmodifierunder( fonts->widget_text_enable.under );
                     //fonts->setmodifierstrike( fonts->widget_text_enable.strike );

                     setstyle( '0', &R, &G, &B, &A, colors, fonts );

                     char* tpstr = (char*) str;
                     int sh = fonts->getstringheight( tpstr );
                     int sp = fonts->getvspacing();

                     currentline = 0;
                     //while(*str && x1 - xpos + fonts->getcharwidth( (char) *str) < width)
                     while (*str)
                     {

                            if(has_focus && str == cursor)
                            {
                                   vlineRGBA( screen, x1, ypos + 1+ (currentline-firstlinevisible) * (sh+sp), ypos + sh + 1+ (currentline-firstlinevisible) * (sh+sp), colors->widget_border_disable.R, colors->widget_border_disable.G, colors->widget_border_disable.B, colors->widget_border_disable.A);
                                   vlineRGBA( screen, x1+1, ypos + 1+ (currentline-firstlinevisible) * (sh+sp), ypos + sh + 1+ (currentline-firstlinevisible) * (sh+sp), colors->widget_border_disable.R, colors->widget_border_disable.G, colors->widget_border_disable.B, colors->widget_border_disable.A);
                                   x1+=2;
                            }


                            if ((str[0]=='#') && (str[1]=='0')) // This corresponds to the normal style
                            {
                                   setstyle( str[1], &R, &G, &B, &A, colors, fonts );
                                   str++;
                            }
                            else if ((str[0]=='#') && (str[1]=='1'))
                            {
                                   setstyle( str[1], &R, &G, &B, &A, colors, fonts );
                                   str++;
                            }
                            else if ((str[0]=='#') && (str[1]=='2'))
                            {
                                   setstyle( str[1], &R, &G, &B, &A, colors, fonts );
                                   str++;
                            }
                            else if ((str[0]=='#') && (str[1]=='3'))
                            {
                                   setstyle( str[1], &R, &G, &B, &A, colors, fonts );
                                   str++;
                            }
                            else if ((str[0]=='#') && (str[1]=='4'))
                            {
                                   setstyle( str[1], &R, &G, &B, &A, colors, fonts );
                                   str++;
                            }
                            else if ((str[0]=='#') && (str[1]=='5'))
                            {
                                   setstyle( str[1], &R, &G, &B, &A, colors, fonts );
                                   str++;
                            }
                            else if ((str[0]=='#') && (str[1]=='6'))
                            {
                                   setstyle( str[1], &R, &G, &B, &A, colors, fonts );
                                   str++;
                            }
                            else if ((str[0]=='#') && (str[1]=='7'))
                            {
                                   setstyle( str[1], &R, &G, &B, &A, colors, fonts );
                                   str++;
                            }
                            else if ((str[0]=='#') && (str[1]=='8'))
                            {
                                   setstyle( str[1], &R, &G, &B, &A, colors, fonts );
                                   str++;
                            }
                            else if ((str[0]=='#') && (str[1]=='9'))
                            {
                                   setstyle( str[1], &R, &G, &B, &A, colors, fonts );
                                   str++;
                            }
                            else if (*str == '\n' )
                            {
                                   // if the current char is "RETURN" we go to the next line
                                   x1 = xpos + 2;
                                   currentline++;
                            }
                            else if (*str == '\t')
                            {
                                   // if the current char is a "TAB", we replace it with 5 SPACES
                                   for(unsigned int u=0; u<5; u++)
                                   {
                                          if ((currentline>=firstlinevisible) && (currentline<firstlinevisible+nblinevisible))
                                          {
                                                 fonts->drawcharleft( screen, ' ', x1, ypos + 2 + (currentline-firstlinevisible) * (sh+sp), R, G, B, A);
                                          }
                                          x1 += fonts->getcharwidth( ' ' ) + fonts->gethspacing();
                                   }
                            }
                            else
                            {
                                   if ((currentline>=firstlinevisible) && (currentline<firstlinevisible+nblinevisible))
                                   {
                                          fonts->drawcharleft( screen, *str, x1, ypos + 2 + (currentline-firstlinevisible) * (sh+sp), R, G, B, A);
                                   }
                                   x1 += fonts->getcharwidth( (char) *str ) + fonts->gethspacing();
                            }

                            if ((escalator==false) && (x1-xpos > width-10))
                            {
                                   x1 = xpos + 2;
                                   currentline++;
                                   if (currentline>currentnblinetotal) currentnblinetotal=currentline;
                            }

                            if ((escalator==true) && (x1-xpos > width-25))
                            {
                                   x1 = xpos + 2;
                                   currentline++;
                                   if (currentline>currentnblinetotal) currentnblinetotal=currentline;
                            }


                            ++str;
                     }

                     if(str == cursor)
                     {
                            vlineRGBA( screen, x1, ypos + 1+ (currentline-firstlinevisible) * (sh+sp), ypos + sh + 1+ (currentline-firstlinevisible) * (sh+sp), colors->widget_border_disable.R, colors->widget_border_disable.G, colors->widget_border_disable.B, colors->widget_border_disable.A);
                            vlineRGBA( screen, x1+1, ypos + 1+ (currentline-firstlinevisible) * (sh+sp), ypos + sh + 1+ (currentline-firstlinevisible) * (sh+sp), colors->widget_border_disable.R, colors->widget_border_disable.G, colors->widget_border_disable.B, colors->widget_border_disable.A);
                            x1+=2;
                     }


              }
              for (auto& c : children )
                     c->render( screen, colors, fonts );
       }

       nblinetotal = currentnblinetotal;
}

void MultiLineRichTextBoxWidget::updateScroll()
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

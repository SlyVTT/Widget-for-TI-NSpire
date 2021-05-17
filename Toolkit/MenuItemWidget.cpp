#include "MenuItemWidget.h"
#include "MenuPaneWidget.h"


MenuItemWidget::MenuItemWidget()
{
       widgettype = "MenuItem";
};

MenuItemWidget::MenuItemWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : MiniButtonWidget( l, x, y, w, h, p )
{
       widgettype = (char*) "MenuItem";
};

MenuItemWidget::~MenuItemWidget()
{
       //dtor
}


unsigned int MenuItemWidget::getfulltextwidth()
{
       return width_full_text;
}

void MenuItemWidget::drop( )
{
       is_dropped = true;
       is_visible = true;
}

void MenuItemWidget::undrop( )
{
       is_dropped = false;
       is_visible = false;
}


bool MenuItemWidget::ispressed()
{
       return is_pressed;
}

void MenuItemWidget::logic( CursorTask *mouse, KeyboardTask *keyboard )
{
       if (is_enabled && is_visible)
       {
              is_hovering = cursoron( mouse );
              bool currently_pressed = (mouse->state || keyboard->kbSCRATCH) && is_hovering;

              if(currently_pressed && !is_pressed)
              {
                     if (clickfunction)
                            clickfunction( (char*) "test" );
              }
              else if(!currently_pressed && is_pressed)
              {
                     if (releasefunction)
                            releasefunction( (char*) "test" );
              }
              else if(is_hovering)
              {
                     if (hoverfunction)
                            hoverfunction( (char*) "test" );
              }

              is_pressed = currently_pressed;

              if (is_pressed && (children.size()!=0))
              {
                     for ( auto& c : children )
                     {
                            //TODO : working on that part of the code for correct overlapping of the menus
                            if (parent)
                                   if (parent->getwidgettype() == "MenuPane")
                                          dynamic_cast<MenuPaneWidget*>(parent)->setchilddropped();

                            if (c->getwidgettype() == "MenuPane")
                            {
                                   c->setvisible();
                                   dynamic_cast<MenuPaneWidget*>(c)->drop();
                            }
                            else
                            {
                                   c->setvisible();
                            }
                     }
              }
              else if (is_pressed && (children.size()==0))
              {
                     if (parent)
                            if (parent->getwidgettype() == "MenuPane")
                            {
                                   dynamic_cast<MenuPaneWidget*>(parent)->unsetchilddropped();
                                   dynamic_cast<MenuPaneWidget*>(parent)->undrop();
                            }
              }

              for (auto& c : children )
                     c->logic( mouse, keyboard );
       }
}

void MenuItemWidget::render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts )
{
       labelarrow = label;
       width_full_text = fonts->getstringwidth( labelarrow );

       if (is_visible)
       {

              if (is_enabled)
              {
                     roundedBoxRGBA( screen, xpos, ypos, xpos+width, ypos+height-2, 3, colors->widget_filling_enable.R, colors->widget_filling_enable.G, colors->widget_filling_enable.B, colors->widget_filling_enable.A);

                     if (!is_hovering)
                     {
                            //roundedRectangleRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_border_enable.R, colors->widget_border_enable.G, colors->widget_border_enable.B, colors->widget_border_enable.A);
                     }
                     else
                     {
                            roundedRectangleRGBA( screen, xpos, ypos, xpos+width, ypos+height-2, 3, colors->widget_border_cursoron.R, colors->widget_border_cursoron.G, colors->widget_border_cursoron.B, colors->widget_border_cursoron.A);
                     }

                     fonts->setcurrentfont( fonts->widget_text_enable.name );
                     fonts->setmodifiertypo( fonts->widget_text_enable.typo );
                     fonts->setmodifierunder( fonts->widget_text_enable.under );
                     fonts->setmodifierstrike( fonts->widget_text_enable.strike );

                     //We check if the title can be written in the titlebar (with 5px on each side of the title + 30 pixels for the buttons on the right
                     drawablecharlabel = fonts->assertstringlength( label, width-2-2 );

                     labelarrow = label;
                     width_full_text = fonts->getstringwidth( labelarrow );

                     if (drawablecharlabel!=0)
                     {
                            drawablelabel = label; //fonts->reducestringtovisible( label, width-2 -2  );
                            int sl = fonts->getstringwidth( drawablelabel );
                            int sh = fonts->getstringheight( drawablelabel );
                            fonts->drawstringleft( screen, drawablelabel, xpos+2, ypos+(height-sh)/2, colors->widget_text_enable.R, colors->widget_text_enable.G, colors->widget_text_enable.B, colors->widget_text_enable.A );


                            // create a mark to indicate that there is a submenu
                            if (parent)
                            {
                                   // if the parent is a menubar, there is no need for the arrow indicator, it is absolutely logic to have a submenu
                                   if (parent->getwidgettype() != "MenuBar")
                                   {
                                          if (children.size()!=0)
                                          {

                                                 for(auto& c : children)
                                                 {
                                                        if (c->getwidgettype() == "MenuPane")
                                                        {
                                                               fonts->drawcharleft( screen, (char) '\u0010',  xpos+sl+5, ypos+(height-sh)/2, colors->widget_border_enable.R, colors->widget_border_enable.G, colors->widget_border_enable.B, colors->widget_border_enable.A);

                                                        }
                                                 }
                                          }
                                   }


                            }
                     }
              }
              else
              {
                     roundedBoxRGBA( screen, xpos, ypos, xpos+width, ypos+height-2, 3, colors->widget_filling_disable.R, colors->widget_filling_disable.G, colors->widget_filling_disable.B, colors->widget_filling_disable.A);
                     //Border of the button is black cause it is disabled
                     //roundedRectangleRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_border_disable.R, colors->widget_border_disable.G, colors->widget_border_disable.B, colors->widget_border_disable.A);

                     fonts->setcurrentfont( fonts->widget_text_disable.name );
                     fonts->setmodifiertypo( fonts->widget_text_disable.typo );
                     fonts->setmodifierunder( fonts->widget_text_disable.under );
                     fonts->setmodifierstrike( fonts->widget_text_disable.strike );

                     //We check if the title can be written in the titlebar (with 5px on each side of the title + 30 pixels for the buttons on the right
                     drawablecharlabel = fonts->assertstringlength( label, width-2-2 );

                     labelarrow = label;
                     width_full_text = fonts->getstringwidth( labelarrow );

                     if (drawablecharlabel!=0)
                     {
                            drawablelabel = fonts->reducestringtovisible( label, width-2 -2  );
                            //int sl = fonts->getstringwidth( drawablelabel );
                            int sh = fonts->getstringheight( drawablelabel );
                            fonts->drawstringleft( screen, drawablelabel, xpos+2, ypos+(height-sh)/2, colors->widget_text_disable.R, colors->widget_text_disable.G, colors->widget_text_disable.B, colors->widget_text_disable.A );
                     }
              }

              for (auto& c : children )
              {
                     if (c->isvisible())
                            c->render( screen, colors, fonts );
              }

       }
}

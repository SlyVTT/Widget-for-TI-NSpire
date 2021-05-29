#include "MenuPaneWidget.h"

#include "FontEngine.h"
#include "MenuItemWidget.h"


MenuPaneWidget::MenuPaneWidget() : ContainerVWidget ()
{
       widgettype = "MenuPane";
       this->undrop();
};


MenuPaneWidget::MenuPaneWidget(std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : ContainerVWidget( l, x, y, w, h, p )
{

       widgettype = "MenuPane";

       label = l;
       xrel=x;
       yrel=y;
       widrel=w;
       heirel=h;
       parent=p;

       if (parent)
       {
              xpos = parent->getuseablexpos();
              ypos = parent->getuseableypos()+12;

              // This part may be subjected to optimisation
              // TODO
              unsigned int tempw = 0;
              unsigned int temph = 0;

              for (auto& c : children )
              {
                     unsigned int currentwidgetwidth;

                     if (c->getwidgettype()=="MenuItem")
                            currentwidgetwidth = dynamic_cast<MenuItemWidget*>(c)->getfulltextwidth();
                     else
                            currentwidgetwidth =10;

                     if ( currentwidgetwidth > tempw) tempw = currentwidgetwidth;
                     //tempw = 50;
                     temph += 14;
              }

              width = tempw+5;
              height = temph;

              // We check we the menu is too wide and will exceed the right border of the screen, if so, we move it to the left accordingly to its size
              if (xpos+width>=SCREEN_WIDTH)
                     xpos=SCREEN_WIDTH-width-4;

              // END TODO

              parent->addpopupchild( this );

       }
       else // Note: THIS SITUATION SHOULD NOTE APPEAR - IT IS A NON SENSE TO ADD A MENU TO NOTHING - THIS IS CODED FOR FUTURE CONTEXTUAL MENUS
       {
              xpos=xrel;
              ypos=yrel;
              width=widrel;
              height=heirel;
       }

       unsigned int i=0;
       nbchildren = children.size();

       for (auto& c : children )
       {
              c->setdimensions( xpos+1, ypos+1 + 14*i, width-2, 12 );
              i++;
       }

       for (auto& c : children ) c->adjust();

       this->undrop();
};



MenuPaneWidget::~MenuPaneWidget()
{
       //dtor
}

void MenuPaneWidget::drop( )
{
       is_dropped = true;
       is_visible = true;
}

void MenuPaneWidget::undrop( )
{
       if (!has_child_menu_open)
       {
              is_dropped = false;
              is_visible = false;
       }
}

void MenuPaneWidget::setchilddropped()
{
       has_child_menu_open = true;
       is_visible = true;
}

void MenuPaneWidget::unsetchilddropped()
{
       has_child_menu_open = false;
}



void MenuPaneWidget::adjust()
{

       if (parent)
       {
              if(parent->getparent())
              {
                     //if the parent of the parent is a MenuPane, we shift on the right of the parent menu (this is a submenu)
                     if (parent->getparent()->getwidgettype() == "MenuPane")
                     {
                            if (parent->getxpos() + parent->getwidth() + 2 + width <= SCREEN_WIDTH) // si on ne dépasse pas le bord droit de l'écran, on met à droite
                            {
                                   xpos = parent->getxpos()+parent->getwidth() + 2;
                            }
                            else
                            {
                                   xpos = parent->getxpos() - width - 2;    // sinon on met à gauche
                            }

                            ypos = parent->getypos() ;

                     }
                     else
                     {
                            xpos = parent->getxpos();   // else we just put below
                            ypos = parent->getypos() + parent->getheight();
                     }



                     // This part may be subjected to optimisation
                     // TODO
                     int tempw = 0;
                     int temph = 0;

                     for (auto& c : children )
                     {
                            unsigned int currentwidgetwidth;

                            if (c->getwidgettype()=="MenuItem")
                                   currentwidgetwidth = dynamic_cast<MenuItemWidget*>(c)->getfulltextwidth();
                            else
                                   currentwidgetwidth =10;

                            if ( currentwidgetwidth > tempw) tempw = currentwidgetwidth;
                            //tempw = 50;
                            temph += 14;
                     }

                     width = tempw+5;
                     height = temph;

                     // We check we the menu is too wide and will exceed the right border of the screen, if so, we move it to the left accordingly to its size
                     if (xpos+width>=SCREEN_WIDTH)
                            xpos=SCREEN_WIDTH-width-4;

                     // END TODO

              }
       }
       else
       {
              xpos=xrel;
              ypos=yrel;
              width=widrel;
              height=heirel;
       }


       int i=0;
       nbchildren = children.size();

       for (auto& c : children )
       {
              c->setdimensions( xpos+1, ypos+1 + 14*i, width-2, 12 );
              i++;
       }

       for (auto& c : children )
              c->adjust();

}


void MenuPaneWidget::logic( CursorTask *mouse, KeyboardTask *keyboard )
{
       if (is_enabled && is_visible)
       {
              for (auto& c : children )
                     c->logic( mouse, keyboard );

              mouse->logic();
              keyboard->logic();

              is_hovering = cursoron( mouse );

              bool clickoutof = (mouse->state || keyboard->kbSCRATCH) && !is_hovering;

              if (clickoutof && !has_child_menu_open && mouse->ismouseevent() && keyboard->iskeyevent())
              {
                     this->undrop();
                     if (parent)
                            if (parent->getparent())
                                   if (parent->getparent()->getwidgettype() == "MenuPane")
                                   {
                                          dynamic_cast<MenuPaneWidget*>(parent->getparent())->unsetchilddropped();
                                          dynamic_cast<MenuPaneWidget*>(parent->getparent())->undrop();
                                   }
              }
       }
 /*      else
       {
              // DEBUG : test to see if it actually works
              for (auto& c : children )
                     c->logic( mouse, keyboard );
       }
*/
}



void MenuPaneWidget::render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts )
{


       // This part may be subjected to optimisation
       // TODO
       int tempw = 0;
       int temph = 0;

       for (auto& c : children )
       {
              unsigned int currentwidgetwidth;

              if (c->getwidgettype()=="MenuItem")
                     currentwidgetwidth = dynamic_cast<MenuItemWidget*>(c)->getfulltextwidth();
              else
                     currentwidgetwidth =10;

              if ( currentwidgetwidth > tempw) tempw = currentwidgetwidth;
              //tempw = 50;
              temph += 14;
       }


       width = tempw+5;
       height = temph;

       // We check we the menu is too wide and will exceed the right border of the screen, if so, we move it to the left accordingly to its size
       if (xpos+width>=SCREEN_WIDTH)
              xpos=SCREEN_WIDTH-width-4;

       int i=0;
       nbchildren = children.size();

       for (auto& c : children )
       {
              c->setdimensions( xpos+1, ypos+1 + 14*i, width-2, 12 );
              i++;
       }

       for (auto& c : children )
              c->adjust();


       // END TODO

       if (is_visible)
       {

              if (is_enabled)
              {
                     boxRGBA( screen, xpos, ypos, xpos+width, ypos+height, colors->widget_filling_enable.R, colors->widget_filling_enable.G, colors->widget_filling_enable.B, colors->widget_filling_enable.A);

                     if (!is_hovering)
                     {
                            roundedRectangleRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_border_enable.R, colors->widget_border_enable.G, colors->widget_border_enable.B, colors->widget_border_enable.A);
                     }
                     else
                     {
                            roundedRectangleRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_border_cursoron.R, colors->widget_border_cursoron.G, colors->widget_border_cursoron.B, colors->widget_border_cursoron.A);
                     }

              }
              else
              {
                     boxRGBA( screen, xpos, ypos, xpos+width, ypos+height, colors->widget_filling_disable.R, colors->widget_filling_disable.G, colors->widget_filling_disable.B, colors->widget_filling_disable.A);
                     roundedRectangleRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_border_disable.R, colors->widget_border_disable.G, colors->widget_border_disable.B, colors->widget_border_disable.A);

              }

              for (auto& c : children )
              {
                     c->render( screen, colors, fonts );
              }

       }
}

#include "MiniButtonWidget.h"


MiniButtonWidget::MiniButtonWidget()
{
       widgettype = "MiniButton";
       //strcpy( widgettype, (char*) "MiniButton");
};

MiniButtonWidget::MiniButtonWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : ButtonWidget( l, x, y, w, h, p )
{
       widgettype =  "MiniButton";
       //strcpy( widgettype, (char*) "MiniButton");
};

MiniButtonWidget::~MiniButtonWidget()
{

};


void MiniButtonWidget::settype( typesymbol type )
{
       switch(type)
       {
       case Bottom_Arrow:
              label = "\u001f";
              //label = (char*) "\u001f";
              break;
       case Up_Arrow:
              label = "\u001e";
              //label = (char*) "\u001e";
              break;
       case Left_Arrow:
              label = "\u0011";
              //label = (char*) "\u0011";
              break;
       case Right_Arrow:
              label = "\u0010";
              //label = (char*) "\u0010";
              break;
       case Close_Symbol:
              label = "\u0009";
              //label = (char*) "\u0009";
              break;
       case Question_Symbol:
              label = "\u003f";
              //label = (char*) "\u003f";
              break;
       case Exclamation_Symbol:
              label = "\u0021";
              //label = (char*) "\u0021";
              break;
       }
}

bool MiniButtonWidget::isticked( void )
{
       return is_ticked;
};

void MiniButtonWidget::invert( void )
{
       is_ticked = !is_ticked;
};


bool MiniButtonWidget::ispressed()
{
       return is_pressed;
}

void MiniButtonWidget::logic( CursorTask *mouse, KeyboardTask *keyboard )
{
       if (is_enabled && is_visible)
       {
              is_hovering = cursoron( mouse );
              bool currently_pressed = (mouse->state || keyboard->kbSCRATCH) && is_hovering;

              if(mouse_hold_down)
              {
                     mouse_hold_down = currently_pressed;
              }
              else if (currently_pressed && !is_ticked )
              {
                     invert();

                     if (clickfunction)
                            clickfunction( (char*) "test" );

                     mouse_hold_down = true;
              }
              else if (currently_pressed && is_ticked )
              {
                     invert();

                     if (releasefunction)
                            releasefunction( (char*) "test" );

                     mouse_hold_down = true;
              }
              else if (is_hovering)
              {
                     if (hoverfunction)
                            hoverfunction( (char*) "test" );
              }

              for (auto& c : children )
                     c->logic( mouse, keyboard );
       }

}


void MiniButtonWidget::render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts )
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
                     else if (is_pressed)
                     {
                            roundedRectangleRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, 0, 0, 255, 0);
                     }
                     else
                     {
                            roundedRectangleRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_border_cursoron.R, colors->widget_border_cursoron.G, colors->widget_border_cursoron.B, colors->widget_border_cursoron.A);
                     }

                     fonts->setcurrentfont( fonts->widget_text_enable.name );
                     fonts->setmodifiertypo( fonts->widget_text_enable.typo );
                     fonts->setmodifierunder( fonts->widget_text_enable.under );
                     fonts->setmodifierstrike( fonts->widget_text_enable.strike );

                     drawablecharlabel = fonts->assertstringlength( label, width-2-2 );

                     if (drawablecharlabel!=0)
                     {
                            drawablelabel = fonts->reducestringtovisible( label, width-2 -2  );

                            int sl = fonts->getstringwidth( drawablelabel );
                            int sh = fonts->getstringheight( drawablelabel );
                            fonts->drawstringleft( screen, drawablelabel, xpos+(width-sl)/2, ypos+(height-sh)/2, colors->widget_text_enable.R, colors->widget_text_enable.G, colors->widget_text_enable.B, colors->widget_text_enable.A );
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

                     drawablecharlabel = fonts->assertstringlength( label, width-2-2 );

                     if (drawablecharlabel!=0)
                     {
                            drawablelabel = fonts->reducestringtovisible( label, width-2 -2  );

                            int sl = fonts->getstringwidth( drawablelabel );
                            int sh = fonts->getstringheight( drawablelabel );
                            fonts->drawstringleft( screen, drawablelabel, xpos+(width-sl)/2, ypos+(height-sh)/2, colors->widget_text_disable.R, colors->widget_text_disable.G, colors->widget_text_disable.B, colors->widget_text_disable.A );
                     }
              }

              for (auto& c : children )
                     c->render( screen, colors, fonts );

       }
}

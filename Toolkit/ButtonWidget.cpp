#include "ButtonWidget.h"


ButtonWidget::ButtonWidget()
{
       widgettype = "Button";
};


ButtonWidget::ButtonWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : Widget( l, x, y, w, h, p )
{
       widgettype = "Button";
};


ButtonWidget::~ButtonWidget()
{

};


bool ButtonWidget::ispressed()
{
       return is_pressed;
}


void ButtonWidget::logic( CursorTask *mouse, KeyboardTask *keyboard )
{
       if (is_enabled && is_visible)
       {
              is_hovering = cursoron( mouse );
              bool currently_pressed = (mouse->state || keyboard->kbSCRATCH) && is_hovering;

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

              for (auto& c : children) c->logic( mouse, keyboard );
       }
}


void ButtonWidget::render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts )
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

                     // THIS IS THE PART OF THE ROUTINE THAT CHECK IF THE TEXT TO BE RENDERED IS TOO LONG AND IF SO THAT REDUCES IT TO THE DRAWABLE LENGTH
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
              else  // CODE TO BE APPLIED WHEN THE WIDGET IS VISIBLE BUT DISABLED
              {
                     roundedBoxRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_filling_disable.R, colors->widget_filling_disable.G, colors->widget_filling_disable.B, colors->widget_filling_disable.A);

                     roundedRectangleRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_border_disable.R, colors->widget_border_disable.G, colors->widget_border_disable.B, colors->widget_border_disable.A);

                     // THIS IS THE PART OF THE ROUTINE THAT CHECK IF THE TEXT TO BE RENDERED IS TOO LONG AND IF SO THAT REDUCES IT TO THE DRAWABLE LENGTH
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

              for (auto& c : children) c->render( screen, colors, fonts );
       }
}

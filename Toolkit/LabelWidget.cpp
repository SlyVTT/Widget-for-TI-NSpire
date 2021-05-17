#include "LabelWidget.h"

LabelWidget::LabelWidget()
{
       widgettype = "Label";
       //strcpy( widgettype, (char*) "Label");
};

LabelWidget::LabelWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : Widget( l, x, y, w, h, p )
{
       widgettype = "Label";
       //strcpy( widgettype, (char*) "Label");
};

LabelWidget::~LabelWidget()
{

};

void LabelWidget::setalignment( LabelWidget::align type )
{
       alignment = type;
};


LabelWidget::align LabelWidget::getalignement()
{
       return alignment;
};

void LabelWidget::logic( CursorTask *mouse, KeyboardTask *keyboard )
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

              for (auto& c : children )
                     c->logic( mouse, keyboard );
       }
}

void LabelWidget::render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts )
{
       if (is_visible)
       {

              if (is_enabled)
              {
                     roundedBoxRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_filling_enable.R, colors->widget_filling_enable.G, colors->widget_filling_enable.B, colors->widget_filling_enable.A);

                     fonts->setcurrentfont( fonts->widget_text_enable.name );
                     fonts->setmodifiertypo( fonts->widget_text_enable.typo );
                     fonts->setmodifierunder( fonts->widget_text_enable.under );
                     fonts->setmodifierstrike( fonts->widget_text_enable.strike );

                     //We check if the titel can be written in the titlebar (with 5px on each side of the title + 30 pixels for the buttons on the right
                     drawablecharlabel = fonts->assertstringlength( label, width-2-2 );

                     if (drawablecharlabel!=0)
                     {
                            drawablelabel = fonts->reducestringtovisible( label, width-2 -2  );
                            int sl = fonts->getstringwidth( drawablelabel );
                            int sh = fonts->getstringheight( drawablelabel );

                            if (alignment==centered) fonts->drawstringleft( screen, drawablelabel, xpos+(width-sl)/2, ypos+(height-sh)/2, colors->widget_text_enable.R, colors->widget_text_enable.G, colors->widget_text_enable.B, colors->widget_text_enable.A );

                            if (alignment==left) fonts->drawstringleft( screen, drawablelabel, xpos, ypos+(height-sh)/2, colors->widget_text_enable.R, colors->widget_text_enable.G, colors->widget_text_enable.B, colors->widget_text_enable.A );

                            if (alignment==right) fonts->drawstringleft( screen, drawablelabel, xpos+(width-sl), ypos+(height-sh)/2, colors->widget_text_enable.R, colors->widget_text_enable.G, colors->widget_text_enable.B, colors->widget_text_enable.A );
                     }

              }
              else
              {
                     roundedBoxRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_filling_disable.R, colors->widget_filling_disable.G, colors->widget_filling_disable.B, colors->widget_filling_disable.A);

                     fonts->setcurrentfont( fonts->widget_text_disable.name );
                     fonts->setmodifiertypo( fonts->widget_text_disable.typo );
                     fonts->setmodifierunder( fonts->widget_text_disable.under );
                     fonts->setmodifierstrike( fonts->widget_text_disable.strike );

                     //We check if the titel can be written in the titlebar (with 5px on each side of the title + 30 pixels for the buttons on the right
                     drawablecharlabel = fonts->assertstringlength( label, width-2-2 );

                      if (drawablecharlabel!=0)
                     {
                            drawablelabel = fonts->reducestringtovisible( label, width-2 -2  );
                            int sl = fonts->getstringwidth( drawablelabel );
                            int sh = fonts->getstringheight( drawablelabel );

                            if (alignment==centered) fonts->drawstringleft( screen, drawablelabel, xpos+(width-sl)/2, ypos+(height-sh)/2, colors->widget_text_disable.R, colors->widget_text_disable.G, colors->widget_text_disable.B, colors->widget_text_disable.A );

                            if (alignment==left) fonts->drawstringleft( screen, drawablelabel, xpos, ypos+(height-sh)/2, colors->widget_text_disable.R, colors->widget_text_disable.G, colors->widget_text_disable.B, colors->widget_text_disable.A );

                            if (alignment==right) fonts->drawstringleft( screen, drawablelabel, xpos+(width-sl), ypos+(height-sh)/2, colors->widget_text_disable.R, colors->widget_text_disable.G, colors->widget_text_disable.B, colors->widget_text_disable.A );
                     }

              }

              for (auto& c : children )
                     c->render( screen, colors, fonts );

       }
}

#include "SpacerWidget.h"

SpacerWidget::SpacerWidget()
{
       widgettype = "Spacer";
       //strcpy( widgettype, (char*) "Spacer");
};

SpacerWidget::SpacerWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : Widget( l, x, y, w, h, p )
{
       widgettype = "Spacer";
       //strcpy( widgettype, (char*) "Spacer");
};

SpacerWidget::~SpacerWidget()
{

};


void SpacerWidget::logic( CursorTask *mouse, KeyboardTask *keyboard )
{
       if (is_enabled && is_visible)
       {
              for (auto& c : children )
                     c->logic( mouse, keyboard );
       }
}

void SpacerWidget::render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts )
{
       if (is_visible)
       {

              if (is_enabled)
              {

              }
              else
              {

              }

              for (auto& c : children )
                     c->render( screen, colors, fonts );
       }
}

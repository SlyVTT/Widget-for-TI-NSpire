#ifndef LABELWIDGET_H
#define LABELWIDGET_H

#include "Widget.h"





class LabelWidget : public Widget
{
public:
       LabelWidget();
       LabelWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p );
       virtual ~LabelWidget();

       enum align
       {
              centered = 0,
              left = 1,
              right = 2
       };

       virtual void logic( CursorTask *mouse, KeyboardTask *keyboard ) override;
       virtual void render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts ) override;

       virtual void setalignment( align type );

       virtual align getalignement();

protected:
       bool is_pressed = false;
       align alignment = centered;

private:
};

#endif // LABELWIDGET_H

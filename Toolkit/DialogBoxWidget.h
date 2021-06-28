#ifndef DIALOGBOXWIDGET_H
#define DIALOGBOXWIDGET_H

#include "WindowWidget.h"


class DialogBoxWidget : public WindowWidget
{
public:
    DialogBoxWidget();
    DialogBoxWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p );
    virtual ~DialogBoxWidget();

    virtual void logic( CursorTask *mouse, KeyboardTask *keyboard ) override;
    virtual void render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts ) override;


    // These methods must be override cause window geometry is a bit different with the title bar
    virtual unsigned int getuseablexpos() override;
    virtual unsigned int getuseableypos() override;
    virtual unsigned int getuseablewidth() override;
    virtual unsigned int getuseableheight() override;

protected:
    bool ismouseontitlebar(CursorTask *mouse) override;

private:
};

#endif // DIALOGBOXWIDGET_H

#ifndef DROPBOXWIDGET_H
#define DROPBOXWIDGET_H

#include "Widget.h"
#include "ListBoxWidget.h"
#include "MiniButtonWidget.h"


class DropBoxWidget : public Widget
{
public:

    DropBoxWidget();
    DropBoxWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p );
    virtual ~DropBoxWidget();


    virtual void adjust() override;

    virtual bool ispressed();

    virtual void drop();

    virtual void undrop();

    virtual void logic( CursorTask *mouse, KeyboardTask *keyboard ) override;

    virtual void render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts ) override;

    virtual void additem( std::string item );

    virtual int getnbitem();

    virtual std::string getitem( int itemnumber );

    virtual int getselected();

    virtual std::string getselecteditem();

    virtual void validate();

    virtual void escape();

    virtual bool isupdated();

protected:

    MiniButtonWidget *dropbutton;
    ListBoxWidget *listbox;

    int selected_item = -1;     // -1 means no selection have been made yet
    std::string selected_item_value;

private:

    bool is_pressed = false;
    bool is_dropped = false;
    bool has_been_updated = false;

};

#endif // DROPBOXWIDGET_H

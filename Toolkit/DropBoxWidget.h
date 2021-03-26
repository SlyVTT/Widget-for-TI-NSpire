#ifndef DROPBOXWIDGET_H
#define DROPBOXWIDGET_H

#include "Widget.h"
#include "ListBoxWidget.h"
#include "MiniButtonWidget.h"


class DropBoxWidget : public Widget
{
    public:
        DropBoxWidget();
        DropBoxWidget(char *l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p );

        virtual void adjust() override;

        virtual ~DropBoxWidget() {};

        virtual bool ispressed();

        virtual void drop() { is_dropped = true; this->listbox->setvisible(); };
        virtual void undrop() { is_dropped = false; this->listbox->setinvisible(); };

        virtual void logic( CursorTask *mouse, KeyboardTask *keyboard ) override;

        virtual void render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts ) override;

        virtual void additem( char *item ) { listbox->additem( item ); };

        virtual int getnbitem() { return listbox->getnbitem(); };

        virtual char* getitem( int itemnumber ) { return listbox->getitem( itemnumber ); };

        virtual void validate();

        virtual void escape();

    protected:

        MiniButtonWidget *dropbutton;
        ListBoxWidget *listbox;

        int selected_item = -1;     // -1 means no selection have been made yet
        char* selected_item_value;

    private:

        bool is_pressed = false;
        bool is_dropped = false;

};

#endif // DROPBOXWIDGET_H

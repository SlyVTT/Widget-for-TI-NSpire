#ifndef FILEDIALOGBOX_H
#define FILEDIALOGBOX_H

#include "DialogBoxWidget.h"
#include "ContainerHWidget.h"
#include "ContainerVWidget.h"
#include "ButtonWidget.h"
#include "InputWidget.h"
#include "ListBoxWidget.h"
#include "SpacerWidget.h"
#include "LabelWidget.h"


class FileDialogBoxWidget : public DialogBoxWidget
{
    public:
        FileDialogBoxWidget();
        FileDialogBoxWidget( char *l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p );

        virtual ~FileDialogBoxWidget();

        ContainerVWidget *vertical_layout;
        LabelWidget *header_text;
        ContainerHWidget *horizontal_split;
        InputWidget *input_name;
        ContainerHWidget *horizontal_split_button;
        ListBoxWidget *filelist;
        ListBoxWidget *folderlist;
        SpacerWidget *space;
        SpacerWidget *space2;
        ButtonWidget *okbutton;
        ButtonWidget *cancelbutton;

        virtual void logic( CursorTask *mouse, KeyboardTask *keyboard ) override;

        virtual void render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts ) override;

            // These methods must be override cause window geometry is a bit different with the title bar
        virtual unsigned int getuseablexpos() override;
        virtual unsigned int getuseableypos() override;
        virtual unsigned int getuseablewidth() override;
        virtual unsigned int getuseableheight() override;

    protected:
        bool ismouseontitlebar(CursorTask *mouse) override;
        char pathtoexplore[256];
        char fileselected[64];
        char fullname[320];

    private:
        int listdir(const char *path);
};

#endif // FILEDIALOGBOX_H

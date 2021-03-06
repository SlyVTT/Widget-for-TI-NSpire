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
    FileDialogBoxWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p );
    virtual ~FileDialogBoxWidget();

    virtual void logic( CursorTask *mouse, KeyboardTask *keyboard ) override;

    virtual void render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts ) override;

    enum filedialogtype
    {
        fileopen = 0,
        filesaveas = 1,
        filesave = 2
    };

    // These methods must be override cause window geometry is a bit different with the title bar
    virtual unsigned int getuseablexpos() override;
    virtual unsigned int getuseableypos() override;
    virtual unsigned int getuseablewidth() override;
    virtual unsigned int getuseableheight() override;

    virtual void setdialogtype( FileDialogBoxWidget::filedialogtype type );
    virtual FileDialogBoxWidget::filedialogtype getdialogtype( void );



    bool validated = false;
    bool canceled = false;

    virtual char *getselectedfilename();
    virtual char *getselectedpath();
    virtual char *getselectedfullname();

protected:
    bool ismouseontitlebar(CursorTask *mouse) override;
    std::string pathtoexplore;
    std::string fileselected;
    std::string fullname;

    ContainerVWidget *vertical_layout;
    LabelWidget *header_text;
    LabelWidget *bottom_text;
    ContainerHWidget *horizontal_split;
    InputWidget *input_name;
    ContainerHWidget *horizontal_split_button;
    ListBoxWidget *filelist;
    ListBoxWidget *folderlist;
    SpacerWidget *space;
    SpacerWidget *space2;
    ButtonWidget *okbutton;
    ButtonWidget *cancelbutton;

private:
    int listdir(std::string path);
    filedialogtype typedialog;
};

#endif // FILEDIALOGBOX_H

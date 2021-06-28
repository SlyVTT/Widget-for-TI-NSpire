#include "FileDialogBoxWidget.h"
#include <stdio.h>
#include <dirent.h>
#include <string.h>


std::string simplify(std::string path)
{
    // using vector in place of stack
    std::vector<std::string> v;
    int n = path.length();
    std::string ans;
    for (int i = 0; i < n; i++)
    {
        std::string dir = "";
        // forming the current directory.
        while (i < n && path[i] != '/')
        {
            dir += path[i];
            i++;
        }

        // if ".." , we pop.
        if (dir == "..")
        {
            if (!v.empty())
                v.pop_back();
        }
        else if (dir == "." || dir == "")
        {
            // do nothing (added for better understanding.)
        }
        else
        {
            // push the current directory into the vector.
            v.push_back(dir);
        }
    }

    // forming the ans
    for (auto i : v)
    {
        ans += "/" + i;
    }

    // vector is empty
    if (ans == "")
        return  std::string("/");

    return ans;
}


FileDialogBoxWidget::FileDialogBoxWidget()
{
    widgettype = "FileDialogBox";
    typedialog = fileopen;
}

FileDialogBoxWidget::~FileDialogBoxWidget()
{
    //dtor
}


void FileDialogBoxWidget::setdialogtype( FileDialogBoxWidget::filedialogtype type )
{
    typedialog = type;
    if (type==fileopen)
    {
        this->setlabel( "File Open ...");
        header_text->setlabel("Pick a folder and a file to open :");
        filelist->enable();
        bottom_text->setlabel("The selected file is :");
    }
    else  if (type==filesaveas)
    {
        this->setlabel( "File Save As ...");
        header_text->setlabel("Pick a folder for save location :");
        filelist->disable();
        bottom_text->setlabel("Name of the file (ending with .tns) :");
    }
    else  if (type==filesave)
    {
        this->setlabel( "File Save ...");
        header_text->setlabel("Pick a folder for save location :");
        filelist->disable();
        bottom_text->setlabel("Name of the file (ending with .tns) :");
    }
}


FileDialogBoxWidget::filedialogtype FileDialogBoxWidget::getdialogtype( void )
{
    return typedialog;
}


char* FileDialogBoxWidget::getselectedfilename()
{
    return (char *) fileselected.c_str();
};


char* FileDialogBoxWidget::getselectedpath()
{
    return (char *) pathtoexplore.c_str();
};

char* FileDialogBoxWidget::getselectedfullname()
{
    return (char *) fullname.c_str();
};


int FileDialogBoxWidget::listdir( std::string path)
{
    std::string name;
    struct dirent *ent;
    DIR *dir = opendir(path.c_str());
    while((ent = readdir(dir)))
    {
        //Test whether it's a directory
        name = path+"/"+std::string(ent->d_name);
        DIR *test = opendir( name.c_str() );
        if(test)    // This is a directory and we add to the folder list widget
        {
            closedir(test);
            std::string temp(ent->d_name);
            folderlist->additem( (char*) temp.c_str() );
        }
        else    // this is a file and we add to the file list widget
        {
            std::string temp(ent->d_name);
            filelist->additem( (char*) temp.c_str() );
        }
    }
    closedir(dir);
    return 0;
}


FileDialogBoxWidget::FileDialogBoxWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ): DialogBoxWidget( l, x, y, w, h, p )
{
    widgettype = "FileDialogBox";
    typedialog = fileopen;
    pathtoexplore = std::string( "/documents/Widget/" );

    vertical_layout = new ContainerVWidget( "ContainerV", 1, 1, 1, 1, this );

    header_text = new LabelWidget( "Pick a file",1,1,1,1, vertical_layout );
    header_text->setalignment( LabelWidget::left );
    vertical_layout->addconstraint( 10, (char*) "px" );

    horizontal_split = new ContainerHWidget( "ContainerH", 1, 1, 1, 1, vertical_layout );
    vertical_layout->addconstraint( 100, (char*) "%" );

    folderlist = new ListBoxWidget( "Folder List",1,1,1,1, horizontal_split );
    horizontal_split->addconstraint( 50, (char*) "%" );

    space = new SpacerWidget( "Spacer",1,1,1,1, horizontal_split );
    horizontal_split->addconstraint( 5, (char*) "px" );

    filelist = new ListBoxWidget( "File List",1,1,1,1, horizontal_split );
    horizontal_split->addconstraint( 50, (char*) "%" );

    bottom_text = new LabelWidget( "Selected file",1,1,1,1, vertical_layout );
    bottom_text->setalignment( LabelWidget::left );
    vertical_layout->addconstraint( 10, (char*) "px" );

    input_name = new InputWidget( ".",1,1,1,1, vertical_layout );
    input_name->setcontent( (char *) pathtoexplore.c_str() );
    vertical_layout->addconstraint( 15, (char*) "px" );


    //TO BE REMOVED - JUST FOR TESTING
    //space = new SpacerWidget( (char*) "Spacer",1,1,1,1, vertical_layout );
    //vertical_layout->addconstraint( 100, (char*) "%" );


    horizontal_split_button = new ContainerHWidget( "ContainerH", 1, 1, 1, 1, vertical_layout );
    vertical_layout->addconstraint( 15, (char*) "px" );

    space2 = new SpacerWidget( "Spacer",1,1,1,1, horizontal_split_button );
    horizontal_split_button->addconstraint( 100, (char*) "%" );

    okbutton = new ButtonWidget( "OK",1,1,1,1, horizontal_split_button );;
    horizontal_split_button->addconstraint( 70, (char*) "px" );

    cancelbutton = new ButtonWidget( "Cancel",1,1,1,1, horizontal_split_button );;
    horizontal_split_button->addconstraint( 70, (char*) "px" );

    listdir( (char *) pathtoexplore.c_str() );

    this->adjust();

}


unsigned int FileDialogBoxWidget::getuseablexpos()
{
    return xpos + 2;
}


unsigned int FileDialogBoxWidget::getuseableypos()
{
    return ypos + 14;               // we just remove the size of the title bar (12px+2px = 14px)
}


unsigned int FileDialogBoxWidget::getuseablewidth()
{
    return width - 4;
}


unsigned int FileDialogBoxWidget::getuseableheight()
{
    return height - 16;                // we just remove the size of the title bar (12px + 2px + 2px = 16px)
}


bool FileDialogBoxWidget::ismouseontitlebar(CursorTask *mouse)
{
    return ((unsigned int) mouse->x >= xpos+2) && ((unsigned int) mouse->y >= ypos+2) && ((unsigned int) mouse->x <= xpos+width-32) && ((unsigned int) mouse->y <= ypos+12);
}


void FileDialogBoxWidget::logic( CursorTask *mouse, KeyboardTask *keyboard )
{
    if (is_activated)
    {

        is_hovering = cursoron( mouse );

        if(is_hovering)
        {
            if (hoverfunction)
                hoverfunction( (char*) "test" );
        }

        bool ontitle = false;

        if (ismouseontitlebar( mouse ))
        {
            mouse->setcursortype( CursorTask::handfinger );
            ontitle = true;
        }
        else
        {
            mouse->setcursortype( CursorTask::pointer );
        }


        if (ontitle && keyboard->kbSCRATCH && !startmove)
        {
            movemode = true;
            startmove = true;
            clickX = mouse->x;
            clickY = mouse->y;
        }
        else if (ontitle && keyboard->kbSCRATCH && startmove)
        {
            movemode = true;
        }
        else
        {
            movemode = false;
            startmove = false;
        }

        // Here comes the resize logic
        // DialopBow cannot be resized


        // Here comes the move logic ...
        if (movemode && ismouseontitlebar( mouse ))
        {
            mouse->logic();

            int deltax = (int) mouse->x - (int) clickX;
            int deltay = (int) mouse->y - (int) clickY;

            //we go left
            if (deltax < 0)
            {
                //if ((int) xpos > (int) (-1 * deltax))   xpos += deltax;
                if ((int) (xpos + deltax) > (int) parent->getuseablexpos() )   xpos += deltax;
            }
            //we go up
            if (deltay < 0)
            {
                //if ((int) ypos > (int) (-1 * deltay))   ypos += deltay;
                if ((int) (ypos + deltay) > (int) parent->getuseableypos() )   ypos += deltay;
            }

            //we go right
            if (deltax > 0)
            {
                //if ((int) (SCREEN_WIDTH - xpos - width) > (int) (deltax))   xpos += deltax;
                if ((int) (parent->getuseablexpos() + parent->getuseablewidth() - xpos - width) > (int) (deltax))   xpos += deltax;
            }
            //we go down
            if (deltay > 0)
            {
                //if ((int) (SCREEN_HEIGHT - ypos - height) > (int) (deltay))   ypos += deltay;
                if ((int) (parent->getuseableypos() + parent->getuseableheight() - ypos - height) > (int) (deltay))   ypos += deltay;
            }

            adjust();

            clickX = mouse->x;
            clickY = mouse->y;

        }


        for (auto& c : children )
            c->logic( mouse, keyboard );


        if (folderlist->validated)
        {
            //strcat( pathtoexplore, folderlist->getselecteditem() );
            //strcpy(pathtoexplore, simplify(pathtoexplore) );
            //strcat( pathtoexplore, "/" );

            pathtoexplore = simplify(pathtoexplore+std::string(folderlist->getselecteditem()) )+"/";

            folderlist->flush();
            filelist->flush();
            folderlist->validated = false;
            listdir( pathtoexplore );
            input_name->setcontent( pathtoexplore.c_str() );
        }

        if (filelist->validated)
        {
            fileselected = std::string( filelist->getselecteditem() );

            filelist->validated = false;

            fullname = pathtoexplore+fileselected;

            input_name->setcontent( fullname.c_str() );
        }



        if (okbutton->ispressed())
        {
            validated = true;
            canceled = false;
            this->setinvisible();
        }


        if (cancelbutton->ispressed())
        {
            validated = false;
            canceled = true;
            this->setinvisible();
        }

        // No PopUpChild

    }
}


void FileDialogBoxWidget::render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts )
{

    if (is_visible)
    {

        if (is_enabled)
        {
            roundedBoxRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_filling_enable.R, colors->widget_filling_enable.G, colors->widget_filling_enable.B, colors->widget_filling_enable.A);
            roundedBoxRGBA( screen, xpos, ypos, xpos+width, ypos+12, 3, colors->window_titlebar_enable.R, colors->window_titlebar_enable.G, colors->window_titlebar_enable.B, colors->window_titlebar_enable.A);

            if (!is_hovering)
            {
                roundedRectangleRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_border_enable.R, colors->widget_border_enable.G, colors->widget_border_enable.B, colors->widget_border_enable.A);
            }
            else
            {
                roundedRectangleRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_border_cursoron.R, colors->widget_border_cursoron.G, colors->widget_border_cursoron.B, colors->widget_border_cursoron.A);
            }

            fonts->setcurrentfont( fonts->window_titlebartext_enable.name );
            fonts->setmodifiertypo( fonts->window_titlebartext_enable.typo );
            fonts->setmodifierunder( fonts->window_titlebartext_enable.under );
            fonts->setmodifierstrike( fonts->window_titlebartext_enable.strike );

            drawablecharlabel = fonts->assertstringlength( label, width-5-5-30 );

            if (drawablecharlabel!=0)
            {
                drawablelabel = fonts->reducestringtovisible( label, width-5 -5 -30 );

                //int sl = fonts->getstringwidth( drawablelabel );
                int sh = fonts->getstringheight( drawablelabel );
                fonts->drawstringleft( screen, drawablelabel, xpos+5, ypos+sh/2, colors->window_titlebartext_enable.R, colors->window_titlebartext_enable.G, colors->window_titlebartext_enable.B, colors->window_titlebartext_enable.A );
            }
        }
        else
        {
            roundedBoxRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_filling_disable.R, colors->widget_filling_disable.G, colors->widget_filling_disable.B, colors->widget_filling_disable.A);
            roundedBoxRGBA( screen, xpos, ypos, xpos+width, ypos+12, 3, colors->window_titlebar_disable.R, colors->window_titlebar_disable.G, colors->window_titlebar_disable.B, colors->window_titlebar_disable.A);
            roundedRectangleRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_border_disable.R, colors->widget_border_disable.G, colors->widget_border_disable.B, colors->widget_border_disable.A);

            fonts->setcurrentfont( fonts->window_titlebartext_disable.name );
            fonts->setmodifiertypo( fonts->window_titlebartext_disable.typo );
            fonts->setmodifierunder( fonts->window_titlebartext_disable.under );
            fonts->setmodifierstrike( fonts->window_titlebartext_disable.strike );

            drawablecharlabel = fonts->assertstringlength( label, width-5-5-30 );

            if (drawablecharlabel!=0)
            {
                drawablelabel = fonts->reducestringtovisible( label, width-5 -5 -30 );

                //int sl = fonts->getstringwidth( drawablelabel );
                int sh = fonts->getstringheight( drawablelabel );
                fonts->drawstringleft( screen, drawablelabel, xpos+5, ypos+sh/2, colors->window_titlebartext_disable.R, colors->window_titlebartext_disable.G, colors->window_titlebartext_disable.B, colors->window_titlebartext_disable.A );
            }
        }

        /*
        // THIS IS FOR DEBUGGING THE DEPTH BUFFER PORTION OF THE CODE
        char* tempID;
        sprintf( tempID, "ID = %ld", WidgetID );
        fonts->setcurrentfont( THIN_FONT );
        fonts->setmodifiertypo( Bold );
        fonts->drawstringleft( screen, tempID, xpos+2, ypos+4, 255, 0, 0, 255 );
        */

        for (auto& c : children )
        {
            if (c->isvisible())
            {
                c->render( screen, colors, fonts );
            }
        }

        // No PopUpChild to be drawn in DialogBox
    }
}


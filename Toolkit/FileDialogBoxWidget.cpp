#include "FileDialogBoxWidget.h"
#include <stdio.h>
#include <dirent.h>
#include <string.h>


char *simplify(char *inputpath)
{
    std::string path( inputpath );
    // using vector in place of stack
    std::vector<std::string> v;
    int n = path.length();
    std::string ans;
    for (int i = 0; i < n; i++) {
        std::string dir = "";
        // forming the current directory.
        while (i < n && path[i] != '/') {
            dir += path[i];
            i++;
        }

        // if ".." , we pop.
        if (dir == "..") {
            if (!v.empty())
                v.pop_back();
        }
        else if (dir == "." || dir == "") {
            // do nothing (added for better understanding.)
        }
        else {
            // push the current directory into the vector.
            v.push_back(dir);
        }
    }

    // forming the ans
    for (auto i : v) {
        ans += "/" + i;
    }

    // vector is empty
    if (ans == "")
        return (char *) "/";

    return (char *) ans.c_str();
}


FileDialogBoxWidget::FileDialogBoxWidget()
{
    strcpy( widgettype, (char*) "FileDialogBox");
    //strcpy( pathtoexplore, (char *) "./Widget\0" );
}

FileDialogBoxWidget::~FileDialogBoxWidget()
{
    //dtor
}

int FileDialogBoxWidget::listdir(const char *path)
{
    char name[255];
    struct dirent *ent;
    DIR *dir = opendir(path);
    while((ent = readdir(dir)))
    {
        //Test whether it's a directory
        strcpy(name, path);
        strcat(name,"/");
        strcat(name, ent->d_name);
        DIR *test = opendir( name );
        if(test)    // This is a directory and we add to the folder list widget
        {
            closedir(test);
            char *temp = (char*) malloc( strlen(ent->d_name) +1 );
            strcpy(temp, ent->d_name );
            folderlist->additem( (char *) temp );
        }
        else    // this is a file and we add to the file list widget
        {
            char *temp = (char*) malloc( strlen(ent->d_name) +1 );
            strcpy(temp, ent->d_name );
            filelist->additem( (char *) temp );
        }
    }
    closedir(dir);
  return 0;
}


FileDialogBoxWidget::FileDialogBoxWidget( char *l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ): DialogBoxWidget( l, x, y, w, h, p )
{
    strcpy( widgettype, (char*) "FileDialogBox");
    strcpy( pathtoexplore, (char *) "/documents/Widget/" );

        vertical_layout = new ContainerVWidget( (char *) "ContainerV", 1, 1, 1, 1, this );

        header_text = new LabelWidget( (char*) "Pick a file",1,1,1,1, vertical_layout );
        header_text->setalignment( left );
        vertical_layout->addconstraint( 10, (char*) "px" );

        horizontal_split = new ContainerHWidget( (char *) "ContainerH", 1, 1, 1, 1, vertical_layout );
        vertical_layout->addconstraint( 100, (char*) "%" );

            folderlist = new ListBoxWidget( (char*) "Folder List",1,1,1,1, horizontal_split );
            horizontal_split->addconstraint( 50, (char*) "%" );

            space = new SpacerWidget( (char*) "Spacer",1,1,1,1, horizontal_split );
            horizontal_split->addconstraint( 5, (char*) "px" );

            filelist = new ListBoxWidget( (char*) "File List",1,1,1,1, horizontal_split );
            horizontal_split->addconstraint( 50, (char*) "%" );


            input_name = new InputWidget( (char*) ".",1,1,1,1, vertical_layout );
            input_name->setcontent( (char *) pathtoexplore );
            vertical_layout->addconstraint( 15, (char*) "px" );


        //TO BE REMOVED - JUST FOR TESTING
        //space = new SpacerWidget( (char*) "Spacer",1,1,1,1, vertical_layout );
        //vertical_layout->addconstraint( 100, (char*) "%" );


        horizontal_split_button = new ContainerHWidget( (char *) "ContainerH", 1, 1, 1, 1, vertical_layout );
        vertical_layout->addconstraint( 15, (char*) "px" );

            space2 = new SpacerWidget( (char*) "Spacer",1,1,1,1, horizontal_split_button );
            horizontal_split_button->addconstraint( 100, (char*) "%" );

            okbutton = new ButtonWidget( (char*) "OK",1,1,1,1, horizontal_split_button );;
            horizontal_split_button->addconstraint( 70, (char*) "px" );

            cancelbutton = new ButtonWidget( (char*) "Cancel",1,1,1,1, horizontal_split_button );;
            horizontal_split_button->addconstraint( 70, (char*) "px" );

            listdir( (char *) pathtoexplore );

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
            strcat( pathtoexplore, folderlist->getselecteditem() );
            strcpy(pathtoexplore, simplify(pathtoexplore) );
            strcat( pathtoexplore, "/" );

            folderlist->flush();
            filelist->flush();
            folderlist->validated = false;
            listdir( (char *) pathtoexplore );
            input_name->setcontent( (char *) pathtoexplore );
        }

        if (filelist->validated)
        {
            strcpy( fileselected, filelist->getselecteditem() );
            filelist->validated = false;

            strcpy( fullname, pathtoexplore );
            //strcat( fullname, "/" );
            strcat( fullname, fileselected );
            input_name->setcontent( (char *) fullname );
        }






        if (okbutton->ispressed())
        {
            validated = true;
            canceled = false;
        }


        if (cancelbutton->ispressed())
        {
            validated = false;
            canceled = true;
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

            //We check if the title can be written in the titlebar (with 5px on each side of the title + 30 pixels for the buttons on the right
            drawablecharlabel = fonts->assertstringlength( label, width-5-5-30 );

            strcpy( drawablelabel, label );
            if ((drawablecharlabel < strlen(label)) && (drawablecharlabel >=2)) drawablelabel[drawablecharlabel-2] = '\u0010';
            if ((drawablecharlabel < strlen(label)) && (drawablecharlabel >=1)) drawablelabel[drawablecharlabel-1] = '\0';

            if (drawablecharlabel!=0)
            {
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

            //We check if the titel can be written in the titlebar (with 5px on each side of the title + 30 pixels for the buttons on the right
            drawablecharlabel = fonts->assertstringlength( label, width-5-5-30 );

            strcpy( drawablelabel, label );
            if ((drawablecharlabel < strlen(label)) && (drawablecharlabel >=2)) drawablelabel[drawablecharlabel-2] = '\u0010';
            if ((drawablecharlabel < strlen(label)) && (drawablecharlabel >=1)) drawablelabel[drawablecharlabel-1] = '\0';

            if (drawablecharlabel!=0)
            {
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


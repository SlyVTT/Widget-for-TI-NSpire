#include "Toolkit/GUIToolkit.h"



extern void Debug( char* strtolog )
{
    FILE *pFile;
    pFile = fopen( "/documents/Widget/Logger.txt.tns" , "a" );
    if (pFile==NULL) { return; }
    fprintf( pFile, "%s\n", strtolog );
    fclose( pFile );
    return;
}

extern void DebugINT( int inttolog )
{
    FILE *pFile;
    pFile = fopen( "/documents/Widget/Logger.txt.tns" , "a" );
    if (pFile==NULL) { return; }
    fprintf( pFile, "%d\n", inttolog );
    fclose( pFile );
    return;
}


int main ( void )
{

    //bool done = false;

    WidgetApplication *MyApp = new WidgetApplication();
    MyApp->setuniformbackgroundcolor(100, 100, 100);
    //MyApp->setbackgroundpicture( (char*) "/documents/Widget/Wallpapers/001.bmp.tns" );


    DesktopWidget *desktop1 = new DesktopWidget( (char*) "First Desktop", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, nullptr );

    WindowWidget *window = new WindowWidget( (char*) "GUI Toolkit for nSpire rev 0.6 Demo", 45, 45, 240, 170, desktop1 );
    window->setminimaldimensions( 90, 75 );

    MenuBarWidget *barmenu0 = new MenuBarWidget( (char*) "Main Menu", 1,1,1,1, window );
    MenuItemWidget *mainmenufile0 = new MenuItemWidget( (char*) "File", 1,1,1,1, barmenu0 );
    MenuItemWidget *mainmenuedit0 = new MenuItemWidget( (char*) "Edit", 1,1,1,1, barmenu0 );
    MenuItemWidget *mainmenuView0 = new MenuItemWidget( (char*) "View", 1,1,1,1, barmenu0 );
    MenuItemWidget *mainmenuSearch0 = new MenuItemWidget( (char*) "Search", 1,1,1,1, barmenu0 );
    MenuItemWidget *mainmenuProject0 = new MenuItemWidget( (char*) "Project", 1,1,1,1, barmenu0 );

/*
    IconBarWidget *baricon0 = new IconBarWidget( (char*) "M", 1,1,1,1, window );
    IconItemWidget *iconfile0 = new IconItemWidget( (char*) "F", 1,1,1,1, baricon0 );
    IconItemWidget *iconedit0 = new IconItemWidget( (char*) "E", 1,1,1,1, baricon0 );
    IconItemWidget *IconView0 = new IconItemWidget( (char*) "V", 1,1,1,1, baricon0 );
    IconItemWidget *IconSearch0 = new IconItemWidget( (char*) "S", 1,1,1,1, baricon0 );
    IconItemWidget *IconProject0 = new IconItemWidget( (char*) "P", 1,1,1,1, baricon0 );
*/


    ContainerVWidget *containervert = new ContainerVWidget( (char*) "container", 1, 1, 1, 1, window );


    LabelWidget *label1 = new LabelWidget( (char*) "Please pick a theme for the Toolkit : ", 1, 1, 1, 1, containervert );
    label1->setalignment( left );

    // this is the new DropBow Widget
    DropBoxWidget *mydropbox = new DropBoxWidget( (char*) "Test Drop", 1, 1, 1, 1, containervert );


    LabelWidget *label2 = new LabelWidget( (char*) "This is an InputBox", 1, 1, 1, 1, containervert );
    label2->setalignment( left );

    InputWidget *input = new InputWidget( (char*) "I am an Inputbox", 1, 1, 1, 1, containervert );
    input->setcontent( (char *) "Please enter something here !!!" );

    LabelWidget *label3 = new LabelWidget( (char*) "Some Radio/Checkbox examples", 1, 1, 1, 1, containervert );
    label3->setalignment( left );

    CheckBoxWidget *check = new CheckBoxWidget( (char*) "I am a CheckBox", 1, 1, 1, 1, containervert );
    RadioControlWidget *radio = new RadioControlWidget( (char*) "I am a RadioControl", 1, 1, 1, 1, containervert );


/*
    LabelWidget *label4 = new LabelWidget( (char*) "ProgressBars (use + and - keys)", 1, 1, 1, 1, containervert );
    label4->setalignment( left );

    ContainerHWidget *contH5 = new ContainerHWidget( (char*) "container", 1, 1, 1, 1, containervert );


    ProgressBarWidget *bar = new ProgressBarWidget( (char*) "ProgressBar", 1, 1, 1, 1, contH5 );
    bar->setstyle( Continuous );
    bar->setprintvalue( true );

    ProgressBarWidget *bars = new ProgressBarWidget( (char*) "ProgressBar", 1, 1, 1, 1, contH5 );
    bars->setstyle( Bricks );
    bars->setnumberbricks( 10 );
    bars->setprintvalue( true );
*/

    ContainerHWidget *containerH = new ContainerHWidget( (char*) "containerH", 1, 1, 1, 1, containervert );

    SpacerWidget *spacer1H = new SpacerWidget( (char*) "Spacer1", 1, 1, 1, 1, containerH );
    ButtonWidget *buttonQuit = new ButtonWidget( (char*) "Quit !!", 1, 1, 1, 1, containerH );
    SpacerWidget *spacer2H = new SpacerWidget( (char*) "Spacer2", 1, 1, 1, 1, containerH );

    // We ask for an automatic positioning of the widgets in the grid
    // Note : this will fully override the dimensions given to the Widgets manually
    window->adjust();



    //-----------------------

    MenuBarWidget *bardesk = new MenuBarWidget( (char*) "Main Menu", 1,1,1,1, desktop1 );

    MenuItemWidget *mainmenufile = new MenuItemWidget( (char*) "File", 1,1,1,1, bardesk );
    MenuItemWidget *mainmenuedit = new MenuItemWidget( (char*) "Edit", 1,1,1,1, bardesk );
    MenuItemWidget *mainmenuView = new MenuItemWidget( (char*) "View", 1,1,1,1, bardesk );
    MenuItemWidget *mainmenuSearch = new MenuItemWidget( (char*) "Search", 1,1,1,1, bardesk );
    MenuItemWidget *mainmenuProject = new MenuItemWidget( (char*) "Project", 1,1,1,1, bardesk );

        MenuPaneWidget *paneFile = new MenuPaneWidget( (char*) "File", 1,1,1,1, mainmenufile );
        paneFile->setinvisible();
        MenuItemWidget *FileOpen = new MenuItemWidget( (char*) "Open ...", 1,1,1,1, paneFile );
        MenuItemWidget *FileSave = new MenuItemWidget( (char*) "Save", 1,1,1,1, paneFile );
        MenuItemWidget *FileSaveAs = new MenuItemWidget( (char*) "Save As ...", 1,1,1,1, paneFile );
        MenuItemWidget *FilePrint = new MenuItemWidget( (char*) "Print ...", 1,1,1,1, paneFile );
        MenuItemWidget *FileClose = new MenuItemWidget( (char*) "Close", 1,1,1,1, paneFile );

        MenuPaneWidget *paneEdit = new MenuPaneWidget( (char*) "Edit", 1,1,1,1, mainmenuedit );
        paneEdit->setinvisible();
        MenuItemWidget *EditUndo = new MenuItemWidget( (char*) "Undo", 1,1,1,1, paneEdit );
        MenuItemWidget *EditRedo = new MenuItemWidget( (char*) "Redo", 1,1,1,1, paneEdit );
        MenuItemWidget *EditCopy = new MenuItemWidget( (char*) "Copy", 1,1,1,1, paneEdit );
        MenuItemWidget *EditCut = new MenuItemWidget( (char*) "Cut", 1,1,1,1, paneEdit );
        MenuItemWidget *EditPaste = new MenuItemWidget( (char*) "Paste", 1,1,1,1, paneEdit );

        MenuPaneWidget *paneView = new MenuPaneWidget( (char*) "View", 1,1,1,1, mainmenuView );
        paneView->setinvisible();
        MenuItemWidget *ViewZoomPlus = new MenuItemWidget( (char*) "Zoom +", 1,1,1,1, paneView );
        MenuItemWidget *ViewZoomMinus = new MenuItemWidget( (char*) "Zoom -", 1,1,1,1, paneView );
        MenuItemWidget *ViewZoomSelect = new MenuItemWidget( (char*) "Select", 1,1,1,1, paneView );
        MenuItemWidget *ViewZoomFit = new MenuItemWidget( (char*) "Fit All", 1,1,1,1, paneView );
        MenuItemWidget *ViewZomeMax = new MenuItemWidget( (char*) "Zoom Max", 1,1,1,1, paneView );
        MenuItemWidget *ViewZomeMin = new MenuItemWidget( (char*) "Zoom Min", 1,1,1,1, paneView );

            MenuPaneWidget *paneZoomSelect = new MenuPaneWidget( (char*) "Zoom Select", 1,1,1,1, ViewZoomSelect );
            paneZoomSelect->setinvisible();
            MenuItemWidget *ViewZoomSelect10 = new MenuItemWidget( (char*) "10%", 1,1,1,1, paneZoomSelect );
            MenuItemWidget *ViewZoomSelect25 = new MenuItemWidget( (char*) "25%", 1,1,1,1, paneZoomSelect );
            MenuItemWidget *ViewZoomSelect50 = new MenuItemWidget( (char*) "50%", 1,1,1,1, paneZoomSelect );
            MenuItemWidget *ViewZoomSelect75 = new MenuItemWidget( (char*) "75%", 1,1,1,1, paneZoomSelect );
            MenuItemWidget *ViewZoomSelect100 = new MenuItemWidget( (char*) "100%", 1,1,1,1, paneZoomSelect );
            MenuItemWidget *ViewZoomSelect150 = new MenuItemWidget( (char*) "150%", 1,1,1,1, paneZoomSelect );

        MenuPaneWidget *paneSearch = new MenuPaneWidget( (char*) "Search", 1,1,1,1, mainmenuSearch );
        paneSearch->setinvisible();
        MenuItemWidget *SearchFindHere = new MenuItemWidget( (char*) "Find Here ...", 1,1,1,1, paneSearch );
        MenuItemWidget *SearchFindAll = new MenuItemWidget( (char*) "Find All Files ...", 1,1,1,1, paneSearch );
        MenuItemWidget *SearchReplace = new MenuItemWidget( (char*) "Replace ...", 1,1,1,1, paneSearch );


    IconBarWidget *baricon1 = new IconBarWidget( (char*) "M", 1,1,1,1, desktop1 );

    IconItemWidget *iconfile1 = new IconItemWidget( (char*) "F", 1,1,1,1, baricon1 );
    iconfile1->assigniconenable( (char*) "/documents/Widget/Icons/Folder.bmp.tns" );
    iconfile1->assignicondisable( (char*) "/documents/Widget/Icons/gr_Folder.bmp.tns" );
    iconfile1->disable();

/*
    IconItemWidget *iconedit1 = new IconItemWidget( (char*) "E", 1,1,1,1, baricon1 );
    iconedit1->assigniconenable( (char*) "/documents/Widget/Icons/Copy.bmp.tns" );
    iconedit1->assignicondisable( (char*) "/documents/Widget/Icons/gr_Copy.bmp.tns" );
    iconedit1->disable();
    IconItemWidget *IconView1 = new IconItemWidget( (char*) "V", 1,1,1,1, baricon1 );
    IconView1->assigniconenable( (char*) "/documents/Widget/Icons/Pie chart.bmp.tns" );
    IconView1->assignicondisable( (char*) "/documents/Widget/Icons/gr_Pie chart.bmp.tns" );
    IconView1->disable();
    IconItemWidget *IconSearch1 = new IconItemWidget( (char*) "S", 1,1,1,1, baricon1 );

    IconItemWidget *IconProject1 = new IconItemWidget( (char*) "P", 1,1,1,1, baricon1 );
*/

    desktop1->adjust();



    //----------------------


    WindowWidget *window2 = new WindowWidget( (char*) "Test Menu", 75, 45, 200, 100, desktop1 );
    window2->setminimaldimensions( 90, 75 );

    MenuBarWidget *bardesk2 = new MenuBarWidget( (char*) "Main Menu",1,1,1,1, window2 );

    MenuItemWidget *mainmenufile2 = new MenuItemWidget( (char*) "File", 1,1,1,1, bardesk2 );
    MenuItemWidget *mainmenuedit2 = new MenuItemWidget( (char*) "Edit", 1,1,1,1, bardesk2 );
    MenuItemWidget *mainmenuView2 = new MenuItemWidget( (char*) "View", 1,1,1,1, bardesk2 );
    MenuItemWidget *mainmenuSearch2 = new MenuItemWidget( (char*) "Search", 1,1,1,1, bardesk2 );

        MenuPaneWidget *paneFile2 = new MenuPaneWidget( (char*) "File", 1,1,1,1, mainmenufile2 );
        paneFile2->setinvisible();
        MenuItemWidget *FileOpen2 = new MenuItemWidget( (char*) "Open ...", 1,1,1,1, paneFile2 );
        MenuItemWidget *FileSave2 = new MenuItemWidget( (char*) "Save", 1,1,1,1, paneFile2 );
        MenuItemWidget *FileSaveAs2 = new MenuItemWidget( (char*) "Save As ...", 1,1,1,1, paneFile2 );
        MenuItemWidget *FilePrint2 = new MenuItemWidget( (char*) "Print ...", 1,1,1,1, paneFile2 );
        MenuItemWidget *FileClose2 = new MenuItemWidget( (char*) "Close", 1,1,1,1, paneFile2 );

        MenuPaneWidget *paneEdit2 = new MenuPaneWidget( (char*) "Edit", 1,1,1,1, mainmenuedit2 );
        paneEdit2->setinvisible();
        MenuItemWidget *EditUndo2 = new MenuItemWidget( (char*) "Undo", 1,1,1,1, paneEdit2 );
        MenuItemWidget *EditRedo2 = new MenuItemWidget( (char*) "Redo", 1,1,1,1, paneEdit2 );
        MenuItemWidget *EditCopy2 = new MenuItemWidget( (char*) "Copy", 1,1,1,1, paneEdit2 );
        MenuItemWidget *EditCut2 = new MenuItemWidget( (char*) "Cut", 1,1,1,1, paneEdit2 );
        MenuItemWidget *EditPaste2 = new MenuItemWidget( (char*) "Paste", 1,1,1,1, paneEdit2 );

        MenuPaneWidget *paneView2 = new MenuPaneWidget( (char*) "View", 1,1,1,1, mainmenuView2 );
        paneView2->setinvisible();
        MenuItemWidget *ViewZoomPlus2 = new MenuItemWidget( (char*) "Zoom +", 1,1,1,1, paneView2 );
        MenuItemWidget *ViewZoomMinus2 = new MenuItemWidget( (char*) "Zoom -", 1,1,1,1, paneView2 );
        MenuItemWidget *ViewZoomSelect2 = new MenuItemWidget( (char*) "Select", 1,1,1,1, paneView2 );
        MenuItemWidget *ViewZoomFit2 = new MenuItemWidget( (char*) "Fit All", 1,1,1,1, paneView2 );
        MenuItemWidget *ViewZomeMax2 = new MenuItemWidget( (char*) "Zoom Max", 1,1,1,1, paneView2 );
        MenuItemWidget *ViewZomeMin2 = new MenuItemWidget( (char*) "Zoom Min", 1,1,1,1, paneView2 );

            MenuPaneWidget *paneZoomSelect2 = new MenuPaneWidget( (char*) "Zoom Select", 1,1,1,1, ViewZoomSelect2 );
            paneZoomSelect2->setinvisible();
            MenuItemWidget *ViewZoomSelect102 = new MenuItemWidget( (char*) "10%", 1,1,1,1, paneZoomSelect2 );
            MenuItemWidget *ViewZoomSelect252 = new MenuItemWidget( (char*) "25%", 1,1,1,1, paneZoomSelect2 );
            MenuItemWidget *ViewZoomSelect502 = new MenuItemWidget( (char*) "50%", 1,1,1,1, paneZoomSelect2 );
            MenuItemWidget *ViewZoomSelect752 = new MenuItemWidget( (char*) "75%", 1,1,1,1, paneZoomSelect2 );
            MenuItemWidget *ViewZoomSelect1002 = new MenuItemWidget( (char*) "100%", 1,1,1,1, paneZoomSelect2 );
            MenuItemWidget *ViewZoomSelect1502 = new MenuItemWidget( (char*) "150%", 1,1,1,1, paneZoomSelect2 );

        MenuPaneWidget *paneSearch2 = new MenuPaneWidget( (char*) "Search", 1,1,1,1, mainmenuSearch2 );
        paneSearch2->setinvisible();
        MenuItemWidget *SearchFindHere2 = new MenuItemWidget( (char*) "Find Here ...", 1,1,1,1, paneSearch2 );
        MenuItemWidget *SearchFindAll2 = new MenuItemWidget( (char*) "Find All Files ...", 1,1,1,1, paneSearch2 );
        MenuItemWidget *SearchReplace2 = new MenuItemWidget( (char*) "Replace ...", 1,1,1,1, paneSearch2 );


    window2->adjust();



    //----------------------

/*
    WindowWidget *window3 = new WindowWidget( (char*) "Test Menu", 45, 75, 150, 80, desktop1 );
    window3->setminimaldimensions( 90, 75 );


    IconBarWidget *baricon3 = new IconBarWidget( (char*) "M", 1,1,1,1, window3 );
    IconItemWidget *iconfile3 = new IconItemWidget( (char*) "F", 1,1,1,1, baricon3 );
    iconfile3->assigniconenable( (char*) "/documents/Widget/Icons/Folder.bmp.tns" );
    iconfile3->assignicondisable( (char*) "/documents/Widget/Icons/gr_Folder.bmp.tns" );
    IconItemWidget *iconedit3 = new IconItemWidget( (char*) "E", 1,1,1,1, baricon3 );
    iconedit3->assigniconenable( (char*) "/documents/Widget/Icons/Copy.bmp.tns" );
    iconedit3->assignicondisable( (char*) "/documents/Widget/Icons/gr_Copy.bmp.tns" );
    IconItemWidget *IconView3 = new IconItemWidget( (char*) "V", 1,1,1,1, baricon3 );
    IconView3->assigniconenable( (char*) "/documents/Widget/Icons/Pie chart.bmp.tns" );
    IconView3->assignicondisable( (char*) "/documents/Widget/Icons/gr_Pie chart.bmp.tns" );
    IconItemWidget *IconSearch3 = new IconItemWidget( (char*) "S", 1,1,1,1, baricon3 );
    IconSearch3->assigniconenable( (char*) "/documents/Widget/Icons/Search.bmp.tns" );
    IconSearch3->assignicondisable( (char*) "/documents/Widget/Icons/gr_Search.bmp.tns" );
    IconItemWidget *IconProject3 = new IconItemWidget( (char*) "P", 1,1,1,1, baricon3 );
    IconProject3->assigniconenable( (char*) "/documents/Widget/Icons/Brief-case.bmp.tns" );
    IconProject3->assignicondisable( (char*) "/documents/Widget/Icons/gr_Brief-case.bmp.tns" );
    window3->adjust();
*/

    //window2->setinvisible();
    //window3->setinvisible();

    //------------------------------

    MyApp->addchild( desktop1 );

    /*
    MyApp->addchild( bardesk );
    MyApp->addchild( window );
    MyApp->addchild( window2 );
    */

    // We fill the list of the dropbox with items to be selectable by the user
    mydropbox->additem( (char*) "Default GUI Toolkit Theme" );
    mydropbox->additem( (char*) "Bright GUI Toolkit Theme" );
    mydropbox->additem( (char*) "Dark GUI Toolkit Theme" );
    mydropbox->additem( (char*) "Hyrule GUI Toolkit Theme" );
    mydropbox->additem( (char*) "Dummy Value - Do Nothing" );
    mydropbox->additem( (char*) "Dummy Value - Do Nothing" );;
    mydropbox->additem( (char*) "Dummy Value - Do Nothing" );
    mydropbox->additem( (char*) "Dummy Value - Do Nothing" );
    mydropbox->additem( (char*) "Dummy Value - Do Nothing" );
    mydropbox->additem( (char*) "Dummy Value - Do Nothing" );
    mydropbox->additem( (char*) "Dummy Value - Do Nothing" );
    mydropbox->additem( (char*) "Dummy Value - Do Nothing" );
    mydropbox->additem( (char*) "Dummy Value - Do Nothing" );
    mydropbox->additem( (char*) "Dummy Value - Do Nothing" );
    mydropbox->additem( (char*) "Dummy Value - Do Nothing" );
    mydropbox->additem( (char*) "Dummy Value - Do Nothing" );

    // We need to init the theme engine, by default, this is not done at startup to save memory
    MyApp->initthemeengine();
    // We apply the default theme while using theme (this is for safe use and avoid any risk of crash)
    MyApp->setdefaulttheme();

    KeyboardTask *keyboard = MyApp->getkeyboardhandler();

    // We render the app for the first time so what we can see what's happening on the screen
    MyApp->render();

    //desktop1->DEBUG_draw_widget_tree_structure( 1, "/documents/Widget/Structure.txt.tns" );





    while (!MyApp->AskForClose)
    {


        MyApp->logic();


        // Check if the dropbox has been updated by the user and if there is actually something selected (-1 means no selection yet
        if (mydropbox->isupdated() && (mydropbox->getselected()!=-1))
        {
            if (mydropbox->getselected() == 0)
            {
                // We reset the theme to default
                MyApp->setdefaulttheme();
            }
            if (mydropbox->getselected() == 1)
            {
                // We load a theme file and aply it on-the-fly
                // the theme NrmClr.CFG.tns is the default theme
                MyApp->loadtheme( (char*) "/documents/widget/Themes/NrmClr.CFG.tns" );
            }
            if (mydropbox->getselected() == 2)
            {
                // We load a theme file and aply it on-the-fly
                // the theme DrkClr.CFG.tns is the dark theme
                MyApp->loadtheme( (char*) "/documents/widget/Themes/DrkClr.CFG.tns" );
            }
            if (mydropbox->getselected() == 3)
            {
                // We load a theme file and aply it on-the-fly
                // the theme Hyrule.CFG.tns is the theme used is the LinkSDL example (put in a theme file)
                MyApp->loadtheme( (char*) "/documents/widget/Themes/Hyrule.CFG.tns" );
            }
        }

        // As usual, Quit is pressed or the magic keyboard shortcut is activated (CTRL+ESC)
        //if ((keyboard->kbCTRL && keyboard->kbESC) || buttonQuit->ispressed()) done = true;


        if (keyboard->kb7)
        {
            iconfile1->disable();
        }

        if (keyboard->kb8)
        {
            iconfile1->enable();
        }

/*
        if (keyboard->kbPLUS)
        {
            float percentage = bar->getcurrentpercentage();
            bar->setcurrentpercentage( percentage + 1.0 );
            bars->setcurrentpercentage( percentage + 1.0 );
        }


        if (keyboard->kbMINUS)
        {
            float percentage = bar->getcurrentpercentage();
            bar->setcurrentpercentage( percentage - 1.0 );
            bars->setcurrentpercentage( percentage - 1.0 );
        }
*/

    }

    return 0;
}


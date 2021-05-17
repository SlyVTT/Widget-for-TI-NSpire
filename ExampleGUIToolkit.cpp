#include "Toolkit/GUIToolkit.h"



extern void Debug( char* strtolog )
{
    FILE *pFile;
    pFile = fopen( "/documents/Widget/Logger.txt.tns", "a" );
    if (pFile==NULL)
    {
        return;
    }
    fprintf( pFile, "%s\n", strtolog );
    fclose( pFile );
    return;
}

extern void DebugINT( int inttolog )
{
    FILE *pFile;
    pFile = fopen( "/documents/Widget/Logger.txt.tns", "a" );
    if (pFile==NULL)
    {
        return;
    }
    fprintf( pFile, "%d\n", inttolog );
    fclose( pFile );
    return;
}


int main ( void )
{

    WidgetApplication *MyApp = new WidgetApplication();
    //MyApp->setuniformbackgroundcolor(100, 100, 100);
    MyApp->setbackgroundpicture(  "/documents/Widget/Wallpapers/003.bmp.tns" );


    DesktopWidget *desktop = new DesktopWidget( "First Desktop", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, nullptr );
    //-----------------------
        MenuBarWidget *bardesk = new MenuBarWidget(  "Main Menu", 1,1,1,1, desktop );
            MenuItemWidget *mainmenufile = new MenuItemWidget(  "File", 1,1,1,1, bardesk );
                MenuPaneWidget *paneFile = new MenuPaneWidget(  "File", 1,1,1,1, mainmenufile );
                    MenuItemWidget *FileOpen = new MenuItemWidget(  "Open ...", 1,1,1,1, paneFile );
                    MenuItemWidget *FileSave = new MenuItemWidget(  "Save", 1,1,1,1, paneFile );
                    MenuItemWidget *FileSaveAs = new MenuItemWidget(  "Save As ...", 1,1,1,1, paneFile );
                    MenuItemWidget *FilePrint = new MenuItemWidget(  "Print ...", 1,1,1,1, paneFile );
                    MenuItemWidget *FileClose = new MenuItemWidget(  "Close", 1,1,1,1, paneFile );
            MenuItemWidget *mainmenuedit = new MenuItemWidget(  "Edit", 1,1,1,1, bardesk );
                MenuPaneWidget *paneEdit = new MenuPaneWidget(  "Edit", 1,1,1,1, mainmenuedit );
                    MenuItemWidget *EditUndo = new MenuItemWidget(  "Undo", 1,1,1,1, paneEdit );
                    MenuItemWidget *EditRedo = new MenuItemWidget(  "Redo", 1,1,1,1, paneEdit );
                    MenuItemWidget *EditCopy = new MenuItemWidget(  "Copy", 1,1,1,1, paneEdit );
                    MenuItemWidget *EditCut = new MenuItemWidget(  "Cut", 1,1,1,1, paneEdit );
                    MenuItemWidget *EditPaste = new MenuItemWidget(  "Paste", 1,1,1,1, paneEdit );
            MenuItemWidget *mainmenuView = new MenuItemWidget(  "View", 1,1,1,1, bardesk );
                MenuPaneWidget *paneView = new MenuPaneWidget(  "View", 1,1,1,1, mainmenuView );
                    MenuItemWidget *ViewZoomPlus = new MenuItemWidget(  "Zoom +", 1,1,1,1, paneView );
                    MenuItemWidget *ViewZoomMinus = new MenuItemWidget(  "Zoom -", 1,1,1,1, paneView );
                    MenuItemWidget *ViewZoomSelect = new MenuItemWidget(  "Select", 1,1,1,1, paneView );
                        MenuPaneWidget *paneZoomSelect = new MenuPaneWidget(  "Zoom Select", 1,1,1,1, ViewZoomSelect );
                            MenuItemWidget *ViewZoomSelect10 = new MenuItemWidget(  "10%", 1,1,1,1, paneZoomSelect );
                            MenuItemWidget *ViewZoomSelect25 = new MenuItemWidget(  "25%", 1,1,1,1, paneZoomSelect );
                            MenuItemWidget *ViewZoomSelect50 = new MenuItemWidget(  "50%", 1,1,1,1, paneZoomSelect );
                            MenuItemWidget *ViewZoomSelect75 = new MenuItemWidget(  "75%", 1,1,1,1, paneZoomSelect );
                            MenuItemWidget *ViewZoomSelect100 = new MenuItemWidget(  "100%", 1,1,1,1, paneZoomSelect );
                            MenuItemWidget *ViewZoomSelect150 = new MenuItemWidget(  "150%", 1,1,1,1, paneZoomSelect );
                    MenuItemWidget *ViewZoomFit = new MenuItemWidget(  "Fit All", 1,1,1,1, paneView );
                    MenuItemWidget *ViewZomeMax = new MenuItemWidget(  "Zoom Max", 1,1,1,1, paneView );
                    MenuItemWidget *ViewZomeMin = new MenuItemWidget(  "Zoom Min", 1,1,1,1, paneView );
            MenuItemWidget *mainmenuSearch = new MenuItemWidget(  "Search", 1,1,1,1, bardesk );
                MenuPaneWidget *paneSearch = new MenuPaneWidget(  "Search", 1,1,1,1, mainmenuSearch );
                MenuItemWidget *SearchFindHere = new MenuItemWidget(  "Find Here ...", 1,1,1,1, paneSearch );
                MenuItemWidget *SearchFindAll = new MenuItemWidget(  "Find All Files ...", 1,1,1,1, paneSearch );
                MenuItemWidget *SearchReplace = new MenuItemWidget(  "Replace ...", 1,1,1,1, paneSearch );
            MenuItemWidget *mainmenuProject = new MenuItemWidget(  "Project", 1,1,1,1, bardesk );


        IconBarWidget *baricon = new IconBarWidget(  "I am the main Bar Icon", 1,1,1,1, desktop );
            IconItemWidget *iconfile = new IconItemWidget(  "F", 1,1,1,1, baricon );
                iconfile->assigniconenable(  "/documents/Widget/Icons/Folder.bmp.tns" );
                iconfile->assignicondisable(  "/documents/Widget/Icons/gr_Folder.bmp.tns" );
            IconItemWidget *iconedit = new IconItemWidget(  "E", 1,1,1,1, baricon );
                iconedit->assigniconenable(  "/documents/Widget/Icons/Copy.bmp.tns" );
                iconedit->assignicondisable(  "/documents/Widget/Icons/gr_Copy.bmp.tns" );
            IconItemWidget *iconview = new IconItemWidget(  "V", 1,1,1,1, baricon );
                iconview->assigniconenable(  "/documents/Widget/Icons/Search.bmp.tns" );
                iconview->assignicondisable(  "/documents/Widget/Icons/gr_Search.bmp.tns" );
            IconItemWidget *iconsearch = new IconItemWidget(  "S", 1,1,1,1, baricon );
                iconsearch->assigniconenable(  "/documents/Widget/Icons/Pie chart.bmp.tns" );
                iconsearch->assignicondisable(  "/documents/Widget/Icons/gr_Pie chart.bmp.tns" );
            IconItemWidget *iconproject = new IconItemWidget(  "P", 1,1,1,1, baricon );
                iconproject->assigniconenable(  "/documents/Widget/Icons/Calendar.bmp.tns" );
                iconproject->assignicondisable(  "/documents/Widget/Icons/gr_Calendar.bmp.tns" );

    desktop->adjust();

      //-----------------------

    WindowWidget *window1 = new WindowWidget(  "GUI Toolkit for nSpire rev 0.75 Demo", 45, 35, 240, 190, desktop );
    window1->setminimaldimensions( 90, 75 );

        MenuBarWidget *barwin1 = new MenuBarWidget(  "Main Menu",1,1,1,1, window1 );
            MenuItemWidget *mainmenufile1 = new MenuItemWidget(  "File", 1,1,1,1, barwin1 );
            MenuItemWidget *mainmenuedit1 = new MenuItemWidget(  "Edit", 1,1,1,1, barwin1 );
            MenuItemWidget *mainmenuView1 = new MenuItemWidget(  "View", 1,1,1,1, barwin1 );
            MenuItemWidget *mainmenuSearch1 = new MenuItemWidget(  "Search", 1,1,1,1, barwin1 );
                MenuPaneWidget *paneFile1 = new MenuPaneWidget(  "File", 1,1,1,1, mainmenufile1 );
                    MenuItemWidget *FileOpen1 = new MenuItemWidget(  "Open ...", 1,1,1,1, paneFile1 );
                    MenuItemWidget *FileSave1 = new MenuItemWidget(  "Save", 1,1,1,1, paneFile1 );
                    MenuItemWidget *FileSaveAs1 = new MenuItemWidget(  "Save As ...", 1,1,1,1, paneFile1 );
                    MenuItemWidget *FilePrint1 = new MenuItemWidget(  "Print ...", 1,1,1,1, paneFile1 );
                    MenuItemWidget *FileClose1 = new MenuItemWidget(  "Close", 1,1,1,1, paneFile1 );
                MenuPaneWidget *paneEdit1 = new MenuPaneWidget(  "Edit", 1,1,1,1, mainmenuedit1 );
                    MenuItemWidget *EditUndo1 = new MenuItemWidget(  "Undo", 1,1,1,1, paneEdit1 );
                    MenuItemWidget *EditRedo1 = new MenuItemWidget(  "Redo", 1,1,1,1, paneEdit1 );
                    MenuItemWidget *EditCopy1 = new MenuItemWidget(  "Copy", 1,1,1,1, paneEdit1 );
                    MenuItemWidget *EditCut1 = new MenuItemWidget(  "Cut", 1,1,1,1, paneEdit1 );
                    MenuItemWidget *EditPaste1 = new MenuItemWidget(  "Paste", 1,1,1,1, paneEdit1 );
                MenuPaneWidget *paneView1 = new MenuPaneWidget(  "View", 1,1,1,1, mainmenuView1 );
                    MenuItemWidget *ViewZoomPlus1 = new MenuItemWidget(  "Zoom +", 1,1,1,1, paneView1 );
                    MenuItemWidget *ViewZoomMinus1 = new MenuItemWidget(  "Zoom -", 1,1,1,1, paneView1 );
                    MenuItemWidget *ViewZoomSelect1 = new MenuItemWidget(  "Select", 1,1,1,1, paneView1 );
                    MenuItemWidget *ViewZoomFit1 = new MenuItemWidget(  "Fit All", 1,1,1,1, paneView1 );
                    MenuItemWidget *ViewZomeMax1 = new MenuItemWidget(  "Zoom Max", 1,1,1,1, paneView1 );
                    MenuItemWidget *ViewZomeMin1 = new MenuItemWidget(  "Zoom Min", 1,1,1,1, paneView1 );
                        MenuPaneWidget *paneZoomSelect1 = new MenuPaneWidget(  "Zoom Select", 1,1,1,1, ViewZoomSelect1 );
                            MenuItemWidget *ViewZoomSelect101 = new MenuItemWidget(  "10%", 1,1,1,1, paneZoomSelect1 );
                            MenuItemWidget *ViewZoomSelect251 = new MenuItemWidget(  "25%", 1,1,1,1, paneZoomSelect1 );
                            MenuItemWidget *ViewZoomSelect501 = new MenuItemWidget(  "50%", 1,1,1,1, paneZoomSelect1 );
                            MenuItemWidget *ViewZoomSelect751 = new MenuItemWidget(  "75%", 1,1,1,1, paneZoomSelect1 );
                            MenuItemWidget *ViewZoomSelect1001 = new MenuItemWidget(  "100%", 1,1,1,1, paneZoomSelect1 );
                            MenuItemWidget *ViewZoomSelect1501 = new MenuItemWidget(  "150%", 1,1,1,1, paneZoomSelect1 );
                MenuPaneWidget *paneSearch1 = new MenuPaneWidget(  "Search", 1,1,1,1, mainmenuSearch1 );
                    MenuItemWidget *SearchFindHere1 = new MenuItemWidget(  "Find Here ...", 1,1,1,1, paneSearch1 );
                    MenuItemWidget *SearchFindAll1 = new MenuItemWidget(  "Find All Files ...", 1,1,1,1, paneSearch1 );
                    MenuItemWidget *SearchReplace1 = new MenuItemWidget(  "Replace ...", 1,1,1,1, paneSearch1 );

        IconBarWidget *baricon1 = new IconBarWidget(  "M", 1,1,1,1, window1 );
            IconItemWidget *iconfile1 = new IconItemWidget(  "F", 1,1,1,1, baricon1 );
                iconfile1->assigniconenable(  "/documents/Widget/Icons/Folder.bmp.tns" );
                iconfile1->assignicondisable(  "/documents/Widget/Icons/gr_Folder.bmp.tns" );
            IconItemWidget *iconedit1 = new IconItemWidget(  "E", 1,1,1,1, baricon1 );
                iconedit1->assigniconenable(  "/documents/Widget/Icons/Copy.bmp.tns" );
                iconedit1->assignicondisable(  "/documents/Widget/Icons/gr_Copy.bmp.tns" );
            IconItemWidget *iconview1 = new IconItemWidget(  "V", 1,1,1,1, baricon1 );
                iconview1->assigniconenable(  "/documents/Widget/Icons/Pie chart.bmp.tns" );
                iconview1->assignicondisable(  "/documents/Widget/Icons/gr_Pie chart.bmp.tns" );
            IconItemWidget *iconsearch1 = new IconItemWidget(  "S", 1,1,1,1, baricon1 );
                iconsearch1->assigniconenable(  "/documents/Widget/Icons/Save.bmp.tns" );
                iconsearch1->assignicondisable(  "/documents/Widget/Icons/gr_Save.bmp.tns" );
            IconItemWidget *iconproject1 = new IconItemWidget(  "P", 1,1,1,1, baricon1 );
                iconproject1->assigniconenable(  "/documents/Widget/Icons/Schedule.bmp.tns" );
                iconproject1->assignicondisable(  "/documents/Widget/Icons/gr_Schedule.bmp.tns" );

    ContainerVWidget *containervert = new ContainerVWidget( "container", 1, 1, 1, 1, window1 );

        LabelWidget *label1 = new LabelWidget( "Please pick a theme for the Toolkit : ", 1, 1, 1, 1, containervert );
        label1->setalignment( LabelWidget::left );
        DropBoxWidget *mydropbox = new DropBoxWidget( "Test Drop", 1, 1, 1, 1, containervert );
        LabelWidget *label2 = new LabelWidget(  "This is an InputBox", 1, 1, 1, 1, containervert );
        label2->setalignment( LabelWidget::left );
        InputWidget *input = new InputWidget( "I am an Inputbox", 1, 1, 1, 1, containervert );
        input->setcontent( (char *) "Please enter something here !!!" );
        LabelWidget *label3 = new LabelWidget( "Some Radio/Checkbox examples", 1, 1, 1, 1, containervert );
        label3->setalignment( LabelWidget::left );
        CheckBoxWidget *check = new CheckBoxWidget(  "I am a CheckBox", 1, 1, 1, 1, containervert );
        RadioControlWidget *radio = new RadioControlWidget( "I am a RadioControl", 1, 1, 1, 1, containervert );
        //    LabelWidget *label4 = new LabelWidget(  "ProgressBars (use + and - keys)", 1, 1, 1, 1, containervert );
        //    label4->setalignment( left );
        //    ContainerHWidget *contH5 = new ContainerHWidget(  "container", 1, 1, 1, 1, containervert );
        //    ProgressBarWidget *bar = new ProgressBarWidget(  "ProgressBar", 1, 1, 1, 1, contH5 );
        //    bar->setstyle( Continuous );
        //    bar->setprintvalue( true );
        //    ProgressBarWidget *bars = new ProgressBarWidget(  "ProgressBar", 1, 1, 1, 1, contH5 );
        //    bars->setstyle( Bricks );
        //    bars->setnumberbricks( 10 );
        //    bars->setprintvalue( true );
        ContainerHWidget *containerH = new ContainerHWidget( "containerH", 1, 1, 1, 1, containervert );
        SpacerWidget *spacer1H = new SpacerWidget( "Spacer1", 1, 1, 1, 1, containerH );
        ButtonWidget *buttonQuit = new ButtonWidget( "Quit !!", 1, 1, 1, 1, containerH );
        SpacerWidget *spacer2H = new SpacerWidget( "Spacer2", 1, 1, 1, 1, containerH );
            // We fill the list of the dropbox with items to be selectable by the user
            mydropbox->additem(  "Default GUI Toolkit Theme" );
            mydropbox->additem(  "Bright GUI Toolkit Theme" );
            mydropbox->additem(  "Dark GUI Toolkit Theme" );
            mydropbox->additem(  "Hyrule GUI Toolkit Theme" );
            mydropbox->additem(  "Dummy Value - Do Nothing" );
            mydropbox->additem(  "Dummy Value - Do Nothing" );;
            mydropbox->additem(  "Dummy Value - Do Nothing" );
            mydropbox->additem(  "Dummy Value - Do Nothing" );
            mydropbox->additem(  "Dummy Value - Do Nothing" );
            mydropbox->additem(  "Dummy Value - Do Nothing" );
            mydropbox->additem(  "Dummy Value - Do Nothing" );
            mydropbox->additem(  "Dummy Value - Do Nothing" );
            mydropbox->additem(  "Dummy Value - Do Nothing" );
            mydropbox->additem(  "Dummy Value - Do Nothing" );
            mydropbox->additem(  "Dummy Value - Do Nothing" );
            mydropbox->additem(  "Dummy Value - Do Nothing" );
        // We ask for an automatic positioning of the widgets in the grid
        // Note : this will fully override the dimensions given to the Widgets manually

        window1->adjust();

    //----------------------

    WindowWidget *window2 = new WindowWidget(  "Test Menu & Multiline Box", 15, 35, 280, 200, desktop );
    window2->setminimaldimensions( 90, 75 );
        MenuBarWidget *barwin2 = new MenuBarWidget(  "Main Menu",1,1,1,1, window2 );
            MenuItemWidget *mainmenufile2 = new MenuItemWidget(  "File", 1,1,1,1, barwin2 );
            MenuItemWidget *mainmenuedit2 = new MenuItemWidget(  "Edit", 1,1,1,1, barwin2 );
            MenuItemWidget *mainmenuView2 = new MenuItemWidget(  "View", 1,1,1,1, barwin2 );
            MenuItemWidget *mainmenuSearch2 = new MenuItemWidget(  "Search", 1,1,1,1, barwin2 );
                MenuPaneWidget *paneFile2 = new MenuPaneWidget(  "File", 1,1,1,1, mainmenufile2 );
                    MenuItemWidget *FileOpen2 = new MenuItemWidget(  "Open ...", 1,1,1,1, paneFile2 );
                    MenuItemWidget *FileSave2 = new MenuItemWidget(  "Save", 1,1,1,1, paneFile2 );
                    MenuItemWidget *FileSaveAs2 = new MenuItemWidget(  "Save As ...", 1,1,1,1, paneFile2 );
                    MenuItemWidget *FilePrint2 = new MenuItemWidget(  "Print ...", 1,1,1,1, paneFile2 );
                    MenuItemWidget *FileClose2 = new MenuItemWidget(  "Close", 1,1,1,1, paneFile2 );
                MenuPaneWidget *paneEdit2 = new MenuPaneWidget(  "Edit", 1,1,1,1, mainmenuedit2 );
                    MenuItemWidget *EditUndo2 = new MenuItemWidget(  "Undo", 1,1,1,1, paneEdit2 );
                    MenuItemWidget *EditRedo2 = new MenuItemWidget(  "Redo", 1,1,1,1, paneEdit2 );
                    MenuItemWidget *EditCopy2 = new MenuItemWidget(  "Copy", 1,1,1,1, paneEdit2 );
                    MenuItemWidget *EditCut2 = new MenuItemWidget(  "Cut", 1,1,1,1, paneEdit2 );
                    MenuItemWidget *EditPaste2 = new MenuItemWidget(  "Paste", 1,1,1,1, paneEdit2 );
                MenuPaneWidget *paneView2 = new MenuPaneWidget(  "View", 1,1,1,1, mainmenuView2 );
                    MenuItemWidget *ViewZoomPlus2 = new MenuItemWidget(  "Zoom +", 1,1,1,1, paneView2 );
                    MenuItemWidget *ViewZoomMinus2 = new MenuItemWidget(  "Zoom -", 1,1,1,1, paneView2 );
                    MenuItemWidget *ViewZoomSelect2 = new MenuItemWidget(  "Select", 1,1,1,1, paneView2 );
                    MenuItemWidget *ViewZoomFit2 = new MenuItemWidget(  "Fit All", 1,1,1,1, paneView2 );
                    MenuItemWidget *ViewZomeMax2 = new MenuItemWidget(  "Zoom Max", 1,1,1,1, paneView2 );
                    MenuItemWidget *ViewZomeMin2 = new MenuItemWidget(  "Zoom Min", 1,1,1,1, paneView2 );
                        MenuPaneWidget *paneZoomSelect2 = new MenuPaneWidget(  "Zoom Select", 1,1,1,1, ViewZoomSelect2 );
                            MenuItemWidget *ViewZoomSelect102 = new MenuItemWidget(  "10%", 1,1,1,1, paneZoomSelect2 );
                            MenuItemWidget *ViewZoomSelect252 = new MenuItemWidget(  "25%", 1,1,1,1, paneZoomSelect2 );
                            MenuItemWidget *ViewZoomSelect502 = new MenuItemWidget(  "50%", 1,1,1,1, paneZoomSelect2 );
                            MenuItemWidget *ViewZoomSelect752 = new MenuItemWidget(  "75%", 1,1,1,1, paneZoomSelect2 );
                            MenuItemWidget *ViewZoomSelect1002 = new MenuItemWidget(  "100%", 1,1,1,1, paneZoomSelect2 );
                            MenuItemWidget *ViewZoomSelect1502 = new MenuItemWidget(  "150%", 1,1,1,1, paneZoomSelect2 );
                MenuPaneWidget *paneSearch2 = new MenuPaneWidget(  "Search", 1,1,1,1, mainmenuSearch2 );
                    MenuItemWidget *SearchFindHere2 = new MenuItemWidget(  "Find Here ...", 1,1,1,1, paneSearch2 );
                    MenuItemWidget *SearchFindAll2 = new MenuItemWidget(  "Find All Files ...", 1,1,1,1, paneSearch2 );
                    MenuItemWidget *SearchReplace2 = new MenuItemWidget(  "Replace ...", 1,1,1,1, paneSearch2 );

        IconBarWidget *baricon2 = new IconBarWidget(  "M", 1,1,1,1, window2 );
            IconItemWidget *iconfile2 = new IconItemWidget(  "F", 1,1,1,1, baricon2 );
                iconfile2->assigniconenable(  "/documents/Widget/Icons/Folder.bmp.tns" );
                iconfile2->assignicondisable(  "/documents/Widget/Icons/gr_Folder.bmp.tns" );
            IconItemWidget *iconedit2 = new IconItemWidget(  "E", 1,1,1,1, baricon2 );
                iconedit2->assigniconenable(  "/documents/Widget/Icons/Copy.bmp.tns" );
                iconedit2->assignicondisable(  "/documents/Widget/Icons/gr_Copy.bmp.tns" );
            IconItemWidget *IconView2 = new IconItemWidget(  "V", 1,1,1,1, baricon2 );
                IconView2->assigniconenable(  "/documents/Widget/Icons/Pie chart.bmp.tns" );
                IconView2->assignicondisable(  "/documents/Widget/Icons/gr_Pie chart.bmp.tns" );
            IconItemWidget *IconSearch2 = new IconItemWidget(  "S", 1,1,1,1, baricon2 );
                IconSearch2->assigniconenable(  "/documents/Widget/Icons/Search.bmp.tns" );
                IconSearch2->assignicondisable(  "/documents/Widget/Icons/gr_Search.bmp.tns" );
            IconItemWidget *IconProject2 = new IconItemWidget(  "P", 1,1,1,1, baricon2 );
                IconProject2->assigniconenable(  "/documents/Widget/Icons/Brief-case.bmp.tns" );
                IconProject2->assignicondisable(  "/documents/Widget/Icons/gr_Brief-case.bmp.tns" );

            ContainerVWidget *containervert2 = new ContainerVWidget( " Main container", 1,1,1,1, window2 );

            MultiLineTextBoxWidget *multiline = new MultiLineTextBoxWidget( "This is a multiline box", 1,1,1,1, containervert2 );

    window2->adjust();

    //----------------------

/*
        WindowWidget *window3 = new WindowWidget(  "Test Menu", 45, 75, 150, 80, desktop );
        window3->setminimaldimensions( 90, 75 );
        IconBarWidget *baricon3 = new IconBarWidget(  "M", 1,1,1,1, window3 );
            IconItemWidget *iconfile3 = new IconItemWidget(  "F", 1,1,1,1, baricon3 );
                iconfile3->assigniconenable(  "/documents/Widget/Icons/Folder.bmp.tns" );
                iconfile3->assignicondisable(  "/documents/Widget/Icons/gr_Folder.bmp.tns" );
            IconItemWidget *iconedit3 = new IconItemWidget(  "E", 1,1,1,1, baricon3 );
                iconedit3->assigniconenable(  "/documents/Widget/Icons/Copy.bmp.tns" );
                iconedit3->assignicondisable(  "/documents/Widget/Icons/gr_Copy.bmp.tns" );
            IconItemWidget *IconView3 = new IconItemWidget(  "V", 1,1,1,1, baricon3 );
                IconView3->assigniconenable(  "/documents/Widget/Icons/Pie chart.bmp.tns" );
                IconView3->assignicondisable(  "/documents/Widget/Icons/gr_Pie chart.bmp.tns" );
            IconItemWidget *IconSearch3 = new IconItemWidget(  "S", 1,1,1,1, baricon3 );
                IconSearch3->assigniconenable(  "/documents/Widget/Icons/Search.bmp.tns" );
                IconSearch3->assignicondisable(  "/documents/Widget/Icons/gr_Search.bmp.tns" );
            IconItemWidget *IconProject3 = new IconItemWidget(  "P", 1,1,1,1, baricon3 );
                IconProject3->assigniconenable(  "/documents/Widget/Icons/Brief-case.bmp.tns" );
                IconProject3->assignicondisable(  "/documents/Widget/Icons/gr_Brief-case.bmp.tns" );

        window3->adjust();
*/


       WindowWidget *window4 = new WindowWidget( "Simple Constrained Window", 80, 85, 150, 90, desktop );
        window4->setminimaldimensions( 90, 75 );
            ContainerVWidget *containerVcons = new ContainerVWidget( "container", 1, 1, 1, 1, window4 );
                ButtonWidget *but1 = new ButtonWidget( "Button 10px high", 1, 1, 1, 1, containerVcons );
                    containerVcons->addconstraint( 10, "px" );
                ButtonWidget *but2 = new ButtonWidget( "Button 20px high", 1, 1, 1, 1, containerVcons );
                    containerVcons->addconstraint( 20, "px" );
                ButtonWidget *but3 = new ButtonWidget( "Button 30% of remaining space", 1, 1, 1, 1, containerVcons );
                    containerVcons->addconstraint( 30, "%" );
                ContainerHWidget *containerHcons = new ContainerHWidget( "containerH", 1, 1, 1, 1, containerVcons );
                    containerVcons->addconstraint( 70, "%" );
                        ButtonWidget *but4 = new ButtonWidget( "Button 30% width", 1, 1, 1, 1, containerHcons );
                            containerHcons->addconstraint( 30, "%" );
                        ButtonWidget *but5 = new ButtonWidget( "Button 70% width", 1, 1, 1, 1, containerHcons );
                            containerHcons->addconstraint( 70, "%" );

            window4->adjust();



//------------------------

    WindowWidget *window6 = new WindowWidget( "Test of GraphicContextWidget", 100, 55, 120, 120, desktop );
        window4->setminimaldimensions( 100, 100 );
            ContainerVWidget *containergraphic = new ContainerVWidget( "container", 1, 1, 1, 1, window6 );
                GraphicContextWidget *graphic = new GraphicContextWidget( "Graphic Context", 1, 1, 1, 1, containergraphic );

        window6->adjust();




    SDL_Surface *image = IMG_Load( "/documents/Widget/Wallpapers/001.bmp.tns" );
    graphic->assignsurface( image );


    FileDialogBoxWidget *window5 = new FileDialogBoxWidget( "Save file as ...", 20, 40, 250, 150, desktop );
    window5->setinvisible();


    //------------------------------

    MyApp->addchild( desktop );

    /*
    MyApp->addchild( bardesk );
    MyApp->addchild( window );
    MyApp->addchild( window2 );
    */


    MyApp->initiateall();


    KeyboardTask* keyboard = MyApp->getkeyboardhandler();

    SDL_Surface* screen = MyApp->getscreenhandler();
    FontEngine* font = MyApp->getfonthandler();



    //MyApp->DEBUG_draw_widget_tree_structure( "/documents/Widget/Structure.txt.tns" );


    bool flag1 = true;

    while (!MyApp->AskForClose)
    {


        MyApp->run( 1 );        // 1 as parameter is logic with forced render, if 0 is logic with render whe needed (on key/mouse event)

        font->setcurrentfont( font->widget_text_enable.name );
        font->setmodifiertypo( font->widget_text_enable.typo );
        font->setmodifierunder( font->widget_text_enable.under );
        font->setmodifierstrike( font->widget_text_enable.strike );

        if (keyboard->keyevent) boxRGBA( screen, 280, 18, 285, 23, 0, 255, 0, 255 );
        if (keyboard->keypressevent) boxRGBA( screen, 290, 18, 295, 23, 0, 255, 0, 255 );
        if (keyboard->keyreleaseevent) boxRGBA( screen, 300, 18, 305, 23, 0, 255, 0, 255 );
        if (keyboard->keyevent_arrow) boxRGBA( screen, 310, 18, 315, 23, 0, 255, 0, 255 );

        if (keyboard->kbSHIFT) font->drawcharcenter(screen, 'S', 280, 25, 0, 0, 0, 255);
        if (keyboard->kbCTRL) font->drawcharcenter(screen, 'C', 290, 25, 0, 0, 0, 255);
        if (keyboard->capsonmode) font->drawcharcenter(screen, 'B', 300, 25, 0, 0, 0, 255);

        SDL_Flip( screen );



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
                MyApp->loadtheme(  "/documents/widget/Themes/NrmClr.CFG.tns" );
            }
            if (mydropbox->getselected() == 2)
            {
                // We load a theme file and aply it on-the-fly
                // the theme DrkClr.CFG.tns is the dark theme
                MyApp->loadtheme(  "/documents/widget/Themes/DrkClr.CFG.tns" );
            }
            if (mydropbox->getselected() == 3)
            {
                // We load a theme file and aply it on-the-fly
                // the theme Hyrule.CFG.tns is the theme used is the LinkSDL example (put in a theme file)
                MyApp->loadtheme(  "/documents/widget/Themes/Hyrule.CFG.tns" );
            }
        }


        // As usual, Quit is pressed or the magic keyboard shortcut is activated (CTRL+ESC)
        //if ((keyboard->kbCTRL && keyboard->kbESC) || buttonQuit->ispressed()) done = true;

/*
        if (keyboard->kb7 || iconfile->ispressed())
        {
            iconview->disable();
        }

        if (keyboard->kb8 || iconedit->ispressed())
        {
            iconview->enable();
        }
*/

        if (FileSaveAs->ispressed())
        {
            desktop->putontop(window5->WidgetID);
            window5->setvisible();
        }


        if (FileClose->ispressed())
        {
            MyApp->AskForClose = true;
        }



        if (window5->validated && flag1)
        {
            WindowWidget *temp = new WindowWidget( "Validation box", 80, 85, 150, 90, desktop );
            ContainerVWidget *containerV1 = new ContainerVWidget( "container", 1, 1, 1, 1, temp );
            LabelWidget *lab1 = new LabelWidget( window5->getselectedpath(), 1, 1, 1, 1, containerV1 );
            LabelWidget *lab2 = new LabelWidget( window5->getselectedfilename(), 1, 1, 1, 1, containerV1 );
            LabelWidget *lab3 = new LabelWidget( window5->getselectedfullname(), 1, 1, 1, 1, containerV1 );
            temp->setminimaldimensions( 90, 75 );
            temp->adjust();
            window5->setinvisible();
            flag1=false;
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


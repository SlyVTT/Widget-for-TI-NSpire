#include "Toolkit/GUIToolkit.h"



int main ( void )
{

    WidgetApplication *MyApp = new WidgetApplication();

    DesktopWidget *desktop = new DesktopWidget( "Desktop", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, nullptr );

//-----------------------------------------

    WindowWidget *window = new WindowWidget(  "Simple Text Editor for TI nSpire v1.0", 1, 1, 320, 240, desktop );
    window->maximize();
    window->setminimaldimensions( 320, 240 );    // This prevent resizing of the window

    MenuBarWidget *bardesk = new MenuBarWidget(  "Main Menu", 1,1,1,1, window );
    MenuItemWidget *mainmenufile = new MenuItemWidget(  "File", 1,1,1,1, bardesk );
    MenuPaneWidget *paneFile = new MenuPaneWidget(  "File", 1,1,1,1, mainmenufile );
    MenuItemWidget *FileOpen = new MenuItemWidget(  "Open ...", 1,1,1,1, paneFile );
    MenuItemWidget *FileSave = new MenuItemWidget(  "Save", 1,1,1,1, paneFile );
    MenuItemWidget *FileSaveAs = new MenuItemWidget(  "Save As ...", 1,1,1,1, paneFile );
    SpacerWidget *spacer1 = new SpacerWidget(" ", 1,1,1,1, paneFile );
    MenuItemWidget *FileClose = new MenuItemWidget(  "Close", 1,1,1,1, paneFile );
    MenuItemWidget *mainmenuedit = new MenuItemWidget(  "Edit", 1,1,1,1, bardesk );
    MenuPaneWidget *paneEdit = new MenuPaneWidget(  "Edit", 1,1,1,1, mainmenuedit );
    MenuItemWidget *EditCopy = new MenuItemWidget(  "Copy", 1,1,1,1, paneEdit );
    MenuItemWidget *EditCut = new MenuItemWidget(  "Cut", 1,1,1,1, paneEdit );
    MenuItemWidget *EditPaste = new MenuItemWidget(  "Paste", 1,1,1,1, paneEdit );
    MenuItemWidget *EditErase = new MenuItemWidget(  "Erase", 1,1,1,1, paneEdit );
    MenuItemWidget *mainmenuHelp = new MenuItemWidget(  "Help", 1,1,1,1, bardesk );
    MenuPaneWidget *paneHelp = new MenuPaneWidget(  "Help", 1,1,1,1, mainmenuHelp );
    MenuItemWidget *HelpFile = new MenuItemWidget(  "View Help File ...", 1,1,1,1, paneHelp );
    MenuItemWidget *HelpKeyb = new MenuItemWidget(  "View Keyboard Layout ...", 1,1,1,1, paneHelp );
    MenuItemWidget *HelpAbout = new MenuItemWidget(  "About ...", 1,1,1,1, paneHelp );


    IconBarWidget *baricon = new IconBarWidget(  "I am the main Bar Icon", 1,1,1,1, window );
    IconItemWidget *iconNew = new IconItemWidget(  "N", 1,1,1,1, baricon );
    iconNew->assigniconenable(  "/documents/Widget/Icons/New document.bmp.tns" );
    iconNew->assignicondisable(  "/documents/Widget/Icons/gr_New document.bmp.tns" );

    SpacerWidget *spacer2 = new SpacerWidget(" ", 1,1,1,1, baricon );

    IconItemWidget *iconCopy = new IconItemWidget(  "C", 1,1,1,1, baricon );
    iconCopy->assigniconenable(  "/documents/Widget/Icons/Copy.bmp.tns" );
    iconCopy->assignicondisable(  "/documents/Widget/Icons/gr_Copy.bmp.tns" );
    IconItemWidget *iconCut = new IconItemWidget(  "X", 1,1,1,1, baricon );
    iconCut->assigniconenable(  "/documents/Widget/Icons/Cut.bmp.tns" );
    iconCut->assignicondisable(  "/documents/Widget/Icons/gr_Cut.bmp.tns" );
    IconItemWidget *iconPaste = new IconItemWidget(  "P", 1,1,1,1, baricon );
    iconPaste->assigniconenable(  "/documents/Widget/Icons/Paste.bmp.tns" );
    iconPaste->assignicondisable(  "/documents/Widget/Icons/gr_Paste.bmp.tns" );
    IconItemWidget *iconErase = new IconItemWidget(  "E", 1,1,1,1, baricon );
    iconErase->assigniconenable(  "/documents/Widget/Icons/Erase.bmp.tns" );
    iconErase->assignicondisable(  "/documents/Widget/Icons/gr_Erase.bmp.tns" );


    ContainerVWidget *containervert = new ContainerVWidget( "Main container", 1,1,1,1, window );

    MultiLineRichTextBoxWidget *multiline = new MultiLineRichTextBoxWidget( "The Editor Text Box", 1,1,1,1, containervert );
//       multiline->loadcontentfromfile( "/documents/Widget/manual.hlp.tns" );
//        multiline->setnoneditable();

//       MultiLineTextBoxWidget *multiline2 = new MultiLineTextBoxWidget( "The Editor Text Box", 1,1,1,1, containervert );
//       multiline2->loadcontentfromfile(  "/documents/Widget/longtext.txt.tns" );
//        multiline2->setnoneditable();

    desktop->adjust();
    /*
           SplashScreenWidget *splash = new SplashScreenWidget("Splash", 1, 1, 1, 1, nullptr );
           splash->assignimage( "/documents/Widget/Logos/Logo Simple Text Editor.bmp.tns" );
           desktop->addpopupchild(splash);
           splash->setduration( 1000 );    // splash screen will appear 3000ms = 3 seconds
    */

//--------------------------------------------------------------------------------


//--------------------------------------------------
// WE CREATE THE KEYBOARD LAYOUT HELP BOX

    WindowWidget *keyboardhelpwin = new WindowWidget("Help : Keyboard Layout",5,5, 310, 230, desktop );
        ContainerVWidget *contverthelpkeyb = new ContainerVWidget( "Main container", 1,1,1,1, keyboardhelpwin );
            GraphicContextWidget *keyboardimage = new GraphicContextWidget( "Keyboard image", 1, 1,1,1, contverthelpkeyb);

                SDL_Surface *image = IMG_Load( "/documents/Widget/Logos/KeyboardLayout.bmp.tns" );
                keyboardimage->assignsurface( image );
                keyboardimage->setuserzoomlevel(0.95f);
                contverthelpkeyb->addconstraint(185, "px");

                ContainerHWidget *conthorithelpkeyb = new ContainerHWidget( "Sub container", 1,1,1,1, contverthelpkeyb );
                contverthelpkeyb->addconstraint(100, "%");

                    SpacerWidget *spacerhelpleft = new SpacerWidget( "Spacer left",1,1,1,1,conthorithelpkeyb );
                    conthorithelpkeyb->addconstraint(50, "%");
                    ButtonWidget *OKbuttonhelp = new ButtonWidget( "OK",1,1,1,1, conthorithelpkeyb);
                    conthorithelpkeyb->addconstraint(50, "px");
                    SpacerWidget *spacerhelpright = new SpacerWidget( "Spacer left",1,1,1,1,conthorithelpkeyb );
                    conthorithelpkeyb->addconstraint(50, "%");

    keyboardhelpwin->adjust();
    keyboardhelpwin->setinvisible();
//--------------------------------------------------


//--------------------------------------------------
// WE CREATE THE ABOUT HELP BOX

    WindowWidget *abouthelpwin = new WindowWidget("Help : About ...",5,5, 310, 230, desktop );
        ContainerVWidget *contverthelpabout = new ContainerVWidget( "Main container", 1,1,1,1, abouthelpwin );

/*            ContainerHWidget *aboutsplit = new ContainerHWidget( "Main container", 1,1,1,1, contverthelpabout );
            contverthelpabout->addconstraint(100, "px");

                GraphicContextWidget *aboutimage = new GraphicContextWidget( "Keyboard image", 1, 1,1,1, aboutsplit);
                SDL_Surface *image2 = IMG_Load( "/documents/Widget/Logos/Logo Simple Text Editor.bmp.tns" );
                aboutimage->assignsurface( image2 );
                aboutimage->setuserzoomlevel(0.5f);
                aboutsplit->addconstraint(150, "px");

                MultiLineRichTextBoxWidget *textabout = new MultiLineRichTextBoxWidget("Text About",1,1,1,1, aboutsplit);
                textabout->appendcontent("#1Simple Text Editor#0 v1.0 Proudly coded by #3SlyVTT#0 using the #1GUI Toolkit for TI nSpire#0");
                aboutsplit->addconstraint(100, "%");
*/
            GraphicContextWidget *GUIimage = new GraphicContextWidget( "Keyboard image", 1, 1,1,1, contverthelpabout);
            SDL_Surface *image2 = IMG_Load( "/documents/Widget/Logos/Logo Master White 300.bmp.tns" );
            GUIimage->assignsurface( image2 );
            GUIimage->setuserzoomlevel(1.0f);
            contverthelpabout->addconstraint(115, "px");

            MultiLineTextBoxWidget *textabout = new MultiLineTextBoxWidget("Text About",1,1,1,1, contverthelpabout);
            textabout->appendcontent( "Welcome to the Simple Text Editor v1.0 made \n with the GUI Toolkit for TI nSPire. " );
            textabout->appendcontent( "Copyright SlyVTT (2021). " );
            textabout->appendcontent( "Please visit : \n github.coom/SlyVTT/Widget-for-TI-NSpire ");
            contverthelpabout->addconstraint(70, "px");

            ContainerHWidget *conthorithelpabout = new ContainerHWidget( "Sub container", 1,1,1,1, contverthelpabout );
            contverthelpabout->addconstraint(100, "%");

                SpacerWidget *spacerhelpleft1 = new SpacerWidget( "Spacer left",1,1,1,1,conthorithelpabout );
                conthorithelpabout->addconstraint(50, "%");
                ButtonWidget *OKbuttonabout = new ButtonWidget( "OK",1,1,1,1, conthorithelpabout);
                conthorithelpabout->addconstraint(50, "px");
                SpacerWidget *spacerhelpright1 = new SpacerWidget( "Spacer left",1,1,1,1,conthorithelpabout );
                conthorithelpabout->addconstraint(50, "%");

    abouthelpwin->adjust();
    abouthelpwin->setinvisible();
//--------------------------------------------------


    MyApp->addchild( desktop );

    MyApp->initiateall();


//       splash->start();


    unsigned int imageKeybtoshow = 1;
//        SDL_Surface *image = nullptr;

    while (!MyApp->AskForClose)
    {

        MyApp->run( 1 );

        if (FileClose->ispressed())
        {
            MyApp->AskForClose = true;
        }

        if (EditCopy->ispressed() || iconCopy->ispressed())
        {
            multiline->copyselection();
        }
        if (EditCut->ispressed() || iconCut->ispressed())
        {
            multiline->cutselection();
        }
        if (EditPaste->ispressed() || iconPaste->ispressed())
        {
            multiline->pasteselection();
        }
        if (EditErase->ispressed() || iconErase->ispressed())
        {
            multiline->eraseselection();
        }

        if (iconNew->ispressed())
        {
            multiline->flush();
        }

        if (HelpKeyb->ispressed())
        {
            multiline->appendcontent( "Keyboard Layout Help Menu  pressed \n" );
            MyApp->putontop( keyboardhelpwin );
            keyboardhelpwin->setvisible();
        }

        if (keyboardhelpwin->isvisible() && OKbuttonhelp->ispressed())
        {
            keyboardhelpwin->setinvisible();
        }

        if (HelpAbout->ispressed())
        {
            multiline->appendcontent( "About Help Menu \n" );
            MyApp->putontop( abouthelpwin );
            abouthelpwin->setvisible();
        }

        if (abouthelpwin->isvisible() && OKbuttonabout->ispressed())
        {
            abouthelpwin->setinvisible();
        }

    }

    MyApp->quit();

    //delete MyApp;


     SDL_FreeSurface( image );
     SDL_FreeSurface( image2 );



    return 0;
}



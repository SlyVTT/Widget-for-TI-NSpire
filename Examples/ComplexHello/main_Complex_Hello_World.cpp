#include "Toolkit/GUIToolkit.h" // the main include file for using the toolkit

int main ( int argc, char** argv )
{

    // we create a WidgetApplication instance that will handle all the application logic and render mechanisms
    WidgetApplication *MyApp = new WidgetApplication();

    // An application can contain several Desktops (i.e. screen) fully independant, but at least one should be created.
    DesktopWidget *desktop1 = new DesktopWidget( "First Desktop", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, nullptr );

    // then we create a Window Widget and we link it to the active Desktop
    WindowWidget *window = new WindowWidget( "GUI Toolkit for TI nSpire", 30, 40, 260, 100, desktop1 );

    // We add a vertical grid container into the window
    ContainerVWidget *containerv = new ContainerVWidget( "container", 1, 1, 1, 1, window );

    // we add a Label widget by manual positioning and link it to the Window
    // we set dummy dimensions to demonstrate the automatic positioning features
    LabelWidget *label = new LabelWidget("Hello World !!!", 1, 1, 1, 1, containerv );
    label->setalignment( centered );

     // We add a horizontal grid container below the label where buttons will be added
    ContainerHWidget *containerh = new ContainerHWidget( "container", 1, 1, 1, 1, containerv );

    // We add a button for increasing the size of the window
    ButtonWidget *buttonbigger = new ButtonWidget( "Bigger", 1, 1, 1, 1, containerh );

    // and a Button to quit
    ButtonWidget *buttonquit = new ButtonWidget( "Quit", 1, 1, 1, 1, containerh );

    // We add a button for decreasing the size of the window
    ButtonWidget *buttonsmaller = new ButtonWidget( "Smaller", 1, 1, 1, 1, containerh );

    // the magic is coming from the container that will compute the size of the components
    containerv->adjust();
    containerh->adjust();



    // We link the window to the desktop
    MyApp->addchild( desktop1 );

    // We render the app for the first time so what we can see what's happening on the screen
    MyApp->render();

    // We llop until que button is clicked
    while (!buttonquit->ispressed())
    {
        // if we click to increase tjhe size
        if (buttonbigger->ispressed())
        {
            // we set the size of the window
            window->setdimensions( 10, 10, 300, 200 );
            // and we re-do the magic
            containerv->adjust();
            containerh->adjust();
            // we force the rendering
            MyApp->render();
        }

        // if we click to increase tjhe size
        if (buttonsmaller->ispressed())
        {
            // we set the size of the window
            window->setdimensions( 30, 40, 260, 100 );
            // and we re-do the magic
            containerv->adjust();
            containerh->adjust();
            // we force the rendering
            MyApp->render();
        }

        // we run the application logic (rendiring is managed by the logic loop)
        MyApp->logic();



    }

    // we exit with a success exit code
    return 0;
}

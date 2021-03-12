#include "Toolkit/GUIToolkit.h" // the main include file for using the toolkit

int main ( int argc, char** argv )
{

    // we create a WidgetApplication instance that will handle all the application logic and render mechanisms
    WidgetApplication *MyApp = new WidgetApplication();

    // An application can contain several Desktops (i.e. screen) fully independant, but at least one should be created.
    DesktopWidget *desktop1 = new DesktopWidget( "First Desktop", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, nullptr );

    // then we create a Window Widget and we link it to the active Desktop
    WindowWidget *window = new WindowWidget( "GUI Toolkit for TI nSpire", 30, 40, 260, 100, desktop1 );

    // we add a Label widget by manual positioning and link it to the Window (this is uqing relative coordinates vs the window
    LabelWidget *label = new LabelWidget("Hello World !!!", 0, 20, window->getuseablewidth(), 15, window );
    label->setalignment( centered );

    // and a Button widget by manual positioning and link it to the Window
    ButtonWidget *button = new ButtonWidget( "Click to Quit", window->getuseablewidth()/2 -50, window->getuseableheight() - 40, 100, 20, window );


    // We link the window to the desktop
    MyApp->addchild( desktop1 );

    // We render the app for the first time so what we can see what's happening on the screen
    MyApp->render();

    // We loop until que button is clicked or CTRL+ESC is pressed
    bool done=false;
    while (!button->ispressed() && !done)
    {
        // we run the application logic (rendiring is managed by the logic loop)
        MyApp->logic();

        // this is a bit dirty, will be improved in next revisions
        if (MyApp->keyboard->kbCTRL && MyApp->keyboard->kbESC) done = true;
    }

    // we exit with a success exit code
    return 0;
}

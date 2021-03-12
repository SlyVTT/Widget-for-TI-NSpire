#include  "Toolkit/GUIToolkit.h"


int main ( int argc, char** argv )
{


    WidgetApplication *MyApp = new WidgetApplication();
    MyApp->setuniformbackgroundcolor(0, 155, 255);

    // We create the main window with automatic positioning feature
    WindowWidget *window = new WindowWidget( "This is a more complex Window", 10, 20, 300, 100, nullptr );
    ContainerVWidget *containerv = new ContainerVWidget( "container", 1, 1, 1, 1, window );
    LabelWidget *label = new LabelWidget( "Let's try some interactions ... ", 1, 1, 1, 1, containerv );
    label->setalignment( centered );
    ContainerHWidget *containerh = new ContainerHWidget( "container", 1, 1, 1, 1, containerv );
    ButtonWidget *buttonCreate = new ButtonWidget( "Create window [7]", 1, 1, 1, 1, containerh );
    ContainerHWidget *containerh2 = new ContainerHWidget( "container", 1, 1, 1, 1, containerv );
    ButtonWidget *buttonHide = new ButtonWidget( "Hide window [4]", 1, 1, 1, 1, containerh2 );
    buttonHide->disable();
    ButtonWidget *buttonShow = new ButtonWidget( "Show Window [5]", 1, 1, 1, 1, containerh2 );
    buttonShow->disable();
    ContainerHWidget *containerh3 = new ContainerHWidget( "container", 1, 1, 1, 1, containerv );
    ButtonWidget *buttonDisable = new ButtonWidget( "Disable window [1]", 1, 1, 1, 1, containerh3 );
    buttonDisable->disable();
    ButtonWidget *buttonEnable = new ButtonWidget( "Enable Window [2]", 1, 1, 1, 1, containerh3 );
    buttonEnable->disable();
    ButtonWidget *buttonQuit = new ButtonWidget( "Quit this Application [0]", 1, 1, 1, 1, containerv );
    window->adjust();

    MyApp->addchild( window );

    MyApp->render();

    // We create a WindowWidget point that will be used at child window creation
    WindowWidget *windowchild;

    bool childexist = false;

    bool done = false;

    while (!buttonQuit->ispressed() && !done)
    {

        MyApp->logic();


        if (MyApp->keyboard->kbCTRL && MyApp->keyboard->kbESC) done = true;

        if (MyApp->keyboard->kb0) done = true;

        // When Create button is pressed or key 7 is pressed
        if ((buttonCreate->ispressed() || MyApp->keyboard->kb7) && !childexist)
        {
                // We create all the widgets in the child window and attached everything to MyApp
                windowchild = new WindowWidget( "Child Window", 80, 150, 160, 80, nullptr );
                LabelWidget *label2 = new LabelWidget( "I am a Child Window", 0, 0, windowchild->getuseablewidth(), windowchild->getuseableheight(), windowchild );
                label2->setalignment( centered );
                windowchild->adjust();

                MyApp->addchild( windowchild );

                buttonCreate->disable();
                buttonHide->enable();
                buttonShow->enable();
                buttonDisable->enable();
                buttonEnable->enable();

                childexist = true;
        }

        // When Hide button is pressed or key 4 is pressed
        if ((buttonHide->ispressed() || MyApp->keyboard->kb4) && childexist)
        {
                windowchild->setinvisible();
                buttonHide->disable();
                buttonShow->enable();
        }

        // When Show button is pressed or key 5 is pressed
        if ((buttonShow->ispressed() || MyApp->keyboard->kb5) && childexist)
        {
                windowchild->setvisible();
                buttonHide->enable();
                buttonShow->disable();
        }

        // When Disable button is pressed or key 1 is pressed
        if ((buttonDisable->ispressed() || MyApp->keyboard->kb1) && childexist)
        {
                windowchild->disable();
                buttonDisable->disable();
                buttonEnable->enable();
        }

        // When Enable button is pressed or key 2 is pressed
        if ((buttonEnable->ispressed() || MyApp->keyboard->kb2) && childexist)
        {
                windowchild->enable();
                buttonDisable->enable();
                buttonEnable->disable();
        }

    }

    return 0;
}

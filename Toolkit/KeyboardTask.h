#ifndef KEYBOARDTASK_H
#define KEYBOARDTASK_H

#include <SDL/SDL.h>

/// Example of program using KeyboardTask
///
/// The following simple example demonstrates how to use the KeyboardTask controls.
/// \image html ButtonWidgetExample.jpg
///
/// ### Examples of usage:
/// ~~~~~~~~~~~~~~~~~~~~~~.cpp
/// #include "Toolkit/GUIToolkit.h"
///
/// int main ( int argc, char** argv )
/// {
///     bool done = false;
///
///     WidgetApplication *MyApp = new WidgetApplication();
///     MyApp->setuniformbackgroundcolor(0, 0, 0);
///
///     DesktopWidget *desktop1 = new DesktopWidget( (char*) "First Desktop", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, nullptr );
///
///     WindowWidget *window = new WindowWidget( (char*) "Examples of ButtonWidgets", 20, 30, 250, 160, desktop1 );
///
///     ContainerVWidget *contH = new ContainerVWidget( (char*) "ContainerH", 1, 1, 1, 1, window );
///
///     ButtonWidget *button = new ButtonWidget();          // Simple constructor so we need to assign all the parameters
///
///     // First the label to be written on the button
///     button->setlabel( (char*) "Enabled Button" );
///
///     // then the dimensions (one by one in that case)
///     button->setxpos( 5 );
///     button->setypos( 10 );
///     button->setwidth( 150 );
///     button->setheight( 15 );
///     // note : we can also use the method button->setdimensions( 5, 10, 150, 15 ) instead
///
///     // and finally we assign the parent by adding the button as a child to conH
///     contH->addchild( button );
///
///     // This is a second button with all parameters passed through the constructon
///     ButtonWidget *button2 = new ButtonWidget( (char*) "Disabled Button", 1, 1, 1, 1, contH );
///     // We disable the button by using the inherited method Wigdet::disable()
///     button2->disable();
///
///     // the button to be clicked to quit
///     ButtonWidget *buttonQuit = new ButtonWidget( (char*) "Quit [CTRL]+[ESC]", 1, 1, 1, 1, contH );
///
///     // We ask for an automatic positioning of the widgets in the grid
///     // Note : this will fully override the dimensions given to the Widgets manually
///     window->adjust();
///
///     MyApp->addchild( desktop1 );
///
///     KeyboardTask *keyboard = MyApp->getkeyboardhandler();
///
///     // We render the app for the first time so what we can see what's happening on the screen
///     MyApp->render();
///
///     while (!done)
///     {
///
///         MyApp->logic();
///
///         if ((keyboard->kbCTRL && keyboard->kbESC) || buttonQuit->ispressed()) done = true;
///
///     }
///
///     return 0;
/// }
/// ~~~~~~~~~~~~~~~~~~~~~~



/// KeyboardTask class.
///
/// The class to be used for accessing the keyboard and keys information.
///
/// ### Examples of usage:
/// ~~~~~~~~~~~~~~~~~~~~~~.cpp
/// KeyboardTask* myKeys = new KeyboardTask();        // Simple constructor, will need specific properties assignement later
/// ~~~~~~~~~~~~~~~~~~~~~~
/// ~~~~~~~~~~~~~~~~~~~~~~.cpp
/// WidgetApplication myApp = new WidgetApplication();
/// KeyboardTask* myKeys = myApp->getkeyboardhandler();
/// ~~~~~~~~~~~~~~~~~~~~~~
/// @note WidgetApplication creates a KeyboardTask object at initialisation. It is then better to ask for a direct access to its KeyboardTask by using the WidgetApplication::getkeyboardhandler() method.
/// @see WidgetApplication::getkeyboardhandler()
///
///
/// Direct key status
///
/// Each key is defined by a boolean: *true* is the corresponding key is pressed and *false* overwise
///
/// Keynames are given as follows
/// @image html KeyNamesLayout.jpg
class KeyboardTask
{

public:
    KeyboardTask();
    virtual ~KeyboardTask();
    virtual void logic();

    virtual bool iskeypressed();
    virtual bool iskeyevent( )
    {
        return keyevent;
    };
    virtual bool iskeypressevent( )
    {
        return keypressevent;
    };
    virtual bool iskeyreleaseevent( )
    {
        return keyreleaseevent;
    };
    virtual bool iskeyarrowevent( )
    {
        return keyevent_arrow;
    };

    bool keypressevent = false;
    bool keyreleaseevent = false;
    bool keyevent = false;
    bool keyevent_arrow = false;
    bool capsonmode = false;




    // First adress block
    bool kbRET = false;
    bool kbENTER = false;
    bool kbMINUSPAR = false;
    bool kbSPACE = false;
    bool kbZ = false;
    bool kbY = false;
    bool kb0 = false;
    bool kbQUESTION = false;
    bool kbON = false;

    // Second adress block
    bool kbX = false;
    bool kbW = false;
    bool kbV = false;
    bool kb3 = false;
    bool kbU = false;
    bool kbT = false;
    bool kbS = false;
    bool kb1 = false;
    bool kbPI = false;
    bool kbTRIG = false;
    bool kb10X = false;

    // Third adress block
    bool kbR = false;
    bool kbQ = false;
    bool kbP = false;
    bool kb6 = false;
    bool kbO = false;
    bool kbN = false;
    bool kbM = false;
    bool kb4 = false;
    bool kbEE = false;
    bool kbX2 = false;

    // Fourth adress block
    bool kbL = false;
    bool kbK = false;
    bool kbJ = false;
    bool kb9 = false;
    bool kbI = false;
    bool kbH = false;
    bool kbG = false;
    bool kb7 = false;
    bool kbDIV = false;
    bool kbEX = false;

    // Fifth adress block
    bool kbF = false;
    bool kbE = false;
    bool kbD = false;
    bool kbC = false;
    bool kbB = false;
    bool kbA = false;
    bool kbEQUAL = false;
    bool kbMULTIPLY = false;
    bool kbPOWER = false;

    // Sixth adress block
    bool kbVAR = false;
    bool kbMINUS = false;
    bool kbPARCLOSE = false;
    bool kbDOT = false;
    bool kbPAROPEN = false;
    bool kb5 = false;
    bool kbCATALOG = false;
    bool kbFRAC = false;
    bool kbDEL = false;
    bool kbSCRATCH = false;

    // Seventh adress block
    bool kbFLAG = false;
    bool kbPLUS = false;
    bool kbDOC = false;
    bool kb2 = false;
    bool kbMENU = false;
    bool kb8 = false;
    bool kbESC = false;
    bool kbTAB = false;

    // Eigth adress block
    bool kbSHIFT = false;
    bool kbCTRL = false;
    bool kbCOMMA = false;

    // Keys of the Touchpad
    bool kbUP = false;
    bool kbUPRIGHT = false;
    bool kbRIGHT = false;
    bool kbRIGHTDOWN = false;
    bool kbDOWN = false;
    bool kbDOWNLEFT = false;
    bool kbLEFT = false;
    bool kbLEFTUP = false;


private:
    unsigned short *base;
};

#endif // KEYBOARDTASK_H

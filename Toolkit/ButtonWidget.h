#ifndef BUTTONWIDGET_H
#define BUTTONWIDGET_H

#include "Widget.h"


/// Example of program using ButtonWidget controls
///
/// The following simple example demonstrates how to use the ButtonWidget controls.
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



/// ButtonWidget class.
///
/// The class to be used for using a ButtonWidget control widget.
/// ButtonWidget inherits from Widget class.
/// @see  Widget
///
/// ### Examples of usage:
/// ~~~~~~~~~~~~~~~~~~~~~~.cpp
/// ButtonWidget* myButton = new ButtonWidget();        // Simple constructor, will need specific properties assignement later
/// ~~~~~~~~~~~~~~~~~~~~~~
/// ~~~~~~~~~~~~~~~~~~~~~~.cpp
/// ButtonWidget* myButton = new ButtonWidget( "I am a Button", 10, 50, 100, 15, parent );        // Full constructor
/// ~~~~~~~~~~~~~~~~~~~~~~
class ButtonWidget : public Widget
{
public:

    /// Simple constructor
    ///
    /// Widget properties are set to default, nothing more.
    /// Simple constructor, will need specific properties assignement later.
    /// @param None
    /// @returns Nothing
    /// @see Widget()
    ButtonWidget()
    {
        //widgettype = (char*) "Button";
        strcpy( widgettype, (char*) "Button");
    };


    /// Advanced constructor.
    ///
    /// Widget properties are set with parameters values given at call.
    /// @param l : text string (char*) that will be used as the widget textual content
    /// @param x : position x in pixels relatively to the parent widget usable drawspace
    /// @param y : position y in pixels relatively to the parent widget usable drawspace
    /// @param w : width in pixel of the widget
    /// @param h : height in pixel of the widget
    /// @param p : pointer type to a Widget* to create a link with the parent widget (if any).
    /// @note *p* should be set to *nullptr* if no parent exists
    /// @note *p* can be omitted (i.e. set to *nullptr*) and parent-children link can be created with a call to the Widget::addchild() method of the parent Widget.
    /// @returns Nothing
    /// @see Widget( char*, int, int, int, int, Widget* )
    ButtonWidget( char *l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : Widget( l, x, y, w, h, p )
    {
        //widgettype = (char*) "Button";
        strcpy( widgettype, (char*) "Button");
    };


    /// Object destructor.
    ///
    /// Object destructor, remove all trace of the object and free allocated memory.
    /// @param None
    /// @returns Nothing
    /// @see ~Widget()
    ~ButtonWidget() {};


    /// Is the ButtonWidget pressed ?
    ///
    /// Gives the status of the ButtonWidget (pressed (i.e. clicked) or not).
    /// @param None
    /// @returns Boolean value : *true* if the button is pressed, *false* otherwise
    virtual bool ispressed();


    /// The ButtonWidget logic mechanism
    ///
    /// Method to be launched to drive the the mechanics behind the widget behavior.
    /// @param mouse : pointer to a CursorTask handler object serving at passing the mouse (Touchpad) state and position
    /// @param keyboard : pointer to a KeyboardTask handler object serving at passing the keyboard state
    /// @returns Nothing, but will launch the logic() method of all the Widgets belonging to chidren (vector<Widget*>)
    /// @note This method overrides Widget::logic( CursorTask*, KeyboardTask*)
    /// @note This method is not intended to be used by a direct call from the user, it is normally called through cascaded calls to children->logic() from the WidgetApplication class
    /// @note Direct call can be used when the Widget is used out of the WidgetApplication 'ecosystem', for example in an application that just use few individual widgets (not recommended cause it may need intensive work from the developper to create adequate working conditions).
    /// @warning Before calling the logic method, a mouse handler and a keyboard handler must be instancied and properly updated through their respective logic() methods. This is normally done by using the WidgetApplication class.
    virtual void logic( CursorTask *mouse, KeyboardTask *keyboard ) override;


    /// The ButtonWidget render method
    ///
    /// Method to be launched to draw the widget.
    /// @param screen : pointer to a SDL_Surface object where we would like to draw the widget
    /// @param colors : pointer to a ColorEngine object giving all the color options to be used (theme) for drawing the widget
    /// @param fonts : pointer to a FontEngine object giving all the fonts options to be used (theme) for drawing the widget
    /// @returns Nothing, but will launch the render() method of all the Widgets belonging to chidren (vector<Widget*>)
    /// @note This method overrides Widget::render( SDL_Surface*, ColorEngine*, FontEngine*)
    /// @note This method is not intended to be used by a direct call from the user, it is normally called through cascaded calls to children->render() from the WidgetApplication class.
    /// @note Direct call can be used when the widget is used out of the WidgetApplication 'ecosystem', for example in an application that just use few individual widgets (not recommended cause it may need intensive work from the developper to create adequate working conditions).
    /// @warning Before calling the render method, a SDL_Surface (i.e. a rendering context) as well as a ColorEngine and FontEngine objects must be properly instancied. This is normally done by using the WidgetApplication class.
    virtual void render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts ) override;

protected:

private:

    friend class MiniButtonWidget;

    /// Is the ButtonWidget pressed ?
    ///
    /// Widget properties giving the status of the Button
    /// @note This boolean should not be adressed directly by the user. Status should be obtained by the ButtonWidget::ispressed() method.
    /// @see ButtonWidget::ispressed()
    bool is_pressed = false;


};



#endif // BUTTONWIDGET_H

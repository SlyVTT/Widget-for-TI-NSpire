#ifndef COMMUTERWIDGET_H
#define COMMUTERWIDGET_H

#include "ButtonWidget.h"



/// Example of program using CommuterWidget controls
///
/// The following simple example demonstrates how to use the CommuterWidget controls.
/// \image html CommuterWidgetExample1.jpg
/// \image html CommuterWidgetExample2.jpg
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
///    WindowWidget *window = new WindowWidget( (char*) "Examples of CommuterWidgets", 5, 5, 310, 230, desktop1 );
///    ContainerVWidget *containervert = new ContainerVWidget( (char*) "container", 1, 1, 1, 1, window );
///
///    LabelWidget *labelB = new LabelWidget( (char*) "Examples of CommuterWidget", 1, 1, 1, 1, containervert );
///
///    ContainerHWidget *contH1 = new ContainerHWidget( (char*) "container", 1, 1, 1, 1, containervert );
///    CommuterWidget *com11 = new CommuterWidget( (char*) "St.1 Normal", 1, 1, 1, 1, contH1 );
///    com11->settype( CommuterWidget::style1 );
///    com11->setnormal();
///    CommuterWidget *com12 = new CommuterWidget( (char*) "St.1 Reverse", 1, 1, 1, 1, contH1 );
///    com12->settype( CommuterWidget::style1 );
///    com12->setreversed();
///
///    ContainerHWidget *contH2 = new ContainerHWidget( (char*) "container", 1, 1, 1, 1, containervert );
///    CommuterWidget *com21 = new CommuterWidget( (char*) "St.2 Normal", 1, 1, 1, 1, contH2 );
///    com21->settype( CommuterWidget::style2 );
///    com21->setnormal();
///    CommuterWidget *com22 = new CommuterWidget( (char*) "St.2 Reverse", 1, 1, 1, 1, contH2 );
///    com22->settype( CommuterWidget::style2 );
///    com22->setreversed();
///
///    ContainerHWidget *contH3 = new ContainerHWidget( (char*) "container", 1, 1, 1, 1, containervert );
///    CommuterWidget *com31 = new CommuterWidget( (char*) "St.3 Normal", 1, 1, 1, 1, contH3 );
///    com31->settype( CommuterWidget::style3 );
///    com31->setnormal();
///    CommuterWidget *com32 = new CommuterWidget( (char*) "St.3 Reverse", 1, 1, 1, 1, contH3 );
///    com32->settype( CommuterWidget::style3 );
///    com32->setreversed();
///
///    ContainerHWidget *contH4 = new ContainerHWidget( (char*) "container", 1, 1, 1, 1, containervert );
///    CommuterWidget *com41 = new CommuterWidget( (char*) "St.4 Normal", 1, 1, 1, 1, contH4 );
///    com41->settype( CommuterWidget::style4 );
///    com41->setnormal();
///    CommuterWidget *com42 = new CommuterWidget( (char*) "St.4 Reverse", 1, 1, 1, 1, contH4 );
///    com42->settype( CommuterWidget::style4 );
///    com42->setreversed();
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



/// CommuterWidget class.
///
/// The class to be used for using a CommuterWidget control widget.
/// CommuterWidget inherits from ButtonWidget class.
/// @see  ButtonWidget
///
/// ### Examples of usage:
/// ~~~~~~~~~~~~~~~~~~~~~~.cpp
/// CommuterWidget* myCommuter = new CommuterWidget();        // Simple constructor, will need specific properties assignement later
/// ~~~~~~~~~~~~~~~~~~~~~~
/// ~~~~~~~~~~~~~~~~~~~~~~.cpp
/// CommuterWidget* myCommuter = new CommuterWidget( "I am a CommuterWidget", 10, 50, 100, 15, parent );        // Full constructor
/// ~~~~~~~~~~~~~~~~~~~~~~
class CommuterWidget : public ButtonWidget
{
public:

    /// Simple constructor.
    ///
    /// Widget properties are set to default, nothing more.
    /// Simple constructor, will need specific properties assignement later.
    /// @param None
    /// @returns Nothing
    /// @see ButtonWidget() or Widget()
    CommuterWidget()
    {
        widgettype = (char*) "Commuter";
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
    /// @see ButtonWidget( char*, int, int, int, int, Widget* ) or Widget( char*, int, int, int, int, Widget* )
    CommuterWidget( char *l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : ButtonWidget( l, x, y, w, h, p )
    {
        widgettype = (char*) "Commuter";
    };


    /// Object destructor
    ///
    /// Object destructor, remove all trace of the object and free allocated memory
    /// @param None
    /// @returns Nothing
    /// @see ~Widget()
    virtual ~CommuterWidget() { };


    /// Enumerator for CommuterWidget style.
    ///
    /// Gives the style of CommuterWidget (of the colors of both backgroud and commuter button).
    /// *style1* the commuter background is blank and the button also
    /// *style2* the commuter background is blank and the button is colorized
    /// *style3* the commuter background is blank and the button is colorized in color depending on switch position
    /// *style4* the commuter background and the button are colorized in color depending on switch position
    enum commutertype
    {
        style1 = 0,
        style2 = 1,
        style3 = 2,
        style4 = 3
    };


    /// Invert the CommuterWidget status
    ///
    /// Invert the CommuterWidget status, if unticked --> ticked and if ticked --> unticked
    /// @param None
    /// @returns None
    /// @note It changes the internal property *is_ticked* of the CommuterWidget
    virtual void invert()
    {
        is_ticked = !is_ticked;
    };


    /// Is the CommuterWidget ticked ?
    ///
    /// Gives the status of the CommuterWidget (switched or not).
    /// @param None
    /// @returns Boolean value : *true* if the CommuterWidget is switched, *false* otherwise
    virtual bool isticked( void )
    {
        return is_ticked;
    };


    /// The CommuterWidget logic mechanism
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



    /// The CommuterWidget render method.
    ///
    /// Method to be launched to draw the CommuterWidget.
    /// @param screen : pointer to a SDL_Surface object where we would like to draw the wigdet
    /// @param colors : pointer to a ColorEngine object giving all the color options to be used (theme) for drawing the widget
    /// @param fonts : pointer to a FontEngine object giving all the fonts options to be used (theme) for drawing the widget
    /// @returns Nothing, but will launch the render() method of all the Widgets belonging to chidren (vector<Widget*>)
    /// @note This method overrides Widget::render( SDL_Surface*, ColorEngine*, FontEngine*)
    /// @note This method is not intended to be used by a direct call from the user, it is normally called through cascaded calls to children->render() from the WidgetApplication class.
    /// @note Direct call can be used when the Widget is used out of the WidgetApplication 'ecosystem', for example in an application that just use few individual widgets (not recommended cause it may need intensive work from the developper to create adequate working conditions).
    /// @warning Before calling the render method, a SDL_Surface (i.e. a rendering context) as well as a ColorEngine and FontEngine objects must be properly instancied. This is normally done by using the WidgetApplication class.
    virtual void render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts ) override;


    /// CommuterWidget style setter.
    ///
    /// Gives the style of CommuterWidget
    /// @param type refers to one of the styles given by the *tick* enumerator
    /// @returns Nothing
    /// @see commutertype
    virtual void settype( commutertype type )
    {
        typetick = type;
    };

    /// CommuterWidget style getter.
    ///
    /// Gives the style of CommuterWidget
    /// @param None
    /// @returns The corresponding type of CommuterWidget style
    /// @see commutertype
    virtual commutertype gettype()
    {
        return typetick;
    };


    /// CommuterWidget normal style setter.
    ///
    /// Set the normal order of the CommuterWidget (false = switch on the left / true = switch on the right)
    /// @param None
    /// @returns Nothing
    virtual void setnormal()
    {
        is_reversed = false;
    };


    /// CommuterWidget reversed style setter.
    ///
    /// Set the normal order of the CommuterWidget (false = switch on the right / true = switch on the left)
    /// @param None
    /// @returns Nothing
    virtual void setreversed()
    {
        is_reversed = true;
    };


    /// CommuterWidget normal/reveresed style getter.
    ///
    /// Ask if the CommuterWidget is normal or reversed
    /// @param None
    /// @returns Nothing
    /// @see setnormal() or setreversed()
    virtual bool isreversed()
    {
        return is_reversed;
    };

protected:

private:

    /// Is the CommuterWidget switched ?
    ///
    /// Widget properties giving the status of the CommuterWidget.
    /// @note This boolean should not be adressed directly by the user. Status should be obtained by the CommuterWidget::isticked() method.
    /// @see CommuterWidget::isticked()
    bool is_ticked = false;


    /// Is the CommuterWidget reversed ?
    ///
    /// Widget properties giving the status of the CommuterWidget.
    /// @note This boolean should not be adressed directly by the user. Status should be obtained by the CommuterWidget::isreversed() method.
    /// @see CommuterWidget::isreversed()
    bool is_reversed = false;



    /// Is the mouse clickbutton hold down ?
    ///
    /// Private property, not accessible by the user directly
    /// @note This boolean should not be adressed directly by the user. It says if the click button is hold down to avoid the CommuterWidget to switch on/off at each call to logic();
    /// @note This is only aiming at serving good behavior of the widget.
    bool mouse_hold_down = false;


    /// The style of the CommuterWidget
    ///
    /// Private property, not accessible by the user directly
    /// @note This boolean should not be adressed directly by the user. Status should be obtained by the CommuterWidget::gettype() method.
    /// @see CommuterWidget::gettype()
    commutertype typetick = style1;
};

#endif // COMMUTERWIDGET_H

#ifndef DESKTOPWIDGET_H
#define DESKTOPWIDGET_H

#include "Widget.h"



/// Example of program using DesktopWidget class
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
///    bool done = false;
///
///    WidgetApplication *MyApp = new WidgetApplication();
///    MyApp->setuniformbackgroundcolor(0, 0, 0);
///
///    DesktopWidget *desktop1 = new DesktopWidget( (char*) "First Desktop", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, nullptr );
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



/// DesktopWidget class.
///
/// The class to be used for using a DesktopWidget control widget.
/// DesktopWidget inherits from Widget class.
/// @see  Widget
///
/// ### Examples of usage:
/// ~~~~~~~~~~~~~~~~~~~~~~.cpp
/// DesktopWidget* myDesktop = new DesktopWidget();        // Simple constructor, will need specific properties assignement later
/// ~~~~~~~~~~~~~~~~~~~~~~
/// ~~~~~~~~~~~~~~~~~~~~~~.cpp
/// DesktopWidget* myDesktop = new DesktopWidget( "I am a Desktop", 10, 50, 100, 15, parent );        // Full constructor
/// ~~~~~~~~~~~~~~~~~~~~~~

class DesktopWidget : public Widget
{
public:

    /// Simple constructor.
    ///
    /// Widget properties are set to default, nothing more.
    /// Simple constructor, will need specific properties assignement later.
    /// @param None
    /// @returns Nothing
    /// @see Widget()
    DesktopWidget()
    {
        //widgettype = (char*) "Desktop";
        strcpy( widgettype, (char*) "Desktop");
        fonttemp = new FontEngine();
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
    /// @see Widget( char*, int, int, int, int, Widget* ) or Widget( char*, int, int, int, int, Widget* )
    DesktopWidget( char *l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : Widget( l, x, y, w, h, p )
    {
        //widgettype = (char*) "Desktop";
        strcpy( widgettype, (char*) "Desktop");
        fonttemp = new FontEngine();
    };


    virtual void setmenubar()
    {
        hasmenubar = true;
    };
    virtual void seticonbar()
    {
        hasiconbar = true;
    };
    virtual bool getmenubar()
    {
        return hasmenubar;
    };
    virtual bool geticonbar()
    {
        return hasiconbar;
    };


    // These methods must be override cause Desktop geometry is a bit different with the menubar/icon bar
    virtual unsigned int getuseablexpos() override;
    virtual unsigned int getuseableypos() override;
    virtual unsigned int getuseablewidth() override;
    virtual unsigned int getuseableheight() override;

    /// Object destructor
    ///
    /// Object destructor, remove all trace of the object and free allocated memory
    /// @param None
    /// @returns Nothing
    /// @see ~Widget()
    virtual ~DesktopWidget() { };


    /// The DesktopWidget logic mechanism
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



    /// The DesktopWidget render method.
    ///
    /// Method to be launched to draw the DesktopWidget.
    /// @param screen : pointer to a SDL_Surface object where we would like to draw the wigdet
    /// @param colors : pointer to a ColorEngine object giving all the color options to be used (theme) for drawing the widget
    /// @param fonts : pointer to a FontEngine object giving all the fonts options to be used (theme) for drawing the widget
    /// @returns Nothing, but will launch the render() method of all the Widgets belonging to chidren (vector<Widget*>)
    /// @note This method overrides Widget::render( SDL_Surface*, ColorEngine*, FontEngine*)
    /// @note This method is not intended to be used by a direct call from the user, it is normally called through cascaded calls to children->render() from the WidgetApplication class.
    /// @note Direct call can be used when the Widget is used out of the WidgetApplication 'ecosystem', for example in an application that just use few individual widgets (not recommended cause it may need intensive work from the developper to create adequate working conditions).
    /// @warning Before calling the render method, a SDL_Surface (i.e. a rendering context) as well as a ColorEngine and FontEngine objects must be properly instancied. This is normally done by using the WidgetApplication class.
    virtual void render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts ) override;

    SDL_Surface *screen = nullptr;
    SDL_Surface *depthbuffer = nullptr;


protected:
    virtual void putontop( unsigned int widgetidsearched );



private:
    bool hasmenubar=false;
    bool hasiconbar=false;
    FontEngine *fonttemp = nullptr;

};

#endif // DESKTOPWIDGET_H

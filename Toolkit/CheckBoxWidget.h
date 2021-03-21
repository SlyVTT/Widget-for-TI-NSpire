#ifndef CHECKBOXWIDGET_H
#define CHECKBOXWIDGET_H

#include "ButtonWidget.h"

/// Example of program using CheckBoxWidget controls
///
/// The following simple example demonstrates how to use the CheckBoxWidget controls.
/// \image html CheckBoxWidgetExample1.jpg
/// \image html CheckBoxWidgetExample2.jpg
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
///    CheckBoxWidget *check1 = new CheckBoxWidget();          // Simple constructor so we need to assign all the parameters
///
///    // First the label to be written on the checkbox
///    check1->setlabel( (char*) "Enabled CheckBox - Square tick" );
///
///    // then the dimensions (one by one in that case)
///    check1->setxpos( 5 );
///    check1->setypos( 10 );
///    check1->setwidth( 150 );
///    check1->setheight( 15 );
///    // note : we can also use the method checkbox->setdimensions( 5, 10, 150, 15 ) instead
///
///    // We set the style to "Square_Tick"
///    check1->settype( CheckBoxWidget::Square_Tick );
///
///    // and finally we assign the parent by adding the checkbox as a child to conH
///    contH->addchild( check1 );
///
///    // This is a second checkbox with all parameters passed through the constructon
///    CheckBoxWidget *check2 = new CheckBoxWidget( (char*) "Enabled CheckBox - Cross tick", 1, 1, 1, 1, contH );
///    // We set the style to "Square_Tick"
///    check2->settype( CheckBoxWidget::Cross_Tick );
///
///    // This is a third checkbox with all parameters passed through the constructon
///    CheckBoxWidget *check3 = new CheckBoxWidget( (char*) "Disabled CheckBox - Square tick", 1, 1, 1, 1, contH );
///    // We set the style to "Square_Tick"
///    check3->settype( CheckBoxWidget::Square_Tick );
///    // We disable the checkbox by using the inherited method Wigdet::disable()
///    check3->disable();
///
///    // This is a third checkbox with all parameters passed through the constructon
///    CheckBoxWidget *check4 = new CheckBoxWidget( (char*) "Disabled CheckBox - Square tick", 1, 1, 1, 1, contH );
///    // We set the style to "Cross_Tick"
///    check4->settype( CheckBoxWidget::Cross_Tick );
///    // We disable the checkbox by using the inherited method Wigdet::disable()
///    check4->disable();
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



/// CheckBoxWidget class.
///
/// The class to be used for using a CheckBoxWidget control widget.
/// CheckBoxWidget inherits from ButtonWidget class.
/// @see  ButtonWidget
///
/// ### Examples of usage:
/// ~~~~~~~~~~~~~~~~~~~~~~.cpp
/// CheckBoxWidget* myCheckBox = new CheckBoxWidget();        // Simple constructor, will need specific properties assignement later
/// ~~~~~~~~~~~~~~~~~~~~~~
/// ~~~~~~~~~~~~~~~~~~~~~~.cpp
/// CheckBoxWidget* myCheckBox = new CheckBoxWidget( "I am a CheckBox", 10, 50, 100, 15, parent );        // Full constructor
/// ~~~~~~~~~~~~~~~~~~~~~~
class CheckBoxWidget : public ButtonWidget
{
    public:

        /// Simple constructor.
        ///
        /// Widget properties are set to default, nothing more.
        /// Simple constructor, will need specific properties assignement later.
        /// @param None
        /// @returns Nothing
        /// @see ButtonWidget() or Widget()
        CheckBoxWidget() { widgettype = (char*) "CheckBox"; };


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
        CheckBoxWidget( char *l, int x, int y, int w, int h, Widget *p ) : ButtonWidget( l, x, y, w, h, p ) { widgettype = (char*) "CheckBox"; };


        /// Object destructor
        ///
        /// Object destructor, remove all trace of the object and free allocated memory
        /// @param None
        /// @returns Nothing
        /// @see ~Widget()
        virtual ~CheckBoxWidget() { };


        /// Enumerator for CheckBoxWidget style.
        ///
        /// Gives the style of CheckBoxWidget (of the tickmark).
        /// *Square_Tick* style represents the tick by a rounded square
        /// *Cross_Tick* style represents the tick by a X / Cross
        enum tick
        {
            Square_Tick = 0,
            Cross_Tick = 1
        };


        /// Invert the CheckBox status
        ///
        /// Invert the CheckBoxWidget status, if unticked --> ticked and if ticked --> unticked
        /// @param None
        /// @returns None
        /// @note It changes the internal property *is_ticked* of the CheckBoxWidget
        virtual void invert() { is_ticked = !is_ticked; };


        /// Is the CheckBox ticked ?
        ///
        /// Gives the status of the CheckBoxWidget (ticked or not).
        /// @param None
        /// @returns Boolean value : *true* if the CheckBox is ticked, *false* otherwise
        virtual bool isticked( void ) { return is_ticked; };


        /// The CheckBoxWidget logic mechanism
        ///
        /// Method to be launched to drive the the mechanics behind the CheckBoxWidget behavior.
        /// @param mouse : pointer to a CursorTask handler object serving at passing the mouse (Touchpad) state and position
        /// @param keyboard : pointer to a KeyboardTask handler object serving at passing the keyboard state
        /// @returns Nothing, but will launch the logic() method of all the widgets belonging to chidren (vector<Widget*>)
        /// @note This method overrides Widget::logic( CursorTask*, KeyboardTask*)
        /// @note This method is not intended to be used by a direct call from the user, it is normally called through cascaded calls to children->logic() from the WidgetApplication class
        /// @note Direct call can be used when the Widget is used out of the WidgetApplication 'ecosystem', for example in an application that just use few individual widgets (not recommended cause it may need intensive work from the developper to create adequate working conditions).
        /// @warning Before calling the logic method, a mouse handler and a keyboard handler must be instancied and properly updated through their respective logic() methods. This is normally done by using the WidgetApplication class.
        virtual void logic( CursorTask *mouse, KeyboardTask *keyboard ) override;



        /// The CheckBoxWidget render method.
        ///
        /// Method to be launched to draw the widget.
        /// @param screen : pointer to a SDL_Surface object where we would like to draw the widget
        /// @param colors : pointer to a ColorEngine object giving all the color options to be used (theme) for drawing the widget
        /// @param fonts : pointer to a FontEngine object giving all the fonts options to be used (theme) for drawing the widget
        /// @returns Nothing, but will launch the render() method of all the Widgets belonging to chidren (vector<Widget*>)
        /// @note This method overrides Widget::render( SDL_Surface*, ColorEngine*, FontEngine*)
        /// @note This method is not intended to be used by a direct call from the user, it is normally called through cascaded calls to children->render() from the WidgetApplication class.
        /// @note Direct call can be used when the Widget is used out of the WidgetApplication 'ecosystem', for example in an application that just use few individual widgets (not recommended cause it may need intensive work from the developper to create adequate working conditions).
        /// @warning Before calling the render method, a SDL_Surface (i.e. a rendering context) as well as a ColorEngine and FontEngine objects must be properly instancied. This is normally done by using the WidgetApplication class.
         virtual void render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts ) override;


        /// CheckBoxWidget style setter.
        ///
        /// Gives the style of CheckBoxWidget (of the tickmark)
        /// @param type refers to one of the styles given by the *tick* enumerator
        /// @returns Nothing
        /// @see tick
        virtual void settype( tick type ) { typetick = type; };


        /// CheckBoxWidget style getter.
        ///
        /// Gives the style of CheckBoxWidget (of the tickmark)
        /// @param None
        /// @returns The corresponding type of CheckBoxWidget style
        /// @see tick
        virtual tick gettype() { return typetick; };

    protected:


    private:

        /// Is the CheckBoxWidget pressed ?
        ///
        /// Widget properties giving the status of the CheckBox.
        /// @note This boolean should not be adressed directly by the user. Status should be obtained by the CheckBoxWidget::isticked() method.
        /// @see CheckBoxWidget::isticked()
        bool is_ticked = false;


        /// Is the mouse button hold down ?
        ///
        /// Private property, not accessible by the user directly
        /// @note This boolean should not be adressed directly by the user. It says if the click button is hold down to avoid the CheckBoxWidget to switch on/off at each call to logic();
        /// @note This is only aiming at serving good behavior of the widget.
        bool mouse_hold_down = false;


        /// The style of the CheckBoxWidget
        ///
        /// Private property, not accessible by the user directly
        /// @note This boolean should not be adressed directly by the user. Status should be obtained by the CheckBoxWidget::gettype() method.
        /// @see CheckBoxWidget::gettype()
        tick typetick = Square_Tick;
};

#endif // CHECKBOXWIDGET_H

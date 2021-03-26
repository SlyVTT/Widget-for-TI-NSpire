#ifndef CURSORTASK_H
#define CURSORTASK_H

#include <SDL/SDL_video.h>


/// CursorTask class.
///
/// The class to be used for accessing the touchpad (mouse) and click information.
///
/// ### Examples of usage:
/// ~~~~~~~~~~~~~~~~~~~~~~.cpp
/// CursorTask* myMouse = new CursorTask();        // Simple constructor, will need specific properties assignement later
/// ~~~~~~~~~~~~~~~~~~~~~~
/// ~~~~~~~~~~~~~~~~~~~~~~.cpp
/// WidgetApplication myApp = new WidgetApplication();
/// CursorTask* myMouse = myApp->getmousehandler();
/// ~~~~~~~~~~~~~~~~~~~~~~
/// @note WidgetApplication creates a KeyboardTask object at initialisation. It is then better to ask for a direct access to its CursorTask by using the WidgetApplication::getmousehandler() method.
/// @see WidgetApplication::getmousehandler()


class CursorTask
{
public:

    /// Simple constructor
    ///
    /// Simple constructor, will need specific properties assignement later.
    /// @param None
    /// @returns Nothing
    CursorTask() {};


    /// Object destructor.
    ///
    /// Object destructor, remove all trace of the object and free allocated memory.
    /// @param None
    /// @returns Nothing
    virtual ~CursorTask() {};


    /// The CursorTask logic mechanism
    ///
    /// All the properties of the Touchpad will be updated and member of the current object will be updated accordingly.
    /// @param None
    /// @returns Nothing, internal members will be updated.
    virtual void logic();


    /// The CursorTask render method
    ///
    /// Method to be launched to draw the mouse cursor on the screen.
    /// @param screen : pointer to a SDL_Surface object where we would like to draw the widget.
    /// @returns Nothing.
    virtual void render( SDL_Surface *screen );


    /// The CursorTask showmouse method
    ///
    /// Method to be launched to actually show (and hence draw) the mouse cursor on the screen.
    /// @param None.
    /// @returns Nothing.
    /// @note By default, at initialisation, the cursor is shown
    virtual void showmouse()
    {
        show=true;
    };


    /// The CursorTask hidemouse method
    ///
    /// Method to be launched to hide (and hence not draw) the mouse cursor on the screen.
    /// @param None.
    /// @returns Nothing.
    /// @note By default, at initialisation, the cursor is shown
    virtual void hidemouse()
    {
        show=false;
    };


    /// The CursorTask ismousevisible method
    ///
    /// Method to be launched to know if the mosue cursor is hiden or visible.
    /// @param None.
    /// @returns Boolean : *true* if the cursor is visible and *false* otherwise.
    /// @note By default, at initialisation, the cursor is shown.
    virtual bool ismousevisible()
    {
        return show;
    };


    /// The CursorTask ismouseevent method
    ///
    /// Method to be launched to know if something happened with the CursorTask since last call of the CursorTasklogic().
    /// Tracked events are cursor motion (touchpad has been touched), the pad has been clicked or has been released
    /// @param None.
    /// @returns Boolean : *true* if something happened and *false* otherwise.
    /// @note Each individual event can be tracked individually by CursorTask::ismousemovement() CursorTask::ismouseclickevent() CursorTask::ismousereleaseevent() respectively.
    /// @see CursorTask::ismousemovement() CursorTask::ismouseclickevent() CursorTask::ismousereleaseevent()
    virtual bool ismouseevent()
    {
        return mouseevent;
    };


    /// The CursorTask ismousemoveevent method
    ///
    /// Method to be launched to know if a cursor move event happened with the CursorTask since last call of the CursorTasklogic().
    /// Tracked events are cursor motion (touchpad has been touched) only.
    /// @param None.
    /// @returns Boolean : *true* if something happened and *false* otherwise.
    /// @see CursorTask::ismouseevent() CursorTask::ismouseclickevent() CursorTask::ismousereleaseevent()
    virtual bool ismousemoveevent()
    {
        return mousemoveevent;
    };


    /// The CursorTask ismouseclickevent method
    ///
    /// Method to be launched to know if a mouse click event happened with the CursorTask since last call of the CursorTasklogic().
    /// Tracked events are pad clicks only.
    /// @param None.
    /// @returns Boolean : *true* if something happened and *false* otherwise.
    /// @see CursorTask::ismouseevent() CursorTask::ismousemoveevent() CursorTask::ismousereleaseevent()
    virtual bool ismouseclickevent()
    {
        return mouseclickevent;
    };


    /// The CursorTask ismousereleaseevent method
    ///
    /// Method to be launched to know if a mouse click release event happened with the CursorTask since last call of the CursorTasklogic().
    /// Tracked events are pad release clicks only.
    /// @param None.
    /// @returns Boolean : *true* if something happened and *false* otherwise.
    /// @see CursorTask::ismouseevent() CursorTask::ismousemoveevent() CursorTask::ismouseclickevent()
    virtual bool ismousereleaseevent()
    {
        return mousereleaseevent;
    };


    /// Enumerator for mouse cursor style.
    ///
    /// Gives the style of mouse cursor.
    /// *triangle* style represents simple triangular arrow cursor.
    /// *rounclock* style represents the simple clock cursor (not animated)
    enum cursortype
    {
        triangle = 0,
        roundclock = 1
    };


    /// Cursor style setter.
    ///
    /// Gives the style of mouse cursor
    /// @param type refers to one of the styles given by the *cursortype* enumerator
    /// @returns Nothing
    /// @see cursortype
    virtual void setcursortype( cursortype type );


    /// Cursor Y coordinate in the screen
    ///
    /// Gives direct access to the X coordinate of the cursor on the screen
    /// @note value should be between 0 and 320
    /// @see CursorTask::y CursorTask::state
    int x = SCREEN_WIDTH / 2;


    /// Cursor Y coordinate in the screen
    ///
    /// Gives direct access to the Y coordinate of the cursor on the screen
    /// @note value should be between 0 and 240
    /// @see CursorTask::x CursorTask::state
    int y = SCREEN_HEIGHT / 2;


    /// Cursor click status
    ///
    /// Gives direct access to the button status of the touchpad
    /// @note value is equal to *true* if clicked and *fals* otherwise.
    /// @see CursorTask::x CursorTask::y
    bool state = false;



private:
    bool show = true;

    bool mouseevent = false;
    bool mousemoveevent = false;
    bool mouseclickevent = false;
    bool mousereleaseevent = false;

    cursortype cursor = triangle;
};

#endif // CURSORTASK_H

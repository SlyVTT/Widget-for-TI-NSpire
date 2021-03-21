#ifndef COLORENGINE_H
#define COLORENGINE_H


/// Structure of colors manipulated by ColorEngine
///
/// Gives a structure for RGBA colors to be used all within the ColorEngine
struct colorRGBA
{
    /// The Red component of the color to be within [0 .. 255]
    unsigned short R;
    /// The Green component of the color to be within [0 .. 255]
    unsigned short G;
    /// The Blue component of the color to be within [0 .. 255]
    unsigned short B;
    /// The Alpha (Opacity) component of the color to be within [0 .. 255]
    unsigned short A;
};


/// ColorEngine class.
///
/// The class to be used for using a ColorEngine object.
/// This object/class is not intended to be used out of th WidgetApplication 'ecosystem'
/// BUT may become mandatory to provide a way to use Widget::render() in a proper way.
/// @see  WidgetApplication and Widget::render( SDL_Surface*, ColorEngine*, FontEngine* )
class ColorEngine
{
public:

    /// Simple constructor
    ///
    /// Engine properties are set to default, nothing more.
    /// Simple constructor, will need specific properties assignement later.
    /// @param None
    /// @returns Nothing
    ColorEngine();


    /// Object destructor.
    ///
    /// Object destructor, remove all trace of the ColorEngine and free allocated memory.
    /// @param None
    /// @returns Nothing
    virtual ~ColorEngine();


    /*
    /// Method for saving color shemes to file.
    ///
    /// To be used to save a color scheme to a file.
    /// @note Not implemented yet.
    virtual void savecolortofile( char *filename );
    */

    /*
    /// Method for loading a color shemes from file.
    ///
    /// To be used to load a color scheme already saved in a file.
    /// @note Not implemented yet.
    virtual void loadcolorfromfile( char *filename );
    */

    /// Method for assigning default color shemes to the ColorEngine.
    ///
    /// To be used to assign the default color scheme the ColorEngine.
    virtual void setdefaultcolorpreset( );


    /// Default color names used by the widgets to be rendered.
    ///
    /// To be used only for developping new Widget and keeping a coherency with the look and feel of the other widgets.
    /// Using these default name permits to have a global theming for an application.
    colorRGBA widget_border_enable;
    colorRGBA widget_border_disable;
    colorRGBA widget_border_cursoron;
    colorRGBA widget_border_hasfocus;

    colorRGBA widget_tickmark_enable;
    colorRGBA widget_tickmark_disable;

    colorRGBA widget_filling_enable;
    colorRGBA widget_filling_disable;

    colorRGBA widget_text_enable;
    colorRGBA widget_text_disable;

    colorRGBA window_titlebar_enable;
    colorRGBA window_titlebar_disable;

    colorRGBA window_titlebartext_enable;
    colorRGBA window_titlebartext_disable;

    colorRGBA widget_commuter_active_filling_style1;
    colorRGBA widget_commuter_inactive_filling_style1;
    colorRGBA widget_commuter_active_cursor_style1;
    colorRGBA widget_commuter_inactive_cursor_style1;

    colorRGBA widget_commuter_active_filling_style2;
    colorRGBA widget_commuter_inactive_filling_style2;
    colorRGBA widget_commuter_active_cursor_style2;
    colorRGBA widget_commuter_inactive_cursor_style2;

    colorRGBA widget_commuter_active_filling_style3;
    colorRGBA widget_commuter_inactive_filling_style3;
    colorRGBA widget_commuter_active_cursor_style3;
    colorRGBA widget_commuter_inactive_cursor_style3;

    colorRGBA widget_commuter_active_filling_style4;
    colorRGBA widget_commuter_inactive_filling_style4;
    colorRGBA widget_commuter_active_cursor_style4;
    colorRGBA widget_commuter_inactive_cursor_style4;

    colorRGBA widget_progressbar_enable_filling;
    colorRGBA widget_progressbar_disable_filling;
    colorRGBA widget_progressbar_rainbow_empty;
    colorRGBA widget_progressbar_rainbow_full;


protected:

private:
};

#endif // COLORENGINE_H

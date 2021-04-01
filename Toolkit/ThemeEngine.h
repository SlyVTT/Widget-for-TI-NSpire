#ifndef THEMEENGINE_H
#define THEMEENGINE_H


#include "ColorEngine.h"
#include "FontEngine.h"



class ThemeEngine
{
public:
    ThemeEngine();
    virtual ~ThemeEngine();

    virtual void loadthemefromfile( char* filename );

    virtual void assigncolorhandler( ColorEngine* handler )
    {
        colorhandler = handler;
    };
    virtual void assignfonthandler( FontEngine* handler )
    {
        fonthandler = handler;
    };

    virtual void setdefaulttheme()
    {
        colorhandler->setdefaultcolorpreset();
        fonthandler->setdefaultfontpreset();
    };

    virtual void applytheme();


protected:

    ColorEngine *colorhandler;
    FontEngine *fonthandler;

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
    colorRGBA widget_selection;

    colorRGBA widget_text_enable;
    colorRGBA widget_text_disable;
    colorRGBA widget_text_selected;

    colorRGBA window_titlebar_enable;
    colorRGBA window_titlebar_disable;
    colorRGBA window_titlebar_minimize;
    colorRGBA window_titlebar_maximize;
    colorRGBA window_titlebar_restore;

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


    /// Default font names used by the widgets to be rendered.
    ///
    /// To be used only for developping new Widget and keeping a coherency with the look and feel of the other widgets.
    /// Using these default name permits to have a global theming for an application.
    fontset font_widget_text_enable;
    fontset font_widget_text_disable;
    fontset font_widget_text_selected;

    fontset font_window_titlebartext_enable;
    fontset font_window_titlebartext_disable;


private:
};

#endif // THEMEENGINE_H

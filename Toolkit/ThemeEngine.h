#ifndef THEMEENGINE_H
#define THEMEENGINE_H


#include "ColorEngine.h"
#include "FontEngine.h"



class ThemeEngine
{
public:
    ThemeEngine();
    virtual ~ThemeEngine();

    virtual void loadthemefromfile( std::string filename );
    virtual void assigncolorhandler( ColorEngine* handler );
    virtual void assignfonthandler( FontEngine* handler );
    virtual void setdefaulttheme();
    virtual void applytheme();


protected:

    ColorEngine *colorhandler;
    FontEngine *fonthandler;

    /// Default color names used by the widgets to be rendered.
    ///
    /// To be used only for developping new Widget and keeping a coherency with the look and feel of the other widgets.
    /// Using these default name permits to have a global theming for an application.
     ColorEngine::colorRGBA widget_border_enable;
     ColorEngine::colorRGBA widget_border_disable;
     ColorEngine::colorRGBA widget_border_cursoron;
     ColorEngine::colorRGBA widget_border_hasfocus;

     ColorEngine::colorRGBA widget_tickmark_enable;
     ColorEngine::colorRGBA widget_tickmark_disable;

     ColorEngine::colorRGBA widget_filling_enable;
     ColorEngine::colorRGBA widget_filling_disable;
     ColorEngine::colorRGBA widget_selection;

     ColorEngine::colorRGBA widget_text_enable;
     ColorEngine::colorRGBA widget_text_disable;
     ColorEngine::colorRGBA widget_text_selected;

     ColorEngine::colorRGBA window_titlebar_enable;
     ColorEngine::colorRGBA window_titlebar_disable;
     ColorEngine::colorRGBA window_titlebar_minimize;
     ColorEngine::colorRGBA window_titlebar_maximize;
     ColorEngine::colorRGBA window_titlebar_restore;

     ColorEngine::colorRGBA window_titlebartext_enable;
     ColorEngine::colorRGBA window_titlebartext_disable;

     ColorEngine::colorRGBA widget_commuter_active_filling_style1;
     ColorEngine::colorRGBA widget_commuter_inactive_filling_style1;
     ColorEngine::colorRGBA widget_commuter_active_cursor_style1;
     ColorEngine::colorRGBA widget_commuter_inactive_cursor_style1;

     ColorEngine::colorRGBA widget_commuter_active_filling_style2;
     ColorEngine::colorRGBA widget_commuter_inactive_filling_style2;
     ColorEngine::colorRGBA widget_commuter_active_cursor_style2;
     ColorEngine::colorRGBA widget_commuter_inactive_cursor_style2;

     ColorEngine::colorRGBA widget_commuter_active_filling_style3;
     ColorEngine::colorRGBA widget_commuter_inactive_filling_style3;
     ColorEngine::colorRGBA widget_commuter_active_cursor_style3;
     ColorEngine::colorRGBA widget_commuter_inactive_cursor_style3;

     ColorEngine::colorRGBA widget_commuter_active_filling_style4;
     ColorEngine::colorRGBA widget_commuter_inactive_filling_style4;
     ColorEngine::colorRGBA widget_commuter_active_cursor_style4;
     ColorEngine::colorRGBA widget_commuter_inactive_cursor_style4;

     ColorEngine::colorRGBA widget_progressbar_enable_filling;
     ColorEngine::colorRGBA widget_progressbar_disable_filling;
     ColorEngine::colorRGBA widget_progressbar_rainbow_empty;
     ColorEngine::colorRGBA widget_progressbar_rainbow_full;


    /// Default font names used by the widgets to be rendered.
    ///
    /// To be used only for developping new Widget and keeping a coherency with the look and feel of the other widgets.
    /// Using these default name permits to have a global theming for an application.
    FontEngine::fontset font_widget_text_enable;
    FontEngine::fontset font_widget_text_disable;
    FontEngine::fontset font_widget_text_selected;

    FontEngine::fontset font_window_titlebartext_enable;
    FontEngine::fontset font_window_titlebartext_disable;


private:
};

#endif // THEMEENGINE_H

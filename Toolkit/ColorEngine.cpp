#include "ColorEngine.h"

ColorEngine::ColorEngine()
{
    //ctor
}

ColorEngine::~ColorEngine()
{
    //dtor
}

/*
void ColorEngine::savecolortofile( char *filename )
{

    // to be done

}
*/

/*
void ColorEngine::loadcolorfromfile( char *filename )
{

    // to be done

}
*/

void ColorEngine::setdefaultcolorpreset( )
{

    // Normal DEFAULT theme (Hard coded)
    widget_border_enable = { 255, 0, 0, 255 }; //RED
    widget_border_disable = { 170, 170, 170, 255 };  //BLACK
    widget_border_cursoron = { 0, 255, 0, 255  }; //GREEN
    widget_border_hasfocus = { 0, 0, 255, 255 }; //BLUE

    widget_tickmark_enable = { 0, 0, 0, 255 }; //BLACK
    widget_tickmark_disable = { 170, 170, 170, 255 }; //DARK GREY

    widget_filling_enable = { 255, 255, 255, 255 }; //WHITE
    widget_filling_disable = { 255, 255, 255, 255 }; //WHITE
    widget_selection = { 255, 0, 125, 255 }; // PURPLEISH

    widget_text_enable = { 0, 0, 0, 255 }; //BLACK
    widget_text_disable = { 170, 170, 170, 255 }; // GREY
    widget_text_selected = { 255, 255, 255, 255 }; //WHITE

    window_titlebar_enable = { 0, 155, 255, 255 }; //LIGHT BLUE/CYAN
    window_titlebar_disable = { 170, 170, 170, 255 }; // GREY
    window_titlebar_minimize = { 255, 0, 0, 255 }; // RED
    window_titlebar_maximize = { 0, 255, 0, 255 }; // GREEN
    window_titlebar_restore = { 255, 255, 0, 255 }; // YELLOW

    window_titlebartext_enable = { 255, 255, 255, 255 }; //WHITE
    window_titlebartext_disable = { 100, 100, 100, 255 }; //DARK GREY

    widget_commuter_active_filling_style1 = { 255, 255, 255, 255 }; //WHITE
    widget_commuter_inactive_filling_style1 = { 255, 191, 191, 255 }; //SALMON
    widget_commuter_active_cursor_style1 = { 255, 255, 255, 255 }; //WHITE
    widget_commuter_inactive_cursor_style1 = { 255, 255, 255, 255 }; //WHITE

    widget_commuter_active_filling_style2 = { 255, 255, 255, 255 }; //WHITE
    widget_commuter_inactive_filling_style2 = { 255, 255, 255, 255 }; //WHITE
    widget_commuter_active_cursor_style2 = { 255, 255, 255, 255 }; //WHITE
    widget_commuter_inactive_cursor_style2 = { 255, 191, 191, 255 }; //SALMON

    widget_commuter_active_filling_style3 =  { 191, 255, 191, 255 }; //TENDER GREEN
    widget_commuter_inactive_filling_style3 = { 255, 191, 191, 255 }; //SALMON
    widget_commuter_active_cursor_style3 = { 255, 255, 255, 255 }; //WHITE
    widget_commuter_inactive_cursor_style3 = { 255, 255, 255, 255 }; //WHITE

    widget_commuter_active_filling_style4 = { 255, 255, 255, 255 }; //WHITE
    widget_commuter_inactive_filling_style4 = { 255, 255, 255, 255 }; //WHITE
    widget_commuter_active_cursor_style4 = { 191, 255, 191, 255 }; //TENDER GREEN
    widget_commuter_inactive_cursor_style4 = { 255, 191, 191, 255 }; //SALMON

    widget_progressbar_enable_filling = { 0, 155, 255, 255 }; //LIGHT BLUE/CYAN
    widget_progressbar_disable_filling = { 170, 170, 170, 255 }; // GREY
    widget_progressbar_rainbow_empty = { 127, 127, 0, 255 };
    widget_progressbar_rainbow_full = { 0, 255, 0, 255 };

}

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
/*
    // Dark theme
    widget_border_enable = { 65, 115, 185, 255  }; //STORM BLUE
    widget_border_disable = { 50, 55, 60, 255 };  //DARK GREY
    widget_border_cursoron = { 200, 210, 220, 255 }; //PALE WHITE
    widget_border_hasfocus = { 50, 55, 60, 255 }; //DARK GREY

    widget_tickmark_enable = { 65, 115, 185, 255  }; //STORM BLUE
    widget_tickmark_disable = { 50, 55, 60, 255 };  //DARK GREY

    widget_filling_enable = { 15, 20, 25, 255 }; //VERY DARK GREY
    widget_filling_disable = { 15, 20, 25, 255 }; //VERY DARK GREY

    widget_text_enable = { 200, 210, 220, 255 }; //PALE WHITE
    widget_text_disable = { 190, 180, 170, 255 }; //GREYISH

    window_titlebar_enable = { 245 , 75, 1255, 255 }; //PINK
    window_titlebar_disable = { 100, 100, 100, 255 }; // GREY

    window_titlebartext_enable = { 255, 255, 255, 255 }; //WHITE
    window_titlebartext_disable = { 190, 180, 170, 255 }; //GREYISH

    widget_commuter_active_filling_style1 = { 15, 20, 25, 255 }; //VERY DARK GREY
    widget_commuter_inactive_filling_style1 = { 245 , 75, 125, 255 }; //PINK
    widget_commuter_active_cursor_style1 = { 15, 20, 25, 255 }; //VERY DARK GREY
    widget_commuter_inactive_cursor_style1 = { 15, 20, 25, 255 }; //VERY DARK GREY

    widget_commuter_active_filling_style2 = { 15, 20, 25, 255 }; //VERY DARK GREY
    widget_commuter_inactive_filling_style2 = { 15, 20, 25, 255 }; //VERY DARK GREY
    widget_commuter_active_cursor_style2 = {15, 20, 25, 255 }; //VERY DARK GREY
    widget_commuter_inactive_cursor_style2 = { 245 , 75, 125, 255 }; //PINK

    widget_commuter_active_filling_style3 =  { 50, 160, 70, 255 }; // OLIVE GREEN
    widget_commuter_inactive_filling_style3 = { 245 , 75, 125, 255 }; //PINK
    widget_commuter_active_cursor_style3 = { 15, 20, 25, 255 }; //VERY DARK GREY
    widget_commuter_inactive_cursor_style3 = { 15, 20, 25, 255 }; //VERY DARK GREY

    widget_commuter_active_filling_style4 = { 15, 20, 25, 255 }; //VERY DARK GREY
    widget_commuter_inactive_filling_style4 = { 15, 20, 25, 255 }; //VERY DARK GREY
    widget_commuter_active_cursor_style4 = { 50, 160, 70, 255 }; // OLIVE GREEN
    widget_commuter_inactive_cursor_style4 = { 245 , 75, 125, 255 }; //PINK

    widget_progressbar_enable_filling = { 245 , 75, 125, 255 }; //PINK
    widget_progressbar_disable_filling = { 50, 55, 60, 255 };  //DARK GREY
    widget_progressbar_rainbow_empty = { 245 , 75, 125, 255 }; //PINK
    widget_progressbar_rainbow_full = { 50, 160, 70, 255 }; // OLIVE GREEN

*/


    // Normal theme
    widget_border_enable = { 255, 0, 0, 255 }; //RED
    widget_border_disable = { 170, 170, 170, 255 };  //BLACK
    widget_border_cursoron = { 0, 255, 0, 255  }; //GREEN
    widget_border_hasfocus = { 0, 0, 255, 255 }; //BLUE

    widget_tickmark_enable = { 0, 0, 0, 255 }; //BLACK
    widget_tickmark_disable = { 170, 170, 170, 255 }; //DARK GREY

    widget_filling_enable = { 255, 255, 255, 255 }; //WHITE
    widget_filling_disable = { 255, 255, 255, 255 }; //WHITE

    widget_text_enable = { 0, 0, 0, 255 }; //BLACK
    widget_text_disable = { 170, 170, 170, 255 }; // GREY

    window_titlebar_enable = { 0, 155, 255, 255 }; //LIGHT BLUE/CYAN
    window_titlebar_disable = { 170, 170, 170, 255 }; // GREY

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


    // the Following colorset is used for the Link_SDL / GUI Toolkit interaction
    /*
        widget_border_enable = { 255, 255, 255, 255 }; //RED
        widget_border_disable = { 170, 170, 170, 255 };  //BLACK
        widget_border_cursoron = { 0, 0, 0, 255  }; //GREEN
        widget_border_hasfocus = { 0, 0, 0, 255 }; //BLUE

        widget_tickmark_enable = { 255, 255, 255, 255 }; //BLACK
        widget_tickmark_disable = { 170, 170, 170, 255 }; // GREY

        widget_filling_enable = { 50, 50, 50, 255 }; //WHITE
        widget_filling_disable = { 0, 0, 0, 0 }; //WHITE

        widget_text_enable = { 255, 255, 255, 255 }; //BLACK
        widget_text_disable = { 100, 100, 100, 255 }; //DARK GREY

        window_titlebar_enable = { 0, 255, 55, 255 }; //LIGHT BLUE/CYAN
        window_titlebar_disable = { 0, 100, 0, 255 }; //LIGHT GREY

        window_titlebartext_enable = { 255, 255, 255, 255 }; //WHITE
        window_titlebartext_disable = { 100, 100, 100, 255 }; //DARK GREY
    */

}

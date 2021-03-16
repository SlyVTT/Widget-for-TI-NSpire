#ifndef COLORENGINE_H
#define COLORENGINE_H

struct colorRGBA
{
    unsigned short R;
    unsigned short G;
    unsigned short B;
    unsigned short A;
};

class ColorEngine
{
    public:
        ColorEngine();
        virtual ~ColorEngine();

        virtual void savecolortofile( char *filename );
        virtual void loadcolorfromfile( char *filename );

        virtual void setdefaultcolorpreset( );


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

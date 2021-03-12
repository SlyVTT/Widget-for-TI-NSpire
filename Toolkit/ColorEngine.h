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

    protected:


    private:
};

#endif // COLORENGINE_H

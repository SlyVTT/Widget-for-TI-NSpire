#include "ProgressBarWidget.h"


void ProgressBarWidget::logic( CursorTask *mouse, KeyboardTask *keyboard )
{
    if (is_enabled && is_visible)
    {
        is_hovering = cursoron( mouse );

        if(is_hovering)
        {
            if (hoverfunction)
                hoverfunction( (char*) "test" );
        }

        for (auto& c : children )
            c->logic( mouse, keyboard );
    }
}

void ProgressBarWidget::render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts )
{
    if (is_visible)
    {

        if (is_enabled)
        {
            roundedBoxRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_filling_enable.R, colors->widget_filling_enable.G, colors->widget_filling_enable.B, colors->widget_filling_enable.A);

            if (!is_hovering)
            {
                roundedRectangleRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_border_enable.R, colors->widget_border_enable.G, colors->widget_border_enable.B, colors->widget_border_enable.A);
            }
            else
            {
                roundedRectangleRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_border_cursoron.R, colors->widget_border_cursoron.G, colors->widget_border_cursoron.B, colors->widget_border_cursoron.A);
            }

            if (percentfilled<=0.0) percentfilled=0.0;

            if (percentfilled>0)
            {
                if (percentfilled>100.0) percentfilled=100.0;

                float length;


                if (style == Continuous)
                {
                    length = (percentfilled/100.0 * (width-2));
                    roundedBoxRGBA( screen, xpos+2, ypos+2, xpos+((int) length), ypos+height-2, 2, colors->widget_progressbar_enable_filling.R, colors->widget_progressbar_enable_filling.G, colors->widget_progressbar_enable_filling.B, colors->widget_progressbar_enable_filling.A);
                }
                else if (style == Bricks)
                {
                    length = width;
                    float bricklength = length / nbbricks;
                    int dx = 0;
                    for( int u=0; u<nbbricks; u++)
                    {
                        if ((u+1)*100/nbbricks <= percentfilled)
                        {
                            roundedBoxRGBA( screen, xpos+3+dx, ypos+2, xpos+dx+bricklength+2, ypos+height-2, 2, colors->widget_progressbar_enable_filling.R, colors->widget_progressbar_enable_filling.G, colors->widget_progressbar_enable_filling.B, colors->widget_progressbar_enable_filling.A);
                            dx += (int) bricklength;
                        }
                        else
                        {
                            float remain = percentfilled-u*100/nbbricks;
                            if (remain >= 0)
                            {
                                int extralength = (int) (remain/100*width);
                                roundedBoxRGBA( screen, xpos+3+dx, ypos+2, xpos+dx+extralength+2, ypos+height-2, 2, colors->widget_progressbar_enable_filling.R, colors->widget_progressbar_enable_filling.G, colors->widget_progressbar_enable_filling.B, colors->widget_progressbar_enable_filling.A);
                            }
                        }
                    }
                }
                else if (style == Rainbow)
                {
                    unsigned short R, G, B, A;
                    R = (unsigned int) (colors->widget_progressbar_rainbow_empty.R + percentfilled/100 * (colors->widget_progressbar_rainbow_full.R - colors->widget_progressbar_rainbow_empty.R));
                    G = (unsigned int) (colors->widget_progressbar_rainbow_empty.G + percentfilled/100 * (colors->widget_progressbar_rainbow_full.G - colors->widget_progressbar_rainbow_empty.G));
                    B = (unsigned int) (colors->widget_progressbar_rainbow_empty.B + percentfilled/100 * (colors->widget_progressbar_rainbow_full.B - colors->widget_progressbar_rainbow_empty.B));
                    A = (unsigned int) (colors->widget_progressbar_rainbow_empty.A + percentfilled/100 * (colors->widget_progressbar_rainbow_full.A - colors->widget_progressbar_rainbow_empty.A));
                    length = (percentfilled/100.0 * (width-2));
                    roundedBoxRGBA( screen, xpos+2, ypos+2, xpos+((int) length), ypos+height-2, 2, R, G, B, A);
                }
                else if (style == RainbowBrick)
                {
                    unsigned short R, G, B, A;
                    R = (unsigned int) (colors->widget_progressbar_rainbow_empty.R + percentfilled/100 * (colors->widget_progressbar_rainbow_full.R - colors->widget_progressbar_rainbow_empty.R));
                    G = (unsigned int) (colors->widget_progressbar_rainbow_empty.G + percentfilled/100 * (colors->widget_progressbar_rainbow_full.G - colors->widget_progressbar_rainbow_empty.G));
                    B = (unsigned int) (colors->widget_progressbar_rainbow_empty.B + percentfilled/100 * (colors->widget_progressbar_rainbow_full.B - colors->widget_progressbar_rainbow_empty.B));
                    A = (unsigned int) (colors->widget_progressbar_rainbow_empty.A + percentfilled/100 * (colors->widget_progressbar_rainbow_full.A - colors->widget_progressbar_rainbow_empty.A));
                    length = width;
                    float bricklength = length / nbbricks;
                    int dx = 0;
                    for( int u=0; u<nbbricks; u++)
                    {
                        if ((u+1)*100/nbbricks <= percentfilled)
                        {
                            roundedBoxRGBA( screen, xpos+3+dx, ypos+2, xpos+dx+bricklength+2, ypos+height-2, 2, R, G, B, A);
                            dx += (int) bricklength;
                        }
                        else
                        {
                            float remain = percentfilled-u*100/nbbricks;
                            if (remain >= 0)
                            {
                                int extralength = (int) (remain/100*width);
                                roundedBoxRGBA( screen, xpos+3+dx, ypos+2, xpos+dx+extralength+2, ypos+height-2, 2, R, G, B, A);
                            }
                        }
                    }
                }
            }


            if (drawvalue)
            {
                char value[10];

                sprintf( value, "%d", (int) percentfilled);

                fonts->setcurrentfont( fonts->widget_text_enable.name );
                fonts->setmodifiertypo( fonts->widget_text_enable.typo );
                fonts->setmodifierunder( fonts->widget_text_enable.under );
                fonts->setmodifierstrike( fonts->widget_text_enable.strike );

                int sl = fonts->getstringwidth( value );
                int sh = fonts->getstringheight( value );

                if (sl<=width-15) boxRGBA( screen, xpos+(width-sl)/2-2, ypos+2, xpos+(width+sl)/2+2, ypos+height-2, colors->widget_filling_enable.R, colors->widget_filling_enable.G, colors->widget_filling_enable.B, colors->widget_filling_enable.A);
                if (sl<=width-15) fonts->drawstringleft( screen, value, xpos+(width-sl)/2, ypos+(height-sh)/2, colors->widget_text_enable.R, colors->widget_text_enable.G, colors->widget_text_enable.B, colors->widget_text_enable.A );
            }
        }
        else
        {
            roundedBoxRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_filling_disable.R, colors->widget_filling_disable.G, colors->widget_filling_disable.B, colors->widget_filling_disable.A);

            roundedRectangleRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_border_disable.R, colors->widget_border_disable.G, colors->widget_border_disable.B, colors->widget_border_disable.A);


            if (percentfilled<=0.0) percentfilled=0.0;

            if (percentfilled>0)
            {
                if (percentfilled>100.0) percentfilled=100.0;

                float length;


                if (style == Continuous)
                {
                    length = (percentfilled/100.0 * (width-2));
                    roundedBoxRGBA( screen, xpos+2, ypos+2, xpos+((int) length), ypos+height-2, 2, colors->widget_progressbar_disable_filling.R, colors->widget_progressbar_disable_filling.G, colors->widget_progressbar_disable_filling.B, colors->widget_progressbar_disable_filling.A);
                }
                else if (style == Bricks)
                {
                    length = width;
                    float bricklength = length / nbbricks;
                    int dx = 0;
                    for( int u=0; u<nbbricks; u++)
                    {
                        if ((u+1)*100/nbbricks <= percentfilled)
                        {
                            roundedBoxRGBA( screen, xpos+3+dx, ypos+2, xpos+dx+bricklength+2, ypos+height-2, 2, colors->widget_progressbar_disable_filling.R, colors->widget_progressbar_disable_filling.G, colors->widget_progressbar_disable_filling.B, colors->widget_progressbar_disable_filling.A);
                            dx += (int) bricklength;
                        }
                        else
                        {
                            float remain = percentfilled-u*100/nbbricks;
                            if (remain >= 0)
                            {
                                int extralength = (int) (remain/100*width);
                                roundedBoxRGBA( screen, xpos+3+dx, ypos+2, xpos+dx+extralength+2, ypos+height-2, 2, colors->widget_progressbar_disable_filling.R, colors->widget_progressbar_disable_filling.G, colors->widget_progressbar_disable_filling.B, colors->widget_progressbar_disable_filling.A);
                            }
                        }
                    }
                }
                else if (style == Rainbow)
                {
                    length = (percentfilled/100.0 * (width-2));
                    roundedBoxRGBA( screen, xpos+2, ypos+2, xpos+((int) length), ypos+height-2, 2, colors->widget_progressbar_disable_filling.R, colors->widget_progressbar_disable_filling.G, colors->widget_progressbar_disable_filling.B, colors->widget_progressbar_disable_filling.A);
                }
                else if (style == RainbowBrick)
                {
                    length = width;
                    float bricklength = length / nbbricks;
                    int dx = 0;
                    for( int u=0; u<nbbricks; u++)
                    {
                        if ((u+1)*100/nbbricks <= percentfilled)
                        {
                            roundedBoxRGBA( screen, xpos+3+dx, ypos+2, xpos+dx+bricklength+2, ypos+height-2, 2, colors->widget_progressbar_disable_filling.R, colors->widget_progressbar_disable_filling.G, colors->widget_progressbar_disable_filling.B, colors->widget_progressbar_disable_filling.A);
                            dx += (int) bricklength;
                        }
                        else
                        {
                            float remain = percentfilled-u*100/nbbricks;
                            if (remain >= 0)
                            {
                                int extralength = (int) (remain/100*width);

                                roundedBoxRGBA( screen, xpos+3+dx, ypos+2, xpos+dx+extralength+2, ypos+height-2, 2, colors->widget_progressbar_disable_filling.R, colors->widget_progressbar_disable_filling.G, colors->widget_progressbar_disable_filling.B, colors->widget_progressbar_disable_filling.A);
                            }
                        }
                    }
                }
            }


            if (drawvalue)
            {
                char value[10];

                sprintf( value, "%d", (int) percentfilled);

                fonts->setcurrentfont( fonts->widget_text_disable.name );
                fonts->setmodifiertypo( fonts->widget_text_disable.typo );
                fonts->setmodifierunder( fonts->widget_text_disable.under );
                fonts->setmodifierstrike( fonts->widget_text_disable.strike );

                int sl = fonts->getstringwidth( value );
                int sh = fonts->getstringheight( value );

                if (sl<=width-15) boxRGBA( screen, xpos+(width-sl)/2-2, ypos+2, xpos+(width+sl)/2+2, ypos+height-2, colors->widget_filling_disable.R, colors->widget_filling_disable.G, colors->widget_filling_disable.B, colors->widget_filling_disable.A);
                if (sl<=width-15) fonts->drawstringleft( screen, value, xpos+(width-sl)/2, ypos+(height-sh)/2, colors->widget_text_disable.R, colors->widget_text_disable.G, colors->widget_text_disable.B, colors->widget_text_disable.A );
            }
        }

        for (auto& c : children )
            c->render( screen, colors, fonts );

    }
}

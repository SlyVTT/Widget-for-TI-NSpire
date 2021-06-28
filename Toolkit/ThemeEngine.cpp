#include "ThemeEngine.h"

#include <stdio.h>

ThemeEngine::ThemeEngine()
{
    //ctor
}

ThemeEngine::~ThemeEngine()
{
    //dtor
}

void ThemeEngine::assigncolorhandler( ColorEngine* handler )
{
    colorhandler = handler;
};

void ThemeEngine::assignfonthandler( FontEngine* handler )
{
    fonthandler = handler;
};

void ThemeEngine::setdefaulttheme()
{
    colorhandler->setdefaultcolorpreset();
    fonthandler->setdefaultfontpreset();
};


void ThemeEngine::loadthemefromfile( std::string filename)
{

    FILE* pFile;
    pFile = fopen (filename.c_str(),"r");
    if (pFile!=NULL)
    {
        char line[20];
        unsigned int R, G, B;           // RGB values (Alpha is always 255)
        unsigned int N, T, U, S;        // Name, Type, Underline, Strike


        // We read all the colors and associated information in the theme file

        fscanf( pFile, "%s", line );
        //if (line == (char*) "[WIDGET_BORDER]")
        {
            fscanf( pFile, "%s", line );
            //if (line == (char*) "enable")
            {
                fscanf( pFile, "%d %d %d", &R, &G, &B );

                widget_border_enable.R = R;
                widget_border_enable.G = G;
                widget_border_enable.B = B;
                widget_border_enable.A = 255;
            }

            fscanf( pFile, "%s", line );
            //if (line == (char*) "disable")
            {
                fscanf( pFile, "%d %d %d", &R, &G, &B );

                widget_border_disable.R = R;
                widget_border_disable.G = G;
                widget_border_disable.B = B;
                widget_border_disable.A = 255;
            }

            fscanf( pFile, "%s", line );
            //if (line == (char*) "cursoron")
            {
                fscanf( pFile, "%d %d %d", &R, &G, &B );

                widget_border_cursoron.R = R;
                widget_border_cursoron.G = G;
                widget_border_cursoron.B = B;
                widget_border_cursoron.A = 255;
            }

            fscanf( pFile, "%s", line );
            //if (line == (char*) "hasfocus")
            {
                fscanf( pFile, "%d %d %d", &R, &G, &B );

                widget_border_hasfocus.R = R;
                widget_border_hasfocus.G = G;
                widget_border_hasfocus.B = B;
                widget_border_hasfocus.A = 255;
            }
        }


        fscanf( pFile, "%s", line );
        //if (line == (char*) "[WIDGET_TICKMARK]")
        {
            fscanf( pFile, "%s", line );
            //if (line == (char*) "enable")
            {
                fscanf( pFile, "%d %d %d", &R, &G, &B );

                widget_tickmark_enable.R = R;
                widget_tickmark_enable.G = G;
                widget_tickmark_enable.B = B;
                widget_tickmark_enable.A = 255;
            }

            fscanf( pFile, "%s", line );
            //if (line == (char*) "disable")
            {
                fscanf( pFile, "%d %d %d", &R, &G, &B );

                widget_tickmark_disable.R = R;
                widget_tickmark_disable.G = G;
                widget_tickmark_disable.B = B;
                widget_tickmark_disable.A = 255;
            }
        }


        fscanf( pFile, "%s", line );
        //if (line == (char*) "[WIDGET_FILL]")
        {
            fscanf( pFile, "%s", line );
            //if (line == (char*) "enable")
            {
                fscanf( pFile, "%d %d %d", &R, &G, &B );

                widget_filling_enable.R = R;
                widget_filling_enable.G = G;
                widget_filling_enable.B = B;
                widget_filling_enable.A = 255;
            }

            fscanf( pFile, "%s", line );
            //if (line == (char*) "disable")
            {
                fscanf( pFile, "%d %d %d", &R, &G, &B );

                widget_filling_disable.R = R;
                widget_filling_disable.G = G;
                widget_filling_disable.B = B;
                widget_filling_disable.A = 255;
            }

            fscanf( pFile, "%s", line );
            //if (line == (char*) "selected")
            {
                fscanf( pFile, "%d %d %d", &R, &G, &B );

                widget_selection.R = R;
                widget_selection.G = G;
                widget_selection.B = B;
                widget_selection.A = 255;
            }
        }


        fscanf( pFile, "%s", line );
        //if (line == (char*) "[WIDGET_TEXT]")
        {
            fscanf( pFile, "%s", line );
            //if (line == (char*) "enable")
            {
                fscanf( pFile, "%d %d %d", &R, &G, &B );

                widget_text_enable.R = R;
                widget_text_enable.G = G;
                widget_text_enable.B = B;
                widget_text_enable.A = 255;
            }

            fscanf( pFile, "%s", line );
            //if (line == (char*) "disable")
            {
                fscanf( pFile, "%d %d %d", &R, &G, &B );

                widget_text_disable.R = R;
                widget_text_disable.G = G;
                widget_text_disable.B = B;
                widget_text_disable.A = 255;
            }

            fscanf( pFile, "%s", line );
            //if (line == (char*) "selected")
            {
                fscanf( pFile, "%d %d %d", &R, &G, &B );

                widget_text_selected.R = R;
                widget_text_selected.G = G;
                widget_text_selected.B = B;
                widget_text_selected.A = 255;
            }
        }


        fscanf( pFile, "%s", line );
        //if (line == (char*) "[WINDOW_TITLEBAR]")
        {
            fscanf( pFile, "%s", line );
            //if (line == (char*) "enable")
            {
                fscanf( pFile, "%d %d %d", &R, &G, &B );

                window_titlebar_enable.R = R;
                window_titlebar_enable.G = G;
                window_titlebar_enable.B = B;
                window_titlebar_enable.A = 255;
            }

            fscanf( pFile, "%s", line );
            //if (line == (char*) "disable")
            {
                fscanf( pFile, "%d %d %d", &R, &G, &B );

                window_titlebar_disable.R = R;
                window_titlebar_disable.G = G;
                window_titlebar_disable.B = B;
                window_titlebar_disable.A = 255;
            }

            fscanf( pFile, "%s", line );
            //if (line == (char*) "maximize")
            {
                fscanf( pFile, "%d %d %d", &R, &G, &B );

                window_titlebar_maximize.R = R;
                window_titlebar_maximize.G = G;
                window_titlebar_maximize.B = B;
                window_titlebar_maximize.A = 255;
            }

            fscanf( pFile, "%s", line );
            //if (line == (char*) "minimize")
            {
                fscanf( pFile, "%d %d %d", &R, &G, &B );

                window_titlebar_minimize.R = R;
                window_titlebar_minimize.G = G;
                window_titlebar_minimize.B = B;
                window_titlebar_minimize.A = 255;
            }

            fscanf( pFile, "%s", line );
            //if (line == (char*) "restore")
            {
                fscanf( pFile, "%d %d %d", &R, &G, &B );

                window_titlebar_restore.R = R;
                window_titlebar_restore.G = G;
                window_titlebar_restore.B = B;
                window_titlebar_restore.A = 255;
            }

        }


        fscanf( pFile, "%s", line );
        //if (line == (char*) "[WINDOW_TITLEBARTEXT]")
        {
            fscanf( pFile, "%s", line );
            //if (line == (char*) "enable")
            {
                fscanf( pFile, "%d %d %d", &R, &G, &B );

                window_titlebartext_enable.R = R;
                window_titlebartext_enable.G = G;
                window_titlebartext_enable.B = B;
                window_titlebartext_enable.A = 255;
            }

            fscanf( pFile, "%s", line );
            //if (line == (char*) "disable")
            {
                fscanf( pFile, "%d %d %d", &R, &G, &B );

                window_titlebartext_disable.R = R;
                window_titlebartext_disable.G = G;
                window_titlebartext_disable.B = B;
                window_titlebartext_disable.A = 255;
            }
        }


        fscanf( pFile, "%s", line );
        //if (line == (char*) "[COMMUTER_STYLE1]")
        {
            fscanf( pFile, "%s", line );
            //if (line == (char*) "activefill")
            {
                fscanf( pFile, "%d %d %d", &R, &G, &B );

                widget_commuter_active_filling_style1.R = R;
                widget_commuter_active_filling_style1.G = G;
                widget_commuter_active_filling_style1.B = B;
                widget_commuter_active_filling_style1.A = 255;
            }

            fscanf( pFile, "%s", line );
            //if (line == (char*) "inactivefill")
            {
                fscanf( pFile, "%d %d %d", &R, &G, &B );

                widget_commuter_inactive_filling_style1.R = R;
                widget_commuter_inactive_filling_style1.G = G;
                widget_commuter_inactive_filling_style1.B = B;
                widget_commuter_inactive_filling_style1.A = 255;
            }

            fscanf( pFile, "%s", line );
            //if (line == (char*) "activecur")
            {
                fscanf( pFile, "%d %d %d", &R, &G, &B );

                widget_commuter_active_cursor_style1.R = R;
                widget_commuter_active_cursor_style1.G = G;
                widget_commuter_active_cursor_style1.B = B;
                widget_commuter_active_cursor_style1.A = 255;
            }

            fscanf( pFile, "%s", line );
            //if (line == (char*) "inactivecur")
            {
                fscanf( pFile, "%d %d %d", &R, &G, &B );

                widget_commuter_inactive_cursor_style1.R = R;
                widget_commuter_inactive_cursor_style1.G = G;
                widget_commuter_inactive_cursor_style1.B = B;
                widget_commuter_inactive_cursor_style1.A = 255;
            }
        }


        fscanf( pFile, "%s", line );
        //if (line == (char*) "[COMMUTER_STYLE2]")
        {
            fscanf( pFile, "%s", line );
            //if (line == (char*) "activefill")
            {
                fscanf( pFile, "%d %d %d", &R, &G, &B );

                widget_commuter_active_filling_style2.R = R;
                widget_commuter_active_filling_style2.G = G;
                widget_commuter_active_filling_style2.B = B;
                widget_commuter_active_filling_style2.A = 255;
            }

            fscanf( pFile, "%s", line );
            //if (line == (char*) "inactivefill")
            {
                fscanf( pFile, "%d %d %d", &R, &G, &B );

                widget_commuter_inactive_filling_style2.R = R;
                widget_commuter_inactive_filling_style2.G = G;
                widget_commuter_inactive_filling_style2.B = B;
                widget_commuter_inactive_filling_style2.A = 255;
            }

            fscanf( pFile, "%s", line );
            //if (line == (char*) "activecur")
            {
                fscanf( pFile, "%d %d %d", &R, &G, &B );

                widget_commuter_active_cursor_style2.R = R;
                widget_commuter_active_cursor_style2.G = G;
                widget_commuter_active_cursor_style2.B = B;
                widget_commuter_active_cursor_style2.A = 255;
            }

            fscanf( pFile, "%s", line );
            //if (line == (char*) "inactivecur")
            {
                fscanf( pFile, "%d %d %d", &R, &G, &B );

                widget_commuter_inactive_cursor_style2.R = R;
                widget_commuter_inactive_cursor_style2.G = G;
                widget_commuter_inactive_cursor_style2.B = B;
                widget_commuter_inactive_cursor_style2.A = 255;
            }
        }


        fscanf( pFile, "%s", line );
        //if (line == (char*) "[COMMUTER_STYLE3]")
        {
            fscanf( pFile, "%s", line );
            //if (line == (char*) "activefill")
            {
                fscanf( pFile, "%d %d %d", &R, &G, &B );

                widget_commuter_active_filling_style3.R = R;
                widget_commuter_active_filling_style3.G = G;
                widget_commuter_active_filling_style3.B = B;
                widget_commuter_active_filling_style3.A = 255;
            }

            fscanf( pFile, "%s", line );
            //if (line == (char*) "inactivefill")
            {
                fscanf( pFile, "%d %d %d", &R, &G, &B );

                widget_commuter_inactive_filling_style3.R = R;
                widget_commuter_inactive_filling_style3.G = G;
                widget_commuter_inactive_filling_style3.B = B;
                widget_commuter_inactive_filling_style3.A = 255;
            }

            fscanf( pFile, "%s", line );
            //if (line == (char*) "activecur")
            {
                fscanf( pFile, "%d %d %d", &R, &G, &B );

                widget_commuter_active_cursor_style3.R = R;
                widget_commuter_active_cursor_style3.G = G;
                widget_commuter_active_cursor_style3.B = B;
                widget_commuter_active_cursor_style3.A = 255;
            }

            fscanf( pFile, "%s", line );
            //if (line == (char*) "inactivecur")
            {
                fscanf( pFile, "%d %d %d", &R, &G, &B );

                widget_commuter_inactive_cursor_style3.R = R;
                widget_commuter_inactive_cursor_style3.G = G;
                widget_commuter_inactive_cursor_style3.B = B;
                widget_commuter_inactive_cursor_style3.A = 255;
            }
        }


        fscanf( pFile, "%s", line );
        //if (line == (char*) "[COMMUTER_STYLE4]")
        {
            fscanf( pFile, "%s", line );
            //if (line == (char*) "activefill")
            {
                fscanf( pFile, "%d %d %d", &R, &G, &B );

                widget_commuter_active_filling_style4.R = R;
                widget_commuter_active_filling_style4.G = G;
                widget_commuter_active_filling_style4.B = B;
                widget_commuter_active_filling_style4.A = 255;
            }

            fscanf( pFile, "%s", line );
            //if (line == (char*) "inactivefill")
            {
                fscanf( pFile, "%d %d %d", &R, &G, &B );

                widget_commuter_inactive_filling_style4.R = R;
                widget_commuter_inactive_filling_style4.G = G;
                widget_commuter_inactive_filling_style4.B = B;
                widget_commuter_inactive_filling_style4.A = 255;
            }

            fscanf( pFile, "%s", line );
            //if (line == (char*) "activecur")
            {
                fscanf( pFile, "%d %d %d", &R, &G, &B );

                widget_commuter_active_cursor_style4.R = R;
                widget_commuter_active_cursor_style4.G = G;
                widget_commuter_active_cursor_style4.B = B;
                widget_commuter_active_cursor_style4.A = 255;
            }

            fscanf( pFile, "%s", line );
            //if (line == (char*) "inactivecur")
            {
                fscanf( pFile, "%d %d %d", &R, &G, &B );

                widget_commuter_inactive_cursor_style4.R = R;
                widget_commuter_inactive_cursor_style4.G = G;
                widget_commuter_inactive_cursor_style4.B = B;
                widget_commuter_inactive_cursor_style4.A = 255;
            }
        }


        fscanf( pFile, "%s", line );
        //if (line == (char*) "[PROGRESS_BAR]")
        {
            fscanf( pFile, "%s", line );
            //if (line == (char*) "enablefill")
            {
                fscanf( pFile, "%d %d %d", &R, &G, &B );

                widget_progressbar_enable_filling.R = R;
                widget_progressbar_enable_filling.G = G;
                widget_progressbar_enable_filling.B = B;
                widget_progressbar_enable_filling.A = 255;
            }

            fscanf( pFile, "%s", line );
            //if (line == (char*) "disablefill")
            {
                fscanf( pFile, "%d %d %d", &R, &G, &B );

                widget_progressbar_disable_filling.R = R;
                widget_progressbar_disable_filling.G = G;
                widget_progressbar_disable_filling.B = B;
                widget_progressbar_disable_filling.A = 255;
            }

            fscanf( pFile, "%s", line );
            //if (line == (char*) "rainbowempty")
            {
                fscanf( pFile, "%d %d %d", &R, &G, &B );

                widget_progressbar_rainbow_empty.R = R;
                widget_progressbar_rainbow_empty.G = G;
                widget_progressbar_rainbow_empty.B = B;
                widget_progressbar_rainbow_empty.A = 255;
            }

            fscanf( pFile, "%s", line );
            //if (line == (char*) "rainbowfull")
            {
                fscanf( pFile, "%d %d %d", &R, &G, &B );

                widget_progressbar_rainbow_full.R = R;
                widget_progressbar_rainbow_full.G = G;
                widget_progressbar_rainbow_full.B = B;
                widget_progressbar_rainbow_full.A = 255;
            }
        }


        fscanf( pFile, "%s", line );
        //if (line == (char*) "[WIDGET_FONT]")
        {
            fscanf( pFile, "%s", line );
            //if (line == (char*) "enable")
            {
                fscanf( pFile, "%d %d %d %d", &N, &T, &U, &S );

                switch (N)
                {
                case 0:
                    font_widget_text_enable.name = FontEngine::THIN_FONT;
                    break;
                case 1:
                    font_widget_text_enable.name = FontEngine::VGA_FONT;
                    break;
                case 2:
                    font_widget_text_enable.name = FontEngine::SPAC_FONT;
                    break;
                case 3:
                    font_widget_text_enable.name = FontEngine::TINY_FONT;
                    break;
                case 4:
                    font_widget_text_enable.name = FontEngine::STAN_FONT;
                    break;
                case 5:
                    font_widget_text_enable.name = FontEngine::FANT_FONT;
                    break;
                }

                switch (T)
                {
                case 1:
                    font_widget_text_enable.typo = FontEngine::Normal;
                    break;
                case 2:
                    font_widget_text_enable.typo = FontEngine::Italic;
                    break;
                case 4:
                    font_widget_text_enable.typo = FontEngine::Bold;
                    break;
                case 8:
                    font_widget_text_enable.typo = FontEngine::ItalicBold;
                    break;
                }

                switch (U)
                {
                case 1:
                    font_widget_text_enable.under = FontEngine::NoUnder;
                    break;
                case 2:
                    font_widget_text_enable.under = FontEngine::UnderSimple;
                    break;
                case 4:
                    font_widget_text_enable.under = FontEngine::UnderDouble;
                    break;
                }

                switch (S)
                {
                case 1:
                    font_widget_text_enable.strike = FontEngine::NoStrike;
                    break;
                case 2:
                    font_widget_text_enable.strike = FontEngine::StrikeSimple;
                    break;
                case 4:
                    font_widget_text_enable.strike = FontEngine::StrikeDouble;
                    break;
                }
            }

            fscanf( pFile, "%s", line );
            //if (line == (char*) "disable")
            {
                fscanf( pFile, "%d %d %d %d", &N, &T, &U, &S );

                switch (N)
                {
                case 0:
                    font_widget_text_disable.name = FontEngine::THIN_FONT;
                    break;
                case 1:
                    font_widget_text_disable.name = FontEngine::VGA_FONT;
                    break;
                case 2:
                    font_widget_text_disable.name = FontEngine::SPAC_FONT;
                    break;
                case 3:
                    font_widget_text_disable.name = FontEngine::TINY_FONT;
                    break;
                case 4:
                    font_widget_text_disable.name = FontEngine::STAN_FONT;
                    break;
                case 5:
                    font_widget_text_disable.name = FontEngine::FANT_FONT;
                    break;
                }

                switch (T)
                {
                case 1:
                    font_widget_text_disable.typo = FontEngine::Normal;
                    break;
                case 2:
                    font_widget_text_disable.typo = FontEngine::Italic;
                    break;
                case 4:
                    font_widget_text_disable.typo = FontEngine::Bold;
                    break;
                case 8:
                    font_widget_text_disable.typo = FontEngine::ItalicBold;
                    break;
                }

                switch (U)
                {
                case 1:
                    font_widget_text_disable.under = FontEngine::NoUnder;
                    break;
                case 2:
                    font_widget_text_disable.under = FontEngine::UnderSimple;
                    break;
                case 4:
                    font_widget_text_disable.under = FontEngine::UnderDouble;
                    break;
                }

                switch (S)
                {
                case 1:
                    font_widget_text_disable.strike = FontEngine::NoStrike;
                    break;
                case 2:
                    font_widget_text_disable.strike = FontEngine::StrikeSimple;
                    break;
                case 4:
                    font_widget_text_disable.strike = FontEngine::StrikeDouble;
                    break;
                }
            }

            fscanf( pFile, "%s", line );
            //if (line == (char*) "selected")
            {
                fscanf( pFile, "%d %d %d %d", &N, &T, &U, &S );

                switch (N)
                {
                case 0:
                    font_widget_text_selected.name = FontEngine::THIN_FONT;
                    break;
                case 1:
                    font_widget_text_selected.name = FontEngine::VGA_FONT;
                    break;
                case 2:
                    font_widget_text_selected.name = FontEngine::SPAC_FONT;
                    break;
                case 3:
                    font_widget_text_selected.name = FontEngine::TINY_FONT;
                    break;
                case 4:
                    font_widget_text_selected.name = FontEngine::STAN_FONT;
                    break;
                case 5:
                    font_widget_text_selected.name = FontEngine::FANT_FONT;
                    break;
                }

                switch (T)
                {
                case 1:
                    font_widget_text_selected.typo = FontEngine::Normal;
                    break;
                case 2:
                    font_widget_text_selected.typo = FontEngine::Italic;
                    break;
                case 4:
                    font_widget_text_selected.typo = FontEngine::Bold;
                    break;
                case 8:
                    font_widget_text_selected.typo = FontEngine::ItalicBold;
                    break;
                }

                switch (U)
                {
                case 1:
                    font_widget_text_selected.under = FontEngine::NoUnder;
                    break;
                case 2:
                    font_widget_text_selected.under = FontEngine::UnderSimple;
                    break;
                case 4:
                    font_widget_text_selected.under = FontEngine::UnderDouble;
                    break;
                }

                switch (S)
                {
                case 1:
                    font_widget_text_selected.strike = FontEngine::NoStrike;
                    break;
                case 2:
                    font_widget_text_selected.strike = FontEngine::StrikeSimple;
                    break;
                case 4:
                    font_widget_text_selected.strike = FontEngine::StrikeDouble;
                    break;
                }
            }

        }


        fscanf( pFile, "%s", line );
        //if (line == (char*) "[WINDOW_FONT]")
        {
            fscanf( pFile, "%s", line );
            //if (line == (char*) "enable")
            {
                fscanf( pFile, "%d %d %d %d", &N, &T, &U, &S );

                switch (N)
                {
                case 0:
                    font_window_titlebartext_enable.name = FontEngine::THIN_FONT;
                    break;
                case 1:
                    font_window_titlebartext_enable.name = FontEngine::VGA_FONT;
                    break;
                case 2:
                    font_window_titlebartext_enable.name = FontEngine::SPAC_FONT;
                    break;
                case 3:
                    font_window_titlebartext_enable.name = FontEngine::TINY_FONT;
                    break;
                case 4:
                    font_window_titlebartext_enable.name = FontEngine::STAN_FONT;
                    break;
                case 5:
                    font_window_titlebartext_enable.name = FontEngine::FANT_FONT;
                    break;
                }

                switch (T)
                {
                case 1:
                    font_window_titlebartext_enable.typo = FontEngine::Normal;
                    break;
                case 2:
                    font_window_titlebartext_enable.typo = FontEngine::Italic;
                    break;
                case 4:
                    font_window_titlebartext_enable.typo = FontEngine::Bold;
                    break;
                case 8:
                    font_window_titlebartext_enable.typo = FontEngine::ItalicBold;
                    break;
                }

                switch (U)
                {
                case 1:
                    font_window_titlebartext_enable.under = FontEngine::NoUnder;
                    break;
                case 2:
                    font_window_titlebartext_enable.under = FontEngine::UnderSimple;
                    break;
                case 4:
                    font_window_titlebartext_enable.under = FontEngine::UnderDouble;
                    break;
                }

                switch (S)
                {
                case 1:
                    font_window_titlebartext_enable.strike = FontEngine::NoStrike;
                    break;
                case 2:
                    font_window_titlebartext_enable.strike = FontEngine::StrikeSimple;
                    break;
                case 4:
                    font_window_titlebartext_enable.strike = FontEngine::StrikeDouble;
                    break;
                }
            }

            fscanf( pFile, "%s", line );
            //if (line == (char*) "disable")
            {
                fscanf( pFile, "%d %d %d %d", &N, &T, &U, &S );

                switch (N)
                {
                case 0:
                    font_window_titlebartext_disable.name = FontEngine::THIN_FONT;
                    break;
                case 1:
                    font_window_titlebartext_disable.name = FontEngine::VGA_FONT;
                    break;
                case 2:
                    font_window_titlebartext_disable.name = FontEngine::SPAC_FONT;
                    break;
                case 3:
                    font_window_titlebartext_disable.name = FontEngine::TINY_FONT;
                    break;
                case 4:
                    font_window_titlebartext_disable.name = FontEngine::STAN_FONT;
                    break;
                case 5:
                    font_window_titlebartext_disable.name = FontEngine::FANT_FONT;
                    break;
                }

                switch (T)
                {
                case 1:
                    font_window_titlebartext_disable.typo = FontEngine::Normal;
                    break;
                case 2:
                    font_window_titlebartext_disable.typo = FontEngine::Italic;
                    break;
                case 4:
                    font_window_titlebartext_disable.typo = FontEngine::Bold;
                    break;
                case 8:
                    font_window_titlebartext_disable.typo = FontEngine::ItalicBold;
                    break;
                }

                switch (U)
                {
                case 1:
                    font_window_titlebartext_disable.under = FontEngine::NoUnder;
                    break;
                case 2:
                    font_window_titlebartext_disable.under = FontEngine::UnderSimple;
                    break;
                case 4:
                    font_window_titlebartext_disable.under = FontEngine::UnderDouble;
                    break;
                }

                switch (S)
                {
                case 1:
                    font_window_titlebartext_disable.strike = FontEngine::NoStrike;
                    break;
                case 2:
                    font_window_titlebartext_disable.strike = FontEngine::StrikeSimple;
                    break;
                case 4:
                    font_window_titlebartext_disable.strike = FontEngine::StrikeDouble;
                    break;
                }
            }

        }


        fclose( pFile );
    }

}


void ThemeEngine::applytheme()
{
    if (colorhandler)
    {

        colorhandler->widget_border_enable = widget_border_enable;
        colorhandler->widget_border_disable = widget_border_disable;
        colorhandler->widget_border_cursoron = widget_border_cursoron;
        colorhandler->widget_border_hasfocus = widget_border_hasfocus;

        colorhandler->widget_tickmark_enable = widget_tickmark_enable;
        colorhandler->widget_tickmark_disable = widget_tickmark_disable;

        colorhandler->widget_filling_enable = widget_filling_enable;
        colorhandler->widget_filling_disable = widget_filling_disable;
        colorhandler->widget_selection = widget_selection;

        colorhandler->widget_text_enable = widget_text_enable;
        colorhandler->widget_text_disable = widget_text_disable;
        colorhandler->widget_text_selected = widget_text_selected;

        colorhandler->window_titlebar_enable = window_titlebar_enable;
        colorhandler->window_titlebar_disable = window_titlebar_disable;
        colorhandler->window_titlebar_minimize = window_titlebar_minimize;
        colorhandler->window_titlebar_maximize = window_titlebar_maximize;
        colorhandler->window_titlebar_restore  = window_titlebar_restore;

        colorhandler->window_titlebartext_enable = window_titlebartext_enable;
        colorhandler->window_titlebartext_disable = window_titlebartext_disable;

        colorhandler->widget_commuter_active_filling_style1 = widget_commuter_active_filling_style1;
        colorhandler->widget_commuter_inactive_filling_style1 = widget_commuter_inactive_filling_style1;
        colorhandler->widget_commuter_active_cursor_style1 = widget_commuter_active_cursor_style1;
        colorhandler->widget_commuter_inactive_cursor_style1 = widget_commuter_inactive_cursor_style1;

        colorhandler->widget_commuter_active_filling_style2 = widget_commuter_active_filling_style2;
        colorhandler->widget_commuter_inactive_filling_style2 = widget_commuter_inactive_filling_style2;
        colorhandler->widget_commuter_active_cursor_style2 = widget_commuter_active_cursor_style2;
        colorhandler->widget_commuter_inactive_cursor_style2 = widget_commuter_inactive_cursor_style2;

        colorhandler->widget_commuter_active_filling_style3 = widget_commuter_active_filling_style3;
        colorhandler->widget_commuter_inactive_filling_style3 = widget_commuter_inactive_filling_style3;
        colorhandler->widget_commuter_active_cursor_style3 = widget_commuter_active_cursor_style3;
        colorhandler->widget_commuter_inactive_cursor_style3 = widget_commuter_inactive_cursor_style3;

        colorhandler->widget_commuter_active_filling_style4 = widget_commuter_active_filling_style4;
        colorhandler->widget_commuter_inactive_filling_style4 = widget_commuter_inactive_filling_style4;
        colorhandler->widget_commuter_active_cursor_style4 = widget_commuter_active_cursor_style4;
        colorhandler->widget_commuter_inactive_cursor_style4 = widget_commuter_inactive_cursor_style4;

        colorhandler->widget_progressbar_enable_filling = widget_progressbar_enable_filling;
        colorhandler->widget_progressbar_disable_filling = widget_progressbar_disable_filling;
        colorhandler->widget_progressbar_rainbow_empty = widget_progressbar_rainbow_empty;
        colorhandler->widget_progressbar_rainbow_full = widget_progressbar_rainbow_full;

    }

    if (fonthandler)
    {

        fonthandler->widget_text_enable = font_widget_text_enable;
        fonthandler->widget_text_disable = font_widget_text_disable;
        fonthandler->widget_text_selected = font_widget_text_selected;

        fonthandler->window_titlebartext_enable = font_window_titlebartext_enable;
        fonthandler->window_titlebartext_disable = font_window_titlebartext_disable;

    }

}

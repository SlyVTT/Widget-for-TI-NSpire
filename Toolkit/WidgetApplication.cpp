#include "WidgetApplication.h"

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "CursorTask.h"
#include "KeyboardTask.h"

#include "ColorEngine.h"
#include "FontEngine.h"

#include "Widget.h"

#include <libndls.h>

#include <sys/stat.h>

#include <string>


bool is_existing( const std::string & file )
{
    struct stat buffer;
    return (stat (file.c_str(), &buffer) == 0);
}

void takescreenshot( SDL_Surface* screen )
{
    std::string namebegin = "/documents/widget/scrsh";
    std::string nameend = ".bmp.tns";
    std::string namemiddle = "000";
    bool screenshotdone = false;
    int i=0;

    do
    {
        std::string fullname = namebegin + namemiddle + nameend;
        if (!is_existing( fullname ))
        {
            SDL_SaveBMP( screen, fullname.c_str() );
            screenshotdone = true;
        }
        else
        {
            i++;
            namemiddle = std::to_string( i );
            if (namemiddle.length()==1)
            {
                namemiddle = "00" + namemiddle;
            };
            if (namemiddle.length()==2)
            {
                namemiddle = "0" + namemiddle;
            };
        }
    }
    while (!screenshotdone);
}

WidgetApplication::WidgetApplication()
{
    if(SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        printf("Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    screen = SDL_SetVideoMode(320, 240, 16, SDL_SWSURFACE);

    if(screen == NULL)
    {
        printf("Couldn't initialize display: %s\n", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    //currentfont = nSDL_LoadFont(NSDL_FONT_THIN, 0, 0, 0);

    mouse = new CursorTask();
    keyboard = new KeyboardTask();

    colors = new ColorEngine();
    colors->setdefaultcolorpreset();

    fonts = new FontEngine();
    fonts->setdefaultfontpreset();

    DesktopFeatures *maindesktop = new DesktopFeatures;
    desktops.push_back( maindesktop );
    setcurrentdesktop( 0 );
}


KeyboardTask* WidgetApplication::getkeyboardhandler()
{
    if (keyboard!=nullptr) return keyboard;
    else return nullptr;
}

CursorTask* WidgetApplication::getmousehandler()
{
    if (mouse!=nullptr) return mouse;
    else return nullptr;
}

ColorEngine* WidgetApplication::getcolorhandler()
{
    if (colors!=nullptr) return colors;
    else return nullptr;
}

FontEngine* WidgetApplication::getfonthandler()
{
    if (fonts!=nullptr) return fonts;
    else return nullptr;
}

SDL_Surface* WidgetApplication::getscreenhandler()
{
    if (screen!=NULL) return screen;
    else return nullptr;
}




WidgetApplication::~WidgetApplication()
{
    //nSDL_FreeFont( currentfont );
    SDL_FreeSurface( screen );

    delete mouse;
    delete keyboard;
    delete colors;
    delete fonts;

    for (auto& c : desktops)
    {
        if (c->background_image != nullptr) SDL_FreeSurface( c->background_image );
    }

    SDL_FreeSurface( screen );

    currentdesktop->rootwidgets.clear();

    SDL_Quit();

    printf("Exited cleanly\n");
}



void WidgetApplication::addchild( Widget *root )
{
    currentdesktop->rootwidgets.push_back( root );
}


void WidgetApplication::removechild( Widget *root )
{
    int i=0;
    for(auto& c : currentdesktop->rootwidgets )
    {
        if (c==root)
        {
            //delete currentdesktop->rootwidgets[i];
            currentdesktop->rootwidgets.erase( currentdesktop->rootwidgets.begin() + i );
            return;
        }
        i++;
    }
}

void WidgetApplication::addchildtodesktop( Widget *root, DesktopFeatures *desktop )
{
    desktop->rootwidgets.push_back( root );
}


void WidgetApplication::adddesktop( )
{
    DesktopFeatures *desktoptoadd = new DesktopFeatures;
    desktops.push_back( desktoptoadd );
    nb_desktop++;
}

void WidgetApplication::setdrawbackground( bool setter )
{
    backgroundtobedrawn = setter;
}

void WidgetApplication::removedesktop( DesktopFeatures *desktoptoremove )
{
    // to be coded here
    int i=0;
    for( auto& c : desktops)
    {
        if (c==desktoptoremove)
        {
            //delete desktops[i];
            desktops.erase( desktops.begin()+i );
            return;
        }
        i++;
    }
}

DesktopFeatures* WidgetApplication::getcurrentdesktoppointer()
{
    return desktops[cur_desktop];
}

void WidgetApplication::setcurrentdesktop( unsigned int ndesk )
{
    if (ndesk < nb_desktop)
    {
        cur_desktop = ndesk;
        currentdesktop = desktops[cur_desktop];
    }
}

int WidgetApplication::getcurrentdesktop()
{
    return cur_desktop;
}

void WidgetApplication::setnextdesktop()
{
    if (cur_desktop < nb_desktop-1)
    {
        cur_desktop++;
    }
    else
    {
        cur_desktop = 0;
    }

    currentdesktop=desktops[cur_desktop];
}

void WidgetApplication::setpreviousdesktop()
{
    if (cur_desktop > 0)
    {
        cur_desktop--;
    }
    else
    {
        cur_desktop = nb_desktop-1;
    }

    currentdesktop=desktops[cur_desktop];
}

void WidgetApplication::render( void )
{
    if (backgroundtobedrawn)
    {
        if (!currentdesktop->uniform_background && !currentdesktop->background_wallpaper) SDL_FillRect( screen, 0, 0x0000);
        if (currentdesktop->uniform_background && !currentdesktop->background_wallpaper) SDL_FillRect( screen, 0, currentdesktop->rgb_background);
        if (!currentdesktop->uniform_background && currentdesktop->background_wallpaper) SDL_BlitSurface( currentdesktop->background_image, NULL, screen, &currentdesktop->position_background);
    }

    /*    fonts->setcurrentfont( VGA_FONT );
        fonts->setmodifiertypo( Normal );
        fonts->drawstringleft( screen, "VGA Normal", 20, 10, 255, 255, 0, 255 );

        fonts->setcurrentfont( VGA_FONT );
        fonts->setmodifiertypo( Italic );
        fonts->drawstringleft( screen, "VGA Italic", 20, 20, 255, 255, 0, 255 );

        fonts->setcurrentfont( VGA_FONT );
        fonts->setmodifiertypo( Bold );
        fonts->drawstringleft( screen, "VGA Bold", 20, 30, 255, 255, 0, 255 );

        fonts->setcurrentfont( VGA_FONT );
        fonts->setmodifiertypo( ItalicBold );
        fonts->drawstringleft( screen, "VGA Italic Bold", 20, 40, 255, 255, 0, 255 );



        fonts->setcurrentfont( STAN_FONT );
        fonts->setmodifiertypo( Normal );
        fonts->drawstringleft( screen, "STAN Normal", 170, 10, 255, 0, 0, 255 );

        fonts->setcurrentfont( STAN_FONT );
        fonts->setmodifiertypo( Italic );
        fonts->drawstringleft( screen, "STAN Italic", 170, 20, 255, 0, 0, 255 );

        fonts->setcurrentfont( STAN_FONT );
        fonts->setmodifiertypo( Bold );
        fonts->drawstringleft( screen, "STAN Bold", 170, 30, 255, 0, 0, 255 );

        fonts->setcurrentfont( STAN_FONT );
        fonts->setmodifiertypo( ItalicBold );
        fonts->drawstringleft( screen, "STAN Italic Bold", 170, 40, 255, 0, 0, 255 );



        fonts->setcurrentfont( FANT_FONT );
        fonts->setmodifiertypo( Normal );
        fonts->drawstringleft( screen, "FANT Normal", 20, 60, 0, 255, 0, 255 );

        fonts->setcurrentfont( FANT_FONT );
        fonts->setmodifiertypo( Italic );
        fonts->drawstringleft( screen, "FANT Italic", 20, 70, 0, 255, 0, 255 );

        fonts->setcurrentfont( FANT_FONT );
        fonts->setmodifiertypo( Bold );
        fonts->drawstringleft( screen, "FANT Bold", 20, 80, 0, 255, 0, 255 );

        fonts->setcurrentfont( FANT_FONT );
        fonts->setmodifiertypo( ItalicBold );
        fonts->drawstringleft( screen, "FANT Italic Bold", 20, 90, 0, 255, 0, 255 );



        fonts->setcurrentfont( THIN_FONT );
        fonts->setmodifiertypo( Normal );
        fonts->drawstringleft( screen, "THIN Normal", 170, 60, 255, 0, 255, 255 );

        fonts->setcurrentfont( THIN_FONT );
        fonts->setmodifiertypo( Italic );
        fonts->drawstringleft( screen, "THIN Italic", 170, 70, 255, 0, 255, 255 );

        fonts->setcurrentfont( THIN_FONT );
        fonts->setmodifiertypo( Bold );
        fonts->drawstringleft( screen, "THIN Bold", 170, 80, 255, 0, 255, 255 );

        fonts->setcurrentfont( THIN_FONT );
        fonts->setmodifiertypo( ItalicBold );
        fonts->drawstringleft( screen, "THIN Italic Bold", 170, 90, 255, 0, 255, 255 );


        fonts->setcurrentfont( TINY_FONT );
        fonts->setmodifiertypo( Normal );
        fonts->drawstringleft( screen, "TINY Normal", 20, 110, 255, 255, 255, 255 );

        fonts->setcurrentfont( TINY_FONT );
        fonts->setmodifiertypo( Italic );
        fonts->drawstringleft( screen, "TINY Italic", 20, 120, 255, 255, 255, 255 );

        fonts->setcurrentfont( TINY_FONT );
        fonts->setmodifiertypo( Bold );
        fonts->drawstringleft( screen, "TINY Bold", 20, 130, 255, 255, 255, 255 );

        fonts->setcurrentfont( TINY_FONT );
        fonts->setmodifiertypo( ItalicBold );
        fonts->drawstringleft( screen, "TINY Italic Bold", 20, 140, 255, 255, 255, 255 );



        fonts->setcurrentfont( SPAC_FONT );
        fonts->setmodifiertypo( Normal );
        fonts->drawstringleft( screen, "SPAC Normal", 170, 110, 0, 255, 255, 255 );

        fonts->setcurrentfont( SPAC_FONT );
        fonts->setmodifiertypo( Italic );
        fonts->drawstringleft( screen, "SPAC Italic", 170, 120, 0, 255, 255, 255 );

        fonts->setcurrentfont( SPAC_FONT );
        fonts->setmodifiertypo( Bold );
        fonts->drawstringleft( screen, "SPAC Bold", 170, 130, 0, 255, 255, 255 );

        fonts->setcurrentfont( SPAC_FONT );
        fonts->setmodifiertypo( ItalicBold );
        fonts->drawstringleft( screen, "SPAC Italic Bold", 170, 140, 0, 255, 255, 255 );



        fonts->setcurrentfont( VGA_FONT );
        fonts->setmodifiertypo( Normal );
        fonts->setmodifierunder( NoUnder );
        fonts->drawstringleft( screen, "VGA No Under", 20, 160, 255, 255, 0, 255 );

        fonts->setcurrentfont( VGA_FONT );
        fonts->setmodifiertypo( Normal );
        fonts->setmodifierunder( UnderSimple );
        fonts->drawstringleft( screen, "VGA Simple Under", 20, 175, 255, 255, 0, 255 );

        fonts->setcurrentfont( VGA_FONT );
        fonts->setmodifiertypo( Normal );
        fonts->setmodifierunder( UnderDouble );
        fonts->drawstringleft( screen, "VGA Double Under", 20, 190, 255, 255, 0, 255 );



        fonts->setcurrentfont( VGA_FONT );
        fonts->setmodifiertypo( Normal );
        fonts->setmodifierunder( NoUnder );
        fonts->setmodifierstrike( NoStrike );
        fonts->drawstringleft( screen, "VGA No Strike", 170, 160, 255, 255, 0, 255 );

        fonts->setcurrentfont( VGA_FONT );
        fonts->setmodifiertypo( Normal );
        fonts->setmodifierstrike( StrikeSimple );
        fonts->drawstringleft( screen, "VGA Simple Strike", 170, 175, 255, 255, 0, 255 );

        fonts->setcurrentfont( VGA_FONT );
        fonts->setmodifiertypo( Normal );
        fonts->setmodifierstrike( StrikeDouble );
        fonts->drawstringleft( screen, "VGA Double Strike", 170, 190, 255, 255, 0, 255 );

        fonts->setmodifiertypo( Normal );
        fonts->setmodifierunder( NoUnder );
        fonts->setmodifierstrike( NoStrike );

        fonts->setcurrentfont( STAN_FONT );
        fonts->drawstringcenter( screen, "Hello STANDARD_FONT", 160, 160, 255, 0, 0, 255 );

        fonts->setcurrentfont( FANT_FONT );
        fonts->drawstringright( screen, "Hello FANTASY_FONT", 160, 170, 255, 255, 255, 255 );

        fonts->setcurrentfont( THIN_FONT );
        fonts->drawstringleft( screen, "Hello THIN_FONT", 160, 180, 255, 0, 255, 255 );

        fonts->setcurrentfont( TINY_FONT );
        fonts->drawstringcenter( screen, "Hello TINY_FONT", 160, 190, 0, 255, 0, 255 );

        fonts->setcurrentfont( SPAC_FONT );
        fonts->drawstringright( screen, "Hello SPACE_FONT", 160, 200, 0, 255, 255, 255 );
    */


    for (auto& c : currentdesktop->rootwidgets )
        c->render( screen, colors, fonts );

    mouse->render( screen );

    SDL_Flip(screen);
}

void WidgetApplication::logic( void )
{
    mouse->logic();
    keyboard->logic();

    // if an event from mouse or from keyboard is detected, we launch the render() and the children->logic() processes
    if (mouse->ismouseevent() || keyboard->iskeyevent())
    {
        render();

        for (auto& c : currentdesktop->rootwidgets )
            c->logic( mouse, keyboard );
    }


    // This is to take a screenshot to be store in the Widget folder.
    if (keyboard->kbCTRL && keyboard->kbDOT)
    {
        takescreenshot( screen );
    }

}


void WidgetApplication::logicwithforcedrender( void )
{
    mouse->logic();
    keyboard->logic();

    // render() has to be called at every loop cause it is force (this is usefull for game loop but not for usual apps.
    render();

    // if an event from mouse or from keyboard is detected, we launch the children->logic() processes
    if (mouse->ismouseevent() || keyboard->iskeyevent())
    {
        for (auto& c : currentdesktop->rootwidgets )
            c->logic( mouse, keyboard );
    }


    // This is to take a screenshot to be store in the Widget folder.
    if (keyboard->kbCTRL && keyboard->kbDOT)
    {
        takescreenshot( screen );
    }

}



void WidgetApplication::setuniformbackgroundcolor( Uint8 r, Uint8 g, Uint8 b)
{
    currentdesktop->uniform_background = true;
    currentdesktop->background_wallpaper = false;

    currentdesktop->r_background = r;
    currentdesktop->g_background = g;
    currentdesktop->b_background = b;
    currentdesktop->rgb_background = SDL_MapRGB(screen->format, currentdesktop->r_background, currentdesktop->g_background, currentdesktop->g_background);
}

void WidgetApplication::setbackgroundpicture( char *filename )
{
    currentdesktop->uniform_background = false;
    currentdesktop->background_wallpaper = true;

    currentdesktop->position_background.x = 0;
    currentdesktop->position_background.y = 0;
    currentdesktop->position_background.w = 320;
    currentdesktop->position_background.h = 240;

    currentdesktop->background_image = IMG_Load( filename );
}


void WidgetApplication::initthemeengine()
{

    theme = new ThemeEngine();
    theme->assigncolorhandler( colors );
    theme->assignfonthandler( fonts );

}

void WidgetApplication::setdefaulttheme()
{

    if (theme)
    {
        theme->setdefaulttheme();
    }
    else
    {
        colors->setdefaultcolorpreset();
        fonts->setdefaultfontpreset();
    }
}


void WidgetApplication::loadtheme( char* filename )
{
    if (theme)
    {
        theme->loadthemefromfile( filename );
        theme->applytheme();
    }
}

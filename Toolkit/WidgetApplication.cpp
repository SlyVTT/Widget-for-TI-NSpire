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


unsigned int GlobalWdidgetIDCounter;




bool is_existing( const std::string & file )
{
    struct stat buffer;
    return (stat (file.c_str(), &buffer) == 0);
}

/*
void WidgetApplication::DEBUG_draw_widget_tree_structure( char* filename )
{

    for( auto& c : currentdesktop->rootwidgets)
        c->DEBUG_draw_widget_tree_structure( 1, filename );

}
*/

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

void takescreenshotdepthbuffer( SDL_Surface* screen )
{
    std::string namebegin = "/documents/widget/dptbfr";
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

    GlobalWdidgetIDCounter = 0;


    DesktopFeatures *maindesktop = new DesktopFeatures;
    desktops.push_back( maindesktop );
    setcurrentdesktop( 0 );

    if(SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        printf("Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    maindesktop->screen = SDL_SetVideoMode(320, 240, 16, SDL_SWSURFACE);
    maindesktop->depthbuffer = SDL_CreateRGBSurface(0, 320, 240, 24, 0, 0, 0, 0);


    if(maindesktop->screen == NULL)
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
    if (currentdesktop->screen!=NULL) return currentdesktop->screen;
    else return nullptr;
}




WidgetApplication::~WidgetApplication()
{
    //nSDL_FreeFont( currentfont );
    //SDL_FreeSurface( screen );

    delete mouse;
    delete keyboard;
    delete colors;
    delete fonts;
    delete theme;

    // for each desktopfeature class
    for (auto& c : desktops)
    {
        // if we have a wallpaper, we free the associated memory
        if (c->background_image != nullptr) SDL_FreeSurface( c->background_image );

        // we free the memory corresponding to the screen and to the depthbuffer
        SDL_FreeSurface( c->screen );
        SDL_FreeSurface( c->depthbuffer );

        //for each widget in the rootwidget of the desktop feature class, we delete it to ask for the destructor
        for (auto& d : c->rootwidgets)
        {
            delete d;
        }

        // then we clear the collection
        c->rootwidgets.clear();

        //and finally we delete the desktopfeature
        delete c;
    }

    SDL_Quit();

    printf("Exited cleanly\n");
}


void WidgetApplication::putontop( Widget *widgetsearched )
{
    dynamic_cast<DesktopWidget*>(currentdesktop->rootwidgets[0])->putontop( widgetsearched );
}


void WidgetApplication::quit()
{
    //nSDL_FreeFont( currentfont );
    //SDL_FreeSurface( screen );

    delete mouse;
    delete keyboard;
    delete colors;
    delete fonts;
    delete theme;

    // for each desktopfeature class
    for (auto& c : desktops)
    {
        // if we have a wallpaper, we free the associated memory
        if (c->background_image != nullptr) SDL_FreeSurface( c->background_image );

        // we free the memory corresponding to the screen and to the depthbuffer
        SDL_FreeSurface( c->screen );
        SDL_FreeSurface( c->depthbuffer );

        //for each widget in the rootwidget of the desktop feature class, we delete it to ask for the destructor
        for (auto& d : c->rootwidgets)
        {
            delete d;
        }

        // then we clear the collection
        c->rootwidgets.clear();

        //and finally we delete the desktopfeature
        delete c;
    }

    SDL_Quit();

    printf("Exited cleanly\n");
}


void WidgetApplication::addchild( Widget *root )
{
    currentdesktop->rootwidgets.push_back( root );
    dynamic_cast<DesktopWidget*>(root)->depthbuffer=currentdesktop->depthbuffer;
    dynamic_cast<DesktopWidget*>(root)->screen=currentdesktop->screen;
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


void WidgetApplication::initiateall( void )
{
    // We need to init the theme engine, by default, this is not done at startup to save memory
    initthemeengine();
    // We apply the default theme while using theme (this is for safe use and avoid any risk of crash)
    setdefaulttheme();

    // We render the app for the first time so what we can see what's happening on the screen
    render();

    // we adjust the desktop
    for (auto&c  : currentdesktop->rootwidgets)
        c->adjust();
}


void WidgetApplication::run( unsigned mode )
{

    if (mode == 1)
        logicwithforcedrender();
    else
        logic();
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



void WidgetApplication::renderdepth( void )
{

    // We clear the depthbuffer of the current desktop
    SDL_FillRect( currentdesktop->depthbuffer, 0, 0x0000);

    // we scrutinize all the rootwidgets on the current desktop and render them in the depth buffer
    // we cannot launch a (currentdesktop->renderdepth method()) cause currentdesktop is a struct, not a widget derivative class
    // the renderdepth method is one of the widget class

    for (auto& c : currentdesktop->rootwidgets )
        if (c->isvisible()) c->renderdepth( currentdesktop->depthbuffer );


}



void WidgetApplication::render( void )
{
    if (backgroundtobedrawn)
    {
        if (!currentdesktop->uniform_background && !currentdesktop->background_wallpaper) SDL_FillRect( currentdesktop->screen, 0, 0x0000);
        if (currentdesktop->uniform_background && !currentdesktop->background_wallpaper) SDL_FillRect( currentdesktop->screen, 0, currentdesktop->rgb_background);
        if (!currentdesktop->uniform_background && currentdesktop->background_wallpaper) SDL_BlitSurface( currentdesktop->background_image, NULL, currentdesktop->screen, &currentdesktop->position_background);
    }

    for (auto& c : currentdesktop->rootwidgets )
        if (c->isvisible()) c->render( currentdesktop->screen, colors, fonts );

    mouse->render( currentdesktop->screen );

    SDL_Flip(currentdesktop->screen);
}



void WidgetApplication::logic( void )
{

    mouse->logic();
    keyboard->logic();

    // if an event from mouse or from keyboard is detected, we launch the render() and the children->logic() processes
    if (mouse->ismouseevent() || keyboard->iskeyevent())
    {
        render();
        renderdepth();

        for (auto& c : currentdesktop->rootwidgets )
            if (c->isvisible() && c->isenabled()) c->logic( mouse, keyboard );
    }

    // This is to take a screenshot to be store in the Widget folder.
    if (keyboard->kbCTRL && keyboard->kbDOT)
    {
        takescreenshot( currentdesktop->screen );
        takescreenshotdepthbuffer( currentdesktop->depthbuffer );
    }

    if (keyboard->kbCTRL && keyboard->kbSHIFT && keyboard->kbESC)
    {
        AskForClose = true;
    };

    if (keyboard->kbCTRL && keyboard->kbLEFT)
    {
        setpreviousdesktop();
        SDL_Delay( 250 );
    };

    if (keyboard->kbCTRL && keyboard->kbRIGHT)
    {
        setnextdesktop();
        SDL_Delay( 250 );
    };

    if (keyboard->kbCTRL && keyboard->kbUP)
    {
        //To be coded : shortcut for listing all the desktops and show a thumbnail
    };

}


void WidgetApplication::logicwithforcedrender( void )
{

    mouse->logic();
    keyboard->logic();


    // render() has to be called at every loop cause it is force (this is usefull for game loop but not for usual apps.
    render();
    renderdepth();

    // if an event from mouse or from keyboard is detected, we launch the children->logic() processes
//    if (mouse->ismouseevent() || keyboard->iskeyevent())
    {
        for (auto& c : currentdesktop->rootwidgets )
            c->logic( mouse, keyboard );
    }

    // This is to take a screenshot to be store in the Widget folder.
    if (keyboard->kbCTRL && keyboard->kbDOT)
    {
        takescreenshot( currentdesktop->screen );
        takescreenshotdepthbuffer( currentdesktop->depthbuffer );
    }

    if (keyboard->kbCTRL && keyboard->kbSHIFT && keyboard->kbESC)
    {
        AskForClose = true;
    };

    if (keyboard->kbCTRL && keyboard->kbLEFT)
    {
        setpreviousdesktop();
        SDL_Delay( 250 );
    };

    if (keyboard->kbCTRL && keyboard->kbRIGHT)
    {
        setnextdesktop();
        SDL_Delay( 250 );
    };

    if (keyboard->kbCTRL && keyboard->kbUP)
    {
        //To be coded : shortcut for listing all the desktops and show a thumbnail
    };

}



void WidgetApplication::setuniformbackgroundcolor( Uint8 r, Uint8 g, Uint8 b)
{
    currentdesktop->uniform_background = true;
    currentdesktop->background_wallpaper = false;

    currentdesktop->r_background = r;
    currentdesktop->g_background = g;
    currentdesktop->b_background = b;
    currentdesktop->rgb_background = SDL_MapRGB(currentdesktop->screen->format, currentdesktop->r_background, currentdesktop->g_background, currentdesktop->g_background);
}

void WidgetApplication::setbackgroundpicture( std::string filename )
{
    currentdesktop->uniform_background = false;
    currentdesktop->background_wallpaper = true;

    currentdesktop->position_background.x = 0;
    currentdesktop->position_background.y = 0;
    currentdesktop->position_background.w = 320;
    currentdesktop->position_background.h = 240;

    currentdesktop->background_image = IMG_Load( filename.c_str() );
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


void WidgetApplication::loadtheme( std::string filename )
{
    if (theme)
    {
        theme->loadthemefromfile( filename );
        theme->applytheme();
    }
}

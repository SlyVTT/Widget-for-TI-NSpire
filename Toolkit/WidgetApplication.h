#ifndef WIDGETAPPLICATION_H
#define WIDGETAPPLICATION_H

#include "Widget.h"
#include "DesktopWidget.h"

#include "CursorTask.h"
#include "KeyboardTask.h"

#include "ColorEngine.h"
#include "FontEngine.h"
#include "ThemeEngine.h"


#include <vector>


struct DesktopFeatures
{
    bool uniform_background = false;
    bool background_wallpaper = false;

    Uint8 r_background = 0;
    Uint8 g_background = 0;
    Uint8 b_background = 0;
    Uint32 rgb_background = 0;

    SDL_Surface *background_image=nullptr;
    SDL_Rect position_background;

    SDL_Surface *screen = nullptr;
    SDL_Surface *depthbuffer = nullptr;

    // This allows having multiple desktops/screens in future revisions
    std::vector< Widget* > rootwidgets;
};


class WidgetApplication
{
public:
    WidgetApplication();
    virtual ~WidgetApplication();

    //virtual void DEBUG_draw_widget_tree_structure( char* filename );

    virtual void addchild( Widget *root );
    virtual void removechild( Widget *root );

    virtual void addchildtodesktop( Widget *root, DesktopFeatures *desktop );

    virtual void adddesktop( );
    virtual void removedesktop( DesktopFeatures *desktoptoremove);
    virtual DesktopFeatures* getcurrentdesktoppointer();
    virtual void setcurrentdesktop( unsigned int ndesk );
    virtual int getcurrentdesktop();
    virtual void setnextdesktop();
    virtual void setpreviousdesktop();

    virtual void initiateall( void );
    virtual void run( unsigned mode );
    virtual void quit (void );

    virtual void render( void );
    virtual void renderdepth( void );

    virtual void putontop( Widget *widgetsearched );

    virtual void logic( void );
    virtual void logicwithforcedrender( void );

    virtual void setuniformbackgroundcolor( Uint8 r, Uint8 g, Uint8 b);
    virtual void setbackgroundpicture( std::string filename );
    virtual void setdrawbackground( bool setter );

    virtual void initthemeengine();
    virtual void setdefaulttheme();
    virtual void loadtheme( std::string filename );

    // To handle the mouse and keyboard events
    virtual KeyboardTask* getkeyboardhandler();
    virtual CursorTask* getmousehandler();
    virtual ColorEngine* getcolorhandler();
    virtual FontEngine* getfonthandler();
    virtual SDL_Surface* getscreenhandler();

    bool AskForClose = false;

protected:
    unsigned int cur_desktop = 0;
    unsigned int nb_desktop = 1;
    std::vector< DesktopFeatures* > desktops;

    DesktopFeatures* currentdesktop;

    CursorTask *mouse = nullptr;
    KeyboardTask *keyboard = nullptr;

    ColorEngine *colors = nullptr;
    FontEngine *fonts = nullptr;
    ThemeEngine *theme = nullptr;

    bool backgroundtobedrawn = true;

private:
};

#endif // WIDGETAPPLICATION_H

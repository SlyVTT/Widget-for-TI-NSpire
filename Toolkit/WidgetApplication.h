#ifndef WIDGETAPPLICATION_H
#define WIDGETAPPLICATION_H

#include "Widget.h"
#include "CursorTask.h"
#include "KeyboardTask.h"

#include "ColorEngine.h"
#include "FontEngine.h"

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

    // This allows having multiple desktops/screens in future revisions
    std::vector< Widget* > rootwidgets;
};


class WidgetApplication
{
public:
    WidgetApplication();
    virtual ~WidgetApplication();

    virtual void adddesktop( );
    virtual void removedesktop( DesktopFeatures *desktoptoremove);

    virtual void addchild( Widget *root );
    virtual void removechild( Widget *root );
    virtual void addchildtodesktop( Widget *root, DesktopFeatures *desktop );

    virtual DesktopFeatures* getcurrentdesktoppointer();
    virtual void setcurrentdesktop( unsigned int ndesk );
    virtual int getcurrentdesktop();

    virtual void setnextdesktop();
    virtual void setpreviousdesktop();

    virtual void render( void );
    virtual void logic( void );
    virtual void logicwithforcedrender( void );

    virtual void setuniformbackgroundcolor( Uint8 r, Uint8 g, Uint8 b);
    virtual void setbackgroundpicture( char *filename );
    virtual void setdrawbackground( bool setter );

    // To handle the mouse and keyboard events
    virtual KeyboardTask* getkeyboardhandler();
    virtual CursorTask* getmousehandler();
    virtual ColorEngine* getcolorhandler();
    virtual FontEngine* getfonthandler();
    virtual SDL_Surface* getscreenhandler();


protected:
    unsigned int cur_desktop = 0;
    unsigned int nb_desktop = 1;
    std::vector< DesktopFeatures* > desktops;

    DesktopFeatures* currentdesktop;

    CursorTask *mouse = nullptr;
    KeyboardTask *keyboard = nullptr;
    //nSDL_Font *currentfont = nullptr;

    ColorEngine *colors = nullptr;
    FontEngine *fonts = nullptr;

    SDL_Surface *screen = nullptr;

    bool backgroundtobedrawn = true;

private:
};

#endif // WIDGETAPPLICATION_H

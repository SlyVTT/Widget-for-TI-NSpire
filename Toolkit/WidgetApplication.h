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
        virtual void addchildtodesktop( Widget *root, DesktopFeatures *desktop );

        virtual DesktopFeatures* getcurrentdesktoppointer();
        virtual void setcurrentdesktop( int ndesk );
        virtual int getcurrentdesktop();

        virtual void setnextdesktop();
        virtual void setpreviousdesktop();

        virtual void render( void );
        virtual void logic( void );

        virtual void setuniformbackgroundcolor( Uint8 r, Uint8 g, Uint8 b);
        virtual void setbackgroundpicture( char *filename );

        // To handle the mouse and keyboard events
        CursorTask *mouse = nullptr;
        KeyboardTask *keyboard = nullptr;
        nSDL_Font *currentfont = nullptr;

        ColorEngine *colors = nullptr;
        FontEngine *fonts = nullptr;

        SDL_Surface *screen = nullptr;


    protected:
        int cur_desktop = 0;
        int nb_desktop = 1;
        std::vector< DesktopFeatures* > desktops;
        DesktopFeatures* currentdesktop;

    private:
};

#endif // WIDGETAPPLICATION_H

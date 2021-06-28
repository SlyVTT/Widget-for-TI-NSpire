#include "CursorTask.h"

//#include <libndls.h>
#include <algorithm>

#include <SDL/SDL_gfxPrimitives.h>
#include "cursors.h"



CursorTask::CursorTask()
{
    // the transparent color is define as red (note that the sprite of the cursor are defined with this convention
    Uint32 transparency = SDL_MapRGB(SDL_GetVideoSurface()->format, 255, 0, 0);

    cursor_pointer = nSDL_LoadImage(image_Arrow);
    SDL_SetColorKey(cursor_pointer, SDL_SRCCOLORKEY, transparency);

    cursor_triangle = nSDL_LoadImage(image_Triangle);
    SDL_SetColorKey(cursor_triangle, SDL_SRCCOLORKEY, transparency);

    cursor_roundclock = nSDL_LoadImage(image_Clock);
    SDL_SetColorKey(cursor_roundclock, SDL_SRCCOLORKEY, transparency);

    cursor_hourglass = nSDL_LoadImage(image_Hourglass);
    SDL_SetColorKey(cursor_hourglass, SDL_SRCCOLORKEY, transparency);

    cursor_topbottom = nSDL_LoadImage(image_TopBottomResize);
    SDL_SetColorKey(cursor_topbottom, SDL_SRCCOLORKEY, transparency);

    cursor_leftright = nSDL_LoadImage(image_LeftRightResize);
    SDL_SetColorKey(cursor_leftright, SDL_SRCCOLORKEY, transparency);

    cursor_handfinger = nSDL_LoadImage(image_HandFinger);
    SDL_SetColorKey(cursor_handfinger, SDL_SRCCOLORKEY, transparency);
}


CursorTask::~CursorTask()
{
    SDL_FreeSurface( cursor_pointer );
    SDL_FreeSurface( cursor_triangle );
    SDL_FreeSurface( cursor_roundclock );
    SDL_FreeSurface( cursor_hourglass );
    SDL_FreeSurface( cursor_topbottom );
    SDL_FreeSurface( cursor_leftright );
    SDL_FreeSurface( cursor_handfinger );
}


void CursorTask::showmouse()
{
    show=true;
};


void CursorTask::hidemouse()
{
    show=false;
};


bool CursorTask::ismousevisible()
{
    return show;
};

bool CursorTask::ismouseevent()
{
    return mouseevent;
};


bool CursorTask::ismousemoveevent()
{
    return mousemoveevent;
};


bool CursorTask::ismouseclickevent()
{
    return mouseclickevent;
};


bool CursorTask::ismousereleaseevent()
{
    return mousereleaseevent;
};


void CursorTask::setcursortype( CursorTask::cursortype type )
{
    cursor = type;
}


void CursorTask::logic()
{
    if(!show)
        return;

    touchpad_report_t touchpad;
    touchpad_scan(&touchpad);

    state = touchpad_arrow_pressed(TPAD_ARROW_CLICK);

    // Check for events linked to mouse click (clicked or released or unchanged=no event)
    if (!mouseclickevent && state)
    {
        mouseclickevent = true;
        mousereleaseevent = false;
    }

    if (mouseclickevent && !state)
    {
        mouseclickevent = false;
        mousereleaseevent = true;
    }

    if ((mouseclickevent && state) || (mousereleaseevent && !state))
    {
        mouseclickevent = false;
        mousereleaseevent = false;
    }

    int dx = 0, dy = 0;
    static bool tp_last_contact = touchpad.contact;
    if(touchpad.contact && !touchpad.pressed)
    {
        static int tp_last_x = touchpad.x;
        static int tp_last_y = touchpad.y;

        if(tp_last_contact)
        {
            dx = (touchpad.x - tp_last_x) / 10;
            dy = (tp_last_y - touchpad.y) / 10;
        }

        tp_last_x = touchpad.x;
        tp_last_y = touchpad.y;
        tp_last_contact = touchpad.contact;
    }
    else
    {
        tp_last_contact = false;
    }


    x+=dx;
    y+=dy;

    // this block the cursor at the side of the screen
    if (x<0)
    {
        x=0;
    };
    if (y<0)
    {
        y=0;
    };
    if (x>=320)
    {
        x=320;
    };
    if (y>=240)
    {
        y=240;
    };


    // The following code allow the mouse cursor to roll from top to bottom or left to right (and vice versa) when reaching the limit of the screen
    // this creates bug when we are resizing a window, so we need to skip this feature
    /*if (x<0)
    {
        x+=320;
    };
    if (y<0)
    {
        y+=240;
    };
    if (x>=320)
    {
        x-=320;
    };
    if (y>=240)
    {
        y-=240;
    };
    */



    // check for mouse move
    if ((dx != 0) || (dy !=0))
    {
        mousemoveevent = true;
    }
    else
    {
        mousemoveevent = false;
    }

    // check if something new has happen with the mouse (either click/release or cursor move)
    if (mouseclickevent || mousereleaseevent || mousemoveevent)
    {
        mouseevent = true;
    }
    else
    {
        mousemoveevent = false;
    }

}


void CursorTask::render( SDL_Surface *screen )
{
    if(!show)
        return;

    SDL_Rect src_rect, screen_pos;
    src_rect.x = 0;
    src_rect.y = 0;
    src_rect.w = 20;
    src_rect.h = 20;


    if (cursor == pointer)
    {
        screen_pos.x = x;
        screen_pos.y = y;
        SDL_BlitSurface(cursor_pointer, &src_rect, screen, &screen_pos);
    }

    if (cursor == triangle)
    {
        screen_pos.x = x;
        screen_pos.y = y;
        SDL_BlitSurface(cursor_triangle, &src_rect, screen, &screen_pos);
    }

    if (cursor == roundclock)
    {
        screen_pos.x = x-10;
        screen_pos.y = y-10;
        SDL_BlitSurface(cursor_roundclock, &src_rect, screen, &screen_pos);
    }

    if (cursor == hourglass)
    {
        screen_pos.x = x-10;
        screen_pos.y = y-10;
        SDL_BlitSurface(cursor_hourglass, &src_rect, screen, &screen_pos);
    }

    if (cursor == leftrightresize)
    {
        screen_pos.x = x-10;
        screen_pos.y = y-10;
        SDL_BlitSurface(cursor_leftright, &src_rect, screen, &screen_pos);
    }

    if (cursor == topbottomresize)
    {
        screen_pos.x = x-10;
        screen_pos.y = y-10;
        SDL_BlitSurface(cursor_topbottom, &src_rect, screen, &screen_pos);
    }

    if (cursor == handfinger)
    {
        screen_pos.x = x-5;
        screen_pos.y = y-5;
        SDL_BlitSurface(cursor_handfinger, &src_rect, screen, &screen_pos);
    }


}

/*

    if (cursor == triangle)
    {
        //Draw the simple mouse cursor
        filledTrigonRGBA( screen, x, y, x+6, y+12, x+12, y+6, 255, 255, 255, 255);
        trigonRGBA( screen, x, y, x+6, y+12, x+12, y+6, 255, 0, 0, 255);
    }
    if (cursor == roundclock)
    {
        //Draw the clock mouse cursor
        filledCircleRGBA( screen, x+6, y+6, 6, 255, 255, 255, 255 );
        circleRGBA( screen, x+6, y+6, 6, 255, 0, 0, 255 );
        circleRGBA( screen, x+6, y+6, 5, 255, 0, 0, 255 );

        lineRGBA( screen, x+6, y+6, x+6, y+1, 255, 0, 0, 255 );
        lineRGBA( screen, x+6, y+6, x+8, y+4, 255, 0, 0, 255 );
    }
    if (cursor == leftrightresize)
    {
        //Draw a double arrow cursor oriented left/right
        filledTrigonRGBA( screen, x-6, y, x-3, y-5, x-3, y+5, 255, 255, 255, 255);
        trigonRGBA( screen, x-6, y, x-3, y-5, x-3, y+5, 255, 0, 0, 255);

        filledTrigonRGBA( screen, x+6, y, x+3, y-5,  x+3, y+5, 255, 255, 255, 255);
        trigonRGBA( screen, x+6, y, x+3, y-5,  x+3, y+5, 255, 0, 0, 255);

        boxRGBA( screen, x-3, y-2, x+3, y+2, 255, 255, 255, 255);
        lineRGBA( screen, x-3, y-2, x+3, y-2, 255, 0, 0, 255);
        lineRGBA( screen, x-3, y+2, x+3, y+2, 255, 0, 0, 255);
    }
    if (cursor == topbottomresize)
    {
        //Draw a double arrow cursor oriented top/bottom
        filledTrigonRGBA( screen, x-5, y-3, x, y-6, x+5, y-3, 255, 255, 255, 255);
        trigonRGBA( screen, x-5, y-3, x, y-6, x+5, y-3, 255, 0, 0, 255);

        filledTrigonRGBA( screen, x-5, y+3, x, y+6, x+5, y+3, 255, 255, 255, 255);
        trigonRGBA( screen, x-5, y+3, x, y+6, x+5, y+3, 255, 0, 0, 255);

        boxRGBA( screen, x-2, y-3, x+2, y+3, 255, 255, 255, 255);
        lineRGBA( screen, x-2, y-3, x-2, y+3, 255, 0, 0, 255);
        lineRGBA( screen, x+2, y-3, x+2, y+3, 255, 0, 0, 255);
    }

}
*/

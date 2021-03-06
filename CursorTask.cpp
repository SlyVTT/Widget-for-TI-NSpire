#include "CursorTask.h"

#include <libndls.h>
#include <algorithm>

#include <SDL/SDL_gfxPrimitives.h>


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

    // This is the initial code from Vogtinator
	//x = std::max<unsigned int>({0, dx + x});
	//y = std::max<unsigned int>({0, dy + y});
	//x = std::min<unsigned int>({x, SCREEN_WIDTH});
	//y = std::min<unsigned int>({y, SCREEN_HEIGHT});


    // The following code allow the mouse cursor to roll from top to bottom or left to right (and vice versa) when reaching the limit of the screen
	x+=dx;
	y+=dy;
	if (x<0) { x+=320; };
	if (y<0) { y+=240; };
	if (x>=320) { x-=320; };
	if (y>=240) { y-=240; };


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

    //Draw the simple mouse cursor
    filledTrigonRGBA( screen, x, y, x+6, y+12, x+12, y+6, 255, 255, 255, 255);
    trigonRGBA( screen, x, y, x+6, y+12, x+12, y+6, 255, 0, 0, 255);
}

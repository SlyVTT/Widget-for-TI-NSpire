#include "DesktopWidget.h"

#include "FontEngine.h"

#include <vector>

/*
 * Return the pixel value at (x, y)
 * NOTE: The surface must be locked before calling this!
 */
Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp)
    {
    case 1:
        return *p;

    case 2:
        return *(Uint16 *)p;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;

    case 4:
        return *(Uint32 *)p;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}


unsigned int DesktopWidget::getuseablexpos()
{
    return 0;
}


unsigned int DesktopWidget::getuseableypos()
{
    if (!hasmenubar && !hasiconbar) return 0;                    // we just remove 2px on top
    if (hasmenubar && !hasiconbar) return 0 + 12;           // we remove the 2px on top and of the menu bar (2px + 12px)
    if (hasmenubar && hasiconbar) return 0 + 12 + 20;       // we remove the 2px on top, of the menu bar and of the icon bar (2px + 12px + 20px)
    if (!hasmenubar && hasiconbar) return 0 + 20;           // we remove the 2px on top, of the menu bar and of the icon bar (2px + 12px + 20px)

    // the following return is to avoir warning, all possible cases are given above
    return 0;

}


unsigned int DesktopWidget::getuseablewidth()
{
    return width - 0;
}


unsigned int DesktopWidget::getuseableheight()
{
    if (!hasmenubar && !hasiconbar) return SCREEN_HEIGHT - 0;                     // we just remove 2px on top and bottom (2px + 2px = 4px)
    if (hasmenubar && !hasiconbar) return SCREEN_HEIGHT - 0 - 12;            // we remove 2px on top and bottom and of the menu bar (4px + 12px)
    if (hasmenubar && hasiconbar) return SCREEN_HEIGHT - 0 - 12 - 20;        // we remove 2px on top and bottom, of the menu bar and of the icon bar (4px + 12px + 20px)
    if (!hasmenubar && hasiconbar) return SCREEN_HEIGHT - 0 - 20;            // we remove 2px on top and bottom, of the menu bar and of the icon bar (4px + 12px + 20px)

    // the following return is to avoir warning, all possible cases are given above
    return 0;
}



void DesktopWidget::logic( CursorTask *mouse, KeyboardTask *keyboard )
{

    if (mouse->state || keyboard->kbSCRATCH)
    {

        Uint8 r,g,b;
        SDL_LockSurface( depthbuffer);
        SDL_GetRGB(getpixel(depthbuffer, mouse->x, mouse->y), depthbuffer->format, &r, &g, &b);
        SDL_UnlockSurface( depthbuffer );


        unsigned int c = (r-(r%25))/25;
        unsigned int d = (g-(g%25))/25;
        unsigned int u = (b-(b%25))/25;

        unsigned int widgetIDpicked = 100*c + 10*d + u;

        /*
                // THIS IS FOR DEBUGGING THE DEPTH BUFFER PORTION OF THE CODE

                char* tempID;
                sprintf( tempID, "ID = %ld", widgetIDpicked );
                fonttemp->setcurrentfont( THIN_FONT );
                fonttemp->setmodifiertypo( Bold );
                unsigned int length=fonttemp->getstringwidth( tempID );
                boxRGBA( screen, mouse->x, mouse->y, mouse->x+length, mouse->y+10, 0, 0, 0, 255 );
                fonttemp->drawstringleft( screen, tempID, mouse->x, mouse->y, 0, 255, 0, 255 );

                SDL_Flip(screen);
        */

        putontop( widgetIDpicked );
    }


    for (auto& c : children )
        c->logic( mouse, keyboard );
}

void DesktopWidget::render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts )
{
    for (auto& c : children )
        c->render( screen, colors, fonts );
}


void DesktopWidget::putontop( unsigned int widgetidsearched )
{
    // we desactivate all the children

    std::list<Widget *>::iterator it=children.begin();

    for( auto& c : children )
    {

        if ((c->WidgetID==widgetidsearched) && (!c->islocked()))
        {
            /*
                        boxRGBA( screen, 5, 230, 150, 240, 0, 0, 0, 255 );
                        fonttemp->drawstringleft( screen, (char*) "Found children", 6, 231, 0, 0, 255, 255 );
                        SDL_Flip(screen);
            */
            c->activate();
            Widget* temp = c;

            children.erase( it );

            children.push_back( temp );
            return;

        }
        else if ((c->WidgetID==widgetidsearched) && (c->islocked()))
        {
            /*
                        boxRGBA( screen, 5, 230, 150, 240, 0, 0, 0, 255 );
                        fonttemp->drawstringleft( screen, (char*) "Found lock", 6, 231, 0, 0, 255, 255 );
                        SDL_Flip(screen);
            */
            c->desactivate();
        }
        else
        {
            /*
                        boxRGBA( screen, 5, 230, 150, 240, 0, 0, 0, 255 );
                        fonttemp->drawstringleft( screen, (char*) "Not found children", 6, 231, 0, 0, 255, 255 );
                        SDL_Flip(screen);
            */
            c->desactivate();
        }

        it++;
    }
}


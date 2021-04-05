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

    switch(bpp) {
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


        // THIS IS FOR DEBUGGING THE DEPTH BUFFER PORTION OF THE CODE
        char* tempID;
        sprintf( tempID, "ID = %d", widgetIDpicked );
        fonttemp->setcurrentfont( THIN_FONT );
        fonttemp->setmodifiertypo( Bold );
        unsigned int length=fonttemp->getstringwidth( tempID );
        boxRGBA( screen, mouse->x, mouse->y, mouse->x+length, mouse->y+10, 0, 0, 0, 255 );
        fonttemp->drawstringleft( screen, tempID, mouse->x, mouse->y, 0, 255, 0, 255 );

        SDL_Flip(screen);

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
    for( unsigned int c=0; c < children.size(); c++ )
    {
        if ((children.at(c)->WidgetID==widgetidsearched) && (!children.at(c)->islocked()))
        {

            boxRGBA( screen, 5, 230, 150, 240, 0, 0, 0, 255 );
            fonttemp->drawstringleft( screen, "Found children", 6, 231, 0, 0, 255, 255 );
            SDL_Flip(screen);

            children.at(c)->activate();
            Widget* temp= children.at(c);

            children.erase( children.begin() + c );

            children.push_back( temp );

        }
        else if ((children.at(c)->WidgetID==widgetidsearched) && (children.at(c)->islocked()))
        {
            boxRGBA( screen, 5, 230, 150, 240, 0, 0, 0, 255 );
            fonttemp->drawstringleft( screen, "Found lock", 6, 231, 0, 0, 255, 255 );
            SDL_Flip(screen);

            children.at(c)->desactivate();
        }
        else
        {
            boxRGBA( screen, 5, 230, 150, 240, 0, 0, 0, 255 );
            fonttemp->drawstringleft( screen, "Not found children", 6, 231, 0, 0, 255, 255 );
            SDL_Flip(screen);

            children.at(c)->desactivate();

        }
    }
}


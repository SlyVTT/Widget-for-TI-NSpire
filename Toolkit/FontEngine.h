#ifndef FONTENGINE_H
#define FONTENGINE_H

#include <vector>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

struct FontChar
{
    int charwidth;
    int charheight;
    unsigned short *chardata;       // Should allow 4bytes coding (i.e. font up to 32x32 with only minimum changes in loading procedure
};

struct FontData
{
    char fontname[25];
    int numberchar;
    std::vector <FontChar*> Font;
};

enum fontname
{
    THIN_FONT = 0,
    VGA_FONT = 1,
    SPAC_FONT = 2,
    TINY_FONT = 3,
    STAN_FONT = 4,
    FANT_FONT = 5,
};

enum fontmodifiertypo
{
    Normal = 1,
    Italic = 2,
    Bold = 4,
    ItalicBold = 8,
};

enum fontmodifierunder
{
    NoUnder = 1,
    UnderSimple = 2,
    UnderDouble = 4,
};

enum fontmodifierstrike
{
    NoStrike = 1,
    StrikeSimple = 2,
    StrikeDouble = 4,
};

class FontEngine
{
    public:
        FontEngine();
        virtual ~FontEngine();

        virtual void loadfontfromfile( char *filename );
        static FontData* loadfontfromfilepointer( char *filename );

        virtual int getstringwidth( char *str );
        virtual int getstringheight( char *str );

        virtual int getcharwidth( char str );
        virtual int getcharheight( char str );

        virtual void setcurrentfont( fontname curfont ); // To be checked for internam parameters
        virtual void setspacing( int hspace, int vspace );
        virtual void setmodifiertypo( fontmodifiertypo mod );
        virtual void setmodifierunder( fontmodifierunder mod );
        virtual void setmodifierstrike( fontmodifierstrike mod );

        virtual void drawstringleft( SDL_Surface *screen, char *str, int x, int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A );
        virtual void drawcharleft( SDL_Surface *screen, char str, int x, int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A );

        virtual void drawstringcenter( SDL_Surface *screen, char *str, int x, int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A );
        virtual void drawcharcenter( SDL_Surface *screen, char str, int x, int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A );

        virtual void drawstringright( SDL_Surface *screen, char *str, int x, int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A );
        virtual void drawcharright( SDL_Surface *screen, char str, int x, int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A );


    protected:
        FontData *currentfont = nullptr;
        fontmodifiertypo currentmodifiertypo;
        fontmodifierunder currentmodifierunder;
        fontmodifierstrike currentmodifierstrike;

        std::vector <FontData*> FontCollection;
        int vspacing = 0;
        int hspacing = 0;

    private:
};

#endif // FONTENGINE_H

#ifndef FONTENGINE_H
#define FONTENGINE_H

#include <vector>
#include <string>

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

struct fontset
{
    fontname name;
    fontmodifiertypo typo;
    fontmodifierunder under;
    fontmodifierstrike strike;
};


class FontEngine
{
public:
    FontEngine();
    virtual ~FontEngine();



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

    struct fontset
    {
        fontname name;
        fontmodifiertypo typo;
        fontmodifierunder under;
        fontmodifierstrike strike;
    };



    virtual void loadfontfromfile( std::string filename );
    static FontData* loadfontfromfilepointer( std::string filename );



    virtual unsigned int assertstringlength( char *str, unsigned int width );
    virtual unsigned int assertstringlength( std::string str, unsigned int width );
    virtual unsigned int assertstringlength( std::string str, unsigned int width, fontname name, fontmodifiertypo typo, fontmodifierunder under, fontmodifierstrike strike );

    virtual std::string reducestringtovisible( std::string str, unsigned int width );
    virtual std::string reducestringtovisible( std::string str, unsigned int width, fontname name, fontmodifiertypo typo, fontmodifierunder under, fontmodifierstrike strike );

    virtual void setcurrentfont( fontname curfont ); // To be checked for internam parameters
    virtual void setspacing( int hspace, int vspace );
    virtual void setmodifiertypo( fontmodifiertypo mod );
    virtual void setmodifierunder( fontmodifierunder mod );
    virtual void setmodifierstrike( fontmodifierstrike mod );

    virtual unsigned int getstringwidth( char *str );
    virtual unsigned int getstringheight( char *str );
    virtual unsigned int getcharwidth( char str );
    virtual unsigned int getcharheight( char str );

    virtual int gethspacing();
    virtual int getvspacing();

    virtual void drawstringleft( SDL_Surface *screen, char *str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A );
    virtual void drawcharleft( SDL_Surface *screen, char str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A );
    virtual void drawstringcenter( SDL_Surface *screen, char *str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A );
    virtual void drawcharcenter( SDL_Surface *screen, char str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A );
    virtual void drawstringright( SDL_Surface *screen, char *str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A );
    virtual void drawcharright( SDL_Surface *screen, char str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A );

    virtual unsigned int getstringwidth( std::string str );
    virtual unsigned int getstringheight( std::string str );
    virtual void drawstringleft( SDL_Surface *screen, std::string str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A );
    virtual void drawstringcenter( SDL_Surface *screen, std::string str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A );
    virtual void drawstringright( SDL_Surface *screen, std::string str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A );


    /// Method for assigning default font shemes to the FontEngine.
    ///
    /// To be used to assign the default font scheme the FontEngine.
    virtual void setdefaultfontpreset( );


    /// Default font names used by the widgets to be rendered.
    ///
    /// To be used only for developping new Widget and keeping a coherency with the look and feel of the other widgets.
    /// Using these default name permits to have a global theming for an application.
    fontset widget_text_enable;
    fontset widget_text_disable;
    fontset widget_text_selected;

    fontset window_titlebartext_enable;
    fontset window_titlebartext_disable;



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

#include "FontEngine.h"

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>


FontEngine::FontEngine()
{
    this->loadfontfromfile( (char*) "/documents/widget/Fonts/THIN.WFE.tns" );
    this->loadfontfromfile( (char*) "/documents/widget/Fonts/VGA.WFE.tns" );
    this->loadfontfromfile( (char*) "/documents/widget/Fonts/SPACE.WFE.tns" );
    this->loadfontfromfile( (char*) "/documents/widget/Fonts/TINY.WFE.tns" );
    this->loadfontfromfile( (char*) "/documents/widget/Fonts/STANDARD.WFE.tns" );
    this->loadfontfromfile( (char*) "/documents/widget/Fonts/FANTASY.WFE.tns" );
    this->setcurrentfont( THIN_FONT );
    vspacing = 0;
    hspacing = -1;
    currentmodifiertypo = Normal;  // set text as normal
    currentmodifierunder = NoUnder; // No underlining
    currentmodifierstrike = NoStrike; // No striking
}

FontEngine::~FontEngine()
{
    //dtor
    for (auto& c : FontCollection )
    {
        for(auto& f : c->Font)
        {
            free( f->chardata );
        }
        delete c;
    }
    //delete FontCollection;
}

FontData* FontEngine::loadfontfromfilepointer( char* filename )
{

    FILE* pFile;
    pFile = fopen (filename,"r");
    if (pFile!=NULL)
    {
        //bool flag = true;
        char line[20];
        //int value=0;
        int width, height, temp;
        //char p0[2], p1[2], p2[2], p3[2], p4[2], p5[2], p6[2], p7[2];
        char valstr[10];

        FontData *tempFont = new FontData;

        {
            fscanf( pFile, "%s", line );    // Should read "Name"
            fscanf( pFile, "%s", tempFont->fontname );

            fscanf( pFile, "%s", line );    // Should read "Width"
            fscanf( pFile, "%d", &width );

            fscanf( pFile, "%s", line );    // Should read "Height"
            fscanf( pFile, "%d", &height );

            fscanf( pFile, "%s", line );    // Should read "CharNumber"
            fscanf( pFile, "%d", &temp );
            tempFont->numberchar = temp;

            fscanf( pFile, "%s", line );    // Should read "Data"

            for (int j = 0; j<tempFont->numberchar; j++)
            {
                FontChar *tempChar = new FontChar;
                tempChar->charwidth = width;
                tempChar->charheight = height;

                tempChar->chardata = (unsigned short *) malloc( height * sizeof( unsigned short ) );

                for (int i = 0; i < height; i++)
                {
                    // we read the hexadecimal value in the file
                    fscanf( pFile, "%s", valstr );

                    // we check how many characters has the Hexa value (F->1; FF->2, FFF->3, FFFF->4) (max is 4 bytes)
                    int length = strlen( valstr );
                    int nbvalue=0;
                    char digit;

                    for(int k = 0; k<length; k++)
                    {
                        digit=valstr[ k ];
                        int digitint=0;
                        switch(digit)
                        {
                        case '0' :
                            digitint=0;
                            break;
                        case '1' :
                            digitint=1;
                            break;
                        case '2' :
                            digitint=2;
                            break;
                        case '3' :
                            digitint=3;
                            break;

                        case '4' :
                            digitint=4;
                            break;
                        case '5' :
                            digitint=5;
                            break;
                        case '6' :
                            digitint=6;
                            break;
                        case '7' :
                            digitint=7;
                            break;

                        case '8' :
                            digitint=8;
                            break;
                        case '9' :
                            digitint=9;
                            break;
                        case 'A' :
                            digitint=10;
                            break;
                        case 'B' :
                            digitint=11;
                            break;

                        case 'C' :
                            digitint=12;
                            break;
                        case 'D' :
                            digitint=13;
                            break;
                        case 'E' :
                            digitint=14;
                            break;
                        case 'F' :
                            digitint=15;
                            break;
                        }

                        nbvalue += (digitint << ((length-k-1)*4));
                    }

                    tempChar->chardata[i] = nbvalue;

                }

                tempFont->Font.push_back( tempChar );
            }
        }

        fclose(pFile);

        return tempFont;
    }

    return nullptr;

}

void FontEngine::loadfontfromfile( char* filename )
{

    FILE* pFile;
    pFile = fopen (filename,"r");
    if (pFile!=NULL)
    {
        //bool flag = true;
        char line[20];
        //int value=0;
        int width, height, temp;
        //char p0[2], p1[2], p2[2], p3[2], p4[2], p5[2], p6[2], p7[2];
        char valstr[10];

        FontData *tempFont = new FontData;

        {
            fscanf( pFile, "%s", line );    // Should read "Name"
            fscanf( pFile, "%s", tempFont->fontname );

            fscanf( pFile, "%s", line );    // Should read "Width"
            fscanf( pFile, "%d", &width );

            fscanf( pFile, "%s", line );    // Should read "Height"
            fscanf( pFile, "%d", &height );

            fscanf( pFile, "%s", line );    // Should read "CharNumber"
            fscanf( pFile, "%d", &temp );
            tempFont->numberchar = temp;

            fscanf( pFile, "%s", line );    // Should read "Data"

            for (int j = 0; j<tempFont->numberchar; j++)
            {
                FontChar *tempChar = new FontChar;
                tempChar->charwidth = width;
                tempChar->charheight = height;

                tempChar->chardata = (unsigned short *) malloc( height * sizeof( unsigned short ) );

                for (int i = 0; i < height; i++)
                {
                    // we read the hexadecimal value in the file
                    fscanf( pFile, "%s", valstr );

                    // we check how many characters has the Hexa value (F->1; FF->2, FFF->3, FFFF->4) (max is 4 bytes)
                    int length = strlen( valstr );
                    int nbvalue=0;
                    char digit;

                    for(int k = 0; k<length; k++)
                    {
                        digit=valstr[ k ];
                        int digitint=0;
                        switch(digit)
                        {
                        case '0' :
                            digitint=0;
                            break;
                        case '1' :
                            digitint=1;
                            break;
                        case '2' :
                            digitint=2;
                            break;
                        case '3' :
                            digitint=3;
                            break;

                        case '4' :
                            digitint=4;
                            break;
                        case '5' :
                            digitint=5;
                            break;
                        case '6' :
                            digitint=6;
                            break;
                        case '7' :
                            digitint=7;
                            break;

                        case '8' :
                            digitint=8;
                            break;
                        case '9' :
                            digitint=9;
                            break;
                        case 'A' :
                            digitint=10;
                            break;
                        case 'B' :
                            digitint=11;
                            break;

                        case 'C' :
                            digitint=12;
                            break;
                        case 'D' :
                            digitint=13;
                            break;
                        case 'E' :
                            digitint=14;
                            break;
                        case 'F' :
                            digitint=15;
                            break;
                        }

                        nbvalue += (digitint << ((length-k-1)*4));
                    }

                    tempChar->chardata[i] = nbvalue;

                }

                tempFont->Font.push_back( tempChar );
            }
        }

        fclose(pFile);

        FontCollection.push_back( tempFont );
    }

}

unsigned int FontEngine::getstringwidth( char *str )
{
    int length = (int) strlen( str );
    int posx = 0;

    for(int i=0; i< length-1; i++)
    {
        posx += currentfont->Font[str[i]]->charwidth + hspacing;
    }
    posx +=currentfont->Font[str[length-1]]->charwidth; // for the alst character we do not add the spacing

    return posx;
}

// this is for monoline text, does not take into consideration \n character yet
unsigned int FontEngine::getstringheight( char *str )
{
    int length = (int) strlen( str );
    int posy = 0;


    for(int i=0; i< length; i++)
    {
        if( currentfont->Font[str[i]]->charheight > posy)
            posy = currentfont->Font[str[i]]->charheight;
    }

    return posy;

}

unsigned int FontEngine::getcharwidth( char str )
{
    return currentfont->Font[str]->charwidth;
}

unsigned int FontEngine::getcharheight( char str )
{
    return currentfont->Font[str]->charheight;
}


unsigned int FontEngine::assertstringlength( char *str, unsigned int width )
{

    unsigned int lengthstr = getstringwidth( str );
    char returnstr[100];

    unsigned int nbchartotal = (unsigned int) strlen( str );

    if (width >= lengthstr)
    {
        return nbchartotal;
    }
    else
    {
        strcpy( returnstr, str );
        for( unsigned int i=nbchartotal; i>1; i-- )
        {
            returnstr[i-1]='\0';
            lengthstr = getstringwidth( returnstr );
            if (width >= lengthstr) return i;
        }
    }

    return 0;
}


void FontEngine::setcurrentfont( fontname curfont ) // To be checked for internam parameters
{
    currentfont = FontCollection[ curfont ];
}

void FontEngine::setspacing( unsigned int hspace, unsigned int vspace )
{
    hspacing = hspace;
    vspacing = vspace;
}

void FontEngine::setmodifiertypo( fontmodifiertypo mod )
{
    currentmodifiertypo = mod;
}

void FontEngine::setmodifierunder( fontmodifierunder mod )
{
    currentmodifierunder = mod;
}

void FontEngine::setmodifierstrike( fontmodifierstrike mod )
{
    currentmodifierstrike = mod;
}

void FontEngine::drawstringleft( SDL_Surface *screen, char *str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A )
{

    int length = (int) strlen( str );
    int posx = x;
    int posy = y;

    for(int i=0; i< length; i++)
    {
        drawcharleft( screen, str[i], posx, posy, R, G, B, A );
        posx += currentfont->Font[str[i]]->charwidth + hspacing;
    }
}

void FontEngine::drawcharleft( SDL_Surface *screen, char str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A )
{
    FontChar *temp = currentfont->Font[str];

    for (int j=0; j<temp->charheight; j++)
    {
        int mask = 1;
        for (int i=0; i<temp->charwidth; i++)
        {
            if ((temp->chardata[j] & (mask << i)) != 0)
            {

                if ((currentmodifiertypo & Normal) !=0 )
                {
                    // text is Normal
                    pixelRGBA( screen, x+temp->charwidth-i-1, y+j, R, G, B, A);
                }
                if ((currentmodifiertypo & Italic) !=0 )
                {
                    // text is Italic but not Bold
                    int shift = (int) ((temp->charheight-1-j)/4);
                    pixelRGBA( screen, x+temp->charwidth-i-1+shift, y+j, R, G, B, A);
                }
                if ((currentmodifiertypo & Bold) !=0 )
                {
                    // text is Bold but not Italic
                    pixelRGBA( screen, x+temp->charwidth-i-1, y+j, R, G, B, A);
                    pixelRGBA( screen, x+temp->charwidth-i, y+j, R, G, B, A);
                }
                if ((currentmodifiertypo & ItalicBold) !=0 )
                {
                    // text is Italic and Bold
                    int shift = (int) ((temp->charheight-1-j)/4);
                    pixelRGBA( screen, x+temp->charwidth-i-1+shift, y+j, R, G, B, A);
                    pixelRGBA( screen, x+temp->charwidth-i+shift, y+j, R, G, B, A);
                }

            }
        }
    }

    if ((currentmodifierunder & NoUnder) !=0 )
    {
        // text is not underlined
    }
    if ((currentmodifierunder & UnderSimple) !=0 )
    {
        // text is underlined with one single line
        lineRGBA( screen, x-1, y+temp->charheight+2, x+temp->charwidth+1, y+temp->charheight+2, R, G, B, A );
    }
    if ((currentmodifierunder & UnderDouble) !=0 )
    {
        // text is underlined with two lines
        lineRGBA( screen, x-1, y+temp->charheight+2, x+temp->charwidth+1, y+temp->charheight+2, R, G, B, A );
        lineRGBA( screen, x-1, y+temp->charheight+4, x+temp->charwidth+1, y+temp->charheight+4, R, G, B, A );
    }




    if ((currentmodifierstrike & NoStrike) !=0 )
    {
        // text is not underlined
    }
    if ((currentmodifierstrike & StrikeSimple) !=0 )
    {
        // text is underlined with one single line
        lineRGBA( screen, x-1, (int) (y+temp->charheight/2), x+temp->charwidth+1, (int) (y+temp->charheight/2), R, G, B, A );
    }
    if ((currentmodifierstrike & StrikeDouble) !=0 )
    {
        // text is underlined with two lines
        lineRGBA( screen, x-1, (int) (y+temp->charheight/2)-1, x+temp->charwidth+1, (int) (y+temp->charheight/2)-1, R, G, B, A );
        lineRGBA( screen, x-1, (int) (y+temp->charheight/2)+1, x+temp->charwidth+1, (int) (y+temp->charheight/2)+1, R, G, B, A );
    }


}

void FontEngine::drawstringcenter( SDL_Surface *screen, char *str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A )
{
    int dx = (int) (getstringwidth( str ) / 2);
    drawstringleft( screen, str, x-dx, y, R, G, B, A);
}

void FontEngine::drawcharcenter( SDL_Surface *screen, char str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A )
{
    int dx = (int) (getcharwidth( str ) / 2);
    drawcharleft( screen, str, x-dx, y, R, G, B, A);
}

void FontEngine::drawstringright( SDL_Surface *screen, char *str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A )
{
    int dx = (int) getstringwidth( str );
    drawstringleft( screen, str, x-dx, y, R, G, B, A);
}

void FontEngine::drawcharright( SDL_Surface *screen, char str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A )
{
    int dx = (int) getcharwidth( str );
    drawcharleft( screen, str, x-dx, y, R, G, B, A);
}

void FontEngine::setdefaultfontpreset( )
{

    widget_text_enable = { THIN_FONT, Normal, NoUnder, NoStrike };
    widget_text_disable = { THIN_FONT, Normal, NoUnder, NoStrike };
    widget_text_selected = { THIN_FONT, Normal, NoUnder, NoStrike };

    window_titlebartext_enable = { THIN_FONT, Bold, NoUnder, NoStrike };
    window_titlebartext_disable = { THIN_FONT, Bold, NoUnder, NoStrike };

}

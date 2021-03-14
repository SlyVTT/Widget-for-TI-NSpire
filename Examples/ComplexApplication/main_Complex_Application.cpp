/*
 *            JUST DO WHATEVER THE FUCK YOU WANNA DO PUBLIC LICENSE
 *                         Version 1, January 2013
 *
 *   Copyright (C) 2013 Christoffer Rehn <crehn@outlook.com>
 *
 *   Everyone is permitted to copy and distribute verbatim or modified copies
 * of this license document, and changing it is allowed.
 *
 *          JUST DO WHATEVER THE FUCK YOU WANNA DO PUBLIC LICENSE
 *     TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 *
 *   0. Just do whatever the fuck you wanna do. Seriously.
 */

 /*
 *  This is the Ndless Link SDL example slightly changed to demonstrate how the Gui Toolkit for nSpire can be used in usual SDL programs without major changes
 */

// We need to add the Toolkit main include file
#include  "Toolkit/GUIToolkit.h"

// this is coming from the Link example, no change, not that SDL.h can be removed cause already part of the Toolkit included files
#include <os.h>
#include <SDL/SDL.h>

#include "link.h"
#include "map1.h"


SDL_Surface *screen;
nSDL_Font *font;
SDL_bool done = SDL_FALSE;
int num_moves = 0;
player_t player;
map_t map;


/*
 * The init() procedure can be removed cause the rendering surface (screen) will be given by the toolkit
 *

void init(void) {
    if(SDL_Init(SDL_INIT_VIDEO) == -1) {
        printf("Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    screen = SDL_SetVideoMode(320, 240, has_colors ? 16 : 8, SDL_SWSURFACE);
    if(screen == NULL) {
        printf("Couldn't initialize display: %s\n", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    SDL_ShowCursor(SDL_DISABLE);
}

*/

void quit(void) {
    SDL_FreeSurface(player.sprite);
    SDL_FreeSurface(map.tileset);

    // the SDL_Quit is managed by the Toolkit destructor, so no need to be added here
    // SDL_Quit();
}

void init_player(int x, int y, dir_t direction, SDL_Surface *sprite) {
    SDL_SetColorKey(sprite,
                    SDL_SRCCOLORKEY | SDL_RLEACCEL,
                    SDL_MapRGB(sprite->format, 255, 0, 255));
    player.x = x;
    player.y = y;
    player.direction = direction;
    player.sprite = sprite;
}

void init_map(char **data,
              int width, int height,
              int num_tiles,
              SDL_Surface *tileset,
              tile_attrib_t *tile_attrib) {
    map.data = data;
    map.width = width;
    map.height = height;
    map.num_tiles = num_tiles;
    map.tileset = tileset;
    map.tile_attrib = tile_attrib;
}

/* This function isn't actually used, but if BMP images were used, load_bmp()
   would load the BMP image and convert it to an optimized format (read: same
   pixel format as the display). */
SDL_Surface *load_bmp(const char *file) {
    SDL_Surface *tmp, *image;
    tmp = SDL_LoadBMP(file);
    if(tmp == NULL)
        return NULL;
    image = SDL_DisplayFormat(tmp);
    SDL_FreeSurface(tmp);
    return image;
}

void draw_tile(SDL_Surface *tileset, int tile_num, int x, int y) {
    SDL_Rect src_rect, screen_pos;
    src_rect.x = tile_num * TILE_WIDTH;
    src_rect.y = 0;
    src_rect.w = TILE_WIDTH;
    src_rect.h = TILE_HEIGHT;
    screen_pos.x = x * TILE_WIDTH;
    screen_pos.y = y * TILE_HEIGHT;
    SDL_BlitSurface(tileset, &src_rect, screen, &screen_pos);
}

void draw_player(void) {
    draw_tile(player.sprite, (int)player.direction, player.x, player.y);
}

void draw_tile_map(void) {
    int i, j;
    for(i = 0; i < map.height; ++i)
        for(j = 0; j < map.width; ++j)
            draw_tile(map.tileset, map.data[i][j] - 'A', j, i);
}

void draw_info(void) {
    SDL_Rect rect = {0, 224, 320, 16};
    SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 32, 0, 0));
    nSDL_DrawString(screen, font, 4, 228, "Moves: %d", num_moves);
    nSDL_DrawString(screen, font,
                    SCREEN_WIDTH - nSDL_GetStringWidth(font, "nSDL " NSDL_VERSION) - 4, 228,
                    "nSDL " NSDL_VERSION);
}

SDL_bool is_walkable(int x, int y) {
    return map.tile_attrib[(int)map.data[y][x] - 'A'].is_walkable;
}

void move_player(dir_t direction) {
    if(player.direction == direction) {
        int prev_x = player.x;
        int prev_y = player.y;
        switch(direction) {
            case UP:
                --player.y;
                break;
            case DOWN:
                ++player.y;
                break;
            case LEFT:
                --player.x;
                break;
            case RIGHT:
                ++player.x;
                break;
        }
        if(!is_walkable(player.x, player.y)) {
            player.x = prev_x;
            player.y = prev_y;
        } else
            ++num_moves;
    } else
        player.direction = direction;
}

void handle_keydown(SDLKey key) {
    switch(key) {
        case SDLK_UP:
            move_player(UP);
            break;
        case SDLK_DOWN:
            move_player(DOWN);
            break;
        case SDLK_LEFT:
            move_player(LEFT);
            break;
        case SDLK_RIGHT:
            move_player(RIGHT);
            break;
        case SDLK_KP_ENTER: /* This corresponds to the "click button" on the TI-Nspire. */
        case SDLK_RETURN:
            if(player.x == 14 && player.y == 8 && player.direction == UP)
                num_moves = 1337;
            break;
        case SDLK_ESCAPE:
            done = SDL_TRUE;
            break;
        default:
            break;
    }
}


int main ( int argc, char** argv )
{

    WidgetApplication *MyApp = new WidgetApplication();
    MyApp->setuniformbackgroundcolor(0, 155, 255);
    MyApp->setdrawbackground( false );

    // the following call to the init() fucntion has to be rewritten to get a rendering context
    //init();

    // this is done by a call the the right method of MyApp
    screen = MyApp->getscreenhandler();



    /* quit() takes care of freeing the next two images. */
    init_player(10, 7, DOWN, nSDL_LoadImage(image_link));
    init_map(map1_data, MAP1_WIDTH, MAP1_HEIGHT, MAP1_NUM_TILES,
             nSDL_LoadImage(image_tileset), map1_tile_attrib);
    if (player.sprite == NULL || map.tileset == NULL)
        return EXIT_FAILURE;
    font = nSDL_LoadFont(NSDL_FONT_TINYTYPE, 255, 255, 255);
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);


    /*
     * this is the new part of the program which create the GUI Tollokit stuff
     */

    // We create the main window with automatic positioning feature
    WindowWidget *window = new WindowWidget( "LINK with GUI Toolkit", 40, 70, 240, 100, nullptr );
    ContainerVWidget *containerv = new ContainerVWidget( "container", 1, 1, 1, 1, window );
    LabelWidget *label = new LabelWidget( "This is a small PoC for using", 1, 1, 1, 1, containerv );
    label->setalignment( centered );
    LabelWidget *label2 = new LabelWidget( "the GUI Toolkit for TI nSpire", 1, 1, 1, 1, containerv );
    label->setalignment( centered );
    LabelWidget *label3 = new LabelWidget( "in a program using the SDL lib.", 1, 1, 1, 1, containerv );
    label->setalignment( centered );
    ButtonWidget *buttonQuit = new ButtonWidget( "Quit this Application [CTRL+ESC]", 1, 1, 1, 1, containerv );
    window->adjust();

    window->setinvisible();

    MyApp->addchild( window );

    MyApp->render();

    // we ask for a handler to the mouse stuff for hiding the mouse uppon request
    CursorTask* mouse = MyApp->getmousehandler();
    mouse->setcursortype( triangle );   // We set the cursor type
    mouse->hidemouse();                 // We hide the cursor during the play sequence

    // we ask for a keyboard handler to track some specific key pressed
    KeyboardTask* keys = MyApp->getkeyboardhandler();

    // this boolean looks if the window is visible
    bool winvisible;


    // this is the normal game loop

    // The loop condition must also look to the click on the button of the toolkit
    // while(!done)
    while (!buttonQuit->ispressed() && !done)
    {
        // this is the usual SDL keyboard handlet, We keep it as initially written, but we can use the keyborad handler
        // this is just to show that changes are minimal and that SDL keybord and App keyboard can be used simultaneously
        SDL_Event event;
        draw_tile_map();
        draw_player();
        draw_info();
        //SDL_Flip(screen);

        // we need to do the App logic
        MyApp->logicwithforcedrender();
        winvisible = window->isvisible();

        if (keys->kbCTRL && keys->kbESC) done = SDL_TRUE;

        if (keys->kbMENU && (winvisible==false))
        {
            window->setvisible();
            mouse->showmouse();
            SDL_Delay( 300 );
        }

        if (keys->kbMENU && (winvisible==true))
        {
            window->setinvisible();
            mouse->hidemouse();
            SDL_Delay( 300 );
        }

        // we just replace the SDL_WaitEvent that is blocking the system by SDL_PollEvent
        //SDL_WaitEvent(&event);
        SDL_PollEvent( &event );


        switch(event.type) {
            case SDL_KEYDOWN:
                handle_keydown(event.key.keysym.sym);
                break;
            default:
                break;
        }
    }
    nSDL_FreeFont(font);
    quit();
    return EXIT_SUCCESS;

}

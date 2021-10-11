from sdl2 import *
from ctypes import byref
import atexit

from polycal4 import KEY_NONE, KEY_LEFT, KEY_UP, KEY_DOWN, KEY_RIGHT, \
    KEY_ENTER, KEY_ESC, KEY_LEFT_PARENTHESIS, KEY_RIGHT_PARENTHESIS

window   = None
renderer = None
texture  = None

pause_on_quit = False

def polycalc_pc_init(width=0, height=0, scale=1):
    if SDL_Init(SDL_INIT_VIDEO) < 0:
        raise Exception("Failed to initialize SDL")
    dm = SDL_DisplayMode()
    SDL_GetCurrentDisplayMode(0, byref(dm))

    global window
    global renderer
    global texture
    global screen_w, screen_h, SCALE
    if width <= 0: width = dm.w // SCALE
    if height <= 0: height = dm.h // SCALE
    screen_w, screen_h, SCALE = width, height, scale
    window = SDL_CreateWindow("Polycalc SDL2".encode(),
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width*SCALE, height*SCALE, SDL_WINDOW_SHOWN)

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_TARGET, width, height)

    if window is None or renderer is None or texture is None:
        raise Exception("Failed to create either window, renderer or texture")

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, b'0')
    SDL_SetRenderTarget(renderer, texture)

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255)
    SDL_RenderClear(renderer)

    atexit.register(polycalc_pc_quit)

def poly_clean_screen():
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255)
    SDL_RenderClear(renderer)

def poly_set_pixel(x, y, color):
    SDL_SetRenderDrawColor(renderer, *color, 255)
    SDL_RenderDrawPoint(renderer, x, y)

def poly_show():
    global renderer
    global texture

    SDL_SetRenderTarget(renderer, None)
    SDL_RenderSetScale(renderer, SCALE, SCALE)

    SDL_RenderCopy(renderer, texture, None, None)
    SDL_RenderPresent(renderer)

    SDL_SetRenderTarget(renderer, texture)
    SDL_RenderSetScale(renderer, 1, 1)

def poly_sdl2_screenshot(scale=-1, fname=None):
    global renderer
    global texture

    if scale == -1:
        scale = SCALE
    w = screen_w * scale
    h = screen_h * scale

    if fname == None:
        fname = b"poly_sdl2_screenshot.bmp"
    fname = bytes(fname)

    surface = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0)

    SDL_SetRenderTarget(renderer, None)
    SDL_RenderSetScale(renderer, scale, scale)

    SDL_RenderReadPixels(renderer, None, 0, surface.contents.pixels,
        surface.contents.pitch)
    SDL_SaveBMP(surface, fname)

    SDL_SetRenderTarget(renderer, texture)
    SDL_RenderSetScale(renderer, 1, 1)

def poly_pause():
    event = SDL_Event()
    while 1:
        SDL_WaitEvent(event)
        if event.type == SDL_KEYDOWN:
            break
        if event.type == SDL_QUIT:
            raise SystemExit

def poly_fill_rect(x, y, w, h, color):
    SDL_SetRenderDrawColor(renderer, *color, 255)
    SDL_RenderFillRect(renderer, SDL_Rect(x, y, w, h))

_keys = {
    KEY_LEFT: (SDLK_LEFT, SDL_SCANCODE_LEFT),
    KEY_UP: (SDLK_UP, SDL_SCANCODE_UP),
    KEY_DOWN: (SDLK_DOWN, SDL_SCANCODE_DOWN),
    KEY_RIGHT: (SDLK_RIGHT, SDL_SCANCODE_RIGHT),
    KEY_ENTER: (SDLK_RETURN, SDL_SCANCODE_RETURN),
    KEY_ESC: (SDLK_ESCAPE, SDL_SCANCODE_ESCAPE),
    KEY_LEFT_PARENTHESIS: (SDLK_LEFTPAREN, SDL_SCANCODE_5),
    KEY_RIGHT_PARENTHESIS: (SDLK_RIGHTPAREN, SDL_SCANCODE_MINUS),
}

def poly_wait_key():
    event = SDL_Event()
    while 1:
        SDL_WaitEvent(event)
        if event.type == SDL_KEYDOWN:
            for key, value in _keys.items():
                if event.key.keysym.sym == value[0]:
                    return key

def poly_test_key(key):
    st = SDL_GetKeyboardState(None)
    return st[_keys[key][1]] != 0

def poly_get_key():
    for key in _keys:
        if poly_test_key(key):
            return key
    return KEY_NONE

def polycalc_pc_quit():
    global window
    global renderer
    global texture

    poly_show()

    if pause_on_quit:
        poly_pause()

    SDL_SetRenderTarget(renderer, None)
    SDL_DestroyTexture(texture)
    SDL_DestroyRenderer(renderer)
    SDL_DestroyWindow(window)
    SDL_Quit()

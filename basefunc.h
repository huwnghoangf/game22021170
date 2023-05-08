#ifndef BASE_FUNC_H_
#define BASE_FUNC_H_

using namespace std;
#include <windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>


static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

//screen
const int SCREEN_WIDTH =810;
const int SCREEN_HEIGHT=810;
const int SCREEN_BPP =32;

const int COLOR_KEY_R=255;
const int COLOR_KEY_G=255;
const int COLOR_KEY_B=255;

const int RENDER_DRAW_COLOR = 0xff;

#define TILE_SIZE 90

#define MAX_MAP_X 9
#define MAX_MAP_Y 9
 struct MAP
{
    int start_x_;
    int start_y_;

    int max_x_;
    int max_y_;

    int tile[MAX_MAP_Y][MAX_MAP_X];
    char* file_name_;
};

#endif
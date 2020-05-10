#ifndef Game_hpp
#define Game_hpp

#include<bits/stdc++.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>
#include<mpg123.h>
#include<png.h>
#include"TextureLoader.hpp"
#include"Birds.hpp"
#include"PlayerPipe.hpp"
#include <unistd.h>
#include"support.hpp"
#include<SDL2/SDL_ttf.h>
#include<freetype2/ft2build.h>

class Game
{
private:
    unsigned char r = 255, g = 0, b = 0;

    bool redDown = false, redUp = false;
    bool greenDown = false, greenUp = false;
    bool blueDown = false, blueUp = false;
    int memex = -400;
    
    bool isStarted = false;
    bool isRunning;
    SDL_Window *window;

    SDL_Color introColor;
    SDL_Color titleColor;
    SDL_Color ptColor = {255, 255, 255};
    SDL_Color diffColor = {0, 0, 0};
    SDL_Color haxColor = {255, 0, 0};

    SDL_Rect title_rect;
    SDL_Rect font_rect;
    SDL_Rect pt_rect;
    SDL_Rect diff_rect;
    SDL_Rect hax_rect;

    int difficulty = 1;
public:
    Game(/* args */);
    ~Game();

    void init(const char *title, int xpos, int ypos, int width, int height, bool opt_fs);
    bool loadbmp(std::string path);
    void render();
    void update();
    void cleanup();
    void event_handler();
    bool running() {return isRunning;};
    void updatergb();

    int randomNumber(int max_val){std::srand(std::time(NULL)); return std::rand()%max_val;};

    static SDL_Renderer *renderer;
    static SDL_Event event;

    static int cnt; 

    static Mix_Chunk* smashfx;

    bool cheat_mode = false;
};

#endif
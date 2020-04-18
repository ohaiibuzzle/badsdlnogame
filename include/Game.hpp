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

class Game
{
private:
    bool isRunning;
    SDL_Window *window;
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

    int randomNumber(int max_val){std::srand(std::time(NULL)); return std::rand()%max_val;};

    static SDL_Renderer *renderer;
    static SDL_Event event;

    static int cnt; 
};

#endif
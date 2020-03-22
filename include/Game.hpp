#ifndef Game_hpp
#define Game_hpp

#include<bits/stdc++.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<png.h>

using namespace std;

class Game
{
private:
    bool isRunning;
    SDL_Window *window;
    static SDL_Renderer *renderer;
    int cnt;
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
};

#endif
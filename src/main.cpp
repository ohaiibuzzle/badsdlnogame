#include"Game.hpp"


Game *game = nullptr;

int main(int argc, const char * argv[]){

    const int fps = 60;
    const int delay = 1000 / fps;

    Uint32 frameStart;
    Uint32 frameTime;

    
    game = new Game();

    game -> init("Hello, World!", 0, 0, 800, 640, false);

    while (game -> running()){
        frameStart = SDL_GetTicks();


        game -> event_handler();
        game -> update();
        game -> render();

        frameTime = SDL_GetTicks() - frameStart;

        if (delay > frameTime){
            SDL_Delay(delay - frameTime);
        }
    }

    game -> cleanup();

    return 0;
}
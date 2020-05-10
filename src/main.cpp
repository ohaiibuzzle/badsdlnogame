#include"Game.hpp"
using namespace std;

Game *game = nullptr;

int main(int argc, const char * argv[]){

    const int fps = 60;
    const int delay = 1000 / fps;

    Uint32 frameStart;
    Uint32 frameTime;

    
    game = new Game();

    game -> init("Is this a game?", 500, 250, 800, 640, false);

    try
    {
        if (support::decodedata(argv[1]).substr(0, support::decodedata(argv[1]).size()-2) == support::encodedata("QnV6emxlIGlzIGN1dGUK").substr(0, support::encodedata("QnV6emxlIGlzIGN1dGUK").size()-2))
        {
            game -> cheat_mode = true;
            cout << "HAX MODE ON!" << endl;
        }
    }
    catch(const std::exception& e)
    {
        cout << "Starting game normally..." << endl;
    }
    

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
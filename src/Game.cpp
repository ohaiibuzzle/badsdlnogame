#include "Game.hpp"
#include "DVD.hpp"
#include "GameObject.hpp"

SDL_Event Game::event;

SDL_Renderer* Game::renderer = nullptr;

SDL_Texture* background = nullptr;

SDL_Rect dest;

DVD* DVD_object;

playerPipe* pipes;

vector<Birds*> all_birds;

int Game::cnt = 0;

Game::Game()
{
}

Game::~Game()
{}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool opt_fs){
    int flags = 0;
    if(opt_fs)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        std::cout << "It works!" << std::endl;
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (window)
        {
            std::cout << "Window up!" << std::endl;
            isRunning = true;
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (renderer)
                {  
                    std::cout << "Renderer up!" << std::endl;
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    
                }
            else
                {
                    printf("Things happened: %s \n", SDL_GetError());
                    isRunning = false;
                }
        }
        else
        {
                printf("Things happened: %s \n", SDL_GetError());
                isRunning = false;
        }
    }
    else
    {
        printf("Things happened: %s \n", SDL_GetError());
    }
    
    DVD_object = new DVD();

    background = TextureLoader::Loader("assets/bg.png");
    dest.w = 800;
    dest.h = 640;
    dest.x = dest.y = 0;

    pipes = new playerPipe(600, -75, 150);

    srand(time(NULL));

    for(int i = 0; i < rand()%20; i++){
        all_birds.push_back(new Birds(std::rand()%200, std::rand()%640));
    }
}

void Game::render(){
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, background, NULL, &dest);
    DVD_object->render();
    pipes->render();
    for_each(all_birds.begin(), all_birds.end(), mem_fun(&Birds::render));
    
    //TODO
    SDL_RenderPresent(renderer);
};

void Game::update(){
    DVD_object->update();
    pipes -> update();
    for_each(all_birds.begin(), all_birds.end(), bind2nd(mem_fun(&Birds::update), pipes->getHeight()));
    for_each(all_birds.begin(), all_birds.end(), bind2nd(mem_fun(&Birds::check_collision), pipes -> getRectUp()));
    for_each(all_birds.begin(), all_birds.end(), bind2nd(mem_fun(&Birds::check_collision), pipes -> getRectDown()));
    for (auto i = 0; i != all_birds.size(); i++)
    {
        if (all_birds[i]->check_defeat()) isRunning=false;
        cout << "Curr. Point:" << cnt << endl;
    }
    if(rand() % 99*60 == 0) for_each(all_birds.begin(), all_birds.end(), mem_fun(&Birds::increase_speed));
}

void Game::event_handler(){
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT){
        isRunning = false;
    }
    else if (event.type == SDL_KEYDOWN){
        switch (event.key.keysym.sym)
        {
        case (SDLK_ESCAPE):
            isRunning = false;
            break;
        case (SDLK_g):
            pipes->startSmashing();
            break;
        default:
            break;
        }
    }
};

void Game::cleanup(){
    std::cout << "Now Cleaning Up!" << std::endl;
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Done!" << std::endl;
}
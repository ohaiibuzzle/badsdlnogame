#include "Game.hpp"
#include "TextureLoader.hpp"
#include "GameObject.hpp"

GameObject* bird;

SDL_Renderer* Game::renderer = nullptr;

Game::Game()
{
    cnt = 0;
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
    
    bird = new GameObject("assets/bird2.png", renderer, 0, 0);

    std::cout << "Application init successful!" << std::endl;

};

void Game::render(){
    SDL_RenderClear(renderer);

    bird->ObjRender();

    //TODO
    SDL_RenderPresent(renderer);
};

void Game::update(){
    bird->ObjUpdate();

    cnt++;
    std::cout << cnt << std::endl;
};
void Game::event_handler(){
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;
    
    default:
        break;
    }
};

void Game::cleanup(){
    std::cout << "Now Cleaning Up!" << std::endl;
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Done!" << std::endl;
}
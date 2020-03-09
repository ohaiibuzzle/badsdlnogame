#include<bits/stdc++.h>
#include<SDL2/SDL.h>

using namespace std;

const int WIDTH = 640;
const int HEIGHT = 480;


int main(){
    SDL_Window* window = NULL;
    
    SDL_Surface* screenSurface = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        cout << "Error while initializing SDL! Quitting!" << endl;
        return 0;
    }
    else{
        window = SDL_CreateWindow("Hello, World!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL){
            cout << "Errow creating window" << endl;
            return 0;
        }
        else{
            screenSurface = SDL_GetWindowSurface(window);
            SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format,0xFF, 0xFF, 0xFF));
            SDL_UpdateWindowSurface(window);
            SDL_Delay(2000);
            SDL_DestroyWindow(window);
            SDL_Quit();
            return 0;
        }
    }
}
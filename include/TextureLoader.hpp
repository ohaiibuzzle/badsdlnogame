#pragma once
#include"Game.hpp"

//using namespace std;

class TextureLoader{
    public:
        static SDL_Texture* Loader(const char* file);
        static void DrawTexture(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
        static SDL_Surface* sfLoader(const char* file);
};
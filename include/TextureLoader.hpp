#pragma once
#include"Game.hpp"

//using namespace std;

class TextureLoader{
    public:
        static SDL_Texture* Loader(const char* file);
};
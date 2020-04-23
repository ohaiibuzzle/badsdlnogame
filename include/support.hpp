#pragma once
#include"Game.hpp"

class support
{
public:

    static std::string intText(int a);
    static std::string formatScore(int scr);

    static SDL_Texture* displayFont(std::string text, std::string path, int size, SDL_Color color);

};
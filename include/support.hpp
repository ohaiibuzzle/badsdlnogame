#pragma once
#include"Game.hpp"
#include<b64/decode.h>
#include<b64/encode.h>

class support
{
public:

    static std::string intText(int a);
    static std::string formatScore(int scr);

    static SDL_Texture* displayFont(std::string text, std::string path, int size, SDL_Color color);

    static std::string encodedata(std::string inp);
    static std::string decodedata(std::string inp);
    static std::string toString(const char* inp);
};
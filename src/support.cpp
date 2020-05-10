#include"support.hpp"

using namespace std;

string support::intText(int a){
    stringstream ss;
    ss << a;
    return ss.str();
}

string support::formatScore(int scr){
    return "You managed to score " + intText(scr) + " points";
}

SDL_Texture* support::displayFont(string text, string path, int size, SDL_Color color){
    if (TTF_Init() == 0)
    {
        SDL_Surface* tmpSf = nullptr;
        SDL_Texture* txt = nullptr;
        TTF_Font* font = TTF_OpenFont(path.c_str(), size);
        if((tmpSf=TTF_RenderText_Blended(font,text.c_str(),color))) 
        {
            txt = SDL_CreateTextureFromSurface(Game::renderer, tmpSf);
        } 
        else   
        {
            printf("Something happened: %s", TTF_GetError());
            throw "Font Error!";
            return txt;
        }
        TTF_CloseFont(font);
        SDL_FreeSurface(tmpSf);
        return txt;
    }
    else
    {
        printf("Something happened: %s", TTF_GetError());
        throw "Font Error!";
        return nullptr;
    }
}

string support::encodedata(string inp)
{
    base64::encoder E;
    stringstream in, out;
    in << inp;
    E.encode(in, out);
    return out.str();
}

string support::decodedata(string inp)
{
    base64::decoder E;
    stringstream in, out;
    in << inp;
    E.decode(in, out);
    return out.str();
}

static string toString(const char* inp)
{
    stringstream in;
    in << inp;
    return in.str();
}
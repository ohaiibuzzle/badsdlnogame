#include "TextureLoader.hpp"
using namespace std;

SDL_Texture* TextureLoader::Loader(const char* file, SDL_Renderer *renderer)
{
    int im_flag = IMG_INIT_PNG;
    if ((IMG_Init(im_flag) & im_flag)){
        SDL_Surface* tmpSf = IMG_Load(file);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,tmpSf);
        SDL_FreeSurface(tmpSf);
        printf("Successfully Load: %s", file);
        return texture;
        
    } 
    else
    {
        printf("Error loading texture %s: %s", file, IMG_GetError());
        SDL_Texture* notex;
        return notex;
    }
    
}
#include "TextureLoader.hpp"
using namespace std;

SDL_Texture* TextureLoader::Loader(const char* file)
{
    int im_flag = IMG_INIT_PNG;
    if ((IMG_Init(im_flag) & im_flag)){
        SDL_Surface* tmpSf = IMG_Load(file);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer,tmpSf);
        SDL_FreeSurface(tmpSf);
        printf("Successfully Load: %s \n", file);
        IMG_Quit();
        return texture;
        
    } 
    else
    {
        printf("Error loading texture %s: %s", file, IMG_GetError());
        throw "TXT_LOAD_ERROR";
    }
    
}
void TextureLoader::DrawTexture(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest){
    SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}

SDL_Surface* TextureLoader::sfLoader(const char* file)
{
    int im_flag = IMG_INIT_PNG;
    if ((IMG_Init(im_flag) & im_flag)){
        SDL_Surface* Sf = IMG_Load(file);
        IMG_Quit();
        return Sf;
    }
    else
    {
        printf("Error loading texture %s: %s", file, IMG_GetError());
        throw "TXT_LOAD_ERROR";
    }
}
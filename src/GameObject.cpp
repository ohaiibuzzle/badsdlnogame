#include"GameObject.hpp"
#include"TextureLoader.hpp"

GameObject::GameObject(const char* texpath, SDL_Renderer* ren, int x, int y)
{
    renderer = ren;
    objTexture = TextureLoader::Loader(texpath, ren);

    xpos = x;
    ypos = y;
}

void GameObject::ObjUpdate(){
    xpos++;
    ypos++;

    srcRect.h = 64;
    srcRect.w = 64;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = srcRect.w;
    destRect.h = srcRect.h;
}

void GameObject::ObjRender(){
    SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}
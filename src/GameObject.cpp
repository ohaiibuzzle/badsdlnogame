#include"GameObject.hpp"
#include"TextureLoader.hpp"

GameObject::GameObject(const char* texpath, int x, int y)
{
    renderer = Game::renderer;
    objTexture = TextureLoader::Loader(texpath);

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
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}
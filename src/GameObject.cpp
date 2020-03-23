#include"GameObject.hpp"
#include"TextureLoader.hpp"

GameObject::GameObject(const char* texpath, int x, int y)
{
    renderer = Game::renderer;
    objTexture = TextureLoader::Loader(texpath);

    xpos = x;
    ypos = y;
}

void GameObject::ObjUpdate()
{
    xpos++;

    srcRect.h = 320;
    srcRect.w = 320;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = srcRect.w / 5;
    destRect.h = srcRect.h / 5;
}

void GameObject::ObjRender(){
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}
#include "Birds.hpp"

Birds::Birds(int posx, int posy)
{
    birdMidTex = TextureLoader::Loader("assets/birdMid.png");
    birdUpTex = TextureLoader::Loader("assets/birdUp.png");
    birdDownTex = TextureLoader::Loader("assets/birdDown.png");

    renderTex = birdMidTex;

    src.x = src.y = 0;
    src.w = 204;
    src.h = 146;

    dest.h = 40;
    dest.w = 30;
    dest.x = posx;
    dest.y = posy;

}

Birds::~Birds(){
    SDL_DestroyTexture(birdUpTex);
    SDL_DestroyTexture(birdDownTex);
    SDL_DestroyTexture(renderTex);
}

void Birds::render(){
    SDL_RenderCopy(Game::renderer, renderTex, &src, &dest);
}

void Birds::update(int height){
    if (dest.y > height - rand() % 150){
        renderTex = birdUpTex;
        flyUp();
        return;
    }
    renderTex = birdDownTex;
    dest.y += gravity + rand() % 4;
    dest.x += speed + rand() %2;
}

void Birds::flyUp(){
    dest.y -= rand()%jump;
}

bool Birds::check_defeat(){
    if (dest.x > 600 + 90) return true;
    else return false;
}

void Birds::increase_speed()
{
    speed++;
}

void Birds::decrease_speed()
{
    speed--;
}

bool Birds::check_collision(SDL_Rect pipeRect){
    if (((SDL_HasIntersection(&dest, &pipeRect) && SDL_TRUE)==SDL_TRUE)){
        dest.x = rand()%200;
        Game::cnt++;
        return true;
    }
    else return false;
}

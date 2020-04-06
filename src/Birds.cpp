#include "Birds.hpp"

Birds::Birds(int posx, int posy)
{
    birdTex = TextureLoader::Loader("assets/bird.png");

    src.x = src.y = 0;
    src.w = 204;
    src.h = 146;

    dest.h = 40;
    dest.w = 30;
    dest.x = posx;
    dest.y = posy;

}

void Birds::render(){
    SDL_RenderCopy(Game::renderer, birdTex, &src, &dest);
}

void Birds::update(int height){
    if (dest.y > height - rand() % 200){
        flyUp();
    }
    dest.y += gravity + rand() % 3;
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

bool Birds::check_collision(SDL_Rect pipeRect){
    if (((SDL_HasIntersection(&dest, &pipeRect) && SDL_TRUE)==SDL_TRUE)){
        dest.x = rand()%200;
        Game::cnt++;
        return true;
    }
    else return false;
}

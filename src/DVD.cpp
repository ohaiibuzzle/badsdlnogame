#include"DVD.hpp"

DVD::DVD(){
    DVD_tex = TextureLoader::Loader("assets/DVD.png");

    src.x = dest.x = 0;
    src.y = dest.y = 0;
    src.h = 650;
    src.w = 1100;

    dest.h = src.h/10;
    dest.w = src.w/10;
};

void DVD::render(){
    SDL_RenderCopy(Game::renderer, DVD_tex, &this->src, &this->dest);
}

void DVD::update(){
    if(!isXNeg && !isYNeg)
    {
        dest.x++; dest.y++;

    }
    else if(isXNeg && !isYNeg)
    {
        dest.x--; dest.y++;
    }
    else if(!isXNeg && isYNeg)
    {
        dest.x++; dest.y--;
    }
    else if(isXNeg && isYNeg)
    {
        dest.x--; dest.y--;
    }

    if (dest.x >= 800-dest.w) {isXNeg = true; SDL_SetRenderDrawColor(Game::renderer, std::rand()%255, std::rand()%255, std::rand()%255, std::rand()%255);}
    if (dest.y >= 640-dest.h) {isYNeg = true; SDL_SetRenderDrawColor(Game::renderer, std::rand()%255, std::rand()%255, std::rand()%255, std::rand()%255);}
    if (dest.x <= 0) {isXNeg = false; SDL_SetRenderDrawColor(Game::renderer, std::rand()%255, std::rand()%255, std::rand()%255, std::rand()%255);}
    if (dest.y <= 0) {isYNeg = false; SDL_SetRenderDrawColor(Game::renderer, std::rand()%255, std::rand()%255, std::rand()%255, std::rand()%255);}
}
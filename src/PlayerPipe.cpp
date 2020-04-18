#include"PlayerPipe.hpp"

playerPipe::playerPipe(int posx, int posy, int space)
{

    spacing = space;
    upperPipe = TextureLoader::Loader("assets/pipeUpper.png");
    lowerPipe = TextureLoader::Loader("assets/pipeLower.png");

    srcLower.w = srcUpper.w = 83;
    srcLower.h = srcUpper.h = 319;

    destLower.w = destUpper.w = 83;
    destLower.h = destUpper.h = 325;

    srcLower.x = srcUpper.x = srcLower.y = srcUpper.y = 0;

    destLower.x = destUpper.x = posx;
    destUpper.y = posy;
    destLower.y = destUpper.y + destUpper.h + spacing;

    xpos = posx;
    ypos = posy;

    
    now = time(NULL);
}

playerPipe::~playerPipe()
{
}

void playerPipe::render(){
    SDL_RenderCopy(Game::renderer, upperPipe, &srcUpper, &destUpper);
    SDL_RenderCopy(Game::renderer, lowerPipe, &srcLower, &destLower);
}

void playerPipe::update(){
        smashPipe();
        releasePipe();
}

void playerPipe::smashPipe(){
    if(isSmashing && smashdist < spacing/2 && !isReleasing){
        destUpper.y+=4;
        destLower.y-=4;
        smashdist+=4;
    }
    else if(!isSmashing && smashdist == ypos && !isReleasing){
        isSmashing = true;
    }
    else if(isSmashing && smashdist >= spacing/2 && !isReleasing){
        isSmashing = false;
        isReleasing = true;
    }
}

void playerPipe::releasePipe(){
    if(!isSmashing && smashdist <= spacing && isReleasing){
        destUpper.y-= 4;
        destLower.y+= 4;
        smashdist-=4;
    }
    if(isReleasing && smashdist == 0){
        isReleasing = false;
    }
}

void playerPipe::startSmashing(){
    if (smashdist == 0) isSmashing = true;
}
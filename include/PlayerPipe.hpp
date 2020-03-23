#pragma once
#include"Game.hpp"

class playerPipe
{
    private:
        SDL_Texture* upperPipe;
        SDL_Texture* lowerPipe;
        
        bool isSmashing = false;
        bool isReleasing = false;
        int smashdist;

        int xpos, ypos;
        int spacing;

        SDL_Rect srcUpper, destUpper;
        SDL_Rect srcLower, destLower;
    public:        

        playerPipe(int posx, int posy, int space);
        ~playerPipe();

        void render();
        void update();

        void smashPipe();
        void releasePipe();

        void startSmashing();

        int getHeight(){return destLower.y;}
        int getSpace(){return spacing;}
        
        SDL_Rect getRectUp(){return destUpper;}
        SDL_Rect getRectDown(){return destLower;}
};
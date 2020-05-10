#pragma once
#include"Game.hpp"

class Birds
{
    private:
        SDL_Texture* birdMidTex;
        SDL_Texture* birdUpTex;
        SDL_Texture* birdDownTex;

        SDL_Texture* renderTex;
        
        SDL_Rect src, dest;
        int gravity = 4;
        int jump = 15;
        int speed = 4;

    public:
        Birds(int posx, int posy);
        ~Birds();

        int birdcountID();

        void update(int height);
        void render();

        void flyUp();
        static void getDestroyed();

        void increase_speed();
        void decrease_speed();

        bool check_collision(SDL_Rect pipeRect);
        bool check_defeat();
};
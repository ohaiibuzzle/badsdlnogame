#pragma once
#include"Game.hpp"

class Birds
{
    private:
        SDL_Texture* birdTex;
        SDL_Rect src, dest;
        const int gravity = 2;
        const int jump = 20;
        const int speed = 3;

    public:
        Birds(int posx, int posy);
        ~Birds();

        int birdcountID();

        void update(int height);
        void render();

        void flyUp();
        static void getDestroyed();

        bool check_collision(SDL_Rect pipeRect);
        bool check_defeat();

};
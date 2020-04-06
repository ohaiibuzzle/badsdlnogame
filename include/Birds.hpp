#pragma once
#include"Game.hpp"

class Birds
{
    private:
        SDL_Texture* birdTex;
        SDL_Rect src, dest;
        int gravity = 2;
        int jump = 15;
        int speed = 2;

    public:
        Birds(int posx, int posy);
        ~Birds();

        int birdcountID();

        void update(int height);
        void render();

        void flyUp();
        static void getDestroyed();

        void increase_speed();

        bool check_collision(SDL_Rect pipeRect);
        bool check_defeat();
};
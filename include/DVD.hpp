#include"Game.hpp"

class DVD{
    private:
        SDL_Rect src, dest;
        bool isXNeg = false, isYNeg = false;
        SDL_Texture* DVD_tex;
    public:
        DVD();
        ~DVD();

        void update();
        void render();
};
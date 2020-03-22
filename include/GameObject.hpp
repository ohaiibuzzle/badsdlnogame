#include "Game.hpp"

class GameObject{
    public:
    GameObject(const char* texpath, int x, int y);
    ~GameObject();

    void ObjUpdate();
    void ObjRender();

    private:
        int xpos, ypos;

        SDL_Texture* objTexture;

        SDL_Rect srcRect, destRect;

        SDL_Renderer* renderer;
};
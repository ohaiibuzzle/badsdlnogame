#include "Game.hpp"
#include "DVD.hpp"
#include "GameObject.hpp"

using namespace std;

SDL_Event Game::event;

SDL_Renderer* Game::renderer = nullptr;

SDL_Texture* background = nullptr;

SDL_Rect dest;

DVD* DVD_object;

playerPipe* pipes;

vector<Birds*> all_birds;

int Game::cnt = 0;

Mix_Music* bgm = nullptr;
Mix_Chunk* Game::smashfx = nullptr;

TTF_Font* displayFont = nullptr;

Game::Game()
{
    srand(time(NULL));
}

Game::~Game()
{}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool opt_fs){
    int flags = 0;
    if(opt_fs)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if(SDL_Init(SDL_INIT_VIDEO) == 0){
        std::cout << "It works!" << std::endl;
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Texture filtering not enabled!");
		}

        if (window)
        {
            std::cout << "Window up!" << std::endl;
            isRunning = true;
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (renderer)
                {  
                    std::cout << "Renderer up!" << std::endl;
                    SDL_SetRenderDrawColor(renderer, 78, 192, 202, 255);
                    SDL_SetWindowIcon(window, TextureLoader::sfLoader("assets/birdMid.png"));
                }
            else
                {
                    printf("Things happened: %s \n", SDL_GetError());
                    isRunning = false;
                }
        }
        else
        {
                printf("Things happened: %s \n", SDL_GetError());
                isRunning = false;
        }
    }
    else
    {
        printf("Things happened: %s \n", SDL_GetError());
    }
    int code = Mix_Init(MIX_INIT_MP3);
	if (!(code & MIX_INIT_MP3))
	{
		throw "Audio error!";
	}

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) != 0) {
		throw "Audio init error!";
	}

    bgm = Mix_LoadMUS("assets/bgm.mp3");
    Mix_PlayMusic(bgm,-1);
    Mix_PauseMusic();

    smashfx = Mix_LoadWAV("assets/smash.wav");
    
    DVD_object = new DVD();

    background = TextureLoader::Loader("assets/bg.png");

    pipes = new playerPipe(600, -75, 150);

    srand(time(NULL));

    for(int i = 0; i < rand()%20 + 5; i++){
        all_birds.push_back(new Birds(std::rand()%200, std::rand()%640));
    }
}

void Game::render(){
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, NULL, NULL);
    if(isStarted){
        pt_rect.x=pt_rect.y=15;
        pt_rect.h = 25;
        pt_rect.w = 200;

        SDL_Texture* pointDisplay = support::displayFont("Current Score: " + support::intText(cnt), "assets/displayFont.ttf", 96, ptColor);

        SDL_RenderCopy(renderer, pointDisplay, NULL, &pt_rect);

        if (cheat_mode)
        {
            SDL_Texture* cheatDisplay = support::displayFont("HAX MODE ON!", "assets/displayFont.ttf", 96, haxColor);
            hax_rect.x= 15;
            hax_rect.y= 605;
            hax_rect.h = 25;
            hax_rect.w = 180;
            SDL_RenderCopy(renderer, cheatDisplay, NULL, &hax_rect);
            SDL_DestroyTexture(cheatDisplay);
        }

        pipes->render();
        for_each(all_birds.begin(), all_birds.end(), mem_fun(&Birds::render));
        
        SDL_DestroyTexture(pointDisplay);
    }
    else
    {        
        DVD_object->render();

        introColor={r,g,b};
        titleColor={255-r,255-g,255-b};

        title_rect.x = 800/2 - 400/2 - 75;
        title_rect.y = 640/2 - 50/2 - 100;
        
        title_rect.w = 550;
        title_rect.h = 75;

        SDL_Texture* titleText = support::displayFont("Flappy desreveR", "assets/displayFont.ttf", 96, titleColor);

        font_rect.x = memex+=4;
        font_rect.y = 640/2 - 50/2;

        if (memex == 800) memex = -400;
        
        font_rect.w = 400;
        font_rect.h = 50;

        SDL_Texture* startText = support::displayFont("Press Space to Start!", "assets/displayFont.ttf", 96, introColor);

        SDL_Texture* diffDisplay = support::displayFont("Current difficulty: " + support::intText(difficulty), "assets/displayFont.ttf", 96, diffColor);
        diff_rect.x= 15;
        diff_rect.y= 605;
        diff_rect.h = 25;
        diff_rect.w = 200;

        SDL_RenderCopy(renderer, titleText, NULL, &title_rect);
        SDL_RenderCopy(renderer, startText, NULL, &font_rect);
        SDL_RenderCopy(renderer, diffDisplay, NULL, &diff_rect);

        SDL_DestroyTexture(titleText);
        SDL_DestroyTexture(startText);
        SDL_DestroyTexture(diffDisplay);
    }
    //TODO
    SDL_RenderPresent(renderer);
};

void Game::update(){
    if (isStarted){
        Mix_ResumeMusic();
        pipes -> update();
        SDL_SetRenderDrawColor(renderer, 78, 192, 202, 255);
        for_each(all_birds.begin(), all_birds.end(), bind2nd(mem_fun(&Birds::update), pipes->getHeight()));
        for_each(all_birds.begin(), all_birds.end(), bind2nd(mem_fun(&Birds::check_collision), pipes -> getRectUp()));
        for_each(all_birds.begin(), all_birds.end(), bind2nd(mem_fun(&Birds::check_collision), pipes -> getRectDown()));
        for (auto i = 0; i != all_birds.size(); i++)
        {
            if (all_birds[i]->check_defeat() && !cheat_mode) 
            {
                Mix_PauseMusic();
                string score = support::formatScore(cnt);
                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "YA YOU DIED!", score.c_str(), NULL);
                isStarted = false;
                all_birds.clear();
                for(int i = 0; i < rand()%20 + 5; i++){
                    all_birds.push_back(new Birds(std::rand()%200, std::rand()%640));
                }
                cnt = 0;
                difficulty = 1;
                break;
            }
            else if (all_birds[i]->check_defeat() && cheat_mode){
                all_birds[i] -> reset();
                cnt++;
            }
            //cout << "Curr. Point:" << cnt << endl;
        }
        if (cnt > 10){
            if(rand() % 450*60 == 0) for_each(all_birds.begin(), all_birds.end(), mem_fun(&Birds::increase_speed));
            if(rand() % 500*60 == 0) all_birds.push_back(new Birds(std::rand()%200, std::rand()%640));
        }
    }
    else
    {       
        updatergb();
        DVD_object->update();
    }
}

void Game::event_handler(){
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT){
        isRunning = false;
    }
    else if (event.type == SDL_KEYDOWN){
        switch (event.key.keysym.sym)
        {
        case (SDLK_ESCAPE):
            isRunning = false;
            break;
        case (SDLK_SPACE):
            if (isStarted){
                pipes->startSmashing();
            }
            else{
                isStarted = true;
                Mix_RewindMusic();
                Mix_ResumeMusic();
            }
            break;
        case (SDLK_RIGHTBRACKET):
        if (!isStarted)
        {
            for_each(all_birds.begin(), all_birds.end(), mem_fun(&Birds::increase_speed));
            difficulty++;

        }
        break;
        case (SDLK_LEFTBRACKET):
        {
            if (difficulty > 1 && !isStarted)
            {
                for_each(all_birds.begin(), all_birds.end(), mem_fun(&Birds::decrease_speed));
                difficulty--;
            }
        }
        default:
            break;
        }
    }
};

void Game::cleanup(){
    std::cout << "Now Cleaning Up!" << std::endl;
    Mix_Quit();
    TTF_Quit();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Done!" << std::endl;
}

void Game::updatergb(){
    if (r == 255 && g == 0 && b == 0) {greenUp = true; blueDown = false;}
    if (r == 255 && g == 255 && b == 0) {greenUp = false; redDown = true;}
    if (r == 0 && g == 255 && b == 0) {redDown = false; blueUp = true;}
    if (r == 0 && g == 255 && b == 255) {blueUp = false; greenDown = true;}
    if (r == 0 && g == 0 && b == 255) {greenDown = false; redUp = true;}
    if (r == 255 && g == 0 && b == 255) {redUp = false; blueDown = true;}

    if (redUp) r++;
    if (greenUp) g++;
    if (blueUp) b++;

    if (redDown) r--;
    if (greenDown) g--;
    if (blueDown) b--;
}
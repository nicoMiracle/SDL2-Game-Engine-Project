//Nicole Nechita, rone8293
#include "System.h"
#include <SDL2/SDL.h>
#include "Constants.h"
#include <SDL2/SDL_mixer.h>
namespace cwing{
    System::System(){
        SDL_Init(SDL_INIT_EVERYTHING);
        win = SDL_CreateWindow("Game",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,600,0);
        ren = SDL_CreateRenderer(win,-1,0);
        TTF_Init();
        font = TTF_OpenFont((constants::gResPath+"/fonts/arial.ttf").c_str(),36);
    }
    /*when System object is killed we need to close and quit the fonts, Renderer, Window and then quit SDL*/
    System::~System(){
        TTF_CloseFont(font);
        TTF_Quit();
        Mix_CloseAudio();
        Mix_Quit();
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        SDL_Quit();
    }
    //these are some basic getter methods
    SDL_Renderer* System::getRen() const{
        return ren;
    }
    TTF_Font* System::getFont() const{
        return font;
    }
    System sys;//static object, constructor will be called at the start
}
//Nicole Nechita, rone8293
#ifndef SYSTEM_H
#define SYSTEM_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
namespace cwing{
class System
{
    /*We have a constructo and destructor, and getter methods for Renderer and Font*/
    public :
    System();
    ~System();
    SDL_Renderer* getRen()const;
    TTF_Font* getFont() const;
    //we create the window, renderer and font already in the System header
    private:
        SDL_Window* win;
        SDL_Renderer* ren;
        TTF_Font* font;
};
    //by using extern, we tell the compiler the definition of sys is somewhere
    //without it, every time System.h is defined, it wll create a new sys, leading to linking issues
    //sys is defined in System.cpp
    extern System sys;
}
#endif
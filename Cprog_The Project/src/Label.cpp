//Nicole Nechita, rone8293
#include "Label.h"
#include <SDL2/SDL_ttf.h>
#include "System.h"
#include <string>
namespace cwing{
    Uint8 Label::m_red =0;
    Uint8 Label::m_green = 0;
    Uint8 Label::m_blue = 0;
    Label::Label(int x, int y, int w, int h, const std::string& txt): Component(x,y,w,h,LABEL),text(txt){
        SDL_Surface* surface = TTF_RenderText_Solid(sys.getFont(),text.c_str(),{m_red,m_green,m_blue});
        texture = SDL_CreateTextureFromSurface(sys.getRen(),surface);
        SDL_FreeSurface(surface);
    }
    //draw is one line long, which just copies the texture to the renderer inside the rectangle it has
    void Label::draw()const{
        SDL_RenderCopy(sys.getRen(),texture,NULL,&getRect());
    }
    //create new instance of label
    Label* Label::getInstance(int x, int y, int w, int h, const std::string& txt){
        return new Label(x,y,w,h,txt);
    }
    //get the text inside the label
    std::string Label::getText()const{
        return text;
    }
    void Label::setText(std::string& newText){
        text = newText;
        SDL_DestroyTexture(texture);
        SDL_Surface* surface = TTF_RenderText_Solid(sys.getFont(),text.c_str(),{m_red,m_green,m_blue});
        texture = SDL_CreateTextureFromSurface(sys.getRen(),surface);
        SDL_FreeSurface(surface);
    } 
    //don't forget to destroy things you make after
    Label::~Label(){
        SDL_DestroyTexture(texture);
    }
    void Label::tick(){}
    void Label::performCollision(const ObjectType& object){}
    void Label::setColor(const Uint8& red,const Uint8& green,const Uint8& blue){
        if(red>=0 && red<=255) m_red = red;
        if(green>=0 && green<=255) m_green = green;
        if(blue>= 0 && blue<=255) m_blue = blue;
    }
}
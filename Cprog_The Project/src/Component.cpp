//Nicole Nechita, rone8293
#include "Component.h"
namespace cwing
{
    //this is pretty basic as all component does is initalised the x y w and h
    Component::Component(int x, int y, int w, int h,ObjectType type):m_rect{x,y,w,h},m_type(type){

    }
    Component::~Component(){

    }
}

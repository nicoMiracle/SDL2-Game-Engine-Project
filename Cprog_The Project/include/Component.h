//Nicole Nechita, rone8293
#ifndef COMPONENT_H
#define COMPONENT_H
#include <SDL2/SDL.h>
namespace cwing{
    enum ObjectType{
        PLAYER,
        ENEMY,
        BULLET,
        LABEL
    };
    class Component{
        public:
            virtual ~Component();
            virtual void mouseDown(const SDL_Event&) {};
            virtual void mouseUp(const SDL_Event&) {};
            virtual void mouseDrag(const SDL_Event&){};
            virtual void performCollision(const ObjectType& object){};
            virtual int getLives()const{return 0;};
            virtual void setLives(const int& lives){}
            virtual void draw() const = 0;
            virtual void tick()=0;
            const SDL_Rect& getRect() const{return m_rect;}
            const ObjectType& getType()const{return m_type;}
            SDL_Rect& getModRect(){return m_rect;}
        protected:
            Component(int x, int y, int w, int h,ObjectType type);
        private:
            SDL_Rect m_rect;
            ObjectType m_type;
            Component(const Component&) = delete;
            const Component& operator=(const Component&) = delete;
    };
}

#endif
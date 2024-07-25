//Nicole Nechita, rone8293
#ifndef ENEMY_H
#define ENEMY_H
#include "Component.h"
#include "Constants.h"
#include "Session.h"
#include "System.h"
#include "Direction.h"
#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <random>
namespace cwing{
    class Enemy: public Component{
    private:
        static SDL_Texture* m_texture;//base
        static Session* m_ses;//base
        static int m_w;//base
        static int m_h;//base
        static int m_minX;
        static int m_maxX;
        static int m_minY;
        static int m_maxY;
        static int m_speed;//base
        static bool m_autoIncreaseSpeed;
        static bool m_spawnHorizontal;//base
        static bool m_spawnVertical;//base
        static bool m_spawnLeft;//base
        static bool m_spawnDown;
        static bool m_spawnRight;
        static bool m_spawnUp;
        static std::mt19937 gen;//base
        Direction m_direction;
        static int getSideSpawn();//base
        double getNextPositionX(const Direction& direction,const int& speed);//base
        double getNextPositionY(const Direction& direction, const int& speed);
        void moveEnemy();//base
        Enemy(const Enemy&) = delete;
        const Enemy& operator=(const Enemy&) = delete;
    protected:
        Enemy(const int& x,const int& y,const Direction& direction);//base
        void performCollision(const ObjectType& type);
        int getLives()const{return 0;}
        void draw()const; //base
        void tick(); //base
    public:
        static Enemy* getInstance();//base
        static void spawnSettings(const bool& spawnLeft,const bool& spawnDown,const bool& spawnRight,const bool& spawnUp);//base
        static void setTexture(const std::string& image); //base
        static void setSession(Session* ses); //base
        static void setSpeed(const int& speed); //base
        static void destroyTexture();//base
        static void setProportion(const int& w, const int& h);
        static void setXLock(const int& left,const int& right);
        static void setYLock(const int& upper,const int& lower);
        ~Enemy();  
};
}
#endif
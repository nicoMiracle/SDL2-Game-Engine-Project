//Nicole Nechita, rone8293
#ifndef BULLET_H
#define BULLET_H
#include "Component.h"
#include <SDL2/SDL_image.h>
#include "Session.h"
#include <string>
#include "Direction.h"
#include "BulletTrajectory.h"
namespace cwing{
    class Bullet: public Component{
    private:
        static int m_w;
        static int m_h;
        static int m_speed;
        static int m_speedSideway;
        static Session* m_ses;
        static SDL_Texture* m_texture;
        BulletTrajectory m_trajectory;
        Direction m_bulletDirection;
        double getNextPositionX(const Direction& bulletDirection,const int& speed);
        double getNextPositionY(const Direction& bulletDirection, const int& speed);
        void performCollision(const ObjectType& object);
        void moveBullet();
        Bullet(const Bullet&) = delete;
        const Bullet& operator=(const Bullet&) = delete;
    public:
        static Bullet* getInstance(const int& x,const int& y,const BulletTrajectory& trajectory,const Direction& bulletDirection);
        static void setTexture(const std::string& name);
        static void setProportion(const int& w,const int& h);
        static void destroyTexture();
        static void setSession(Session* ses);
        static void setSpeed(const int& speed);
        static void setSpeedSideway(const int& speed);

        
        ~Bullet();
    protected:
        void draw()const;
        void tick();
        int getLives()const{return 0;}
        Bullet(const int& x,const int& y,const BulletTrajectory& trajectory,const Direction& bulletDirection);
    };
}

#endif
//Nicole Nechita, rone8293
#include "Bullet.h"
#include "System.h"
#include "Player.h"
#include <cmath>
namespace cwing{
    SDL_Texture* Bullet::m_texture = nullptr;
    int Bullet::m_w = 20;
    int Bullet::m_h = 5;
    int Bullet::m_speed=1000;
    int Bullet::m_speedSideway = 260;
    Session* Bullet::m_ses = nullptr;

    Bullet::~Bullet(){}
    Bullet::Bullet(const int& x,const int& y,const BulletTrajectory& traj,const Direction& dir)
                        :Component(x,y,m_w,m_h,BULLET),m_trajectory(traj),m_bulletDirection(dir){
    }
    Bullet* Bullet::getInstance(const int& x, const int& y,const BulletTrajectory& traj,const Direction& dir){
        return new Bullet(x,y,traj,dir);
    }
    void Bullet::draw()const {
        SDL_RenderCopy(sys.getRen(),m_texture,NULL,&getRect());
    }
    void Bullet::moveBullet(){
        if(m_bulletDirection==LEFT || m_bulletDirection==RIGHT){
            switch(m_trajectory){
                case STRAIGHT:{
                    getModRect().x = getNextPositionX(m_bulletDirection,m_speed);
                    break;
                }
                case UPWARDS:{
                    getModRect().x = getNextPositionX(m_bulletDirection,m_speed);
                    getModRect().y = getNextPositionY(UP,m_speedSideway);
                    break;
                }
                case DOWNWARDS:{
                    getModRect().x = getNextPositionX(m_bulletDirection,m_speed);
                    getModRect().y = getNextPositionY(DOWN,m_speedSideway);
                    break;
                }
            }
        }
        else{
            switch(m_trajectory){
                case STRAIGHT:{
                    getModRect().y = getNextPositionY(m_bulletDirection,m_speed);
                    break;
                }
                case UPWARDS:{
                    getModRect().y = getNextPositionY(m_bulletDirection,m_speed);
                    getModRect().x = getNextPositionX(RIGHT,m_speedSideway);
                    break;
                }
                case DOWNWARDS:{
                    getModRect().y = getNextPositionY(m_bulletDirection,m_speed);
                    getModRect().x = getNextPositionX(LEFT,m_speedSideway);
                    break;
                }
            }
        }
    }
    void Bullet::tick(){
        moveBullet();
        if(getRect().x>800 || (getRect().y+getRect().h)<0 || getRect().y>600){
             m_ses->remove(this);
        }   
    }
    void Bullet::setProportion(const int& w,const int& h){
        m_w = w;
        m_h = h;
    }
    //has to be set before the program starts
    void Bullet::setTexture(const std::string& image){
        if(m_texture){
            SDL_DestroyTexture(m_texture);
            m_texture = nullptr;
        }
        SDL_Surface* surf = IMG_Load((constants::gResPath +"images/"+image).c_str());
        m_texture = SDL_CreateTextureFromSurface(sys.getRen(),surf);
        SDL_FreeSurface(surf);
    }
    //called after session is over
    void Bullet::destroyTexture(){
        if(m_texture){
           SDL_DestroyTexture(m_texture);
           m_texture = nullptr;
        }
    }
    void Bullet::setSession(Session* ses){
        m_ses = ses;
    }
    void Bullet::setSpeed(const int& speed){
        m_speed = speed;
    }
    double Bullet::getNextPositionX(const Direction& direction, const int& speed){
        double rectanglePosX = getRect().x;
        double deltaTime = m_ses->getDeltaTime();
        switch(direction){
            case RIGHT:{
                return round(rectanglePosX+=speed*deltaTime);
                break;
            }
            case LEFT:{
                return round(rectanglePosX-=speed*deltaTime);
                break;
            }
            default:{
                return 0.0;
            }
        }
    }
    double Bullet::getNextPositionY(const Direction& direction,const int& speed){
        double rectanglePosY = getRect().y;
        double deltaTime = m_ses->getDeltaTime();
        switch(direction){
            case DOWN:{
                return round(rectanglePosY+=speed*deltaTime);
                break;
            }
            case UP:{
                return round(rectanglePosY-=speed*deltaTime);
                break;
            }
            default:{
                return 0.0;
            }
        }
    }
    void Bullet::setSpeedSideway(const int& speed){
        m_speedSideway = speed;
    }
    void Bullet::performCollision(const ObjectType& object){
        switch(object){
            case ENEMY:{
                m_ses->remove(this);
                break;
            }
            default:{}
        }
    }
}
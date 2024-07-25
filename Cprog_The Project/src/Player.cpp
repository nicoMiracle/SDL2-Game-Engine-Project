//Nicole Nechita, rone8293
#include "Player.h"
#include "Constants.h"
#include "SDL2/SDL_image.h"
#include<SDL2/SDL_mixer.h>
#include "System.h"
#include <iostream>
#include <string>
#include "Bullet.h"
namespace cwing{
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    Player::Player(Session& ses,int x,int y,int w,int h,const std::string& image):Component(x,y,w,h,PLAYER),m_ses(ses){
        setTexture(image);
    }
    void Player::draw()const{
        SDL_RenderCopyEx(sys.getRen(),m_texture,NULL,&getRect(),0.0,nullptr,flip);
    }
    Player* Player::getInstance(Session& ses,int x,int y,int w,int h,const std::string& image){
        return new Player(ses,x,y,w,h,image);
    }
    void Player::mouseDrag(const SDL_Event& event){
        if(!m_xLocked){
            if((getRect().x+(getRect().w/2)>event.motion.x) && m_canFlip){
                flip = SDL_FLIP_NONE;
                m_shootDirection = LEFT;
            }
            else if((getRect().x+(getRect().w/2)<event.motion.x) && m_canFlip){
                flip = SDL_FLIP_HORIZONTAL;
                m_shootDirection = RIGHT;
            }

            getModRect().x = event.motion.x-(getRect().w/2);
        }
        if(!m_yLocked){
           getModRect().y = event.motion.y-(getRect().h/2); 
        }
    }
    void Player::mouseDown(const SDL_Event& event){
        if(!m_hasGun){
            return;
        }
        m_mouseDown = true;
        shoot();
    }
    void Player::shoot(){
        m_lastShot = SDL_GetTicks();
        if(m_sound){
            int channel = Mix_PlayChannel(-1,m_sound,0);
            Mix_Volume(channel,m_ses.getVolume());
        }
        switch (m_shootType){
            case SINGLE:{
                Bullet* bullet = Bullet::getInstance(getRect().x+(getRect().w/2),getRect().y+(getRect().h/2),STRAIGHT,m_shootDirection);
                m_ses.add(bullet);
                break; 
            }//case 0
            case SPREAD:{
                Bullet* upBullet = Bullet::getInstance(getRect().x+(getRect().w/2),getRect().y+(getRect().h/2),UPWARDS,m_shootDirection);
                Bullet* forwardBullet = Bullet::getInstance(getRect().x+(getRect().w/2),getRect().y+(getRect().h/2),STRAIGHT,m_shootDirection);
                Bullet* downBullet = Bullet::getInstance(getRect().x+(getRect().w/2),getRect().y+(getRect().h/2),DOWNWARDS,m_shootDirection);
                m_ses.add(upBullet);
                m_ses.add(forwardBullet);
                m_ses.add(downBullet);
                break;
            }//case 1
            default:{
                m_shootType = SINGLE;
                break;
            }//default
            }//switch
    }
    Player::~Player(){
        if(m_texture){
          SDL_DestroyTexture(m_texture);
          m_texture = nullptr;
        }
        if(m_sound){
          Mix_FreeChunk(m_sound);
          m_sound = nullptr;
        }
    }
    void Player::tick(){
        if(m_mouseDown){
            mouseHeld();
        }
    }
    void Player::mouseUp(const SDL_Event&){
        m_mouseDown = false;
    }
    void Player::mouseHeld(){
        if(m_mouseDown){
            Uint32 currentTime = SDL_GetTicks();
            if(currentTime-m_lastShot>=300){
                shoot();
            }
        }
    }
    void Player::lockX(){
        m_xLocked = true;
    }
    void Player::lockY(){
        m_yLocked = true;
    }
    void Player::disableGun(){
        m_hasGun = false;
    }
    //-1 for infinite, other number but 0 for finite
    void Player::setLives(const int& lives){
        m_lives = lives;
    }
    void Player::setTexture(const std::string& image){
        if(m_texture){
            SDL_DestroyTexture(m_texture);
            m_texture = nullptr;
        }
        SDL_Surface* surf = IMG_Load((constants::gResPath +"images/"+image).c_str());
        m_texture = SDL_CreateTextureFromSurface(sys.getRen(),surf);
        SDL_FreeSurface(surf); 
    }
    //0 for one shot, 1 for spread
    void Player::setGunBehaviour(const ShootType& value){
        m_shootType=value;
    }
    //0 for right, 1 for down, 2 for left, 3 for up
    void Player::setShootDirection(const Direction& value){
        if(value>=LEFT && value<=UP){
            m_shootDirection = value;
        }
    }
    void Player::setSoundEffect(const std::string& sound){
        if(m_sound){
            Mix_FreeChunk(m_sound);
            m_sound = nullptr;
        }
        m_sound = Mix_LoadWAV((constants::gResPath+"sounds/"+sound+".wav").c_str());
    }
    void Player::performCollision(const ObjectType& object){
        switch(object){
            case ENEMY:{
                if(m_lives>0){
                    m_lives--;
                    m_ses.decreaseLives();
                }
                break;
            }
            default:{}
        }
    }
    int Player::getLives()const {
        return m_lives;
    }
    void Player::enableFlip(){
        m_canFlip = true;
    }
}
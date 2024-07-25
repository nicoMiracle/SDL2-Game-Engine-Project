//Nicole Nechita, rone8293
#ifndef PLAYER_H
#define PLAYER_H
#include "Component.h"
#include "Label.h"
#include "Session.h"
#include "Constants.h"
#include <SDL2/SDL_mixer.h>
#include "Direction.h"
#include "BulletTrajectory.h"
#include <string>
namespace cwing{
    enum ShootType{
        SINGLE,
        SPREAD
    };
    class Player: public Component{
    private:
        Session& m_ses;
        SDL_Texture* m_texture = nullptr;
        Mix_Chunk* m_sound = nullptr;
        int m_lives=3;
        int m_movementType=0;
        ShootType m_shootType=SINGLE;
        Direction m_shootDirection=RIGHT;
        int m_mouseDown=false;
        bool m_hasGun=true;
        bool m_xLocked=false;
        bool m_yLocked=false;
        bool m_canFlip = false;
        Uint32 m_lastShot=5000;
        void mouseHeld();
        void shoot();
        Player(const Player&) = delete;
        const Player& operator=(const Player&) = delete;
    protected:
        void mouseDrag(const SDL_Event& event);
        void mouseDown(const SDL_Event& event);
        void mouseUp(const SDL_Event& event);
        void performCollision(const ObjectType& object);
        void draw() const;
        void tick();
        int getLives()const;
        Player(Session& ses,int x,int y,int w,int h,const std::string& image);
    public:
        static Player* getInstance(Session&,int x,int y,int w,int h,const std::string& image);
        void setTexture(const std::string& image);
        void setGunBehaviour(const ShootType& value);
        void setShootDirection(const Direction& value);
        void setSoundEffect(const std::string& sound);
        void disableGun();
        void lockX();
        void lockY();
        void enableFlip();
        void setLives(const int& lives);
        inline const Session& getSes(){return m_ses;}
        ~Player();
    };
}
#endif
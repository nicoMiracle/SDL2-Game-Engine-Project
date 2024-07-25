//Nicole Nechita, rone8293
#include "Session.h"
#include <SDL2/SDL.h>
#include<SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include "System.h"
#include "Enemy.h"
#include "Player.h"
#include "Constants.h"
#include <string>
#include <iostream>
namespace cwing{
    //add a component to the vector of components
    void Session::spawnEnemy(){
        Enemy* enemy = cwing::Enemy::getInstance();
        if(enemy){
            add(enemy);
        }
    }
    void Session::add(Component* component){
        if(component->getType()==PLAYER) {
            m_playerLives= m_originalPlayerLives = component->getLives();
            m_mainPlayer = component;
        }
        m_added.push_back(component);
    }
    void Session::remove(Component* component){
        m_removed.push_back(component);
    }
    //most of this is honestly self explanatory
    void Session::run(){
        bool quit = false;
        if(m_music){
          int channel = Mix_PlayChannel(-1,m_music,-1);
          Mix_Volume(channel,m_volume);
        }
        double tickInterval = 1000.0 / m_FPS;
        double prev_time = SDL_GetTicks64();
        while(!quit){
            double nextTick = SDL_GetTicks() + tickInterval;
            m_deltaTime = static_cast<double>(SDL_GetTicks64() - prev_time)/1000.0;
            prev_time = SDL_GetTicks64();
            SDL_Event event;
            while(SDL_PollEvent(&event)){
                switch(event.type){
                    //using commentaries at the end of brackets is great way to keep track of them
                    case SDL_QUIT: quit = true; break;
                    case SDL_MOUSEBUTTONDOWN:{
                        for(Component* component:m_comps){
                            component->mouseDown(event);
                        }
                        break;
                    }//mouse down
                    case SDL_MOUSEBUTTONUP:{
                        for(Component* component:m_comps){
                            component->mouseUp(event);
                        }
                        break;
                    }//mouse up
                    case SDL_MOUSEMOTION:{
                        for(Component* component: m_comps){
                            component->mouseDrag(event);
                        }
                        break;
                    }//mouse motion
                    case SDL_KEYDOWN:{
                        m_playerDied = false;
                        m_playerLives = m_originalPlayerLives+1;
                        m_timePoint= 0;
                        m_enemyPoint = 0;
                        restartPlayer();
                        break;
                    }
                }//switch
            }//inner while
            Uint32 currentTimeEnemy = SDL_GetTicks();
            Uint32 currentTimePoint = SDL_GetTicks();

            for(Component* comp : m_comps){
                comp->tick();
            }
            if(m_enemiesAllowed &&(currentTimeEnemy - m_lastEnemySpawn >= m_enemySpawnInterval)){
                spawnEnemy();
                m_lastEnemySpawn = currentTimeEnemy;    
            }
            if(m_timePointLabel &&(currentTimePoint - m_lastPointTime >= 500)&& !m_playerDied){
                increaseTimePoint();
                m_lastPointTime = currentTimePoint;
            }
            for(Component* comp : m_added){
                m_comps.push_back(comp);
            }
            m_added.clear();
            for(Component* &comp: m_removed){
                for (std::vector<Component*>::iterator i = m_comps.begin();i != m_comps.end();){
				if (*i == comp) {
                    delete *i;
					i = m_comps.erase(i);
				}
				else{
					i++;
				}
			}}
            m_removed.clear();
            
            SDL_SetRenderDrawColor(sys.getRen(),255,255,255,255);
           
            SDL_RenderClear(sys.getRen());

            if(m_backgroundTex) SDL_RenderCopy(sys.getRen(),m_backgroundTex,NULL,NULL);

            for(Component* component: m_comps){
                component->draw();
                for(Component* otherComp : m_comps){
                    if(component!=otherComp){
                        SDL_Rect rectangle;
                        if(SDL_IntersectRect(&component->getRect(),&otherComp->getRect(),&rectangle)==SDL_TRUE){
                            component->performCollision(otherComp->getType());
                        }
                    }
                }
            }
            SDL_RenderPresent(sys.getRen());
            double delay = nextTick - SDL_GetTicks64();
		    if (delay > 0){
			    SDL_Delay(delay);
            }
        }//last while
    }
    Session::~Session(){
        
        if(m_backgroundTex){
            SDL_DestroyTexture(m_backgroundTex);
            m_backgroundTex = nullptr;
        }
        if(m_music){
            Mix_FreeChunk(m_music);
            m_music = nullptr;
        }
        for(Component* &point:m_comps){
            if(point){
                delete point;
                point = nullptr;
            }
        }
    }
    //called before music is set
    void Session::allowSound(){
        Mix_OpenAudio(48000, AUDIO_S16SYS,2,2048);
    }
    void Session::allowEnemies(){
        m_enemiesAllowed = true;
    }
    void Session::setMusic(const std::string& musicName){
        if(m_music){
            Mix_FreeChunk(m_music);
            m_music = nullptr;
        }
        m_music = Mix_LoadWAV((constants::gResPath+"sounds/"+musicName+".wav").c_str());
    }
    void Session::setBackground(const std::string& background){
        if(m_backgroundTex){
            SDL_DestroyTexture(m_backgroundTex);
            m_backgroundTex = nullptr;
        }
        m_backgroundTex = IMG_LoadTexture(sys.getRen(),(constants::gResPath+"images/"+background).c_str());
    }
    //set FPS to a certain level, too much FPS can break the movement of slower objects as the delta value becomes too low
    void Session::setFPS(const double& FPS){
        if(FPS>=1 && FPS<=1000){
            m_FPS = FPS;
        }
    }
    void Session::setVolume(const int& value){
        m_volume = value;
    }
    void Session::setEnemySpawnInterval(const Uint32& value){
        m_enemySpawnInterval = value;
    }
    double& Session::getDeltaTime(){
        return m_deltaTime;
    }
    double& Session::getFPS(){
        return m_FPS;
    }
    int Session::getVolume(){
        return m_volume;
    }
    void Session::increaseEnemyPoint(){
        if(m_enemyPointLabel && !m_playerDied){
            m_enemyPoint++;
            std::string newString = m_enemyPointCustomText+std::to_string(m_enemyPoint);
            m_enemyPointLabel->setText(newString);
        }
    }
    void Session::increaseTimePoint(){
        m_timePoint++;
        std::string newString = m_timePointCustomText+std::to_string(m_timePoint);
        m_timePointLabel->setText(newString);
    }
    void Session::decreaseLives(){
        if(m_livesLabel){
            m_playerLives--;
            std::string newString = m_livesLabelCustomText+std::to_string(m_playerLives);
            m_livesLabel->setText(newString);
        }
        if(m_playerLives==0) m_playerDied=true;
    }
    void Session::setEnemyPointLabel(const int& x,const int& y,const int& w,const int& h,const std::string& customText){
        if(m_enemyPointLabel){
            delete m_enemyPointLabel;
            m_enemyPointLabel = nullptr;
        }
        m_enemyPointCustomText = customText;
        std::string newString = m_enemyPointCustomText+std::to_string(m_enemyPoint);
        m_enemyPointLabel= Label::getInstance(x,y,w,h,newString);
        add(m_enemyPointLabel);
    }
    void Session::setTimePointLabel(const int& x,const int& y,const int& w,const int& h,const std::string& customText){
        if(m_timePointLabel){
            delete m_timePointLabel;
            m_timePointLabel = nullptr;
        }
        m_timePointCustomText = customText;
        std::string newString = m_timePointCustomText+std::to_string(m_timePoint);
        m_timePointLabel= Label::getInstance(x,y,w,h,newString);
        add(m_timePointLabel);
    }
    void Session::setLivesLabel(const int& x,const int& y,const int& w,const int& h,const std::string& customText){
        if(m_livesLabel){
            delete m_livesLabel;
            m_timePointLabel = nullptr;
        }
        m_livesLabelCustomText = customText;
        std::string newString = m_livesLabelCustomText+std::to_string(m_playerLives);
        m_livesLabel= Label::getInstance(x,y,w,h,newString);
        add(m_livesLabel);
    }
    void Session::restartPlayer(){
        m_mainPlayer->setLives(m_originalPlayerLives);
        if(m_enemyPointLabel) increaseEnemyPoint();
        if(m_timePointLabel) increaseTimePoint();
        if(m_livesLabel) decreaseLives();
    }
}
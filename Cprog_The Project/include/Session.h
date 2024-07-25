//Nicole Nechita, rone8293
#ifndef SESSION_H
#define SESSION_H
#include <vector>
#include <string>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include "Component.h"
#include "Label.h"
namespace cwing{
    /*session is used to add components to the window, and then run the program*/
    class Session{
        public:
        void add(Component* component);
        void remove(Component* component);
        void run();
        void allowSound();
        void allowEnemies();
        void setMusic(const std::string& musicName);
        void setBackground (const std::string& backgroundName);
        void setFPS(const double&  value);
        void setVolume(const int& value);
        void setEnemyPointLabel(const int& x,const int& y,const int& w,const int& h,const std::string& customText);
        void setTimePointLabel(const int& x,const int& y,const int& w,const int& h,const std::string& customText);
        void setLivesLabel(const int& x,const int& y,const int& w,const int& h,const std::string& customText);
        void increaseEnemyPoint();
        void decreaseLives();
        void setEnemySpawnInterval(const Uint32& value);
        int getVolume();
        double& getDeltaTime();
        double& getFPS();
        Session(){}
        ~Session();
        //inside private we have a vector pointer to the components, we want to have a vector of pointers
        private:
        std::vector<Component*> m_added;
        std::vector<Component*> m_removed;
        std::vector<Component*> m_comps;
        Label* m_enemyPointLabel=nullptr;
        Label* m_timePointLabel = nullptr;
        Label* m_livesLabel = nullptr;
        Component* m_mainPlayer = nullptr;
        Mix_Chunk* m_music = nullptr;
        SDL_Texture* m_backgroundTex = nullptr;
        std::string m_enemyPointCustomText;
        std::string m_timePointCustomText;
        std::string m_livesLabelCustomText;
        double m_FPS = 120;
        double m_deltaTime;
        int m_volume=50;
        bool m_enemiesAllowed = false;
        bool m_playerDied = false;
        Uint32 m_enemySpawnInterval = 700;
        Uint32 m_lastEnemySpawn = 0;
        Uint32 m_lastPointTime = 0;
        Uint64 m_enemyPoint = 0;
        Uint64 m_timePoint =0;
        int m_playerLives = 3;
        int m_originalPlayerLives = 3;
        void spawnEnemy();
        void increaseTimePoint();
        void restartPlayer();
        Session(const Session&) = delete;
        const Session& operator=(const Session&) = delete;
    };
}
#endif
//Nicole Nechita, rone8293
#include "Enemy.h"
namespace cwing{
    
    SDL_Texture* Enemy::m_texture = nullptr;
    Session* Enemy::m_ses = nullptr;
    int Enemy::m_w =30;
    int Enemy::m_h =30;
    int Enemy::m_speed = 600;
    int Enemy::m_minX = 1;
    int Enemy::m_maxX= 799;
    int Enemy::m_minY = 1;
    int Enemy::m_maxY = 599;
    bool Enemy::m_autoIncreaseSpeed = false;

    bool Enemy::m_spawnHorizontal = false;
    bool Enemy::m_spawnVertical = false;
    bool Enemy::m_spawnLeft = false;
    bool Enemy::m_spawnDown = false;
    bool Enemy::m_spawnRight = false;
    bool Enemy::m_spawnUp = false;
    std::mt19937 Enemy::gen(std::random_device{}());

    Enemy::Enemy(const int& x,const int& y,const Direction& direction):Component(x,y,m_w,m_h,ENEMY),m_direction(direction){}
    Enemy::~Enemy(){}

    int Enemy::getSideSpawn(){
        if(!m_spawnHorizontal && !m_spawnVertical){
            return 0;
        }

        int lowerBound = 1;
        int higherBound = 4;
        if(!m_spawnHorizontal){
            lowerBound = 3;
        }
        if(!m_spawnVertical){
            higherBound = 2;
        }
        std::uniform_int_distribution<int> distribution(lowerBound, higherBound);
        int randomSide = distribution(gen);
        if (randomSide == 1 && m_spawnRight) {
            return 1;
        } 
        else if (randomSide == 2 && m_spawnLeft) {
            return 2;
        }
        else if (randomSide == 3 && m_spawnUp) {
            return 3;
        } 
        else if (randomSide == 4 && m_spawnDown) {
            return 4;
        }
        return getSideSpawn();
    }
    Enemy* Enemy::getInstance(){
        int x = 0;
        int y = 0;
        Direction direction;
        switch(getSideSpawn()){
            case 1:{
                x = 799;
                std::uniform_int_distribution<int> distribution(m_minY, m_maxY);
                y = distribution(gen);
                direction = LEFT;
                break;
            }
            case 2:{
                x = 1-m_w;
                std::uniform_int_distribution<int> distribution(m_minY, m_maxY);
                y = distribution(gen);
                direction = RIGHT;
                break;
            }
            case 3:{
                y = 1-m_h;
                std::uniform_int_distribution<int> distribution(m_minX, m_maxX);
                x = distribution(gen);
                direction = DOWN;
                break;
            }
            case 4:{
                y = 599;
                std::uniform_int_distribution<int> distribution(m_minX, m_maxX);
                x = distribution(gen);
                direction = UP;
                break;
            }
            default:{
                return nullptr;
            }
        }
        return new Enemy(x,y,direction);
    }
    void Enemy::draw()const{
        SDL_RenderCopy(sys.getRen(),m_texture,NULL, &getRect());
    }
    double Enemy::getNextPositionX(const Direction& direction,const int& speed){
        double rectanglePosX = getRect().x;
        double deltaTime = m_ses->getDeltaTime();
        switch(direction){
            case LEFT:{
                return round(rectanglePosX-=speed*deltaTime);
                break;
            }
            case RIGHT:{
                return round(rectanglePosX+=speed*deltaTime);
                break;
            }
            default:{
                return 0.0;
            }
        }
    }
    double Enemy::getNextPositionY(const Direction& direction,const int& speed){
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
    void Enemy::moveEnemy(){
        switch(m_direction){
            case LEFT:{
                getModRect().x = getNextPositionX(m_direction,m_speed);
                break;
            }
            case RIGHT:{
                getModRect().x = getNextPositionX(m_direction,m_speed);
                break;
            }
            case UP:{
                getModRect().y = getNextPositionY(m_direction,m_speed);
                break;
            }
            case DOWN:{
                getModRect().y = getNextPositionY(m_direction,m_speed);
                break;
            }
        }
    }
    void Enemy::tick(){
        moveEnemy();
        if(getRect().x>800 || (getRect().y+getRect().h)<0 || getRect().y>600){
             m_ses->remove(this);
        }   
    }
    void Enemy::setTexture(const std::string& image){
        if(m_texture){
            SDL_DestroyTexture(m_texture);
            m_texture = nullptr;
        }
        SDL_Surface* surf = IMG_Load((constants::gResPath +"images/"+image).c_str());
        m_texture = SDL_CreateTextureFromSurface(sys.getRen(),surf);
        SDL_FreeSurface(surf); 
    }
    void Enemy::setSession(Session* ses){
        m_ses = ses;
    }
    void Enemy::setSpeed(const int& speed){
        m_speed = speed;
    }
    void Enemy::setProportion(const int& w, const int& h){
        m_w = w;
        m_h = h;
    }
    void Enemy::destroyTexture(){
        if(m_texture){
           SDL_DestroyTexture(m_texture);
            m_texture = nullptr; 
        }
    }
    void Enemy::spawnSettings(const bool& spawnLeft,const bool& spawnDown,const bool& spawnRight,const bool& spawnUp){
        if(spawnLeft){
            m_spawnLeft = true;;
            m_spawnHorizontal = true;
        }
        if(spawnRight){
            m_spawnRight = true;;
            m_spawnHorizontal = true;
        }
        if(spawnDown){
            m_spawnDown = true;;
            m_spawnVertical = true;
        }
        if(spawnUp){
            m_spawnUp = true;;
            m_spawnVertical = true;
        }
    }
    void Enemy::setXLock(const int& right,const int& left){
        if(right>0 && right<left)m_minX = right;
        if(left>right && left<800)m_maxX = left;
    }
    void Enemy::setYLock(const int& upper,const int& lower){
        if(upper>0 && upper<lower)m_minY = upper;
        if(lower>upper && lower<600)m_maxY = lower;
    }
    void Enemy::performCollision(const ObjectType& object){
        switch(object){
            case PLAYER:
            case BULLET:{
                m_ses->remove(this);
                m_ses->increaseEnemyPoint();
                break;
            }
            default:{}
        }
    }
}
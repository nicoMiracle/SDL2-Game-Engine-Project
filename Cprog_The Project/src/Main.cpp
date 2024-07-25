//Nicole Nechita, rone8293
#include <SDL2/SDL.h>
#include "Label.h"
#include "Session.h"
#include <string>
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

int main(int argc, char** argv){
    cwing::Session session;
    cwing::Label::setColor(255,255,255);
    session.allowSound();
    session.setMusic("background_music");
    session.setBackground("space.jpg");
    session.allowEnemies();
    session.setEnemySpawnInterval(300);
    session.setTimePointLabel(20,20,180,50,"Time survived: ");

    cwing::Player* player =cwing::Player::getInstance(session,400,350,70,20,"The_Airplane.png");
    player->setLives(5);
    player->disableGun();

    cwing::Enemy::setSession(&session);
    cwing::Enemy::setTexture("meteor.png");
    cwing::Enemy::spawnSettings(true,true,true,true);
    cwing::Enemy::setProportion(60,60);
    cwing::Enemy::setSpeed(450);
    session.setFPS(144);
    session.add(player);

    session.setLivesLabel(20,550,80,30,"Lives: ");

    session.run();
    cwing::Bullet::destroyTexture();
    cwing::Enemy::destroyTexture();
    return 0;

    //alternative game
    /*
    cwing::Session session;
    cwing::Label::setColor(255,255,255);
    session.allowSound();
    session.setMusic("background_music");
    session.setBackground("farm.jpg");
    session.allowEnemies();
    session.setEnemySpawnInterval(600);
    session.setEnemyPointLabel(20,560,100,40,"Points: ");

    cwing::Bullet::setTexture("bullet.png");
    cwing::Bullet::setProportion(5,20);
    cwing::Bullet::setSession(&session);

    cwing::Player* player =cwing::Player::getInstance(session,400,530,100,70,"farmer.png");
    player->lockY();
    player->setGunBehaviour(cwing::SINGLE);
    player->setShootDirection(cwing::UP);
    player->setSoundEffect("gun_shoot");

    cwing::Enemy::setSession(&session);
    cwing::Enemy::setTexture("duck.png");
    cwing::Enemy::spawnSettings(true,false,true,false);
    cwing::Enemy::setProportion(90,90);
    cwing::Enemy::setSpeed(350);
    cwing::Enemy::setYLock(1,360);

    session.setFPS(100);
    session.add(player);

    session.run();
    cwing::Bullet::destroyTexture();
    cwing::Enemy::destroyTexture();
    return 0;*/
} 

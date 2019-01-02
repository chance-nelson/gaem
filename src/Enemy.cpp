#ifndef ENEMY_CPP
#define ENEMY_CPP


#include "Enemy.hpp"
#include <iostream>


Enemy::Enemy(EnemyType type, Entity *player, int max_health, double speed, sf::Sprite sprite) : Entity(max_health, speed, sprite) {
    this->player = player;
    this->type = type;
    return; 
}


Enemy::Enemy(EnemyType type, Entity *player, int max_health, double speed, sf::Sprite sprite, sf::Texture *bullet_texture, std::vector<Bullet> *bullets) : Entity(max_health, speed, sprite, bullet_texture, bullets){
    this->player = player;
    this->type = type;
    return;
}


void Enemy::step() {
    switch(this->type) {
        case EnemyType::Runner: {
            sf::Vector2f player_location = this->player->getSprite().getPosition();
            sf::Vector2f enemy_location = this->getSprite().getPosition();

            sf::Vector2f dist_vector = player_location - enemy_location;
            double magnitude = sqrt(pow(dist_vector.x, 2) + pow(dist_vector.y, 2));

            dist_vector.x /= magnitude;
            dist_vector.y /= magnitude;

            dist_vector.x *= this->getSpeed();
            dist_vector.y *= this->getSpeed();
            
            if(magnitude <= 0) {
                break;
            }

            this->setPosition(enemy_location + dist_vector);
            break;
        }

        case EnemyType::Shooter: {
            // TODO
            break;
        }
    }

    return;
}


#endif

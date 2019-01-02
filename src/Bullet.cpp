#ifndef BULLET_CPP
#define BULLET_CPP


#include "Bullet.hpp"


Bullet::Bullet(Entity *parent, sf::Vector2i direction, double speed, sf::Texture *texture, sf::Vector2f pos) {
    this->direction            = direction;
    this->speed                = speed;
    this->parent               = parent;
    this->sprite               = sf::Sprite(*texture);
    this->sprite.setPosition(pos);
    this->sprite.setScale(5, 5);

    if(this->direction.x == 1) {
        if(this->direction.y == 1) {
            this->sprite.rotate(135);
        } else if(this->direction.y == -1) {
            this->sprite.rotate(45);
        } else {
            this->sprite.rotate(90);
        }
    } else if(this->direction.x == -1) {
        if(this->direction.y == 1) {
            this->sprite.rotate(225);
        } else if(this->direction.y == -1) {
            this->sprite.rotate(315);
        } else {
            this->sprite.rotate(-90);
        }
    } else {
        if(this->direction.y == -1) {
            
        } else if(this->direction.y == 1) {
            this->sprite.rotate(180);
        }
    }

    return;
}


Entity *Bullet::getParent() {
    return this->parent;
}


sf::Sprite Bullet::getSprite() {
    return this->sprite;
}


sf::Vector2f Bullet::step() {
    sf::Vector2f last_pos = this->sprite.getPosition();

    switch(this->direction.x) {
        case -1:
            last_pos.x -= this->speed;
            break;

        case 1:
            last_pos.x += this->speed;
            break;

        default:
            break;
    }

 
    switch(this->direction.y) {
        case -1:
            last_pos.y -= this->speed;
            break;

        case 1:
            last_pos.y += this->speed;
            break;

        default:
            break;

    }

    this->sprite.setPosition(last_pos);

    return last_pos;
}


#endif

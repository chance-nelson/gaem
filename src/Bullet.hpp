#ifndef BULLET_HPP
#define BULLET_HPP


#include <SFML/Graphics.hpp>
#include <vector>
#include "Entity.hpp"


class Entity;


class Bullet {
    public:
        Bullet(Entity *parent, sf::Vector2i direction, double speed, sf::Texture *texture, sf::Vector2f pos);
        
        Entity *getParent();
        sf::Sprite getSprite();
        sf::Vector2f step();


    private:
        Entity       *parent;
        sf::Sprite   sprite;
        sf::Vector2f pos;
        sf::Vector2i direction;
        double       speed;
};


#endif

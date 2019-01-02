#ifndef ENTITIY_HPP
#define ENTITIY_HPP


#include <SFML/Graphics.hpp>
#include "Bullet.hpp"


class Bullet;


class Entity {
    public:
        Entity(int maxHealth, double speed, sf::Sprite sprite);
        Entity(int maxHealth, double speed, sf::Sprite sprite, sf::Texture *bullet_texture, std::vector<Bullet> *bullets);

        sf::Vector2i getDirection();
        void         setDirection(sf::Vector2i direction);
        sf::Vector2f getPosition();        
        void         setPosition(sf::Vector2f pos);
        sf::Sprite   getSprite();
        int          getHealth();
        double       getSpeed();
        void         changeDirection(sf::Vector2i new_direction);
        void         fire(); 
        void         fire(sf::Vector2i direction); 


    private:
        sf::Sprite sprite;
        int maxHealth, health;
        double speed;
        sf::Vector2i direction;
        sf::Texture *bullet_texture;
        std::vector<Bullet> *bullets;
};


#endif

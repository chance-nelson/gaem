#ifndef ENTITIY_CPP
#define ENTITIY_CPP


#include "Entity.hpp"


Entity::Entity(int maxHealth, double speed, sf::Sprite sprite) {
    this->speed           = speed;
    this->maxHealth       = maxHealth;
    this->health          = maxHealth;
    this->sprite          = sprite;
    this->direction       = sf::Vector2i(0, 1);

    this->bullet_texture = nullptr;
    this->bullets        = nullptr;    

    return;
}


Entity::Entity(int max_health, double speed, sf::Sprite sprite, sf::Texture *bullet_texture, std::vector<Bullet> *bullets) {
    this->speed           = speed;
    this->maxHealth       = maxHealth;
    this->health          = maxHealth;
    this->sprite          = sprite;
    this->direction       = sf::Vector2i(0, 1);

    this->bullet_texture  = bullet_texture;
    this->bullets         = bullets;

    return;
}


void Entity::fire() {
    if(!this->bullet_texture) return;

    double width_mod  = 0;
    double height_mod = 0;

    sf::FloatRect size_box = this->sprite.getGlobalBounds();
    
    width_mod  = size_box.width / 2;
    height_mod = size_box.height / 2;

    sf::Vector2f pos = this->sprite.getPosition();
    pos.x += width_mod;
    pos.y += height_mod;

    this->bullets->push_back(Bullet(this, this->direction, this->speed * 2, this->bullet_texture, pos));
}


void Entity::fire(sf::Vector2i direction) {
    if(!this->bullet_texture) return;

    double width_mod  = 0;
    double height_mod = 0;

    sf::FloatRect size_box = this->sprite.getGlobalBounds();
    
    width_mod  = size_box.width / 2;
    height_mod = size_box.height / 2;

    sf::Vector2f pos = this->sprite.getPosition();
    pos.x += width_mod;
    pos.y += height_mod;

    this->bullets->push_back(Bullet(this, direction, this->speed * 2, this->bullet_texture, pos));
}

sf::Vector2i Entity::getDirection() {
    return this->direction;
}


void Entity::changeDirection(sf::Vector2i new_direction) {
    this->direction = new_direction;

    // TODO: Change sprite direction information

    return;
}


void Entity::setPosition(sf::Vector2f pos) {
    this->sprite.setPosition(pos);

    return;
}


sf::Vector2f Entity::getPosition() {
    return this->sprite.getPosition();
}


sf::Sprite Entity::getSprite() {
    return this->sprite;
}


int Entity::getHealth() {
    return this->health;
}


double Entity::getSpeed() {
    return this->speed;
}


#endif

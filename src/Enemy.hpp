#ifndef ENEMY_HPP
#define ENEMY_HPP


#include <cmath>
#include <SFML/Graphics.hpp>
#include "Bullet.hpp"
#include "Entity.hpp"


enum EnemyType {
    Runner,
    Shooter
};


class Enemy: public Entity {
    public:
        Enemy(EnemyType type, Entity *player, int max_health, double speed, sf::Sprite sprite);
        Enemy(EnemyType type, Entity *player, int max_health, double speed, sf::Sprite sprite, sf::Texture *bullet_texture, std::vector<Bullet> *bullets);

        void step();


    private:
        EnemyType type;
        Entity    *player;
};

#endif

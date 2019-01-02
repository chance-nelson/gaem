#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Entity.hpp"
#include "Bullet.hpp"
#include "Enemy.hpp"


const double       FRAME_STEP = ((1/60) * 1000);
const sf::Vector2f SPRITE_SCALE(2, 2);


int main() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1366, 768), "SFML window", sf::Style::Fullscreen);
    
    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile("../assets/font.ttf")) return EXIT_FAILURE;
    sf::Text text("My original Sonic OC DO NOT STEAL", font, 10);

    sf::Texture background_texture;
    background_texture.loadFromFile("../assets/background.png");
    sf::Sprite background(background_texture);

    std::vector<Bullet> bullets;
    std::vector<Enemy>  enemies;

    // Init Player 
    sf::Texture player_texture;
    sf::Texture player_bullet_texture;
    player_bullet_texture.loadFromFile("../assets/player_bullet.png");
    player_texture.loadFromFile("../assets/player.png");
    sf::Sprite player_sprite(player_texture);
    player_sprite.setScale(SPRITE_SCALE);
    Entity player(100, .5, player_sprite, &player_bullet_texture, &bullets); 

   sf::Texture em_texture;
   em_texture.loadFromFile("../assets/em.png");
   srand(time(NULL));
    // Init Enemy
    for(int i = 0; i < 10; i++) {
        sf::Vector2f pos(rand() % 1366 + 1, rand() % 768 + 1);
        sf::Sprite *em_sprite = new sf::Sprite(em_texture);
        em_sprite->setScale(SPRITE_SCALE);
        em_sprite->setPosition(pos);
        Enemy *em = new Enemy(EnemyType::Runner, &player, 10, .25, *em_sprite);
        
        enemies.push_back(*em);
    }


    sf::Clock last_frame;
    sf::Clock last_player_shoot;

    // Start the game loop 
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed) window.close();
        }

        sf::Vector2f player_pos             = player.getPosition();
        sf::Vector2i player_direction       = sf::Vector2i(0, 0);
        sf::Vector2i player_shoot_direction = sf::Vector2i(0 ,0);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            player_shoot_direction.x = -1;
        }
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            player_shoot_direction.x = 1;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            player_shoot_direction.y = -1;
        }
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            player_shoot_direction.y = 1;
        }

        if(player_shoot_direction.x != 0 || player_shoot_direction.y != 0) { 
            if(last_player_shoot.getElapsedTime().asMilliseconds() > (100)) {
                player.fire(player_shoot_direction);
                last_player_shoot.restart();
            }           
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            player_pos.x -= player.getSpeed();
            player_direction.x = -1;
        }
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            player_pos.x += player.getSpeed();
            player_direction.x = 1;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            player_pos.y -= player.getSpeed();
            player_direction.y = -1;
        }
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            player_pos.y += player.getSpeed();
            player_direction.y = 1;
        }

        if(player_direction.x != 0 || player_direction.y != 0) {
            player.changeDirection(player_direction);
        }

        player.setPosition(player_pos);

        sf::Time frame_time = last_frame.getElapsedTime();

        while(frame_time.asMilliseconds() < FRAME_STEP) {
            frame_time = last_frame.getElapsedTime();
            continue;
        }

        last_frame.restart();

        window.clear(sf::Color(100, 100, 100));
        
        window.draw(background);

        window.draw(player.getSprite());

        int i = 0;
        while(i < bullets.size()) {
            bullets[i].step();

            // Remove bullets that go off screen
            sf::Vector2f position = bullets[i].getSprite().getPosition();
            if(0 > position.x || position.x > 2000) {
                bullets.erase(bullets.begin() + i);
                i++;
                continue;
            } else if (0 > position.y || position.y > 2000) {
                bullets.erase(bullets.begin() + i);
                i++;
                continue;
            }

            // Check collision
            int entity = 0;
            bool bullet_collide = false;
            while(entity < enemies.size()) {
                sf::Sprite enemy  = enemies[entity].getSprite();
                sf::Sprite bullet = bullets[i].getSprite();
                if(bullet.getGlobalBounds().intersects(enemy.getGlobalBounds())) {
                    enemies.erase(enemies.begin() + entity);
                    bullets.erase(bullets.begin() + i);
                    bullet_collide = true;
                    
                    sf::Vector2f pos(rand() % 1366 + 1, rand() % 768 + 1);
                    sf::Sprite *em_sprite = new sf::Sprite(em_texture);
                    em_sprite->setScale(SPRITE_SCALE);
                    em_sprite->setPosition(pos);
                    Enemy *em = new Enemy(EnemyType::Runner, &player, 10, .25, *em_sprite);
                    
                    enemies.push_back(*em);
                    
                    break;
                }

                entity++;
            }

            if(!bullet_collide) {
                window.draw(bullets[i].getSprite());
            }

            i++;
        }

        i = 0;
        while(i < enemies.size()) {
            enemies[i].step(); 

            sf::Sprite enemy = enemies[i].getSprite();
            
            if(enemy.getGlobalBounds().intersects(player.getSprite().getGlobalBounds())) {
                sf::Vector2f newpos(0, 0);
                player.setPosition(newpos);
            }

            window.draw(enemies[i].getSprite());
            sf::Vector2f pos = enemies[i].getSprite().getPosition();
            i++;
        }

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}

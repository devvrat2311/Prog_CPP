#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <cwchar>

class Player {
private:
  sf::RectangleShape shape;
  sf::Vector2f position;
  sf::Vector2f velocity;
  sf::Vector2f acceleration;

  bool isJumping = false;
  float jumpVelocity = -450.f;
  float gravity = 980.f;
  float maxFallSpeed = 800.f;
  float moveSpeed = 300.f;
  float accelRate = 1500.f;
  float decelRate = 750.f;

  sf::FloatRect currentObject;
  sf::RectangleShape currOb;

  sf::Texture texture;
  sf::Sprite sprite;

public:
  Player();
  Player(float, float);

  void move(float x, float y, float dtime, sf::RenderWindow &window,
            const std::vector<sf::RectangleShape> &map_objects);
  void move_stop(sf::RenderWindow &window);

  bool checkCollision(const sf::RectangleShape &map_object);
  bool checkCollisions(const std::vector<sf::RectangleShape> &map_objects);

  void render(sf::RenderWindow &window);

  void applyPhysics(float deltaTime);
  void applyGravity(float deltaTime);
  void jump();
  void update(float deltaTime,
              const std::vector<sf::RectangleShape> &map_objects,
              sf::RenderWindow &window);

  // Other Methods as needed
};

#endif

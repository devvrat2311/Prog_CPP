#include "../include/player.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

Player::Player() {
  // shape.setSize(sf::Vector2f(50.f, 50.f));
  if (!texture.loadFromFile("../jason.png")) {
    std::cout << "herro no sprite-o\n";
  }
  sprite.setTexture(texture);

  sprite.setPosition(100.f, 100.f);
  sprite.setScale(0.7f, 0.7f);

  shape.setSize(sf::Vector2f(20.f, 20.f));
  shape.setFillColor(sf::Color::Red);
  position = sf::Vector2f(100.f, 100.f);
  velocity = sf::Vector2f(0.f, 0.f);
  acceleration = sf::Vector2f(0.f, 0.f);
}

Player::Player(float pos_x, float pos_y) {
  if (!texture.loadFromFile("./jason.png")) {
    // std::cout << "hero no sprito\n";
  }
  sprite.setTexture(texture);

  sprite.setPosition(100.f, 100.f);
  // sprite.setScale(0.5f, 0.5f);

  shape.setSize(sf::Vector2f(20.f, 50.f));
  shape.setFillColor(sf::Color::Blue);
  position = sf::Vector2f(pos_x, pos_y);
  velocity = sf::Vector2f(0.f, 0.f);
  acceleration = sf::Vector2f(0.f, 0.f);
}

void Player::move(float x, float y, float dtime, sf::RenderWindow &window,
                  const std::vector<sf::RectangleShape> &map_objects) {
  acceleration.x = x * accelRate;
  velocity.x += acceleration.x * dtime;

  // max velocity constraint
  if (velocity.x > moveSpeed)
    velocity.x = moveSpeed;
  if (velocity.x < -moveSpeed)
    velocity.x = -moveSpeed;

  float newX = position.x + velocity.x * dtime;
  float newY = position.y + velocity.y * dtime;

  sf::Vector2f tempPosition = position;
  tempPosition.x = newX;
  sprite.setPosition(tempPosition);

  if (!checkCollisions(map_objects)) {
    position.x = newX;
  } else {
    velocity.x = 0;
  }

  tempPosition.y = newY;
  sprite.setPosition(tempPosition);

  if (!checkCollisions(map_objects)) {
    position.y = newY;
  } else {
    velocity.y = 0;
    // isJumping = false;
  }

  // boundary collision control
  if (position.x < 0) {
    position.x = 0;
    velocity.x = 0;
  } else if (position.x + sprite.getGlobalBounds().width > window.getSize().x) {
    position.x = window.getSize().x - sprite.getGlobalBounds().width;
    velocity.x = 0;
  }

  if (position.y < 0) {
    position.y = 0;
    velocity.y = 0;
  } else if (position.y + sprite.getGlobalBounds().height >
             window.getSize().y) {
    position.y = window.getSize().y - sprite.getGlobalBounds().height;
    velocity.y = 0;
    isJumping = false;
  }
  // shape.setPosition(position);
  sprite.setPosition(position);
}

bool Player::checkCollision(const sf::RectangleShape &mapObject) {
  // get the bounding box of the player
  sf::FloatRect playerbounds = sprite.getGlobalBounds();

  // get the bounding box of the map object
  sf::FloatRect mapObjectBounds = mapObject.getGlobalBounds();
  // std::cout << (playerbounds.intersects(mapObjectBounds) ? "yes\n" : "");
  if (playerbounds.intersects(mapObjectBounds)) {

    //horizontal collision
    if (playerbounds.left < mapObjectBounds.left + mapObjectBounds.width &&
        playerbounds.left + playerbounds.width >
            mapObjectBounds.left + mapObjectBounds.width) {
      currentObject = mapObjectBounds;
      position.x = mapObjectBounds.left + mapObjectBounds.width;
      velocity.x = 0;
      shape.setFillColor(sf::Color::Yellow);
    } else if (playerbounds.left < mapObjectBounds.left &&
               playerbounds.left + playerbounds.width > mapObjectBounds.left) {
      currentObject = mapObjectBounds;
      position.x = mapObjectBounds.left - playerbounds.width;
      velocity.x = 0;
      shape.setFillColor(sf::Color::Yellow);
    }

    //vertical collision(platform floor and ceiling)
    else if (playerbounds.top < mapObjectBounds.top &&
             playerbounds.top + playerbounds.height > mapObjectBounds.top) {
      // Falling onto the platform
      currentObject = mapObjectBounds;
      position.y = mapObjectBounds.top - playerbounds.height;
      velocity.y = 0;    // Stop downward movement1
      isJumping = false; // Player has landed
      gravity = 0.f;     // VVVIMPORTENT
      shape.setFillColor(sf::Color::Blue);
    } else if (playerbounds.top > mapObjectBounds.top &&
               playerbounds.top <
                   mapObjectBounds.top + mapObjectBounds.height) {
      // Jumping and hitting the bottom of the platform
      // isJumping = false;
      position.y = mapObjectBounds.top + mapObjectBounds.height;
      velocity.y = 0; // Stop upward movement
      shape.setFillColor(sf::Color::Red);
    }

    return true;
  }

  else if (playerbounds.left + playerbounds.width < currentObject.left ||
           playerbounds.left > currentObject.left + currentObject.width) {
    gravity = 980.f;
    isJumping = true;
    shape.setFillColor(sf::Color(140, 140, 200));
  }

  return false;
}

bool Player::checkCollisions(
    const std::vector<sf::RectangleShape> &map_objects) {

  for (const auto map_object : map_objects) {
    if (checkCollision(map_object)) {
      return true;
    }
  }
  return false;
}

void Player::move_stop(sf::RenderWindow &window) {
  velocity = sf::Vector2f(0.f, 0.f);
  acceleration = sf::Vector2f(0.f, 0.f);
}

void Player::render(sf::RenderWindow &window) {
  // shape.setPosition(position);
  window.draw(shape);
  window.draw(sprite);
}

void Player::applyPhysics(float deltaTime) {

  velocity.y += (gravity)*deltaTime; // applying gravitS

  // setting maxFallSpeed under the influence of gravity
  if (velocity.y > maxFallSpeed) {
    velocity.y = maxFallSpeed;
  }

  // Apply deceleration when no key is pressed (smoothing movement)
  if (acceleration.x == 0) {
    // std::cout << "decelration executed \n";
    if (velocity.x > 0) {
      velocity.x -= decelRate * deltaTime;
      if (velocity.x < 0)
        velocity.x = 0;
    } else if (velocity.x < 0) {
      velocity.x += decelRate * deltaTime;
      if (velocity.x > 0)
        velocity.x = 0;
    }
  }

  // Update position based on velocity
  position += velocity * deltaTime;

  // Update the player's shape position
  // shape.setPosition(position);
}

void Player::applyGravity(float deltaTime) {
  sf::Vector2f gravity(0.f, 400.f);
  velocity += gravity * deltaTime;
}

void Player::jump() {
  if (!isJumping) {
    isJumping = true;
    velocity.y = jumpVelocity;
    gravity = 980.f;
  }
}

void Player::update(float deltaTime,
                    const std::vector<sf::RectangleShape> &map_objects,
                    sf::RenderWindow &window) {
  // applyGravity(deltaTime);

  applyPhysics(deltaTime); // sets position

  if (acceleration.x < 0) {
    sprite.setOrigin(sprite.getGlobalBounds().width, 0.f);
    sprite.setScale(-1.f, 1.f);
  } else if (acceleration.x > 0) {
    sprite.setOrigin(0.f, 0.f);
    sprite.setScale(1.f, 1.f);
  }
  // system("clear");
  // if (shape.getFillColor() == sf::Color::Yellow) {
  //   std::cout << std::endl;
  //   std::cout << "acceleration:\t" << acceleration.x << "," << acceleration.y
  //             << '\n';
  //   std::cout << "velocity:\t" << velocity.x << "," << velocity.y << '\n';
  //   std::cout << "position:\t" << position.x << "," << position.y << '\n';
  //   std::cout << "gravity:\t" << gravity << "\nnormal: \t" << '\n';
  //   std::cout << std::endl;
  // }
}

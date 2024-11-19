#include "../include/player.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/System.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Joystick.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Window.hpp>
#include <cstdlib>
#include <vector>

// using namespace sf;

int main() {
  sf::RenderWindow window(sf::VideoMode(1024, 720), "bounzer");
  Player player(50, 100);
  Player playertwo;
  sf::Clock clock;

  std::vector<sf::RectangleShape> map_objects;

  sf::RectangleShape mapOb1(sf::Vector2f(700.f, 40.f));
  mapOb1.setPosition(sf::Vector2f(50.f, window.getSize().y - 150.f));
  map_objects.push_back(mapOb1);

  sf::RectangleShape mapOb2(sf::Vector2f(200.f, 40.f));
  mapOb2.setPosition(sf::Vector2f(140.f, window.getSize().y - 300.f));
  map_objects.push_back(mapOb2);

  while (window.isOpen()) {
    sf::Time deltaTime = clock.restart();
    float dtime = deltaTime.asSeconds();

    sf::Event event;
    while (window.pollEvent(event)) { // event loop
      if (event.type == sf::Event::Closed)
        window.close();
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
          window.close();
        }
      }
    }
    float moveX = 0.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
      player.jump();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
      moveX = -1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
      moveX = 1.f;
    }
    if (sf::Joystick::isConnected(0)) {
      float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
      if (x > 20) {
        moveX = 1.f;
      } else if (x < -20) {
        moveX = -1.f;
      }
      if (sf::Joystick::isButtonPressed(0, 0)) {
        player.jump();
      }
      if (sf::Joystick::isButtonPressed(0, 6)) {
        window.close();
      }
    }

    player.move(moveX, 0, dtime, window, map_objects);
    player.update(dtime, map_objects, window); // sets position
    window.clear();
    for (const auto &map_object : map_objects) {
      window.draw(map_object);
    }
    player.render(window); // only draws, does not set position
    window.display();
  }
  return 0;
}

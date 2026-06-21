#include <SFML/Graphics.hpp>

int main() {
  sf::RenderWindow window(sf::VideoMode({800, 600}), "Pong");
  sf::CircleShape shape(10.f);
  shape.setFillColor(sf::Color::Magenta);
  shape.setPosition(sf::Vector2f((800.f / 2 - 10.f / 2), (600.f / 2 - 10.f / 2)));

  sf::RectangleShape leftPaddle;
  leftPaddle.setSize(sf::Vector2f(15, 80));
  leftPaddle.setOutlineColor(sf::Color::Cyan);
  leftPaddle.setOutlineThickness(2);
  leftPaddle.setPosition(sf::Vector2f(10.f, (600.f / 2 - 80.f / 2)));

  sf::RectangleShape rightPaddle;
  rightPaddle.setSize(sf::Vector2f(15, 80));
  rightPaddle.setOutlineColor(sf::Color::Red);
  rightPaddle.setOutlineThickness(2);
  rightPaddle.setPosition(sf::Vector2f((800.f - 10.f - 15.f), (600.f / 2 - 80.f / 2)));

  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) window.close();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
      if () {
        leftPaddle.move(sf::Vector2f(0.f, -5.f));
      }
    }

    window.clear();
    window.draw(shape);
    window.draw(leftPaddle);
    window.draw(rightPaddle);
    window.display();
  }

  return 0;
}
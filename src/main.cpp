#include <SFML/Graphics.hpp>

int main() {
  sf::RenderWindow window(sf::VideoMode({800, 600}), "Pong");
  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Magenta);

  sf::RectangleShape rectangle;
  rectangle.setSize(sf::Vector2f(100, 50));
  rectangle.setOutlineColor(sf::Color::Red);
  rectangle.setOutlineThickness(5);
  rectangle.setPosition(sf::Vector2f(10.f, 20.f));

  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) window.close();
    }

    window.clear();
    window.draw(shape);
    window.draw(rectangle);
    window.display();
  }

  return 0;
}
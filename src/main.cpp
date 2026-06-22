#include <SFML/Graphics.hpp>

int main() {
  sf::RenderWindow window(sf::VideoMode({800, 600}), "Pong");
  sf::CircleShape shape(10.f);
  shape.setFillColor(sf::Color::White);
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

  sf::Vector2f ballVelocity(0.1f, 0.1f);

  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) window.close();
    }

    shape.move(ballVelocity);
    if (shape.getGlobalBounds().findIntersection(leftPaddle.getGlobalBounds())) {
      ballVelocity.x = -ballVelocity.x;
    }

    if (shape.getGlobalBounds().findIntersection(rightPaddle.getGlobalBounds())) {
      ballVelocity.x = -ballVelocity.x;
    }

    if (shape.getPosition().y <= 0 || shape.getPosition().y + 20 >= 600) {
      ballVelocity.y = -ballVelocity.y;
    }
    // умова відбиття від бокових стіном, коли налаштуються ракетки - прибрати
    if (shape.getPosition().x <= 0 || shape.getPosition().x + 20 >= 800) {
      ballVelocity.x = -ballVelocity.x;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && leftPaddle.getPosition().y > 0) {
      leftPaddle.move(sf::Vector2f(0.f, -0.5f));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && rightPaddle.getPosition().y > 0) {
      rightPaddle.move(sf::Vector2f(0.f, -0.5f));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && leftPaddle.getPosition().y + 80 < 600) {
      leftPaddle.move(sf::Vector2f(0.f, 0.5f));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) &&
        rightPaddle.getPosition().y + 80 < 600) {
      rightPaddle.move(sf::Vector2f(0.f, 0.5f));
    }

    window.clear();
    window.draw(shape);
    window.draw(leftPaddle);
    window.draw(rightPaddle);
    window.display();
  }

  return 0;
}
#include "Menu.h"

Menu::Menu(const sf::Font& font, std::string startText, std::string quitText)
    : start(font), quit(font), arrowShape(3) {
  start.setString(startText);
  start.setCharacterSize(40);
  start.setFillColor(sf::Color::White);
  start.setPosition(sf::Vector2f(300.f, 250.f));

  quit.setString(quitText);
  quit.setCharacterSize(40);
  quit.setFillColor(sf::Color::White);
  quit.setPosition(sf::Vector2f(300.f, 320.f));

  // Задаємо координати точок для трикутника
  arrowShape.setPoint(0, sf::Vector2f(0.f, 0.f));
  arrowShape.setPoint(1, sf::Vector2f(100.f, 50.f));
  arrowShape.setPoint(2, sf::Vector2f(0.f, 100.f));

  // Додаткові налаштування(колір, позиція тощо)
  arrowShape.setFillColor(sf::Color::Green);
  arrowShape.setPosition(sf::Vector2f(200.f, 150.f));
};
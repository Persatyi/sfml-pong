#include "Menu.h"

Menu::Menu(const sf::Font& font, std::string startText, std::string quitText)
    : start(font), quit(font) {
  start.setString(startText);
  start.setCharacterSize(40);
  start.setFillColor(sf::Color::White);
  start.setPosition(sf::Vector2f(300.f, 250.f));

  quit.setString(quitText);
  quit.setCharacterSize(40);
  quit.setFillColor(sf::Color::White);
  quit.setPosition(sf::Vector2f(300.f, 320.f));
};
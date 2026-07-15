#ifndef MENU_H_
#define MENU_H_

#include <SFML/Graphics.hpp>

#include "GameEnums.h"

class Menu {
 public:
  Menu(const sf::Font& font, std::string start, std::string quit);

  sf::Text& getStartText() {
    return start;
  }

  sf::Text& getQuitText() {
    return quit;
  }

  sf::ConvexShape& getArrowShape() {
    return arrowShape;
  }

  void updateMenuVisuals();

  void handleInput(const sf::Event& event);

  GameState getSelected();

 private:
  // стан для визначення який пункт меню вибрано
  int selectedItem = MenuItem::Start;
  sf::ConvexShape arrowShape;
  sf::Text start;
  sf::Text quit;
};

#endif  // MENU_H_
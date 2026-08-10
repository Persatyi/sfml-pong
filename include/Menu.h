#ifndef MENU_H_
#define MENU_H_

#include <SFML/Graphics.hpp>

#include "GameEnums.h"

class Menu {
 public:
  Menu(const sf::Font& font, std::string startText, std::string settingsText, std::string quitText);

  sf::Text& getStartText() {
    return start;
  }

  sf::Text& getQuitText() {
    return quit;
  }

  sf::Text& getReadyText() {
    return ready;
  }

  sf::Text& getSettingsText() {
    return settings;
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
  sf::Text settings;
  sf::Text quit;
  sf::Text ready;
};

class PauseMenu {
 public:
  PauseMenu(const sf::Font& font);

  sf::Text& getPausedText() {
    return paused;
  }

  sf::Text& getRestartText() {
    return restart;
  }

  sf::Text& getSettingsText() {
    return settings;
  }

 private:
  sf::Text paused;
  sf::Text restart;
  sf::Text settings;
};

#endif  // MENU_H_
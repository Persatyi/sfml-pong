#ifndef MENU_H_
#define MENU_H_

#include <SFML/Graphics.hpp>

class Menu {
 public:
  Menu(const sf::Font& font, std::string start, std::string quit);

  sf::Text& getStartText() {
    return start;
  }

  sf::Text& getQuitText() {
    return quit;
  }

 private:
  sf::Text start;
  sf::Text quit;
};

#endif  // MENU_H_
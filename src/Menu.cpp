#include "Menu.h"

Menu::Menu(const sf::Font& font, std::string startText, std::string quitText)
    : start(font), quit(font), arrowShape(3) {
  start.setString(startText);
  start.setCharacterSize(40);
  start.setPosition(sf::Vector2f(300.f, 250.f));

  quit.setString(quitText);
  quit.setCharacterSize(40);
  quit.setPosition(sf::Vector2f(300.f, 320.f));

  // Задаємо координати точок для трикутника
  arrowShape.setPoint(0, sf::Vector2f(0.f, 0.f));
  arrowShape.setPoint(1, sf::Vector2f(40.f, 20.f));
  arrowShape.setPoint(2, sf::Vector2f(0.f, 40.f));
  // Додаткові налаштування(колір)
  arrowShape.setFillColor(sf::Color::Green);

  updateMenuVisuals();
};

void Menu::updateMenuVisuals() {
  if (selectedItem == Start) {
    start.setFillColor(sf::Color::Green);
    quit.setFillColor(sf::Color::White);
  } else if (selectedItem == Quit) {
    start.setFillColor(sf::Color::White);
    quit.setFillColor(sf::Color::Green);
  }
  // Додаткові налаштування(вирахування позиції трикутника)
  // 2. Рахуємо позицію трикутника математично
  // 255 — стартова позиція по Y. 72 — крок між пунктами (327 - 255)
  float arrowY = 255.f + static_cast<float>(selectedItem) * 72.f;
  arrowShape.setPosition(sf::Vector2f(245.f, arrowY));
}

void Menu::handleInput(const sf::Event& event) {
  if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
    if (keyPressed->code == sf::Keyboard::Key::Down && selectedItem < Quit) {
      selectedItem++;
      updateMenuVisuals();
    } else if (keyPressed->code == sf::Keyboard::Key::Up && selectedItem > Start) {
      selectedItem--;
      updateMenuVisuals();
    }
  }
}

GameState Menu::getSelected() {
  switch (selectedItem) {
    case MenuItem::Start:
      return GameState::WaitingToStart;
    case MenuItem::Quit:
      return GameState::Quit;
  }
}
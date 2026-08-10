#include "Menu.h"

Menu::Menu(const sf::Font& font, std::string startText, std::string settingsText,
           std::string quitText)
    : start(font), settings(font), quit(font), arrowShape(3), ready(font) {
  start.setString(startText);
  start.setCharacterSize(40);
  start.setPosition(sf::Vector2f(300.f, 250.f));

  settings.setString(settingsText);
  settings.setCharacterSize(40);
  settings.setPosition(sf::Vector2f(300.f, 320.f));

  quit.setString(quitText);
  quit.setCharacterSize(40);
  quit.setPosition(sf::Vector2f(300.f, 390.f));

  ready.setString("Press space to start");
  ready.setCharacterSize(20);
  ready.setPosition(sf::Vector2f(300.f, 320.f));
  ready.setFillColor(sf::Color::Green);

  // Задаємо координати точок для трикутника
  arrowShape.setPoint(0, sf::Vector2f(0.f, 0.f));
  arrowShape.setPoint(1, sf::Vector2f(40.f, 20.f));
  arrowShape.setPoint(2, sf::Vector2f(0.f, 40.f));
  // Додаткові налаштування(колір)
  arrowShape.setFillColor(sf::Color::Green);

  updateMenuVisuals();
}

void Menu::updateMenuVisuals() {
  switch (selectedItem) {
    case Start:
      start.setFillColor(sf::Color::Green);
      settings.setFillColor(sf::Color::White);
      break;
    case Settings:
      start.setFillColor(sf::Color::White);
      settings.setFillColor(sf::Color::Green);
      quit.setFillColor(sf::Color::White);
      break;
    case Quit:
      settings.setFillColor(sf::Color::White);
      quit.setFillColor(sf::Color::Green);
      break;
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
    case MenuItem::Settings:
      return GameState::Settings;
    default:
      return GameState::Menu;
  }
}

// Реалізація меню паузи
PauseMenu::PauseMenu(const sf::Font& font) : paused(font), restart(font), settings(font) {
  paused.setString("Paused");
  paused.setCharacterSize(30);
  paused.setPosition(sf::Vector2f(340.f, 110.f));
  paused.setFillColor(sf::Color::Yellow);

  restart.setString("Restart");
  restart.setCharacterSize(30);
  restart.setPosition(sf::Vector2f(340.f, 180.f));
  restart.setFillColor(sf::Color::White);

  settings.setString("Settings");
  settings.setCharacterSize(30);
  settings.setPosition(sf::Vector2f(340.f, 250.f));
  settings.setFillColor(sf::Color::White);
}
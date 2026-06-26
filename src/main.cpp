#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <string>

int main() {
  sf::RenderWindow window(sf::VideoMode({800, 600}), "Pong");

  // підключаєм шрифт
  sf::Font font;
  if (!font.openFromFile("assets/fonts/BlackOpsOne-Regular.ttf")) {
    return -1;
  }

  // Змінні для підрахунку очок
  int leftScore = 0;
  int rightScore = 0;

  // Створюєм текст для рахунку
  sf::Text scoreText(font);
  scoreText.setCharacterSize(30);
  scoreText.setFillColor(sf::Color::White);
  scoreText.setString(std::to_string(leftScore) + " : " + std::to_string(rightScore));
  sf::FloatRect textBounds = scoreText.getLocalBounds();
  scoreText.setPosition(sf::Vector2f(400.f - textBounds.size.x / 2.f, 10.f));

  // Колір і розмір м'яча
  sf::CircleShape shape(10.f);
  shape.setFillColor(sf::Color::White);
  shape.setPosition(sf::Vector2f((800.f / 2 - 10.f / 2), (600.f / 2 - 10.f / 2)));

  // Центральна розділювальна лінія
  sf::RectangleShape dividingLine;
  dividingLine.setSize(sf::Vector2f(1, 600));
  dividingLine.setFillColor(sf::Color::White);
  dividingLine.setPosition(sf::Vector2f(400.f, 0.f));

  // Розміри ракеток і їхнє положення
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

  // швидкість руху м'яча
  sf::Vector2f ballVelocity(0.1f, 0.1f);

  // один раз до циклу
  srand(time(nullptr));

  // Цикл для роботи нашої програми
  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) window.close();
    }

    shape.move(ballVelocity);
    // умови для роботи ракеток
    if (shape.getGlobalBounds().findIntersection(leftPaddle.getGlobalBounds())) {
      ballVelocity.x = -ballVelocity.x;
    }

    if (shape.getGlobalBounds().findIntersection(rightPaddle.getGlobalBounds())) {
      ballVelocity.x = -ballVelocity.x;
    }

    if (shape.getPosition().y <= 0 || shape.getPosition().y + 20 >= 600) {
      ballVelocity.y = -ballVelocity.y;
    }

    // Обробляємо рахунок як тільки м'ячик вилетів за межі
    if (shape.getPosition().x < 0) {
      rightScore++;
      scoreText.setString(std::to_string(leftScore) + " : " + std::to_string(rightScore));
      // скинути м'яч по центру
      shape.setPosition(sf::Vector2f(390.f, 290.f));
      // перевіряємо чи текст не змінив свою ширини і перераховуємо (потрібно для того щоб стояв
      // чітко по центру)
      sf::FloatRect textBounds = scoreText.getLocalBounds();
      scoreText.setPosition(sf::Vector2f(400.f - textBounds.size.x / 2.f, 10.f));

      // змінюємо швидкість і кут польоту м'яча після скидання
      // float dirY = (rand() % 3 + 1) * (rand() % 2 == 0 ? 0.1f : -0.1f);
      // ballVelocity = sf::Vector2f(-0.1f, dirY);
    }

    if (shape.getPosition().x + 20 >= 800) {
      leftScore++;
      scoreText.setString(std::to_string(leftScore) + " : " + std::to_string(rightScore));
      // скинути м'яч по центру
      shape.setPosition(sf::Vector2f(390.f, 290.f));
      // перевіряємо чи текст не змінив свою ширини і перераховуємо (потрібно для того щоб стояв
      // чітко по центру)
      sf::FloatRect textBounds = scoreText.getLocalBounds();
      scoreText.setPosition(sf::Vector2f(400.f - textBounds.size.x / 2.f, 10.f));

      // змінюємо швидкість і кут польоту м'яча після скидання
      // float dirY = (rand() % 3 + 1) * (rand() % 2 == 0 ? 0.1f : -0.1f);
      // ballVelocity = sf::Vector2f(0.1f, dirY);
    }

    // умови для керування ракетками
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
    window.draw(scoreText);
    window.draw(shape);
    window.draw(dividingLine);
    window.draw(leftPaddle);
    window.draw(rightPaddle);
    window.display();
  }

  return 0;
}

// розбиваємо по різних файлах
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "Ball.h"
#include "GameEnums.h"
#include "Menu.h"
#include "Paddle.h"

int main() {
  sf::RenderWindow window(sf::VideoMode({800, 600}), "Pong");

  // підключаєм шрифт
  sf::Font font;
  if (!font.openFromFile("assets/fonts/BlackOpsOne-Regular.ttf")) {
    std::cerr << "Error loading font\n";
    return -1;
  }

  // Змінні для підрахунку очок
  int leftScore = 0;
  int rightScore = 0;

  // меню
  Menu menu(font, "Start", "Quit");

  // Створюєм текст для рахунку
  sf::Text scoreText(font);
  scoreText.setCharacterSize(30);
  scoreText.setFillColor(sf::Color::White);
  scoreText.setString(std::to_string(leftScore) + " : " + std::to_string(rightScore));
  sf::FloatRect textBounds = scoreText.getLocalBounds();
  scoreText.setPosition(sf::Vector2f(400.f - textBounds.size.x / 2.f, 10.f));

  // Колір і розмір м'яча
  Ball ball(10.f, (800.f / 2 - 10.f / 2), (600.f / 2 - 10.f / 2), 0.1f, 0.1f, sf::Color::White);

  // Центральна розділювальна лінія
  sf::RectangleShape dividingLine;
  dividingLine.setSize(sf::Vector2f(1, 600));
  dividingLine.setFillColor(sf::Color::White);
  dividingLine.setPosition(sf::Vector2f(400.f, 0.f));

  // Розміри ракеток і їхнє положення
  Paddle leftPaddle(10.f, (600.f / 2 - 80.f / 2), sf::Color::Cyan);
  Paddle rightPaddle((800.f - 10.f - 15.f), (600.f / 2 - 80.f / 2), sf::Color::Red);

  GameState gameState = GameState::Menu;

  // --- Змінні для мигання ---
  sf::Clock blinkClock;        // Таймер
  bool showText = true;        // Прапорець видимості
  float blinkInterval = 0.5f;  // Інтервал мигання в секундах

  // Цикл для роботи нашої програми
  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>() || gameState == GameState::Quit) window.close();
      if (gameState == GameState::Menu) {
        menu.handleInput(*event);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
          gameState = menu.getSelected();
        }
      }

      // Обробка паузи по клавіші Escape
      if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->code == sf::Keyboard::Key::Escape) {
          if (gameState == GameState::Playing) {
            gameState = GameState::Paused;
          } else if (gameState == GameState::Paused) {
            gameState = GameState::Playing;
          }
        }
      }
    }

    if (gameState == GameState::Menu) {
      window.clear();
      window.draw(menu.getArrowShape());
      window.draw(menu.getStartText());
      window.draw(menu.getQuitText());
      window.display();
    } else if (gameState == GameState::WaitingToStart) {
      // Логіка мигання тексту
      // Якщо з моменту останнього перезапуску таймера пройшло більше ніж 0.5 сек
      if (blinkClock.getElapsedTime().asSeconds() > blinkInterval) {
        showText = !showText;  // Змінюємо видимість на протилежну
        blinkClock.restart();  // Скидаємо таймер
      }

      // Перевіряємо натискання пробілу
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
        gameState = GameState::Playing;
      }

      window.clear();

      // Малюємо текст готовності ТІЛЬКИ якщо showText == true
      if (showText) {
        window.draw(menu.getReadyText());
      }

      window.draw(dividingLine);
      window.draw(leftPaddle.getShape());
      window.draw(rightPaddle.getShape());
      window.display();
    } else if (gameState == GameState::Playing) {
      // рух м'яча
      ball.move();

      // умови для роботи ракеток
      ball.checkPaddleCollision(leftPaddle);
      ball.checkPaddleCollision(rightPaddle);

      // Умова відбиття від верхньої і нижньої стінок
      ball.checkWallCollision(600.f);

      // Обробляємо рахунок як тільки м'ячик вилетів за межі
      if (ball.getShape().getPosition().x < 0) {
        rightScore++;
        scoreText.setString(std::to_string(leftScore) + " : " + std::to_string(rightScore));
        // скинути м'яч по центру
        ball.resetBall(390.f, 290.f);
        // перевіряємо чи текст не змінив свою ширини і перераховуємо (потрібно для того щоб стояв
        // чітко по центру)
        sf::FloatRect textBounds = scoreText.getLocalBounds();
        scoreText.setPosition(sf::Vector2f(400.f - textBounds.size.x / 2.f, 10.f));
      }

      if (ball.getShape().getPosition().x + 20 >= 800) {
        leftScore++;
        scoreText.setString(std::to_string(leftScore) + " : " + std::to_string(rightScore));
        // скинути м'яч по центру
        ball.resetBall(390.f, 290.f);
        // перевіряємо чи текст не змінив свою ширини і перераховуємо (потрібно для того щоб стояв
        // чітко по центру)
        sf::FloatRect textBounds = scoreText.getLocalBounds();
        scoreText.setPosition(sf::Vector2f(400.f - textBounds.size.x / 2.f, 10.f));
      }

      // умови для керування ракетками
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) &&
          leftPaddle.getShape().getPosition().y > 0) {
        leftPaddle.move(0.f, -0.5f);
      }

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) &&
          rightPaddle.getShape().getPosition().y > 0) {
        rightPaddle.move(0.f, -0.5f);
      }

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) &&
          leftPaddle.getShape().getPosition().y + 80 < 600) {
        leftPaddle.move(0.f, 0.5f);
      }

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) &&
          rightPaddle.getShape().getPosition().y + 80 < 600) {
        rightPaddle.move(0.f, 0.5f);
      }

      // Відмальовуємо всі елементи
      window.clear();
      window.draw(scoreText);
      window.draw(ball.getShape());
      window.draw(dividingLine);
      window.draw(leftPaddle.getShape());
      window.draw(rightPaddle.getShape());
      window.display();
    } else if (gameState == GameState::Paused) {
      // тут будемо відмальовувати меню паузи
    }
  }

  return 0;
}

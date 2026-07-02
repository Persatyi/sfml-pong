#ifndef BALL_H_
#define BALL_H_

#include <SFML/Graphics.hpp>

#include "Paddle.h"

class Ball {
 public:
  Ball(float size, float x, float y, float speedX, float speedY, sf::Color color);

  void move();

  void checkWallCollision(float windowHeight);

  void checkPaddleCollision(Paddle& paddle);

  sf::CircleShape& getShape() {
    return shape;
  }

  sf::Vector2f& getVelocity() {
    return ballVelocity;
  }

 private:
  sf::CircleShape shape;
  sf::Vector2f ballVelocity;
};
#endif  // BALL_H_
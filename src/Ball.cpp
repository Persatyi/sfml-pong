#include "Ball.h"

Ball::Ball(float size, float x, float y, float speedX, float speedY, sf::Color color) {
  shape = sf::CircleShape(size);
  shape.setPosition(sf::Vector2f(x, y));
  shape.setFillColor(color);
  // початкова швидкість руху м'яча
  ballVelocity = sf::Vector2f(speedX, speedY);
}

void Ball::move() {
  shape.move(ballVelocity);
}

void Ball::checkWallCollision(float windowHeight) {
  if (shape.getPosition().y <= 0 || shape.getPosition().y + shape.getRadius() * 2 >= windowHeight) {
    ballVelocity.y = -ballVelocity.y;
  }
}

void Ball::checkPaddleCollision(Paddle& paddle) {
  if (shape.getGlobalBounds().findIntersection(paddle.getShape().getGlobalBounds())) {
    ballVelocity.x = -ballVelocity.x;
  }
}
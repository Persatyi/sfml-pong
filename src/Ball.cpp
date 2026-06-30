#include "Ball.h"

Ball::Ball(float size, float x, float y, sf::Color color) {
  sf::CircleShape shape(size);
  shape.setPosition(sf::Vector2f(x, y));
  shape.setFillColor(color);
}

void Ball::move(float x, float y) {
  shape.move(sf::Vector2f(x, y));
}
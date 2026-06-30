#include "Paddle.h"

Paddle::Paddle(float x, float y, sf::Color color) {
  shape.setSize(sf::Vector2f(15, 80));
  shape.setOutlineColor(color);
  shape.setOutlineThickness(2);
  shape.setPosition(sf::Vector2f(x, y));
};

void Paddle::move(float x, float y) {
  shape.move(sf::Vector2f(x, y));
}
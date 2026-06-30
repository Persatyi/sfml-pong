#ifndef PADDLE_H_
#define PADDLE_H_

#include <SFML/Graphics.hpp>

class Paddle {
 public:
  Paddle(float x, float y, sf::Color color);

  sf::RectangleShape& getShape() {
    return shape;
  }

  void move(float x, float y);

  void draw();

 private:
  sf::RectangleShape shape;
};

#endif  // PADDLE_H_
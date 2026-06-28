#ifndef PADDLE_H_
#define PADDLE_H_

#include <SFML/Graphics.hpp>

class Paddle {
  Paddle();

 public:
  void move();

  void draw();

 private:
  sf::RectangleShape shape;
};

#endif  // PADDLE_H_
#ifndef BALL_H_
#define BALL_H_

#include <SFML/Graphics.hpp>

class Ball {
 public:
  Ball(float shape, float x, float y, sf::Color color);

  void move(float x, float y);

  sf::CircleShape& getShape() {
    return shape;
  }

 private:
  sf::CircleShape shape;
};
#endif  // BALL_H_
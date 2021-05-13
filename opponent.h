#include <iostream>
#include "cpputils/graphics/image.h"
#include "game_element.h"
#ifndef OPPONENT_H
#define OPPONENT_H

class Opponent : public GameElement {
 public:
  Opponent() : Opponent(0, 0) {}
  Opponent(int x, int y) : GameElement(x, y, 60, 60) {}

  void Draw(graphics::Image& background) override;
  void Move(const graphics::Image& opponent) override;
};

class OpponentProjectile : public GameElement {
 public:
  OpponentProjectile() : OpponentProjectile(0, 0) {}
  OpponentProjectile(int x, int y) : GameElement(x, y, 15, 15) {}

  void Draw(graphics::Image& background) override;
  void Move(const graphics::Image& oppoProj) override;
};

#endif

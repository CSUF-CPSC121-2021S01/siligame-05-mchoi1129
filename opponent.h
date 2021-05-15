#include <iostream>
#include <memory>
#include "cpputils/graphics/image.h"
#include "game_element.h"
#ifndef OPPONENT_H
#define OPPONENT_H

class OpponentProjectile : public GameElement {
 public:
  OpponentProjectile() : GameElement(0, 0, 15, 15) {}
  OpponentProjectile(int x, int y) : GameElement(x, y, 15, 15) {}

  void Draw(graphics::Image& background) override;
  void Move(const graphics::Image& oppoProj) override;
};

class Opponent : public GameElement {
 public:
  Opponent() : GameElement(0, 0, 60, 60) {}
  Opponent(int x, int y) : GameElement(x, y, 60, 60) {}

  void Draw(graphics::Image& background) override;
  void Move(const graphics::Image& opponent) override;
  std::unique_ptr<OpponentProjectile> LaunchProjectile();

 private:
  int counter = 1;
};

#endif

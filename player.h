#include <iostream>
#include "cpputils/graphics/image.h"
#include "game_element.h"
#include "opponent.h"
#ifndef PLAYER_H
#define PLAYER_H

class Player : public GameElement {
 public:
  Player() : Player(0, 0) {}
  Player(int x, int y) : GameElement(x, y, 60, 60) {}

  void Draw(graphics::Image& background) override;
  // bool IntersectsWith(const Opponent& intersect_opp);
  // bool IntersectsWith(const OpponentProjectile& intersect_opp_proj);
  void Move(const graphics::Image& screen) override;
};

class PlayerProjectile : public GameElement {
 public:
  PlayerProjectile() : PlayerProjectile(0, 0) {}
  PlayerProjectile(int x, int y) : GameElement(x, y, 15, 15) {}

  void Draw(graphics::Image& background) override;
  // bool IntersectsWith(const Opponent& intersect_play);
  void Move(const graphics::Image& screen) override;
};

#endif

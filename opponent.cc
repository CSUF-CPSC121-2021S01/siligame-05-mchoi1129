#include "opponent.h"
#include <iostream>
#include "cpputils/graphics/image.h"

void Opponent::Draw(graphics::Image& background) {
  graphics::Image opponent;
  opponent.Load("Opponent.bmp");
  for (int i = 0; i < opponent.GetWidth(); i++) {
    for (int j = 0; j < opponent.GetHeight(); j++) {
      graphics::Color color = opponent.GetColor(i, j);
      background.SetColor(GetX() + i, GetY() + j, color);
    }
  }
}

void Opponent::Move(const graphics::Image& opponent) {
  SetX(GetX() + 1);
  SetY(GetY() + 1);
  if (IsOutOfBounds(opponent)) {
    SetIsActive(false);
  }
}

void OpponentProjectile::Draw(graphics::Image& background) {
  graphics::Image opp_tile;
  opp_tile.Load("OpponentProjectile.bmp");
  for (int i = 0; i < opp_tile.GetWidth(); i++) {
    for (int j = 0; j < opp_tile.GetHeight(); j++) {
      graphics::Color color = opp_tile.GetColor(i, j);
      background.SetColor(GetX() + i, GetY() + j, color);
    }
  }
}

void OpponentProjectile::Move(const graphics::Image& oppoProj) {
  SetY(GetY() + 3);
  if (IsOutOfBounds(oppoProj)) {
    SetIsActive(false);
  }
}

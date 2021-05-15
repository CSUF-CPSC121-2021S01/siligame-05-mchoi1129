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

void Opponent::Move(const graphics::Image& screen) {
  if (going_right_ && GetX() + GetWidth() >= 800) {
    going_right_ = false;
  } else if (!going_right_ && GetX() <= 0) {
    going_right_ = true;
  }
  int offset = going_right_ ? 1 : -1;
  SetX(GetX() + offset * 5);
  SetY(GetY() + 2);
  if (IsOutOfBounds(screen)) {
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

void OpponentProjectile::Move(const graphics::Image& screen) {
  SetY(GetY() + 3);
  if (IsOutOfBounds(screen)) {
    SetIsActive(false);
  }
}

std::unique_ptr<OpponentProjectile> Opponent::LaunchProjectile() {
  counter++;
  if (counter % 10 == 0) {
    std::unique_ptr<OpponentProjectile> other_proj =
        std::make_unique<OpponentProjectile>(GetX(), GetY() + 70);
    return std::move(other_proj);
  } else {
    return nullptr;
  }
}

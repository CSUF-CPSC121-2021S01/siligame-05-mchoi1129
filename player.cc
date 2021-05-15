#include "player.h"
#include <iostream>
#include "cpputils/graphics/image.h"

void Player::Draw(graphics::Image& background) {
  graphics::Image player;
  player.Load("Player.bmp");
  for (int i = 0; i < player.GetWidth(); i++) {
    for (int j = 0; j < player.GetHeight(); j++) {
      graphics::Color color = player.GetColor(i, j);
      background.SetColor(GetX() + i, GetY() + j, color);
    }
  }
}

void Player::Move(const graphics::Image& screen) {}

void PlayerProjectile::Draw(graphics::Image& background) {
  graphics::Image play_tile;
  play_tile.Load("PlayerProjectile.bmp");
  for (int i = 0; i < play_tile.GetWidth(); i++) {
    for (int j = 0; j < play_tile.GetHeight(); j++) {
      graphics::Color color = play_tile.GetColor(i, j);
      background.SetColor(GetX() + i, GetY() + j, color);
    }
  }
}

void PlayerProjectile::Move(const graphics::Image& screen) {
  SetY(GetY() - 3);
  if (IsOutOfBounds(screen)) {
    SetIsActive(false);
  }
}

/*
bool Player::IntersectsWith(Opponent& intersect_opp) {
  int OppX = intersect_opp.GetX();
  int OppY = intersect_opp.GetY();
  int OppWidth = intersect_opp.GetWidth();
  int OppHeight = intersect_opp.GetHeight();
  if ((x_ >= OppX) && (x_ <= OppX + OppWidth) && (y_ >= OppY) &&
      (y_ <= OppY + OppHeight)) {
    return true;
  } else if ((x_ >= OppX) && (x_ <= OppX + OppWidth) &&
             (y_ + height_ >= OppY) && (y_ + height_ <= OppY + OppHeight)) {
    return true;
  } else if ((x_ + width_ >= OppX) && (x_ + width_ <= OppX + OppWidth) &&
             (y_ + height_ >= OppY) && (y_ + height_ <= OppY + OppHeight)) {
    return true;
  } else if ((x_ + width_ >= OppX) && (x_ + width_ <= OppX + OppWidth) &&
             (y_ >= OppY) && (y_ <= OppY + OppHeight)) {
    return true;
  } else {
    return false;
  }
}

bool Player::IntersectsWith(OpponentProjectile& intersect_opp_proj) {
  int OppX = intersect_opp_proj.GetX();
  int OppY = intersect_opp_proj.GetY();
  int OppWidth = intersect_opp_proj.GetWidth();
  int OppHeight = intersect_opp_proj.GetHeight();
  if ((x_ >= OppX) && (x_ <= OppX + OppWidth) && (y_ >= OppY) &&
      (y_ <= OppY + OppHeight)) {
    return true;
  } else if ((x_ >= OppX) && (x_ <= OppX + OppWidth) &&
             (y_ + height_ >= OppY) && (y_ + height_ <= OppY + OppHeight)) {
    return true;
  } else if ((x_ + width_ >= OppX) && (x_ + width_ <= OppX + OppWidth) &&
             (y_ + height_ >= OppY) && (y_ + height_ <= OppY + OppHeight)) {
    return true;
  } else if ((x_ + width_ >= OppX) && (x_ + width_ <= OppX + OppWidth) &&
             (y_ >= OppY) && (y_ <= OppY + OppHeight)) {
    return true;
  } else {
    return false;
  }
}

bool PlayerProjectile::IntersectsWith(Opponent& intersect_play) {
  int OppX = intersect_play.GetX();
  int OppY = intersect_play.GetY();
  int OppWidth = intersect_play.GetWidth();
  int OppHeight = intersect_play.GetHeight();
  if ((x_ >= OppX) && (x_ <= OppX + OppWidth) && (y_ >= OppY) &&
      (y_ <= OppY + OppHeight)) {
    return true;
  } else if ((x_ >= OppX) && (x_ <= OppX + OppWidth) &&
             (y_ + height_ >= OppY) && (y_ + height_ <= OppY + OppHeight)) {
    return true;
  } else if ((x_ + width_ >= OppX) && (x_ + width_ <= OppX + OppWidth) &&
             (y_ + height_ >= OppY) && (y_ + height_ <= OppY + OppHeight)) {
    return true;
  } else if ((x_ + width_ >= OppX) && (x_ + width_ <= OppX + OppWidth) &&
             (y_ >= OppY) && (y_ <= OppY + OppHeight)) {
    return true;
  } else {
    return false;
  }
}
*/

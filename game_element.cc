#include "game_element.h"

/*void GameElement::Draw(graphics::Image& screen) {
  screen.DrawRectangle(x_, y_, 15, 15, graphics::Color(255, 255, 255));
}*/
void GameElement::PadPoints(std::vector<int>& points, int pad_x, int pad_y) {
  for (int i = 0; i < points.size(); i++) {
    if (i % 2 == 0) {
      points[i] += pad_x;
    } else {
      points[i] += pad_y;
    }
  }
}
bool GameElement::IntersectsWith(GameElement& element) {
  if (element.GetX() >= x_ + width_ ||
      element.GetX() + element.GetWidth() <= x_ ||
      element.GetY() >= y_ + height_ ||
      element.GetY() + element.GetHeight() <= y_) {
    return false;
  } else {
    return true;
  }
}
bool GameElement::IsOutOfBounds(const graphics::Image& object) {
  if (GetX() <= 0 || GetY() <= 0 || GetX() + GetWidth() >= 800 ||
      GetY() + GetHeight() >= 600) {
    return true;
  } else {
    return false;
  }
}

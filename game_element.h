#ifndef GAMEELEMENT_H
#define GAMEELEMENT_H
#include "cpputils/graphics/image.h"

class GameElement {
 public:
  GameElement() : GameElement(0, 0, 50, 50) {}
  GameElement(int x, int y, int width, int height)
      : x_(x), y_(y), width_(width), height_(height) {}

  int GetX() const { return x_; }
  int GetY() const { return y_; }
  void SetX(int x) { x_ = x; }
  void SetY(int y) { y_ = y; }
  int GetWidth() const { return width_; }
  int GetHeight() const { return height_; }
  
  bool GetIsActive() const { return is_active_; }
  void SetIsActive(bool is_active) { is_active_ = is_active; }

  virtual void Draw(graphics::Image& screen) = 0;
  virtual void Move(const graphics::Image& object) = 0;
  bool IntersectsWith(GameElement* element);
  bool IsOutOfBounds(const graphics::Image& screen);

 protected:
  void PadPoints(std::vector<int>& points, int pad_x, int pad_y);

 private:
  int x_ = 0;
  int y_ = 0;
  int width_ = 60;
  int height_ = 60;
  bool is_active_ = true;
};

#endif

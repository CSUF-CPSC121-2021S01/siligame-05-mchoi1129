#ifndef GAME_H
#define GAME_H
#include <vector>
#include <memory>
#include "cpputils/graphics/image_event.h"
#include "opponent.h"
#include "player.h"

class Game : public graphics::AnimationEventListener,
             graphics::MouseEventListener {
 public:
  Game() : Game(800, 600) {}
  Game(int width, int height) : screen_(width, height) {}

  graphics::Image& GetGameScreen() { return screen_; }
  std::vector<std::unique_ptr<Opponent>>& GetOpponents() { return opponent_; }
  std::vector<std::unique_ptr<OpponentProjectile>>& GetOpponentProjectiles() {
    return oppoProj_;
  }
  std::vector<std::unique_ptr<PlayerProjectile>>& GetPlayerProjectiles() { return playProj_; }
  Player& GetPlayer() { return player_; }

  void CreateOpponents();
  void CreateOpponentProjectiles();
  void CreatePlayerProjectiles();
  void Init();
  void UpdateScreen();
  void Start();
  void MoveGameElements();
  void FilterIntersections();
  void OnAnimationStep() override;
  void OnMouseEvent(const graphics::MouseEvent& mouse) override;

  void LaunchProjectiles();
  int GetScore();
  bool HasLost();
  void RemoveInactive();

 private:
  graphics::Image screen_;
  std::vector<std::unique_ptr<Opponent>> opponent_;
  std::vector<std::unique_ptr<OpponentProjectile>> oppoProj_;
  std::vector<std::unique_ptr<PlayerProjectile>> playProj_;
  Player player_;
};

#endif

#ifndef GAME_H
#define GAME_H
#include <vector>
#include "cpputils/graphics/image_event.h"
#include "opponent.h"
#include "player.h"

class Game : public graphics::AnimationEventListener,
             graphics::MouseEventListener {
 public:
  Game() : Game(800, 600) {}
  Game(int width, int height) : screen_(width, height) {}

  graphics::Image& GetGameScreen() { return screen_; }
  std::vector<Opponent>& GetOpponents() { return opponent_; }
  std::vector<OpponentProjectile>& GetOpponentProjectiles() {
    return oppoProj_;
  }
  std::vector<PlayerProjectile>& GetPlayerProjectiles() { return playProj_; }
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

 private:
  graphics::Image screen_;
  std::vector<Opponent> opponent_;
  std::vector<OpponentProjectile> oppoProj_;
  std::vector<PlayerProjectile> playProj_;
  Player player_;
};

#endif
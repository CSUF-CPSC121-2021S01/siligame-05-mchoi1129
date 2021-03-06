#include "game.h"

void Game::CreateOpponents() {
  for (int i = 0; i < 1; i++) {
    std::unique_ptr<Opponent> opponent = std::make_unique<Opponent>(300 * i, 0);
    opponent_.push_back(std::move(opponent));
  }
}
void Game::CreateOpponentProjectiles() {
  for (int i = 0; i < 1; i++) {
    std::unique_ptr<OpponentProjectile> oppoProj =
        std::make_unique<OpponentProjectile>(400 * i, 100);
    oppoProj_.push_back(std::move(oppoProj));
  }
}
void Game::CreatePlayerProjectiles() {
  for (int i = 0; i < 3; i++) {
    std::unique_ptr<PlayerProjectile> playProj =
        std::make_unique<PlayerProjectile>(100 * i, 450);
    playProj_.push_back(std::move(playProj));
  }
}

void Game::UpdateScreen() {
  screen_.DrawRectangle(0, 0, 800, 600, graphics::Color(255, 255, 255));
  for (int i = 0; i < opponent_.size(); i++) {
    if (opponent_[i]->GetIsActive()) {
      opponent_[i]->Draw(screen_);
    }
  }
  for (int j = 0; j < oppoProj_.size(); j++) {
    if (oppoProj_[j]->GetIsActive()) {
      oppoProj_[j]->Draw(screen_);
    }
  }
  for (int k = 0; k < playProj_.size(); k++) {
    if (playProj_[k]->GetIsActive()) {
      playProj_[k]->Draw(screen_);
    }
  }
  if (player_.GetIsActive()) {
    player_.Draw(screen_);
  }
  std::string text = "Score: " + std::to_string(GetScore());
  screen_.DrawText(0, 0, text, 30, graphics::Color(115, 10, 220));
  if (HasLost()) {
    screen_.DrawText(300, 250, "Game Over", 50, graphics::Color(0, 0, 0));
  }
}

void Game::Start() { screen_.ShowUntilClosed(); }

void Game::MoveGameElements() {
  for (int i = 0; i < opponent_.size(); i++) {
    if (opponent_[i]->GetIsActive() && !HasLost()) {
      opponent_[i]->Move(screen_);
    }
  }
  for (int j = 0; j < oppoProj_.size(); j++) {
    if (oppoProj_[j]->GetIsActive() && !HasLost()) {
      oppoProj_[j]->Move(screen_);
    }
  }
  for (int k = 0; k < playProj_.size(); k++) {
    if (playProj_[k]->GetIsActive() && !HasLost()) {
      playProj_[k]->Move(screen_);
    }
  }
}

void Game::FilterIntersections() {
  for (int i = 0; i < opponent_.size(); i++) {
    if (player_.IntersectsWith(opponent_[i].get())) {
      player_.SetIsActive(false);
      opponent_[i]->SetIsActive(false);
      has_lost_ = true;
    }
  }
  for (int j = 0; j < oppoProj_.size(); j++) {
    if (player_.IntersectsWith(oppoProj_[j].get())) {
      player_.SetIsActive(false);
      oppoProj_[j]->SetIsActive(false);
      has_lost_ = true;
    }
  }
  for (int l = 0; l < opponent_.size(); l++) {
    for (int k = 0; k < playProj_.size(); k++) {
      if (playProj_[k]->IntersectsWith(opponent_[l].get())) {
        opponent_[l]->SetIsActive(false);
        playProj_[k]->SetIsActive(false);
        if (player_.GetIsActive()) {
          score_++;
        }
      }
    }
  }
}

void Game::OnMouseEvent(const graphics::MouseEvent& mouse) {
  if (!HasLost()) {
    if (mouse.GetMouseAction() == graphics::MouseAction::kMoved ||
        mouse.GetMouseAction() == graphics::MouseAction::kDragged) {
      int previousX = player_.GetX();
      int previousY = player_.GetY();
      player_.SetX(mouse.GetX() - player_.GetWidth() / 2);
      player_.SetY(mouse.GetY() - player_.GetWidth() / 2);
      if (player_.GetX() <= 0 || player_.GetY() <= 0 ||
          player_.GetX() + player_.GetWidth() >= 800 ||
          player_.GetY() + player_.GetHeight() >= 600) {
        player_.SetX(previousX);
        player_.SetY(previousY);
      }
    }
    if (mouse.GetMouseAction() == graphics::MouseAction::kPressed ||
        mouse.GetMouseAction() == graphics::MouseAction::kDragged) {
      std::unique_ptr<PlayerProjectile> proj =
          std::make_unique<PlayerProjectile>(mouse.GetX(), mouse.GetY());
      playProj_.push_back(std::move(proj));
    }
  }
}

void Game::Init() {
  player_.SetX(400);
  player_.SetY(500);
  screen_.AddMouseEventListener(*this);
  screen_.AddAnimationEventListener(*this);
}

void Game::OnAnimationStep() {
  if (opponent_.size() < 1) {
    CreateOpponents();
  }
  MoveGameElements();
  LaunchProjectiles();
  FilterIntersections();
  UpdateScreen();
  RemoveInactive();
  screen_.Flush();
}

void Game::LaunchProjectiles() {
  for (int i = 0; i < opponent_.size(); i++) {
    std::unique_ptr<OpponentProjectile> opponents =
        opponent_[i]->LaunchProjectile();
    if (opponents != nullptr) {
      oppoProj_.push_back(std::move(opponents));
    }
  }
}

int Game::GetScore() { return score_; }

bool Game::HasLost() { return has_lost_; }

void Game::RemoveInactive() {
  for (int i = opponent_.size() - 1; i >= 0; i--) {
    if (!opponent_[i]->GetIsActive()) {
      opponent_.erase(opponent_.begin() + i);
    }
  }
  for (int j = oppoProj_.size() - 1; j >= 0; j--) {
    if (!oppoProj_[j]->GetIsActive()) {
      oppoProj_.erase(oppoProj_.begin() + j);
    }
  }
  for (int k = playProj_.size() - 1; k >= 0; k--) {
    if (!playProj_[k]->GetIsActive()) {
      playProj_.erase(playProj_.begin() + k);
    }
  }
}

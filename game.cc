#include "game.h"

void Game::CreateOpponents() {
  for (int i = 0; i < 3; i++) {
    std::unique_ptr<Opponent> opponent = std::make_unique<Opponent>(200 + 200 * i, 50);
    opponent_.push_back(std::move(opponent));
  }
}
void Game::CreateOpponentProjectiles() {
  for (int i = 0; i < 3; i++) {
    std::unique_ptr<OpponentProjectile> oppoProj = std::make_unique<OpponentProjectile>(200 + 200 * i, 130);
    oppoProj_.push_back(std::move(oppoProj));
  }
}
void Game::CreatePlayerProjectiles() {
  for (int i = 0; i < 3; i++) {
    std::unique_ptr<PlayerProjectile> playProj = std::make_unique<PlayerProjectile>(200 + 200 * i, 450);
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
  screen_.DrawText(10, 10, text, 14, 115, 10, 220);
  if (HasLost() == false) {
    screen_.DrawText(300, 250, "Game Over", 20, 255, 255, 255);
  }
}

void Game::Start() { screen_.ShowUntilClosed(); }

void Game::MoveGameElements() {
  for (int i = 0; i < opponent_.size(); i++) {
    if (opponent_[i]->GetIsActive()) {
      opponent_[i]->Move(screen_);
    }
  }
  for (int j = 0; j < oppoProj_.size(); j++) {
    if (oppoProj_[j]->GetIsActive()) {
      oppoProj_[j]->Move(screen_);
    }
  }
  for (int k = 0; k < playProj_.size(); k++) {
    if (playProj_[k]->GetIsActive()) {
      playProj_[k]->Move(screen_);
    }
  }
}

void Game::FilterIntersections() {
  for (int i = 0; i < opponent_.size(); i++) {
    if (player_.IntersectsWith(opponent_[i].get())) {
      player_.SetIsActive(false);
      opponent_[i]->SetIsActive(false);
    }
  }
  for (int j = 0; j < oppoProj_.size(); j++) {
    if (player_.IntersectsWith(oppoProj_[j].get())) {
      player_.SetIsActive(false);
      oppoProj_[j]->SetIsActive(false);
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
  RemoveInactive();
  UpdateScreen();
  screen_.Flush();
}

void Game::LaunchProjectiles() {
  for (int i = 0; opponent_.size(); i++) {
    std::unique_ptr<OpponentProjectile> opponents = opponent_[i]->LaunchProjectile();
    if (opponents != nullptr) {
      oppoProj_.push_back(std::move(opponents));
    }
  }
}

int Game::GetScore() { return score_; }

bool Game::HasLost() {
  if (player_.GetIsActive()) {
    return true;
  } else {
    return false;
  }
}

void Game::RemoveInactive() {
  for (int i = 0; i < opponent_.size(); i++) {
    if (opponent_[i]->GetIsActive() == false) {
      opponent_.erase(opponent_.begin() + i);
    }
  }
  for (int j = 0; j < oppoProj_.size(); j++) {
    if (oppoProj_[j]->GetIsActive() == false) {
      oppoProj_.erase(oppoProj_.begin() + j);
    }
  }
  for (int k = 0; k < playProj_.size(); k++) {
    if (playProj_[k]->GetIsActive() == false) {
      playProj_.erase(playProj_.begin() + k);
    }
  }
}

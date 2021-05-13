#include <iostream>
#include "game.h"

int main() {
  Game game;
  game.OnAnimationStep();
  game.Init();
  game.Start();
  return 0;
}

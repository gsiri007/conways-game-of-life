#include "Game.hpp"

int main() {
  Game game;
  bool init_result = game.initialize();

  if (!init_result) {
    return EXIT_FAILURE;
  }

  game.run_loop();
  game.shutdown();

  return EXIT_SUCCESS;
}

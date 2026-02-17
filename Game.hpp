#include <SDL3/SDL.h>
#include "Cells.hpp"

class Game {
public:
  Game();
  bool initialize();
  void run_loop();
  void shutdown();

private:
  bool is_running;

  SDL_Window *window;
  map_dimensions_t window_dimensions;

  SDL_Renderer *renderer;

  CellMap cell_map;

  void process_input();
  void generate_output();
  void update_game();
};

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
  SDL_Renderer *renderer;

  map_dimensions_t window_dimensions {1000, 1000};
  CellMap cell_map = CellMap(window_dimensions);

  void process_input();
  void generate_output();
  void update_game();
};

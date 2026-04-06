#include "Cells.hpp"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

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
  TTF_TextEngine *text_engine;
  TTF_Font *ttf_font;
  TTF_Text *controls_txt;

  const dimensions_t window_dimensions {1920, 1080};
  const dimensions_t map_dimensions {1000, 1080};
  CellMap cell_map = CellMap();

  void process_input();
  void generate_output();
  void update_game();
};

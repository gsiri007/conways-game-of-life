#include <SDL3/SDL_render.h>
#include <vector>
#include <SDL3/SDL_rect.h>
#include <SDL3_ttf/SDL_ttf.h>

typedef struct MapIndex {
  int row; // row index
  int col; // column index
} map_index_t;

typedef struct Cell {
  SDL_FRect *rect;
  int state;   //  dead = 0, alive = 1
  map_index_t map_index;
} cell_t;

typedef struct Dimensions {
  int width;
  int height;
} dimensions_t;


class CellMap {
public:
  CellMap();
  void init_cell_map(dimensions_t map_dimensions);
  void render_map(SDL_Renderer *renderer, TTF_TextEngine *text_engine, TTF_Font *ttf_font);
  void set_cell_alive(SDL_FPoint *mouse_position);
  void update_cell_map(dimensions_t map_dimensions);
  void toggle_update();
  bool get_update_state();
  bool is_neighbour_cell(map_index_t neighbour);
  std::vector<cell_t> get_alive_neighbours(cell_t cell);

private:
  float cell_width;
  float cell_height;

  int num_rows;
  int num_cols;

  std::vector<std::vector<cell_t>> cell_map;

  int generation;
  int population;

  bool is_updating;
};

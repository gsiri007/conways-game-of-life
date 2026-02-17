#include <SDL3/SDL_render.h>
#include <vector>
#include <SDL3/SDL_rect.h>

typedef struct Cell {
  SDL_FRect *rect;
  int state;   //  dead = 0, alive = 1

} cell_t;

typedef struct MapDimensions {
  int width;
  int height;
} map_dimensions_t;

typedef struct CellPosition {
  int x;
  int y;
} cell_pos_t;

class CellMap {
public:
  void init_cell_map(map_dimensions_t map_dimensions);
  void init_cell_map(map_dimensions_t map_dimensions, float cell_width, float cell_height, int cell_state);
  void toggle_cell_state(cell_pos_t cell_pos);
  SDL_FRect *get_cell_rect(cell_pos_t cell_pos);
  void render_cells(SDL_Renderer *renderer);

private:
  int num_rows;
  int num_cols;
  std::vector<std::vector<cell_t>> cell_map;
};

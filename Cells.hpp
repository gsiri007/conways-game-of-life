#include <SDL3/SDL_render.h>
#include <vector>
#include <SDL3/SDL_rect.h>

typedef struct MapIndex {
  int row; // row index
  int col; // column index
} map_index_t;

typedef struct Cell {
  SDL_FRect *rect;
  int state;   //  dead = 0, alive = 1
  map_index_t map_index;
} cell_t;

typedef struct MapDimensions {
  int width;
  int height;
} map_dimensions_t;


class CellMap {
public:
  void init_cell_map(map_dimensions_t map_dimensions);
  void init_cell_map(map_dimensions_t map_dimensions, float cell_width, float cell_height);
  void render_cells(SDL_Renderer *renderer);
  void set_cell_alive(SDL_FPoint *mouse_position);
  void update_cell_map();
  bool is_neighbour_cell(map_index_t neighbour);
  std::vector<cell_t> get_neighbour_cells(cell_t cell);

private:
  int num_rows;
  int num_cols;
  std::vector<std::vector<cell_t>> cell_map;
};

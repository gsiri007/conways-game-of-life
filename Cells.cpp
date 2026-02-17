#include "Cells.hpp"
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>

void CellMap::init_cell_map(map_dimensions_t map_dimensions) {
  float cell_width = (5.0 / 100) * map_dimensions.width;
  float cell_height = (5.0 / 100) * map_dimensions.height;

  num_rows = map_dimensions.height / cell_height;
  num_cols = map_dimensions.width / cell_width;

  cell_map.resize(num_rows);

  for (int i = 0; i < num_rows; i++) {
    for (int j = 0; j < num_cols; j++) {
      SDL_FRect *rect = new SDL_FRect();

      rect->x = j * cell_width;
      rect->y = i * cell_height;
      rect->w = cell_width;
      rect->h = cell_height;

      cell_t cell {rect, 0};

      cell_map[i].push_back(cell);
    }
  }
}

void CellMap::init_cell_map(map_dimensions_t map_dimensions, float cell_width, float cell_height, int cell_state) {
  num_rows = map_dimensions.height / cell_height;
  num_cols = map_dimensions.width / cell_width;

  cell_map.resize(num_rows);

  for (int i = 0; i < num_rows; i++) {
    for (int j = 0; j < num_cols; j++) {
      SDL_FRect *rect = new SDL_FRect();

      rect->x = j * cell_width;
      rect->y = i * cell_height;
      rect->w = cell_width;
      rect->h = cell_height;

      cell_t cell {rect, 0};

      cell_map[i].push_back(cell);
    }
  }
}

SDL_FRect *CellMap::get_cell_rect(cell_pos_t cell_pos) {
  cell_t target_cell = cell_map[cell_pos.x][cell_pos.y];
  return target_cell.rect;
}

void CellMap::toggle_cell_state(cell_pos_t cell_pos) {
  cell_t &target_cell = cell_map[cell_pos.x][cell_pos.y];

  if (target_cell.state == 0) {
    target_cell.state = 1;
  } else {
    target_cell.state = 0;
  }
}

void CellMap::render_cells(SDL_Renderer *renderer) {
  for (int i = 0; i < num_rows; i++) {
    for (int j = 0; j < num_cols; j++) {
      cell_pos_t pos {i, j};
      cell_t target_cell = cell_map[pos.x][pos.y];
      SDL_RenderRect(renderer, target_cell.rect);
    }
 
  }

}

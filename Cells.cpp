#include "Cells.hpp"
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <iostream>
#include <stdexcept>
#include <vector>

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

      map_index_t index {i, j};

      cell_t cell {rect, 0, index};

      cell_map[i].push_back(cell);
    }
  }
}

void CellMap::init_cell_map(map_dimensions_t map_dimensions, float cell_width, float cell_height) {
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

      map_index_t index {i, j};

      cell_t cell {rect, 0, index};

      cell_map[i].push_back(cell);
    }
  }
}

void CellMap::render_cells(SDL_Renderer *renderer) {
  for (int i = 0; i < num_rows; i++) {
    for (int j = 0; j < num_cols; j++) {
      cell_t target_cell = cell_map[j][i];

      if (target_cell.state == 1) {
        SDL_RenderFillRect(renderer, target_cell.rect);
        continue;
      }

      SDL_RenderRect(renderer, target_cell.rect);
    }
  }
}

void CellMap::set_cell_alive(SDL_FPoint *mouse_position) {
  for (int i = 0; i < cell_map.size(); i++) {
    for (int j = 0; j < cell_map[i].size(); j++) {
      cell_t &current_cell = cell_map[i][j];

      if (SDL_PointInRectFloat(mouse_position, current_cell.rect)) {
        current_cell.state = 1;
      }
    }
  }
}

bool CellMap::is_neighbour_cell(map_index_t neighbour) {

  try {
    cell_t neighbour_cell = cell_map.at(neighbour.row).at(neighbour.col);
    return true;
  } catch (const std::out_of_range &e) {
    return false;
  }

}

std::vector<cell_t> CellMap::get_neighbour_cells(cell_t cell) {
  std::vector<cell_t> neighbour_cells;


  map_index_t cell_pos = cell.map_index;

  map_index_t top_left_neighbour {cell_pos.row - 1, cell_pos.col - 1};
  map_index_t top_neighbour {cell_pos.row - 1, cell_pos.col};
  map_index_t top_right_neighbour {cell_pos.row - 1, cell_pos.col + 1};

  map_index_t left_neighbour {cell_pos.row, cell_pos.col - 1};
  map_index_t right_neighbour {cell_pos.row, cell_pos.col + 1};

  map_index_t bottom_left_neighbour {cell_pos.row + 1, cell_pos.col - 1};
  map_index_t bottom_neighbour {cell_pos.row + 1, cell_pos.col};
  map_index_t bottom_right_neighbour {cell_pos.row + 1, cell_pos.col + 1};

  if (is_neighbour_cell(top_left_neighbour)) {
    cell_t neighbour_cell = cell_map[top_left_neighbour.row][top_left_neighbour.col];
    neighbour_cells.push_back(neighbour_cell);
  }

  if (is_neighbour_cell(top_neighbour)) {
    cell_t neighbour_cell = cell_map[top_neighbour.row][top_neighbour.col];
    neighbour_cells.push_back(neighbour_cell);
  }

  if (is_neighbour_cell(top_right_neighbour)) {
    cell_t neighbour_cell = cell_map[top_right_neighbour.row][top_right_neighbour.col];
    neighbour_cells.push_back(neighbour_cell);
  }

  if (is_neighbour_cell(left_neighbour)) {
    cell_t neighbour_cell = cell_map[left_neighbour.row][left_neighbour.col];
    neighbour_cells.push_back(neighbour_cell);
  }

  if (is_neighbour_cell(right_neighbour)) {
    cell_t neighbour_cell = cell_map[right_neighbour.row][right_neighbour.col];
    neighbour_cells.push_back(neighbour_cell);
  }

  if (is_neighbour_cell(bottom_left_neighbour)) {
    cell_t neighbour_cell = cell_map[bottom_left_neighbour.row][bottom_left_neighbour.col];
    neighbour_cells.push_back(neighbour_cell);
  }

  if (is_neighbour_cell(bottom_neighbour)) {
    cell_t neighbour_cell = cell_map[bottom_neighbour.row][bottom_neighbour.col];
    neighbour_cells.push_back(neighbour_cell);
  }

  if (is_neighbour_cell(bottom_right_neighbour)) {
    cell_t neighbour_cell = cell_map[bottom_right_neighbour.row][bottom_right_neighbour.col];
    neighbour_cells.push_back(neighbour_cell);
  }

  return neighbour_cells;
}

void CellMap::update_cell_map() {
  for (int i = 0; i < 1; i++) {
    for (int j = 0; j < 1; j++) {
      cell_t current_cell = cell_map[j][i];
      std::vector<cell_t> neighbour_cells = get_neighbour_cells(current_cell);

      for (int k = 0; k < neighbour_cells.size(); k++) {
        std::cout << "neighbour " << k << " -> " << "row: " << neighbour_cells[k].map_index.row
          << " col: " << neighbour_cells[k].map_index.col<< '\n';
      }
      std::cout << "--------------------------" << '\n';
    }
  }
}

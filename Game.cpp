#include "Game.hpp"
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_scancode.h>
#include <iostream>

Game::Game() {
  is_running = true;
}

bool Game::initialize() {
  bool sdl_result = SDL_Init(SDL_INIT_VIDEO);
  if (!sdl_result) {
    SDL_Log("Error initializing SDL.");
    return false;
  }

  window = SDL_CreateWindow("GameOfLife", window_dimensions.width, window_dimensions.height, 0);
  if (!window) {
    SDL_Log("Error creating window.");
    return false;
  }

  renderer = SDL_CreateRenderer(window, NULL);
  if (!renderer) {
    SDL_Log("Error creating renderer.");
    return false;
  }

  return true;
}

void Game::run_loop() {
  while (is_running) {
    process_input();
    update_game();
    generate_output();
  }
}

void Game::shutdown() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
}

void Game::process_input() {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_EVENT_QUIT:
        is_running = false;
        break;
      case SDL_EVENT_MOUSE_BUTTON_DOWN:
        if (event.button.button == SDL_BUTTON_LEFT) {
          SDL_FPoint mouse_pos {event.button.x, event.button.y};
          cell_map.set_cell_alive(&mouse_pos);
        }
        break;
    }
  }

  const bool *keyboard_state = SDL_GetKeyboardState(NULL);

  if (keyboard_state[SDL_SCANCODE_ESCAPE]) {
    is_running = false;
  }

  if (keyboard_state[SDL_SCANCODE_Q]) {
    is_running = false;
  }

  if (keyboard_state[SDL_SCANCODE_RETURN]) {
    cell_map.toggle_update();
  }

}

void Game::generate_output() {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

  cell_map.render_cells(renderer);

  SDL_RenderPresent(renderer);
}

void Game::update_game() {
  if (cell_map.get_update_state()) {
    std::cout << "Updating cell map" << '\n';
    cell_map.update_cell_map(window_dimensions);
    return;
  }
  std::cout << "Paused cell map" << '\n';
}

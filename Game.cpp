#include "Game.hpp"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3_ttf/SDL_ttf.h>

Game::Game() {
  is_running = true;
}

bool Game::initialize() {
  bool sdl_result = SDL_Init(SDL_INIT_VIDEO);
  if (!sdl_result) {
    SDL_Log("Error initializing SDL.");
    return false;
  }

  window = SDL_CreateWindow("GameOfLife", 1920, 1080, 0);
  if (!window) {
   SDL_Log("Error creating window.");
    return false;
  }

  renderer = SDL_CreateRenderer(window, NULL);
  if (!renderer) {
    SDL_Log("Error creating renderer.");
    return false;
  }

  bool ttf_result = TTF_Init();
  if (!ttf_result) {
    SDL_Log("Error initializing TTF.");
    return false;
  }

  text_engine = TTF_CreateRendererTextEngine(renderer);
  if (!text_engine) {
    SDL_Log("Error creating text engine.");
    return false;
  }

  ttf_font = TTF_OpenFont("./fonts/OpenSans-Regular.ttf", 16);
  if (!ttf_font) {
    SDL_Log("Error loading fonts.");
    return false;
  }

  std::string controls_raw = R"(
    Mouse Click: Set a cell as alive.

    Return (Enter): Toggle simulation start/stop.

    Esc / Q: Quit the application.)";

  controls_txt = TTF_CreateText(
      text_engine,
      ttf_font,
      controls_raw.c_str(),
      0);

  cell_map.init_cell_map(map_dimensions);

  return true;
}

void Game::run_loop() {
  const int FPS {5};
  const int frame_delay {1000 / FPS};

  Uint64 frame_start;
  int frame_time;

  while (is_running) {
    frame_start = SDL_GetTicks();

    process_input();
    update_game();
    generate_output();

    frame_time = SDL_GetTicks() - frame_start;

    if (frame_time < frame_delay) {
      SDL_Delay(frame_delay - frame_time);
    }
  }
}

void Game::shutdown() {

  TTF_DestroyText(controls_txt);
  TTF_CloseFont(ttf_font);
  TTF_DestroyRendererTextEngine(text_engine);
  TTF_Quit();

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
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

void Game::update_game() {
  if (cell_map.get_update_state()) {
    cell_map.update_cell_map(map_dimensions);
    return;
  }
}

void Game::generate_output() {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

  cell_map.render_map(renderer, text_engine, ttf_font);
  TTF_DrawRendererText(controls_txt, 1080, 60);

  SDL_RenderPresent(renderer);
}

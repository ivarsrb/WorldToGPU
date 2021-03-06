//
// Created by Ivars Rusbergs in 2021
//
#include "lsim/platform/i_application.h"

#include <SDL.h>

#include "lsim/base/log.h"
#include "lsim/platform/types.h"

namespace lsim::platform {
IApplication::IApplication(int argc, char **argv,
                           const struct Settings &settings)
    : settings(settings), window_(settings),
      renderer_(window_.Handle(), settings) {
  (void)argc;
  (void)argv;

  base::Log::Info("platform", "initialized");
}

IApplication::~IApplication() {
  base::Log::Info("platform", "shuttind down..");
}

void IApplication::Run() {
  base::Log::Info("platform", "main loop", "entering..");
  // Poll for user input.
  bool running = true;
  while (running) {

    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {

      switch (event.type) {
      case SDL_QUIT:
        running = false;
        break;
      case SDL_WINDOWEVENT:
        if (event.window.event == SDL_WINDOWEVENT_CLOSE &&
            event.window.windowID == SDL_GetWindowID(window_.Handle())) {
          running = false;
        }
        break;
      case SDL_KEYUP:
        if (event.key.keysym.sym == SDLK_ESCAPE) {
          running = false;
        }
        break;
      }
    }

    RenderFrame();
    // running = false;
    // SDL_Delay(10);
  }
  base::Log::Info("platform", "main loop", "exiting..");
  OnExit();
}

Window &IApplication::Window() { return window_; }
renderer::Renderer &IApplication::Renderer() { return renderer_; }

} // namespace lsim::platform
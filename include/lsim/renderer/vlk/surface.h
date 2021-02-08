//
// Created by Ivars Rusbergs in 2021
//
// OS dependant surface images are presented to
#ifndef LSIM_RENDERER_VLK_SURFACE_H_
#define LSIM_RENDERER_VLK_SURFACE_H_

#include <SDL2/SDL.h>
#include <vulkan/vulkan.h>

namespace lsim::renderer::vlk {
class Surface {
public:
  // Surface depends on OS specific window
  Surface(const VkInstance &instance, SDL_Window *window);
  ~Surface();
  Surface(Surface const &) = delete;
  Surface operator=(Surface const &) = delete;
  const VkSurfaceKHR &Get() const;

private:
  VkSurfaceKHR Create(SDL_Window *window) const;
  // Reference to resource this renderable was created with.
  // It is used also for destruction of the surface.
  const VkInstance &instance_;
  // Images are presented to the surface
  const VkSurfaceKHR surface_ = VK_NULL_HANDLE;
};

} // namespace lsim::renderer::vlk

#endif
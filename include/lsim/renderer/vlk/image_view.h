//
// Created by Ivars Rusbergs in 2021
//
#ifndef LSIM_RENDERER_VLK_IMAGE_VIEW_H_
#define LSIM_RENDERER_VLK_IMAGE_VIEW_H_
#include <vulkan/vulkan.h>

namespace lsim::renderer::vlk {
class ImageView {
public:
  // Create image view for given image with given format
  // Specify also aspect flag (color (default), depth ...)
  ImageView(VkDevice device, VkImage image, VkFormat format,
            VkImageAspectFlags aspect_flags = VK_IMAGE_ASPECT_COLOR_BIT);
  ~ImageView();
  ImageView(ImageView const &) = delete;
  ImageView &operator=(ImageView const &) = delete;
  // Move constructor
  ImageView(ImageView &&other) noexcept;
  // Move asignment
  ImageView &operator=(ImageView &&other) noexcept;
  // Returns Vulkan object handle
  [[nodiscard]] VkImageView Handle();

private:
  [[nodiscard]] VkImageView Create(VkImage image, VkFormat format,
                                   VkImageAspectFlags aspect_flags) const;
  void Destroy();
  // Pointer to object this resource was created with
  VkDevice const context_device_;
  VkImageView image_view_ = VK_NULL_HANDLE;
};
} // namespace lsim::renderer::vlk

#endif
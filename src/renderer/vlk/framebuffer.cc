//
// Created by Ivars Rusbergs in 2021
//
#include "lsim/renderer/vlk/framebuffer.h"

#include <vector>

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

#include "lsim/base/log.h"
#include "vulkan_shared.h"

namespace lsim::renderer::vlk {
Framebuffer::Framebuffer(const VkDevice &device,
                         const VkRenderPass &render_pass,
                         const VkImageView &swapchain_image_view,
                         const VkExtent2D &swapchain_extent,
                         const VkImageView &depth_image_view)
    : device_(device),
      framebuffer_(Create(render_pass, swapchain_image_view, swapchain_extent,
                          depth_image_view)) {
  base::Log::Info("renderer", "framebuffer", "created");
}

Framebuffer::~Framebuffer() { Destroy(); }

Framebuffer::Framebuffer(Framebuffer &&other) noexcept
    : device_(other.device_) {
  // Call move-asignment operator
  *this = std::move(other);
  //base::Log::Info("renderer", "framebuffer", "move cnstructed");
}

Framebuffer &Framebuffer::operator=(Framebuffer &&other) noexcept {
  if (this != &other) {
    // Destroy current resource if there is anything to destroy
    Destroy();
    this->framebuffer_ = other.framebuffer_;
    other.framebuffer_ = VK_NULL_HANDLE;
    //base::Log::Info("renderer", "framebuffer", "move assigned");
  }
  return *this;
}

const VkFramebuffer &Framebuffer::Get() const { return framebuffer_; }

VkFramebuffer Framebuffer::Create(const VkRenderPass &render_pass,
                                  const VkImageView &swapchain_image_view,
                                  const VkExtent2D &swapchain_extent,
                                  const VkImageView &depth_image_view) const {
  (void)depth_image_view;
  const std::vector<VkImageView> attachments = {swapchain_image_view/*,
                                                depth_image_view*/};
  VkFramebufferCreateInfo framebuffer_create_info{};
  framebuffer_create_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
  // Render pass this framebuffer is compatable with
  framebuffer_create_info.renderPass = render_pass;
  framebuffer_create_info.attachmentCount =
      static_cast<uint32_t>(attachments.size());
  framebuffer_create_info.pAttachments = attachments.data();
  framebuffer_create_info.width = swapchain_extent.width;
  framebuffer_create_info.height = swapchain_extent.height;
  framebuffer_create_info.layers = 1;
  VkFramebuffer framebuffer;
  ErrorCheck(vkCreateFramebuffer(device_, &framebuffer_create_info, nullptr,
                                 &framebuffer));
  return framebuffer;
}

void Framebuffer::Destroy() {
  if (framebuffer_ != VK_NULL_HANDLE) {
    base::Log::Info("renderer", "framebuffer", "destroying..");
    vkDestroyFramebuffer(device_, framebuffer_, nullptr);
  }
}
} // namespace lsim::renderer::vlk
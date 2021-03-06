//
// Created by Ivars Rusbergs in 2021
//
// Abstraction of a Vulkan command pool object.
#ifndef LSIM_RENDERER_VLK_COMMAND_POOL_H_
#define LSIM_RENDERER_VLK_COMMAND_POOL_H_
#include <type_traits>

#include <vulkan/vulkan.h>

#include "queue_families.h"

namespace lsim::renderer::vlk {
class CommandPool {
public:
  // Flags of a command buffer
  enum class Flags { kNone = 0, kResetable = 1 << 0, kTransient = 1 << 1 };
  enum class BufferLevel {
    // Can be submitted to a queue for execution, but cannot be called from
    // other command buffers.
    kPrimary = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
    // Cannot be submitted directly, but can be called from primary command
    // buffers.
    kSecondary = VK_COMMAND_BUFFER_LEVEL_SECONDARY
  };
  // is_transient - true for short-lived buffers for optimization
  CommandPool(VkDevice device, QueueFamilies::Index family_index,
              Flags flags = Flags::kNone);
  ~CommandPool();
  CommandPool(CommandPool const &) = delete;
  CommandPool &operator=(CommandPool const &) = delete;
  CommandPool(CommandPool &&) = delete;
  CommandPool &operator=(CommandPool &&) = delete;
  // Returns Vulkan object handle
  [[nodiscard]] VkCommandPool Handle();
  // Allocate and return command buffer of a given level
  [[nodiscard]] VkCommandBuffer
  AllocateCommandBuffer(BufferLevel level = BufferLevel::kPrimary) const;

private:
  [[nodiscard]] VkCommandPool Create(QueueFamilies::Index family_index,
                                     Flags flags) const;
  // Pointer to resource this object is created with
  VkDevice const context_device_;
  VkCommandPool const command_pool_ = VK_NULL_HANDLE;
};

// Comparison operators for flag
inline CommandPool::Flags operator|(CommandPool::Flags lhs,
                                    CommandPool::Flags rhs) {
  return static_cast<CommandPool::Flags>(
      static_cast<std::underlying_type<CommandPool::Flags>::type>(lhs) |
      static_cast<std::underlying_type<CommandPool::Flags>::type>(rhs));
}
inline CommandPool::Flags operator&(CommandPool::Flags lhs,
                                    CommandPool::Flags rhs) {
  return static_cast<CommandPool::Flags>(
      static_cast<std::underlying_type<CommandPool::Flags>::type>(lhs) &
      static_cast<std::underlying_type<CommandPool::Flags>::type>(rhs));
}
} // namespace lsim::renderer::vlk

#endif

//
// Created by Ivars Rusbergs in 2021
//
#include "lsim/renderer/vlk/pipeline_graphics.h"

#include <vulkan/vulkan.h>

#include "lsim/base/log.h"
#include "vulkan_shared.h"

namespace lsim::renderer::vlk {
PipelineGraphics::PipelineGraphics(
    VkDevice device, const VkGraphicsPipelineCreateInfo &create_info)
    : context_device_(device), pipeline_(Create(create_info)) {
  base::Log::Info("renderer", "pipeline", "created");
}

PipelineGraphics::~PipelineGraphics() {
  base::Log::Info("renderer", "pipeline", "destroying..");
  vkDestroyPipeline(context_device_, pipeline_, nullptr);
}

VkPipeline PipelineGraphics::Handle() { return pipeline_; }

VkPipeline PipelineGraphics::Create(
    const VkGraphicsPipelineCreateInfo &create_info) const {

  VkPipeline pipeline  = VK_NULL_HANDLE;
  ErrorCheck(vkCreateGraphicsPipelines(context_device_, VK_NULL_HANDLE, 1, &create_info,
                                       nullptr, &pipeline));
  return pipeline;
}

} // namespace lsim::renderer::vlk
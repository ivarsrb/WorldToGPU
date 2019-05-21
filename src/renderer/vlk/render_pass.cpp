#include "render_pass.h"
#include <base/log.h>

namespace renderer::vlk {
RenderPass::RenderPass(const VkDevice& device, const VkFormat& swapchain_format) : 
    device_(device),
    render_pass_(Create(swapchain_format)) {
    base::Log::Info("Renderer: render pass created");
}

RenderPass::~RenderPass() {
    base::Log::Info("Renderer: render pass destroying...");
    vkDestroyRenderPass(device_, render_pass_, nullptr);
}

const VkRenderPass& RenderPass::Get() const {
    return render_pass_;
}

// How many color and depth buffers there will be, how many samples to use for each of
// themand how their contents should be handled throughout the rendering operations
VkRenderPass RenderPass::Create(const VkFormat& swapchain_format) const {
    // Attachment is Vulkan�s name for what you might otherwise know as a render target -
    // an Image to be used as output from rendering.You don�t point to specific Images here � 
    // you just describe their formats. (Understanding Vulkan objects)
    // Actual images to render to are defined in framebuffers to which this renderpass is compatable
    // Single color buffer attachmnt
    VkAttachmentDescription color_attachment{};
    // The format of the color attachment should match the format of the swap chain images
    // because we are rendering to it
    color_attachment.format = swapchain_format;
    // No multisampling
    color_attachment.samples = VK_SAMPLE_COUNT_1_BIT;
    // What to do with data in attachment before rendering (color and depth data)
    color_attachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    // After rendering
    color_attachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    // Stencil data
    color_attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    color_attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    color_attachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    // Images to be presented in the swap chain
    color_attachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
    // Attachment reference
    VkAttachmentReference color_attachment_ref {};
    // Specifies which attachment to reference by its index in the attachment descriptions array
    color_attachment_ref.attachment = 0;
    color_attachment_ref.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    // Subpasses
    VkSubpassDescription subpass{};
    subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.colorAttachmentCount = 1;
    // The index of the attachment in this array is directly referenced from the 
    // fragment shader with the layout(location = 0) out vec4 outColor directive!
    subpass.pColorAttachments = &color_attachment_ref;
    // Subpass dependancies
    // Specify memory and execution dependencies between subpasses
    VkSubpassDependency dependency = {};
    dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
    dependency.dstSubpass = 0;
    dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.srcAccessMask = 0;
    dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    // Pass
    VkRenderPassCreateInfo render_pass_create_info {};
    render_pass_create_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    render_pass_create_info.attachmentCount = 1;
    render_pass_create_info.pAttachments = &color_attachment;
    render_pass_create_info.subpassCount = 1;
    render_pass_create_info.pSubpasses = &subpass;
    render_pass_create_info.dependencyCount = 1;
    render_pass_create_info.pDependencies = &dependency;
    VkRenderPass render_pass;
    ErrorCheck(vkCreateRenderPass(device_, &render_pass_create_info, nullptr, &render_pass));
    return render_pass;
}
}; // renderer vlk
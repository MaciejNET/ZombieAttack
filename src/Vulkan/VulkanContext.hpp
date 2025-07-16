#pragma once

#ifndef VULKAN_CONTEXT_HPP
#define VULKAN_CONTEXT_HPP

#include <vulkan.h>
#include <GLFW/glfw3.h>

namespace Vulkan {

class VulkanContext {
public:
    VulkanContext() = default;
    ~VulkanContext() = default;

    void Initialize(GLFWwindow* window);
    void Cleanup();

private:
    VkInstance instance{VK_NULL_HANDLE};
    VkSurfaceKHR surface{VK_NULL_HANDLE};
    VkDevice device{VK_NULL_HANDLE};
};

} // namespace Vulkan

#endif // VULKAN_CONTEXT_HPP

#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
private:
	GLFWwindow* m_Window;
	int m_Width, m_Height;
	bool m_IsFullscreen = false;

public:

	Window();
	~Window();

	static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
	int SetupGLFW(int width, int height, std::string name);

	_NODISCARD __forceinline GLFWwindow* GetWindow() const noexcept { return m_Window; };
	__forceinline void GetWindowSize() noexcept { glfwGetWindowSize(m_Window, &m_Width, &m_Height); } // Update the window size when resizing it
	_NODISCARD __forceinline int GetWidth() const noexcept { return m_Width; };
	_NODISCARD __forceinline int GetHeight() const noexcept { return m_Height; };
	_NODISCARD __forceinline bool IsFullScreen() const noexcept { return m_IsFullscreen; };

	__forceinline void SetWidth(int width) noexcept { m_Width = width; };
	__forceinline void SetHeight(int height) noexcept { m_Height = height;};
	__forceinline void SetFullScreen(bool fullscreen) noexcept { m_IsFullscreen = fullscreen; };
};


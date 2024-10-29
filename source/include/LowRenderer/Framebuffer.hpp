#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Framebuffer
{
private:
	int m_Width, m_Height;

	unsigned int m_FBO;
	unsigned int m_RBO;
	unsigned int m_FramebufferTexture;
public:
	Framebuffer(int width, int height);

	int GetTexture() { return m_FramebufferTexture; };

	void Create();
	void Bind();
	void Unbind();
	void Rescale(float width, float height);
};
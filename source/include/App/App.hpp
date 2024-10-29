#pragma once

#include "Log.hpp"
#include "Assertion.hpp"

#include "ResourcesManager.hpp"
#include "Model.hpp"
#include "Camera.hpp"
#include "Texture.hpp"

#include "DirLight.hpp"
#include "PointLight.hpp"
#include "SpotLight.hpp"

#include "Object.hpp"

#include "PlaneCollider.hpp"
#include "BoxCollider.hpp"

#include "Cube.hpp"

#include "Skybox.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Window.hpp"

#include "Scene.hpp"

class App
{
private:
	static Camera m_Cam;
	static Window window;
	static std::vector<Scene> m_ScenesList;

public:

	~App();
	
	static Camera cam;
	static float deltaTime;


	static void processInput(GLFWwindow* window);
	static void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

	static const unsigned int SCR_WIDTH = 1460;
	static const unsigned int SCR_HEIGHT = 920;

	static int Update();
};
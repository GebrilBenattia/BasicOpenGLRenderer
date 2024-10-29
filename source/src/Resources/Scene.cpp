#include "Scene.hpp"

Scene::Scene(std::string name)
{
	m_Name = name;
	m_Camera = Camera(0, 0, 20, 0, 1, 0);
}

Scene::~Scene()
{
}

void Scene::AddDirLight(DirLight dirlight)
{
	m_DirLightList.push_back(&dirlight);
	std::cout << m_DirLightList.size() << " " << dirlight.name << std::endl;
}

void Scene::AddSpotLight(SpotLight spotlight)
{
	m_SpotLightList.push_back(&spotlight);
	std::cout << m_SpotLightList.size() << " " << spotlight.name << std::endl;
}

void Scene::AddPointLight(PointLight pointlight)
{
	m_PointLightList.push_back(&pointlight);
	std::cout << m_PointLightList.size() << " " << pointlight.name << std::endl;
}

void Scene::AddCube(Cube cube)
{
	m_CubeList.push_back(&cube);
}

void Scene::Update()
{	
	for (size_t i = 0; i < m_DirLightList.size(); i++) {
		m_DirLightList[i]->Update();
	}
	for (size_t i = 0; i < m_SpotLightList.size(); i++) {
		m_SpotLightList[i]->Update(m_Camera);
	}
	for (size_t i = 0; i < m_PointLightList.size(); i++) {
		m_PointLightList[i]->Update(m_Camera);
	}
	/*for (size_t i = 0; i < m_CubeList.size(); i++) {
		m_CubeList[i]->Update(*ResourceManager::Get<Shader>("ourshader"));
	}*/
}
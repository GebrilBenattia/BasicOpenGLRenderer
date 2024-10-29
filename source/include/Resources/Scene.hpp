#pragma once

#include "DirLight.hpp"
#include "PointLight.hpp"
#include "SpotLight.hpp"

#include "Cube.hpp"

class Scene
{
private:
	std::vector<DirLight*> m_DirLightList;
	std::vector<PointLight*> m_PointLightList;
	std::vector<SpotLight*> m_SpotLightList;

	std::vector<Cube*> m_CubeList;

	Camera m_Camera;

	bool m_Loaded = false;

	std::string m_Name;
public:

	Scene(std::string name);
	~Scene();

	void AddDirLight(DirLight dirlight);
	void AddSpotLight(SpotLight spotlight);
	void AddPointLight(PointLight pointlight);
	void AddCube(Cube cube);

	_NODISCARD __forceinline std::vector<DirLight*>& GetDirLightList() noexcept { return m_DirLightList; };
	_NODISCARD __forceinline std::vector<PointLight*>& GetPointLightList() noexcept { return m_PointLightList; };
	_NODISCARD __forceinline std::vector<SpotLight*>& GetSpotLightList() noexcept { return m_SpotLightList; };

	_NODISCARD __forceinline std::vector<Cube*>& GetCubeList() noexcept { return m_CubeList; };

	_NODISCARD __forceinline std::string GetName() noexcept { return m_Name; };

	void Update();
};
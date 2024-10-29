#pragma once

#include <iostream>
#include <unordered_map>
#include "IResource.hpp"

template<class T>
concept ResourceClass = std::is_base_of<IResource, T>::value;

class ResourceManager
{
private:

public:
	static std::unordered_map<std::string, IResource*> map;

	template<ResourceClass T>
	static void Create(std::string name)
	{
		T* res = dynamic_cast<T*>(map[name]);
		if (res) {
			delete res;
		}
		res = new T(name.c_str());
		map[name] = res;
	}

	template<ResourceClass T>
	static T* Get(std::string name)
	{
		return dynamic_cast<T*>(map[name]);
	}
	static void Delete(std::string name);

	static void DeleteAll();
};
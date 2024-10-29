#include "ResourcesManager.hpp"
std::unordered_map<std::string, IResource*> ResourceManager::map;

void ResourceManager::Delete(std::string name) { map.erase(name); }

void ResourceManager::DeleteAll()
{
	for (auto& it : map) {
		delete(&it);
	}
}
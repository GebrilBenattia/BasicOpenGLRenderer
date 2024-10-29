#pragma once

#include <string>

class IResource
{
public:
	std::string name;

	IResource() {};
	virtual ~IResource() = 0 {};
};
#pragma once
#include <iostream>
#include <filesystem>
#include <fstream>
#include <cstdarg>

#define DEBUG_LOG(...) {std::cout << std::string(static_cast<std::string>(__FILE__).substr(static_cast<std::string>(__FILE__).rfind('\\') + 1))  << "(" << __LINE__ << "): "; Log::Print(__VA_ARGS__);}

class Log
{
private:
	static std::ofstream m_File;

public:
	Log();
	~Log();

	static void OpenFile(std::filesystem::path const& filename);

	static void Print(const char* format, ...);
};
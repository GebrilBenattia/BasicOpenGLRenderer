#include "Log.hpp"
#include "Assertion.hpp"
#include <string>

std::ofstream Log::m_File;

std::filesystem::path const& folderpath = "Log/";

Log::Log()
{

}

Log::~Log()
{
    m_File.close();
}

void Log::OpenFile(std::filesystem::path const& filename)
{
    m_File.open((folderpath.string() + filename.string()), std::ios_base::app);
}

void Log::Print(const char* format, ...)
{
	va_list args;
	va_start(args, format);

    (!m_File.bad()) ? m_File << '\n' : std::cout << "";

    while (*format != '\0')
    {
        if (*format == '%') {
            ++format;
            if (*format == 'd') {
                int i = va_arg(args, int);
                std::cout << i;
                (!m_File.bad()) ? m_File << i : std::cout << "";
            }
            else if (*format == 'c') {
                int c = va_arg(args, int);
                std::cout << static_cast<char>(c);
                (!m_File.bad()) ? m_File << static_cast<char>(c) : std::cout << "";
            }
            else if (*format == 'f') {
                double d = va_arg(args, double);
                std::cout << d;
                (!m_File.bad()) ? m_File << d : std::cout << "";
            }
        }
        else {
            std::cout << *format;
            (!m_File.bad()) ? m_File << *format : std::cout << "";
        }
        ++format;
    }
    va_end(args);
}
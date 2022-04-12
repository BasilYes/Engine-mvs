#include <debug.h>

#if _DEBUG
#include <string>
#include <iostream>
#include <assert.h>
void error(const char* message, const char* file, const int line)
{
	std::cout << "ERROR:" << message << " in file " << file << " in line " << line << "\n";
	assert(true, std::string(message) + " in file " + std::string(file) + " in line " + std::to_string(line));
}
void warning(const char* message, const char* line, const char* file)
{
	std::cout << "WARNING:" << message << " in file " << file << " in line " << line << "\n";
}
void trace(const char* message, const char* file, const int line)
{
	std::cout << "TRACE:" << message << " in file " << file << " in line " << line << "\n";
}
void my_assert(bool is, const char* message, const char* file, const int line)
{
	assert(is, std::string(message) + " in file " + std::string(file) + " in line " + std::to_string(line));
}
#else

#endif

#include "debug.h"

#if _DEBUG
#include <string>
#include <iostream>
#include <stdlib.h>
void error(const char* message, const char* file, const int line)
{
	std::cout << "ERROR:" << message << " in file " << file << " in line " << line << "\n";
	exit(-1);
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
	if (!is)
	{
		std::cout << "ASSERT:" << message << " in file " << file << " in line " << line << "\n";
		exit(-1);
	}
}
#else
void error(const char* message, const char* file, const int line)
{
}
void warning(const char* message, const char* line, const char* file)
{
}
void trace(const char* message, const char* file, const int line)
{
}
void my_assert(bool is, const char* message, const char* file, const int line)
{
}
#endif

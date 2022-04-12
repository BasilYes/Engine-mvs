#pragma once

void error(const char* message, const char* file, const int line);
void warning(const char* message, const char* line, const char* file);
void trace(const char* message, const char* file, const int line);
void my_assert(bool is, const char* message, const char* file, const int line);
#define ERROR(x) error(x, __FILE__, __LINE__);
#define WARNING(x) warning(x, __FILE__, __LINE__);
#define TRACE(x) trace(x, __FILE__, __LINE__);
#define ASSERT(x,y) my_assert(x, y, __FILE__, __LINE__);
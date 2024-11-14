#pragma once

#ifndef MACROS_HPP
#define MACROS_HPP

#include <iostream>
#include <cstdlib>
#include <glad/glad.h>

inline void CheckOpenGLError(const char* stmt, const char* fname, int line)
{
    GLenum err = glGetError();
    if (err != GL_NO_ERROR)
    {
        std::cerr << "OpenGL error " << err << " at " << fname << ":" << line << " for " << stmt << std::endl;
        exit(1);
    }
}
#define GL_CHECK(stmt) do { \
        stmt; \
        CheckOpenGLError(#stmt, __FILE__, __LINE__); \
    } while (0)

#define ZA_ASSERT(condition, message) \
    do { \
        if (!(condition)) { \
            std::cerr << "Assertion failed: (" #condition "), function " << __FUNCTION__ \
                      << ", file " << __FILE__ << ", line " << __LINE__ << "." << std::endl; \
            std::cerr << "Message: " << message << std::endl; \
            std::abort(); \
        } \
    } while (false)

#endif //MACROS_HPP

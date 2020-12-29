#ifndef CALL_H
#define CALL_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

void glClearError();

bool GLLogCall(const char* fun, const char* fil, int line);

#define ASSERT(x) if((!x)) raise(SIGBREAK);

#define Call(x)  glClearError();\
        x;\
        ASSERT(GLLogCall(#x, __FILE__, __LINE__));

#endif // CALL_H

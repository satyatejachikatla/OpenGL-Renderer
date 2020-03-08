#pragma once

#include <iostream>

void GLClearError();
bool GLLogCall();

#define ASSERT(x)                                             \
    if (!(x)) {                                               \
            std::cerr << __FILE__ << ":"<<                    \
                                      __LINE__ << std::endl;  \
            exit(EXIT_FAILURE);                               \
    }

#define glCall(call)                                          \
    GLClearError();                                           \
    call;                                                     \
    ASSERT(GLLogCall());                                      \


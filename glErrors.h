#ifndef __GL_ERRORS_H__
#define __GL_ERRORS_H__

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

#endif /* __GL_ERRORS_H__ */
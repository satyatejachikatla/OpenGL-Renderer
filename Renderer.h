#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <iostream>
#include <GL/glew.h>    // GL Wrangler

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

#endif /* __RENDERER_H__ */

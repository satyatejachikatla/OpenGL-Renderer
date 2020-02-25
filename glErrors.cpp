#include <iostream>
#include <GL/glew.h>    // GL Wrangler

#include "glErrors.h"

void GLClearError() {
	while(glGetError() != GL_NO_ERROR);
}

bool GLLogCall() {
	while(GLenum error = glGetError()) {
		std::cout << "[OpenGL error]: ("<< error <<")"<< std::endl;
		return false;
	}
	return true;
}

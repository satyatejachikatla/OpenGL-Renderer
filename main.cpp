#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <GL/glew.h>	// GL Wrangler
#include <GLFW/glfw3.h> // Window management

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

struct ShaderProgrameSource {
	std::string VertexSource;
	std::string FragmentSource;
};

static ShaderProgrameSource ParseShader(const std::string filePath) {

	std::ifstream stream(filePath);

	enum class ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};	

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	while(getline(stream,line)) {
		if(line.find("#shader") != std::string::npos) {
			if(line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else {
			ss[(int)type] << line << "\n"; 
		}
	}

	return {ss[0].str(),ss[1].str()};

}

static unsigned int CompileShader(unsigned int type,const std::string& source) {
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();

	/* sharder id , num shaders , source pointer, no array lenths required */
	glCall(glShaderSource(id,1,&src,nullptr));
	glCall(glCompileShader(id));

	int result;
	glCall(glGetShaderiv(id,GL_COMPILE_STATUS,&result));
	if (result == GL_FALSE) {
		int length;
		glCall(glGetShaderiv(id,GL_INFO_LOG_LENGTH,&length));
		char* message = (char *)alloca(length*sizeof(char));\

		glCall(glGetShaderInfoLog(id,length,&length,message));

		std::cerr << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") <<std::endl;
		std::cerr << message <<std::endl;

		glCall(glDeleteShader(id));
		return 0;

	}

	return id;
}

static unsigned int CreateShader(const std::string& vertexShader,const std::string& fragmentShader )  {
	glCall(unsigned int program = glCreateProgram());
	glCall(unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader));
	glCall(unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader));

	glCall(glAttachShader(program,vs));
	glCall(glAttachShader(program,fs));
	glCall(glLinkProgram(program));
	glCall(glValidateProgram(program));

	glCall(glDeleteShader(vs));
	glCall(glDeleteShader(fs));

	return program;
}

int main(void) {

/* START SETTINGS */
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit()){
		std::cerr << "Failed to init glfw" << std::endl;
		return EXIT_FAILURE;
	}


	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glCall(glfwMakeContextCurrent(window));
	/* FPS in sec */
	glCall(glfwSwapInterval(1));

	/* glewInit after context setting */
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to init glew" << std::endl; 
		return EXIT_FAILURE;
	}

	/* OpenGl Version */
	std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
/* END SETTINGS */
{ // Scope Createtion to delete the gl variables before the window exit

	int points_n = 2;
	int positions_n = 4*points_n;
	float positions[positions_n] = {
		-0.5f, -0.5f,
		 0.5f,  -0.5f,
		 0.5f, 0.5f,
		 -0.5f, 0.5f,
	};


/// All the Vertex Object Creation
	VertexArray va;
	VertexBuffer vb(positions,positions_n*sizeof(*positions));
	VertexBufferLayout layout;
	layout.Push<float>(points_n);
	va.AddBuffer(vb,layout);

///

/// with indices mapping to points to draw
	unsigned int indices_n = 6;
	unsigned int indices[] = {
		0,1,2,
		2,3,0
	};

	IndexBuffer ib(indices,indices_n);
///

	ShaderProgrameSource source = ParseShader("./Basic.shader");
	std::cout << "Vertex" << std::endl;
	std::cout << source.VertexSource << std::endl;
	std::cout << "Fragment" << std::endl;
	std::cout << source.FragmentSource << std::endl;


	glCall(unsigned int shader= CreateShader(source.VertexSource,source.FragmentSource));
	glCall(glUseProgram(shader));

	/*Setting Data in Shader*/
	glCall(int location = glGetUniformLocation(shader,"u_Color"));
	ASSERT(location != -1);
	glCall(glUniform4f(location,0.8f,0.3f,0.8f,1.0f));

	/* lets unbind everything */
	va.Unbind();
	glCall(glUseProgram(0));
	vb.Unbind();
	ib.Unbind();

	float r = 0.0f;
	float increment = 0.05f;
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window)) {
		/* Render here */
		glCall(glClear(GL_COLOR_BUFFER_BIT));

		/* Binds during th loop */

		//Bind VAO//
		va.Bind();

		//Update Shader//
		glCall(glUseProgram(shader));
		glCall(glUniform4f(location,r,0.3f,0.8f,1.0f));

		// Update Buffer array //
		vb.Bind();	

		// Update Index array //
		ib.Bind();

		//glDrawArrays(GL_TRIANGLES,0,positions_n/points_n);
		glCall(glDrawElements(GL_TRIANGLES,indices_n,GL_UNSIGNED_INT,nullptr));

		if(r > 1.0f)
			increment = -0.05f;
		else if(r < 0.0f)
			increment = 0.05f;

		r += increment;

		/* Swap front and back buffers */
		glCall(glfwSwapBuffers(window));

		/* Poll for and process events */
		glCall(glfwPollEvents());
	}
	glCall(glDeleteProgram(shader));
}
	glCall(glfwTerminate());
	return 0;
}
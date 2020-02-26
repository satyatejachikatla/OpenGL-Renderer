#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <GL/glew.h>	// GL Wrangler
#include <GLFW/glfw3.h> // Window management

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "glErrors.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

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
	/* Vsyncing screen number for proper frame rate*/
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

	int positions_n = 4*4;
	float positions[] = {
		-0.5f, -0.5f, 0.0f, 0.0f, //0
		 0.5f, -0.5f, 1.0f, 0.0f, //1
		 0.5f,  0.5f, 1.0f, 1.0f, //2
		-0.5f,  0.5f, 0.0f, 1.0f, //3
	};

	unsigned int indices_n = 6;
	unsigned int indices[indices_n] = {
		0,1,2,
		2,3,0
	};

	glm::mat4 proj = glm::ortho(-2.0f,2.0f,-1.5f,1.5f,-1.0f,1.0f);

	glCall(glEnable(GL_BLEND));
	glCall(glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA));

/// All the Vertex Object Creation
	VertexArray va;
	VertexBuffer vb(positions,positions_n*sizeof(*positions));
	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);
	va.AddBuffer(vb,layout);
	IndexBuffer ib(indices,indices_n);
///

	Shader shader("./Basic.shader");
	shader.Bind();
	shader.SetUniform4f("u_Color",0.8f,0.3f,0.8f,1.0f);
	shader.SetUniformMat4f("u_MVP",proj);

	Texture texture("./res/textures/TheCherno.png");
	texture.Bind(0);
	shader.SetUniform1i("u_Texture",0);

	va.Unbind();
	vb.Unbind();
	ib.Unbind();
	shader.Unbind();

	Renderer renderer;

	float r = 0.0f;
	float increment = 0.05f;
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window)) {
		/* Render here */
		renderer.Clear();

		//Update Shader//
		shader.Bind();
		shader.SetUniform4f("u_Color",r ,0.3f,0.8f,1.0f);

		renderer.Draw(va,ib,shader);

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
}
	glCall(glfwTerminate());
	return 0;
}
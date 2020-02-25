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
#include "Shader.h"

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

	int axis_n = 2;
	int positions_n = 4*axis_n;
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
	layout.Push<float>(axis_n);
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

	Shader shader("./Basic.shader");
	shader.Bind();
	shader.SetUniform4f("u_Color",0.8f,0.3f,0.8f,1.0f);

	/* lets unbind everything */
	va.Unbind();
	vb.Unbind();
	ib.Unbind();
	shader.Unbind();


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
		shader.Bind();
		shader.SetUniform4f("u_Color",r ,0.3f,0.8f,1.0f);

		// Update Buffer array //
		vb.Bind();	

		// Update Index array //
		ib.Bind();

		//glDrawArrays(GL_TRIANGLES,0,positions_n/axis_n);
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
}
	glCall(glfwTerminate());
	return 0;
}
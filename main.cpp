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

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

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
		-50.0f, -50.0f, 0.0f, 0.0f, //0
		 50.0f, -50.0f, 1.0f, 0.0f, //1
		 50.0f,  50.0f, 1.0f, 1.0f, //2
		-50.0f,  50.0f, 0.0f, 1.0f, //3
	};

	unsigned int indices_n = 6;
	unsigned int indices[indices_n] = {
		0,1,2,
		2,3,0
	};

	glm::mat4 proj  = glm::ortho(0.0f,960.0f,0.0f,540.0f,-1.0f,1.0f);
	glm::mat4 view  = glm::translate(glm::mat4(1.0f),glm::vec3(0,0,0));
//	glm::mat4 model = glm::translate(glm::mat4(1.0f),glm::vec3(200,200,0));
//	glm::mat4 mvp = proj * view * model;

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
//	shader.SetUniform4f("u_Color",0.8f,0.3f,0.8f,1.0f);
//	shader.SetUniformMat4f("u_MVP",mvp);

	Texture texture("./res/textures/TheCherno.png");
	texture.Bind(0);
	shader.SetUniform1i("u_Texture",0);

	va.Unbind();
	vb.Unbind();
	ib.Unbind();
	shader.Unbind();

	Renderer renderer;

	ImGui::CreateContext();
	// Style//
	ImGui::StyleColorsDark();
	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");


	glm::vec3 translationA(200,200,0);
	glm::vec3 translationB(400,200,0);

	float r = 0.0f;
	float increment = 0.05f;
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window)) {
		/* Render here */
		renderer.Clear();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		//Update Shader//
		shader.Bind();
		shader.SetUniform4f("u_Color",r ,0.3f,0.8f,1.0f);

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f),translationA);
			glm::mat4 mvp = proj * view * model;
			shader.Bind();
			shader.SetUniformMat4f("u_MVP",mvp);
			renderer.Draw(va,ib,shader);
		}

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f),translationB);
			glm::mat4 mvp = proj * view * model;
			shader.Bind();
			shader.SetUniformMat4f("u_MVP",mvp);
			renderer.Draw(va,ib,shader);
		}

		if(r > 1.0f)
			increment = -0.05f;
		else if(r < 0.0f)
			increment = 0.05f;

		r += increment;

		{
			ImGui::SliderFloat3("TranslationA", &translationA.x, 0.0f, 960.0f);
			ImGui::SliderFloat3("TranslationB", &translationB.x, 0.0f, 960.0f);
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		}

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		/* Swap front and back buffers */
		glCall(glfwSwapBuffers(window));

		/* Poll for and process events */
		glCall(glfwPollEvents());
	}
}
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glCall(glfwTerminate());
	return 0;
}
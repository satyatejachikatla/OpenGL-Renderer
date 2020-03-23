#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <GL/glew.h>	// GL Wrangler
#include <GLFW/glfw3.h> // Window management

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "glErrors.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <InputSystem.h>

/* //Test Includes// */
#include "tests/Test.h"
/* Generated Code In Here */
#include "tests/allTestInclude.h"
/* \\Test Includes\\ */


int main(int arc,char** argv) {

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
	window = glfwCreateWindow(1000, 1000, "Hello World", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	/* Make the window's interaction callbacks */
	glCall(glfwMakeContextCurrent(window));
	glCall(glfwSetCursorPosCallback(window, cursor_position_callback));
	glCall(glfwSetMouseButtonCallback(window, mouse_button_callback));
	glCall(glfwSetScrollCallback(window, scroll_callback));
	/* Vsyncing screen number for proper frame rate*/
	glCall(glfwSwapInterval(1));

	/* glewInit after context setting */
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to init glew" << std::endl; 
		return EXIT_FAILURE;
	}


	/* Set Input Key Callback */
	glfwSetKeyCallback(window, key_callback);

	/* OpenGl Version */
	std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;

/* END SETTINGS */
{ // Scope Createtion to delete the gl variables before the window exit

	glCall(glEnable(GL_BLEND));
	glCall(glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA));

	glCall(glEnable(GL_DEPTH_TEST));

	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");

	test::Test* currentTest=nullptr;
	test::TestMenu* testMenu = new test::TestMenu(currentTest);
	currentTest = testMenu;

	/* Generated Code In Here */
	#include "tests/allTestReg.h"

	while (!glfwWindowShouldClose(window)) {

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		glCall(glClearColor(0.0f,0.0f,0.0f,0.0f));
		glCall(glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT));

		if(currentTest) {
			currentTest->OnUpdate(0.0f);
			currentTest->OnRender();
			ImGui::Begin("Test");
			if(currentTest != testMenu && ImGui::Button("<-")) {
				delete currentTest;
				currentTest = testMenu;
			}
			currentTest->OnImGuiRender();
			ImGui::End();
		}

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glCall(glfwSwapBuffers(window));
		glCall(glfwPollEvents());
	}

	delete currentTest;
	if (currentTest != testMenu) {
		delete testMenu;
	}

}
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glCall(glfwTerminate());
	return 0;
}
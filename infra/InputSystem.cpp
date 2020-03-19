#include <GLFW/glfw3.h> // Window management
#include <Camera.h>
#include <iostream>

#define SPEED 0.01f

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	/*
	if(action != GLFW_PRESS) {
		return;
	}*/

	Camera* cam = Camera::getCurrentCamera();
	switch (key) {
		case GLFW_KEY_A:
			if(cam) {
				cam->OnUpdate(SPEED,0,0);
			}
			break;
		case GLFW_KEY_D:
			if(cam) {
				cam->OnUpdate(-SPEED,0,0);
			}
			break;
		case GLFW_KEY_W:
			if(cam) {
				cam->OnUpdate(0,-SPEED,0);
			}
			break;
		case GLFW_KEY_S:
			if(cam) {
				cam->OnUpdate(0,SPEED,0);
			}
			break;
		case GLFW_KEY_UP:
			if(cam) {
				cam->OnUpdate(0,0,-SPEED);
			}
			break;
		case GLFW_KEY_DOWN:
			if(cam) {
				cam->OnUpdate(0,0,SPEED);
			}
			break;
	}

}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
/*
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
		std::cout  << "Right Mouse Pressed" << std::endl;
*/
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
/*
	Camera* cam = Camera::getCurrentCamera();
	if(cam) {
		cam->OnUpdate(glm::vec3(0.0,0.0,SPEED*yoffset));
	}
*/
}


#include <GLFW/glfw3.h> // Window management
#include <Camera.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define POS_SPEED 0.01f
#define TARGET_SPEED 0.1f

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	/*
	if(action != GLFW_PRESS) {
		return;
	}*/

	glm::vec3 pos_updates = glm::vec3(0.0f,0.0f,0.0f);
	glm::vec3 target_speeds = glm::vec3(0.0f,0.0f,0.0f);

	switch (key) {
		case GLFW_KEY_A:
			pos_updates.x = -POS_SPEED;
			break;
		case GLFW_KEY_D:
			pos_updates.x = POS_SPEED;
			break;
		case GLFW_KEY_W:
			pos_updates.z = -POS_SPEED;
			break;
		case GLFW_KEY_S:
			pos_updates.z = POS_SPEED;
			break;
		case GLFW_KEY_SPACE:
			pos_updates.y = POS_SPEED;
			break;
		case GLFW_KEY_LEFT_ALT:
			pos_updates.y = -POS_SPEED;
			break;
		case GLFW_KEY_LEFT:
			target_speeds.x = -TARGET_SPEED;
			break;
		case GLFW_KEY_RIGHT:
			target_speeds.x = TARGET_SPEED;
			break;
		case GLFW_KEY_UP:
			target_speeds.y = -TARGET_SPEED;
			break;
		case GLFW_KEY_DOWN:
			target_speeds.y = TARGET_SPEED;
			break;
	}

	Camera* cam = Camera::getCurrentCamera();
	if(cam) {
		cam->OnUpdatePos(pos_updates);
		cam->OnUpdateTarget(target_speeds);
	}
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
/*
	glm::vec3 straf = glm::vec3(0.0f,0.0f,0.0f);

	straf.x = (320 - xpos)/320;
	straf.z = (240 - ypos)/240;

	Camera* cam = Camera::getCurrentCamera();
	if(cam) {
		cam->OnUpdateStraf(straf);
	}
*/
	//std::cout  << "X pos" << xpos << " Y pos" << ypos << std::endl;
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


#include <glErrors.h>
#include <GLFW/glfw3.h> // Window management
#include <Camera.h>
#include <iostream>
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#define POS_SPEED 0.01f
#define MOUSE_SENSITIVITY 0.1f

static bool escape_menu_set = false;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

	static std::map<unsigned int,bool> keymap;
	static bool escape_menu_set_toggle = false;


	if(action == GLFW_PRESS) {
		keymap[key] = true;
	} else if(action == GLFW_RELEASE){
		keymap[key] = false;
	}

	glm::vec3 pos_updates = glm::vec3(0.0f,0.0f,0.0f);

	if (keymap[GLFW_KEY_A])
			pos_updates.x = -POS_SPEED;
	if (keymap[GLFW_KEY_D])
			pos_updates.x = POS_SPEED;
	if (keymap[GLFW_KEY_W])
			pos_updates.z = -POS_SPEED;
	if (keymap[GLFW_KEY_S])
			pos_updates.z = POS_SPEED;
	if (keymap[GLFW_KEY_SPACE])
			pos_updates.y = POS_SPEED;
	if (keymap[GLFW_KEY_Z])
			pos_updates.y = -POS_SPEED;
	if (keymap[GLFW_KEY_ESCAPE]) {
		escape_menu_set_toggle = true;
	}

	if(escape_menu_set_toggle) {
		if (escape_menu_set) {
			glCall(GLFWwindow* window = glfwGetCurrentContext());
			glCall(glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL));
		} else {
			glCall(GLFWwindow* window = glfwGetCurrentContext());
			glCall(glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED));
		}
		escape_menu_set = !escape_menu_set;
		escape_menu_set_toggle = false;
	}

	Camera* cam = Camera::getCurrentCamera();
	if(cam)
		cam->OnUpdatePos(pos_updates);
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	static double pitch = 0.0f;
	static double yaw = 0.0f;

	static double last_xpos = 0.0f;
	static double last_ypos = 0.0f;

	static double xoffset = 0.0f;
	static double yoffset = 0.0f;

	xoffset = last_xpos - xpos;
	yoffset = last_ypos - ypos;

	last_xpos = xpos;
	last_ypos = ypos;

	if(!escape_menu_set) {
		return;
	}

	pitch += MOUSE_SENSITIVITY * yoffset;
	yaw -= MOUSE_SENSITIVITY * xoffset;

	if (pitch > 89)
		pitch = 89;
	else if (pitch < -89)
		pitch = -89;

	if (yaw > 360)
		yaw -= 360;
	else if (yaw < -360)
		yaw += 360;

    glm::vec3 direction = glm::vec3(0.0f,0.0f,0.0f);
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction = glm::normalize(direction);

	Camera* cam = Camera::getCurrentCamera();
	if(cam) {
		cam->OnUpdateTarget(direction);
	}

	// std::cout <<glm::to_string(direction)<<std::endl;
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


#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <map>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

class InputHandler
{
private:
	std::map<int, int> track_key_state = {
	{ GLFW_KEY_UP, GLFW_RELEASE },
	{ GLFW_KEY_DOWN, GLFW_RELEASE},
	{ GLFW_KEY_LEFT, GLFW_RELEASE },
	{ GLFW_KEY_RIGHT, GLFW_RELEASE },
	{ GLFW_KEY_E, GLFW_RELEASE },
	{ GLFW_KEY_W, GLFW_RELEASE }
	};

public:
	GLFWwindow* window;

	int Init(int SCR_WIDTH, int SCR_HEIGHT)
	{
#pragma region Init GLFW

		// glfw: initialize and configure
		// ------------------------------
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

#pragma endregion

#pragma region Init Window

		// glfw window creation
		// --------------------
		window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
		if (window == NULL)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return -1;
		}
		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

#pragma endregion

#pragma region Init GLAD

		// glad: load all OpenGL function pointers
		// ---------------------------------------
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return -1;
		}

#pragma endregion

		return 0;
	}
	
	void Update()
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		for (std::map<int, int>::iterator i = track_key_state.begin(); i != track_key_state.end(); i++)
			i->second = glfwGetKey(window, i->first);
	}
	
	bool IsKeyDown(int key) {
		return track_key_state[key] == GLFW_RELEASE && glfwGetKey(window, key) == GLFW_PRESS;
	}

	bool IsKeyUp(int key)
	{
		return track_key_state[key] == GLFW_PRESS && glfwGetKey(window, key) == GLFW_RELEASE;
	}
};

#endif
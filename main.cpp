// Basic C++ file for testing OpenGL
// Author: Mahmoud Abbouchi

#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Windows.h>
#define PI 3.14159265789

void resize_win(GLFWwindow* win, int height, int width);

int main(){
	// Initialization of OpenGL and Window
	std::string name = "Mahmoud";
	std::cout << "Hello world, + " << PI << std::endl;
	std::cin >> name;
	std::cout << name;
	glfwInit();
	// Setting up the window hint to use version 4.6
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Creating a GLFW window with wdith 1000, height 350 and catch error if exists.
	GLFWwindow * window1 = glfwCreateWindow(1000, 350, name.c_str(), NULL, NULL);
	if (window1 == NULL) {
		std::cerr << "Failed to created the GLFW Window." << std::endl;
		return -1;
	}
	glfwMakeContextCurrent(window1);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	// Using openGL
	//glViewport(100, 10, 900, 340);
	glViewport(0, 0, 1000, 350);
	glfwSetFramebufferSizeCallback(window1, resize_win);
	glClearColor(0.9, 0.1, 0.82, 1.0);

	while(!glfwWindowShouldClose(window1)){
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window1);
		glfwPollEvents();
	}
	std::cout << "Window has been closed." << std::endl;
	//Sleep(5000); //Delay to make the program sleep for a while.
	glfwTerminate();
	return 0x1a4;
}

// Creating a frame buffer size callback function
void resize_win(GLFWwindow * win, int height, int width) {
	glViewport(0, 0, height, width);
}
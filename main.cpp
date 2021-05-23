// Basic C++ file for testing OpenGL
// Author: Mahmoud Abbouchi

#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Windows.h>
#define PI 3.14159265789

void resize_win(GLFWwindow* win, int height, int width);

int main() {
	// Initialization of OpenGL and Window and variables
	float obj1_vertices[] = {0.4f, 0.2f, 0.0f,
							 0.3f, -0.2f, 0.0f,
							 0.1f, 0.7f, 0.0f};
	unsigned int obj1_indices[] = {0, 1, 2};
	// Using a c string instead
	const char * vrtx_string_src = "#version 460 core\nlayout(location = 0) in vec3 apos;\nvoid main() {\ngl_Position = vec4(apos, 1.0);\n}";
	const char * frag_string_src = "#version 460 core\nout vec4 frag_colour;\nvoid main() {\nfrag_colour = vec4(0.3, 0.8, 0.01, 1.0);\n}";
	
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

	//Setting Callback function and colour
	glViewport(0, 0, 1000, 350);
	glfwSetFramebufferSizeCallback(window1, resize_win);
	glClearColor(0.7f, 0.1f, 0.62f, 1.0f); //RGBA Colours as floats (not doubles)
	
	//
	unsigned int vrtx_arr_obj;
	glGenVertexArrays(1, &vrtx_arr_obj);
	glBindVertexArray(vrtx_arr_obj);

	// Setting verticies buffer
	unsigned int vrtx_buf_obj;
	// Creates a buffer and stores the buffer id
	glGenBuffers(1, &vrtx_buf_obj);
	// Binding the vertex buffer GL_ARRAY_BUFFER to my vertex
	glBindBuffer(GL_ARRAY_BUFFER, vrtx_buf_obj);
	// Feeds my vertex to the GL_ARRAY_BUFFER slot
	glBufferData(GL_ARRAY_BUFFER, sizeof(obj1_vertices), obj1_vertices,	GL_STATIC_DRAW);

	// Setting up vertex attributes
	// This allows us to define how the vertices should be interpreted
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Creating the vertex shader
	unsigned int vrtx_shader_obj = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vrtx_shader_obj, 1, &vrtx_string_src, NULL);
	glCompileShader(vrtx_shader_obj); //BugFix: Check for error later

	// Creating the fragment shader
	unsigned int frag_shader_obj = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(frag_shader_obj, 1, &frag_string_src, NULL);
	glCompileShader(frag_shader_obj); //BugFix: Check for error later

	// Creating the shader program
	unsigned int shader_prog = glCreateProgram();
	glAttachShader(shader_prog, vrtx_shader_obj);
	glAttachShader(shader_prog, frag_shader_obj);
	glLinkProgram(shader_prog);

	// Cleaning up shaders
	glDeleteShader(vrtx_shader_obj);
	glDeleteShader(frag_shader_obj);

	while(!glfwWindowShouldClose(window1)){
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shader_prog);
		glBindVertexArray(vrtx_arr_obj);
		glDrawArrays(GL_TRIANGLES, 0, 3);
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
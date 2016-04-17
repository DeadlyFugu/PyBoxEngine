#include "gl_render.h"
#include "glfw\glfw3.h"
#include <cstdio>

GLFWwindow* window;
int width, height;

GLRender::GLRender() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	width = 640;
	height = 480;
	window = glfwCreateWindow(width, height, "PyBoxEngine", nullptr, nullptr);
	if (window == nullptr) {
		std::printf("ERROR: could not create window.");
	}
	
	glfwMakeContextCurrent(window);
}

GLRender::~GLRender() {
	glfwTerminate();
}

void GLRender::ClearScreen(float r, float g, float b) {
	glClearColor(r, g, b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLRender::PostUpdate() {
	glfwSwapBuffers(window);
	glfwPollEvents();
}

int GLRender::GetWidth() {
	return width;
}

int GLRender::GetHeight() {
	return height;
}

bool GLRender::IsCloseRequested() {
	return glfwWindowShouldClose(window) ? true : false;
}
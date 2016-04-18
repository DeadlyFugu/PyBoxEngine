#include "gl_render.h"
#include "glew\glew.h"
#include "glfw\glfw3.h"
#include <cstdio>

GLFWwindow* window;
int width, height;
float* view_matrix;

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

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::printf("ERROR: could not init GLEW");
	}

	glViewport(0, 0, width, height);
	glEnable(GL_BLEND);
	glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

	LoadViewMatrix();
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

void GLRender::LoadViewMatrix() {
	static float _view_matrix[] = {
		2.f / width, 0, -1,
		0, 2.f / height, -1,
		0, 0, 1,
	};
	view_matrix = _view_matrix;
}

#include "gl_render.h"
#include <cstdio>
#include <cstdint>
#include <cassert>

#include "bcm_host.h"

#include "GLES2/gl2.h"
#include "EGL/egl.h"
#include "EGL/eglext.h"

static std::uint32_t width, height;

static DISPMANX_DISPLAY_HANDLE_T dispman_display;
static DISPMANX_UPDATE_HANDLE_T dispman_update;
static DISPMANX_ELEMENT_HANDLE_T dispman_element;

static DISPMANX_WINDOW_T native_window;

static EGLDisplay display;
static EGLSurface surface;
static EGLContext context;

float* view_matrix;

GLRender::GLRender() {
	int result;
	
	display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	assert(display != EGL_NO_DISPLAY);

	result = eglInitialize(display, nullptr, nullptr);
	assert(result != EGL_FALSE);

	static const EGLint attrib_list[] = {
		EGL_RED_SIZE, 8,
		EGL_GREEN_SIZE, 8,
		EGL_BLUE_SIZE, 8,
		EGL_ALPHA_SIZE, 8,
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		EGL_NONE
	};
	EGLConfig config;
	EGLint num_config;
	result = eglChooseConfig(display, attrib_list, &config, 1, &num_config);
	assert(result != EGL_FALSE);

	result = eglBindAPI(EGL_OPENGL_ES_API);
	assert(result != EGL_FALSE);

	static const EGLint context_attrib_list[] = {
		EGL_CONTEXT_CLIENT_VERSION, 2,
		EGL_NONE
	};
	context = eglCreateContext(display, config, EGL_NO_CONTEXT, context_attrib_list);
	assert(context != EGL_NO_CONTEXT);

	result = graphics_get_display_size(0, &width, &height);
	assert(result >= 0);

	VC_RECT_T dst_rect{ 0, 0, width, height };
	VC_RECT_T src_rect{ 0, 0, width << 16, height << 16 };

	dispman_display = vc_dispmanx_display_open(0);
	dispman_update = vc_dispmanx_update_start(0);
	dispman_element = vc_dispmanx_element_add(dispman_update, dispman_display,
		0, &dst_rect, 0, &src_rect, DISPMANX_PROTECTION_NONE,
		0, 0, (DISPMANX_TRANSFORM_T) 0);

	native_window.element = dispman_element;
	native_window.width = width;
	native_window.height = height;
	vc_dispmanx_update_submit_sync(dispman_update);

	surface = eglCreateWindowSurface(display, config, &native_window, NULL);
	assert(surface != EGL_NO_SURFACE);

	result = eglMakeCurrent(display, surface, surface, context);
	assert(result != EGL_FALSE);

	glViewport(0, 0, width, height);
	glEnable(GL_BLEND);
	//glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	//glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

	LoadViewMatrix();
}

GLRender::~GLRender() {
	glClear(GL_COLOR_BUFFER_BIT);
	eglSwapBuffers(display, surface);

	eglDestroySurface(display, surface);

	vc_dispmanx_element_remove(dispman_update, dispman_element);
	vc_dispmanx_update_submit_sync(dispman_update);
	vc_dispmanx_display_close(dispman_display);

	eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
	eglDestroyContext(display, context);
	eglTerminate(display);
}

void GLRender::ClearScreen(float r, float g, float b) {
	glClearColor(r, g, b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLRender::PostUpdate() {
	eglSwapBuffers(display, surface);
}

int GLRender::GetWidth() {
	return width;
}

int GLRender::GetHeight() {
	return height;
}

bool GLRender::IsCloseRequested() {
	return false; //TODO: fix
}

void GLRender::LoadViewMatrix() {
	static float _view_matrix[] = {
		2.f / width, 0, -1,
		0, 2.f / height, -1,
		0, 0, 1,
	};
	view_matrix = _view_matrix;
}

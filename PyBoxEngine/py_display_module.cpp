#include "py_display_module.h"
#include "gl_render.h"
#include "input.h"

extern GLRender* glrender;

static PyObject* display_clear_screen(PyObject* self, PyObject* args) {
	float r, g, b;
	if (!PyArg_ParseTuple(args, "fff", &r, &g, &b)) {
		return NULL;
	}
	glrender->ClearScreen(r, g, b);
	return Py_BuildValue("");
}

static PyObject* display_post_update(PyObject* self, PyObject* args) {
	if (!PyArg_ParseTuple(args, "")) {
		return NULL;
	}
	glrender->PostUpdate();
	input.PollDevice(); // TODO probably shouldn't put this here
	return Py_BuildValue("");
}

static PyObject* display_close_requested(PyObject* self, PyObject* args) {
	if (!PyArg_ParseTuple(args, "")) {
		return NULL;
	}
	bool result = glrender->IsCloseRequested();
	return Py_BuildValue("b", result);
}


static PyMethodDef DisplayMethods[] = {
	{ "clear_screen", display_clear_screen, METH_VARARGS,
	"Clears the screen to a specified color" },
	{ "post_update", display_post_update, METH_VARARGS,
	"Displays image, waits for vsync" },
	{ "close_requested", display_close_requested, METH_VARARGS,
	"Returns true if close button was pressed" },
	{ NULL, NULL, 0, NULL }
};

static PyModuleDef DisplayModule = {
	PyModuleDef_HEAD_INIT, "display", NULL, -1 , DisplayMethods, NULL, NULL, NULL, NULL
};

PyObject* PyInit_display(void) {
	return PyModule_Create(&DisplayModule);
}

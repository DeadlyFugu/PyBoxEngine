#include "py_input_module.h"
#include "input.h"


static PyObject* input_axis_lx(PyObject* self, PyObject* args) {
	if (!PyArg_ParseTuple(args, "")) {
		return NULL;
	}
	return Py_BuildValue("f", input.LeftAxisX());
}

static PyObject* input_axis_ly(PyObject* self, PyObject* args) {
	if (!PyArg_ParseTuple(args, "")) {
		return NULL;
	}
	return Py_BuildValue("f", input.LeftAxisY());
}

static PyObject* input_axis_rx(PyObject* self, PyObject* args) {
	if (!PyArg_ParseTuple(args, "")) {
		return NULL;
	}
	return Py_BuildValue("f", input.RightAxisX());
}

static PyObject* input_axis_ry(PyObject* self, PyObject* args) {
	if (!PyArg_ParseTuple(args, "")) {
		return NULL;
	}
	return Py_BuildValue("f", input.RightAxisY());
}

static PyObject* input_button_down(PyObject* self, PyObject* args) {
	int btn;
	if (!PyArg_ParseTuple(args, "i", &btn)) {
		return NULL;
	}
	return Py_BuildValue("b", input.ButtonDown(btn));
}

static PyMethodDef InputMethods[] = {
	{ "axis_lx", input_axis_lx, METH_VARARGS,
	"Gets the value of the left thumbstick's x-axis, from -1.0 to 1.0" },
	{ "axis_ly", input_axis_ly, METH_VARARGS,
	"Gets the value of the left thumbstick's y-axis, from -1.0 to 1.0" },
	{ "axis_rx", input_axis_rx, METH_VARARGS,
	"Gets the value of the right thumbstick's x-axis, from -1.0 to 1.0" },
	{ "axis_ry", input_axis_ry, METH_VARARGS,
	"Gets the value of the right thumbstick's y-axis, from -1.0 to 1.0" },
	{ "button_down", input_button_down, METH_VARARGS,
	"Returns true if the button passed as an argument is held down"},
	{ NULL, NULL, 0, NULL }
};

static PyModuleDef InputModule = {
	PyModuleDef_HEAD_INIT, "input", NULL, -1, InputMethods, NULL, NULL, NULL, NULL
};

PyObject* PyInit_input(void) {
	return PyModule_Create(&InputModule);
}
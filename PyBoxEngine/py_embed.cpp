#include "py_embed.h"
#include "py_graphics_module.h"
#include "py_display_module.h"
#include "py_input_module.h"
#include <Python.h>

PythonEval::PythonEval() {
	PyImport_AppendInittab("graphics", &PyInit_graphics);
	PyImport_AppendInittab("display", &PyInit_display);
	PyImport_AppendInittab("input", &PyInit_input);
	Py_Initialize();
}

PythonEval::~PythonEval() {
	Py_Finalize();
}

void PythonEval::RunFile(char* fname) {
	FILE* fp = _Py_fopen(fname, "r");
	PyRun_SimpleFile(fp, fname);
}
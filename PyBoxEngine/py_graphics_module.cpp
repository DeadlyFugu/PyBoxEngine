#include "py_graphics_module.h"
#include "picture.h"
#include <unordered_map>

static PyObject* emb_greet_native(PyObject* self, PyObject* args) {
	if (!PyArg_ParseTuple(args, "")) {
		return NULL;
	}
	printf("Greetings from C++!\n");
	return Py_BuildValue("");
}

static std::unordered_map<std::string, Picture*> cache_pictures;

static PyObject* graphics_draw_sprite(PyObject* self, PyObject* args) {
	int x, y;
	char* fname_cstr;
	if (!PyArg_ParseTuple(args, "sii", &fname_cstr, &x, &y)) {
		return NULL;
	}
	std::string fname(fname_cstr);
	auto found = cache_pictures.find(fname);
	if (found != cache_pictures.end()) {
		found->second->Draw(x, y);
	} else {
		cache_pictures[fname] = new Picture(fname_cstr);
	}
	return Py_BuildValue("");
}

static PyMethodDef GraphicsMethods[] = {
	{ "greet_native", emb_greet_native, METH_VARARGS,
	"Display a greeting from C++" },
	{ "draw_sprite", graphics_draw_sprite, METH_VARARGS,
	"Draw an image on screen" },
	{ NULL, NULL, 0, NULL }
};

static PyModuleDef GraphicsModule = {
	PyModuleDef_HEAD_INIT, "graphics", NULL, -1, GraphicsMethods, NULL, NULL, NULL, NULL
};

PyObject* PyInit_graphics(void) {
	return PyModule_Create(&GraphicsModule);
}
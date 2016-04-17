// PyBoxEngine.cpp : Defines the entry point for the console application.
//

#include <Python.h>
#include <conio.h>

static PyObject* emb_greet_native(PyObject* self, PyObject* args) {
	if (!PyArg_ParseTuple(args, "")) {
		return NULL;
	}
	printf("Greetings from C++!\n");
	return Py_BuildValue("");
}

static PyMethodDef EmbMethods[] = {
	{"greet_native", emb_greet_native, METH_VARARGS,
	"Display a greeting from C++"},
	{ NULL, NULL, 0, NULL }
};

static PyModuleDef EmbModule = {
	PyModuleDef_HEAD_INIT, "emb", NULL, -1, EmbMethods, NULL, NULL, NULL, NULL
};

static PyObject* PyInit_emb(void) {
	return PyModule_Create(&EmbModule);
}

int main()
{
	char* fname = "embedded.py";
	FILE* fp;

	PyImport_AppendInittab("emb", &PyInit_emb);
	Py_Initialize();

	fp = _Py_fopen(fname, "r");
	PyRun_SimpleFile(fp, fname);

	Py_Finalize();

	printf("Press any key to exit...\n");
	if (!_getch()) _getch();
	return 0;
}


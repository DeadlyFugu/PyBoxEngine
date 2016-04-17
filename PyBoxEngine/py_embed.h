#pragma once

class PythonEval {
public:
	PythonEval();
	~PythonEval();

	void RunFile(char* fname);
};
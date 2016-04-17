#pragma once

class Shader {
public:
	Shader(char* vs_fname, char* fs_fname);
	~Shader();

	void Bind();
private:
	unsigned int program;
};
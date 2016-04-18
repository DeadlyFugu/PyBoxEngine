#include "shader.h"
#include <glew/glew.h>
#include <cstdio>
#include <stdlib.h>

char* ReadTextFile(char* fname) {
	using namespace std;
	FILE* file;
	file = fopen(fname, "rb");
	if (file) {
		fseek(file, 0, SEEK_END);
		int size = ftell(file);
		char* buf = (char*) calloc(size + 1, sizeof(char)); // new char[size + 1];
		rewind(file);
		fread(buf, 1, size, file);
		fclose(file);
		return buf;
	} else {
		printf("ERROR: file not found %s.", fname);
		return nullptr;
	}
}

void CheckShaderErrors(GLuint shader, char* fname) {
	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char log[512];
		glGetShaderInfoLog(shader, 512, nullptr, log);
		std::printf("[%s] compile error: %s", fname, log);
	}
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
}

bool CheckLinkErrors(GLuint program, char* vs_fname, char* fs_fname) {
	int success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		char log[512];
		glGetProgramInfoLog(program, 512, nullptr, log);
		std::printf("[%s and %s] link error: %s", vs_fname, fs_fname, log);
	}
	glGetShaderiv(program, GL_COMPILE_STATUS, &success);
	return success;
}

Shader::Shader(char * vs_fname, char * fs_fname) {
	char* vs_src = ReadTextFile(vs_fname);
	char* fs_src = ReadTextFile(fs_fname);

	if (vs_src == nullptr || fs_src == nullptr) {
		return;
	}

	unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vs_src, nullptr);
	glCompileShader(vs);
	CheckShaderErrors(vs, vs_fname);

	unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fs_src, nullptr);
	glCompileShader(fs);
	CheckShaderErrors(fs, fs_fname);

	unsigned int program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);

	free(vs_src);
	free(fs_src);
	glDeleteShader(vs);
	glDeleteShader(fs);

	bool success = CheckLinkErrors(program, vs_fname, fs_fname);
	if (success) {
		this->program = program;
	}
}

Shader::~Shader() {
	if (this->program) {
		glDeleteProgram(this->program);
	}
}

void Shader::Bind() {
	glUseProgram(this->program);
}

int Shader::GetLocation(char* uniform) {
	return glGetUniformLocation(program, uniform);
}

void Shader::SetFloat(char* uniform, float v) {
	glUniform1f(GetLocation(uniform), v);
}

void Shader::SetVec2(char* uniform, float x, float y) {
	glUniform2f(GetLocation(uniform), x, y);
}

void Shader::SetTexture(char* uniform, Texture* tex, int slot) {
	glActiveTexture(GL_TEXTURE0 + slot);
	tex->Bind();
	glUniform1i(GetLocation(uniform), slot);
}

void Shader::SetMat3(char * uniform, float* mat) {
	glUniformMatrix3fv(GetLocation(uniform), 1, GL_FALSE, mat);
}

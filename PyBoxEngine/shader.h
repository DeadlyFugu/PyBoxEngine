#pragma once
#include "texture.h"

class Shader {
public:
	Shader(char* vs_fname, char* fs_fname);
	~Shader();

	void Bind();
	int GetLocation(char* uniform);
	void SetFloat(char* uniform, float v);
	void SetVec2(char* uniform, float x, float y);
	void SetTexture(char* uniform, Texture* tex, int slot);
private:
	unsigned int program;
};
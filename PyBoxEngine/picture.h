#pragma once
#include "texture.h"
#include "shader.h"
#include "mesh.h"
#include "gl_render.h"

class Picture {
public:
	Picture(char* fname);
	~Picture();
	void Draw(int x, int y);
private:
	Texture* tex;
	Shader* shader;
	Mesh* mesh;
};
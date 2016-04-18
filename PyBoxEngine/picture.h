#pragma once
#include "texture.h"
#include "shader.h"
#include "mesh.h"

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
#pragma once

class Mesh {
public:
	Mesh(int buffc, float* buffp);
	~Mesh();

	void AddAttribute(int pos, int offs, int spacing);
	void Draw();
private:
	unsigned int vao, vbo;
	unsigned int size;
};
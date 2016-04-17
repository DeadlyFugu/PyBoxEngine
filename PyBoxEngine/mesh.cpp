#include "mesh.h"
#include <glew/glew.h>

Mesh::Mesh(int buffc, float* buffp) : vao(0), vbo(0) {
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, buffc * sizeof(float), buffp, GL_STATIC_DRAW);

	size = buffc / 2;
}

Mesh::~Mesh() {
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
}

void Mesh::AddAttribute(int pos, int offs, int spacing) {
	glVertexAttribPointer(pos, 2, GL_FLOAT, GL_FALSE,
		(1 + spacing) * 2 * sizeof(float),
		(void*) (offs * 2 * sizeof(float)));
	glEnableVertexAttribArray(pos);
}

void Mesh::Draw() {
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, size);
}
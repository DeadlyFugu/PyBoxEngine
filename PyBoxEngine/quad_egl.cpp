#include "quad.h"

#include <GLES2/gl2.h>

static float quad_vertices[] = {
	0,0, 0,1, 1,1, 1,0
};

static unsigned char quad_indices[] = {
	0, 1, 2, 0, 2, 3
};

void load_quad() {}

void render_unit_quad() {
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, quad_vertices);
	glEnableVertexAttribArray(0);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, quad_indices);
}
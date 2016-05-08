#include "quad.h"

#include "mesh.h"

static Mesh* quad_mesh;

float quad_vertices[] = {
	0,1,1,1,1,0,
	0,1,1,0,0,0
};

void load_quad() {
	quad_mesh = new Mesh(12, quad_vertices);
	quad_mesh->AddAttribute(0, 0, 0);
}

void delete_quad() {
	delete quad_mesh;
}

void render_unit_quad() {
	quad_mesh->Draw();
}
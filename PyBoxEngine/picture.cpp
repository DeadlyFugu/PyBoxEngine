#include "picture.h"

float quad_vertices[] = {
	0,1,1,1,1,0,
	0,1,1,0,0,0
};

Picture::Picture(char * fname) {
	tex = new Texture(fname);
	shader = new Shader("picture.vs", "picture.fs");
	mesh = new Mesh(12, quad_vertices);
	mesh->AddAttribute(0, 0, 0);
}

Picture::~Picture() {
	delete tex;
	delete shader;
}

void Picture::Draw(int x, int y) {
	shader->Bind();
	shader->SetVec2("pos", x, y);
	shader->SetVec2("dim", tex->GetWidth(), tex->GetHeight());
	float id_mat[] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };
	shader->SetMat3("view", view_matrix);
	//shader->SetTexture("_tex", tex, 0);
	tex->Bind();
	mesh->Draw();
}

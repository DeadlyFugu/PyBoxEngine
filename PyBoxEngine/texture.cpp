#include "texture.h"
#include <glew/glew.h>
#include <soil/SOIL.h>

Texture::Texture(char * fname) {
	unsigned char* image = SOIL_load_image(fname, &width, &height, 0, SOIL_LOAD_RGB);
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
}

Texture::~Texture() {
	glDeleteTextures(1, &tex);
}

void Texture::Bind() {
	glBindTexture(GL_TEXTURE_2D, tex);
}

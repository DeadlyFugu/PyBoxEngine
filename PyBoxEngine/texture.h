#pragma once

class Texture {
public:
	Texture(char* fname);
	~Texture();

	void Bind();
	int GetWidth() { return width; }
	int GetHeight() { return height; }
private:
	int width, height;
	unsigned int tex;
};
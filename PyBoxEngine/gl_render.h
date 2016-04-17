#pragma once

class GLRender {
public:
	GLRender();
	~GLRender();

	void ClearScreen(float r, float g, float b);
	void PostUpdate();

	int GetWidth();
	int GetHeight();

	bool IsCloseRequested();
};
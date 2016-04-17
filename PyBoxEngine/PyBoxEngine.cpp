// PyBoxEngine.cpp : Defines the entry point for the console application.
//

#include "py_embed.h"
#include "gl_render.h"
#include "mesh.h"
#include "shader.h"
#include <conio.h>
#include <stdio.h>

#include <glew/glew.h>

int main()
{
	PythonEval py;
	py.RunFile("embedded.py");

	{
		GLRender g;
		float verts[] = {
			0.0, 1.0, 0.95, 0.31, 0.59, -0.81,
			0.0, 1.0, 0.59, -0.81, -0.59, -0.81,
			0.0, 1.0, -0.59, -0.81, -0.95, 0.31,
		};
		Mesh pentagon(18, verts);
		pentagon.AddAttribute(0, 0, 0);
		Shader shader("shader.vs", "shader.fs");

		while (!g.IsCloseRequested()) {
			g.ClearScreen(1.0f, 0.0f, 0.5f);

			shader.Bind();
			pentagon.Draw();

			g.PostUpdate();
		}
	}

	printf("Press any key to exit...\n");
	if (!_getch()) _getch();
	return 0;
}


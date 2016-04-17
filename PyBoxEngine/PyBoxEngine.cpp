// PyBoxEngine.cpp : Defines the entry point for the console application.
//

#include "py_embed.h"
#include "gl_render.h"
#include <conio.h>
#include <stdio.h>

int main()
{
	PythonEval py;
	py.RunFile("embedded.py");

	{
		GLRender g;
		while (!g.IsCloseRequested()) {
			g.ClearScreen(1.0f, 0.0f, 0.5f);
			g.PostUpdate();
		}
	}

	printf("Press any key to exit...\n");
	if (!_getch()) _getch();
	return 0;
}


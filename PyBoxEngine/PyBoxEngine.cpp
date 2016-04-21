// PyBoxEngine.cpp : Defines the entry point for the console application.
//

#include "py_embed.h"
#include "gl_render.h"
#include "mesh.h"
#include "shader.h"
#include "picture.h"
#include "input.h"
#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <chrono>

#include <glew/glew.h>

GLRender* glrender;

int main()
{
	PythonEval py;
	glrender = new GLRender();
	py.RunFile("game.py");
	delete glrender;

	{
		/*float verts[] = {
			0.0, 1.0, 0.95, 0.31, 0.59, -0.81,
			0.0, 1.0, 0.59, -0.81, -0.59, -0.81,
			0.0, 1.0, -0.59, -0.81, -0.95, 0.31,
		};
		Mesh pentagon(18, verts);
		pentagon.AddAttribute(0, 0, 0);
		Shader shader("shader.vs", "shader.fs");
		Picture picture("grass.png");
		Picture face("face.png");
		float x = 120, y = 150;
		float n = 0;
		using namespace std::chrono;
		steady_clock::time_point prev = steady_clock::now();
		float dt = 1 / 60.f;*/

		/*while (!glrender->IsCloseRequested()) {
			glrender->ClearScreen(1.0f, 0.0f, 0.5f);
			input.PollDevice();
			printf("axes: (%f, %f)\n", input.LeftAxisX(), input.LeftAxisY());
			x += input.LeftAxisX() * 100 * dt;
			y += input.LeftAxisY() *100 * dt;
			//y = 200 + sinf(n * 6.2f / 2) * 120;
			//x = 200 + cosf(n * 6.2f / 2) * 120;
			n+=dt;

			shader.Bind();
			pentagon.Draw();
			picture.Draw(100, 100);
			face.Draw(x, y);

			glrender->PostUpdate();

			steady_clock::time_point current = steady_clock::now();
			dt = duration_cast<duration<double>>(current - prev).count();
			prev = current;
			printf("dt = %f\n", dt);
		}*/
	}

	printf("Press any key to exit...\n");
	if (!_getch()) _getch();
	return 0;
}


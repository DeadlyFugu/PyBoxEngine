// PyBoxEngine.cpp : Defines the entry point for the console application.
//

#include "py_embed.h"
#include <conio.h>
#include <stdio.h>

int main()
{
	PythonEval py;
	py.RunFile("embedded.py");

	printf("Press any key to exit...\n");
	if (!_getch()) _getch();
	return 0;
}


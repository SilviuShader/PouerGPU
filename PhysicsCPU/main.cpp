#include <raylib.h>

int main()
{
	InitWindow(800, 450, "PhysicsCPU");

	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		PollInputEvents();

		BeginDrawing();

		ClearBackground(RAYWHITE);
		DrawText("PhysicsCPU", 10, 10, 10, GRAY);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
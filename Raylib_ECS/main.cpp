#include "Game.h";

Game game;

//Sorry for this Mess, iam a beginner
int main() {
	InitWindow(600, 600, "Engine with ECS");
	SetTargetFPS(60);
	game.Init();
	while (!WindowShouldClose())
	{
		game.Update();
		BeginDrawing();
		game.Draw();
		EndDrawing();
	}
}
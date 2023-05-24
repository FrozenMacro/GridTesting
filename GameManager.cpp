#include "GameManager.h"
#include "raylib.h"

void GameManager::Start()
{
	InitWindow(gameWidth, gameHeight, "Space Invaders");
	SetTargetFPS(60);

	Initialize();

	while (!WindowShouldClose()) // Loop
	{
		Update(GetFrameTime());
	}

	Destroy();
}

void GameManager::Initialize()
{

}

void GameManager::Destroy()
{

}

void GameManager::Update(float deltaTime)
{
	// BEGIN UPDATE // 

	if (IsKeyDown(KEY_LEFT))
	{
		playerPos.x -= force * deltaTime;
	}

	// END UPDATE //

	// BEGIN DRAWING //

	BeginDrawing();
	ClearBackground(BLACK);

	DrawCircle(playerPos.x, playerPos.y, 3, RAYWHITE);

	EndDrawing();

	// END DRAWING //
}
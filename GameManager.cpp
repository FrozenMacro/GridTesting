#include "GameManager.h"
#include "raylib.h"

GameManager::GameManager()
{

}

GameManager::~GameManager()
{

}

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
	playerPos = { startPos.x, startPos.y };
}

void GameManager::Destroy()
{

}

float GameManager::lerp(float a, float b, float t)
{
	return a + (b - a) * t;
}
void GameManager::Update(float deltaTime)
{
	// BEGIN UPDATE // 

	if (IsKeyDown(KEY_LEFT))
	{
		playerPos.x -= force * deltaTime;
	}

	if (IsKeyDown(KEY_RIGHT))
	{
		playerPos.x += force * deltaTime;
	}

	lerpPos = { lerp(lerpPos.x, playerPos.x, deltaTime * 4), lerp(lerpPos.y, playerPos.y, deltaTime * 4) };

	// END UPDATE //

	// BEGIN DRAWING //

	BeginDrawing();
	ClearBackground(BLACK);

	DrawCircle(lerpPos.x, lerpPos.y, 3, RAYWHITE);

	EndDrawing();

	// END DRAWING //
}
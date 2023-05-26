#include "GameManager.h"
#include "raylib.h"
#include <iostream>
#include <vector>
using namespace std;

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

	obj.setPosition({200, 250});
	obj.Intialize();

	/*for (size_t i = 0; i < sizeof(objects) / sizeof(TileObject); i++)
	{
		objects[i].Initialize();
		objects[i].setPosition({startPos.x + (6 * i), startPos.y});
		std::cout << i << std::endl;
		objects[i].blockType = i;
	}*/
}

void GameManager::Destroy()
{

}

void GameManager::DestroyBullet(Bullet obj) {
	std::cout << "HIT BLOCK" << std::endl;
	//bullets.erase(std::remove(bullets.begin(), bullets.end(), obj), bullets.end());
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

	if (IsKeyDown(KEY_SPACE))
	{
		Bullet bull;
		bull.Initialize({lerpPos.x, lerpPos.y}, -50);
		bullets.push_back(bull);
	}

	for (size_t i = 0; i < bullets.size(); i++)
	{
		Bullet bull = bullets[i];
		for (size_t x = 0; x < sizeof(obj.objects) / sizeof(TileObject); x++)
		{
			TileObject obj2 = obj.objects[x];

			if (bull.Overlapping(obj2.min, obj2.max))
			{
				DestroyBullet(bull);
			}
		}
	}

	if (bullets.size() > 0)
	{
		for (size_t i = 0; i < bullets.size(); i++)
		{
			bullets[i].Update(deltaTime);
		}
	}

	// END UPDATE //

	// BEGIN DRAWING //

	BeginDrawing();
	ClearBackground(BLACK);

	DrawCircle(lerpPos.x, lerpPos.y, 3, RAYWHITE);

	obj.Draw();
	/*for (size_t i = 0; i < sizeof(objects) / sizeof(TileObject); i++)
	{
		objects[i].Draw();
	}*/
	if (bullets.size() > 0)
	{
		for (size_t i = 0; i < bullets.size(); i++)
		{
			bullets[i].Draw();
		}
	}

	EndDrawing();

	// END DRAWING //
}
#include "GameManager.h"
#include "raylib.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;

GameManager::GameManager()
{

}

GameManager::~GameManager()
{

}

void GameManager::Start()
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
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
	player.setPosition(startPos);
	player.Initialize();

	camera = {0};
	camera.zoom = 2;
	//camera.target = { gameWidth / 4.0f, gameHeight / 4.0f };

	for (size_t i = 0; i < 4; i++)
	{
		Barricade barricade;
		barricade.position = {(float)(70 * i) + 25, (float)(200)};
		barricade.Intialize();
		barricades.push_back(barricade);
	}

	for (size_t i = 0; i < 55; i++)
	{
		int line = i / 11;
		EnemyClass enemy;
		enemy.setPosition({(float)20 + (20 * (i - (line * 11))), (float)40 + (15 * line)});
		enemy.Initialize();
		enemies.push_back(enemy);
	}
}

void GameManager::DestroyBullet(int index)
{
	if (bullets.size() > 0)
	{
		bullets.erase(bullets.begin() + index);
	}
}

void GameManager::Destroy()
{

}

void GameManager::Update(float deltaTime)
{
	// BEGIN UPDATE // 

	if (IsKeyDown(KEY_ENTER)) {
		ToggleFullscreen();
	}

	player.Update(deltaTime);
	//camera.target = { player.getPosition().x - gameWidth / 4, player.getPosition().y - gameHeight / 4 };

	for (size_t i = 0; i < bullets.size(); i++)
	{
		Bullet bull = bullets[i];
		for (size_t y = 0; y < barricades.size(); y++)
		{
			for (size_t x = 0; x < barricades[y].objects.size(); x++)
			{
				TileObject obj2 = barricades[y].objects[x];

				if (bull.Overlapping(obj2.min, obj2.max))
				{
					DestroyBullet(i);
					barricades[y].objects[x].OnHit();
					break;
				}
			}
		}
		if (bull.Overlapping(player.min, player.max) && bull.type != 1 && !player.hit) {
			DestroyBullet(i);
			lives--;
			player.OnHit(lives);
			cout << lives << endl;
		}	

		if (bull.type != 0){
			for (size_t x = 0; x < enemies.size(); x++)
			{
				if (bull.Overlapping(enemies[x].min, enemies[x].max)) {
					score += enemies[x].GetPoints();
					DestroyBullet(i);
					enemies.erase(enemies.begin() + x);
				}
			}
		}
	}

	bool check = false;
	for (size_t i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].type == 1)
		{
			check = true;
		}
	}

	if (IsKeyDown(KEY_E))
	{
		Bullet bull;
		bull.Initialize({ (float)(rand() % gameWidth), 10}, 150);
		bull.type = 0;
		bullets.push_back(bull);
	}

	if (IsKeyDown(KEY_SPACE) && !check)
	{
		Bullet bull;
		bull.Initialize(player.getPosition(), -300);
		bull.type = 1;
		bullets.push_back(bull);
	}

	if (bullets.size() > 0)
	{
		for (size_t i = 0; i < bullets.size(); i++)
		{
			bullets[i].Update(deltaTime);

			if (bullets[i].position.x <= 0 || bullets[i].position.x >= gameWidth ||
				bullets[i].position.y <= 0 || bullets[i].position.y >= gameHeight)
			{
				DestroyBullet(i);
			}
		}
	}

	for (size_t i = 0; i < barricades.size(); i++)
	{
		for (size_t x = 0; x < barricades[i].objects.size(); x++)
		{
			if (barricades[i].objects[x].hit >= 4)
			{
				barricades[i].objects.erase(barricades[i].objects.begin() + x);
			}
		}
	}

	// END UPDATE //

	// BEGIN DRAWING //

	BeginDrawing();
	ClearBackground(BLACK);

	BeginMode2D(camera);

	player.Draw();
	//DrawCircle(lerpPos.x, lerpPos.y, 3, RAYWHITE);

	for (size_t i = 0; i < barricades.size(); i++)
	{
		barricades[i].Draw();
	}

	for (size_t i = 0; i < bullets.size(); i++)
	{
		bullets[i].Draw();
	}

	for (size_t i = 0; i < enemies.size(); i++)
	{
		enemies[i].Draw();
	}

	string text = "SCORE: " + to_string(score);
	string livesCounter = "LIVES: " + to_string(lives);
	DrawText(text.c_str(), 5, 5, 10, RAYWHITE);
	DrawText(livesCounter.c_str(), 225 , 5, 10, RAYWHITE);
	EndDrawing();

	// END DRAWING //
}
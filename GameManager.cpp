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
	enemies.clear();
	barricades.clear();
	bullets.clear();

	yLevelSpeed = 0;
	waves = 0;
	lives = 3;
	score = 0;

	player.setPosition(startPos);
	player.Initialize();

	camera = {0};
	camera.zoom = 2;
	//camera.target = { gameWidth / 4.0f, gameHeight / 4.0f };

	for (size_t i = 0; i < 4; i++)
	{
		Barricade barricade;
		barricade.position = {(float)(70 * i) + 25, (float)(185)};
		barricade.Intialize();
		barricades.push_back(barricade);
	}

	SpawnEnemies();
}

void GameManager::SpawnEnemies() {
	oppositeDirection = false;
	for (size_t i = 0; i < 55; i++)
	{
		int clampedWaves = waves;
		if (clampedWaves > 4) {
			clampedWaves = 4;
		}
		int line = i / 11;
		EnemyClass enemy;
		switch (line) {
		case 0:
			enemy.type = 2;
			break;
		case 1:
			enemy.type = 1;
			break;
		case 2:
			enemy.type = 1;
			break;
		}
		enemy.setPosition({ (float)10 + (20 * (i - (line * 11))), (float)30 + (15 * line) + (10 * clampedWaves) });
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

void GameManager::OnTimerFinish() {
	float furthest = 0, closest = gameWidth;
	float lowest = 0;
	bool moveDown = false;
	for (size_t i = 0; i < enemies.size(); i++)
	{
		Vector2 newPos = enemies[i].GetPosition();
		if (newPos.x > furthest) {
			furthest = newPos.x;
		}
		if (newPos.x < closest) {
			closest = newPos.x;
		}
		if (newPos.y > lowest) {
			lowest = newPos.y;
		}
	}
	cout << lowest << endl;
	if (lowest >= 190) {
		lives = 0;
	}

	if (!oppositeDirection && furthest >= 272) {
		moveDown = true;
		oppositeDirection = !oppositeDirection;
	}

	if (oppositeDirection && closest <= -4) {
		moveDown = true;
		oppositeDirection = !oppositeDirection;
	}
	for (size_t i = 0; i < enemies.size(); i++)
	{
		Vector2 newPos = enemies[i].GetPosition();
		if (!moveDown)
		{
			newPos.x += 4 * ((oppositeDirection) ? -1 : 1);
		}
		else
		{
			newPos.y += 5;
		}
		enemies[i].setPosition(newPos);
		enemies[i].UpdateSprite();
	}
	int  clampedWaves = waves;
	if (moveDown) { yLevelSpeed++; }
	if (clampedWaves > 4) {
		clampedWaves = 4;
	}
	timer = 30 - (3 * clampedWaves) - (yLevelSpeed);
}

void GameManager::Update(float deltaTime)
{
	if (!player.hit && lives <= 0) {
		// BEGIN DRAWING // GAME OVER UPDATE

		if (IsKeyPressed(KEY_R)) {
			Initialize();
		}

		BeginDrawing();
		ClearBackground(BLACK);

		BeginMode2D(camera);

		string scoreTXT = "FINAL SCORE: " + to_string(score);
		DrawText("GAME OVER", 10, 10, 20, RAYWHITE);
		DrawText(scoreTXT.c_str(), 10, 50, 10, RAYWHITE);
		DrawText("Press R to restart.", 10, 80, 10, RAYWHITE);
		DrawText("Press ESC to quit.", 10, 95, 10, RAYWHITE);

		EndDrawing();

		// END DRAWING //
	}
	else {
		// BEGIN UPDATE // 
		if (timer > 0 && !player.hit) {
			timer -= deltaTime;
			timerActive = true;
		}
		else if (timer <= 0 && timerActive) {
			OnTimerFinish();
			timerActive = false;
		}

		if (enemy_bt > 0 && !player.hit) {
			enemy_bt -= deltaTime;
			enemy_bt_active = true;
		}
		else if (enemy_bt <= 0 && enemy_bt_active) {
			enemy_bt_active = false;
			int enemyPick = rand() % (enemies.size() - 1);
			int minTime = (rand() % 10) + 10, maxTime = (rand() % (20 - (waves * 3))) + 10;
			Bullet bull;
			bull.Initialize(enemies[enemyPick].GetPosition(), 150);
			bull.type = 0;
			bullets.push_back(bull);
			enemy_bt = (rand() % maxTime) + minTime;
		}

		if (enemies.size() == 0) {
			yLevelSpeed = 0;
			cout << "WAVE FINISHED" << endl;
			lives++;
			waves++;
			SpawnEnemies();
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

			if (bull.type != 0) {
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

		if (IsKeyDown(KEY_SPACE) && !check && !player.hit)
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
		DrawText(livesCounter.c_str(), 225, 5, 10, RAYWHITE);
		EndDrawing();

		// END DRAWING //
	}
}
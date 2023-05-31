#pragma once

#include "raylib.h"
#include "TileObject.h"
#include "Barricade.h"
#include "Bullet.h"
#include "PlayerSprite.h"
#include "EnemyClass.h"
#include <vector>
class GameManager
{
public:

	GameManager();
	~GameManager();

	void Start();
	void DestroyBullet(int index);

	Vector2 startPos = { 150, 225 };
	PlayerSprite player;
	Camera2D camera;
	bool game_running;

	std::vector<Barricade> barricades;
	std::vector<Bullet> bullets;
	std::vector<EnemyClass> enemies;
private:
	void Update(float deltaTime);
	void Draw();
	void OnTimerFinish();
	void SpawnEnemies();

	void Initialize();
	void Destroy();
	float lerp(float a, float b, float t);
private:
	int gameWidth = 550, gameHeight = 475;
	int score = 0;
	int lives = 3;
	int timer = 20;
	int enemy_bt = 5;//
	bool enemy_bt_active = false;
	int waves = 0;
	int yLevelSpeed = 0;
	bool timerActive = false;
	bool oppositeDirection;
};
#pragma once

#include "raylib.h"
class GameManager
{
public:

	GameManager();
	~GameManager();

	void Start();
	Vector2 startPos;
	int force = 50;

private:
	void Update(float deltaTime);
	void Draw();

	void Initialize();
	void Destroy();
private:
	int gameWidth = 400, gameHeight = 500;
	Vector2 playerPos;
};
#pragma once

#include "raylib.h"
#include "TileObject.h"
#include "Barricade.h"
class GameManager
{
public:

	GameManager();
	~GameManager();

	void Start();
	Vector2 startPos = {200, 400};
	int force = 150;
	//TileObject objects[4];
	Barricade obj;
private:
	void Update(float deltaTime);
	void Draw();

	void Initialize();
	void Destroy();
	float lerp(float a, float b, float t);
private:
	int gameWidth = 400, gameHeight = 500;
	Vector2 playerPos;
	Vector2 lerpPos {0, 0};
};
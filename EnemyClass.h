#pragma once
#include "raylib.h"
#include <string>
class EnemyClass
{
public:
	void Initialize();
	void Update(float deltaTime);
	void Draw();
	void setPosition(Vector2 pos);
	void UpdateSprite();
	int GetPoints();
	Vector2 GetPosition();
	int type = 0;
	Vector2 min, max;
private:
	int spriteCounter = 0;
	int points;
	Vector2 position;
	Texture sprite;
	Rectangle frameRec;
};


#pragma once
#include "raylib.h"

class Bullet {
public:
	Vector2 position;
	float velocity = 20;
	Rectangle frameRec = { 0, 0, 3, 3 };

	void Draw();
	void Update(float deltaTime);
	void Initialize(Vector2 pos, float speed);
	void Destroy();
	bool Overlapping(Vector2 o_min, Vector2 o_max);
	Vector2 min, max;
	int type = 1; // 0 - Player, Anything else is enemy
};

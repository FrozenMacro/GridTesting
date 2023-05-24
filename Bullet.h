#pragma once
#include "raylib.h"

class Bullet {
public:
	Vector2 position;
	float velocity;

	void Draw();
	void Initialize(Vector2 pos, float speed);
};

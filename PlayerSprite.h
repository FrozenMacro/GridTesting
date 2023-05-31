#pragma once
#include "raylib.h"

class PlayerSprite
{
public:
	void Initialize();
	void setForce(float newForce);
	void setPosition(Vector2 pos);
	Vector2 getPosition();
	void Update(float deltaTime);
	void Draw();
	float lerp(float a, float b, float t);
	void OnHit(int livesLeft);
public:
	Vector2 min, max;
	bool hit = false;
private:
	float timer = 0;
	Texture texture;
	Vector2 position;
	Rectangle frameRec;
	float force = 80;
};


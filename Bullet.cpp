#include "raylib.h"
#include <iostream>
#include <vector>
#include "Bullet.h"

void Bullet::Initialize(Vector2 pos, float speed)
{
	position = pos;
	velocity = speed;
}

void Bullet::Update(float deltaTime)
{
	position.y += velocity * deltaTime;
}

bool Bullet::Overlapping(Vector2 o_min, Vector2 o_max)
{
	return !(max.x < o_min.x || max.y < o_min.y || min.x > o_max.x || min.y > o_max.y);
}

void Bullet::Draw()
{
	min = { position.x - 2, position.y - 2 };
	max = { position.x + 2, position.y + 2 };
	DrawCircle(position.x, position.y, 3, GREEN);
}
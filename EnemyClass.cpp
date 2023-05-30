#include "EnemyClass.h"
#include "GameManager.h"

void EnemyClass::Initialize() {
	sprite = LoadTexture("Resources/alien0");
	frameRec = { 0, 0, 11, 9 };
}

void EnemyClass::Update(float deltaTime, bool running) {
	if (running)
	{

	}
}

void EnemyClass::Draw() {
	DrawTextureRec(sprite, frameRec, position, RAYWHITE);
}
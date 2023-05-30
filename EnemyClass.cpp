#include "EnemyClass.h"
#include "GameManager.h"

void EnemyClass::Initialize() {
	sprite = LoadTexture("Resources/alien0.png");
	frameRec = { 0, 0, 11, 9 };
	switch (type) {
	case 0:
		points = 10;
		break;
	}
}

int EnemyClass::GetPoints() {
	return points;
}

void EnemyClass::setPosition(Vector2 pos) {
	position = pos;
}

void EnemyClass::Update(float deltaTime) {
	//Do something
}

void EnemyClass::Draw() {
	min = { position.x, position.y };
	max = { position.x + frameRec.width, position.y + frameRec.height };
	DrawTextureRec(sprite, frameRec, position, RAYWHITE);
}
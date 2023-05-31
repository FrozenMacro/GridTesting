#include "EnemyClass.h"
#include <string>
void EnemyClass::Initialize() {
	std::string fileName = "";
	switch (type) {
	case 0:
		fileName = "alien0";
		points = 10;
		break;
	case 1:
		fileName = "alien1";
		points = 20;
		break;
	case 2:
		fileName = "alien2";
		points = 40;
		break;
	}
	sprite = LoadTexture(("Resources/" + fileName + ".png").c_str());
	frameRec = { 0, 0, (float)sprite.width / 2, (float)sprite.height };
}

int EnemyClass::GetPoints() {
	return points;
}

Vector2 EnemyClass::GetPosition() {
	return position;
}

void EnemyClass::setPosition(Vector2 pos) {
	position = pos;
}

void EnemyClass::Update(float deltaTime) {
	//Do something
}

void EnemyClass::UpdateSprite() {
	spriteCounter++;
	if (spriteCounter > 1) {
		spriteCounter = 0;
	}
	frameRec.x = frameRec.width * spriteCounter;
}

void EnemyClass::Draw() {
	min = { position.x, position.y };
	max = { position.x + frameRec.width, position.y + frameRec.height };
	DrawTextureRec(sprite, frameRec, position, RAYWHITE);
}
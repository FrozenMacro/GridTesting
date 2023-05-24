#include "Barricade.h"

#include "TileObject.h"
#include "raylib.h"

void Barricade::setPosition(Vector2 pos)
{
	position = pos;

	for (size_t i = 0; i < sizeof(objects) / sizeof(TileObject); i++)
	{
		switch (i)
		{
		case 0 | 1 | 2 | 3:
			objects[i].setPosition({ position.x + (6 * i), position.y });
		case 4 | 5 | 6 | 7:
			objects[i].setPosition({ position.x + (6 * i), position.y + 6 });
		case 8 | 9:
			objects[i].setPosition({ position.x + (6 * i), position.y + 12 });
		}
	}
}

void Barricade::Intialize()
{
	start_pos = { 200, 250 };
	for (size_t i = 0; i < sizeof(objects) / sizeof(TileObject); i++)
	{
		int amount = (i / 4);
		objects[i].Initialize();
		objects[i].setPosition({ start_pos.x + (6 * i) - (amount * 6 * 4), start_pos.y + (amount * 6)});
		switch (i)
		{
		case 0:
			objects[i].blockType = 4;
			break;
		case 3:
			objects[i].blockType = 1;
			break;
		case 10:
			objects[i].blockType = 3;
			break;
		case 9:
			objects[i].blockType = 2;
			break;
		}
	}
}

void Barricade::Draw()
{
	for (size_t i = 0; i < sizeof(objects) / sizeof(TileObject); i++)
	{
		objects[i].Draw();
	}
}

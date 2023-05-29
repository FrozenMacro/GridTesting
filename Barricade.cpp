#include "Barricade.h"

#include "TileObject.h"
#include "raylib.h"

void Barricade::setPosition(Vector2 pos)
{
	position = pos;

	for (size_t i = 0; i < objects.size(); i++)
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
	for (size_t i = 0; i < 10; i++)
	{
		TileObject obj;
		obj.blockType = 0;
		int amount = (i / 4);
		obj.Initialize();
		obj.setPosition({ position.x + (6 * i) - (amount * 6 * 4), position.y + (amount * 6)});
		switch (i)
		{
		case 0:
			obj.blockType = 4;
			break;
		case 3:
			obj.blockType = 1;
			break;
		case 9:
			obj.position.x += 12;
			//obj.blockType = 2;
			break;
		case 5:
			obj.blockType = 2;
			break;
		case 6:
			obj.blockType = 3;
			break;
		}
		objects.push_back(obj);
	}
}

void Barricade::Draw()
{
	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i].Draw();
	}
}

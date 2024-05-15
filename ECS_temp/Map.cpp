#include "Map.h"
#include <fstream>
#include "Components.h"

extern Manager manager;

Map::Map(const char* texPath, int ms, int ts) : texturePath(texPath), mapScale(ms), tileSize(ts) {
	scaledSize = ms * ts;
}

Map::~Map() {

}

void Map::LoadMap(std::string path, int sizeX, int sizeY)
{
	char c;
	std::fstream mapFile;
	mapFile.open(path);

	int srcX, srcY;
	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(c);
			srcY = atoi(&c) * tileSize;
			mapFile.get(c);
			srcX = atoi(&c) * tileSize;

			AddTile(srcY, srcX, x * scaledSize, y * scaledSize);
			mapFile.ignore();
		}
	}
	mapFile.ignore();
	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(c);
			std::cout << c;
			if (c == '1')
			{

				//auto& tcol(manager.addEntity());
				//tcol.addComponent<ColliderComponent>("terrain", x * scaledSize, y * scaledSize, scaledSize);
				//tcol.addGroup(Game::groupColliders);

			}
			mapFile.ignore();
		}
	}
	std::cout << '\n';
	mapFile.close();
}

void Map::AddTile(int srcX, int srcY, int xPos, int yPos)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcY, srcX, xPos, yPos, tileSize, mapScale, texturePath);
	//tile.addGroup(Game::groupMap);
}
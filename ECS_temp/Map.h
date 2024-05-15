#pragma once
#include <string>

class Map {
public:
	Map(const char* texPath, int ms, int ts);
	~Map();

	void LoadMap(std::string path, int sizeX, int sizeY);
	void AddTile(int srcX, int srcY, int xPos, int yPos);
private:
	const char* texturePath;
	int mapScale;
	int tileSize;
	int scaledSize;
};
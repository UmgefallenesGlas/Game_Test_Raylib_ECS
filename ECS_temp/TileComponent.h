#pragma once
#include "Components.h"

class TileComponent : public Component {
public:
	Texture texture;
	Rectangle srcRect;
	Rectangle destRect;
	Vector2 position;

	TileComponent() = default;
	~TileComponent() {
		UnloadTexture(texture);
	}

	TileComponent(int srcX, int srcY, int xPos, int yPos, int tSize, int tScale, const char* path) {
		Image tempImg = LoadImage(path);
		texture = LoadTextureFromImage(tempImg);
		UnloadImage(tempImg);

		position.x = xPos;
		position.y = yPos;
		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.width = srcRect.height = tSize;

		destRect.x = xPos;
		destRect.y = yPos;
		destRect.width = destRect.height = tSize * tScale;
	}

	void update() override {
		destRect.x = position.x;
		destRect.y = position.y;
	}

	void draw() override {
		DrawTexturePro(texture, srcRect, destRect, position, 0, WHITE);
	}
};
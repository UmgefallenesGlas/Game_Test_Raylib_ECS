#pragma once
#include <raylib.h>

#include "ECS/Components.h"

class Game
{
public:
	Game();
	~Game();

	void Init();
	void Update();
	void Draw();

	static Camera2D camera;

	enum groupLabels : std::size_t {
		groupMap,
		groupPlayer,
		groupEnemys,
		groupColliders
	};

private:
	
};
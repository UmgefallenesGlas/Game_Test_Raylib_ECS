#pragma once
#include <raylib.h>

#include "ECS/Components.h"
#include "ECS/ECS.h"

class Game
{
public:
	void Init();
	void Update();
	void Draw();

	static Manager manager;
	static Camera2D camera;

	enum groupLabels : std::size_t {
		groupMap,
		groupPlayer,
		groupEnemys,
		groupColliders
	};
};
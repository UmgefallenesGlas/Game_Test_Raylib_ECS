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
	//Declaration for Manager here. Also want to have a refrence to Manager for my Components
	static Camera2D camera;

	enum groupLabels : std::size_t {
		groupMap,
		groupPlayer,
		groupEnemys,
		groupColliders
	};

private:
	
};
#pragma once
#include <raylib.h>

#include "ECS/Components.h"
#include "ECS/ECS.h"

class Game
{
public:
	Game();//Doesnt need this, should i delete it?
	~Game();//This too
	
	void Init();
	void Update();
	void Draw();
	//Need to add Unload()

	static Manager manager;
	static Camera2D camera;

	enum groupLabels : std::size_t {
		groupMap,
		groupPlayer,
		groupEnemys,
		groupColliders
	};

private:
	
};
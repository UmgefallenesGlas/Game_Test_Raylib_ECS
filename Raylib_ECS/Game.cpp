#include "Game.h"
#include <raymath.h>
#include "ECS/Collision.h"

Manager Game::manager;
Manager manager;
Collision collision;
Camera2D Game::camera;

#pragma region Objects
auto& wall1 = Game::manager.addEntity();
auto& wall2 = Game::manager.addEntity();
auto& wall3 = Game::manager.addEntity();
auto& myEntity = manager.addEntity();
auto& player = Game::manager.addEntity();
#pragma endregion

Vector2 inputKeys;

enum playerLookDir { up, down, left, right };
playerLookDir playerDir;
float speed = 400.f;


void HandlePlayer() {
	Vector2 newPosOrigin = player.getComponent<TransformComponent>().position;
	#pragma region InputHandling
	inputKeys = { (float)(-IsKeyDown(KEY_A) + IsKeyDown(KEY_D)),
				(float)(-IsKeyDown(KEY_W) + IsKeyDown(KEY_S)) };



	if (inputKeys.x > 0) {
		playerDir = playerLookDir(right);
	}
	else if (inputKeys.x < 0) {
		playerDir = playerLookDir(left);
	}
	else if (inputKeys.y > 0) {
		playerDir = playerLookDir(down);
	}
	else if (inputKeys.y < 0) {
		playerDir = playerLookDir(up);
	}

	switch (playerDir)
	{
	case up:
		if (inputKeys.x != 0 || inputKeys.y != 0) {
			player.getComponent<AnimatedSpriteComponent>().Play("Walk_Up");
		}
		else {
			player.getComponent<AnimatedSpriteComponent>().Play("Idle_Up");
		}
		break;
	case down:
		if (inputKeys.x != 0 || inputKeys.y != 0) {
			player.getComponent<AnimatedSpriteComponent>().Play("Walk_Down");
		}
		else {
			player.getComponent<AnimatedSpriteComponent>().Play("Idle_Down");
		}
		break;
	case left:
		if (inputKeys.x != 0 || inputKeys.y != 0) {
			player.getComponent<AnimatedSpriteComponent>().Play("Walk_Left");
		}
		else {
			player.getComponent<AnimatedSpriteComponent>().Play("Idle_Left");
		}
		break;
	case right:
		if (inputKeys.x != 0 || inputKeys.y != 0) {
			player.getComponent<AnimatedSpriteComponent>().Play("Walk_Right");
		}
		else {
			player.getComponent<AnimatedSpriteComponent>().Play("Idle_Right");
		}
		break;
	default:
		break;
	}

	newPosOrigin = Vector2Add(newPosOrigin, Vector2Scale(inputKeys, speed * GetFrameTime()));
	collision.MovingObjectCollision(&newPosOrigin, player);
#pragma endregion

	player.getComponent<TransformComponent>().position = newPosOrigin;
}

void Game::Init(){
	#pragma region Objects

	wall1.addComponent<TransformComponent>(96, 128, 32, 32, 2, 0);
	wall1.addComponent<SpriteComponent>("assets/water.png");
	wall1.addGroup(groupMap);

	wall2.addComponent<TransformComponent>(288+1, 128, 96, 32, 2, 0);
	wall2.addComponent<SpriteComponent>("assets/dirt.png");
	wall2.addGroup(groupMap);

	wall3.addComponent<TransformComponent>(256-32, 128+64, 32, 96, 2, 0);
	wall3.addComponent<SpriteComponent>("assets/water.png");
	wall3.addGroup(groupMap);


	player.addComponent<TransformComponent>(300, 300, 32, 32, 2, 0);
	player.addComponent<AnimatedSpriteComponent>("assets/Char_Main_file.png");
	player.addGroup(groupPlayer);

#pragma endregion
	#pragma region Animation
	Animation idle_down = Animation(0, 1, 5);
	Animation idle_up = Animation(1, 1, 5);
	Animation idle_left = Animation(2, 1, 5);
	Animation idle_right = Animation(3, 1, 5);

	Animation walk_down = Animation(0, 4, 5);
	Animation walk_up = Animation(1, 4, 5);
	Animation walk_left = Animation(2, 4, 5);
	Animation walk_right = Animation(3, 4, 5);

	player.getComponent<AnimatedSpriteComponent>().animations.emplace("Idle_Down", idle_down);
	player.getComponent<AnimatedSpriteComponent>().animations.emplace("Idle_Up", idle_up);
	player.getComponent<AnimatedSpriteComponent>().animations.emplace("Idle_Left", idle_left);
	player.getComponent<AnimatedSpriteComponent>().animations.emplace("Idle_Right", idle_right);

	player.getComponent<AnimatedSpriteComponent>().animations.emplace("Walk_Down", walk_down);
	player.getComponent<AnimatedSpriteComponent>().animations.emplace("Walk_Up", walk_up);
	player.getComponent<AnimatedSpriteComponent>().animations.emplace("Walk_Left", walk_left);
	player.getComponent<AnimatedSpriteComponent>().animations.emplace("Walk_Right", walk_right);
	playerDir = playerLookDir(down);
#pragma endregion
	Game::camera.zoom = 1;
}

void Game::Update(){
	HandlePlayer();
	manager.update();
	manager.refresh();
}

void Game::Draw(){
	ClearBackground(WHITE);
	BeginMode2D(Game::camera);
	manager.draw();
	EndMode2D();
	//|--------UI | UX Here--------|
	DrawFPS(0, 0);
	//|----------------------------|
}
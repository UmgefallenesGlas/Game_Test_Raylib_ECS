#include "Game.h"
#include "GameManager.h"
#include <raymath.h>
#include "ECS/Collision.h"

Manager Game::manager;

Collision collision;
Camera2D Game::camera;

#pragma region Objects
auto& coin1(Game::manager.addEntity());
auto& coin2(Game::manager.addEntity());
auto& coin3(Game::manager.addEntity());
auto& coin4(Game::manager.addEntity());

auto& player(Game::manager.addEntity());
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

#pragma endregion
	#pragma region Collision


	//collision.PlayerCollision(newPosOrigin);
	
	//want to do that everything here is in collision -> PlayerCollision
	
	Vector2 intersectPoint[2] = { {-100,-100},{-100,-100} };
	bool collided = false;
	int collisionCount = 0;
	for (auto& e : Game::manager.entities) {
		if (e->hasGroup(Game::groupMap) && e->isActive() == 1 && e->hasComponent<TransformComponent>()) {
			Vector2 hitPoint = {
				float(-(player.getComponent<TransformComponent>().width *	player.getComponent<TransformComponent>().scale)),
				float(-(player.getComponent<TransformComponent>().height * player.getComponent<TransformComponent>().scale)),
			};
			Vector2 hitNormal = { 0,0 };
			collision.PointNearestRectanglePoint(e->getComponent<TransformComponent>().rectangle, newPosOrigin, &hitPoint, &hitNormal);
			Vector2 vectorToHit = Vector2{ hitPoint.x - newPosOrigin.x, hitPoint.y - newPosOrigin.y };

			bool inside = Vector2LengthSqr(vectorToHit) < player.getComponent<TransformComponent>().width * player.getComponent<TransformComponent>().width;

			if (inside)
			{
				collided = true;
				intersectPoint[collisionCount++] = hitPoint;

				// normalize
				vectorToHit = Vector2Normalize(vectorToHit);

				// get point that is deepest into the rectangle
				Vector2 projectedPoint = Vector2Add(newPosOrigin, Vector2Scale(vectorToHit, player.getComponent<TransformComponent>().width));

				// shift it to nearest
				Vector2 delta = { 0,0 };

				if (hitNormal.x != 0)
					delta.x = hitPoint.x - projectedPoint.x;
				else
					delta.y = hitPoint.y - projectedPoint.y;

				// shift the new point by the delta to push us outside of the rectangle
				newPosOrigin = Vector2Add(newPosOrigin, delta);
			}
		}

	}


#pragma endregion
	player.getComponent<TransformComponent>().position = newPosOrigin;
}

Game::Game() { }

Game::~Game() { }

void Game::Init(){
	#pragma region Objects
	coin1.addComponent<TransformComponent>(96, 128, 32, 32, 2, 0);
	coin1.addComponent<SpriteComponent>("assets/water.png");
	coin1.addGroup(groupMap);

	coin2.addComponent<TransformComponent>(256, 128, 32, 32, 2, 0);
	coin2.addComponent<SpriteComponent>("assets/dirt.png");
	coin2.addGroup(groupMap);

	coin3.addComponent<TransformComponent>(352-32, 128, 32, 32, 2, 0);
	coin3.addComponent<SpriteComponent>("assets/grass.png");
	coin3.addGroup(groupMap);

	coin4.addComponent<TransformComponent>(480, 128, 32, 32, 2, 0);
	coin4.addComponent<SpriteComponent>("assets/water.png");
	coin4.addGroup(groupMap);


	player.addComponent<TransformComponent>(300, 300, 32, 32, 2, 0);
	player.addComponent<AnimatedSpriteComponent>("assets/Char_Main_file.png");
	player.addGroup(groupPlayer);
	//player.addGroup(groupColliders);
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
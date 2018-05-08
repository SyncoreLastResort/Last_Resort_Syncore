#include "Application.h"
#include "PowerUpHolder.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"

PowerUpHolder::PowerUpHolder(int x, int y) : Enemy(x, y)
{
	texturename = App->enemies->someenemies;
	life = 1;
	score = 100;

	fly.PushBack({ 0,178,32,16 });
	fly.PushBack({ 0, 194, 32, 15 });
	fly.PushBack({ 0, 209, 32, 16 });
	fly.PushBack({ 0, 225, 32, 15 });
	fly.PushBack({ 0, 240, 32, 16 });
	fly.speed = 0.075f;
	fly.loop = true;

	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, 24, 24 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;
}

void PowerUpHolder::Move()
{
	
	position.x -= 1;
}
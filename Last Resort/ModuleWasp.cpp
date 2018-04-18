#include "Application.h"
#include "ModuleWasp.h"
#include "ModuleCollision.h"

Enemy_Wasp::Enemy_Wasp(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 0,177,32,16 });
	fly.PushBack({ 0, 193, 32, 15 });
	fly.PushBack({ 0, 208, 32, 16 });
	fly.PushBack({ 0, 224, 32, 15 });
	fly.PushBack({ 0, 239, 32, 16 });
	fly.speed = 0.1f;
	fly.loop = true;

	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, 24, 24 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;
}

void Enemy_Wasp::Move()
{
	
	position.x -= 1;
}
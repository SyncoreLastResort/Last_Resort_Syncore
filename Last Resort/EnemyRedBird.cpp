#include "Application.h"
#include "EnemyRedBird.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"

Enemy_RedBird::Enemy_RedBird(int x, int y) : Enemy(x, y)
{

	texturename = App->enemies->someenemies;
	fly.PushBack({ 162,235,26,10 });
	fly.PushBack({ 189,231,26,18 });
	fly.PushBack({ 0,225,27,29 }); 
	fly.PushBack({ 27, 231, 26, 18 }); 
	fly.PushBack({ 54, 235, 26, 18 });
	fly.PushBack({ 81, 230, 26, 19 });
	fly.PushBack({ 108, 226, 26, 29 });
	
	fly.speed = 0.1f;
	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, 24, 24 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	score = 150;
	original_y = y;
}

void Enemy_RedBird::Move()
{
	if (going_up)
	{
		if (wave > 1.0f)
			going_up = false;
		else
			wave += 0.025f;
	}
	else
	{
		if (wave < -1.0f)
			going_up = true;
		else
			wave -= 0.025f;
	}

	position.y = int(float(original_y) + (25.0f * sinf(wave)));
	position.x -= 1;
}

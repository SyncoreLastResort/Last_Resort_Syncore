#include "Application.h"
#include "ModuleRhino.h"
#include "ModuleCollision.h"


Enemy_Rhino::Enemy_Rhino(int x, int y) : Enemy(x, y)
{

	life = 6;
	movement.PushBack({ 64,211,48,45 });
	movement.PushBack({ 112,211,48,45 });
	movement.PushBack({ 160,211,48,45 });
	movement.PushBack({ 208,211,48,45 });
	movement.PushBack({ 160,211,48,45 });
	movement.PushBack({ 112,211,48,45 });
	movement.PushBack({ 64,211,48,45 });
	
	animation = &movement;
	movement.speed = 0.04f;
	movement.loop = true;
	

	collider = App->collision->AddCollider({ 0, 0, 48, 45 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	original_y = y;

}

void Enemy_Rhino::Move()
{
	if (going_up)
	{
		if (wave > 1.0f)
			going_up = false;
		else
			wave += 0.05f;
	}
	else
	{
		if (wave < -1.0f)
			going_up = true;
		else
			wave -= 0.05f;
	}

	position.y = ((float)(original_y)+(69.0f * sinf(wave)));
	position.x -= 1;
}
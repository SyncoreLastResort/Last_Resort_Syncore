#include "Application.h"
#include "PowerUpBomb.h"
#include "ModuleCollision.h"

Power_Up_Bomb::Power_Up_Bomb(int x, int y) : Enemy(x, y)
{

	//Power up animation
	Powerup.PushBack({ 33,204,31,16 });
	Powerup.loop = true;
	Powerup.speed = 0.05f;

	animation = &Powerup;

	collider = App->collision->AddCollider({ 0, 0, 24, 24 }, COLLIDER_TYPE::COLLIDER_POWERUP, (Module*)App->enemies);

	original_y = y;
}


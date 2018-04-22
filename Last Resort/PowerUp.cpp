#include "Application.h"
#include "PowerUp.h"
#include "ModuleCollision.h"

Power_Up::Power_Up(int x, int y) : Enemy(x, y)
{

	//Power up animation
	Powerup.PushBack({ 33,188,31,16 });
	Powerup.loop = true;
	Powerup.speed = 0.05f;

	weapon_upgraded = WEAPON_TYPE::LASER_BEAM;
	
	animation = &Powerup;


	collider = App->collision->AddCollider({ 0, 0, 24, 24 }, COLLIDER_TYPE::COLLIDER_POWERUP, (Module*)App->enemies);

	original_y = y;
}


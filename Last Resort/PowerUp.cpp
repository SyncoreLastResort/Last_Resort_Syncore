#include "Application.h"
#include "PowerUp.h"
#include "ModuleCollision.h"

Power_Up::Power_Up(int x, int y) : Enemy(x, y)
{

	//Powe up animation
	Powerup.PushBack({ 33,188,31,16 });
	Powerup.PushBack({ 33,204,31,16 });
	Powerup.loop = true;
	Powerup.speed = 0.05f;

	animation = &Powerup;

	collider = App->collision->AddCollider({ 0, 0, 24, 24 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;
}

//void Enemy_Wasp::Move()
//{
//
//	position.x -= 1.5;
//}
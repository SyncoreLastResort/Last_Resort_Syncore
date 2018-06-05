#include "Application.h"
#include "CannonPlatform.h"
#include "ModuleCollision.h"
#include "ModuleCollision.h"
#include "Animation.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"


CannonPlatform::CannonPlatform(int x, int y) : Enemy(x, y)
{
	idle.PushBack({ 160, 150, 80, 50 });
	idle.loop = true;

	shooting.PushBack({160, 150, 80, 50});
	shooting.PushBack({ 80, 150, 80, 50 });
	shooting.PushBack({ 0, 150, 80, 50 });
	shooting.PushBack({ 160, 100, 80, 50 });
	shooting.PushBack({ 80, 100, 80, 50 });
	shooting.PushBack({ 0, 100, 80, 50 });
	shooting.PushBack({ 160, 50, 80, 50 });
	shooting.PushBack({ 80, 50, 80, 50 });
	shooting.PushBack({ 0, 50, 80, 50 });
	shooting.PushBack({ 160, 0, 80, 50 });
	shooting.PushBack({ 80, 0, 80, 50 });
	shooting.PushBack({ 0, 0, 80, 50 });
	shooting.PushBack({ 80, 0, 80, 50 });
	shooting.PushBack({ 160, 0, 80, 50 });
	shooting.PushBack({ 0, 50, 80, 50 });
	shooting.PushBack({ 80, 50, 80, 50 });
	shooting.PushBack({ 160, 50, 80, 50 });
	shooting.PushBack({ 0, 100, 80, 50 });
	shooting.PushBack({ 80, 100, 80, 50 });
	shooting.PushBack({ 160, 100, 80, 50 });
	shooting.PushBack({ 0, 150, 80, 50 });
	shooting.PushBack({ 80, 150, 80, 50 });
	shooting.PushBack({ 160, 150, 80, 50 });
	shooting.speed = 0.2f;
	shooting.loop = false;

	animation = &idle;
	score = 500;
	life = 10;
	texturename = App->enemies->cannonplatform;
	
	collider = App->collision->AddCollider({ 0, 10, 80, 30 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);


}

void CannonPlatform::Move()
{
	if (counter >= 150) {
		counter = 0;
		shot = true;
		shooting.Reset();
	}
	else {
		counter++;
	}

	if (shot == true) {
		animation = &shooting;
		App->particles->Cannon_shot.speed.x = 2;
		App->particles->Cannon_shot.speed.x++;
		App->particles->AddParticle(App->particles->Cannon_shot, position.x + 20, position.y, COLLIDER_TYPE::COLLIDER_ENEMY_SHOT);
	}
}
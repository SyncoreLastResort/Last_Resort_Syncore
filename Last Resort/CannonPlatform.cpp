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

}

void CannonPlatform::Move()
{
	PlayerPosition = App->player->position;

	if (counter >= 150) {
		counter = 0;
		shooting.Reset();
		animation = &shooting;
		if (PlayerPosition.x > position.x) {
			App->particles->Cannon_laser.speed.x = 2;
			App->particles->Cannon_laser.speed.x++;
			App->particles->AddParticle(App->particles->Cannon_shot, position.x + 80, position.y + 20, COLLIDER_TYPE::COLLIDER_BOSS_SHOT, 500);
			App->particles->AddParticle(App->particles->Cannon_laser, position.x + 80, position.y + 20, COLLIDER_TYPE::COLLIDER_BOSS_SHOT,500);
		}
		else if (PlayerPosition.x < position.x ) {
			App->particles->Cannon_laser.speed.x = -2;
			App->particles->Cannon_laser.speed.x--;
			App->particles->AddParticle(App->particles->Cannon_shot, position.x, position.y + 20, COLLIDER_TYPE::COLLIDER_BOSS_SHOT,500);
			App->particles->AddParticle(App->particles->Cannon_laser, position.x, position.y + 20, COLLIDER_TYPE::COLLIDER_BOSS_SHOT,500);
		}
	}
	else {
		counter++;
	}

}
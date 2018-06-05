#include "Application.h"
#include "EnemySpider.h"
#include "ModuleCollision.h"
#include "ModuleCollision.h"
#include "Animation.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include <math.h>


EnemySpider::EnemySpider(int x, int y) : Enemy(x, y)
{

	left_bottom.PushBack({ 0, 0, 32, 31 });
	left_bottom.PushBack({ 32, 0, 32, 31 });
	left_bottom.PushBack({ 64, 0, 32, 31 });
	left_bottom.PushBack({ 96, 0, 32, 31 });

	left_bottom.speed = 0.1f;

	right_bottom.PushBack({ 0, 31, 32, 31 });
	right_bottom.PushBack({ 32, 31, 32, 31 });
	right_bottom.PushBack({ 64, 31, 32, 31 });
	right_bottom.PushBack({ 96, 31, 32, 31 });

	right_bottom.speed = 0.1f;

	left_top.PushBack({ 0, 62, 32, 31 });
	left_top.PushBack({ 32, 62, 32, 31 });
	left_top.PushBack({ 64, 62, 32, 31 });
	left_top.PushBack({ 96, 62, 32, 31 });

	left_top.speed = 0.1f;

	right_top.PushBack({ 0, 93, 32, 31 });
	right_top.PushBack({ 32, 93, 32, 31 });
	right_top.PushBack({ 64, 93, 32, 31 });
	right_top.PushBack({ 96, 93, 32, 31 });

	right_top.speed = 0.1f;

	score = 200;
	life = 3;
	texturename = App->enemies->spider;


	animation = &left_top;
	/*left_top.speed = 0.04f;*/
	left_top.loop = true;


	collider = App->collision->AddCollider({ 0, 0, 48, 45 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	original_y = y;

}

void EnemySpider::Move()
{
	PlayerPosition = App->player->position;

	radians = atan2((position.y - PlayerPosition.y), (position.x - PlayerPosition.x));
	radians2 = atan2((PlayerPosition.y + 2 - position.y), (PlayerPosition.x + 6 - position.x));

	angle2 = radians2*(180 / PI);
	if (radians2 < 0) {
		angle2 += 360;
	}
	angle = radians*(180 / PI);
	if (radians < 0) {
		angle += 360;
	}

	if (going_left)
	{
		if (PlayerPosition.x > position.x +30)
		{
			going_left = false;
			if (original_y > SCREEN_HEIGHT / 2) { animation = &right_bottom; }
			else { animation = &right_top; }

			App->particles->BeeShot.speed.x = 2 * (cos(angle2*PI / 180));
			App->particles->BeeShot.speed.x++;
			App->particles->BeeShot.speed.y = 2 * (sin(angle2*PI / 180));
			App->particles->AddParticle(App->particles->BeeShot, position.x + 20, position.y, COLLIDER_TYPE::COLLIDER_ENEMY_SHOT);
			App->particles->BeeShot.speed.x = 3 * (cos(angle2*PI / 180));
			App->particles->BeeShot.speed.x++;
			App->particles->BeeShot.speed.y = 3 * (sin(angle2*PI / 180));
			App->particles->AddParticle(App->particles->BeeShot, position.x + 20, position.y, COLLIDER_TYPE::COLLIDER_ENEMY_SHOT);
			App->particles->BeeShot.speed.x = 4 * (cos(angle2*PI / 180));
			App->particles->BeeShot.speed.x++;
			App->particles->BeeShot.speed.y = 4 * (sin(angle2*PI / 180));
			App->particles->AddParticle(App->particles->BeeShot, position.x + 20, position.y, COLLIDER_TYPE::COLLIDER_ENEMY_SHOT);
		}
		else
			position.x -= 2;
	}
	else
	{
		if (PlayerPosition.x < position.x - 30)
		{
			going_left = true;
			if (original_y > SCREEN_HEIGHT / 2) { animation = &left_bottom; }
			else { animation = &left_top; }

			App->particles->BeeShot.speed.x = 2 * (cos(angle2*PI / 180));
			App->particles->BeeShot.speed.x++;
			App->particles->BeeShot.speed.y = 2 * (sin(angle2*PI / 180));
			App->particles->AddParticle(App->particles->BeeShot, position.x + 20, position.y, COLLIDER_TYPE::COLLIDER_ENEMY_SHOT);
			App->particles->BeeShot.speed.x = 3 * (cos(angle2*PI / 180));
			App->particles->BeeShot.speed.x++;
			App->particles->BeeShot.speed.y = 3 * (sin(angle2*PI / 180));
			App->particles->AddParticle(App->particles->BeeShot, position.x + 20, position.y, COLLIDER_TYPE::COLLIDER_ENEMY_SHOT);
			App->particles->BeeShot.speed.x = 4 * (cos(angle2*PI / 180));
			App->particles->BeeShot.speed.x++;
			App->particles->BeeShot.speed.y = 4 * (sin(angle2*PI / 180));
			App->particles->AddParticle(App->particles->BeeShot, position.x + 20, position.y, COLLIDER_TYPE::COLLIDER_ENEMY_SHOT);

		}
		else
			position.x += 2;
	}

}
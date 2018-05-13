#include "Application.h"
#include "PowerUpHolder.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"

PowerUpHolder::PowerUpHolder(int x, int y) : Enemy(x, y)
{
	texturename = App->enemies->someenemies;
	life = 1;
	score = 100;

	walk.PushBack({ 146,158,24,31 });
	walk.PushBack({ 173, 159, 25, 30 });
	walk.PushBack({ 201, 158, 24, 31 });
	walk.PushBack({ 230, 159, 24, 30 });
	walk.PushBack({ 146,189,24,31 });
	walk.PushBack({ 173, 190, 25, 30 });
	walk.PushBack({ 202, 193, 24, 27 });
	walk.PushBack({ 229, 197, 24, 23 });
	walk.PushBack({ 228, 222, 28, 29 });
	walk.speed = 0.075f;
	walk.loop = true;

	fly.PushBack({ 32,161,32,26 });
	fly.PushBack({ 64, 161, 32, 26 });
	fly.PushBack({ 96, 161, 32, 26 });
	fly.PushBack({ 128, 161, 32, 26 });
	fly.speed = 0.075f;
	fly.loop = true;

	animation = &walk;

	collider = App->collision->AddCollider({ 0, 0, 24, 24 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	powerupholderpath.PushBack({ -0.5,0 }, 40, &walk);
	powerupholderpath2.PushBack({ -0.5,-0.5 }, 20, &fly);

	original_y = y;
	original_x = x;
}

void PowerUpHolder::Move()
{
	
	
	if (original_x - position.x <= 20 && animation==&walk)
	{
		position.x = original_x + powerupholderpath.GetCurrentPosition().x;
		position.y = original_y + powerupholderpath.GetCurrentPosition().y;
	}
	else
	{
		if (original_y - position.y < 60)
		{
			position.x = original_x + powerupholderpath2.GetCurrentPosition().x;
		position.y = original_y + powerupholderpath2.GetCurrentPosition().y;
	    }

		else 
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

			position.y = int(float(original_y) + (25.0f * sinf(wave)));
			position.x -= 1;
		}

		if (changeanim == 1)
		{
			animation = &fly;
			changeanim = 0;
			texturename = App->enemies->sprites;
		}
	}


}
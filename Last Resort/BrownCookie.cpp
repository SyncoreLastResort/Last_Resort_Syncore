#include "Application.h"
#include "BrownCookie.h"
#include "ModuleCollision.h"


EnemyBrownCookie::EnemyBrownCookie(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 5,72,21,22 });

	fly.speed = 0.2f;

	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, 24, 24 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);


	browncookiepath.PushBack({ -0.75, -0.5 }, 100, &fly);
	browncookiepath.PushBack({ -0.75, +0.5 }, 100, &fly);
	browncookiepath.PushBack({ -0.75, -0.5 }, 100, &fly);
	browncookiepath.PushBack({ +0.75, +0.5 }, 100, &fly);
	browncookiepath.PushBack({ +0.75, -0.5 }, 100, &fly);
	browncookiepath.PushBack({ +0.75, +0.5 }, 100, &fly);

	original_x = x;
	original_y = y;
}

void EnemyBrownCookie::Move()
{

	position.x = original_x + browncookiepath.GetCurrentPosition().x;
	position.y = original_y + browncookiepath.GetCurrentPosition().y;

}

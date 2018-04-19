#include "ModuleBall.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
ModuleBall::ModuleBall()
{
	ball_0.PushBack({ 195,2, 22, 16 });
};

ModuleBall::~ModuleBall()
{

}

bool ModuleBall::Start()
{
	position = { App->player->position.x + 37, App->player->position.y };
	return true;
}
bool ModuleBall::CleanUp()
{
	return true;
}
update_status ModuleBall::Update()
{
	Move();
	App->render->Blit(App->player->graphics, position.x, position.y, &ball_0.GetCurrentFrame());
	return UPDATE_CONTINUE;
}

void ModuleBall::Move()
{
	uint speed = App->player->speed;
	//Ship goes down  -  ball moves to the sides
	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	{
		if (position.y <= App->player->position.y - 14)
			position.y = App->player->position.y - 14;
		if (position.y != App->player->position.y - 14)
		{
			if (position.x >= App->player->position.x + 16 && position.y <= App->player->position.y - 1)
			{
				position.x -= speed;
			}
			else if (position.x >= App->player->position.x + 16 && position.y > App->player->position.y - 1)
			{
				position.x += speed;
			}
			else if (position.x < App->player->position.x + 16 && position.y <= App->player->position.y - 1)
			{
				position.x += speed;
			}
			else if (position.x < App->player->position.x + 16 && position.y > App->player->position.y - 1)
			{
				position.x -= speed;
			}
		}
	}
	//Ship goes up, ball moves to the sides
	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
	{
		if (position.y >= App->player->position.y + 28)
			position.y = App->player->position.y + 28;
		if (position.y != App->player->position.y + 28)
		{
			if (position.x >= App->player->position.x + 16 && position.y <= App->player->position.y-1)
			{
				position.x += speed;
			}
			else if (position.x >= App->player->position.x + 16 && position.y > App->player->position.y - 1)
			{
				position.x -= speed;
			}
			else if (position.x < App->player->position.x + 16 && position.y <= App->player->position.y - 1)
			{
				position.x -= speed;
			}
			else if (position.x < App->player->position.x + 16 && position.y > App->player->position.y - 1)
			{
				position.x += speed;
			}
		}
		
	}
	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		if (position.x >= App->player->position.x + 37)
			position.x = App->player->position.x + 37;
		if (position.x != App->player->position.x + 37)
		{
			if (position.x >= App->player->position.x + 16 && position.y <= App->player->position.y - 1)
			{
				position.y += speed;
			}
			else if (position.x >= App->player->position.x + 16 && position.y > App->player->position.y - 1)
			{
				position.y -= speed;
			}
			else if (position.x < App->player->position.x + 16 && position.y <= App->player->position.y - 1)
			{
				position.y -= speed;
			}
			else if (position.x < App->player->position.x + 16 && position.y > App->player->position.y - 1)
			{
				position.y += speed;
			}
		}
	}
	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		if (position.x < App->player->position.x - 5)
			position.x = App->player->position.x - 5;
		if (position.x != App->player->position.x - 5)
		{
			if (position.x >= App->player->position.x + 16 && position.y <= App->player->position.y - 1)
			{
				position.y -= speed;
			}
			else if (position.x >= App->player->position.x + 16 && position.y > App->player->position.y - 1)
			{
				position.y += speed;
			}
			else if (position.x < App->player->position.x + 16 && position.y <= App->player->position.y - 1)
			{
				position.y += speed;
			}
			else if (position.x < App->player->position.x + 16 && position.y > App->player->position.y - 1)
			{
				position.y -= speed;
			}
		}
	}

}
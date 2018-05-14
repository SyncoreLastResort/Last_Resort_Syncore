#include "ModuleBall.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
ModuleBall::ModuleBall()
{
	//right
	for (int i=0;i<8;++i)
		blueball_0.PushBack({ 195,2+i*16, 22, 16 });
	blueball_0.speed = 0.2;
	//up & right
	for (int i = 0; i < 8; ++i)
		blueball_45.PushBack({ 240, 2 + i * 22, 21, 21 });
	blueball_45.speed = 0.1;
	//up
	for (int i = 0; i < 8; ++i)
		blueball_90.PushBack({ 278, 2 + i * 22, 16, 22});
	blueball_90.speed = 0.1;
	//up and left
	for (int i = 0; i < 8; ++i)
		blueball_135.PushBack({ 311, 2 + i * 22, 21, 21 });
	blueball_135.speed = 0.1;
	//lwft
	for (int i = 0; i < 8; ++i)
		blueball_180.PushBack({ 354, 2 + i * 16, 22, 16 });
	blueball_180.speed = 0.1;
	//left & downards
	for (int i = 0; i < 8; ++i)
		blueball_225.PushBack({ 398, 2 + i * 22, 21, 21 });
	blueball_225.speed = 0.1;
	//downwards
	for (int i = 0; i < 8; ++i)
		blueball_270.PushBack({ 436, 2 + i * 22, 16, 22 });
	blueball_270.speed = 0.1;

	//downwards & right
	for (int i = 0; i < 8; ++i)
		blueball_315.PushBack({ 469, 2 + i * 22,21, 21 });
	blueball_315.speed = 0.1;

	for (int i = 0; i < 6; ++i)
		blueball_thrown.PushBack({169, 180 +i*26, 26,26});
	blueball_thrown.speed = 0.30;

	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 5; ++j)
			blueball_charging.PushBack({ 230+46*j,45+46*i,46,46 });
	blueball_charging.speed = 0.3;

};

ModuleBall::~ModuleBall()
{

}

bool ModuleBall::Start()
{
	//Initial angle
	angle = 0;

	fix_position = false;
	ball_fixed=false;


	//Load audio
	fix_ball = App->audio->LoadSoundEffect("assets/sounds/011.Death_ball_fix.wav");
	unfix_ball = App->audio->LoadSoundEffect("assets/sounds/012.Death_ball_unfix.wav");
	release_ball_sound = App->audio->LoadSoundEffect("assets/sounds/009.Charged_shot_release.wav");
	charge_ball_sound = App->audio->LoadSoundEffect("assets/sounds/008.Charging_shot.wav");
	
	//Load the texrure
	ball_aditional_effects = App->textures->Load("assets/sprites/Ball_aditional_effects.png");

	//Load colliders
	position = { App->player->position.x +42, App->player->position.y};
	ball1_collider = App->collision->AddCollider({ position.x, position.y, 22, 22 }, COLLIDER_BALL,this);
	current_animation = &blueball_0;
	return true;
}

bool ModuleBall::CleanUp()
{
	
	if (ball1_collider != nullptr)

		ball1_collider->to_delete = true;
	App->textures->Unload(ball_aditional_effects);
	App->audio->UnloadSoundEffect(unfix_ball);
	App->audio->UnloadSoundEffect(fix_ball);
	App->audio->UnloadSoundEffect(release_ball_sound);
	App->audio->UnloadSoundEffect(charge_ball_sound);

	return true;
}

update_status ModuleBall::Update()
{
	laps =int ( angle / (2 * PI));

	if (ball_thrown == false)
	{
		//move the ball
		MoveAround();
		if (App->input->keyboard[SDL_SCANCODE_N] == KEY_STATE::KEY_REPEAT)
			aim_angle += 6;

		if (App->input->keyboard[SDL_SCANCODE_M] == KEY_STATE::KEY_DOWN) //We fix/unfix the ball
		{
			if (fix_position)
				App->audio->PlaySoundEffect(unfix_ball);
			
			if(!fix_position)
				App->audio->PlaySoundEffect(fix_ball);
			
			fix_position = !fix_position;
			
			ball_fixed = false;
		}
		

		if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_REPEAT)
			ChargeBall();

		if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_UP)
		{
			charge_time = 0;
			ReleaseBall();
		}
		if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
		{
			charge_time = SDL_GetTicks();
			Shoot();
		}
	}

	if (ball_thrown == true)
	{
		Trail();
		current_animation = &blueball_thrown;
		if (back_to_player == false)
		{
			Path();
		}
		else if (back_to_player == true)
		{
			ReturnBall();
		}
	}
	

	ball1_collider->SetPos(position.x, position.y);
	
	App->render->Blit_rotate(App->player->graphics, position, 22, 16, &current_animation->GetCurrentFrame(),ball_center, aim_angle);
	
	return UPDATE_CONTINUE;
}

void ModuleBall::MoveAround()
{

	if (ball_fixed == false) //If the ball is fixed, it will stop rotating around the ship
	{
		if (App->player->going_up && App->player->going_left)
		{
			if ((SDL_sin(angle) <= sqrt(2) / 2 - 0.1 || SDL_sin(angle) >= sqrt(2) / 2 + 0.1) || (SDL_cos(angle) <= sqrt(2) / 2 - 0.1 || SDL_cos(angle) >= sqrt(2) / 2 + 0.1)) //Bottom right 
			{
				if (SDL_sin(angle) < -sqrt(2) / 2 || cos(angle) > sqrt(2) / 2)
					angle += rotation_speed;
				else
					angle -= rotation_speed;
			}
		}

		else if (App->player->going_up && App->player->going_right)
		{
			if ((SDL_sin(angle) <= sqrt(2) / 2 - 0.1 || SDL_sin(angle) >= sqrt(2) / 2 + 0.1) || (SDL_cos(angle) <= -sqrt(2) / 2 - 0.1 || SDL_cos(angle) >= -sqrt(2) / 2 + 0.1))
			{
				if (SDL_sin(angle) < -sqrt(2) / 2 || cos(angle) < -sqrt(2) / 2)
					angle -= rotation_speed;
				else
					angle += rotation_speed;
			}
		}

		else if (App->player->going_down && App->player->going_right)
		{
			if ((SDL_sin(angle) <= -sqrt(2) / 2 - 0.1 || SDL_sin(angle) >= -sqrt(2) / 2 + 0.1) || (SDL_cos(angle) <= -sqrt(2) / 2 - 0.1 || SDL_cos(angle) >= -sqrt(2) / 2 + 0.1))
			{
				if (SDL_sin(angle) > sqrt(2) / 2 || cos(angle) < -sqrt(2) / 2)
					angle += rotation_speed;
				else
					angle -= rotation_speed;
			}
		}

		else if (App->player->going_down && App->player->going_left)
		{
			if ((SDL_sin(angle) <= -sqrt(2) / 2 - 0.1 || SDL_sin(angle) >= -sqrt(2) / 2 + 0.1) || (SDL_cos(angle) <= sqrt(2) / 2 - 0.1 || SDL_cos(angle) >= sqrt(2) / 2 + 0.1))
			{
				if (SDL_sin(angle) > sqrt(2) / 2 || cos(angle) > sqrt(2) / 2)
					angle -= rotation_speed;
				else
					angle += rotation_speed;
			}
		}

		else if (App->player->going_up)
		{
			if (SDL_sin(angle) < 0.999) // When the ball gets to the lowest position - The sin of the angle never gets to 1, so we try to get as close as posible
			{
				if (position.x + 8 > App->player->position.x + 16)
					angle += rotation_speed;

				else if (position.x + 8 <= App->player->position.x + 16)
					angle -= rotation_speed;
			}

		}

		else if (App->player->going_down)
		{
			if (SDL_sin(angle) > -0.999)// When the ball gets to the highest position - The sin of the angle never gets to 1, so we try to get as close as posible
			{
				if (position.x + 8 >= App->player->position.x + 14)
					angle -= rotation_speed;

				else if (position.x + 8 < App->player->position.x + 14)
					angle += rotation_speed;
			}
		}

		else if (App->player->going_left)
		{
			if (SDL_cos(angle) < 0.999)// When the ball gets to the right - The cos of the angle never gets to 1, so we try to get as close as posible
			{
				if (position.y + 8 < App->player->position.y + 7)
					angle += rotation_speed;

				else if (position.y + 8 >= App->player->position.y + 7)
					angle -= rotation_speed;
			}

		}

		else if (App->player->going_right)
		{
			if (SDL_cos(angle) > -0.999)// When the ball gets to the left - The cos of the angle never gets to 1, so we try to get as close as posible
			{
				if (position.y + 8 >= App->player->position.y + 11)
					angle += rotation_speed;
				if (position.y + 8 < App->player->position.y + 11)
					angle -= rotation_speed;
			}
		}

		if (fix_position == true)
		{
			//We fix the ball at the spots we want to
			if ((SDL_sin(angle) >= sqrt(2) / 2 - 0.1 && SDL_sin(angle) <= sqrt(2) / 2 + 0.1)) //bottom corners
				ball_fixed = true;

			if ((SDL_sin(angle) >= -sqrt(2) / 2 - 0.1 && SDL_sin(angle) <= -sqrt(2) / 2 + 0.1)) // top corners 
				ball_fixed = true;
		
			if (SDL_sin(angle) < 0.05 && SDL_sin(angle) > -0.01) //sides
				ball_fixed = true;

			if (SDL_cos(angle) < 0.05 && SDL_cos(angle) > -0.05) // top or bottom
				ball_fixed = true;
		}
	}
	
	//Define the position of the ball depending on the angle
	position.x = App->player->position.x + radius * SDL_cos(angle) + 8;
	position.y = App->player->position.y + 1 + radius * SDL_sin(angle);
}



void ModuleBall::ChargeBall()
{
	charge_ball_sound->volume = 128;
	charge+=2;
	if (charge > 80)
		shot_charged = true;
	if (SDL_GetTicks() - charge_time > 200)
	{
		if (charge>=20&&charge<=26)
			App->audio->PlaySoundEffect(charge_ball_sound);

		if (current_animation == &blueball_0)
			App->render->Blit(ball_aditional_effects, position.x - 15, position.y - 15, &blueball_charging.GetCurrentFrame());

		if (current_animation == &blueball_45)
			App->render->Blit(ball_aditional_effects, position.x - 15, position.y - 10, &blueball_charging.GetCurrentFrame());

		if (current_animation == &blueball_90)
			App->render->Blit(ball_aditional_effects, position.x - 15, position.y - 9, &blueball_charging.GetCurrentFrame());

		if (current_animation == &blueball_135)
			App->render->Blit(ball_aditional_effects, position.x - 10, position.y - 10, &blueball_charging.GetCurrentFrame());

		if (current_animation == &blueball_180)
			App->render->Blit(ball_aditional_effects, position.x - 9, position.y - 15, &blueball_charging.GetCurrentFrame());

		if (current_animation == &blueball_225)
			App->render->Blit(ball_aditional_effects, position.x - 10, position.y - 15, &blueball_charging.GetCurrentFrame());

		if (current_animation == &blueball_270)
			App->render->Blit(ball_aditional_effects, position.x - 15, position.y - 15, &blueball_charging.GetCurrentFrame());

		if (current_animation == &blueball_315)
			App->render->Blit(ball_aditional_effects, position.x - 15, position.y - 15, &blueball_charging.GetCurrentFrame());
	}
	


}

void ModuleBall::ReleaseBall()
{
	charge_ball_sound->volume = 0;
	blueball_charging.Reset();
	if (!shot_charged)
		charge = 0;
	if (shot_charged)
	{
		shot_charged = false;
		App->audio->PlaySoundEffect(release_ball_sound);
		if (getPosition() == RIGHT_SIDE)
		{
			velocity = { 8,0 };
		}
		if (getPosition() == RIGHT_TOP)
		{
			velocity = { 6,-6 };
		}
		if (getPosition() == RIGHT_BOTTOM)
		{
			velocity = { 6,6 };
		}
		if (getPosition() == LEFT_SIDE)
		{
			velocity = { -8,0 };
		}
		if (getPosition() == LEFT_TOP)
		{
			velocity = { -8,-6 };
		}
		if (getPosition() == LEFT_BOTTOM)
		{
			velocity = { -8,6 };
		}
		if (getPosition() == BOTTOM)
		{
			velocity = {0 ,8 };
		}
		if (getPosition() == TOP)
		{
			velocity = { 0,-8 };
		}
		ball_thrown = true;
	}
	
}

void ModuleBall::Path()
{
	position += velocity;
	if (abs(position.x-App->player->position.x)>=300|| abs(position.y - App->player->position.y) >= 300)
		back_to_player = true;
}

void ModuleBall::ReturnBall()
{
	if (position.x > App->player->position.x + 24)
		position.x -= 5;
	else if (position.x < App->player->position.x + 8)
		position.x += 5;

	if (position.y > App->player->position.y + 14)
		position.y -= 5;

	else if (position.y < App->player->position.y - 16)
		position.y += 5;

	if (position.x <= App->player->position.x + 42 && position.x >= App->player->position.x - 26 && position.y >= App->player->position.y - 35 && position.y <= App->player->position.y + 35)
	{
		back_to_player = false;
		ball_thrown = false;
		charge = 0;
	}
}

BALL_POSITION ModuleBall::getPosition()
{
	BALL_POSITION ret = NONE;
	if (position.x < App->player->position.x + 15 && position.x >= App->player->position.x - 10 &&position.y < App->player->position.y - 1 && position.y > App->player->position.y - 25)
		ret = LEFT_TOP;
	
	else if (position.x < App->player->position.x + 10 && position.x >= App->player->position.x - 10 && position.y>App->player->position.y - 1 && position.y < App->player->position.y + 25)
		ret = LEFT_BOTTOM;
	
	else if (position.x <= App->player->position.x - 10)
		ret = LEFT_SIDE;
	
	else if (position.x >= App->player->position.x + 15 && position.y < App->player->position.y - 1&& position.y > App->player->position.y - 25&& position.x < App->player->position.x + 41)
		ret = RIGHT_TOP;
	
	else if (position.x >= App->player->position.x + 10 && position.y > App->player->position.y - 1 && position.y < App->player->position.y + 25 && position.x < App->player->position.x + 41)
		ret = RIGHT_BOTTOM;
	
	else if (position.x >= App->player->position.x + 41)
		ret = RIGHT_SIDE;
	
	else if (position.y <= App->player->position.y - 25)
		ret = TOP;
	
	else if (position.y >= App->player->position.y + 25)
		ret = BOTTOM;

	return ret;
}

void ModuleBall::Shoot()
{
	if (current_animation == &blueball_0)
		App->particles->ball_shot.speed = { 7,0 };
	
	else if (current_animation == &blueball_45)
		App->particles->ball_shot.speed = { 5,-5 };
	
	else if (current_animation == &blueball_90)
		App->particles->ball_shot.speed = { 0,-7 };
	
	else if (current_animation == &blueball_135)
		App->particles->ball_shot.speed = { -5,-5 };
	
	else if (current_animation == &blueball_180)
		App->particles->ball_shot.speed = { -7,0 };
	
	else if (current_animation == &blueball_225)
		App->particles->ball_shot.speed = { -5,5 };
	
	else if (current_animation == &blueball_270)
		App->particles->ball_shot.speed = { 0,7 };
	
	else if (current_animation == &blueball_315)
		App->particles->ball_shot.speed = { 5,5 };
	
	App->particles->AddParticle(App->particles->ball_shot, position.x, position.y, COLLIDER_PLAYER_SHOT);
}

void ModuleBall::Trail()
{
	if (SDL_GetTicks()%80>=0&& SDL_GetTicks() % 80 <= 20)
		App->particles->AddParticle(App->particles->ball_trail, position.x - 6, position.y - 6);
}

void ModuleBall::OnCollision(Collider* c1, Collider* c2) 
{
	if (ball_thrown == true) 
	{
		if (c1->type == COLLIDER_WALL || c2->type == COLLIDER_WALL || c1->type == COLLIDER_BOSS || c2->type == COLLIDER_BOSS)
		{
			back_to_player = true;
		}
		if (c1->type == COLLIDER_ENEMY || c2->type == COLLIDER_ENEMY )
		{
			if (charge < 200)
				back_to_player = true;
		}
	}

}
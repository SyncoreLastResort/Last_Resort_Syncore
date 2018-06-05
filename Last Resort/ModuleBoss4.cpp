#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "SDL/include/SDL_timer.h"
#include "ModuleBall.h"
#include "ModulePlayer2.h"
#include "ModuleBoss4.h"
#include "ModuleInput.h"

ModuleBoss4::ModuleBoss4()
{
	//Rectangles of the parts
	head = { 62,156,64,34 };
	body_module = {1,187,30, 16};
	bottom = { 126, 157,56 ,32 };
	core = {182,157,46,32};
	core_leftcannon = { 0,219,16,16 };
	core_rightcannon = { 0,203,16,16 };
	module_leftcannon = { 16,219,16,16 };
	module_rightcannon = { 16,203,16,16 };
}

ModuleBoss4::~ModuleBoss4() {};

bool ModuleBoss4::Start()
{
	//HP
	rightcore_hp = 60;
	leftcore_hp = 60;

	module1_cannonright_alive = true;
	module1_cannonleft_alive = true;
	module2_cannonright_alive = true;
	module2_cannonleft_alive = true;
	module3_cannonright_alive = true;
	module3_cannonleft_alive = true;
	module4_cannonright_alive = true;
	module4_cannonleft_alive = true;
	core_cannonright_alive =true;
	core_cannonleft_alive = true;

	//Initial positions
	core_position.x = 5200;
	core_position.y = 100;
	module1_position.x = core_position.x + 8;
	module1_position.y = core_position.y + 8;
	module2_position = module3_position = module4_position = module1_position;
	head_position.x = core_position.x - 9;
	head_position.y = core_position.y - 11;
	bottom_position.x = core_position.x - 5;
	bottom_position.y = core_position.y+5;

	//Colliders
	core_collider = App->collision->AddCollider({ core_position.x,core_position.y,46,32 }, COLLIDER_BOSS, this);
	head_collider= App->collision->AddCollider({ head_position.x,core_position.y,64,34 }, COLLIDER_BOSS);
	bottom_collider = App->collision->AddCollider({ bottom_position.x, bottom_position.y, 56,32 }, COLLIDER_BOSS);
	module1_collider = App->collision->AddCollider({ module1_position.x, module1_position.y, 30,16 }, COLLIDER_BOSS, this);
	module2_collider= App->collision->AddCollider({ module2_position.x, module2_position.y, 30,16 }, COLLIDER_BOSS, this);
	module3_collider= App->collision->AddCollider({ module3_position.x, module3_position.y, 30,16 }, COLLIDER_BOSS, this);
	module4_collider= App->collision->AddCollider({ module4_position.x, module4_position.y, 30,16 }, COLLIDER_BOSS, this);
	module1_leftcannon_collider = App->collision->AddCollider({ module1_leftcannon_position.x,module1_leftcannon_position.y, 16,16 }, COLLIDER_BOSS, this);
	module1_rightcannon_collider = App->collision->AddCollider({ module1_rightcannon_position.x,module1_rightcannon_position.y, 16,16 }, COLLIDER_BOSS, this);
	module2_leftcannon_collider = App->collision->AddCollider({ module2_leftcannon_position.x,module2_leftcannon_position.y, 16,16 }, COLLIDER_BOSS, this);
	module2_rightcannon_collider = App->collision->AddCollider({ module2_rightcannon_position.x,module2_rightcannon_position.y, 16,16 }, COLLIDER_BOSS, this);
	module3_leftcannon_collider = App->collision->AddCollider({ module3_leftcannon_position.x,module3_leftcannon_position.y, 16,16 }, COLLIDER_BOSS, this);
	module3_rightcannon_collider = App->collision->AddCollider({ module3_rightcannon_position.x,module3_rightcannon_position.y, 16,16 }, COLLIDER_BOSS, this);
	module4_leftcannon_collider = App->collision->AddCollider({ module4_leftcannon_position.x,module4_leftcannon_position.y, 16,16 }, COLLIDER_BOSS, this);
	module4_rightcannon_collider = App->collision->AddCollider({ module4_rightcannon_position.x,module4_rightcannon_position.y, 16,16 }, COLLIDER_BOSS, this);
	core_rightcannon_collider = App->collision->AddCollider({core_rightcannon_position.x,core_rightcannon_position.y,16,16 },COLLIDER_BOSS, this);
	core_leftcannon_collider = App->collision->AddCollider({ core_leftcannon_position.x,core_leftcannon_position.y,16,16 }, COLLIDER_BOSS, this);

	//Load the texture
	boss_textures = App->textures->Load("assets/sprites/Boss4_sprites.png");
	
	rightcore_hp = 50;
	leftcore_hp = 50;

	boss4_dead = false;
	closed = true;
	opening = false;
	open = false;
	closing = false;

	move_right = true;
	move_right = false;
	return true;
}

bool ModuleBoss4::CleanUp() 
{
	App->textures->Unload(boss_textures);

	//     DELETE COLLIDERS
	if (core_collider != nullptr)
		core_collider->to_delete=true;

	if (head_collider != nullptr)
		head_collider->to_delete = true;

	if (bottom_collider != nullptr)
		bottom_collider->to_delete = true;

	if (module1_collider != nullptr)
		module1_collider->to_delete = true;

	if (module2_collider != nullptr)
		module2_collider->to_delete = true;

	if (module3_collider != nullptr)
		module3_collider->to_delete = true;

	if (module4_collider != nullptr)
		module4_collider->to_delete = true;


	
	return true;
}

update_status ModuleBoss4::Update()
{
	module1_position.x = module2_position.x = module3_position.x = module4_position.x = core_position.x + 8;
	bottom_position.x = core_position.x - 5;
	head_position.x = core_position.x - 9;



	if (App->input->keyboard[SDL_SCANCODE_J] == KEY_REPEAT)
		core_position.x++;
		
	if (App->player->position.x > 5000 || App->player2->position.x > 5000)
	{
		if (closed)
			Move();

		if (closing)
			Close();

		if (opening)
			Open();
		
		if (open)
		{
			open_timer++;
			if (open_timer == 100)
				Shot1();

			if (open_timer == 350)
				Shot2();

			if (open_timer == 500)
				Shot2();

			if (open_timer > 600)
				closing = true;
		}
		





	}


	//	~~~~~~~~~~~~BLITS~~~~~~~~~~
	App->render->Blit(boss_textures, module1_position.x, module1_position.y, &body_module);
	App->render->Blit(boss_textures, module2_position.x, module2_position.y, &body_module);
	App->render->Blit(boss_textures, module3_position.x, module3_position.y, &body_module);
	App->render->Blit(boss_textures, module4_position.x, module4_position.y, &body_module);

	

	if (module1_cannonleft_alive)
	{
		module1_leftcannon_position.x = module1_position.x - 4;
		module1_leftcannon_position.y = module1_position.y;
		App->render->Blit(boss_textures, module1_leftcannon_position.x, module1_leftcannon_position.y, &module_leftcannon);
	}

	if (module1_cannonright_alive)
	{
		module1_rightcannon_position.x = module1_position.x + 18;
		module1_rightcannon_position.y = module1_position.y;
		App->render->Blit(boss_textures, module1_rightcannon_position.x, module1_rightcannon_position.y, &module_rightcannon);
	}

	if (module2_cannonright_alive)
	{
		module2_rightcannon_position.x = module2_position.x + 18;
		module2_rightcannon_position.y = module2_position.y;
		App->render->Blit(boss_textures, module2_rightcannon_position.x, module2_rightcannon_position.y, &module_rightcannon);
	}

	if (module2_cannonleft_alive)
	{
		module2_leftcannon_position.x = module2_position.x - 4;
		module2_leftcannon_position.y = module2_position.y;
		App->render->Blit(boss_textures, module2_leftcannon_position.x, module2_leftcannon_position.y, &module_leftcannon);
	}

	if (module3_cannonright_alive)
	{
		module3_rightcannon_position.x = module3_position.x + 18;
		module3_rightcannon_position.y = module3_position.y;
		App->render->Blit(boss_textures, module3_rightcannon_position.x, module3_rightcannon_position.y, &module_rightcannon);
	}

	if (module3_cannonleft_alive)
	{
		module3_leftcannon_position.x = module3_position.x - 4;
		module3_leftcannon_position.y = module3_position.y;
		App->render->Blit(boss_textures, module3_leftcannon_position.x, module3_leftcannon_position.y, &module_leftcannon);
	}

	if (module4_cannonright_alive)
	{
		module4_rightcannon_position.x = module4_position.x + 18;
		module4_rightcannon_position.y = module4_position.y;
		App->render->Blit(boss_textures, module4_rightcannon_position.x, module4_rightcannon_position.y, &module_rightcannon);
	}

	if (module4_cannonleft_alive)
	{
		module4_leftcannon_position.x = module4_position.x - 4;
		module4_leftcannon_position.y = module4_position.y;
		App->render->Blit(boss_textures, module4_leftcannon_position.x, module4_leftcannon_position.y, &module_leftcannon);
	}

	// WEAPONS && BLITS
	if (core_cannonleft_alive)
	{
		core_leftcannon_position.x = core_position.x - 2;
		core_leftcannon_position.y = core_position.y + 8;
		App->render->Blit(boss_textures, core_leftcannon_position.x, core_leftcannon_position.y, &core_leftcannon);
	}

	if (core_cannonright_alive)
	{
		core_rightcannon_position.x = core_position.x + 31;
		core_rightcannon_position.y = core_position.y + 8;
		App->render->Blit(boss_textures, core_rightcannon_position.x, core_rightcannon_position.y, &core_rightcannon);
	}
	
	
	App->render->Blit(boss_textures, core_position.x, core_position.y, &core);
	App->render->Blit(boss_textures, bottom_position.x, bottom_position.y, &bottom);
	App->render->Blit(boss_textures, head_position.x, head_position.y, &head);

	//Update colliders
	core_collider->SetPos(core_position.x, core_position.y);
	head_collider->SetPos(head_position.x, head_position.y);
	bottom_collider->SetPos(bottom_position.x, bottom_position.y);
	module1_collider->SetPos(module1_position.x, module1_position.y);
	module2_collider->SetPos(module2_position.x, module2_position.y);
	module3_collider->SetPos(module3_position.x, module3_position.y);
	module4_collider->SetPos(module4_position.x, module4_position.y);
	
	module1_leftcannon_collider->SetPos(module1_leftcannon_position.x, module1_leftcannon_position.y);
	module1_rightcannon_collider->SetPos(module1_rightcannon_position.x, module1_rightcannon_position.y);

	module2_leftcannon_collider->SetPos(module2_leftcannon_position.x, module2_leftcannon_position.y);
	module2_rightcannon_collider->SetPos(module2_rightcannon_position.x, module2_rightcannon_position.y);

	module3_leftcannon_collider->SetPos(module3_leftcannon_position.x, module3_leftcannon_position.y);
	module3_rightcannon_collider->SetPos(module3_rightcannon_position.x, module3_rightcannon_position.y);

	module4_leftcannon_collider->SetPos(module4_leftcannon_position.x, module4_leftcannon_position.y);
	module4_rightcannon_collider->SetPos(module4_rightcannon_position.x, module4_rightcannon_position.y);

	core_leftcannon_collider->SetPos(core_leftcannon_position.x, core_leftcannon_position.y);
	core_rightcannon_collider->SetPos(core_rightcannon_position.x, core_rightcannon_position.y);

	return UPDATE_CONTINUE;
}

void ModuleBoss4::Open()
{
	closed = false;
	closing = false;
	if (head_position.y>core_position.y-64)
	{
		head_position.y -= 1;

		if (module1_position.y > module2_position.y - 16)
			module1_position.y -= 1;

		if (module2_position.y > core_position.y - 16)
			module2_position.y -= 1; 
	}

	if (bottom_position.y < core_position.y + 64)
	{
		bottom_position.y += 1;

		if (module3_position.y < core_position.y + 32)
			module3_position.y += 1;
	
		if (module4_position.y < module3_position.y + 16)
			module4_position.y += 1;
	}

	if (head_position.y <= core_position.y - 64 && bottom_position.y >= core_position.y + 64)
	{
		open = true;
		opening = false;
		open_timer = 0;
	}

}

void ModuleBoss4::Close()
{
	open = false;
	opening = false;

	if (head_position.y < core_position.y - 11)
	{
		head_position.y += 2;

		if (head_position.y >= core_position.y - 41)
		{
			module1_position.y += 2;
		}
		if (head_position.y >= core_position.y - 25)
		{
			module2_position.y += 2;
		}
	}

	if (bottom_position.y > core_position.y+5)
	{
		bottom_position.y -= 2;

		if (bottom_position.y <= core_position.y + 48)
			module4_position.y -= 2;

		if (bottom_position.y <= core_position.y + 32)
			module3_position.y -= 2;
	}

	if (head_position.y >= core_position.y - 11 && bottom_position.y <= core_position.y + 5)
	{
		closed = true;
		closing = false;
	}
	
}

void ModuleBoss4::Shot1()
{
	if (core_cannonleft_alive)
	{
		App->particles->AddParticle(App->particles->boss4_small_shot, core_position.x, core_position.y, COLLIDER_ENEMY_SHOT, 0, nullptr, { -1,2 });
		App->particles->AddParticle(App->particles->boss4_small_shot, core_position.x, core_position.y, COLLIDER_ENEMY_SHOT, 0, nullptr, { -1,-1 });
		App->particles->AddParticle(App->particles->boss4_small_shot, core_position.x, core_position.y, COLLIDER_ENEMY_SHOT, 0, nullptr, { -1,0 });
		App->particles->AddParticle(App->particles->boss4_small_shot, core_position.x, core_position.y, COLLIDER_ENEMY_SHOT, 0, nullptr, { -1,2 });
		App->particles->AddParticle(App->particles->boss4_small_shot, core_position.x, core_position.y, COLLIDER_ENEMY_SHOT, 0, nullptr, { -1,1 });
	}
	if (core_cannonright_alive)
	{
		App->particles->AddParticle(App->particles->boss4_small_shot, core_position.x, core_position.y, COLLIDER_ENEMY_SHOT, 0, nullptr, { 1,-2 });
		App->particles->AddParticle(App->particles->boss4_small_shot, core_position.x, core_position.y, COLLIDER_ENEMY_SHOT, 0, nullptr, { 1,-1 });
		App->particles->AddParticle(App->particles->boss4_small_shot, core_position.x, core_position.y, COLLIDER_ENEMY_SHOT, 0, nullptr, { 1,0 });
		App->particles->AddParticle(App->particles->boss4_small_shot, core_position.x, core_position.y, COLLIDER_ENEMY_SHOT, 0, nullptr, { 1,2 });
		App->particles->AddParticle(App->particles->boss4_small_shot, core_position.x, core_position.y, COLLIDER_ENEMY_SHOT, 0, nullptr, { 1,1 });
	}
}

void ModuleBoss4::Shot2()
{
	if (module1_cannonleft_alive)
		App->particles->AddParticle(App->particles->boss4_heat_ball, module1_leftcannon_position.x, module1_leftcannon_position.y, COLLIDER_ENEMY_SHOT, 0, nullptr, { -2,0 });
	
	if (module1_cannonright_alive)
		App->particles->AddParticle(App->particles->boss4_heat_ball, module1_rightcannon_position.x, module1_rightcannon_position.y, COLLIDER_ENEMY_SHOT, 0, nullptr, { 2,0 });

	if (module2_cannonleft_alive)
		App->particles->AddParticle(App->particles->boss4_heat_ball, module2_leftcannon_position.x, module2_leftcannon_position.y, COLLIDER_ENEMY_SHOT, 0, nullptr, { -2,0 });

	if (module2_cannonright_alive)
		App->particles->AddParticle(App->particles->boss4_heat_ball, module2_rightcannon_position.x, module2_rightcannon_position.y, COLLIDER_ENEMY_SHOT, 0, nullptr, { 2,0 });

	if (module3_cannonleft_alive)
		App->particles->AddParticle(App->particles->boss4_heat_ball, module3_leftcannon_position.x, module3_leftcannon_position.y, COLLIDER_ENEMY_SHOT, 0, nullptr, { -2,0 });

	if (module3_cannonright_alive)
		App->particles->AddParticle(App->particles->boss4_heat_ball, module3_rightcannon_position.x, module3_rightcannon_position.y, COLLIDER_ENEMY_SHOT, 0, nullptr, { 2,0 });

	if (module4_cannonleft_alive)
		App->particles->AddParticle(App->particles->boss4_heat_ball, module4_leftcannon_position.x, module4_leftcannon_position.y, COLLIDER_ENEMY_SHOT, 0, nullptr, { -2,0 });

	if (module4_cannonright_alive)
		App->particles->AddParticle(App->particles->boss4_heat_ball, module4_rightcannon_position.x, module4_rightcannon_position.y, COLLIDER_ENEMY_SHOT, 0, nullptr, { 2,0 });
}

void ModuleBoss4::Shot3()
{
	App->particles->AddParticle(App->particles->boss4_blue_circle, bottom_position.x+28, bottom_position.y+16, COLLIDER_ENEMY_SHOT, 0, nullptr, { -1,0 });
	App->particles->AddParticle(App->particles->boss4_blue_circle, bottom_position.x + 28, bottom_position.y+16, COLLIDER_ENEMY_SHOT, 0, nullptr, { -1,-1 });
	App->particles->AddParticle(App->particles->boss4_blue_circle, bottom_position.x + 28, bottom_position.y+16, COLLIDER_ENEMY_SHOT, 0, nullptr, { -1,1 });
	App->particles->AddParticle(App->particles->boss4_blue_circle, bottom_position.x + 28, bottom_position.y+16, COLLIDER_ENEMY_SHOT, 0, nullptr, { 1,0 });
	App->particles->AddParticle(App->particles->boss4_blue_circle, bottom_position.x + 28, bottom_position.y + 16, COLLIDER_ENEMY_SHOT, 0, nullptr, { 1,-1 });
	App->particles->AddParticle(App->particles->boss4_blue_circle, bottom_position.x + 28, bottom_position.y + 16, COLLIDER_ENEMY_SHOT, 0, nullptr, { 1,1 });
}

void ModuleBoss4::Move()
{

	if (move_right)
		core_position.x+=2;

	else if (move_left)
		core_position.x -= 2;
	
	move_timer += 2;
	if (move_timer >= 500)
	{
		move_right = !move_right;
		move_left = !move_left;
		move_timer = 2;
		opening = true;
	}

}

void ModuleBoss4::OnCollision(Collider* col_1, Collider* col_2)
{
	if (col_1 == module1_leftcannon_collider || col_2 == module1_leftcannon_collider)
	{
		App->particles->AddParticle(App->particles->enemy_explosion, module1_leftcannon_position.x, module1_leftcannon_position.y);
		module1_cannonleft_alive = false;
		module1_leftcannon_collider->to_delete=true;
	}

	if (col_1 == module1_rightcannon_collider || col_2 == module1_rightcannon_collider)
	{
		App->particles->AddParticle(App->particles->enemy_explosion, module1_rightcannon_position.x, module1_rightcannon_position.y);
		module1_cannonright_alive = false;
		module1_rightcannon_collider->to_delete = true;
	}

	if (col_1 == module2_leftcannon_collider || col_2 == module2_leftcannon_collider)
	{
		App->particles->AddParticle(App->particles->enemy_explosion, module2_leftcannon_position.x, module2_leftcannon_position.y);
		module2_cannonleft_alive = false;
		module2_leftcannon_collider->to_delete = true;
	}

	if (col_1 == module2_rightcannon_collider || col_2 == module2_rightcannon_collider)
	{
		App->particles->AddParticle(App->particles->enemy_explosion, module2_rightcannon_position.x, module2_rightcannon_position.y);
		module2_cannonright_alive = false;
		module2_rightcannon_collider->to_delete = true;
	}

	if (col_1 == module3_leftcannon_collider || col_2 == module3_leftcannon_collider)
	{
		App->particles->AddParticle(App->particles->enemy_explosion, module3_leftcannon_position.x, module3_leftcannon_position.y);
		module3_cannonleft_alive = false;
		module3_leftcannon_collider->to_delete = true;
	}

	if (col_1 == module3_rightcannon_collider || col_2 == module3_rightcannon_collider)
	{
		App->particles->AddParticle(App->particles->enemy_explosion, module3_rightcannon_position.x, module3_rightcannon_position.y);
		module3_cannonright_alive = false;
		module3_rightcannon_collider->to_delete = true;
	}

	if (col_1 == module4_leftcannon_collider || col_2 == module4_leftcannon_collider)
	{
		App->particles->AddParticle(App->particles->enemy_explosion, module4_leftcannon_position.x, module4_leftcannon_position.y);
		module4_cannonleft_alive = false;
		module4_leftcannon_collider->to_delete = true;
	}

	if (col_1 == module4_rightcannon_collider || col_2 == module4_rightcannon_collider)
	{
		App->particles->AddParticle(App->particles->enemy_explosion, module4_rightcannon_position.x, module4_rightcannon_position.y);
		module4_cannonright_alive = false;
		module4_rightcannon_collider->to_delete = true;
	}

	if (col_1 == core_leftcannon_collider|| col_2 == core_leftcannon_collider)
	{
		leftcore_hp--;
		if (leftcore_hp < 1)
		{
			App->particles->AddParticle(App->particles->enemy_explosion, core_leftcannon_position.x, core_leftcannon_position.y);
			core_cannonleft_alive = false;
			core_leftcannon_collider->to_delete = true;
		}
	}

	if (col_1 == core_rightcannon_collider || col_2 == core_rightcannon_collider)
	{
		rightcore_hp--;
		if (rightcore_hp < 1)
		{
			App->particles->AddParticle(App->particles->enemy_explosion, core_rightcannon_position.x, core_rightcannon_position.y);
			core_cannonright_alive = false;
			core_rightcannon_collider->to_delete = true;
		}
	}
	
	if (rightcore_hp < 1 && leftcore_hp < 1)
		boss4_dead = true;
}
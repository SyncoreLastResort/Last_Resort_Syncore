#ifndef __ModuleBoss4_H__
#define __ModuleBoss4_H__


#include "Module.h"


class ModuleBoss4 : public Module
{
public:
	ModuleBoss4();
	~ModuleBoss4();


	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* col_1, Collider* col_2) override;
	
	
	void Open();
	void Close();
	void Shot1();
	void Shot2();
	void Shot3();


public:

private:
	int rightcore_hp;
	int leftcore_hp;
	//Bools
	bool open;
	bool opening;
	bool closing;
	bool closed;

	//Beapon booleans
	bool module1_cannonright_alive;
	bool module1_cannonleft_alive;
	bool module2_cannonright_alive;
	bool module2_cannonleft_alive;
	bool module3_cannonright_alive;
	bool module3_cannonleft_alive;
	bool module4_cannonright_alive;
	bool module4_cannonleft_alive;
	bool core_cannonright_alive;
	bool core_cannonleft_alive;

	//Position of the parts
	iPoint core_position;
	iPoint module1_position;//above the core
	iPoint module2_position;//above the core
	iPoint module3_position;//below the core
	iPoint module4_position;//below the core
	iPoint head_position;
	iPoint bottom_position;

	iPoint core_leftcannon_position;
	iPoint core_rightcannon_position;
	iPoint module1_leftcannon_position;
	iPoint module1_rightcannon_position;
	iPoint module2_leftcannon_position;
	iPoint module2_rightcannon_position;
	iPoint module3_rightcannon_position;
	iPoint module3_leftcannon_position;
	iPoint module4_rightcannon_position;
	iPoint module4_leftcannon_position;
	
	//Frames of the parts
	SDL_Rect head;
	SDL_Rect body_module;
	SDL_Rect bottom;
	SDL_Rect core;
	SDL_Rect module_leftcannon;
	SDL_Rect module_rightcannon;
	SDL_Rect core_leftcannon;
	SDL_Rect core_rightcannon;

	//Colliders
	Collider* head_collider;
	Collider *module1_collider;
	Collider *module2_collider;
	Collider *module3_collider;
	Collider *module4_collider;
	Collider *core_collider;
	Collider *bottom_collider;

	Collider* module1_leftcannon_collider;
	Collider* module1_rightcannon_collider;

	Collider* module2_leftcannon_collider;
	Collider* module2_rightcannon_collider;

	Collider* module3_leftcannon_collider;
	Collider* module3_rightcannon_collider;

	Collider* module4_leftcannon_collider;
	Collider* module4_rightcannon_collider;

	Collider* core_leftcannon_collider;
	Collider* core_rightcannon_collider;

	//Textures
	SDL_Texture* boss_textures;


};

#endif
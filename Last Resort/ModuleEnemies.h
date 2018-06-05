#ifndef __ModuleEnemies_H__
#define __ModuleEnemies_H__

#include "Module.h"


#define MAX_ENEMIES 150



enum ENEMY_TYPES
{
	NO_TYPE,
	Power_Up_Holder,
	RHINO,
	POWER_UP,
	POWER_UP_BOMB,
	RedBird,
	TrackingBee,
	Spider,
	CannonPlatf
};

class Enemy;

struct EnemyInfo
{
	ENEMY_TYPES type = ENEMY_TYPES::NO_TYPE;
	int x, y; 
};

class ModuleEnemies : public Module
{
public:

	ModuleEnemies();
	~ModuleEnemies();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	bool AddEnemy(ENEMY_TYPES type, int x, int y);

	SDL_Texture* sprites = nullptr;
	SDL_Texture* someenemies = nullptr;
	SDL_Texture* trackingbee = nullptr;
	SDL_Texture* spider = nullptr;
	SDL_Texture* cannonplatform = nullptr;

private:

	void SpawnEnemy(const EnemyInfo& info);

private:
	EnemyInfo queue[MAX_ENEMIES];
	Enemy* enemies[MAX_ENEMIES];
};

#endif // __ModuleEnemies_H__
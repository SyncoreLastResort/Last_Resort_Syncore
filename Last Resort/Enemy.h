#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "p2Point.h"
#include "Animation.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "String.h"


struct SDL_Texture;
struct Collider;
struct SDL_Texture;
enum WEAPON_TYPE;

class Enemy
{
protected:
	Animation* animation = nullptr;
	Collider* collider = nullptr;

public:
	fPoint position;
	float life;
	uint score;
	SDL_Texture * texturename;
	enum WEAPON_TYPE weapon_upgraded;
	

public:
	Enemy(int x, int y);
	virtual ~Enemy();

	const Collider* GetCollider() const;

	virtual void Move() {};
	virtual void Draw(SDL_Texture* sprites);
	virtual void OnCollision(Collider* collider);
};

#endif // __ENEMY_H__
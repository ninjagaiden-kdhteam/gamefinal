#pragma once
#include "GameObject.h"
#include "Explosion.h"
#include "Sound.h"


class Weapon : public GameObject
{
public:
	Weapon();
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	~Weapon();
};

typedef Weapon* LPWEAPON;

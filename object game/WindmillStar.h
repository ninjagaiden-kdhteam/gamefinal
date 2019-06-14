#pragma once
#include "Weapon.h"
#include "Explosion.h"
#include "Ninja.h"
class Ninja;
class Explosion;
class WindmillStar :public Weapon
{
	//hệ số a,b của phương trình y=ax+b cho windmillstar
	int a;
	int b;
	float change;//vị trí biên để đổi hướng && tính lại hệ số a,b
	bool isLeftNinja; //cờ: check đã rời khỏi ninja chưa
public:
	WindmillStar();
	~WindmillStar();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	bool checkState(float xNinja, float yNinja, int ninjaAni, int ninjaDirection, int ninjaFrame, DWORD dt);
	void Render(float xNinja, float yNinja, int ninjaAni, int ninjaDirection, int ninjaFrame, DWORD dt);
	void CaculateAB(float xninja, float yninja);
	void collisionEnemies(vector<LPGAMEOBJECT> *enemies);
	bool collisionWithNinja();
	void GetBoundingBox(float &l, float &t, float &r, float &b);
};




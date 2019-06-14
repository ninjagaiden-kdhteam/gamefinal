#pragma once
#include "GameObject.h"
#include "Sound.h"
#define TIME_EXPLOSION 3000
class Explosion;
class Explosion :public GameObject
{
	static Explosion* __Instance;
	bool exploding; //đang nổ ở đâu đó
	int ani;
	DWORD time; //thời gian nổ, dành cho boss chết
public:
	bool getExploding() { return exploding; }
	void Render();
	Explosion();
	void SetExplosion(float x, float y,int ani);
	void EndExplosion();
	bool isExploding() { return this->exploding; };
	static Explosion* GetInstance();
	~Explosion() {};
};


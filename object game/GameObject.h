#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include "Sprites.h"
#include "Animations.h"
#include "Camera.h"
#include "Textures.h"
#include "debug.h"


using namespace std;

class GameObject;
typedef GameObject * LPGAMEOBJECT;

struct CollisionEvent;
typedef CollisionEvent * LPCOLLISIONEVENT;
struct CollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;
	CollisionEvent(float t, float nx, float ny, LPGAMEOBJECT obj = NULL) { this->t = t; this->nx = nx; this->ny = ny; this->obj = obj; }

	static bool compare(const LPCOLLISIONEVENT &a, LPCOLLISIONEVENT &b)
	{
		return a->t < b->t;
	}
};

class GameObject
{
protected:
	//Tọa độ object
	D3DXVECTOR3 position;
	float dx;
	float dy;
	DWORD dt;
	//vận tốc
	float vx;
	float vy;
	float xx;
	float yy;
	//hướng object: >0: (phải) else (trái)
	int direction;
	int w;
	int h;
	int id;//id của object(trong grid)
	bool IsContainer;//có phải là container không?

	State state;//trạng thái
	Type type;
	vector<LPANIMATION> animations;
	int IsActive;
	D3DXVECTOR3 initposition;//vị trí khởi tạo
	int initdirection;//hướng khởi tạo
	float InitVx;//vận tốc khởi tạo
	int HP;//máu
public:
	bool die = false;
#pragma region get set
	bool  GetIsContainer() { return this->IsContainer; }
	int getHP() { return HP; }
	int GetWidth() { return w; }
	int GetHeight() { return h; }

	int GetId() { return this->id; }
	virtual void SetActive(int x);

	int GetActive() { return IsActive; }

	void SetPosition(D3DXVECTOR3 p) { this->position = p; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void SetState(State state) { this->state = state; }
	float GetVx() { return vx; }
	float GetVy() { return vy; }
	void GetSpeed(float &svx, float  &svy) { svx = vx; svy = vy; }
	State GetState() { return this->state; }
	int GetDirection() { return direction; }
	D3DXVECTOR3 GetPosition() { return position; }
	void SetDirection(int di) { this->direction = di; }
	Type GetType() { return this->type; }
#pragma endregion

	void DecreaseHP(int damage);
	D3DXVECTOR3 GetInitposition() { return this->initposition; }
	
	void AddAnimation(int aniId);
	GameObject();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render() = 0;

	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void RenderBoundingBox();

	
	bool IsInCamera();

	
	bool checkAABB(LPGAMEOBJECT obj);
	static void SweptAABB(float ml, float mt, float mr,	float mb, float dx,	float dy, float sl,	float st, float sr, float sb, float &t, float &nx, float &ny);
	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
	void FilterCollision(vector<LPCOLLISIONEVENT> &coEvents, vector<LPCOLLISIONEVENT> &coEventsResult, float &min_tx, float &min_ty, float &nx, float &ny);
	//-------------------------------------------------------
	~GameObject();
};

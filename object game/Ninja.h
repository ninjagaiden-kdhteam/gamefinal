#pragma once
#include "GameObject.h"
#include "Input.h"
#include "Background.h"
#include "Weapon.h"
#include "Sword.h"
#include "ThrowingStar.h"
#include "WindmillStar.h"
#include "debug.h"
#include "Wall.h"
#include "Sound.h"
#include "Items.h"
#include "Time.h"
#include "GreenSniper.h"
#include "SoldierGreen.h"
#include "Mummies.h"
#define STOP_GAME_TIME 2000

class Weapon;
class Sword;
class Ninja: public GameObject
{
	
private:
	static Ninja* __Instance;
	bool flicker; //cờ nháy, dùng khi bị tấn công
#pragma region thuộc tính tương ứng trạng thái 
	int isJumping;
	int isSitting;
	int isHitting;
	int isClimbing;
	int canLatch;
	int canClimb;
	int isLatching;
	int isJumpWall;
	int isUsingItem;
	int isBeingAttacked;
#pragma endregion

#pragma region vũ khí
	vector<LPWEAPON> weapons; //mảng weapon của ninja, 1: throwing star, 2: windmill star
	Weapon* nowWeapon; //weapon đang sử dụng, trỏ đến weapons[i]
	Sword *ninjaSword;
#pragma endregion

	int gameWidth; 

	//giới hạn bức tường ninja đang leo
	int minClimb; 
	int maxClimb;

	DWORD unTouchable;
	float unTouchable_start; //lưu thời điểm bắt đầu untouch

	int currentFrame; //frame hiện tại đang được vẽ của ninja

	DWORD start_stop; //lưu thời điểm bắt đầu stop game

	int score; //điểm
	int Life; //số mạng còn lại
	int strength; //mana, điểm spirit để dùng item
	int createStar; //cờ, =0: chưa tạo ra star nào cả, =1: star đã được tạo ra và còn đang xuất hiện
	int godMode;
	bool isBossDie = false;
public:
	void SetIsBossDie(bool b) { isBossDie=b; }
#pragma region get set thuộc tính
	void setCreateStar(int x) { createStar = x; }
	int GetStrength() { return this->strength; }
	void SetStrength(int st) { this->strength = st; if (st < 0) this->strength = 0; }
	void SetNullNowweapon() { nowWeapon = NULL; }
	int GetLife() { return this->Life; }
	void SetLife(int life);
	int getScore() { return score; }
	void IncreaseScore(int x) { score += x; }
	void SetisJumping(int j) { this->isJumping = j; }
	int GetisJumping() { return this->isJumping; }
	void SetisSitting(int s) { this->isSitting = s; }
	int GetisSitting() { return this->isSitting; }
	void SetisHitting(int h) { this->isHitting = h; }
	int GetisHitting() { return this->isHitting; }
	void SetisClimbing(int c) { this->isClimbing = c; }
	int GetisClimbing() { return this->isClimbing; }
	void SetisLatching(int l) { this->isLatching = l; }
	int GetisLatching() { return this->isLatching; }
	void SetisJumpWall(int jw) { this->isJumpWall = jw; }
	int GetisJumpWall() { return this->isJumpWall; }
#pragma endregion

	int getAnimation();
	EItem GetNowWeapon();
	int isStillStopGame();

	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects=NULL);
	void KeyUpdate(DWORD dt); //update trạng thái ninja dựa vào phím nhấn
	void Render();
	void SetState(State state); //set trạng thái ninja
	void GetBoundingBox(float &l, float &t, float &r, float &b);

	int collisionWall(vector<LPGAMEOBJECT> *coObjects);
	void collisionBrick(vector<LPGAMEOBJECT> *coObjects,int coWall);
	void collisionEnemies(vector<LPGAMEOBJECT> *coObjects);
	void collisionItems();
	void processCollision(vector<LPGAMEOBJECT> *Coobjects);

	int isOnGround(vector<LPGAMEOBJECT> *bricks); //hàm check đang ở trên mặt đất ko

	void startUntouchable() { unTouchable_start = GetTickCount(); unTouchable = 1; }
	void endUntouchable() { unTouchable_start = unTouchable = 0; }
	int stillUntouchable();
	static Ninja* GetInstance();
	Ninja();
};
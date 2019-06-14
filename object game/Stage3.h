#pragma once
#include "GameStage.h"
#include "Brick.h"
#include "Explosion.h"
#include <fstream>
#include "Boss.h"
#include "Bullet.h"

class Stage3 : public GameStage
{
private:
	vector<LPGAMEOBJECT> enemies; //list quái
	vector<LPGAMEOBJECT> bricks; //list gạch
	Boss* boss;
	DWORD time_boss_dead;
	wchar_t buffer[256]; //buffer viết chữ lên màn hình
public:
	Stage3();
	~Stage3();

	// Inherited via GameState
	void Initialize();
	void DestroyAll();
	void Update(DWORD);
	void Render();

	void RenderGameOver();//vẽ màn hình gameover
	void RenderGameWin();//vẽ màn hình gamewin
	void ProcessGameOver(DWORD);//xử lý gameover
	void ProcessGameWin(DWORD);//xử lý gamewin
	void RenderScoreboard();//vẽ bảng điểm

	void getBrick();
};


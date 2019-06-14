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
	vector<LPGAMEOBJECT> enemies;
	vector<LPGAMEOBJECT> bricks;
	Boss* boss;
	DWORD time_boss_dead;
public:
	Stage3();
	~Stage3();

	// Inherited via GameState
	void Initialize();
	void DestroyAll();
	void Update(DWORD);
	void Render();

	void RenderGameOver();
	void RenderGameWin();
	void ProcessGameOver(DWORD);
	void ProcessGameWin(DWORD);
	void RenderScoreboard();

	void getBrick();
};


#pragma once
#include "GameStage.h"
#include "Brick.h"
#include "Explosion.h"
#include <fstream>


#define NINJA_POSITION_MAP1_X 40
#define NINJA_POSITION_MAP1_Y 60

class Stage1: public GameStage
{
private:
	

	vector<LPGAMEOBJECT> bricks;
	vector<LPGAMEOBJECT> enemies;
public:
	Stage1();
	~Stage1();
	
	// Inherited via GameState
	void Initialize();
	void DestroyAll();
	void Update(DWORD);
	void Render();

	void RenderGameOver();
	void ProcessGameOver(DWORD);
	void RenderScoreboard();
	void getBrick();
};


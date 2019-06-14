#ifndef _STAGE2_H_
#define _STAGE2_H_
#include "GameStage.h"
#include "Brick.h"
#include "Wall.h"
#include "Explosion.h"
#include <fstream>

#define NINJA_POSITION_MAP2_X 40
#define NINJA_POSITION_MAP2_Y 60

class Stage2: public GameStage
{
private:
	vector<LPGAMEOBJECT> bricks;
	vector<LPGAMEOBJECT> walls;
	vector<LPGAMEOBJECT> enemies;
public:
	Stage2();
	~Stage2();

	// Inherited via GameState
	void Initialize();
	void DestroyAll();
	void Update(DWORD);
	void Render();


	void RenderGameOver();
	void ProcessGameOver(DWORD);
	void RenderScoreboard();

	void getBrick();
	void getWall();
};

#endif
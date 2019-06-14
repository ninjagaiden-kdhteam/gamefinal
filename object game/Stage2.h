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
	wchar_t buffer[256]; //buffer để viết lên màn hình

	vector<LPGAMEOBJECT> bricks; //list gạch của map 1
	vector<LPGAMEOBJECT> walls; //tường: leo được của map 2
	vector<LPGAMEOBJECT> enemies; //list quái của map 1
public:
	Stage2();
	~Stage2();

	// Inherited via GameState
	void Initialize();
	void DestroyAll();
	void Update(DWORD);
	void Render();


	void RenderGameOver();//vẽ màn hình gameover
	void ProcessGameOver(DWORD);//xử lý gameover
	void RenderScoreboard();//vẽ bảng điểm

	void getBrick();
	void getWall();
};

#endif
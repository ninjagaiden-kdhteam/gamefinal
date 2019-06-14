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
	wchar_t buffer[256]; //buffer để viết lên màn hình

	vector<LPGAMEOBJECT> bricks; //list gạch của map 1
	vector<LPGAMEOBJECT> enemies; //list quái của map 1
public:
	Stage1();
	~Stage1();
	
	// Inherited via GameState
	void Initialize();
	void DestroyAll();
	void Update(DWORD);
	void Render();

	void RenderGameOver(); //vẽ màn hình game over
	void ProcessGameOver(DWORD); //xử lý game over
	void RenderScoreboard(); //vẽ bảng điểm
	void getBrick(); //lấy thông tin gạch map1 từ file txt
};


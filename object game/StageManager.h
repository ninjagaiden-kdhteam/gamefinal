#pragma once
#include "GameStage.h"
#include "Graphic.h"
class GameStage;
class StageManager
{
private:
	GameStage * gameStage;
	Graphic * graphic;
	int stageID;
public:
	StageManager();
	~StageManager();
	void Initialize(HWND hwnd);
	//Load state theo id
	void LoadStage(int stageID);
	void Render();
	void Update(DWORD gameTime);
};
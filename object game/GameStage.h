#pragma once
#include <windows.h>
#include "Textures.h"
#include "Sprites.h"
#include "Camera.h"
#include "GameDefinitions.h"
#include "Grid.h"
#include "Sound.h"
#include "Items.h"
#include "Time.h"
#include "Background.h"
#include "Ninja.h"
class GameStage
{
protected:
	int nextStage;
	int Select;//khi gameover, 1 là continue, -1 là end
	Ninja * ninja;
	Background * back; //đối tượng để vẽ background
	Sound* sound;
	Grid* grid;
	DWORD time_render_dead=0;//thời gian để tính nháy màn hình khi ninja die
	int select_alpha = 0;//chọn màu để nháy khi ninja die
public:
	int stage;
	virtual void Initialize() = 0;
	//Xóa bộ nhớ
	virtual void DestroyAll() = 0;
	virtual void Update(DWORD) = 0;
	virtual void Render() = 0;
	//Lấy id trạng thái tiếp theo
	int GetNextStage() { return nextStage; };
	//Thay đổi trạng thái (màn chơi)
	void ChangeStage(int id) { nextStage = id; }

	//đặt lại một số thông số khi ninja die để chơi lại màn
	void SetNinjaAfterDie();

	GameStage();
	~GameStage();
};


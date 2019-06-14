#include "StageManager.h"
#include "Stage1.h"
#include "Stage2.h"
#include "Stage3.h"

StageManager::StageManager()
{
}


StageManager::~StageManager()
{
}

void StageManager::Initialize(HWND hwnd)
{
	graphic = Graphic::GetInstance();
}

//Load state theo id
void StageManager::LoadStage(int stageID)
{
	switch (stageID)
	{
	case 1:
		gameStage = new Stage1();
		gameStage->Initialize();
		gameStage->stage = stageID;
		this->stageID = stageID;
		break;
	case 2:
		gameStage = new Stage2();
		gameStage->Initialize();
		gameStage->stage = stageID;
		this->stageID = stageID;
		break;
	case 3:
		gameStage = new Stage3();
		gameStage->Initialize();
		gameStage->stage = stageID;
		this->stageID = stageID;
		break;
	default:
		break;
	}
}
void StageManager::Render()
{
	graphic->Clear();
	graphic->Begin();

	gameStage->Render();

	graphic->End();
	graphic->Present();
}

void StageManager::Update(DWORD gameTime)
{
	int next = gameStage->GetNextStage();//Lấy id next state
	if (next != stageID)//Nếu được yêu cầu chuyển state khác (id state mới khác id state hiện tại)
	{
		gameStage->DestroyAll();//Xóa bộ nhớ
		LoadStage(next);//Load state tiếp theo
		gameStage->ChangeStage(next);//Đảm bảo game không chuyển state cho đến khi next state thay đổi
	}
	gameStage->Update(gameTime);
}

#include "GameStage.h"



void GameStage::SetNinjaAfterDie()
{
	IsNinjaDie = false;
	time_render_dead = 0;
	Time::GetInstance()->Reset();
	ninja->SetState(IDLE);
	ninja->SetDirection(1);
	ninja->DecreaseHP(-17);
	ninja->die = false;
	ninja->SetLife(ninja->GetLife() - 1);
	if (stage == 1 || stage == 2)
		ninja->SetPosition(D3DXVECTOR3(40, 60, 0));
	else
		ninja->SetPosition(D3DXVECTOR3(70, 60, 0));
	Camera::GetInstance()->Initialize(0, GAME_HEIGHT);
	Items::GetInstance()->Clear();
	if(stage==1||stage==2)
	grid->ReLoadGrid();
}

GameStage::GameStage()
{
}


GameStage::~GameStage()
{
}

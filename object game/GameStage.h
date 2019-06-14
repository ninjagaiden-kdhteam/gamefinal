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
	int Select;
	Ninja * ninja;
	Background * back;
	Sound* sound;
	Grid* grid;
	DWORD time_render_dead=0;
	int select_alpha = 0;
	wchar_t buffer[256];
public:
	int stage;
	virtual void Initialize() = 0;
	
	virtual void DestroyAll() = 0;
	virtual void Update(DWORD) = 0;
	virtual void Render() = 0;
	
	int GetNextStage() { return nextStage; };
	void ChangeStage(int id) { nextStage = id; }
	void SetNinjaAfterDie();

	GameStage();
	~GameStage();
};


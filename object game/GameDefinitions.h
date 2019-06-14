#pragma once
#include <Windows.h>
#define NINJA_ANIMATION_TIME 50

#define CLASS_NAME L"NinjaGaidenClass"
#define FULLSCREEN 0
#define GAME_TITLE L"Ninja Gaiden"
#define GAME_WIDTH 256
#define GAME_HEIGHT 192+20
#define FRAMES_PER_SECOND 60

#define JUMP_SPEED_Y		0.28f
#define NINJA_UNTOUCHABLE_TIME 1000

#pragma region Map Size
#define MAP_WIDTH_1 2048
#define MAP_WIDTH_2 3072
#define MAP_WIDTH_3 240
#pragma endregion

#define SIZE_TILE_SET 16

#define WALKING_SPEED		0.1f
#define NINJA_CLIMB_SPEED		0.1f

#define GRAVITY			0.02f
#define SOLDIER_GREEN_WALKING   0.07f
#define SOLDIER_YELLOW_WALKING 0.05f
#define DOG_WALKING 0.102f
#define MUMMIES_WALKING 0.06f

#pragma region animation ninja
#define NINJA_ANI_IDLE				0
#define NINJA_ANI_WALKING			1
#define NINJA_ANI_SIT				2
#define NINJA_ANI_STAND_HIT			3
#define NINJA_ANI_SIT_HIT			4
#define NINJA_ANI_JUMP				5
#define NINJA_ANI_LATCH				6
#define NINJA_ANI_CLIMB				7
#define NINJA_ANI_BEING_ATTACKED	8
#define NINJA_ANI_USE_ITEM			9
#define NINJA_ANI_DIE 10

#pragma endregion

#pragma region animation enemy
#define SOLDIERYELLOW_ANI_WALKING 0
#define BAT_ANI 0
#define SOLDIERGREEN_ANI_WALKING 0
#define SOLDIERGREEN_ANI_ATTACK 1
#define DOG_ANI 0
#define MUMMIES_ANI_WALKING 0
#define MUMMIES_ANI_ATTACK 1
#define BIRD_ANI 0
#define BUTTERFLY_ANI 0
#define GREENSNIPER_ANI 0
#define GREENSNIPER_ANI_ATTACK 1
#define EAGGLE_ANI 0
#define RUNNINGMAN_ANI 0
#pragma endregion

#pragma region animation item
#define I_BONUSPOINTBLUE_ANI 0
#define I_BONUSPOINTRED_ANI 1
#define I_SPIRITPOINTSRED_ANI 2
#define I_SPIRITPOINTSBLUE_ANI 3
#define I_TIMEFREEZE_ANI 4
#define I_HEALTH_ANI 5
#define I_FLAMES_ANI 6
#define I_THROWINGSTAR_ANI 7
#define I_WINDMILLSTAR_ANI 8
#pragma endregion

#pragma region weapon ani
#define SWORD_ANI 0
#define BULLET_ANI 0
#define THROWINGSTAR_ANI 0
#define WINDMILLSTAR_ANI 0
#define KNIFE_ANI 0
#pragma endregion

#pragma region ninja size
#define NINJA_IDLE_W 17
#define NINJA_IDLE_H 32
#define NINJA_ATTACK_W 17
#define NINJA_ATTACK_H 32

#define NINJA_SIT_W 17
#define NINJA_SIT_H 32
#define NINJA_SITATTACK_W 17
#define NINJA_SITATTACK_H 32
#define NINJA_JUMP_W 17
#define NINJA_JUMP_H 32
#define NINJA_WALK_W 17
#define NINJA_WALK_H 32
#define NINJA_CLIMB_W 17
#define NINJA_CLIMB_H 32
#define NINJA_LATCH_W 17
#define NINJA_LATCH_H 32
#define NINJA_BE_ATTACK_W 17
#define NINJA_BE_ATTACK_H 32
#pragma endregion

#pragma region object size
#define BAT_W 17
#define BAT_H 15
#define BIRD_W 20
#define BIRD_H 28
#define BUTTERFLY_W 16
#define BUTTERFLY_H 20
#define DOG_W 30
#define DOG_H 19
#define MUMMIES_W 26
#define MUMMIES_H 35
#define SOLDIERGREEN_W 17
#define SOLDIERGREEN_H 34
#define SOLDIERYELLOW_W 26
#define SOLDIERYELLOW_H 40
#define GREENSNIPER_W 26
#define GREENSNIPER_H 26
#define EAGGLE_W 17
#define EAGGLE_H 17
#define RUNNINGMAN_W 17
#define RUNNINGMAN_H 33

#define KNIFE_W 10
#define KNIFE_H 15
#define BULLET_W 8
#define BULLET_H 3
#define SWORD_W 20
#define SWORD_H 12
#define THROWINGSTAR_W 9
#define THROWINGSTAR_H 9
#define WINDMILLSTAR_W 17
#define WINDMILLSTAR_H 17
#define ITEM_W 15
#define ITEM_H 15
#pragma endregion

//object TYPE
enum Type
{
	BAT = 1,
	BIRD = 2,
	BUTTERFLY = 3,
	DOG = 4,
	MUMMIES = 5,
	SOLDIERGREEN = 6,
	SOLDIERYELLOW = 7,
	BRICK =8,
	SWORD = 9,
	BULLET = 10,
	WALL=11,
	THROWINGSTAR=12,
	WINDMILLSTAR=13,
	RUNNINGMAN=14,
	EAGGLE=15,
	GREENSNIPER=16,
	KNIFE=17,
	BOSS=18
};
//object STATE
enum State
{
	ATTACK,
	IDLE,
	WALKING_RIGHT,
	WALKING_LEFT,
	JUMP,
	SIT,
	STAND_HIT,
	SIT_HIT,
	LATCH,
	CLIMB_UP,
	CLIMB_DOWN,
	JUMPWALL_RIGHT,
	JUMPWALL_LEFT,
	BEING_ATTACKED_RIGHT,
	BEING_ATTACKED_LEFT,
	USE_ITEM,
	WALKING,
	DIE
};
//Sound
enum ESound
{
	background1 = 1,
	sword = 2,
	untouch = 3,
	gameover = 4,
	chemitem = 5,
	chemtrungquai = 6,
	chem=7,
	ninjajump=8,
	bossdie=9,
	background2=10,
	hetgio=11,
	background3=12
};
//item TYPE
enum EItem
{
	I_BONUSPOINTBLUE=0,
	I_BONUSPOINTRED=1,
	I_SPIRITPOINTSRED=2,
	I_SPIRITPOINTSBLUE=3,
	I_TIMEFREEZE=4,
	I_HEALTH=5,
	I_FLAMES=6,
	I_THROWINGSTAR=7,
	I_WINDMILLSTAR=8
};

#pragma region game over choice
#define CONTINUE 1 
#define END -1
#pragma endregion

#pragma region check render sprite
#define NHAY_MOTMAU 1
#define KHONG_NHAY 0
#define GODMODE 3
#pragma endregion

#define IsKeyDown(keyCode) Input::GetInstance()->isKeyDown(keyCode)
#define IsKeyPress(keyCode) Input::GetInstance()->isKeyPress(keyCode)

extern HWND hwndGlobal;//handle của window
extern bool IsTimeFreeze;//kiểm tra xem có đang đóng băng do item freeze không?
extern bool IsGamePause;//kiểm tra có đang dừng game không?
extern bool IsNinjaDie;//kiểm tra ninja có đang die không?
extern bool AllowSound;//có chấp nhận phát âm thanh không?
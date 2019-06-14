
#include "Sound.h"

Sound* Sound::__Instance = NULL;

Sound::Sound()
{
	Init();
	LoadSound();
}



void Sound::LoadSound()
{
	AddSound(ESound::background1, L"sounds/bg13audio.wav");
	AddSound(ESound::background2, L"sounds/map2background.wav");
	AddSound(ESound::sword, L"sounds/22.wav");
	AddSound(ESound::untouch, L"sounds/bitancong.wav");
	AddSound(ESound::gameover, L"sounds/gameover.wav");
	AddSound(ESound::chemtrungquai, L"sounds/chemtrungquai.wav");
	AddSound(ESound::chemitem, L"sounds/chemitem.wav");
	AddSound(ESound::chem, L"sounds/chem.wav");
	AddSound(ESound::ninjajump, L"sounds/ninjajump.wav");
	AddSound(ESound::bossdie, L"sounds/bossDie.wav");
	AddSound(ESound::hetgio, L"sounds/hetgio.wav");
}

bool Sound::isPlaying(ESound type)
{
	return listSound[type]->IsSoundPlaying();
}

void Sound::StopAll()
{
	for (auto& x : listSound)
	{
		if (x.second->IsSoundPlaying())
			x.second->Stop();
	}
}


void Sound::AddSound(ESound type, LPTSTR filename)
{
	CSound *wave;
	HRESULT result = dsound->Create(&wave, filename);
	if (result != DS_OK)
	{
		return;
	}
	listSound[type] = wave;
}

void Sound::Play(ESound type, bool isLoop)
{
	listSound[type]->Play(0, isLoop);
}

void Sound::Stop(ESound type)
{
	listSound[type]->Stop();
}



void Sound::Init()
{
	dsound = new CSoundManager();
	dsound->Initialize(hwndGlobal, DSSCL_PRIORITY);
	dsound->SetPrimaryBufferFormat(2, 22050, 16);
}

Sound * Sound::GetInstance()
{
	if (__Instance == NULL)
		__Instance = new Sound();
	return __Instance;
}
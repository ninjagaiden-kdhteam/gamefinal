#ifndef __TIME_H__
#define __TIME_H__
#include <Windows.h>
#include "Sound.h"
class Time
{
private:
	Time();
	int time;
	DWORD timetroiqua;//thời gian trôi qua nếu >=1000 thì qua 1s
	bool IsPause;//dừng đồng hồ
public:
	static Time* __Instance;
	static Time* GetInstance();
	~Time();
	void Pause();//dừng đếm, dùng khi ăn item timefreeze
	void UnPause();//đếm tiếp, dùng để mở khóa hết hạn item timefreeze
	void Update(DWORD dt);//cập nhật thời gian
	void Reset();//đặt thời gian về 150s
	int GetTime();
	void SetTime(int t) { time = t; }
};
#endif // !__TIME_H__

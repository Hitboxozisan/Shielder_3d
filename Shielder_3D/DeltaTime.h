#pragma once

/// <summary>
/// �V���O���g���i�V���O���g���ł͂Ȃ�static�ő�p�\�j
/// �ǂ��ł��g����悤�ɂł͂Ȃ��A�������݂����獢��Ƃ��ɃV���O���g���͎g��
/// ��������Ƒ��݈Ӗ��̂���V���O���g���Ȃ�OK
/// </summary>
class DeltaTime
{
public:
	DeltaTime();
	~DeltaTime();
	static DeltaTime& GetInstance();
	void   InstrumentationDeltaTime();
	// void   SetDeltaTime(float delta);
	void   SetCount();
	inline float GetDeltaTime() { return deltaTime; }

private:
	int nowCount;
	int prevCount;
	float deltaTime;
	bool  isSlow;
};


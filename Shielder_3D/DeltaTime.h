#pragma once
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


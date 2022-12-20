#pragma once

/// <summary>
/// シングルトン（シングルトンではなくstaticで代用可能）
/// どこでも使えるようにではなく、複数存在したら困るときにシングルトンは使う
/// しっかりと存在意味のあるシングルトンならOK
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


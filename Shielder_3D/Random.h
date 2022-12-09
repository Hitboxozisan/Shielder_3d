#pragma once
class Random
{
public:
	Random();
	~Random();
	
	static Random& GetInstance();						// インスタンスの取得
	int   GetRandomInt(int min, int max);				// ランダムなint値を返す
	float GetRandomFloat(float min, float max);			// ランダムなfloat値を返す
private:
	
};


#pragma once
class EffectBase
{
public:
	EffectBase();
	virtual ~EffectBase();

	virtual void Initialize() = 0;
	virtual void Finalize() = 0;
	virtual void Activate(VECTOR inPosition) = 0;		//引数をどうにかしたい
	virtual void Deactivate() = 0;
	virtual void Update(VECTOR inPostion, VECTOR inEnemyPosition) = 0;
	virtual void Draw() = 0;

	bool GetExist() const;			//存在しているかどうか
protected:
	int effectHandle;
	int playingEffectHandle;
	VECTOR position;
	float frame;
	float size;			// エフェクトの拡大率
	bool exist;			// 存在しているか
	int existFrame;		// 存在できる残りフレーム
	
private:
	EffectBase(const EffectBase&);
	void operator=(const EffectBase&);
};


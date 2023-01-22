#pragma once

#include "EffectBase.h"

class EffectFieldBackground : public EffectBase
{
public:
	EffectFieldBackground();
	~EffectFieldBackground();

	void Initialize();
	void Finalize();
	void Activate(VECTOR inPosition);
	void Deactivate();
	void Update(VECTOR inPostion, VECTOR inEnemyPosition);
	void Draw();

private:
	EffectFieldBackground(const EffectFieldBackground&);
	void operator=(const EffectFieldBackground&);
};


#pragma once

#include "EffectBase.h"

class EffectTeleport : public EffectBase
{
public:
	EffectTeleport();
	~EffectTeleport();

	void Initialize();
	void Finalize();
	void Activate(VECTOR inPosition);
	void Deactivate();
	void Update(VECTOR inPostion, VECTOR inEnemyPosition);
	void Draw();

private:
	EffectTeleport(const EffectTeleport&);
	void operator=(const  EffectTeleport&);
};


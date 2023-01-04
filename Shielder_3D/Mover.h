#pragma once

#include "ObjectBase.h"

class Mover : public ObjectBase
{
public:
	Mover();
	virtual ~Mover();

protected:
	virtual void MoveFinish() = 0;			// 移動予定地に実際に移動する

	VECTOR nextPosition;		// 次フレームの位置
	VECTOR nextDirection;		// 次フレームの向き
	VECTOR prevPosition;		// 前フレームの位置
	VECTOR prevDirection;		// 前フレームの向き

private:

};


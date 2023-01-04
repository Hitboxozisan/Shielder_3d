#pragma once

#include "ObjectBase.h"

class Mover : public ObjectBase
{
public:
	Mover();
	virtual ~Mover();

protected:
	virtual void MoveFinish() = 0;			// �ړ��\��n�Ɏ��ۂɈړ�����

	VECTOR nextPosition;		// ���t���[���̈ʒu
	VECTOR nextDirection;		// ���t���[���̌���
	VECTOR prevPosition;		// �O�t���[���̈ʒu
	VECTOR prevDirection;		// �O�t���[���̌���

private:

};


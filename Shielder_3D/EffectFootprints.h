#pragma once

#include "BillboardBase.h"

/// <summary>
/// ���ՃG�t�F�N�g
/// �ړ���ɃI�u�W�F�N�g�̑����ɃG�t�F�N�g��\������
/// </summary>
class EffectFootprints final : public BillboardBase
{
public:
	EffectFootprints();
	~EffectFootprints();

	void Activate(const VECTOR& inPosition, float inSize);
	void Draw(const VECTOR& inPosition);

	void UpdateEach();

private:
	static const int DEFAULT_EXIST_FRAME;			//���݂ł��鏉���t���[����
	static const float INCREASE_SIZE;				//1�t���[���ő�������T�C�Y

	float size;				//�摜�̑傫��

	float opacity;			//�s�����x
};


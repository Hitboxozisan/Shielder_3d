#pragma once

#include "BillboardBase.h"

class ChargeEnergyEffect final : public BillboardBase
{
public:
	ChargeEnergyEffect();
	~ChargeEnergyEffect();

	void Activate(const VECTOR& inPosition, float inSize);	// ����������
	bool Diffusion();										// �G�t�F�N�g���g�U������
	void Draw(const VECTOR& inPosition);					// �`��

	void UpdateEach();										// ���q���Q�[�W�܂ŏW�߂�
private:
	//static const float INITIAL_SIZE;						// �����T�C�Y
	static const float DIFFUSION_SPEED;						// �g�U���x
	static const float MAX_DIFFUSION_DISTANCE;				// �ő�g�U����
	static const float MIN_DIFFUSION_DISTANCE;				// �ŏ��g�U����
	static const float INCREASE_SPEED_EACH_FRAME;			// 1�t���[�����Ƒ��x�̑�����

	float size;			// �摜�̑傫��

	VECTOR generationPosition;		// �����ʒu
	VECTOR velocity;				// ���݂̑��x�A�����x�A����
	float  speed;					// �ړ����x�ivelocity�Ƃ̈Ⴂ�́H�j
	float  opacity;					// �s�����x
	float  diffusionDistance;		// �g�U����
	float  progressDistance;		// �i�s����
};


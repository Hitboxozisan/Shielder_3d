#include "Pch.h"
#include <chrono>
#include <thread>
#include <random>
#include "Math3d.h"
#include "ChargeEnergyEffect.h"

using namespace Math3d;

const float ChargeEnergyEffect::DIFFUSION_SPEED			  = 30.0f;
const float ChargeEnergyEffect::MAX_DIFFUSION_DISTANCE	  = 50.0f;
const float ChargeEnergyEffect::MIN_DIFFUSION_DISTANCE	  = 15.0f;
const float ChargeEnergyEffect::INCREASE_SPEED_EACH_FRAME = 0.5f;

ChargeEnergyEffect::ChargeEnergyEffect()
{
}

ChargeEnergyEffect::~ChargeEnergyEffect()
{
}

void ChargeEnergyEffect::Activate(const VECTOR& inPosition, float inSize)
{
	//�����p�ϐ�
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<int> next(MIN_DIFFUSION_DISTANCE, MAX_DIFFUSION_DISTANCE);
	std::uniform_real_distribution<> velocity1(0, 1);
	std::uniform_real_distribution<> velocity2(0, 1);
	std::uniform_real_distribution<> velocity3(0, 1);

	exist = true;
	existFrame = 100;
	position = inPosition;
	generationPosition = position;

	size = inSize;

	speed = 0.0f;
	velocity = VGet(velocity1(eng), velocity2(eng), velocity3(eng));
	opacity = 1.0f;
	diffusionDistance = next(eng);	//�g�U������ݒ�
	progressDistance = 0.0f;
}

/// <summary>
/// �g�U�w��͈͂܂ŗ��q���g�U������
/// </summary>
/// <returns></returns>
bool ChargeEnergyEffect::Diffusion()
{

	// �g�U�w�苗���܂ŗ��q���g�U������
	if (diffusionDistance >= progressDistance)
	{
		position = VAdd(position, VScale(velocity, DIFFUSION_SPEED));		// �g�U������
		progressDistance = VSize(position - generationPosition);			// �����ʒu����̋������v�Z
		return false;
	}

	// �g�U�����I������@�@�@
	return true;
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="inPosition"></param>
void ChargeEnergyEffect::Draw(const VECTOR& inPosition)
{
	//���݂��Ȃ��Ȃ珈�����Ȃ�
	if (exist == false)
	{
		return;
	}

	//SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, 255);	//�u�����h���[�h

	DrawBillboard3D(position, 0.5f, 0.5f, size, 0.0f, *graphicPointer, TRUE);		//�摜�̕`��

	//SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, 255);	//�u�����h���[�h����
}

/// <summary>
/// �X�V����
/// </summary>
void ChargeEnergyEffect::UpdateEach()
{
	// �g�U������������G�l�~�[�̑̊��Q�[�W�W�܂�n�߂�
	if (Diffusion())
	{
		speed += INCREASE_SPEED_EACH_FRAME;
		VECTOR destination = ConvScreenPosToWorldPos(VGet(SCREEN_CENTER, 900.0f, 1.0f));
		// �Ȃ���Y���̑傫����900�ɗ��R�s��
		//VECTOR destination = VGet(SCREEN_CENTER, 900.0f, 0.0f);
		VECTOR force = destination - position;

		position = VAdd(position, VNorm(force) * speed);		//�ړ�������

		// �ړI�n�ɓ��B�����瑶�݂��Ȃ���Ԃɂ���
		// X���̌덷�͍l�����Ȃ�
		if (position.y >= destination.y)
		{
			exist = false;
		}
	}

	
}

#pragma once

#include "EffectBase.h"
#include "BillboardBase.h"
#include <string>

class EffectManager final
{
public:
	enum Effects
	{
		SPARK,				// �X�p�[�N
		DAMAGE,				// �_���[�W
		PLAYER_DEAD,		// ���S
		ENEMY_TELEPORT,		// �u�Ԉړ�
		//RECOVERY,			// ��
		//PLAYER_LASER,		// �v���C���[�����G�t�F�N�g

		EFFECT_AMOUNT,		// �G�t�F�N�g�̑���
	};

	EffectManager();
	~EffectManager();

	void Initialize();
	void Finalize();
	void Activate(VECTOR inPosition);
	void Deactivate();
	void Update(VECTOR inPostion, VECTOR inEnemyPosition);
	void Draw(const VECTOR& inPosition);

	void CreateSparkEffect(const VECTOR& inPosition);		// �ΉԂ𐶐�����
	void CreateEnergyEffect(const VECTOR& inPosition);		// ���q�𐶐�����
	void CreateSmokeEffect(const VECTOR& inPosition);		// ���𐶐�����
	void CreateDamageEffect(const VECTOR& inPosition);		// �_���[�W�G�t�F�N�g�𐶐�����
	void CreatePlayerDiedEffect(const VECTOR& inPosition);	// �v���C���[���S�G�t�F�N�g�𐶐�����
	void CreateRecoveryEffect(const VECTOR& inPosition);	// �v���C���[�񕜃G�t�F�N�g�𐶐�����
	void CreatePlayerLaser(const VECTOR& inPosition);		// �v���C���[�����G�t�F�N�g�𐶐�����
	void CreateTeleportEffect(const VECTOR& inPosition);	// �e���|�[�g�G�t�F�N�g�𐶐�����

	bool GetEnergyEffectState();							// ���q�G�t�F�N�g�̏�Ԃ��擾����

private:
	EffectManager(const EffectManager&);
	void operator=(const EffectManager&);

	static const std::string SPARK_EFFECT_PATH;
	static const std::string DAMAGE_EFFECT_PATH;
	static const std::string RIGOR_EFFECT_GRAPHIC_PATH;
	static const std::string ENERGY_EFFECT_GRAPHIC_PATH;

	static const int SMOKE_EFFECT_AMOUNT;
	static const int ENERGY_EFFECT_AMOUNT;

	// �摜�G�t�F�N�g�T�C�Y�i����͊e�G�t�F�N�g�̂ق��Ŏw�肷�ׂ��Ǝv���j
	static const float SMOKE_EFFECT_SIZE;

	// �x�[�X�N���X�C���X�^���X�̑���
	// enum �� �����炩���ꂷ��K�v����
	static const int BILLBOARD_AMOUNT;

	EffectBase* effects[EFFECT_AMOUNT];
	BillboardBase** graphicEffects;

	int smokeGraphicHandle;
	int energyGraphicHandle;
};


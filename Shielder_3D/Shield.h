#pragma once

#include "ObjectBase.h"

class Shield final : public ObjectBase
{
public:
	Shield();
	~Shield();

	// ���
	enum class State
	{
		NONE,			// ���݂��Ȃ�
		DEPLOYMENT,		// �W�J��
		DESTRUCTION		// �j��
	};

	void Initialize();									// ����������
	void Finalize();									// �I������
	void Activate(const VECTOR& inPosition,
				  const VECTOR& inDirection,
				  const VECTOR& inPrevDirection);		// ����������
	void Deactivate();									// �񊈐�������
	void Update();										// �X�V����
	void Draw();										// �`�揈��

	void DecrementHitPoint();							// �ϋv�l������������

	State GetState() const { return state; }			// ���݂̏�Ԃ�Ԃ�
	void SetShieldPosition(const VECTOR& inPosition,
							 const VECTOR& inDirection,
							 const VECTOR& inPrevDirection);	// �V�[���h�̈ʒu��ݒ�

private:
	Shield(const Shield&);			// �R�s�[�R���X�g���N�^
	void operator=(const Shield&);	// ������Z�q

	static const float MAX_HITPOINT;							// �ő�ϋv�l
	static const float SCALE_BY_DIRECTION_FOR_CORRECTION;		// �v���C���[�Ƃ̋���

	State state;

	void (Shield::* pUpdate)();		// Update�֐��|�C���^

	float hitPoint;					// �V�[���h�̑ϋv�l
	float elapsedtTime;				// �V�[���h��W�J���Ă���̌o�ߎ���
	VECTOR distanceToPlayer;		// �v���C���[�Ƃ̋���

	void UpdateDeployment();		// DEPLOYMENT���X�V����
	void UpdateDestruction();		// DESTRUCTION���X�V����

};


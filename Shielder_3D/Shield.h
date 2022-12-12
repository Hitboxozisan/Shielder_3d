#pragma once

#include "ObjectBase.h"

class Shield : public ObjectBase
{
public:
	Shield();
	~Shield();

	// ���
	enum State
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
	void Update(const VECTOR& inPosition, 
				const VECTOR& inDirection, 
				const VECTOR& inPrevDirection);			// �X�V����
	void Draw();										// �`�揈��

	void DecrementHitPoint();							// �ϋv�l������������

	State GetState() const { return state; }			// ���݂̏�Ԃ�Ԃ�

private:
	Shield(const Shield&);			// �R�s�[�R���X�g���N�^
	void operator=(const Shield&);	// ������Z�q

	static const float SCALE_BY_DIRECTION_FOR_CORRECTION;		// �v���C���[�Ƃ̋���

	State state;

	float hitPoint;					// �V�[���h�̑ϋv�l
	float elapsedtTime;				// �V�[���h��W�J���Ă���̌o�ߎ���
	VECTOR distanceToPlayer;		// �v���C���[�Ƃ̋���

};


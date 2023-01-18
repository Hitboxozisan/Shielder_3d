#pragma once

#include "Mover.h"

class Sword : public Mover
{
public:
	// �I�u�W�F�N�g�̏��
	enum class State
	{
		NONE,		// ���݂��Ȃ�
		ACTIVE		// ���݂��Ă���
	};

	Sword();
	~Sword();

	void Initialize();							// ����������
	void Finalize();							// �I������
	void Activate(const VECTOR& inPosition,
				  const VECTOR& inDirection);	// ����������
	void Deactivate();							// �񊈐�������
	void Update();								// �X�V����
	void Draw();								// �`�揈��

	void activateSword(const VECTOR& inPosition,
					   const VECTOR& inDirection);	// ���𑶍݂�����
	void rollSword();								// ����U��
private:
	static const VECTOR INITIAL_POSITION;						// �����ʒu
	static const VECTOR INITIAL_DIRECTION;						// ��������
	static const VECTOR INITIAL_SCALE;							// �����T�C�Y
	static const float SCALE_BY_DIRECTION_FOR_CORRECTION;		// �O������

	State state;

	void SetToFrontOfObject(const VECTOR& inPosition,
							const VECTOR& inDirection);			// �I�u�W�F�N�g�̑O�ɔz�u����
	void MoveFinish();											// �ړ��\��n�Ɏ��ۂɈړ�����
};


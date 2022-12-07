#pragma once

#include "Character.h"

class Player : public Character
{
public:
	Player();
	~Player();

	// ���
	enum State
	{
		NONE,		// ���݂��Ȃ�
		NORMAL,		// �ʏ�
		DEAD		// ���S
	};

	void Initialize();		// ����������
	void Finalize();		// �I������
	void Activate();		// ����������
	void Deactivate();		// �񊈐�������
	void Update();			// �X�V����
	void Draw();			// �`�揈��

	void GameStart();			// �Q�[���J�n���i���o�p�j
	void Releaseinvincible();	// ���G��ԉ���

private:
	static const VECTOR INITIAL_POSITION;		// �����ʒu
	static const VECTOR INITIAL_DIRECTION;		// ��������
	static const VECTOR NORMAL_SPEED;			// 
	static const float  MAX_HITPOINT;			// �ő�HitPoint

	State state;								// ���
	VECTOR inputDirection;						// ���͕���

	void (Player::* pUpdate)();					// Update�֐��|�C���^

	// �eState���Ƃ̍X�V����
	void UpdateNomal();							// NORMAL���X�V����
	void UpdateDead();							// DEAD���X�V����

	void InputAction();							// ���͏���
};
#pragma once

#include "Mover.h"

class Character : public Mover
{
public:
	Character();
	virtual ~Character();

	virtual void Initialize() = 0;		// ����������
	virtual void Finalize() = 0;		// �I������
	virtual void Activate() = 0;		// ����������
	virtual void Deactivate() = 0;		// �񊈐�������
	virtual void Update() = 0;			// �X�V����
	virtual void Draw() = 0;			// �`�揈��

	void		 MoveFinish();				// �ړ��\��n�Ɏ��ۂɈړ�
	virtual void GameStart() = 0;			// �Q�[���J�n���i���o�p�j
	virtual void Releaseinvincible() = 0;	// ���G��ԉ���

	bool IsAlive();							// �����Ă��邩��Ԃ�

protected:

	float hitPoint;	
	float speed;					// �ړ����x				
	float invincibleTime;			// ���G����
	bool  noDrawFrame;				// �`��\�t���[����
	bool  isAlive;					// �����Ă��邩

private:


};


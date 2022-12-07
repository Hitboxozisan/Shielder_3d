#include "Pch.h"
#include "Player.h"
#include "KeyManager.h"
#include "ModelManager.h"

const VECTOR Player::INITIAL_POSITION  = VGet(500.0f, 0.0f, 100.0f);
const VECTOR Player::INITIAL_DIRECTION = VGet(0.0f, 0.0f, 1.0f);

using namespace Math3d;		// VECTOR�̌v�Z�Ɏg�p

/// <summary>
/// �R���X�g���N�^
/// </summary>
Player::Player()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Player::~Player()
{
}

/// <summary>
/// ����������
/// </summary>
void Player::Initialize()
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::PLAYER));

	

}

/// <summary>
/// �I������
/// </summary>
void Player::Finalize()
{
	
}

/// <summary>
/// ����������
/// </summary>
void Player::Activate()
{
	// �����ʒu�E������ݒ�
	position = INITIAL_POSITION;
	nextPosition = position;
	prevPosition = position;
	direction = INITIAL_DIRECTION;
	nextDirection = direction;
	prevDirection = direction;

	// ��Ԃ� NORMAL ��
	state = NORMAL;
}

/// <summary>
/// �񊈐�������
/// </summary>
void Player::Deactivate()
{
}

/// <summary>
/// �X�V����
/// </summary>
void Player::Update()
{

}

/// <summary>
/// �`�揈��
/// </summary>
void Player::Draw()
{
}

/// <summary>
/// �Q�[���J�n���̏����i���o�p�j
/// </summary>
void Player::GameStart()
{
}

/// <summary>
/// ���G��ԉ���
/// </summary>
void Player::Releaseinvincible()
{

}

/// <summary>
/// NORMAL���X�V����
/// </summary>
void Player::UpdateNomal()
{
	MoveFinish();
}

/// <summary>
/// DEAD���X�V����
/// </summary>
void Player::UpdateDead()
{

}

/// <summary>
/// ���͏���
/// </summary>
void Player::InputAction()
{
#ifdef DEBUG
	// P�L�[�Ŏ��S
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_P))
	{
		hitPoint = 0;
	}

#endif // DEBUG

	// ���E�ړ�
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_A) && nextPosition.x >= SCREEN_LEFTMOST)
	{
		inputDirection += LEFT * speed * deltaTime;
	}
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_D) && nextPosition.x <= SCREEN_RIGHTMOST)
	{
		inputDirection += RIGHT * speed * deltaTime;
	}

	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_SPACE))
	{
		// �W�����v

	}

	// �h��
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_LSHIFT) ||
		KeyManager::GetInstance().CheckPressed(KEY_INPUT_SPACE))
	{
		speed = DEFENSE_SPEED;	// �ړ����x�ύX
		CreateShield();			// ������

		pUpdate = &Player::UpdateDefence;
	}
	else
	{
		speed = NORMAL_SPEED;	// 

		shield->Deactivate();	//�������ł�����
		pUpdate = &Player::UpdateNormal;
	}

	// ��
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_R))
	{
		Recovery();
	}
}

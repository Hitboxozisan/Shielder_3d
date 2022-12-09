#include "Pch.h"
#include "Player.h"
#include "DeltaTime.h"
#include "KeyManager.h"
#include "ModelManager.h"

const VECTOR Player::INITIAL_POSITION  = VGet(500.0f, 0.0f, 100.0f);
const VECTOR Player::INITIAL_DIRECTION = VGet(0.0f, 0.0f, 1.0f);
const VECTOR Player::INITIAL_SCALE = VGet(0.5f, 0.5f, 0.5f);
const float  Player::NORMAL_SPEED = 100.0f;

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
	// ���f���̓ǂݍ���
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::PLAYER));
	MV1SetScale(modelHandle, INITIAL_SCALE);
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
	speed = NORMAL_SPEED;
	noDrawFrame = false;

	// ��Ԃ� NORMAL ��
	state = NORMAL;
	pUpdate = &Player::UpdateNomal;

	// ���f���������ʒu�ɔz�u
	MV1SetPosition(modelHandle, position);
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
	if (pUpdate != nullptr)
	{
		(this->*pUpdate)();		// ��Ԃ��Ƃ̍X�V����
	}

}

/// <summary>
/// �`�揈��
/// </summary>
void Player::Draw()
{
	// �`�悵�Ȃ��t���[���Ȃ�`�悵�Ȃ�
	if (noDrawFrame || state == DEAD)
	{
		return;
	}

	MV1DrawModel(modelHandle);
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
	Move();
	MoveFinish();
	InputAction();
}

/// <summary>
/// DEAD���X�V����
/// </summary>
void Player::UpdateDead()
{

}

/// <summary>
/// �ړ�����
/// </summary>
void Player::Move()
{
	float deltaTime = DeltaTime::GetInstance().GetDeltaTime();

	// ���͂��Ȃ��Ȃ��~����
	if (VSquareSize(inputDirection) != 0.0f)
	{
		nextDirection = VNorm(inputDirection);
	}
	else
	{
		nextDirection = inputDirection;
	}

	nextPosition = VAdd(position, VScale(nextDirection, speed) * deltaTime);
}

/// <summary>
/// 
/// </summary>
void Player::MoveFinish()
{

}

/// <summary>
/// ���͏���
/// </summary>
void Player::InputAction()
{
	float deltaTime = DeltaTime::GetInstance().GetDeltaTime();
	inputDirection = ZERO_VECTOR;

#ifdef DEBUG
	// P�L�[�Ŏ��S
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_P))
	{
		hitPoint = 0;
	}

#endif // DEBUG

	// �O�㍶�E�ړ�
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_W))
	{
		inputDirection += PROGRESS * speed * deltaTime;
	}
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_S))
	{
		inputDirection += RECESSION * speed * deltaTime;
	}
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_A))
	{
		inputDirection += LEFT * speed * deltaTime;
	}
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_D))
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
		//speed = DEFENSE_SPEED;	// �ړ����x�ύX
		//CreateShield();			// ������

		//pUpdate = &Player::UpdateDefence;
	}
	else
	{
		//speed = NORMAL_SPEED;	// 

		//shield->Deactivate();	//�������ł�����
		//pUpdate = &Player::UpdateNormal;
	}

	// ��
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_R))
	{
		//Recovery();
	}
}

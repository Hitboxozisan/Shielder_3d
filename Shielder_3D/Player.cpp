#include "Pch.h"
#include "Player.h"
#include "Shield.h"
#include "DeltaTime.h"
#include "KeyManager.h"
#include "ModelManager.h"

const VECTOR Player::INITIAL_POSITION  = VGet(500.0f, 0.0f, 100.0f);
const VECTOR Player::INITIAL_DIRECTION = VGet(0.0f, 0.0f, 1.0f);
const VECTOR Player::INITIAL_SCALE     = VGet(0.5f, 0.5f, 0.5f);
const float  Player::SPEED_INCREASE    = 5.0f;
const float  Player::SPEED_DECREASE    = 10.0f;
const float  Player::MAX_NORMAL_SPEED  = 300.0f;
const float  Player::MAX_DEFENSE_SPEED = 100.0f;

using namespace Math3d;		// VECTOR�̌v�Z�Ɏg�p

/// <summary>
/// �R���X�g���N�^
/// </summary>
Player::Player()
	:inputDirection(ZERO_VECTOR)
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
	speed = 0.0f;
	maxSpeed = MAX_NORMAL_SPEED;
	noDrawFrame = false;

	// ��Ԃ� NORMAL ��
	state = NORMAL;
	pUpdate = &Player::UpdateNomal;

	// ���f���������ʒu�ɔz�u
	MV1SetPosition(modelHandle, position);

	shield = new Shield();
	shield->Initialize();
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
	shield->Draw();
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
/// DEFENSE���X�V����
/// </summary>
void Player::UpdateDefense()
{
	Move();
	MoveFinish();
	InputAction();
	shield->SetShieldPosition(position, direction, prevDirection);
	shield->Update();
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

	// ���͂�����ƈړ�����
	if (VSize(inputDirection) != 0.0f)
	{
		// �ő呬�x�܂ňړ����x�����X�ɑ���������
		if (speed <= maxSpeed)
		{
			speed += SPEED_INCREASE;
		}

		nextDirection = VNorm(inputDirection);
	}
	else
	{
		// �ړ����x�����X�Ɍ���������
		if (speed > 0.0f)
		{
			speed -= SPEED_DECREASE;
		}
		else
		{
			speed = 0.0f;
		}
	}

	nextPosition = VAdd(position, VScale(nextDirection, speed) * deltaTime);
}

/// <summary>
/// 
/// </summary>
//void Player::MoveFinish()
//{
//	printfDx("child");
//}

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
		inputDirection += PROGRESS;
	}
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_S))
	{
		inputDirection += RECESSION;
	}
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_A))
	{
		inputDirection += LEFT;
	}
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_D))
	{
		inputDirection += RIGHT;
	}

	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_SPACE))
	{
		// �W�����v

	}

	// �h��
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_LSHIFT) ||
		KeyManager::GetInstance().CheckPressed(KEY_INPUT_SPACE))
	{
		ChangeSpeed(MAX_DEFENSE_SPEED);			// ���x��ύX����
		expandShield();							// ���𐶐�����

		//pUpdate = &Player::UpdateDefence;
	}
	else
	{
		ChangeSpeed(MAX_NORMAL_SPEED);			// ���x��ύX����
		shield->Deactivate();					//�������ł�����
		//pUpdate = &Player::UpdateNormal;
	}

	// ��
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_R))
	{
		//Recovery();
	}
}

/// <summary>
/// �ő�ړ����x��ύX����
/// </summary>
/// <param name="speed">�ύX��̍ő呬�x</param>
void Player::ChangeSpeed(float afterSpeed)
{
	maxSpeed = afterSpeed;
	// �ύX���A�ړ����x���ύX��̍ő呬�x��葬�������瑬�x�𗎂Ƃ�
	if (speed > maxSpeed)
	{
		speed = maxSpeed;
	}
}

/// <summary>
/// ����W�J����
/// </summary>
void Player::expandShield()
{
	// �������ɑ��݂��Ă�������͔j�󂳂�Ă���Ȃ珈�����Ȃ�
	if (shield->GetState() == Shield::State::DEPLOYMENT ||
		shield->GetState() == Shield::State::DESTRUCTION)
	{
		return;
	}
	shield->Activate(position, direction, prevDirection);
}

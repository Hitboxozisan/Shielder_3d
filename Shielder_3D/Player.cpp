//----------------------------------------------------------------
// <�s��E�o�O>
// �E���b�N�I�����A���x����������̂͌����ɉe�����邽�߈ړ������͂��~�߂�ƁA
// �@�O�ɐi�ޕs����������B���O�̓��͌������擾���邱�Ƃŉ������H
// 
//----------------------------------------------------------------

#include "Pch.h"
#include "Player.h"
#include "Shield.h"
#include "Camera.h"
#include "EffectManager.h"
#include "DeltaTime.h"
#include "KeyManager.h"
#include "ModelManager.h"
#include "Timer.h"

const VECTOR Player::INITIAL_POSITION    = VGet(500.0f, 0.0f, 100.0f);
const VECTOR Player::INITIAL_DIRECTION   = VGet(0.0f, 0.0f, 1.0f);
const VECTOR Player::INITIAL_SCALE       = VGet(0.5f, 0.5f, 0.5f);
const float  Player::SPEED_INCREASE      = 5.0f;
const float  Player::SPEED_DECREASE      = 10.0f;
const float  Player::MAX_HIT_POINT	     = 100.0f;
const float  Player::MAX_NORMAL_SPEED    = 500.0f;
const float  Player::MAX_DEFENSE_SPEED   = 200.0f;
const float  Player::COLLIDE_RADIUS	     = 100.0f;
const float  Player::DECREMENT_HIT_POINT = 10.0f;
const float  Player::FORCE_AT_DAMAGE	 = 500.0f;
const float  Player::FORCE_AT_DEFENSE    = 300.0f;
const float  Player::FRICTIONAL_FORCE	 = -400.0f;

using namespace Math3d;		// VECTOR�̌v�Z�Ɏg�p

/// <summary>
/// �R���X�g���N�^
/// </summary>
Player::Player(Camera* const inCamera)
	:inputDirection(ZERO_VECTOR)
	,camera(inCamera)
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
void Player::Initialize(EffectManager* const inEffectManager)
{
	shield = new Shield();
	shield->Initialize(inEffectManager);

	effectManager = inEffectManager;
	// ���f���̓ǂݍ���
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::PLAYER));
	// ���f���̊g�嗦�ݒ�
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
	hitPoint = MAX_HIT_POINT;
	speed = 0.0f;
	maxSpeed = MAX_NORMAL_SPEED;
	frame = 0;
	noDrawFrame = false;
	// �����蔻�苅���ݒ�
	collisionSphere.localCenter = ZERO_VECTOR;
	collisionSphere.worldCenter = position;
	collisionSphere.radius = COLLIDE_RADIUS;


	// ��Ԃ� NORMAL ��
	state = State::NORMAL;
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

	// �����蔻�苅�ړ�����
	collisionSphere.Move(position);
}

/// <summary>
/// �`�揈��
/// </summary>
void Player::Draw()
{
	// �`�悵�Ȃ��t���[���Ȃ�`�悵�Ȃ�
	if (noDrawFrame || state == State::DEAD)
	{
		return;
	}

	MV1DrawModel(modelHandle);
	shield->Draw();

#ifdef DEBUG
	//�����蔻��f�o�b�N�`��
	DrawSphere3D(collisionSphere.worldCenter, collisionSphere.radius,
		32, GetColor(0, 255, 0), 0, FALSE);

#endif // DEBUG
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
/// ���̃L�����N�^�[�ƐڐG����
/// </summary>
void Player::HitOtherCharacter(const VECTOR& forceDirection)
{
	// ���˕Ԃ�͂�ݒ�
	force = forceDirection;
	force = VScale(force, FORCE_AT_DAMAGE);

	// �_���[�W�G�t�F�N�g�𐶐�����
	effectManager->CreateDamageEffect(position);

	// HitPoint������������
	DecrementHitPoint();

	// ��Ԃ� DAMAGE ��
	state = State::DAMAGE;
	pUpdate = &Player::UpdateDamage;
}

/// <summary>
/// �V�[���h�����̃L�����N�^�[���ڐG����
/// </summary>
/// <param name="forceDirection"></param>
void Player::HitShieldOtherCharacter(const VECTOR& forceDirection)
{
	// ���˕Ԃ�͂�ݒ�
	force = forceDirection;
	force = VScale(force, FORCE_AT_DEFENSE);

	// �K�[�h�G�t�F�N�g�𐶐�����
	effectManager->CreateSparkEffect(position);

	// ��Ԃ� DAMAGE ��
	state = State::PREVENT;
	pUpdate = &Player::UpdatePrevent;
}

/// <summary>
/// �����蔻�苅���a��Ԃ�
/// </summary>
/// <returns></returns>
const float Player::GetCollideRadius()
{
	return collisionSphere.radius;
}

const float Player::GetHitPoint()
{
	return hitPoint;
}

/// <summary>
/// �v���C���[�̏�Ԃ�Ԃ�
/// </summary>
/// <returns></returns>
const Player::State Player::GetCurrentState()
{
	return state;
}

/// <summary>
/// ���̃|�C���^��Ԃ�
/// </summary>
/// <returns></returns>
Shield *Player::GetShieldPointer()
{
	return shield;
}

///// <summary>
///// ���̌��݈ʒu��Ԃ�
///// </summary>
///// <returns></returns>
//VECTOR Player::GetShieldPosition()
//{
//	shield->GetPosition();
//}
//
//State Player::GetShieldState()
//{
//	return shield->GetState();
//}

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
/// PREVENT���X�V����
/// </summary>
void Player::UpdatePrevent()
{
	MoveFinish();
	DefenseBouncePlayer();
	shield->SetShieldPosition(position, direction, prevDirection);
	shield->Update();
}

/// <summary>
/// DAMAGE���̍X�V����
/// </summary>
void Player::UpdateDamage()
{
	// ���˕Ԃ�I����s���\��
	if (DamageBouncePlayer())
	{
		/*InputAction();
		InvincibleUpdate();
		Move();*/
	}

	// �ړ��\��n�Ɏ��ۂɈړ�����
	MoveFinish();
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
		// ���K��
		inputDirection = VNorm(inputDirection);
		// �ő呬�x�܂ňړ����x�����X�ɑ���������
		if (speed <= maxSpeed)
		{
			speed += SPEED_INCREASE;
		}

		nextDirection = inputDirection;
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

	// ���b�N�I�����̏ꍇ�͌������Œ肷��
	if (camera->IsRockOn())
	{
		VECTOR front = position - camera->GetPosition();
		front.y = 0.0f;
		front = VNorm(front);
		nextDirection = front;
	}

	
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
	VECTOR yAxis = { 0, 1, 0 };
	VECTOR front = position - camera->GetPosition();
	front.y = 0.0f;				// �����x�N�g�����l�����Ȃ�
	front = VNorm(front);
	VECTOR left = VCross(front, yAxis);

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
		inputDirection += front;
	}
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_S))
	{
		inputDirection += VScale(front, -1.0f);
	}
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_A))
	{
		inputDirection += left;
	}
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_D))
	{
		inputDirection += VScale(left, -1.0f);
	}

	// ���b�N�I���؂�ւ�
	if (KeyManager::GetInstance().CheckJustPressed(KEY_INPUT_R))
	{
		camera->ChangeCamera();
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
		ActivateShield();						// ���𐶐�����
	}
	else
	{
		ChangeSpeed(MAX_NORMAL_SPEED);			// ���x��ύX����
		shield->Deactivate();					// �������ł�����
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
void Player::ActivateShield()
{
	// �������ɑ��݂��Ă�������͔j�󂳂�Ă���Ȃ珈�����Ȃ�
	if (shield->GetState() == Shield::State::DEPLOYMENT ||
		shield->GetState() == Shield::State::DESTRUCTION)
	{
		return;
	}
	shield->Activate(position, direction, prevDirection);
	pUpdate = &Player::UpdateDefense;
}

/// <summary>
/// �������ł�����
/// </summary>
void Player::DeactivateShield()
{
	shield->Deactivate();
	pUpdate = &Player::UpdateNomal;
}

/// <summary>
/// �̗͂�����������
/// </summary>
void Player::DecrementHitPoint()
{
	// HitPoint������������
	hitPoint -= DECREMENT_HIT_POINT;
	// HitPoint����������炱��ȏ㌸�����Ȃ��悤�ɂ���
	if (hitPoint <= 0)
	{
		hitPoint = 0.0f;
	}
}

/// <summary>
/// ���G��ԏ���
/// </summary>
void Player::InvincibleUpdate()
{
	// �C���X�^���X�̐���
	if (timer == nullptr)
	{
		timer = new Timer(2.0f);
	}

	float deltaTime = DeltaTime::GetInstance().GetDeltaTime();

	// ��莞�Ԗ��G��Ԃɂ���
	timer->Update(deltaTime);

	// ��莞�Ԍo�ߌ㖳�G��ԉ���
	if (timer->IsTimeout())
	{
		noDrawFrame = false;

		// ��Ԃ� NORMAL ��
		state = State::NORMAL;
		pUpdate = &Player::UpdateNomal;
	}
	else
	{
		// 2�t���[����1��`�悷��
		noDrawFrame != noDrawFrame;
	}

}

/// <summary>
/// �v���C���[�𒵂˕Ԃ��i�_���[�W�j
/// </summary>
bool Player::DamageBouncePlayer()
{
	float deltaTime = DeltaTime::GetInstance().GetDeltaTime();
	++frame;

	// ���C�͂�ݒ�
	VECTOR frictionalForce = VNorm(force);
	frictionalForce = VScale(frictionalForce, FRICTIONAL_FORCE);

	nextPosition = VAdd(nextPosition, force * deltaTime);
	force = VAdd(force, frictionalForce * deltaTime);

	// ��莞�Ԃ����ɃG�t�F�N�g����
	if (frame % 10 == 0)
	{
		// �X���[�N�G�t�F�N�g����
		effectManager->CreateSmokeEffect(nextPosition);
	}
	
	// ���˕Ԃ��͂�0�ɋ߂��Ȃ�����I������
	if (VSize(force) <= 1.0f)
	{
		// �o�߃t���[�������Z�b�g
		frame = 0;
		// ��Ԃ� NORMAL ��
		state = State::NORMAL;
		pUpdate = &Player::UpdateNomal;
		return true;
	}
	return false;
}

/// <summary>
/// �v���C���[�𒵂˕Ԃ��i�f�B�t�F���X�j
/// </summary>
/// <returns></returns>
bool Player::DefenseBouncePlayer()
{
	float deltaTime = DeltaTime::GetInstance().GetDeltaTime();
	++frame;

	// ���C�͂�ݒ�
	VECTOR frictionalForce = VNorm(force);
	frictionalForce = VScale(frictionalForce, FRICTIONAL_FORCE);

	// �ړ�
	nextPosition = VAdd(nextPosition, force * deltaTime);
	force = VAdd(force, frictionalForce * deltaTime);

	// ��莞�Ԃ����ɃG�t�F�N�g����
	if (frame % 10 == 0)
	{
		// �X���[�N�G�t�F�N�g����
		effectManager->CreateSmokeEffect(nextPosition);
	}

	// ���˕Ԃ��͂�0�ɋ߂��Ȃ�����I������
	if (VSize(force) <= 1.0f)
	{
		// �V�[���h��񊈐���
		shield->Deactivate();
		// �o�߃t���[�������Z�b�g
		frame = 0;
		// �͂�0�ɖ߂�


		// ��Ԃ� NORMAL ��
		state = State::NORMAL;
		pUpdate = &Player::UpdateNomal;
		return true;
	}
	return false;
}


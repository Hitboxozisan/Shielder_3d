//----------------------------------------------------------------
// <�s��E�o�O>
// �E
// <note>
// �E�U�������b�N�I�����Ƃ킩��ɂ���������x�̌덷�͒ǂ�Ȃ��悤�ɂ���ׂ����H
//----------------------------------------------------------------

#include "Pch.h"
#include "Boss.h"
#include "Player.h"
#include "Bullet.h"
#include "BulletCreater.h"
#include "KeyManager.h"
#include "ModelManager.h"
#include "Random.h"
#include "Timer.h"
#include "DeltaTime.h"

using namespace My3dLib;
using namespace Math3d;

const VECTOR Boss::INITIAL_POSITION    = VGet(500.0f, 0.0f, 500.0f);
const VECTOR Boss::INITIAL_DIRECTION   = VGet(0.0f, 0.0f, -1.0f);
const VECTOR Boss::INITIAL_SCALE       = VGet(0.5f, 0.5f, 0.5f);
const VECTOR Boss::JUMP_FORCE		   = VGet(0.0f, 800.0f, 0.0f);
const float  Boss::FRICTIONAL_FORCE    = -0.1f;
const float  Boss::GRAVITY			   = -10.0f;
const float  Boss::FORCE_AT_HIT_SHIELD = 3.0f;
const float  Boss::COLLIDE_RADIUS      = 100.0f;
const float  Boss::VIBRATE_TIME		   = 2.0f;
const float  Boss::ASSAULT_SPEED	   = 1000.0f;
const float  Boss::ASSAULT_DISTANCE    = 1500.0f;
const float  Boss::TELEPORT_DISTANCE   = 500.0f;
const float  Boss::SHOT_INTERVAL	   = 2.0f;
const int    Boss::ASSAULT_TIME		   = 3;
const int	 Boss::SHOT_TIME		   = 3;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Boss::Boss(Player* inPlayer,
		   BulletCreater* const inBulletCreater)
	:player(inPlayer)
	,bulletCreater(inBulletCreater)
{
	// �����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Boss::~Boss()
{
	// �����Ȃ�
}

/// <summary>
/// ����������
/// </summary>
void Boss::Initialize()
{
	// ���f���̓ǂݍ���
	modelHandle = ModelManager::GetInstance().GetModelHandle(ModelManager::ENEMY);
	// ���f���̊g�嗦�ݒ�
	MV1SetScale(modelHandle, INITIAL_SCALE);
}

/// <summary>
/// �I������
/// </summary>
void Boss::Fainalize()
{
}

/// <summary>
/// ����������
/// </summary>
void Boss::Activate()
{
	position = INITIAL_POSITION;
	nextPosition = position;
	prevPosition = position;
	direction = INITIAL_DIRECTION;
	nextDirection = direction;
	prevDirection = direction;

	// �����蔻�苅���ݒ�
	collisionSphere.localCenter = ZERO_VECTOR;
	collisionSphere.worldCenter = position;
	collisionSphere.radius = COLLIDE_RADIUS;

	assaultTime = 0;
	shotTime = 0;
	hitPoint = 50.0f;
	vibrateTime = 0.0f;
	startAssaultPosition = ZERO_VECTOR;
	force = ZERO_VECTOR;
	jumpForce = ZERO_VECTOR;

	// ������Ԃ� NORMAL �Ɂi��ɕʓr�s���؂�ւ��j
	state = State::ATTACK;
	pUpdate = &Boss::UpdateAttack;

#ifdef DEBUG

#endif // DEBUG

	ChangeAttackState(AttackState::THINKING);
	// �U���p�^�[���� ASSAULT ��
	//attackState = AttackState::THINKING;
	//pUpdateAttack = &Boss::UpdateThinking;

	// ���f���������ʒu�ɔz�u
	MV1SetPosition(modelHandle, position);
}

/// <summary>
/// �񊈐�������
/// </summary>
void Boss::Deactivate()
{
}

/// <summary>
/// �X�V����
/// </summary>
void Boss::Update()
{
	if (pUpdate != nullptr)
	{
		(this->*pUpdate)();		// ��Ԃ��Ƃ̍X�V����
	}

	// �ړ��\��n�Ɏ��ۂɈړ�����
	MoveFinish();
	// �����蔻�苅�ړ�
	collisionSphere.Move(position);
}

/// <summary>
/// �`�揈��
/// </summary>
void Boss::Draw()
{
	// �`�悵�Ȃ��t���[���Ȃ�`�悵�Ȃ�
	if (state == State::NONE || state == State::DEAD)
	{
		return;
	}
	
	// ���f���̕`��
	MV1DrawModel(modelHandle);

#ifdef DEBUG

	//�����蔻��f�o�b�N�`��
	DrawSphere3D(collisionSphere.worldCenter, collisionSphere.radius,
		8, GetColor(0, 255, 0), 0, FALSE);

#endif // DEBUG
}

/// <summary>
/// �ړ��\��n�Ɏ��ۂɈړ�����
/// </summary>
void Boss::MoveFinish()
{
	prevPosition = position;
	position = nextPosition;
	direction = nextDirection;

	// �ʒu��ݒ�
	MV1SetPosition(modelHandle, position);

	// ���f���̌���������
	MV1SetRotationYUseDir(modelHandle, direction, 0.0f);
}

/// <summary>
/// ���̃L�����N�^�[�ƐڐG����
/// </summary>
/// <param name="forceDirection"></param>
void Boss::HitOtherCharacter(const VECTOR& forceDirection)
{
	// ���˕Ԃ�͂�ݒ�
	//force = forceDirection;
	//force = VScale(force, FORCE_AT_DEFENSE);

	// �K�[�h�G�t�F�N�g�𐶐�����


	// ��Ԃ� DAMAGE ��
	//state = State::;
	//pUpdate = &Player::UpdatePrevent;

	// ���̍s�������肷��
	ChangeAttackState(AttackState::THINKING);
	//attackState = AttackState::THINKING;
	//pUpdateAttack = &Boss::UpdateThinking;
}

/// <summary>
/// �V�[���h�ɐڐG����
/// </summary>
/// <param name="forceDirection"></param>
void Boss::HitShield(const VECTOR& forceDirection)
{
	// ���˕Ԃ�͂�ݒ�
	force = forceDirection;
	force = VScale(force, FORCE_AT_HIT_SHIELD);

	// ��Ԃ� DAMAGE ��
	state = State::SLIDE;
	pUpdate = &Boss::UpdateSlide;
}

/// <summary>
/// ���݂�HitPoint��Ԃ�
/// </summary>
/// <returns></returns>
const float Boss::GetHitPoint()
{
	return hitPoint;
}

/// <summary>
/// �����蔻�苅���a��Ԃ�
/// </summary>
/// <returns></returns>
const float Boss::GetCollideRadius()
{
	return collisionSphere.radius;
}

/// <summary>
/// AttackState�ɍ��킹�čX�V������ύX����
/// </summary>
void Boss::SetNextAttackUpdate()
{
	// �eAttackState���ƂɍX�V������ύX����
	switch (attackState)
	{
	case AttackState::ASSAULT:
		pUpdateAttack = &Boss::UpdateAssault;
		break;
	case AttackState::BULLET:
		pUpdateAttack = &Boss::UpdateBullet;
		break;
	case AttackState::JUMP:
		pUpdateAttack = &Boss::UpdateJump;
		break;
	case AttackState::TELEPORT:
		pUpdateAttack = &Boss::UpdateTeleport;
		break;
	case AttackState::THINKING:
		pUpdateAttack = &Boss::UpdateThinking;
		break;
	default:
		break;
	}
}

/// <summary>
/// ����state�����肷��
/// </summary>
void Boss::SetNextAttackState()
{
	int attackStateAmount = static_cast<int>(AttackState::ATTACK_AMOUST);
	AttackState nextAttack;

	// �e�����L�[���͏���
	for (int i = 0; i < attackStateAmount; ++i)
	{
		// �eAttackState �ɕύX�i�L�[�̔ԍ��́j
		if (KeyManager::GetInstance().CheckJustPressed(i + 2))
		{
			nextAttack = static_cast<AttackState>(i);
			// �s��������
			ChangeAttackState(nextAttack);
			//attackState = nextAttack;
			//SetNextAttackUpdate();
		}
	}

}

/// <summary>
/// ATTACK���̍X�V����
/// </summary>
void Boss::UpdateAttack()
{
	if (pUpdateAttack != nullptr)
	{
		(this->*pUpdateAttack)();
	}

	// �ړ��\��n�Ɏ��ۂɈړ�����
	MoveFinish();			
}

/// <summary>
/// SLLIDE���̍X�V����
/// </summary>
void Boss::UpdateSlide()
{
	// ���������I����A���̍s�����v�l����
	if (Slide())
	{
		state = State::ATTACK;
		pUpdate = &Boss::UpdateAttack;
		ChangeAttackState(AttackState::THINKING);
		//pUpdateAttack = &Boss::UpdateThinking;
	}
}

/// <summary>
/// ASSAULT���̍X�V����
/// </summary>
void Boss::UpdateAssault()
{
	// �K��񐔂܂œːi�𑱂���
	if (assaultTime < ASSAULT_TIME)
	{
		// ��莞�ԐU����v���C���[�Ɍ������ēːi
		if (Vibrate())
		{
			AssaultToPlayer();
		}
		else
		{
			// �v���C���[�̂ق�������
			FaceToPlayer();		
		}
	}
	// �K��񐔂܂œːi���I������玟�̍s�������肷��
	else
	{
		ChangeAttackState(AttackState::THINKING);
		//attackState = AttackState::THINKING;
		//pUpdateAttack = &Boss::UpdateThinking;
	}
}

/// <summary>
/// BULLET���̍X�V����
/// </summary>
void Boss::UpdateBullet()
{
	float deltaTime = DeltaTime::GetInstance().GetDeltaTime();

	if (timer == nullptr)
	{
		timer = new Timer(SHOT_INTERVAL);
	}
	// �^�C�}�[���X�V
	timer->Update(deltaTime);

	// �v���C���[�̂ق�������
	FaceToPlayer();

	// �K��񐔂܂Ŕ��˂���
	if (shotTime <= SHOT_TIME && timer->IsTimeout())
	{
		ReloadBullet();			// �e�̐���
		ShootBullet();			// �e�𔭎˂���
		shotTime++;				// ���ˉ񐔃J�E���g
		timer->Reset();			// �^�C�}�[�����Z�b�g
	}
	// �K��񐔔��˂���Ǝ��̍s���Ɉڂ�
	else if(shotTime > SHOT_TIME)
	{
		ChangeAttackState(AttackState::THINKING);
	}

}

/// <summary>
/// JUMP���̍X�V����
/// </summary>
void Boss::UpdateJump()
{
	// �W�����v���I������玟�̍s���Ɉڂ�
	if (Jump())
	{
		ChangeAttackState(AttackState::ASSAULT);
		//attackState = AttackState::ASSAULT;
		//pUpdateAttack = &Boss::UpdateAssault;
	}
}

/// <summary>
/// TELEPORT���̍X�V����
/// </summary>
void Boss::UpdateTeleport()
{
	float deltaTime = DeltaTime::GetInstance().GetDeltaTime();
	// �^�C�}�[�����Z�b�g
	if (timer == nullptr)
	{
		timer = new Timer(1.0f);
	}

	// �^�C�}�[���X�V
	timer->Update(deltaTime);

	// State �� NONE �ɂ����݂����Ō��莞�Ԍo�ߌ� State �� NORMAL �ɖ߂�
	if (timer->IsTimeout())
	{
		// �e���|�[�g�G�t�F�N�g�𐶐�����

		// �v���C���[�����苗���̈ʒu�ɏu�Ԉړ�����
		Teleport();
		state = State::ATTACK;
		ChangeAttackState(AttackState::THINKING);
		//attackState = AttackState::THINKING;
	}
	else
	{
		// �{�X�̏�Ԃ�ύX����
		if (state != State::NONE)
		{
			// �e���|�[�g�G�t�F�N�g�𐶐�����


			state = State::NONE;
		}
	}

	
}

/// <summary>
/// THINKING���̍X�V����
/// </summary>
void Boss::UpdateThinking()
{
	int attackAmoust = static_cast<int>(AttackState::ATTACK_AMOUST);
	int nextAttack = Random::GetInstance().GetRandomInt(0, attackAmoust);
	AttackState nextState;

	// �e��l�����Z�b�g
	if (timer != nullptr)
	{
		timer->Reset();
	}
	assaultTime = 0;
	

#ifdef DEBUG

	// ���̍s��������
	SetNextAttackState();
	ChangeStateInitialize();

#else

	// �O��ƈႤ�s���ɂ���
	do
	{
		// ���̍s��������
		nextState = static_cast<AttackState>(nextAttack);

	} while (prevAttackState != nextState);

	// ���̏�ԂɈڍs����
	attackState = nextState;
	SetNextAttackUpdate();

#endif // DEBUG
	
}

/// <summary>
/// ��ԕω����̏�����
/// </summary>
void Boss::ChangeStateInitialize()
{
	// JUMP ���̏���������
	if (attackState == AttackState::JUMP)
	{
		// �W�����v�͂�ݒ�
		jumpForce = JUMP_FORCE;
	}
}

// �U���p�^�[���ύX
void Boss::ChangeAttackState(AttackState nextState)
{
	// �U���p�^�[���ύX
	attackState = nextState;
	SetNextAttackUpdate();
}

/// <summary>
/// Y���W��0.0f�̈ʒu�ɖ߂�
/// </summary>
void Boss::ResetPositionYaw()
{
	
}

/// <summary>
/// �v���C���[�̂ق�������
/// </summary>
void Boss::FaceToPlayer()
{
	VECTOR sub = player->GetPosition() - position;
	VECTOR inDirection = VNorm(sub);

	nextDirection = inDirection;
}

/// <summary>
/// �v���C���[�Ɍ������ēːi����
/// </summary>
void Boss::AssaultToPlayer()
{
	float deltaTime = DeltaTime::GetInstance().GetDeltaTime();
	VECTOR speed = direction * ASSAULT_SPEED;
	VECTOR sub = position - startAssaultPosition;
	float inDistance = VSize(sub);

	// �w�苗���ːi������
	if (inDistance >= ASSAULT_DISTANCE)
	{
		// �I������
		++assaultTime;
		// �U�����̃^�C�}�[�����Z�b�g����
		timer->Reset();
		return;
	}

	nextPosition = VAdd(nextPosition, speed * deltaTime);
	
}

/// <summary>
/// �e���[����
/// </summary>
void Boss::ReloadBullet()
{
	// �e�𐶐��\�Ȃ琶������
	if (bulletCreater->IsCreatableCheck())
	{
		bullet = bulletCreater->Create(position, direction);
	}
}

/// <summary>
/// �e�𔭎˂���
/// </summary>
void Boss::ShootBullet()
{
	// �e��ێ����Ă��Ȃ��Ȃ珈�����Ȃ�
	if (bullet == nullptr)
	{
		return;
	}

	bullet->Shoot();
}

/// <summary>
/// �W�����v������
/// </summary>
bool Boss::Jump()
{
	float deltaTime = DeltaTime::GetInstance().GetDeltaTime();

	jumpForce.y += GRAVITY;

	// ��荂���܂ŃW�����v������
	if (jumpForce.y <= 0.0f)
	{
		jumpForce = ZERO_VECTOR;

		return true;
	}

	// �ړ�
	nextPosition = VAdd(nextPosition, jumpForce * deltaTime);

	return false;

}

/// <summary>
/// �U��������
/// </summary>
/// <returns></returns>
bool Boss::Vibrate()
{
	float deltaTime = DeltaTime::GetInstance().GetDeltaTime();
	if (timer == nullptr)
	{
		timer = new Timer(VIBRATE_TIME);
	}
	
	float randomX = Random::GetInstance().GetRandomFloat(-200, 200);
	float randomZ = Random::GetInstance().GetRandomFloat(-200, 200);

	// �����_���ȕ����Ɉړ���������
	VECTOR randomForce = VGet(randomX, 0.0f, randomZ);
	
	timer->Update(deltaTime);

	// �w��b���U��������
	if (!timer->IsTimeout())
	{

		nextPosition = prevPosition;
		position = prevPosition;

		nextPosition = VAdd(nextPosition, randomForce * deltaTime);

		// �ːi�J�n�ʒu���X�V����
		startAssaultPosition = position;
		return false;
	}
	
	return true;
}

/// <summary>
/// �v���C���[�����苗���̈ʒu�ɏu�Ԉړ�����
/// </summary>
/// <returns></returns>
bool Boss::Teleport()
{
	// �v���C���[���甼�a�i��苗���j�̏ꏊ�ɏu�Ԉړ�����
	VECTOR origin = player->GetPosition();
	VECTOR newPosition = origin;
	float angle = Random::GetInstance().GetRandomFloat(0.0f, 2.0f);

	// �o���ʒu���Z�o
	newPosition.x = origin.x + TELEPORT_DISTANCE * cosf(angle * DX_PI);
	newPosition.z = origin.z + TELEPORT_DISTANCE * sinf(angle * DX_PI);
	// �O�̂���Y���W�����Z�b�g����
	newPosition.y = 0.0f;

	// �ʒu��ݒ�
	nextPosition = newPosition;

	return true;
}

/// <summary>
/// �h�䂳�ꂽ�Ƃ��̔���
/// </summary>
/// <returns>�ړ����I������</returns>
bool Boss::Slide()
{
	float deltaTime = DeltaTime::GetInstance().GetDeltaTime();
	// ���C�͂�ݒ�
	VECTOR frictionalForce = VNorm(force);
	frictionalForce = VScale(frictionalForce, FRICTIONAL_FORCE);

	nextPosition = VAdd(nextPosition, force * deltaTime);
	force = VAdd(force, frictionalForce * deltaTime);

	// ���˕Ԃ��͂�0�ɂȂ�����I������
	if (VSize(force) <= 0.0f)
	{
		// ��Ԃ� NORMAL ��
		state = State::ATTACK;
		pUpdate = &Boss::UpdateAttack;
		return true;
	}
	return false;
}

#include "Pch.h"

#include "Bullet.h"
#include "DeltaTime.h"
#include "ModelManager.h"

const VECTOR Bullet::INITIAL_SCALE			 = VGet(0.5f, 0.5f, 0.5f);
const float  Bullet::NORMAL_SPEED		     = 1000.0f;
const float  Bullet::SLOW_SPEED				 = 200.0f;
const float  Bullet::SCALE_BY_DIRECTION_FOR_CORRECTION = 1.0f;
const float  Bullet::NORMAL_FORWARD_DISTANCE = 100.0f;
const float  Bullet::COLLIDE_RADIUS			 = 50.0f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Bullet::Bullet()
	:state(State::NORMAL)
	,velocity()
	,speed(0.0f)
{
	// �����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Bullet::~Bullet()
{
	if (modelHandle != NULL)
	{
		Finalize();
	}
}

/// <summary>
/// ����������
/// </summary>
void Bullet::Initialize()
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::BULLET));
}

/// <summary>
/// �I������
/// </summary>
void Bullet::Finalize()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;
}

/// <summary>
/// ����������
/// </summary>
/// <param name="inPosition">���ˈʒu</param>
/// <param name="inDirection">���ˌ���</param>
void Bullet::Activate(const VECTOR& inPosition, const VECTOR& inDirection)
{
	// �ʒu�E������ݒ�
	position = inPosition;
	nextPosition = position;
	prevPosition = position;
	direction = inDirection;
	nextDirection = direction;
	prevDirection = direction;

	velocity = ZERO_VECTOR;
	
	speed = NORMAL_SPEED;
	state = State::SHOOT;

	collisionSphere.localCenter = ZERO_VECTOR;
	collisionSphere.radius = COLLIDE_RADIUS;
	collisionSphere.worldCenter = position;

	SetToFrontOfEnemy(inPosition, inDirection);					// �G�l�~�[�̑O���Ɉʒu����

	MV1SetScale(modelHandle, INITIAL_SCALE);					// ���f���g��k��
	MV1SetRotationXYZ(modelHandle, VGet(0.0f, 1.5f, 0.0f));		// ���f���̌�����ݒ�
}

/// <summary>
/// �񊈐�������
/// </summary>
void Bullet::Deactivate()
{
	state = State::NORMAL;
}

/// <summary>
/// �X�V����
/// </summary>
/// <returns></returns>
bool Bullet::Update()
{
	//���݂��Ȃ��Ȃ珈�����Ȃ�
	if (state == State::NONE)
	{
		return false;
	}

	//���ł���Ƃ��̏���
	if (state == State::NORMAL ||
		state == State::SHOOT)
	{
		if (state == State::NORMAL)
		{
			
		}
		else
		{
			Move();
		}
		MoveFinish();

		return true;
	}

	return true;
}

/// <summary>
/// �`�揈��
/// </summary>
void Bullet::Draw()
{
	// ���݂��Ȃ��Ȃ�`�悵�Ȃ�
	if (state == State::NONE)
	{
		return;
	}

	MV1DrawModel(modelHandle);					// 3D���f���̕`��

#ifdef DEBUG

	// �����蔻��f�o�b�N�`��
	//DrawSphere3D(collisionSphere.worldCenter, collisionSphere.radius,
		//8, GetColor(0, 255, 0), 0, FALSE);

#endif // DEBUG	
}

/// <summary>
/// 
/// </summary>
/// <param name="attackType"></param>
void Bullet::Shoot()
{
	// ���ˏ�Ԃɂ���
	state = State::SHOOT;
}

/// <summary>
/// �G�l�~�[�̑O���ɐݒu
/// </summary>
/// <param name="inPosition"></param>
/// <param name="inDirection"></param>
void Bullet::SetToFrontOfEnemy(const VECTOR& inPosition, const VECTOR& inDirection)
{
	position = inPosition;
	direction = inDirection;

	//�G�l�~�[�̑O���Ɉʒu����
	VECTOR distanceToPlayer = VScale(direction, SCALE_BY_DIRECTION_FOR_CORRECTION);

	nextPosition = VAdd(nextPosition, distanceToPlayer);
}

/// <summary>
/// ���݂̏�Ԃ�Ԃ�
/// </summary>
/// <returns></returns>
Bullet::State Bullet::GetState() const
{
	return state;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
bool Bullet::IsCollidableState() const
{
	if (state == State::NORMAL ||
		state == State::SHOOT)
	{
		return true;
	}

	return false;
}

/// <summary>
/// �����蔻�苅���a��Ԃ�
/// </summary>
/// <returns></returns>
const float Bullet::GetCollisionRadius() const
{
	return collisionSphere.radius;
}

/// <summary>
/// �t�B�[���h�O�ɏo��
/// </summary>
void Bullet::OnOutField()
{
	Deactivate();
}

/// <summary>
/// �����ɓ������ĉ�ꂽ
/// </summary>
void Bullet::OnHitBreak()
{
	state = State::NONE;
}

/// <summary>
/// �ړ�����
/// </summary>
void Bullet::Move()
{
	float deltaTime = DeltaTime::GetInstance().GetDeltaTime();
	//�t�B�[���h�O�ɏo������ł�����


	nextPosition = VAdd(nextPosition, VScale(direction, speed * deltaTime));	//�����Ă�������Ɉړ�
	collisionSphere.Move(position);												//�����蔻�苅�ړ�
}

/// <summary>
/// �ړ��\��n�Ɏ��ۂɈړ�����
/// </summary>
void Bullet::MoveFinish()
{
	prevPosition = position;
	position = nextPosition;
	direction = nextDirection;

	// ���f���̈ʒu��ݒ�
	MV1SetPosition(modelHandle, position);

	// ���f���̌�����ݒ�
	MV1SetRotationYUseDir(modelHandle, direction, 0.0f);
}

/// <summary>
/// �I�u�W�F�N�g�𒆐S�ɉ�]
/// </summary>
void Bullet::RotationAboutObject(Mover* bullet, VECTOR objPos, int totalBullet)
{
	VECTOR objPosition = objPos;
	
	position.x = objPosition.x + NORMAL_FORWARD_DISTANCE * cosf(0.0f);
	position.z = objPosition.z + NORMAL_FORWARD_DISTANCE * sinf(1.0f);

}

/// <summary>
/// ���f���̌����𔭎˗p�ɐݒ�
/// </summary>
void Bullet::SetShootDirection()
{
	// ���˗p�p�x��ݒ�
	VECTOR newDirection;

	// ���f���̌�����ݒ�

}

/// <summary>
/// ���f���̌����� NORMAL ���ɖ߂�
/// </summary>
void Bullet::ResetDirection()
{
	// ���̊p�x�ɖ߂�

}

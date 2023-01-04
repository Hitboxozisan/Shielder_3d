#include "Pch.h"

#include "Bullet.h"

#include "ModelManager.h"

const float Bullet::NORMAL_SPEED   = 16.0f;
const float Bullet::SLOW_SPEED     = 8.0f;
const float Bullet::SCALE_BY_DIRECTION_FOR_CORRECTION = 1.0f;
const float Bullet::COLLIDE_RADIUS = 50.0f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Bullet::Bullet()
	:state(NONE)
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
	
	state = NORMAL;

	collisionSphere.localCenter = ZERO_VECTOR;
	collisionSphere.radius = COLLIDE_RADIUS;
	collisionSphere.worldCenter = position;

	SetToFrontOfEnemy(inPosition, inDirection);					// �G�l�~�[�̑O���Ɉʒu����

	MV1SetScale(modelHandle, VGet(0.5f, 0.5f, 0.2f));			// ���f���g��k��
	MV1SetRotationXYZ(modelHandle, VGet(0.0f, 1.5f, 0.0f));		// ���f���̌�����ݒ�
}

/// <summary>
/// �񊈐�������
/// </summary>
void Bullet::Deactivate()
{
	state = NONE;
}

/// <summary>
/// �X�V����
/// </summary>
/// <returns></returns>
bool Bullet::Update()
{
	//���݂��Ȃ��Ȃ珈�����Ȃ�
	if (state == NONE)
	{
		return false;
	}

	//�G�l�~�[�U�����ʏ틅�Ȃ�
	if (state == NORMAL)
	{
		speed = NORMAL_SPEED;
	}
	else
	{
		speed = SLOW_SPEED;
	}

	//�e�X�g�pdirection
	//direction = VGet(0.5f, 0.0f, 0.0f);

	//���ł���Ƃ��̏���
	if (state == NORMAL ||
		state == SLOW)
	{
		Move();
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
	if (state == NONE)
	{
		return;
	}

	MV1SetPosition(modelHandle, position);		// 3D���f���̃|�W�V�����ݒ�
	

	MV1DrawModel(modelHandle);					// 3D���f���̕`��

#ifdef DEBUG

	// �����蔻��f�o�b�N�`��
	DrawSphere3D(collisionSphere.worldCenter, collisionSphere.radius,
		8, GetColor(0, 255, 0), 0, FALSE);

#endif // DEBUG	
}

/// <summary>
/// 
/// </summary>
/// <param name="attackType"></param>
void Bullet::Shoot(int attackType)
{
	//�G�l�~�[�U�����ʏ�e�Ȃ�
	if (attackType == 1)		
	{
		state = NORMAL;
	}
	else if(attackType == 2)
	{
		state = SLOW;
	}
	
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

	position = VAdd(position, distanceToPlayer);
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
	if (state == NORMAL ||
		state == SLOW)
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
	state = NONE;
}

/// <summary>
/// �ړ�����
/// </summary>
void Bullet::Move()
{
	//�t�B�[���h�O�ɏo������ł�����


	position = VAdd(position, VScale(direction, speed));	//�����Ă�������Ɉړ�
	collisionSphere.Move(position);				//�����蔻�苅�ړ�
}

//----------------------------------------------------------------
// <�s��E�o�O>
// �E
// <note>
// �E���b�N�I�������f���̓��ߗ�0%���ƓG���B��邽�߃J�����̒��߂��A
// �@���̓��ߗ����グ��K�v������
//----------------------------------------------------------------

#include "Pch.h"
#include "Shield.h"
#include "Timer.h"
#include "EffectManager.h"
#include "DeltaTime.h"
#include "ModelManager.h"

const VECTOR Shield::INITIAL_SCALE					   = VGet(0.5f, 0.5f, 0.5f);
const float  Shield::MAX_TRUNK_POINT				   = 100.0f;
const float  Shield::SCALE_BY_DIRECTION_FOR_CORRECTION = 150.0f;
const float  Shield::JUST_DEFENSE_TIME				   = 0.1f;
const float  Shield::COLLIDE_RADIUS					   = 50.0f;
const float  Shield::COLLIDE_HEIGHT					   = 125.0f;
const float  Shield::INCREMENT_TRUNK_POINT			   = 10.0f;
const float  Shield::DECREMENT_TRUNK_POINT			   = 1.0f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Shield::Shield()
{
	// �����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Shield::~Shield()
{
	// �����Ȃ�
}

/// <summary>
/// ����������
/// </summary>
void Shield::Initialize(EffectManager* inEffectManager)
{
	effectManager = inEffectManager;

	trunkPoint = 0.0f;
	// ���f���̓ǂݍ���
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::SHIELD));
	MV1SetScale(modelHandle, INITIAL_SCALE);
}

/// <summary>
/// �I������
/// </summary>
void Shield::Finalize()
{

}

/// <summary>
/// ����������
/// </summary>
/// <param name="inPosition"></param>
/// <param name="inDirection"></param>
/// <param name="inPrevDirection"></param>
void Shield::Activate(const VECTOR& inPosition,
					  const VECTOR& inDirection, 
					  const VECTOR& inPrevDirection)
{
	state = State::DEPLOYMENT;

	position = inPosition;
	direction = inDirection;
	distanceToPlayer = VScale(inPrevDirection, SCALE_BY_DIRECTION_FOR_CORRECTION);

	collisionSphere.localCenter = ZERO_VECTOR;
	collisionSphere.worldCenter = position;
	collisionSphere.radius = COLLIDE_RADIUS;

	MV1SetPosition(modelHandle, position);					// ���f���̈ʒu��ݒ�
	MV1SetRotationYUseDir(modelHandle, direction, 0.0f);	// ���̌�����ݒ�

	pUpdate = &Shield::UpdateDeployment;
}

/// <summary>
/// �񊈐�������
/// </summary>
void Shield::Deactivate()
{
	state = State::NONE;
	elapsedtTime = 0.0f;
	pUpdate = nullptr;
}

/// <summary>
/// �X�V����
/// </summary>
void Shield::Update()
{
	// ���݂��Ȃ��Ȃ珈�����Ȃ�
	if (state == State::NONE)
	{
		return;
	}

	if (pUpdate != nullptr)
	{
		(this->*pUpdate)();		// ��Ԃ��Ƃ̍X�V����
	}

	collisionSphere.Move(position);
}

/// <summary>
/// �`�揈��
/// </summary>
void Shield::Draw()
{
	// ���݂��Ȃ��Ȃ珈�����Ȃ�
	if (state == State::NONE)
	{
		return;
	}

	// ���f���̕`��
	MV1DrawModel(modelHandle);

#ifdef DEBUG
	//�����蔻��f�o�b�N�`��
	//DrawSphere3D(collisionSphere.worldCenter, collisionSphere.radius,
		//32, GetColor(0, 255, 0), 0, FALSE);

#endif // DEBUG

}

/// <summary>
/// ���̃L�����N�^�[�ƐڐG����
/// </summary>
/// <param name="forceDirection"></param>
void Shield::HitOtherCharacter(float magnification)
{

	// "�W���X�g�K�[�h"���ǂ����ŃG�t�F�N�g��ύX����
	if (isJust())
	{
		// �K�[�h�G�t�F�N�g�𐶐�
		effectManager->CreateSparkEffect(position);
	}
	else
	{
		// �K�[�h�G�t�F�N�g�𐶐�
		effectManager->CreateSparkEffect(position);
	}

	// �ϋv�l�𑝉�������
	// �ő�l�܂ŒB�����ꍇ�͔j�󂷂�
	if (IncrementTrunkPoint(magnification))
	{
		state = State::DESTRUCTION;
		pUpdate = &Shield::UpdateDestruction;
	}
}

/// <summary>
/// �G�����˂����e�ƐڐG����
/// </summary>
/// <param name="magnification"></param>
void Shield::HitBullet(float magnification)
{
	// "�W���X�g�K�[�h"���ǂ����ŃG�t�F�N�g��ύX����
	if (isJust())
	{
		// �K�[�h�G�t�F�N�g�𐶐�
		effectManager->CreateSparkEffect(position);
	}
	else
	{
		// �K�[�h�G�t�F�N�g�𐶐�
		effectManager->CreateSparkEffect(position);
	}

	// �ϋv�l�𑝉�������
	// �ő�l�܂ŒB�����ꍇ�͔j�󂷂�
	if (IncrementTrunkPoint(magnification))
	{
		state = State::DESTRUCTION;
		pUpdate = &Shield::UpdateDestruction;
	}
}

/// <summary>
/// �����蔻�苅���a��Ԃ�
/// </summary>
/// <returns></returns>
const float Shield::GetCollideRadius()
{
	return collisionSphere.radius;
}

/// <summary>
/// "�W���X�g�K�[�h"���ǂ��� 
/// </summary>
/// <returns></returns>
const bool Shield::isJust()
{
	// �ݒ莞�Ԃ��Z�����"�W���X�g�K�[�h"�Ɣ��f����
	if (elapsedtTime <= JUST_DEFENSE_TIME)
	{
		return true;
	}

	return false;
}

/// <summary>
/// �ʒu���Z�b�g
/// </summary>
/// <param name="inPosition"></param>
/// <param name="inDirection"></param>
/// <param name="inPrevDirection"></param>
void Shield::SetShieldPosition(const VECTOR& inPosition, const VECTOR& inDirection, const VECTOR& inPrevDirection)
{
	position = inPosition;
	direction = inDirection;

	distanceToPlayer = VScale(direction, SCALE_BY_DIRECTION_FOR_CORRECTION);

	position = VAdd(position, distanceToPlayer);
	// �����蔻�苅�̍����𒲐߂���
	collisionSphere.worldCenter.y = COLLIDE_HEIGHT;
}

/// <summary>
/// ���ۂɈړ�����
/// </summary>
void Shield::MoveFinish()
{
	// ���f���̈ʒu��ݒ�
	MV1SetPosition(modelHandle, position);
	// ���f���̌�����ݒ�
	MV1SetRotationYUseDir(modelHandle, direction, 0.0f);
}

/// <summary>
/// DEPLOYMENT���X�V����
/// </summary>
void Shield::UpdateDeployment()
{
	elapsedtTime += DeltaTime::GetInstance().GetDeltaTime();
	MoveFinish();
}

/// <summary>
/// DESTRUCTION���X�V����
/// </summary>
void Shield::UpdateDestruction()
{
	if (DecrementTrunkPoint())
	{
		state = State::NONE;
	}
}

/// <summary>
///  �V�[���h�̑ϋv�l�𑝉�������
/// </summary>
/// <param name="magnification">�����{��</param>
/// <returns>�ő�l�܂ő��������i�j�󂳂ꂽ�j</returns>
bool Shield::IncrementTrunkPoint(float magnification)
{
	// �ϋv�l���U����ނ��Ƃ̔{���ɍ��킹�Č���������
	trunkPoint += INCREMENT_TRUNK_POINT * magnification;
	// �ϋv�l���ő�l�܂ł̑��������ꍇ�͒l���ő�l������Ȃ��悤�ɂ���
	if (trunkPoint >= MAX_TRUNK_POINT)
	{
		trunkPoint = MAX_TRUNK_POINT;
		return true;
	}

	return false;
}

/// <summary>
/// �V�[���h�̑ϋv�l������������
/// </summary>
/// <returns> 0 �ɂȂ���</returns>
bool Shield::DecrementTrunkPoint()
{
	// ������͏펞���葱������̂Ȃ̂� deltaTime ���g�p


	float deltaTime = DeltaTime::GetInstance().GetDeltaTime();
	// �l������������
	trunkPoint -= DECREMENT_TRUNK_POINT * deltaTime;
	// �l�� 0 �ɂȂ�����A����ȏ㌸��Ȃ��悤�ɂ���
	if (trunkPoint <= 0.0f)
	{
		trunkPoint = 0.0f;
		return true;
	}

	return false;
}

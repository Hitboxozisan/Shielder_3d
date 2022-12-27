#include "Pch.h"
#include "Boss.h"
#include "ModelManager.h"

const VECTOR Boss::INITIAL_POSITION  = VGet(500.0f, 0.0f, 500.0f);
const VECTOR Boss::INITIAL_DIRECTION = VGet(0.0f, 0.0f, -1.0f);
const VECTOR Boss::INITIAL_SCALE     = VGet(0.5f, 0.5f, 0.5f);

/// <summary>
/// �R���X�g���N�^
/// </summary>
Boss::Boss()
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

	// ������Ԃ� NORMAL �Ɂi��ɕʓr�s���؂�ւ��j
	state = State::ATTACK;
	pUpdate = &Boss::UpdateAttack;

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
}

/// <summary>
/// �`�揈��
/// </summary>
void Boss::Draw()
{
	// �`�悵�Ȃ��t���[���Ȃ�`�悵�Ȃ�
	if (state == State::DEAD)
	{
		return;
	}
	
	MV1DrawModel(modelHandle);
}

/// <summary>
/// �ړ��\��n�Ɏ��ۂɈړ�����
/// </summary>
void Boss::MoveFinish()
{
}

void Boss::UpdateAttack()
{
	
}

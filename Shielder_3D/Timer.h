#pragma once

/// <summary>
/// �^�C�}�[�N���X
/// </summary>
class Timer
{
public:
	Timer(float limitTime);
	~Timer();

	void Update(float deltaTime);		// �X�V����
	void Reset();						// �^�C�}�[�̃��Z�b�g
	bool IsTimeout() const;				// �^�C���A�E�g��

private:
	float time;			// ���݂̎���
	float limitTime;	// ��������
};


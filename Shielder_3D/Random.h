#pragma once
class Random
{
public:
	Random();
	~Random();
	
	static Random& GetInstance();						// �C���X�^���X�̎擾
	int   GetRandomInt(int min, int max);				// �����_����int�l��Ԃ�
	float GetRandomFloat(float min, float max);			// �����_����float�l��Ԃ�
private:
	
};


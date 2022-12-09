#pragma once
class DebugMenu
{
public:
	DebugMenu();
	~DebugMenu();

	void Initialize();
	void Update();
	void Draw();
	
	void DrawCameraPosition(VECTOR position);		// �J�����̌��݈ʒu��`��
	void DrawCameraDirection(VECTOR direction);		// �J�����̌�����`��

private:

	int displayCount;					// �f�o�b�O�\������

	static const int FIRST_POSITION_X;		// �擪�ʒu_X
	static const int FIRST_POSITION_Y;		// �擪�ʒu_Y

};


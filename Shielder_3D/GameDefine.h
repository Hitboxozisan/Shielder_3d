#pragma once

extern const bool IS_WINDOW_MODE;		// �E�B���h�E���[�h��
                                           
extern const int  SCREEN_WIDTH;			// �E�B���h�E�̕�
extern const int  SCREEN_HEIGHT;		// �E�B���h�E�̍���
extern const int  COLOR_BIT_DEPTH;      // �J���[�r�b�g��
                        
extern const int SCREEN_LEFTMOST;		// ��ʍ��[���W
extern const int SCREEN_RIGHTMOST;		// ��ʉE�[���W
                                           
extern const int SCREEN_CENTER;		    // ��ʒ��S���W
extern const int POSITION_CENTER;       // �X�e�[�W���S���W

extern const float FIELD_POSITION_NORTH;    // �X�e�[�W�k�[
extern const float FIELD_POSITION_SOUTH;    // �X�e�[�W��[
extern const float FIELD_POSITION_EAST;     // �X�e�[�W���[
extern const float FIELD_POSITION_WEST;     // �X�e�[�W���[
                                           
extern const VECTOR ZERO_VECTOR;		// �[���x�N�g��

extern const VECTOR PROGRESS;           // �O�i
extern const VECTOR RECESSION;          // ���
extern const VECTOR UP;                 // �㏸
extern const VECTOR DOWN;               // ���~
extern const VECTOR RIGHT;              // �E�ړ�
extern const VECTOR LEFT;               // ���ړ�

// �t�B�[���h�[
//1450.0f, 1450.0f;

template <typename T>
inline void SafeDelete(T*& p)   // �|�C���^�̎Q�Ɠn��
{
    // NULL�`�F�b�N�͕s�v
    delete (p);
    (p) = nullptr;

}
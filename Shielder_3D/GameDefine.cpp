#include "Pch.h"

#ifdef DEBUG
const bool IS_WINDOW_MODE = true;
#else
const bool IS_WINDOW_MODE = false;
#endif

const int  SCREEN_WIDTH = 1920;						// �E�B���h�E�̕�
const int  SCREEN_HEIGHT = 1080;					// �E�B���h�E�̍���
													   
const int SCREEN_LEFTMOST = 1150;					// ��ʍ��[���W
const int SCREEN_RIGHTMOST = 2850;					// ��ʉE�[���W

// ��ʒ��S���W
const int SCREEN_CENTER = ((SCREEN_RIGHTMOST - SCREEN_LEFTMOST) / 2) + SCREEN_LEFTMOST;
// �X�e�[�W���S���W
const int POSITION_CENTER = (SCREEN_RIGHTMOST - SCREEN_LEFTMOST) / 2;

const VECTOR ZERO_VECTOR = { 0.0f, 0.0f, 0.0f };	// �[���x�N�g��


const VECTOR RIGHT = { 1.0f, 0.0f, 0.0f };			// �E
const VECTOR LEFT = { -1.0f, 0.0f, 0.0f };			// ��
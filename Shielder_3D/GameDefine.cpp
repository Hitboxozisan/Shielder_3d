#include "Pch.h"

#ifdef DEBUG
const bool IS_WINDOW_MODE = true;
#else
const bool IS_WINDOW_MODE = false;
#endif

const int  SCREEN_WIDTH = 1920;						// �E�B���h�E�̕�
const int  SCREEN_HEIGHT = 1080;					// �E�B���h�E�̍���
const int  COLOR_BIT_DEPTH = 32;					// �J���[�r�b�g��
													   
const int SCREEN_LEFTMOST = 1150;					// ��ʍ��[���W
const int SCREEN_RIGHTMOST = 2850;					// ��ʉE�[���W

const float FIELD_POSITION_NORTH = 1450.0f;		    // �X�e�[�W�k�[
const float FIELD_POSITION_SOUTH = -1450.0f;	    // �X�e�[�W��[
const float FIELD_POSITION_EAST = 1450.0f;		    // �X�e�[�W���[
const float FIELD_POSITION_WEST = -1450.0f;		    // �X�e�[�W���[

// ��ʒ��S���W
const int SCREEN_CENTER = ((SCREEN_RIGHTMOST - SCREEN_LEFTMOST) / 2) + SCREEN_LEFTMOST;
// �X�e�[�W���S���W
const int POSITION_CENTER = (SCREEN_RIGHTMOST - SCREEN_LEFTMOST) / 2;

const VECTOR ZERO_VECTOR = { 0.0f, 0.0f, 0.0f };	// �[���x�N�g��

const VECTOR PROGRESS  = {  0.0f,  0.0f,  1.0f };		// �O
const VECTOR RECESSION = {  0.0f,  0.0f, -1.0f };		// ��
const VECTOR UP		   = {  0.0f,  0.0f,  1.0f };		// ��
const VECTOR DOWN	   = {  0.0f,  0.0f, -1.0f };		// ��
const VECTOR RIGHT     = {  1.0f,  0.0f,  0.0f };		// �E
const VECTOR LEFT	   = { -1.0f,  0.0f,  0.0f };		// ��
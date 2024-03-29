#include "Pch.h"

#ifdef DEBUG
const bool IS_WINDOW_MODE = true;
#else
const bool IS_WINDOW_MODE = false;
#endif

const int  SCREEN_WIDTH = 1920;						// ウィンドウの幅
const int  SCREEN_HEIGHT = 1080;					// ウィンドウの高さ
const int  COLOR_BIT_DEPTH = 32;					// カラービット数
													   
const int SCREEN_LEFTMOST = 1150;					// 画面左端座標
const int SCREEN_RIGHTMOST = 2850;					// 画面右端座標

const float FIELD_POSITION_NORTH = 1450.0f;		    // ステージ北端
const float FIELD_POSITION_SOUTH = -1450.0f;	    // ステージ南端
const float FIELD_POSITION_EAST = 1450.0f;		    // ステージ西端
const float FIELD_POSITION_WEST = -1450.0f;		    // ステージ東端

// 画面中心座標
const int SCREEN_CENTER = ((SCREEN_RIGHTMOST - SCREEN_LEFTMOST) / 2) + SCREEN_LEFTMOST;
// ステージ中心座標
const int POSITION_CENTER = (SCREEN_RIGHTMOST - SCREEN_LEFTMOST) / 2;

const VECTOR ZERO_VECTOR = { 0.0f, 0.0f, 0.0f };	// ゼロベクトル

const VECTOR PROGRESS  = {  0.0f,  0.0f,  1.0f };		// 前
const VECTOR RECESSION = {  0.0f,  0.0f, -1.0f };		// 後
const VECTOR UP		   = {  0.0f,  0.0f,  1.0f };		// 上
const VECTOR DOWN	   = {  0.0f,  0.0f, -1.0f };		// 下
const VECTOR RIGHT     = {  1.0f,  0.0f,  0.0f };		// 右
const VECTOR LEFT	   = { -1.0f,  0.0f,  0.0f };		// 左
#pragma once

extern const bool IS_WINDOW_MODE;		// ウィンドウモードか
                                           
extern const int  SCREEN_WIDTH;			// ウィンドウの幅
extern const int  SCREEN_HEIGHT;		// ウィンドウの高さ
extern const int  COLOR_BIT_DEPTH;      // カラービット数
                        
extern const int SCREEN_LEFTMOST;		// 画面左端座標
extern const int SCREEN_RIGHTMOST;		// 画面右端座標
                                           
extern const int SCREEN_CENTER;		    // 画面中心座標
extern const int POSITION_CENTER;       // ステージ中心座標

extern const float FIELD_POSITION_NORTH;    // ステージ北端
extern const float FIELD_POSITION_SOUTH;    // ステージ南端
extern const float FIELD_POSITION_EAST;     // ステージ西端
extern const float FIELD_POSITION_WEST;     // ステージ東端
                                           
extern const VECTOR ZERO_VECTOR;		// ゼロベクトル

extern const VECTOR PROGRESS;           // 前進
extern const VECTOR RECESSION;          // 後退
extern const VECTOR UP;                 // 上昇
extern const VECTOR DOWN;               // 下降
extern const VECTOR RIGHT;              // 右移動
extern const VECTOR LEFT;               // 左移動

// フィールド端
//1450.0f, 1450.0f;

template <typename T>
inline void SafeDelete(T*& p)   // ポインタの参照渡し
{
    // NULLチェックは不要
    delete (p);
    (p) = nullptr;

}
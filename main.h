//=============================================================================
//
// メイン処理 [main.h]
// Author : TANEKAWA RIKU
//
//=============================================================================
#ifndef _MAIN_H_// このマクロ定義がされていなかったら
#define _MAIN_H_// 2重インクルード防止のマクロ定義

#include<windows.h>
#include "d3dx9.h"												// 描画処理に必要
#define DIRECTINPUT_VERSION (0x0800)							// ビルド時の警告対処用マクロ
#include "dinput.h"												// 入力処理に必要
#include "Xinput.h"												// ジョイパッド処理に必要
#include "xaudio2.h"											// サウンド処理に必要
#include <array>
#include <string>

// ライブラリのリンク
#pragma comment(lib,"d3d9.lib")									// 描画処理に必要
#pragma comment(lib,"d3dx9.lib")								// [d3d9.lib]の拡張ライブラリ
#pragma comment(lib,"dxguid.lib")								// DirectXコンポーネント(部品)使用に必要
#pragma comment(lib,"winmm.lib")								// システム時刻取得に必要
#pragma comment(lib,"dinput8.lib")								// 入力処理に必要
#pragma comment(lib,"xinput.lib")								// ジョイパッド処理に必要

//#pragma comment(lib,"BulletCollision.lib")
//#pragma comment(lib,"BulletDynamics.lib")
//#pragma comment(lib,"LinearMath.lib")

// マクロ定義
#define CLASS_NAME "WindowClass"								// ウィンドウクラスの名前
#define WINDOW_NAME "Ruins Good!"								// ウィンドウの名前(キャプションに表示)
#define SCREEN_WIDTH (1280)										// ウィンドウの幅
#define SCREEN_HEIGHT (720)										// ウィンドウの高さ
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)	//座標・法線・カラー・テクスチャ

// 初期化用マクロ定義
#define INIT_VEC3 (D3DXVECTOR3(0.0f,0.0f,0.0f))

// 
using namespace std;

// 画面の種類
typedef enum
{
	MODE_TITLE = 0,												// タイトル画面
	MODE_SELECT,												// モードセレクト画面
	MODE_TUTORIAL,												// チュートリアル画面
	MODE_GAME,													// ゲーム画面
	MODE_RESULT,												// リザルト画面
	MODE_RANKING,												// ランキング画面
	MODE_MAX
}MODE;

// 頂点情報[2D]の構造体を定義
typedef struct
{
	D3DXVECTOR3 pos;											// 頂点座標
	float rhw;													// 座標変換用係数
	D3DCOLOR col;												// 座標カラー
	D3DXVECTOR2 tex;											// テクスチャ座標
}VERTEX_2D;

//頂点情報[3D]の構造体を定義
typedef struct
{
	D3DXVECTOR3 pos;											//頂点座標
	D3DXVECTOR3 nor;											//法線ベクトル
	D3DCOLOR col;												//座標カラー
	D3DXVECTOR2 tex;											//テクスチャ座標
}VERTEX_3D;

// プロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//void ToggleFullscreen(HWND hWnd);// ウィンドウをフルスクリーン
//bool GetFullScreen(void);

#endif
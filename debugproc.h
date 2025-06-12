//=============================================================================
//
// デバッグ表示処理 [debugproc.h]
// Author : TANEKAWA RIKU
//
//=============================================================================
#ifndef _DEBUGPROC_H_
#define _DEBUGPROC_H_

#include "main.h"

// デバッグクラス
class CDebugProc
{
public:
	CDebugProc();
	~CDebugProc();

	void Init(void);
	void Uninit(void);
	static void Print(const char* fmt, ...);
	static void Draw(D3DXCOLOR col,int posX,int posY);

private:
	static LPD3DXFONT m_pFont;	// フォントへのポインタ
	static char m_aStr[1024];	// 文字列を格納するバッファ

};
#endif
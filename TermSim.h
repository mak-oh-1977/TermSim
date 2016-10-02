
// TermSim.h : TermSim アプリケーションのメイン ヘッダー ファイル
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"       // メイン シンボル


// CTermSimApp:
// このクラスの実装については、TermSim.cpp を参照してください。
//

class CTermSimApp : public CWinApp
{
public:
	CTermSimApp();


// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CTermSimApp theApp;

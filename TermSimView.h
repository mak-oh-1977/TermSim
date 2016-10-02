
// TermSimView.h : CTermSimView クラスのインターフェイス
//


#pragma once
#include "clientsock.h"


class CTermSimView : public CEditView
{
protected: // シリアル化からのみ作成します。
	CTermSimView();
	DECLARE_DYNCREATE(CTermSimView)

// 属性
public:
	CTermSimDoc* GetDocument() const;

// 操作
public:

// オーバーライド
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 実装
public:
	virtual ~CTermSimView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成された、メッセージ割り当て関数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSend();
	void OutDump(void* p, int iLen);
	void Output(const CString& s);
private:
	CClientSock m_sock;

public:
	void SendData(void);
};

#ifndef _DEBUG  // TermSimView.cpp のデバッグ バージョン
inline CTermSimDoc* CTermSimView::GetDocument() const
   { return reinterpret_cast<CTermSimDoc*>(m_pDocument); }
#endif


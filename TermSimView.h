
// TermSimView.h : CTermSimView �N���X�̃C���^�[�t�F�C�X
//


#pragma once
#include "clientsock.h"


class CTermSimView : public CEditView
{
protected: // �V���A��������̂ݍ쐬���܂��B
	CTermSimView();
	DECLARE_DYNCREATE(CTermSimView)

// ����
public:
	CTermSimDoc* GetDocument() const;

// ����
public:

// �I�[�o�[���C�h
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ����
public:
	virtual ~CTermSimView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
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

#ifndef _DEBUG  // TermSimView.cpp �̃f�o�b�O �o�[�W����
inline CTermSimDoc* CTermSimView::GetDocument() const
   { return reinterpret_cast<CTermSimDoc*>(m_pDocument); }
#endif


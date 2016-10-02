
// TermSimView.cpp : CTermSimView クラスの実装
//

#include "stdafx.h"
#include "TermSim.h"

#include "TermSimDoc.h"
#include "TermSimView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTermSimView

IMPLEMENT_DYNCREATE(CTermSimView, CEditView)

BEGIN_MESSAGE_MAP(CTermSimView, CEditView)
	ON_COMMAND(IDR_SEND, &CTermSimView::OnSend)
END_MESSAGE_MAP()

// CTermSimView コンストラクション/デストラクション

CTermSimView::CTermSimView()
{
	// TODO: 構築コードをここに追加します。

}

CTermSimView::~CTermSimView()
{
}

BOOL CTermSimView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// ワード ラップを使用可能にします

	return bPreCreated;
}


// CTermSimView 診断

#ifdef _DEBUG
void CTermSimView::AssertValid() const
{
	CEditView::AssertValid();
}

void CTermSimView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CTermSimDoc* CTermSimView::GetDocument() const // デバッグ以外のバージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTermSimDoc)));
	return (CTermSimDoc*)m_pDocument;
}
#endif //_DEBUG


// CTermSimView メッセージ ハンドラ

void CTermSimView::OnSend()
{
	SendData();
}

void CTermSimView::OutDump(void* p, int iLen)
{
	BYTE* pby = (BYTE*)p;
	CString sOut("");
	
	sOut = "===================================================================\r\n";

	CString sLine;
	sLine = "       ";
	for(int i = 0; i < 16; i++)
	{
		CString s;
		s.Format(_T("+%X "), i);
		sLine += s;

	}
	sOut += sLine;
	
	sLine = "";
	int i;
	for(i = 0; i < iLen; i++)
	{
		if ((i % 16) == 0)
		{
			sOut += sLine;

			sLine.Format(_T("\r\n%06X "), i);
			
		}
		CString s;
		s.Format(_T("%02x "), pby[i]);
		sLine += s;
	}
	while ((i % 16) != 0)
	{
		sLine += "   ";
	
		i++;
	}
	sOut += sLine;
	sOut += "\r\n";
	
	CString s;
	s.Format(_T("Dump Length = %d bytes\r\n\r\n"), iLen);
	sOut += s;

	Output(sOut);
}

void CTermSimView::Output(const CString& s)
{
	int nLen = GetWindowTextLength();
	SetFocus();
	GetEditCtrl().SetSel(nLen, nLen);
	GetEditCtrl().ReplaceSel(s);
}


void CTermSimView::SendData(void)
{
	CString sIp("localhost");

	CString         filter("TRC Files (*.trc)|*.trc||");
	CFileDialog     dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, filter);

	if (dlg.DoModal() != IDOK)
	{
		return;
	}
	

	
	CFile cf;
	cf.Open(dlg.GetPathName(), CFile::modeRead);
	BYTE pbyData[100000];
	int len;
	len = cf.Read(pbyData, sizeof(pbyData));
	cf.Close();
	
	OutDump(pbyData, len);	

	m_sock.Open("localhost", 9003);
	
	m_sock.Send(pbyData, len);

	len = m_sock.Recv(pbyData, sizeof(pbyData));
	
	OutDump(pbyData, len);
	
	m_sock.Close();
}


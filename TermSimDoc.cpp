
// TermSimDoc.cpp : CTermSimDoc クラスの実装
//

#include "stdafx.h"
#include "TermSim.h"

#include "TermSimDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTermSimDoc

IMPLEMENT_DYNCREATE(CTermSimDoc, CDocument)

BEGIN_MESSAGE_MAP(CTermSimDoc, CDocument)
END_MESSAGE_MAP()


// CTermSimDoc コンストラクション/デストラクション

CTermSimDoc::CTermSimDoc()
{
	// TODO: この位置に 1 度だけ呼ばれる構築用のコードを追加してください。

}

CTermSimDoc::~CTermSimDoc()
{
}

BOOL CTermSimDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	reinterpret_cast<CEditView*>(m_viewList.GetHead())->SetWindowText(NULL);

	// TODO: この位置に再初期化処理を追加してください。
	// (SDI ドキュメントはこのドキュメントを再利用します。)

	return TRUE;
}




// CTermSimDoc シリアル化

void CTermSimDoc::Serialize(CArchive& ar)
{
	// CEditView は、すべてのシリアル化を処理するエディット コントロールを含んでいます。
	reinterpret_cast<CEditView*>(m_viewList.GetHead())->SerializeRaw(ar);
}


// CTermSimDoc 診断

#ifdef _DEBUG
void CTermSimDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTermSimDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CTermSimDoc コマンド

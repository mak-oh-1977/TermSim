
// TermSimDoc.cpp : CTermSimDoc �N���X�̎���
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


// CTermSimDoc �R���X�g���N�V����/�f�X�g���N�V����

CTermSimDoc::CTermSimDoc()
{
	// TODO: ���̈ʒu�� 1 �x�����Ă΂��\�z�p�̃R�[�h��ǉ����Ă��������B

}

CTermSimDoc::~CTermSimDoc()
{
}

BOOL CTermSimDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	reinterpret_cast<CEditView*>(m_viewList.GetHead())->SetWindowText(NULL);

	// TODO: ���̈ʒu�ɍď�����������ǉ����Ă��������B
	// (SDI �h�L�������g�͂��̃h�L�������g���ė��p���܂��B)

	return TRUE;
}




// CTermSimDoc �V���A����

void CTermSimDoc::Serialize(CArchive& ar)
{
	// CEditView �́A���ׂẴV���A��������������G�f�B�b�g �R���g���[�����܂�ł��܂��B
	reinterpret_cast<CEditView*>(m_viewList.GetHead())->SerializeRaw(ar);
}


// CTermSimDoc �f�f

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


// CTermSimDoc �R�}���h

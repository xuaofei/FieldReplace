// DropFileEdit.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FieldReplace.h"
#include "DropFileEdit.h"


// CDropFileEdit

IMPLEMENT_DYNAMIC(CDropFileEdit, CEdit)

CDropFileEdit::CDropFileEdit()
{

}

CDropFileEdit::~CDropFileEdit()
{
}


BEGIN_MESSAGE_MAP(CDropFileEdit, CEdit)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()



// CDropFileEdit ��Ϣ�������




void CDropFileEdit::OnDropFiles(HDROP hDropInfo)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CEdit::OnDropFiles(hDropInfo);
}

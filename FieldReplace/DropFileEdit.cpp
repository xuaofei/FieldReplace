// DropFileEdit.cpp : 实现文件
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



// CDropFileEdit 消息处理程序




void CDropFileEdit::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CEdit::OnDropFiles(hDropInfo);
}


// FieldReplace.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CFieldReplaceApp: 
// �йش����ʵ�֣������ FieldReplace.cpp
//

class CFieldReplaceApp : public CWinApp
{
public:
	CFieldReplaceApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CFieldReplaceApp theApp;
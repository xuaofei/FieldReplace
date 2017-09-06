#pragma once


// CDropFileEdit

class CDropFileEdit : public CEdit
{
	DECLARE_DYNAMIC(CDropFileEdit)

public:
	CDropFileEdit();
	virtual ~CDropFileEdit();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
};



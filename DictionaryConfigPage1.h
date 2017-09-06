#pragma once


// CDictionaryConfigDialog �Ի���
#include <vector>
#include <string>
using namespace std;

class CDictionaryConfigPage1 : public CDialogEx
{
	DECLARE_DYNAMIC(CDictionaryConfigPage)

public:
	CDictionaryConfigPage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDictionaryConfigPage();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DICTIONARYCONFIGDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnAddDictionaryTableFile();
	afx_msg void OnStartAddDictionary();

private:
	void splitString(const std::wstring& s, std::vector<std::wstring>& v, const std::wstring& c);
	wstring Ansi2WChar(LPCSTR pszSrc, int nLen);
public:
	afx_msg void OnDestroy();
	afx_msg void OnSearchPhrase();
};

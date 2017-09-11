#pragma once


// CPhraseReplacePage 对话框
#include <fstream>  
#include <string>  
#include <iostream>
#include <vector>
using namespace std;
class CPhraseReplacePage : public CDialogEx
{
	DECLARE_DYNAMIC(CPhraseReplacePage)

public:
	CPhraseReplacePage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPhraseReplacePage();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PHRASEREPLACE_DIALOG
	};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBnClickedCancel();


private:
	static wstring Ansi2WChar(LPCSTR pszSrc, int nLen);
	static std::string WChar2Ansi(LPCWSTR pwszSrc);

	CString GetModuleDir();
	void FindPhraseFile(CString strFoldername, vector<CString> &phrases);
	void PhraseReplace(wstring &phrase, wstring &replacedPhrase);

	CString m_ArticleDir;
	CString m_ReplacedArticleDir;

	CString m_ArticleDirPath;
	CString m_ReplacedArticleDirPath;
};

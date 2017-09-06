#pragma once
#include "afxcmn.h"
#include <fstream>  
#include <string>  
#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include "afxwin.h"
using namespace std;

// CDictionaryConfigPage 对话框

class CDictionaryConfigPage : public CDialogEx
{
	DECLARE_DYNAMIC(CDictionaryConfigPage)

public:
	CDictionaryConfigPage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDictionaryConfigPage();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DICTIONARYCONFIG_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnAddDictionaryTableFile();
	afx_msg void OnAddOneDictionary();
	afx_msg void OnLvnGetdispinfoList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSearchPhrase();
	afx_msg void OnSaveDictionary();
	afx_msg void OnOK();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnEnChangeSearchphrase();
private:
	//static bool compare(const CChineseCharacters* a, const CChineseCharacters *b);
	void GetPinYin(wstring& Chinese, wstring& PinYin);
	void splitString(const std::wstring& s, std::vector<std::wstring>& v, const std::wstring& c);
	static wstring Ansi2WChar(LPCSTR pszSrc, int nLen);
	static std::string WChar2Ansi(LPCWSTR pwszSrc);


	CListCtrl m_SearchDictionaryList;
	vector<wstring> m_lines;
	vector<wstring> m_SearchOriginalPhrase;
	vector<wstring> m_SearchNewPhrase;
	CEdit m_EditSearchPhrase;
	CEdit m_EditAddDirtionaryForOriginalPhrase;
	CEdit m_EditAddDirtionaryForNewPhrase;
};

// DictionaryConfigDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "FieldReplace.h"
#include "DictionaryConfigPage.h"
#include "afxdialogex.h"
#include <atlconv.h>
#include <fstream>  
#include <string>  
#include <iostream>
#include <vector>
using namespace std;

// CDictionaryConfigDialog 对话框

IMPLEMENT_DYNAMIC(CDictionaryConfigPage, CDialogEx)

CDictionaryConfigPage::CDictionaryConfigPage(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DICTIONARYCONFIGDIALOG, pParent)
{

}

CDictionaryConfigPage::~CDictionaryConfigPage()
{
}

void CDictionaryConfigPage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDictionaryConfigPage, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDictionaryConfigPage::OnAddDictionaryTableFile)
	ON_BN_CLICKED(IDC_BUTTON2, &CDictionaryConfigPage::OnStartAddDictionary)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON3, &CDictionaryConfigPage::OnSearchPhrase)
END_MESSAGE_MAP()


// CDictionaryConfigDialog 消息处理程序


void CDictionaryConfigPage::OnAddDictionaryTableFile()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strFile = _T("");

	CFileDialog    dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("Describe Files (*.txt)|*.txt|All Files (*.*)|*.*||"), NULL);

	if (dlgFile.DoModal())
	{
		strFile = dlgFile.GetPathName();
		CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT1);
		pEdit->SetWindowTextW(strFile);
	}
}


void CDictionaryConfigPage::OnStartAddDictionary()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strFile = _T("");
	GetDlgItem(IDC_EDIT1)->GetWindowTextW(strFile);
	//USES_CONVERSION;
	//string strFilePath = W2A(strFile);

	ifstream in(strFile);
	vector<wstring> lines;
	lines.reserve(10000 * 25);
	string line;

	if (in) // 有该文件  
	{
		while (getline(in, line)) // line中不包括每行的换行符  
		{
			std::wstring wLine = Ansi2WChar(line.c_str(), line.size());
			lines.push_back(wLine);
		}
	}
	//不存储到lines,用时6秒钟
	//存储到lines,用时13秒钟

	CListCtrl *list = (CListCtrl *)GetDlgItem(IDC_LIST1);
	LONG styles;
	styles = GetWindowLong(list->m_hWnd, GWL_STYLE);
	SetWindowLong(list->m_hWnd, GWL_STYLE, styles);
	CRect rect;
	list->GetClientRect(&rect);
	list->MoveWindow(rect.left, 200, 600, 200);
	list->GetClientRect(&rect);
	int iLength = rect.Width();

	list->SetExtendedStyle(list->GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	list->InsertColumn(0, _T("编号"), LVCFMT_LEFT,200);
	list->InsertColumn(1, _T("频率(Hz)"), LVCFMT_LEFT,200);

	//使用47秒钟
	for (size_t i = 0; i < lines.size(); i++)
	{
		//获取首字结构体
		wstring splitString = L"=";
		vector<std::wstring> vecString;
	//	vecString.clear();
		this->splitString(lines[i], vecString, splitString);
		if (vecString.size() == 2)
		{
			CPhraseManager::GetInstance()->addOnePhrase(vecString[0], vecString[1]);
		}
		list->InsertItem(i, vecString[0].c_str());// 插入行
		list->SetItemText(i, 1, vecString[1].c_str());
	}
}


void CDictionaryConfigPage::splitString(const std::wstring& s, std::vector<std::wstring>& v, const std::wstring& c)
{
	std::wstring::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while (std::wstring::npos != pos2)
	{
		v.push_back(s.substr(pos1, pos2 - pos1));

		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}

	if (pos1 != s.length())
		v.push_back(s.substr(pos1));
}

std::wstring CDictionaryConfigPage::Ansi2WChar(LPCSTR pszSrc, int nLen)

{
	int nSize = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)pszSrc, nLen, 0, 0);
	if (nSize <= 0) return NULL;

	WCHAR *pwszDst = new WCHAR[nSize + 1];
	if (NULL == pwszDst) return NULL;

	MultiByteToWideChar(CP_ACP, 0, (LPCSTR)pszSrc, nLen, pwszDst, nSize);
	pwszDst[nSize] = 0;

	if (pwszDst[0] == 0xFEFF) // skip Oxfeff  
		for (int i = 0; i < nSize; i++)
			pwszDst[i] = pwszDst[i + 1];

	wstring wcharString(pwszDst);
	delete pwszDst;

	return wcharString;
}

void CDictionaryConfigPage::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	CPhraseManager::ReleaseInstance();
}


void CDictionaryConfigPage::OnSearchPhrase()
{
	// TODO: 在此添加控件通知处理程序代码

	//CString strFile = _T("");
	//GetDlgItem(IDC_SEARCHPHRASE)->GetWindowTextW(strFile);
	//wstring wstrFile(strFile);
	//CPhraseManager::GetInstance()->findFristChineseCharacters(wstrFile);
}

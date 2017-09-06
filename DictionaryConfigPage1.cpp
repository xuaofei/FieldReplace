// DictionaryConfigDialog.cpp : ʵ���ļ�
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

// CDictionaryConfigDialog �Ի���

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


// CDictionaryConfigDialog ��Ϣ�������


void CDictionaryConfigPage::OnAddDictionaryTableFile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strFile = _T("");
	GetDlgItem(IDC_EDIT1)->GetWindowTextW(strFile);
	//USES_CONVERSION;
	//string strFilePath = W2A(strFile);

	ifstream in(strFile);
	vector<wstring> lines;
	lines.reserve(10000 * 25);
	string line;

	if (in) // �и��ļ�  
	{
		while (getline(in, line)) // line�в�����ÿ�еĻ��з�  
		{
			std::wstring wLine = Ansi2WChar(line.c_str(), line.size());
			lines.push_back(wLine);
		}
	}
	//���洢��lines,��ʱ6����
	//�洢��lines,��ʱ13����

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
	list->InsertColumn(0, _T("���"), LVCFMT_LEFT,200);
	list->InsertColumn(1, _T("Ƶ��(Hz)"), LVCFMT_LEFT,200);

	//ʹ��47����
	for (size_t i = 0; i < lines.size(); i++)
	{
		//��ȡ���ֽṹ��
		wstring splitString = L"=";
		vector<std::wstring> vecString;
	//	vecString.clear();
		this->splitString(lines[i], vecString, splitString);
		if (vecString.size() == 2)
		{
			CPhraseManager::GetInstance()->addOnePhrase(vecString[0], vecString[1]);
		}
		list->InsertItem(i, vecString[0].c_str());// ������
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

	// TODO: �ڴ˴������Ϣ����������
	CPhraseManager::ReleaseInstance();
}


void CDictionaryConfigPage::OnSearchPhrase()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//CString strFile = _T("");
	//GetDlgItem(IDC_SEARCHPHRASE)->GetWindowTextW(strFile);
	//wstring wstrFile(strFile);
	//CPhraseManager::GetInstance()->findFristChineseCharacters(wstrFile);
}

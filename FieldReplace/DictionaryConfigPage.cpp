// DictionaryConfigPage.cpp : 实现文件
//

#include "stdafx.h"
#include "FieldReplace.h"
#include "DictionaryConfigPage.h"
#include "PhraseManager.h"
#include "afxdialogex.h"

// CDictionaryConfigPage 对话框

IMPLEMENT_DYNAMIC(CDictionaryConfigPage, CDialogEx)

CDictionaryConfigPage::CDictionaryConfigPage(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DICTIONARYCONFIG_DIALOG, pParent)
{
	m_lines.reserve(10000 * 30);
	m_SearchOriginalPhrase.reserve(1000);
	m_SearchNewPhrase.reserve(1000);

	m_DictionaryDir = L"DictionaryDir";
	m_DortedDictionaryDir = L"DortedDictionaryDir";
}

CDictionaryConfigPage::~CDictionaryConfigPage()
{
}

void CDictionaryConfigPage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_SearchDictionaryList);
	DDX_Control(pDX, IDC_SEARCHPHRASE, m_EditSearchPhrase);
	DDX_Control(pDX, IDC_EDIT3, m_EditAddDirtionaryForOriginalPhrase);
	DDX_Control(pDX, IDC_EDIT4, m_EditAddDirtionaryForNewPhrase);
}


BEGIN_MESSAGE_MAP(CDictionaryConfigPage, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDictionaryConfigPage::OnAddDictionaryTableFile)
	ON_BN_CLICKED(IDC_BUTTON2, &CDictionaryConfigPage::OnAddOneDictionary)
	ON_NOTIFY(LVN_GETDISPINFO, IDC_LIST1, &CDictionaryConfigPage::OnLvnGetdispinfoList)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON3, &CDictionaryConfigPage::OnSearchPhrase)
//	ON_COMMAND(IDOK, &CDictionaryConfigPage::OnIdok)
ON_COMMAND(IDOK, &CDictionaryConfigPage::OnOK)
ON_EN_CHANGE(IDC_SEARCHPHRASE, &CDictionaryConfigPage::OnEnChangeSearchphrase)
END_MESSAGE_MAP()


// CDictionaryConfigPage 消息处理程序


void CDictionaryConfigPage::OnAddDictionaryTableFile()
{

}


void CDictionaryConfigPage::OnAddOneDictionary()
{
	CString originalPhrase = _T(""); 
	CString newPhrase = _T("");
	m_EditAddDirtionaryForOriginalPhrase.GetWindowTextW(originalPhrase);
	m_EditAddDirtionaryForNewPhrase.GetWindowTextW(newPhrase);

	wstring wOriginalPhrase(originalPhrase);
	wstring wNewPhrase(newPhrase);
	 
	if (wOriginalPhrase.empty() || wNewPhrase.empty())
	{
		return;
	}

	vector<CChineseCharacters*> vecChineseCharacters;
	CPhraseManager::GetInstance()->FindPhrase(wOriginalPhrase, vecChineseCharacters);
	if (!vecChineseCharacters.empty())
	{
		//已经有相同的原词组，替换新词组
		auto iter = vecChineseCharacters.rbegin();
		(*iter)->replaceString = wNewPhrase;
		return;
	}

	wstring newDirtionary(wOriginalPhrase + CPhraseManager::GetInstance()->getSeparator() + wNewPhrase);
	m_lines.push_back(newDirtionary);


	if (m_EditSearchPhrase.GetWindowTextLengthW() == 0)
	{
		m_SearchDictionaryList.SetItemCount(m_lines.size());
		m_SearchDictionaryList.EnsureVisible(m_lines.size() - 1, FALSE);
		m_SearchDictionaryList.SetItemState(m_lines.size() - 1, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
	}
}


void CDictionaryConfigPage::LoadDictionary()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	//CString strFile = _T("");

	//CFileDialog    dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("Describe Files (*.txt)|*.txt|All Files (*.*)|*.*||"), NULL);

	//if (dlgFile.DoModal())
	//{
	//	strFile = dlgFile.GetPathName();
	//	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT1);
	//	pEdit->SetWindowTextW(strFile);
	//}

	//// TODO: 在此添加控件通知处理程序代码
	//GetDlgItem(IDC_EDIT1)->GetWindowTextW(strFile);

	vector<CString> dictionarys;
	FindDictionaryFile(m_DictionaryDirPath, dictionarys);

	for (auto iter = dictionarys.begin(); iter != dictionarys.end(); iter++)
	{
		CString strFile = *iter;

		ifstream in(strFile);


		string line;

		if (in) // 有该文件  
		{
			while (getline(in, line)) // line中不包括每行的换行符  
			{
				std::wstring wLine = Ansi2WChar(line.c_str(), line.size());
				m_lines.push_back(wLine);
			}
		}

		for (size_t i = 0; i < m_lines.size(); i++)
		{
			//获取首字结构体
			wstring splitString = L"=";
			vector<std::wstring> vecString;
			this->splitString(m_lines[i], vecString, splitString);
			if (vecString.size() == 2)
			{
				CPhraseManager::GetInstance()->addOnePhrase(vecString[0], vecString[1]);
			}
		}

	}

	//CRect rect;
	//m_SearchDictionaryList.GetClientRect(&rect);
	//m_SearchDictionaryList.MoveWindow(rect.left, 200, 600, 200);
	//m_SearchDictionaryList.GetClientRect(&rect);
	//int iLength = rect.Width();

	//m_SearchDictionaryList.SetExtendedStyle(m_SearchDictionaryList.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	//m_SearchDictionaryList.InsertColumn(0, _T("序号"), LVCFMT_LEFT, 200);
	//m_SearchDictionaryList.InsertColumn(1, _T("原字段"), LVCFMT_LEFT, 200);
	//m_SearchDictionaryList.InsertColumn(2, _T("新字段"), LVCFMT_LEFT, 200);
	//m_SearchDictionaryList.SetItemCount(m_lines.size());
}

void CDictionaryConfigPage::GetPinYin(wstring& Chinese, wstring& PinYin)
{

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

std::string CDictionaryConfigPage::WChar2Ansi(LPCWSTR pwszSrc)
{
	int nLen = WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, NULL, 0, NULL, NULL);
	if (nLen <= 0) return std::string("");
	char* pszDst = new char[nLen];
	if (NULL == pszDst) return std::string("");
	WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, pszDst, nLen, NULL, NULL);
	pszDst[nLen - 1] = 0;
	std::string strTemp(pszDst);
	delete[] pszDst;
	return strTemp;
}

void CDictionaryConfigPage::OnLvnGetdispinfoList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	LV_ITEM* pItem = &(pDispInfo)->item;
	int  iItemIndex = pItem->iItem;  //行号
	int col = pItem->iSubItem;  //列号

	wstring splitString = L"=";
	vector<std::wstring> vecString;
	this->splitString(m_lines[iItemIndex], vecString, splitString);


	if (pItem->mask & LVIF_TEXT)
	{
		if (col == 0)
		{
			//序号
			WCHAR index[8];
			wsprintfW(index, L"%d", iItemIndex+1);
			lstrcpyn(pItem->pszText, index, pItem->cchTextMax);
		}
		else if (col == 1)
		{
			if (m_SearchOriginalPhrase.empty())
			{
				lstrcpyn(pItem->pszText, vecString[0].c_str(), pItem->cchTextMax);
			}
			else
			{
				lstrcpyn(pItem->pszText, m_SearchOriginalPhrase[iItemIndex].c_str(), pItem->cchTextMax);
			}
		}
		else if (col == 2)
		{
			if (m_SearchNewPhrase.empty())
			{
				lstrcpyn(pItem->pszText, vecString[1].c_str(), pItem->cchTextMax);
			}
			else
			{
				lstrcpyn(pItem->pszText, m_SearchNewPhrase[iItemIndex].c_str(), pItem->cchTextMax);
			}
		}
	}
}


int CDictionaryConfigPage::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;


	// TODO:  在此添加您专用的创建代码
	m_DictionaryDirPath = GetModuleDir() + m_DictionaryDir;
	if (!PathFileExists(m_DictionaryDirPath))
	{
		::CreateDirectory(m_DictionaryDirPath, NULL);//创建目录,已有的话不影响
	}

	m_DortedDictionaryDirPath = GetModuleDir() + m_DortedDictionaryDir;
	if (!PathFileExists(m_DortedDictionaryDirPath))
	{
		::CreateDirectory(m_DortedDictionaryDirPath, NULL);//创建目录,已有的话不影响
	}

	LoadDictionary();
	return 0;
}


void CDictionaryConfigPage::OnSearchPhrase()
{
	// TODO: 在此添加控件通知处理程序代码

	CString strSearchPhrase = _T("");
	m_EditSearchPhrase.GetWindowTextW(strSearchPhrase);
	wstring wstrSearchPhrase(strSearchPhrase);


	m_SearchOriginalPhrase.clear();
	m_SearchNewPhrase.clear();

	if (wstrSearchPhrase.empty())
	{
		m_SearchDictionaryList.SetItemCount(m_lines.size());
		return;
	}

	CPhraseManager::GetInstance()->FindPhraseWithPrefix(wstrSearchPhrase, m_SearchOriginalPhrase, m_SearchNewPhrase);


	m_SearchDictionaryList.SetItemCount(m_SearchOriginalPhrase.size());
}


void CDictionaryConfigPage::OnSaveDictionary()
{
	// TODO: 在此添加控件通知处理程序代码

	//wstring splitString = L"=";
	//vector<std::wstring> vecString;
	//this->splitString(m_lines[i], vecString, splitString);

	//sort(m_lines.begin(),m_lines.end(), com);
}



//void CDictionaryConfigPage::OnIdok()
//{
//	// TODO: 在此添加命令处理程序代码
//}


void CDictionaryConfigPage::OnOK()
{
	// TODO: 在此添加命令处理程序代码
}


BOOL CDictionaryConfigPage::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_ESCAPE: //Esc按键事件  
			return true;
		case VK_RETURN: //Enter按键事件  
			return true;
		default:
			break;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CDictionaryConfigPage::OnEnChangeSearchphrase()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

	OnSearchPhrase();
}

CString CDictionaryConfigPage::GetModuleDir()
{
	HMODULE module = GetModuleHandle(0);
	WCHAR pFileName[MAX_PATH];
	GetModuleFileName(module, pFileName, MAX_PATH);

	CString csFullPath(pFileName);
	int nPos = csFullPath.ReverseFind(_T('\\'));
	if (nPos < 0)
		return CString("");
	else
		return csFullPath.Left(nPos + 1);
}

void CDictionaryConfigPage::FindDictionaryFile(CString strFoldername, vector<CString> &dictionarys)
{
	CFileFind tempFind;
	BOOL bFound; //判断是否成功找到文件  
	bFound = tempFind.FindFile(strFoldername + L"\\*.txt");//修改" "内内容给限定查找文件类型  
	CString strTmp;   //如果找到的是文件夹 存放文件夹路径  
	while (bFound)      //遍历所有文件  
	{
		
		bFound = tempFind.FindNextFile(); //第一次执行FindNextFile是选择到第一个文件，以后执行为选择到下一个文件
		CString f = tempFind.GetFileName();
		if (tempFind.IsDots())
			continue; //如果找到的是返回上层的目录 则结束本次查找  
		if (tempFind.IsDirectory())   //找到的是文件夹，则遍历该文件夹下的文件  
		{
			continue; //保存文件名，包括后缀名
		}
		else
		{
			strTmp = tempFind.GetFilePath(); //保存文件名，包括后缀名  
			dictionarys.push_back(strTmp);
		}
	}
	tempFind.Close();
	return;
}
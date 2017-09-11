// PhraseReplacePage.cpp : 实现文件
//

#include "stdafx.h"
#include "FieldReplace.h"
#include "PhraseReplacePage.h"
#include "afxdialogex.h"


// CPhraseReplacePage 对话框

IMPLEMENT_DYNAMIC(CPhraseReplacePage, CDialogEx)

CPhraseReplacePage::CPhraseReplacePage(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PHRASEREPLACE_DIALOG, pParent)
{
	m_ArticleDir = L"ArticleDir";
	m_ReplacedArticleDir = L"ReplacedArticleDir";
}

CPhraseReplacePage::~CPhraseReplacePage()
{
}

void CPhraseReplacePage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPhraseReplacePage, CDialogEx)
	ON_BN_CLICKED(IDOK, &CPhraseReplacePage::OnBnClickedOk)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDCANCEL, &CPhraseReplacePage::OnBnClickedCancel)
END_MESSAGE_MAP()


// CPhraseReplacePage 消息处理程序


void CPhraseReplacePage::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}

void CPhraseReplacePage::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


int CPhraseReplacePage::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;


	// TODO:  在此添加您专用的创建代码
	m_ArticleDirPath = GetModuleDir() + m_ArticleDir + L"\\";
	if (!PathFileExists(m_ArticleDirPath))
	{
		::CreateDirectory(m_ArticleDirPath, NULL);//创建目录,已有的话不影响
	}

	m_ReplacedArticleDirPath = GetModuleDir() + m_ReplacedArticleDir + L"\\";
	if (!PathFileExists(m_ReplacedArticleDirPath))
	{
		::CreateDirectory(m_ReplacedArticleDirPath, NULL);//创建目录,已有的话不影响
	}

	vector<CString> phrases;
	FindPhraseFile(m_ArticleDirPath, phrases);
	for (auto iter = phrases.begin(); iter != phrases.end(); iter++)
	{
		CString strFile = *iter;

		ifstream in(strFile);

		std::string str((std::istreambuf_iterator<char>(in)),
			std::istreambuf_iterator<char>());

		wstring phrase = Ansi2WChar(str.c_str(),str.size());


		wstring replacedPhras;

		PhraseReplace(phrase, replacedPhras);


		int nPos = strFile.ReverseFind('\\');

		CString fileName = strFile.Right(strFile.GetLength() - nPos - 1);
		fileName = m_ReplacedArticleDirPath +  L"Replaced_" + fileName;
		ofstream out(fileName);
		out << WChar2Ansi(replacedPhras.c_str());


		wstring f(L"fgsdg");
		PhraseReplace(f, replacedPhras);
	}
	return 0;
}

CString CPhraseReplacePage::GetModuleDir()
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


void CPhraseReplacePage::FindPhraseFile(CString strFoldername, vector<CString> &phrases)
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
			phrases.push_back(strTmp);
		}
	}
	tempFind.Close();
	return;

}

void CPhraseReplacePage::PhraseReplace(wstring &phrase, wstring &replacedPhrase)
{
	
	size_t last = 0;
	wstring wTempStr;
	wstring lastReplaceString;
	vector<CChineseCharacters*> vecChineseCharacters;
	bool hasFindPhrase = false;
	for (size_t index = 0; index <= phrase.size(); index++)
	{

	//}
	//for (auto iter = phrase.begin(); iter <= phrase.end(); iter++)
	//{
		vecChineseCharacters.clear();
		
		wTempStr = phrase.substr(last, index - last);
		if (wTempStr.compare(L"顺序") == 0)
		{
			int i = 0;
			i++;
		}
		CPhraseManager::GetInstance()->FindPhrase(wTempStr, vecChineseCharacters);
		if (vecChineseCharacters.size() && (*vecChineseCharacters.rbegin())->end)
		{
			lastReplaceString = (*vecChineseCharacters.rbegin())->replaceString;
			if (lastReplaceString.compare(L"瘦瘦") == 0)
			{
				int i = 0;
				i++;
			}
			hasFindPhrase = true;
			continue;
		}
		else
		{
			if (hasFindPhrase)
			{
				replacedPhrase += lastReplaceString;
				lastReplaceString = L"";
				last = --index;
				hasFindPhrase = false;
			}
			else
			{
				replacedPhrase += wTempStr;
				last = index;
			}
		}
		
	}

	replacedPhrase += lastReplaceString;
}


std::wstring CPhraseReplacePage::Ansi2WChar(LPCSTR pszSrc, int nLen)

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

std::string CPhraseReplacePage::WChar2Ansi(LPCWSTR pwszSrc)
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
// DictionaryConfigPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FieldReplace.h"
#include "DictionaryConfigPage.h"
#include "afxdialogex.h"





// CDictionaryConfigPage �Ի���

IMPLEMENT_DYNAMIC(CDictionaryConfigPage, CDialogEx)

CDictionaryConfigPage::CDictionaryConfigPage(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DICTIONARYCONFIG_DIALOG, pParent)
{
	m_lines.reserve(10000 * 25);
	m_SearchOriginalPhrase.reserve(1000);
	m_SearchNewPhrase.reserve(1000);
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


// CDictionaryConfigPage ��Ϣ�������


void CDictionaryConfigPage::OnAddDictionaryTableFile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strFile = _T("");

	CFileDialog    dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("Describe Files (*.txt)|*.txt|All Files (*.*)|*.*||"), NULL);

	if (dlgFile.DoModal())
	{
		strFile = dlgFile.GetPathName();
		CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT1);
		pEdit->SetWindowTextW(strFile);
	}

	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_EDIT1)->GetWindowTextW(strFile);
	ifstream in(strFile);


	string line;

	if (in) // �и��ļ�  
	{
		while (getline(in, line)) // line�в�����ÿ�еĻ��з�  
		{
			std::wstring wLine = Ansi2WChar(line.c_str(), line.size());
			m_lines.push_back(wLine);
		}
	}

	for (size_t i = 0; i < m_lines.size(); i++)
	{
		//��ȡ���ֽṹ��
		wstring splitString = L"=";
		vector<std::wstring> vecString;
		this->splitString(m_lines[i], vecString, splitString);
		if (vecString.size() == 2)
		{
			CPhraseManager::GetInstance()->addOnePhrase(vecString[0], vecString[1]);
		}
	}

	CRect rect;
	m_SearchDictionaryList.GetClientRect(&rect);
	m_SearchDictionaryList.MoveWindow(rect.left, 200, 600, 200);
	m_SearchDictionaryList.GetClientRect(&rect);
	int iLength = rect.Width();

	m_SearchDictionaryList.SetExtendedStyle(m_SearchDictionaryList.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	m_SearchDictionaryList.InsertColumn(0, _T("���"), LVCFMT_LEFT, 200);
	m_SearchDictionaryList.InsertColumn(1, _T("ԭ�ֶ�"), LVCFMT_LEFT, 200);
	m_SearchDictionaryList.InsertColumn(2, _T("���ֶ�"), LVCFMT_LEFT, 200);
	m_SearchDictionaryList.SetItemCount(m_lines.size());
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
		//�Ѿ�����ͬ��ԭ���飬�滻�´���
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
	int  iItemIndex = pItem->iItem;  //�к�
	int col = pItem->iSubItem;  //�к�

	wstring splitString = L"=";
	vector<std::wstring> vecString;
	this->splitString(m_lines[iItemIndex], vecString, splitString);


	if (pItem->mask & LVIF_TEXT)
	{
		if (col == 0)
		{
			//���
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

	// TODO:  �ڴ������ר�õĴ�������



	return 0;
}


void CDictionaryConfigPage::OnSearchPhrase()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

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
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//wstring splitString = L"=";
	//vector<std::wstring> vecString;
	//this->splitString(m_lines[i], vecString, splitString);

	//sort(m_lines.begin(),m_lines.end(), com);
}



//void CDictionaryConfigPage::OnIdok()
//{
//	// TODO: �ڴ���������������
//}


void CDictionaryConfigPage::OnOK()
{
	// TODO: �ڴ���������������
}


BOOL CDictionaryConfigPage::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_ESCAPE: //Esc�����¼�  
			return true;
		case VK_RETURN: //Enter�����¼�  
			return true;
		default:
			break;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CDictionaryConfigPage::OnEnChangeSearchphrase()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	OnSearchPhrase();
}


// FieldReplaceDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FieldReplace.h"
#include "FieldReplaceDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CFieldReplaceDlg �Ի���



CFieldReplaceDlg::CFieldReplaceDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_FIELDREPLACE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFieldReplaceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tabCtrl);
}

BEGIN_MESSAGE_MAP(CFieldReplaceDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(IDOK, &CFieldReplaceDlg::OnOK)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CFieldReplaceDlg::OnSelchangeTab)
END_MESSAGE_MAP()


// CFieldReplaceDlg ��Ϣ�������

BOOL CFieldReplaceDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	this->initUIInternal();
	this->initConfig();

	this->ShowWindow(SW_HIDE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CFieldReplaceDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CFieldReplaceDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CFieldReplaceDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CFieldReplaceDlg::initUIInternal()
{
	CRect rec;
	GetClientRect(&rec);

	
	//����tabCtrl�ؼ�  

	//��ӿؼ���ť����
	//m_tabCtrl.InsertItem(0, _T("�ֵ��"));
	//m_tabCtrl.InsertItem(1, _T("�滻�ֶ�"));
	//�Ի���ҳ��  
	m_dictionaryConfigPage.Create(IDD_DICTIONARYCONFIG_DIALOG, GetDlgItem(IDC_TAB1));
	m_phraseReplacePage.Create(IDD_PHRASEREPLACE_DIALOG, GetDlgItem(IDC_TAB1));

	m_tabCtrl.MoveWindow(0, 0, rec.Width(), rec.Height());
	m_dictionaryConfigPage.MoveWindow(0, 25, rec.Width(), rec.Height());

	//��ʾ��һ��ҳ��  
	//m_carList.ShowWindow(SW_SHOW);
	//���õ�һ��ҳ����ʾ  
	m_tabCtrl.SetCurSel(0);
	//m_dictionaryConfigPage.ShowWindow(SW_SHOW);

	m_tabCtrl.ShowWindow(SW_HIDE);
}

void CFieldReplaceDlg::initConfig()
{
	//CChineseCharactersTable::GetInstance()->loadChineseCharactersFromFile(std::string(""));
}




void CFieldReplaceDlg::OnOK()
{
	// TODO: �ڴ���������������
}


BOOL CFieldReplaceDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	// TODO: Add your specialized code here and/or call the base class  
	// ��Esc��Enter�����¼���Ϣ���˵����������Ϣ�ᵼ�¶�ӦӦ�ó������OnOK��������������Ӧ�ó���  
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


void CFieldReplaceDlg::OnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//��ȡ��ѡ���ҳ��  
	//int nCurSel = m_tabCtrl.GetCurSel();
	//if (nCurSel == 0)
	//{
	//	//ҳ��һ��ʾ��ҳ�������  
	//	m_dictionaryConfigPage.ShowWindow(SW_SHOW);
	//	m_phraseReplacePage.ShowWindow(SW_HIDE);
	//}
	//else if (nCurSel == 1)
	//{
	//	m_dictionaryConfigPage.ShowWindow(SW_HIDE);
	//	m_phraseReplacePage.ShowWindow(SW_SHOW);
	//}
	*pResult = 0;
}

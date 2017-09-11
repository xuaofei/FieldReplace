
// FieldReplaceDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FieldReplace.h"
#include "FieldReplaceDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CFieldReplaceDlg 对话框



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


// CFieldReplaceDlg 消息处理程序

BOOL CFieldReplaceDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	this->initUIInternal();
	this->initConfig();

	this->ShowWindow(SW_HIDE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFieldReplaceDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CFieldReplaceDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CFieldReplaceDlg::initUIInternal()
{
	CRect rec;
	GetClientRect(&rec);

	
	//创建tabCtrl控件  

	//添加控件按钮名称
	//m_tabCtrl.InsertItem(0, _T("字典表"));
	//m_tabCtrl.InsertItem(1, _T("替换字段"));
	//对话框页面  
	m_dictionaryConfigPage.Create(IDD_DICTIONARYCONFIG_DIALOG, GetDlgItem(IDC_TAB1));
	m_phraseReplacePage.Create(IDD_PHRASEREPLACE_DIALOG, GetDlgItem(IDC_TAB1));

	m_tabCtrl.MoveWindow(0, 0, rec.Width(), rec.Height());
	m_dictionaryConfigPage.MoveWindow(0, 25, rec.Width(), rec.Height());

	//显示第一个页面  
	//m_carList.ShowWindow(SW_SHOW);
	//设置第一个页面显示  
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
	// TODO: 在此添加命令处理程序代码
}


BOOL CFieldReplaceDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	// TODO: Add your specialized code here and/or call the base class  
	// 把Esc和Enter按键事件消息过滤掉，否则该消息会导致对应应用程序调用OnOK（）方法，结束应用程序  
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


void CFieldReplaceDlg::OnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码

	//获取所选择的页面  
	//int nCurSel = m_tabCtrl.GetCurSel();
	//if (nCurSel == 0)
	//{
	//	//页面一显示，页面二隐藏  
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

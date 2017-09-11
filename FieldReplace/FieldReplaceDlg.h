
// FieldReplaceDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "DictionaryConfigPage.h"
#include "PhraseReplacePage.h"

// CFieldReplaceDlg 对话框
class CFieldReplaceDlg : public CDialogEx
{
// 构造
public:
	CFieldReplaceDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FIELDREPLACE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnOK();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult);
	DECLARE_MESSAGE_MAP()
private:
	void initUIInternal();
	void initConfig();

	CTabCtrl m_tabCtrl;
	CDictionaryConfigPage m_dictionaryConfigPage;
	CPhraseReplacePage m_phraseReplacePage;
public:

};

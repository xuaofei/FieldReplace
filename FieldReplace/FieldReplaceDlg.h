
// FieldReplaceDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "DictionaryConfigPage.h"
#include "PhraseReplacePage.h"

// CFieldReplaceDlg �Ի���
class CFieldReplaceDlg : public CDialogEx
{
// ����
public:
	CFieldReplaceDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FIELDREPLACE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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


// HQTESTDlg.h : ͷ�ļ�
//

#pragma once
#include "Quotation.h"
#include "afxwin.h"


#define TREADNUM 20


// CHQTESTDlg �Ի���
class CHQTESTDlg : public CDialog
{
// ����
public:
	CHQTESTDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_HQTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	int m_istock;
	STOCKCODE stockcode[ 3000 ];
	CQuotation * pquo[TREADNUM];
	
	int preMin;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg LRESULT OnNotifyIcon(WPARAM wParam,LPARAM IParam);
	NOTIFYICONDATA NotifyIcon;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CListBox m_lstbox_msg;
};

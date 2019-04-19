
// sensDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "ftd2xx.h"

// CsensDlg ��ȭ ����
class CsensDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CsensDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SENS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CStatic m_picture;
	CWinThread *m_pThread;

	static UINT ThreadFunc(LPVOID lParam);
	afx_msg void OnDestroy();
	static int MakeBMI(BITMAPINFO **);
	FT_HANDLE m_hfthandle;

	afx_msg void OnBnClickedButton2();
	static void SaveBin(char * pImage, int nIdx);
	CButton m_chkSaveFile;
	int m_nDrawCount;
	static void moveData(BYTE cSrc[][256], BYTE cDst[][256], int nFlip);
	CButton m_chkVFlip;
};

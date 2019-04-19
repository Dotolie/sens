
// sensDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "ftd2xx.h"

// CsensDlg 대화 상자
class CsensDlg : public CDialogEx
{
// 생성입니다.
public:
	CsensDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SENS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
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


// sensDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "sens.h"
#include "sensDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


static bool g_bRun;
int g_aData[256*256] = {0,};

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CsensDlg ��ȭ ����




CsensDlg::CsensDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CsensDlg::IDD, pParent)
	, m_pThread(NULL)
	, m_hfthandle(NULL)
	, m_nDrawCount(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CsensDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PICTURE, m_picture);
	DDX_Control(pDX, IDC_CHECK1, m_chkSaveFile);
	DDX_Control(pDX, IDC_CHECK2, m_chkVFlip);
}

BEGIN_MESSAGE_MAP(CsensDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CsensDlg::OnBnClickedButton1)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON2, &CsensDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CsensDlg �޽��� ó����

BOOL CsensDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
	m_nDrawCount = 0;

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CsensDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CsensDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CsensDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CsensDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	FT_STATUS res;
	

	res = FT_Open( 0, &m_hfthandle );
	if( res != FT_OK )
	{
		AfxMessageBox(_T("Can't open Device."), MB_ICONSTOP | MB_OK );
		return;
	}
	
	GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);

	res = FT_SetBitMode( m_hfthandle, 0xff, 0x00);
	Sleep(100);
	res = FT_SetBitMode( m_hfthandle, 0xff, 0x40 );

	res = FT_SetLatencyTimer( m_hfthandle, 255 );
	res = FT_SetUSBParameters( m_hfthandle, 0x10000, 0x10000 );
	res = FT_SetFlowControl( m_hfthandle, FT_FLOW_RTS_CTS, 0, 0 );
	res = FT_Purge( m_hfthandle, FT_PURGE_RX | FT_PURGE_TX);

	Sleep(100);

	g_bRun = true;
	m_pThread = AfxBeginThread(ThreadFunc, this, 0, 0, CREATE_SUSPENDED);
	ASSERT( m_pThread != NULL );

	m_pThread->ResumeThread();

}


UINT CsensDlg::ThreadFunc(LPVOID lParam)
{
	CsensDlg *pDlg = (CsensDlg*)AfxGetApp()->m_pMainWnd;
	CDC *pdc = pDlg->m_picture.GetDC();
	BYTE n = 0;
	FT_STATUS res;
	DWORD EventDWord;
	DWORD RxBytes;
	DWORD TxBytes;
	DWORD BytesReceived = 0;
	DWORD BytesWritten = 0;
	char TxBuffer[4096];

	BITMAPINFO *pBmi = NULL;
	BYTE Data[256][256];
	BYTE Buff[256][256];
	int nIdx = 0;

	MakeBMI( &pBmi );

	while(g_bRun)
	{
		res = FT_GetStatus(pDlg->m_hfthandle, &RxBytes, &TxBytes, &EventDWord);
		if((res == FT_OK) && (TxBytes == 0))
		{
			res = FT_Write(pDlg->m_hfthandle,TxBuffer,4096,&BytesWritten);
			if (res == FT_OK)
			{
				// FT_Write OK
				TRACE("Write %d bytes!\r\n", BytesWritten);
			}
			else
			{
				// FT_Write Failed
				TRACE("Write fail\n");
			}
		}
		if ( pDlg->m_chkSaveFile.GetCheck())
		{
			SaveBin( (char*)Buff, nIdx);
		}
		for(int j=0;j<100;j++)
		{
			if(g_bRun == false )
			{
				break;
			}

			res = FT_GetStatus(pDlg->m_hfthandle, &RxBytes, &TxBytes, &EventDWord);
			if((res == FT_OK) && (RxBytes >= 65536))
			{
				res = FT_Read(pDlg->m_hfthandle, Buff, 65536, &BytesReceived);
				if(res == FT_OK )
				{
					// FT_Read OK
					if ( pDlg->m_chkVFlip.GetCheck())
					{
						moveData(Buff, Data, pDlg->m_nDrawCount);
					}
					else
					{
						moveData(Buff, Data, 0);
					}
					SetDIBitsToDevice(pdc->m_hDC, 0, 0, 256, 256, 0, 0, 0, 256, Data, pBmi, DIB_RGB_COLORS);
					nIdx++;
					pDlg->m_nDrawCount++;

					TRACE("j=%d : Read %d bytes! \r\n", j, BytesReceived);
					break;
				}
				else
				{
					// FT_Read Failed
					TRACE("j=%d, Read Fail\n", j);
				}
			}
			else
			{
				TRACE("---loop i=%d \n", j );
				Sleep(10);
			}
		}

		Sleep(1);

	}

	delete(pBmi);


	pDlg->ReleaseDC(pdc); 
	Sleep(100);

	return 0;
}






void CsensDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	DWORD dwCode = 0;
	FT_STATUS res;
	g_bRun = false;

	if( m_pThread)
	{
//		GetExitCodeThread(m_pThread->m_hThread, &dwCode);
//		TRACE(_T("dwCode=%d\n", dwCode));
		
		WaitForSingleObject(m_pThread->m_hThread, 5000);

		GetExitCodeThread(m_pThread->m_hThread, &dwCode);
		TRACE(_T("dwCode=%d\n"), dwCode);
	}

	if( m_hfthandle != NULL )
	{
		res = FT_SetBitMode( m_hfthandle, 0xff, 0x00);

		FT_Close(m_hfthandle);
	}
	m_hfthandle = NULL;
}


int CsensDlg::MakeBMI(BITMAPINFO **pi)
{
	BITMAPINFO *pBmi = (BITMAPINFO*)malloc(sizeof(BITMAPINFO) + 256 * sizeof(RGBQUAD));

	pBmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	pBmi->bmiHeader.biWidth = 256;
	pBmi->bmiHeader.biHeight = 256;
	pBmi->bmiHeader.biPlanes = 1;
	pBmi->bmiHeader.biBitCount = 8;
	pBmi->bmiHeader.biCompression = BI_RGB;
	pBmi->bmiHeader.biSizeImage = 256*256;
	pBmi->bmiHeader.biXPelsPerMeter = 0;
	pBmi->bmiHeader.biYPelsPerMeter = 0;
	pBmi->bmiHeader.biClrUsed = 0;
	pBmi->bmiHeader.biClrImportant = 0;
	
	for (int j=0; j<256; j++)
    {
		pBmi->bmiColors[j].rgbRed       = j;
        pBmi->bmiColors[j].rgbGreen     = j;
        pBmi->bmiColors[j].rgbBlue      = j;
        pBmi->bmiColors[j].rgbReserved  = 0;
    }

	*pi = pBmi;
	return 0;
}


void CsensDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	FT_STATUS res;
	DWORD dwCode = 0;

	GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);

	g_bRun = false;

	if( m_pThread)
	{
		WaitForSingleObject(m_pThread->m_hThread, 1000);

		GetExitCodeThread(m_pThread->m_hThread, &dwCode);
		TRACE(_T("dwCode=%d\n"), dwCode);
	}



	m_pThread = NULL;

	if( m_hfthandle != NULL )
	{
		res = FT_SetBitMode( m_hfthandle, 0xff, 0x00);

		FT_Close(m_hfthandle);
	}

	m_hfthandle = NULL;

}


void CsensDlg::SaveBin(char *pImage, int nIdx)
{
	SYSTEMTIME cur_time;
	GetLocalTime(&cur_time);
	CTime time = CTime::GetCurrentTime();
	CString strTime = time.Format(_T("img%Y%m%d%H%M%S"));
	strTime.Format(_T("%s%03d.bin"),strTime, cur_time.wMilliseconds);

	if( nIdx == 0 )
		return;

	try 
	{
		CFile file;
		file.Open(strTime, CFile::modeCreate | CFile::modeWrite );
		file.Write( pImage, 65536 );
		file.Close();
	}
	catch( CFileException *e )
	{
		e->ReportError();
		TRACE(_T("Error : Can't Create File\n"));
	}
	

}


void CsensDlg::moveData(BYTE cSrc[][256], BYTE cDst[][256], int nFlip)
{
	for(int i=0;i<256;i++)
	{
		if( (nFlip % 2) == 0 )
		{
			memcpy(cDst[255-i], cSrc[i], 256);
		}
		else
		{
			memcpy(cDst[i], cSrc[i], 256);
		}
	}
}

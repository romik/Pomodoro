
// PomodoroDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Pomodoro.h"
#include "PomodoroDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CPomodoroDlg dialog




CPomodoroDlg::CPomodoroDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPomodoroDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPomodoroDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
}

BEGIN_MESSAGE_MAP(CPomodoroDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CPomodoroDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CPomodoroDlg::OnBnClickedCancel)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_START, &CPomodoroDlg::OnBnClickedBtnStart)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CPomodoroDlg message handlers

BOOL CPomodoroDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_nPomodoroTime=25;
	m_nPomodoroCount=0;
	///Set FOnt
	
	//m_Font.Detach();
	
	/*m_Font.CreateFontW(200,                        // nHeight
					20,                         // nWidth
					0,                         // nEscapement
					0,                         // nOrientation
					FW_NORMAL,                 // nWeight
					FALSE,                     // bItalic
					FALSE,                     // bUnderline
					0,                         // cStrikeOut
					ANSI_CHARSET,              // nCharSet
					OUT_DEFAULT_PRECIS,        // nOutPrecision
					CLIP_DEFAULT_PRECIS,       // nClipPrecision
					DEFAULT_QUALITY,           // nQuality
					DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
					_T("Arial"));                 // lpszFacename*/
	 m_Font.CreatePointFont(500, _T("Helvetica Light"));

	GetDlgItem(IDC_STATIC_DISPLAY2)->SetFont(&m_Font);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPomodoroDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPomodoroDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPomodoroDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPomodoroDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


void CPomodoroDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}




void CPomodoroDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	COleDateTime dtNow=COleDateTime::GetCurrentTime();
	COleDateTimeSpan ts = dtNow-m_dtStartTime;
	CString strMessage;
	m_minutes=ts.GetMinutes();
	strMessage.Format(_T("%02d:%02d"), ts.GetMinutes(), ts.GetSeconds());
	SetDlgItemText(IDC_STATIC_DISPLAY2, strMessage);
	m_Progress.SetPos(m_minutes);
	if(m_minutes>=m_nPomodoroTime)
	{
		KillTimer(1);
		SetDlgItemText(IDC_STATIC_DISPLAY, _T("Pomodoro Complete."));
		AfxMessageBox(_T("Pomodoro complete. Time to take a break"));
		m_Progress.SetPos(0);
		GetDlgItem(IDC_BTN_START)->EnableWindow(TRUE);
		m_nPomodoroCount++;
		strMessage.Format(_T("Pomodoros Completed:%d"), m_nPomodoroCount);
		SetDlgItemText(IDC_STATIC_COMPLETED, strMessage);
	}


	CDialogEx::OnTimer(nIDEvent);
}






void CPomodoroDlg::OnBnClickedBtnStart()
{
	// TODO: Add your control notification handler code here
	m_nTimer=SetTimer(1,1000,0);
	m_dtStartTime=COleDateTime::GetCurrentTime();
	m_Progress.SetRange(0,m_nPomodoroTime);
	GetDlgItem(IDC_BTN_START)->EnableWindow(FALSE);
	SetDlgItemText(IDC_STATIC_DISPLAY, _T("Time: "));
}


BOOL CPomodoroDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnEraseBkgnd(pDC);

	CRect rect;
	GetClientRect(&rect);

	int r1=255,g1=94,b1=58; //start color
	int r2=255,g2=19,b2=0; //stop color

	for(int i=0;i<rect.Height();i++)
	{ 
		int r,g,b;
		r = r1 + (i * (r2-r1) / rect.Height());
		g = g1 + (i * (g2-g1) / rect.Height());
		b = b1 + (i * (b2-b1) / rect.Height());
		pDC->FillSolidRect(0,i,rect.Width(),1,RGB(r,g,b));
	}
	return true;
}


HBRUSH CPomodoroDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	if(pWnd->GetDlgCtrlID() == IDC_STATIC_DISPLAY2)
		pDC->SetBkColor(RGB(255,94,58));
	else if(pWnd->GetDlgCtrlID() == IDC_STATIC_COMPLETED)
		pDC->SetBkColor(RGB(255,19,0));

	// TODO:  Return a different brush if the default is not desired
	return hbr;

}

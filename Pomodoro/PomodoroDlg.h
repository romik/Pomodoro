
// PomodoroDlg.h : header file
//

#pragma once


// CPomodoroDlg dialog
class CPomodoroDlg : public CDialogEx
{
// Construction
public:
	CPomodoroDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_POMODORO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
private:
	UINT_PTR m_nTimer;
	COleDateTime m_dtStartTime;
	int m_minutes;
	int m_nPomodoroTime;
	int m_nPomodoroCount;
	CFont m_Font;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CProgressCtrl m_Progress;
	afx_msg void OnBnClickedBtnStart();
};

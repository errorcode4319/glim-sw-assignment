
// DrawCircleDlg.h : header file
//

#pragma once

#include "canvas.h"

// CDrawCircleDlg dialog
class CDrawCircleDlg : public CDialogEx
{
// Construction
public:
	CDrawCircleDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DRAWCIRCLE_DIALOG };
#endif

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



private:
	Canvas canvas_;


public:
	afx_msg void OnBnClickedBtnClear();
	afx_msg void OnBnClickedBtnRandom();
	afx_msg void OnBnClickedBtnStop();

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

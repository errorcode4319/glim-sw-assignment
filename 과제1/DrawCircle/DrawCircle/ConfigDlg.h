#pragma once


// CConfigDlg dialog

class CConfigDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CConfigDlg)

public:
	CConfigDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CConfigDlg();

	CWnd* p_parent_;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CConfigDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedBtnConfigSave();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};

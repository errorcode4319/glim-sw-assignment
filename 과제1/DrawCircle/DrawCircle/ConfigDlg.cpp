// CConfigDlg.cpp : implementation file
//

#include "pch.h"
#include "DrawCircle.h"
#include "ConfigDlg.h"
#include "afxdialogex.h"

#include "DrawCircleDlg.h"


// CConfigDlg dialog

IMPLEMENT_DYNAMIC(CConfigDlg, CDialogEx)

CConfigDlg::CConfigDlg(CWnd* pParent)
	: CDialogEx(IDD_CConfigDlg, pParent), p_parent_(pParent)
{

}

CConfigDlg::~CConfigDlg()
{
}

void CConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CConfigDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_CONFIG_SAVE, &CConfigDlg::OnBnClickedBtnConfigSave)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CConfigDlg message handlers


void CConfigDlg::OnBnClickedBtnConfigSave()
{

	auto* parent = (CDrawCircleDlg*)p_parent_;

	int point_r = GetDlgItemInt(IDC_EDIT_POINT_R, NULL, TRUE);
	int thickness = GetDlgItemInt(IDC_EDIT_THICKNESS, NULL, TRUE);

	GetDlgItem(IDC_TEXT_SAVE_SUCCESS)->ShowWindow(SW_HIDE);

	if (point_r < 1 || point_r > 20) {
		GetDlgItem(IDC_CAUTION_POINT_R)->ShowWindow(SW_SHOW);
		return;
	}

	if (thickness < 1 || thickness > 10) {
		GetDlgItem(IDC_CAUTION_THICKNESS)->ShowWindow(SW_SHOW);
		return;
	}

	// TODO: Add your control notification handler code here
	parent->SetPointR(point_r);
	parent->SetCircleThickness(thickness);

	GetDlgItem(IDC_CAUTION_POINT_R)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CAUTION_THICKNESS)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_TEXT_SAVE_SUCCESS)->ShowWindow(SW_SHOW);

	parent->SendMessage(WM_FRAME_UPDATE_MSG);

}


void CConfigDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	auto* parent = (CDrawCircleDlg*)p_parent_;

	SetDlgItemInt(IDC_EDIT_POINT_R, parent->GetPointR(), TRUE);
	SetDlgItemInt(IDC_EDIT_THICKNESS, parent->GetCircleThickness(), TRUE);

	GetDlgItem(IDC_CAUTION_POINT_R)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CAUTION_THICKNESS)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_TEXT_SAVE_SUCCESS)->ShowWindow(SW_HIDE);

}

// DrawCircleDlg.h : header file
//

#pragma once

#include "canvas.h"
#include "mouse_control.h"
#include "solver.h"
#include "utils.h"

#include "ConfigDlg.h"

#define WM_FRAME_UPDATE_MSG	(WM_USER + 100)

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

public:
	afx_msg void OnBnClickedBtnClear();
	afx_msg void OnBnClickedBtnRandom();
	afx_msg void OnBnClickedBtnStop();

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedBtnConfig();

	afx_msg LRESULT OnFrameUpdateMsg(WPARAM wParam, LPARAM lParam);

public:	// Config Dialog 인스턴스 + 인터페이스
	void SetPointR(int point_r) { point_r_ = point_r; }
	int  GetPointR() const { return point_r_; }

	void SetCircleThickness(int thickness) { circle_thickness_ = thickness; }
	int  GetCircleThickness() const { return circle_thickness_; }

	std::unique_ptr<CConfigDlg>	p_config_dlg_;

private:
	void UpdateCanvasFrame();

	void UpdateButtonState(bool btn_clear, bool btn_random, bool btn_stop);

	bool CheckMouseInFrame(CPoint pt);;

	void BGProcess();

private:
	std::thread bg_thread_;

	std::atomic<bool> on_exit_ = false;
	std::atomic<bool> on_random_mode_ = false;

	std::mutex btn_state_mut_;

	Canvas canvas_;
	MouseController mouse_ctl_;
	Solver solver_;

	int	cur_point_idx_ = -1;
	int point_r_ = 10;
	int circle_thickness_ = 3;

	const int frame_offset_x_ = 10;
	const int frame_offset_y_ = 10;
	const int frame_width_ = 720;
	const int frame_height_ = 480;

	const CRect frame_rect_ = { frame_offset_x_, frame_offset_y_, frame_width_ + frame_offset_x_, frame_height_ + frame_offset_y_ };
};

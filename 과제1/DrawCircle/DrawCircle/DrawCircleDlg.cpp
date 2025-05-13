
// DrawCircleDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "DrawCircle.h"
#include "DrawCircleDlg.h"
#include "afxdialogex.h"
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	RGBQUAD rgb;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDrawCircleDlg dialog



CDrawCircleDlg::CDrawCircleDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DRAWCIRCLE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDrawCircleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDrawCircleDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BTN_CLEAR, &CDrawCircleDlg::OnBnClickedBtnClear)
	ON_BN_CLICKED(IDC_BTN_RANDOM, &CDrawCircleDlg::OnBnClickedBtnRandom)
	ON_BN_CLICKED(IDC_BTN_STOP, &CDrawCircleDlg::OnBnClickedBtnStop)
	ON_MESSAGE(WM_BG_THREAD_MSG, &CDrawCircleDlg::OnBGThreadMsg)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CDrawCircleDlg message handlers

BOOL CDrawCircleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	std::cout << "[CDrawCircleDlg::" << __func__ << "]" << std::endl;


	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// Canvas 초기화
	canvas_.Init(frame_width_, frame_height_);
	canvas_.BufferClear(255);


	// 백그라운드 쓰레드 초기화 
	on_exit_ = false;
	on_random_mode_ = false;
	bg_thread_ = std::thread{ &CDrawCircleDlg::BGProcess, this };

	// 버튼 상태 초기화 
	UpdateButtonState(true, true, false);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDrawCircleDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDrawCircleDlg::OnPaint()
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
		UpdateCanvasFrame();

		CDialogEx::OnPaint();
	}
}

void CDrawCircleDlg::UpdateCanvasFrame() {
	CPaintDC dc(this); // device context for painting

	canvas_.BufferClear();

	const auto& points = solver_.GetPoints();
	for (int i = 0; i < points.size();i++) {
		uint8_t color = 0;
		if (i == cur_point_idx_) color = 128;
		canvas_.DrawCircle(points[i].x, points[i].y, point_r_, -1, color);
	}

	if (solver_.GetPointCount() == 3) {
		auto result = solver_.Solve();
		canvas_.DrawCircle(result.x, result.y, result.r, circle_thickness_);
	}

	canvas_.BufferUpdate();
	canvas_.GetMFCImage()->Draw(dc, frame_offset_x_, frame_offset_y_);
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDrawCircleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDrawCircleDlg::UpdateButtonState(bool btn_clear, bool btn_random, bool btn_stop) {
	std::unique_lock<std::mutex> lock(btn_state_mut_);
	GetDlgItem(IDC_BTN_CLEAR)->EnableWindow(btn_clear);
	GetDlgItem(IDC_BTN_RANDOM)->EnableWindow(btn_random);
	GetDlgItem(IDC_BTN_STOP)->EnableWindow(btn_stop);
}

// Clear Button 
void CDrawCircleDlg::OnBnClickedBtnClear()
{
	std::cout << OUT_METHOD_NAME << std::endl;

	// 이미 랜덤 모드가 실행중인 경우 
	if (on_random_mode_ == true) {
		return;
	}

	// TODO: Canvas 초기화 + PointManager 초기화
	cur_point_idx_ = -1;
	solver_.Clear();
	Invalidate();
}

// Random Button 
void CDrawCircleDlg::OnBnClickedBtnRandom()
{
	std::cout << OUT_METHOD_NAME << std::endl;
	// TODO: 랜덤 포인트 생성 + 이미지 출력 로직 추가 

	// 이미 랜덤 모드가 실행중인 경우 
	if (on_random_mode_.load()) {
		return;
	}
	
	UpdateButtonState(false, false, true);
	on_random_mode_.store(true);

	Invalidate();
}

// Stop Button 
void CDrawCircleDlg::OnBnClickedBtnStop()
{
	std::cout << OUT_METHOD_NAME << std::endl;
	// TODO: 랜덤 쓰레드 종료

	on_random_mode_.store(false);
	UpdateButtonState(true, true, false);


	Invalidate();
}

bool CDrawCircleDlg::CheckMouseInFrame(CPoint pt) {
	// 마우스 클릭 좌표가 프레임 영역을 벗어난 경우 
	if (pt.x < frame_offset_x_ || pt.x >= frame_offset_x_ + frame_width_ ||
		pt.y < frame_offset_y_ || pt.y >= frame_offset_y_ + frame_height_)
		return false;
	return true;
}

// Mouse L Button Down
void CDrawCircleDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CDialogEx::OnLButtonDown(nFlags, point);

	// 마우스가 프레임을 벗어난 경우
	if (!CheckMouseInFrame(point))
		return;

	if (on_random_mode_)
		return;

	mouse_ctl_.Click(point.x - frame_offset_x_, point.y - frame_offset_y_);

	auto mpos = mouse_ctl_.GetCurMouseCoord();

	// TODO: 현재 Random 모드가 아닐 경우 + 포인트를 3개 다 찍지 않은 경우 포인트 찍기
	std::cout << "Mouse Down (x: " << mpos.x << ", y: " << mpos.y << ")\n";

	// 포인트 추가 
	if (solver_.GetPointCount() < 3) {
		solver_.AddPoint(mpos.x, mpos.y);
	}
	// 포인트 선택 
	else {
		const auto& points = solver_.GetPoints();
		
		cur_point_idx_ = -1;
		for (int i = 0; i < points.size(); i++) {
			auto pt = points[i];
			auto dist = GetDistance(mpos.x, mpos.y, pt.x, pt.y);

			if (dist <= double(point_r_)) {
				cur_point_idx_ = i;
				break;
			}
		}
	}

	InvalidateRect(&frame_rect_, FALSE);
}

// Mouse Move 
void CDrawCircleDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	CDialogEx::OnMouseMove(nFlags, point);

	if (!CheckMouseInFrame(point))
		return;
	
	if (on_random_mode_)
		return;

	mouse_ctl_.MoveTo(point.x - frame_offset_x_, point.y - frame_offset_y_);
	auto mpos = mouse_ctl_.GetCurMouseCoord();

	// 마우스 드래그 상태일 경우 + 현재 선택된 포인트가 있을 경우 -> 포인트 위치 이동
	if (mouse_ctl_.OnDrag() && cur_point_idx_ != -1) {
		solver_.MovePoint(cur_point_idx_, mpos.x, mpos.y);
		std::cout << "Mouse Move (cur_poins: " << cur_point_idx_ << "x: " << mpos.x << ", y : " << mpos.y << ")\n";
	}
	InvalidateRect(&frame_rect_, FALSE);
}

// Mouse L Button Release 
void CDrawCircleDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	CDialogEx::OnLButtonUp(nFlags, point);
	mouse_ctl_.Release();
	cur_point_idx_ = -1;

	if (on_random_mode_)
		return;

	std::cout << "Mouse Release\n";
	InvalidateRect(&frame_rect_, FALSE);
}

void CDrawCircleDlg::BGProcess() {

	int random_count = 0;
	uint64_t last_time_ms = 0;

	while (!on_exit_.load()) {

		if (on_random_mode_.load()) {
			auto current_time_ms = GetEpochTimeMs();

			if (current_time_ms - last_time_ms >= 500) {
				last_time_ms = GetEpochTimeMs();
				this->solver_.RandomGenerate(frame_width_, frame_height_);
				random_count++;

				PostMessage(WM_BG_THREAD_MSG);
			}

			if (random_count == 10) {
				on_random_mode_.store(false);
				UpdateButtonState(true, true, false);
			}
		}
		else {
			random_count = 0;
			last_time_ms = 0;
		}

		SleepMs(50);
	}

}

LRESULT CDrawCircleDlg::OnBGThreadMsg(WPARAM wParam, LPARAM lParam) {
	InvalidateRect(&frame_rect_, FALSE);
	return 0;
}

void CDrawCircleDlg::OnDestroy()
{

	// TODO: Add your message handler code here

	on_random_mode_.store(false);
	on_exit_.store(true);

	bg_thread_.join();

	std::cout << "Program Exit" << std::endl;


	CDialogEx::OnDestroy();
}

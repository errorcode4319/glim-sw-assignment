
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

	canvas_.Init(720, 480);
	canvas_.BufferClear(255);

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
		CPaintDC dc(this); // device context for painting

		canvas_.BufferUpdate();
		canvas_.GetMFCImage()->Draw(dc, 10, 10);

		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDrawCircleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// Clear Button 
void CDrawCircleDlg::OnBnClickedBtnClear()
{
	// TODO: Canvas 초기화 + PointManager 초기화

	Invalidate();
}

// Random Button 
void CDrawCircleDlg::OnBnClickedBtnRandom()
{
	// TODO: 랜덤 포인트 생성 + 이미지 출력 로직 추가 

	Invalidate();
}

// Stop Button 
void CDrawCircleDlg::OnBnClickedBtnStop()
{
	// TODO: 랜덤 쓰레드 종료

	Invalidate();
}

// Mouse L Button Down
void CDrawCircleDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CDialogEx::OnLButtonDown(nFlags, point);
	mouse_ctl_.Click(point.x, point.y);

	// TODO: 현재 Random 모드가 아닐 경우 + 포인트를 3개 다 찍지 않은 경우 포인트 찍기
	std::cout << "Mouse Down (x: " << point.x << ", y: " << point.y << ")\n";


	Invalidate();
}

// Mouse Move 
void CDrawCircleDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	CDialogEx::OnMouseMove(nFlags, point);
	mouse_ctl_.MoveTo(point.x, point.y);

	// TODO: 드래그 상태일 경우, 해당 포인트 위치 이동






	CPaintDC dc(this); // device context for painting
	canvas_.BufferUpdate();
	canvas_.GetMFCImage()->Draw(dc, 10, 10);
}

// Mouse L Button Release 
void CDrawCircleDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	CDialogEx::OnLButtonUp(nFlags, point);
	mouse_ctl_.Release();
	
	// TODO: 포인트 드래그 상태 해제 

	std::cout << "Mouse Release (x: " << point.x << ", y: " << point.y << ")\n";

	Invalidate();
}
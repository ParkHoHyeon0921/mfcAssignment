
// phh_PrjDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "phh_Prj.h"
#include "phh_PrjDlg.h"
#include "afxdialogex.h"
#include "DlgImage.h"
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CphhPrjDlg 대화 상자



CphhPrjDlg::CphhPrjDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PHH_PRJ_DIALOG, pParent)
	, editCenterX(_T(""))
	, editCenterY(_T(""))
	, backColorRed(0)
	, backColorGreen(0)
	, backColorBlue(0)
	, m_editRGB(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

void CphhPrjDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_MAKE_CIRCLE, m_btnMakeCirecle);
	DDX_Control(pDX, IDC_EDIT_RAIDUS, m_editRadius);
	DDX_Control(pDX, IDC_STATIC_Label, m_stcRadius);

	DDX_Text(pDX, IDC_EDIT_CENTER_X, editCenterX);
	DDX_Text(pDX, IDC_EDIT_CENTER_Y, editCenterY);
	DDX_Control(pDX, IDC_EDIT_RGB_RED, m_editRGBRed);
	DDX_Control(pDX, IDC_EDIT_RGB_GREEN, m_editRGBGreen);
	DDX_Control(pDX, IDC_EDIT_RGB_BLUE, m_editRGBBlue);
	DDX_Text(pDX, IDC_EDIT_RGB, m_editRGB);
	DDX_Control(pDX, IDC_EDIT_RGB_VIEW, m_editRGBView);
}

BEGIN_MESSAGE_MAP(CphhPrjDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_MAKE_CIRCLE, &CphhPrjDlg::OnBnClickedBtnMakeCircle)
	ON_BN_CLICKED(IDC_BTN_CHANGE_COLOR, &CphhPrjDlg::OnBnClickedBtnChangeColor)
END_MESSAGE_MAP()


// CphhPrjDlg 메시지 처리기

BOOL CphhPrjDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	MoveWindow(0, 0, MAIN_WIDTH, MAIN_HEIGHT);
	
	m_pDlgImage = new CDlgImage;
	m_pDlgImage->Create(IDD_DLGIMAGE, this);
	m_pDlgImage->ShowWindow(SW_SHOW);
	m_pDlgImage->MoveWindow(0, 0, m_pDlgImage->m_Image.GetWidth(), m_pDlgImage->m_Image.GetHeight());


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CphhPrjDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CphhPrjDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CphhPrjDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CphhPrjDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (m_pDlgImage)		delete m_pDlgImage;	
}

void CphhPrjDlg::OnBnClickedBtnMakeCircle()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_pDlgImage->Invalidate();
	m_pDlgImage->UpdateWindow();

	CString strRadius;
	m_editRadius.GetWindowText(strRadius);
	double nDiameter = _tstof(strRadius);

	if (nDiameter > 0) {
		CRect nRect = rectData(nDiameter);
		CDC* pDC = m_pDlgImage->GetDC();
		
		drawBackColor();
		drawCircle(pDC, nRect); // 원그리기 기능
		drawLine(pDC, nRect, 5);  // 중심점 십자가 기능
		
		ReleaseDC(pDC);
	}
}


CRect CphhPrjDlg::rectData(double nDiameter)
{
	int nCMaxX = m_pDlgImage->m_Image.GetWidth();
	int nCMaxY = m_pDlgImage->m_Image.GetHeight();
	int nCPosL = rand() % int(nCMaxX - nDiameter);
	int nCPosT = rand() % int(nCMaxY - nDiameter);
	double nCPosR = nCPosL + nDiameter;
	double nCPosB = nCPosT + nDiameter;
	double nSumX = nCPosL + nCPosR;
	double nSumY = nCPosB + nCPosT;
	double nCenterX = nSumX / 2.0;
	double nCenterY = nSumY / 2.0;
	UpdateData();
	editCenterX.Format(_T("%f"), nCenterX);
	editCenterY.Format(_T("%f"), nCenterY);
	UpdateData(FALSE);
	

	CRect rect(nCPosL, nCPosT, nCPosR, nCPosB);
	
	return rect;
}

void CphhPrjDlg::drawCircle(CDC* pDC, CRect pRect)
{
	CPen penCircle;

	penCircle.CreatePen(PS_SOLID, 5, RGB(0xff, 0xff, 0));

	pDC->SelectObject(&penCircle);
	pDC->Ellipse(pRect);
}

void CphhPrjDlg::drawLine(CDC* pDC, CRect pRect, int pLength)
{
	int nCPosL = pRect.left;
	int nCPosT = pRect.top;
	int nCPosR = pRect.right;
	int nCPosB = pRect.bottom;
	int nSumX = nCPosL + nCPosR;
	
	int nSumY = nCPosB + nCPosT;
	int nCenterX = nSumX / 2.0;
	int nCenterY = nSumY / 2.0;
	

	CPen penLine;
	penLine.CreatePen(PS_SOLID, 1, RGB(0xff, 0, 0));
	pDC->SelectObject(&penLine);
	pDC->MoveTo(nCenterX - pLength, nCenterY);
	pDC->LineTo(nCenterX + pLength, nCenterY);

	pDC->MoveTo(nCenterX, nCenterY - pLength);
	pDC->LineTo(nCenterX, nCenterY + pLength);
}

void CphhPrjDlg::drawBackColor()
{
	CDC* nDC = m_pDlgImage->GetDC();
	int nCMaxX = m_pDlgImage->m_Image.GetWidth();
	int nCMaxY = m_pDlgImage->m_Image.GetHeight();
	CRect nRect(0, 0, nCMaxX, nCMaxY);
	COLORREF fillColor = RGB(backColorRed, backColorGreen, backColorBlue);
	nDC->FillSolidRect(nRect, fillColor);
}

void CphhPrjDlg::OnBnClickedBtnChangeColor()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sColorRed;
	CString sColorGreen;
	CString sColorBlue;
	m_editRGBRed.GetWindowText(sColorRed);
	m_editRGBGreen.GetWindowText(sColorGreen);
	m_editRGBBlue.GetWindowText(sColorBlue);
	backColorRed = _ttoi(sColorRed);
	backColorGreen = _ttoi(sColorGreen);
	backColorBlue = _ttoi(sColorBlue);
	if (backColorRed < 255 && backColorGreen < 255 && backColorBlue < 255) {
		if (0 <= backColorRed && 0 <= backColorGreen && 0 <= backColorBlue) {
			UpdateData();
			m_editRGB.Format(_T("%s, %s, %s"), sColorRed, sColorGreen, sColorBlue);
			CDC* pDC = m_editRGBView.GetDC();
			CRect rect;
			m_editRGBView.GetClientRect(&rect);
			pDC->FillSolidRect(rect, RGB(backColorRed, backColorGreen, backColorBlue));
			m_editRGBView.ReleaseDC(pDC);
			UpdateData(FALSE);
		}
		
	}
	
	
	
	

}

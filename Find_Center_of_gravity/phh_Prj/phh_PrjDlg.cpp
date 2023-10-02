
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
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")


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
	, m_pDlgImage(nullptr)
	, editCenterX("0")
	, editCenterY("0")
	, backColorRed(0)
	, backColorGreen(0)
	, backColorBlue(0)
	, m_editRGB("0, 0, 0")
	, bakcColor(0xff)
	, nBackcolor(0x80)
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
	ON_BN_CLICKED(IDC_BTN_FIND_CENTER, &CphhPrjDlg::OnBnClickedBtnFindCenter)
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
	defaultSet();

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
	CString strRadius;
	m_editRadius.GetWindowText(strRadius);
	int nRadius = _ttoi(strRadius);
	if (nRadius > 0) {
		/*CRect nRect = rectData(nRadius);
		m_pDlgImage->DestroyWindow();
		delete m_pDlgImage;
		defaultSet();
		m_pDlgImage->Invalidate();
		m_pDlgImage->UpdateWindow();
		drawBackColor();*/
		drawCircle(nRadius); // 원그리기 기능
		//drawLine(nRect, 5);  // 중심점 십자가 기능
	}
}


//CRect CphhPrjDlg::rectData(int nRaidus)
//{
//
//	int nCMaxX = m_pDlgImage->m_Image.GetWidth();
//	int nCMaxY = m_pDlgImage->m_Image.GetHeight();
//	int nCPosL = rand() % (nCMaxX - nRaidus);
//	int nCPosT = rand() % (nCMaxY - nRaidus);
//	int nCPosR = nCPosL + nRaidus;
//	int nCPosB = nCPosT + nRaidus;
//	int nSumX = nCPosL + nCPosR;
//	int nSumY = nCPosB + nCPosT;
//	int nCenterX = nSumX / 2;
//	int nCenterY = nSumY / 2;
//	UpdateData();
//	editCenterX.Format(_T("%d"), nCenterX);
//	editCenterY.Format(_T("%d"), nCenterY);
//	UpdateData(FALSE);
//
//	CRect rect(nCPosL, nCPosT, nCPosR, nCPosB);
//	return rect;
//}

void CphhPrjDlg::drawCircle(int Raidus)
{
	/*CDC* pDC = m_pDlgImage->GetDC();
	CPen penCircle;


	penCircle.CreatePen(PS_SOLID, 5, RGB(0xff, 0xff, 0));

	pDC->SelectObject(&penCircle);
	pDC->Ellipse(Rect);
	m_pDlgImage->ReleaseDC(pDC);*/
	unsigned char* fm = (unsigned char*)m_pDlgImage->m_Image.GetBits();
	int nWidth = m_pDlgImage->m_Image.GetWidth();
	int nHeight = m_pDlgImage->m_Image.GetHeight();
	int nPitch = m_pDlgImage->m_Image.GetPitch();
	int x = rand() % nWidth;
	int y = rand() % nHeight;

	int nCenterX = x + Raidus;
	int nCenterY = y + Raidus;

	memset(fm, 255, nWidth * nHeight * 3);

	for (int j = y; j < y + Raidus * 2; j++) {
		for (int i = x; i < x + Raidus * 2; i++) {
			if (validImgPos(i, j)) {
				int nCircleSwitch = isInCircle(i, j, nCenterX, nCenterY, Raidus);
				if (nCircleSwitch == 1) {
					fm[j * nPitch + i * 3 + 0] = 0;
					fm[j * nPitch + i * 3 + 1] = 0xff;
					fm[j * nPitch + i * 3 + 2] = 0xff;
				}
				else if (nCircleSwitch == 2) {
					fm[j * nPitch + i * 3 + 0] = 0xff;
					fm[j * nPitch + i * 3 + 1] = 0xff;
					fm[j * nPitch + i * 3 + 2] = 0xff;
				}

				if (j == nCenterY) {
					if (i > nCenterX - 10 && i < nCenterX + 10) {
						fm[j * nPitch + i * 3 + 0] = 0;
						fm[j * nPitch + i * 3 + 1] = 0;
						fm[j * nPitch + i * 3 + 2] = 0xff;
					}
				}
				else if (i == nCenterX) {
					if (j > nCenterY - 10 && j < nCenterY + 10) {
						fm[j * nPitch + i * 3 + 0] = 0;
						fm[j * nPitch + i * 3 + 1] = 0;
						fm[j * nPitch + i * 3 + 2] = 0xff;
					}
				}
			}
		}
	}
	m_pDlgImage->Invalidate();
}
int CphhPrjDlg::isInCircle(int i, int j, int nCenterX, int nCenterY, int nRaidus)
{
	int bRet = 0;

	double dX = i - nCenterX;
	double dY = j - nCenterY;
	double dDist = (dX * dX) + (dY * dY);
	int nArea = nRaidus * nRaidus;
	int nRound = 5; // 원의 둘레
	if (dDist < nArea) {
		//bRet = 1;
		if (dDist > (nRaidus - nRound) * (nRaidus - nRound))
		{
			bRet = 1;
		}
		else {
			bRet = 2;
		}
	}
	return bRet;
}

BOOL CphhPrjDlg::validImgPos(int x, int y)
{
	int nWidth = m_pDlgImage->m_Image.GetWidth();
	int nHeight = m_pDlgImage->m_Image.GetHeight();
	CRect rect(0, 0, nWidth, nHeight);
	return rect.PtInRect(CPoint(x, y));
}

void CphhPrjDlg::drawLine(CRect rect, int length)
{
	/*CDC* pDC = m_pDlgImage->GetDC();
	CRect nRect = rect;

	int nLength = length;
	int nCPosL = nRect.left;
	int nCPosT = nRect.top;
	int nCPosR = nRect.right;
	int nCPosB = nRect.bottom;
	int nSumX = nCPosL + nCPosR;

	int nSumY = nCPosB + nCPosT;
	int nCenterX = (int)(nSumX / 2.0);
	int nCenterY = (int)(nSumY / 2.0);


	CPen penLine;
	penLine.CreatePen(PS_SOLID, 1, RGB(0xff, 0, 0));
	pDC->SelectObject(&penLine);
	pDC->MoveTo(nCenterX - nLength, nCenterY);
	pDC->LineTo(nCenterX + nLength, nCenterY);

	pDC->MoveTo(nCenterX, nCenterY - nLength);
	pDC->LineTo(nCenterX, nCenterY + nLength);
	m_pDlgImage->ReleaseDC(pDC);*/
}

void CphhPrjDlg::drawBackColor()
{

	/*CDC* pDC = m_pDlgImage->GetDC();
	int nCMaxX = m_pDlgImage->m_Image.GetWidth();
	int nCMaxY = m_pDlgImage->m_Image.GetHeight();

	CRect nRect(0, 0, nCMaxX, nCMaxY);
	bakcColor = RGB(backColorRed, backColorGreen, backColorBlue);
	pDC->FillSolidRect(nRect, bakcColor);

	m_pDlgImage->ReleaseDC(pDC);*/
}

void CphhPrjDlg::OnBnClickedBtnChangeColor()
{
	/*CString sColorRed;
	CString sColorGreen;
	CString sColorBlue;
	m_editRGBRed.GetWindowText(sColorRed);
	m_editRGBGreen.GetWindowText(sColorGreen);
	m_editRGBBlue.GetWindowText(sColorBlue);

	backColorRed = _ttoi(sColorRed);
	backColorGreen = _ttoi(sColorGreen);
	backColorBlue = _ttoi(sColorBlue);

	if (backColorRed < 256 && backColorGreen < 256 && backColorBlue < 256) {
		if (0 <= backColorRed && 0 <= backColorGreen && 0 <= backColorBlue) {
			UpdateData(TRUE);
			m_editRGB.Format(_T("%d, %d, %d"), backColorRed, backColorGreen, backColorBlue);
			CDC* pDC = m_editRGBView.GetDC();
			CRect rect;
			m_editRGBView.GetClientRect(&rect);
			pDC->FillSolidRect(rect, RGB(backColorRed, backColorGreen, backColorBlue));
			ReleaseDC(pDC);
			UpdateData(FALSE);
			drawBackColor();
		}
	}*/
}

void CphhPrjDlg::defaultSet()
{
	m_pDlgImage = new CDlgImage;
	m_pDlgImage->Create(IDD_DLGIMAGE, this);
	m_pDlgImage->ShowWindow(SW_SHOW);
	m_pDlgImage->MoveWindow(0, 0, m_pDlgImage->m_Image.GetWidth(), m_pDlgImage->m_Image.GetHeight());

}


void CphhPrjDlg::OnBnClickedBtnFindCenter()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	unsigned char* fm = (unsigned char*)m_pDlgImage->m_Image.GetBits();
	int nWidth = m_pDlgImage->m_Image.GetWidth();
	int nHeight = m_pDlgImage->m_Image.GetHeight();
	int nPitch = m_pDlgImage->m_Image.GetPitch();

	int nTh = 0;
	CRect rect(0, 0, nWidth, nHeight);
	int nSumX = 0;
	int nSumY = 0;
	int nCount = 0;
	for (int j = rect.top; j < rect.bottom; j++) {
		for (int i = rect.left; i < rect.right; i++) {
			if (fm[j * nPitch + i * 3] == nTh) {
				/*int nTh_1 = fm[j * nPitch + i * 3];
				std::cout << nTh_1 << std::endl;*/
				nSumX += i;
				nSumY += j;
				nCount++;
			}
		}
	}
	double dCenterX = (double)nSumX / nCount;
	double dCenterY = (double)nSumY / nCount;
	std::cout << "Center.X : " << dCenterX << ", Center.Y : " << dCenterY << std::endl;
	UpdateData();
	editCenterX.Format(_T("%f"), dCenterX);
	editCenterY.Format(_T("%f"), dCenterY);
	UpdateData(false);


}

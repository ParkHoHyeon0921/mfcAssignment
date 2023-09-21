
// mfcCImageDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "mfcCImage.h"
#include "mfcCImageDlg.h"
#include "afxdialogex.h"
#include <functional> // std::ref를 사용하기 위해 필요한 헤더

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <thread>
using namespace std;


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


// CmfcCImageDlg 대화 상자



CmfcCImageDlg::CmfcCImageDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCIMAGE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmfcCImageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_STOP, m_cStopBtn);
}

BEGIN_MESSAGE_MAP(CmfcCImageDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_IMAGE, &CmfcCImageDlg::OnBnClickedBtnImage)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CmfcCImageDlg::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_LOAD, &CmfcCImageDlg::OnBnClickedBtnLoad)
	ON_BN_CLICKED(IDC_BTN_ACTION, &CmfcCImageDlg::OnBnClickedBtnAction)
	ON_BN_CLICKED(IDC_BTN_STOP, &CmfcCImageDlg::OnBnClickedBtnStop)
END_MESSAGE_MAP()


// CmfcCImageDlg 메시지 처리기

BOOL CmfcCImageDlg::OnInitDialog()
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

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CmfcCImageDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CmfcCImageDlg::OnPaint()
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
HCURSOR CmfcCImageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CmfcCImageDlg::OnBnClickedBtnImage()
{
	int nWidth = 640; // n만 붙으면 지역변수 m이붙으면 클래스변수
	int nHeight = 480;  // 수치를 변수화 하면 유연한 프로그램 구성에 도움이됨
	int nBpp = 8; // Gray Level

	ImageDistroy();
	m_image.Create(nWidth, -nHeight, nBpp);
	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		m_image.SetColorTable(0, 256, rgb);
	}

	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits(); // 내가 만든 이미지의 첫번째 포인터 값을 가져오겠다.

	memset(fm, 0xff, sizeof(unsigned char) * nWidth * nHeight);

	//for (int j = 0; j < nHeight; j++) {
	//	for (int i = 0; i < nWidth; i++) {
	//		//fm[j * nPitch + i] = j*60 % 255; // 그라데이션
	//		//fm[j * nPitch + i] = 128; // 회색
	//		fm[j * nPitch + i] = j%255; // 하얀색
	//	}
	//}

	/*fm[12 * nPitch + 16] = 0;
	fm[0 * nPitch + 0] = 128;
	fm[0 * nPitch + 1] = 128;
	fm[1 * nPitch + 0] = 128;*/

	//// 절반을 다른색으로 변경하기
	/*for (int j = 0; j < nHeight / 2; j++) {
		for (int i = 0; i < nWidth / 2; i++) {
			fm[j * nPitch + i] = 128;
		}
	}*/

	UpdateDisplay();
}

CString g_strFileImage = (_T("c:\\image\\save.bmp"));
void CmfcCImageDlg::OnBnClickedBtnSave()
{
	m_image.Save(g_strFileImage);
}


void CmfcCImageDlg::OnBnClickedBtnLoad()
{
	ImageDistroy();
	// 없애고나서 다시 뿌려야함
	m_image.Load(g_strFileImage);
	UpdateDisplay();

}

void CmfcCImageDlg::UpdateDisplay()
{
	CClientDC dc(this); // CClientDC형태의 dc변수를 만들어놓고 this에 초기화하겠다. this는 현재 다이어로그다
	m_image.Draw(dc, 0, 0); // 그리겠다. dc를 0, 0에다가
}

void CmfcCImageDlg::ImageDistroy()
{
	// 로드하기전 CImage를 정리해야함
	if (m_image != NULL) {
		m_image.Destroy();
	}
}

void CmfcCImageDlg::moveRect()
{
	static int nSttX = rand() % m_image.GetWidth();
	static int nSttY = rand() % m_image.GetHeight();

	int nGray = 10;
	int nWidth = m_image.GetWidth(); // n만 붙으면 지역변수 m이붙으면 클래스변수
	int nHeight = m_image.GetHeight();  // 수치를 변수화 하면 유연한 프로그램 구성에 도움이됨
	int nPitch = m_image.GetPitch();
	int nRadius = 10;
	unsigned char* fm = (unsigned char*)m_image.GetBits(); // 내가 만든 이미지의 첫번째 포인터 값을 가져오겠다.


	//memset(fm, 0xff, nWidth * nHeight);

	DrawCircle(fm, nSttX, nSttY, nRadius, nGray);


	/*for (int j = nSttY; j < nSttY + 48; j++) {
		for (int i = nSttX; i < nSttX + 64; i++) {
			if (nSttX == 0 || nSttY == 0) {
				validImgSwitch = false;
			}
			if(validImgPos(i, j))
				fm[j * nPitch + i] = nGray;
			else
			{
				validImgSwitch = true;
			}
		}
	}*/

	if (validXSwitch == true) {
		nSttX++;
		
	}
	else {
		nSttX--;
	}
	if (validYSwitch == true) {
		nSttY++;
	}
	else {
		nSttY--;
	}
	UpdateDisplay();
}


void CmfcCImageDlg::OnBnClickedBtnAction()
{
	// std::thread를 사용하여 람다 함수를 호출하고 클래스 인스턴스를 전달
	std::thread t1([this] { ThreadMoveRect(); });
	t1.detach();
}

void CmfcCImageDlg::ThreadMoveRect()
{
	while (true) {
		if (threadSwitch == false) {
			continue;
		}
		moveRect();
	}
}

BOOL CmfcCImageDlg::validImgPos(int x, int y)
{
	// 변수를 한번 쓰면 계속 쓸수 있겠끔함
	int nWidth = m_image.GetWidth(); // 넓이
	int nHeight = m_image.GetHeight(); // 높이
	CRect rect(0, 0, nWidth, nHeight);

	return rect.PtInRect(CPoint(x, y)); // 어떤 포인트가 그 영역에 들어가냐 bool값으로 알려줌.;
}

void CmfcCImageDlg::DrawCircle(unsigned char* fm, int x, int y, int nRadius, int nGray)
{
	int nCenterX = x + nRadius;
	int nCenterY = y + nRadius;
	int nPitch = m_image.GetPitch();

	for (int j = y; j < y + nRadius * 2; j++) {
		for (int i = x; i < x + nRadius * 2; i++) {
			if (x <= 0) {
				validXSwitch = true;
			}
			else if (x >= m_image.GetWidth()){
				validXSwitch = false;
			}
			if (y <= 0) {
				validYSwitch = true;
			}
			else if (y >= m_image.GetHeight()) {
				validYSwitch = false;
			}
			
			if (validImgPos(i, j)) {
				if (isInCircle(i, j, nCenterX, nCenterY, nRadius))
					fm[j * nPitch + i] = nGray;
			}
		}
	}
}

bool CmfcCImageDlg::isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius)
{
	// 사각형 형태에 원을 그리는것
	bool bRet = false;
	
	double dX = i - nCenterX;
	double dY = j - nCenterY;
	double dDist = dX * dX + dY * dY;

	if (dDist < nRadius * nRadius) {
		return !bRet;
	}

	return bRet;
}

void CmfcCImageDlg::OnBnClickedBtnStop()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (threadSwitch == true) {
		threadSwitch = false;
		m_cStopBtn.SetWindowTextW(_T("Play"));
	}
	else if(threadSwitch == false) {
		threadSwitch = true;
		m_cStopBtn.SetWindowTextW(_T("Stop"));
	}

}

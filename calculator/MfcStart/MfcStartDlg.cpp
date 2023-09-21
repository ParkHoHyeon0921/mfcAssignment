
// MfcStartDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MfcStart.h"
#include "MfcStartDlg.h"
#include "afxdialogex.h"
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CMfcStartDlg 대화 상자



CMfcStartDlg::CMfcStartDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCSTART_DIALOG, pParent)
	, m_sInputNum("0")
	, m_nCalculationNum(0)
	, m_sResult("")
	, m_bCalculation(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMfcStartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_TITLE, m_Title);
	DDX_Text(pDX, IDC_EDIT3, m_sInputNum);
	DDX_Text(pDX, IDC_EDIT4, m_sResult);
}

BEGIN_MESSAGE_MAP(CMfcStartDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Btn_CaNCEL, &CMfcStartDlg::OnBnClickedBtnCancel)
	ON_BN_CLICKED(IDC_BUTTON13, &CMfcStartDlg::OnBnClickedButtonNum)
	ON_BN_CLICKED(IDC_BUTTON19, &CMfcStartDlg::OnBnClickedButtonNum)
	ON_BN_CLICKED(IDC_BUTTON25, &CMfcStartDlg::OnBnClickedButtonNum)
	ON_BN_CLICKED(IDC_BUTTON12, &CMfcStartDlg::OnBnClickedButtonNum)
	ON_BN_CLICKED(IDC_BUTTON18, &CMfcStartDlg::OnBnClickedButtonNum)
	ON_BN_CLICKED(IDC_BUTTON24, &CMfcStartDlg::OnBnClickedButtonNum)
	ON_BN_CLICKED(IDC_BUTTON11, &CMfcStartDlg::OnBnClickedButtonNum)
	ON_BN_CLICKED(IDC_BUTTON17, &CMfcStartDlg::OnBnClickedButtonNum)
	ON_BN_CLICKED(IDC_BUTTON23, &CMfcStartDlg::OnBnClickedButtonNum)
	ON_BN_CLICKED(IDC_BUTTON16, &CMfcStartDlg::OnBnClickedButtonNum)
	ON_BN_CLICKED(IDC_BUTTON20, &CMfcStartDlg::DoRefreshFunction)
	ON_BN_CLICKED(IDC_BUTTON29, &CMfcStartDlg::DoResultFunction)
	ON_BN_CLICKED(IDC_BUTTON30, &CMfcStartDlg::DoResultFunction)
	ON_BN_CLICKED(IDC_BUTTON31, &CMfcStartDlg::DoResultFunction)
	ON_BN_CLICKED(IDC_BUTTON32, &CMfcStartDlg::DoResultFunction)
	ON_BN_CLICKED(IDC_BUTTON28, &CMfcStartDlg::DoResultFunction)
	ON_BN_CLICKED(IDC_BUTTON26, &CMfcStartDlg::DoBackSpaceFunction)
	ON_BN_CLICKED(IDC_Btn_CaNCEL2, &CMfcStartDlg::OnBnClickedBtnCancel2)
END_MESSAGE_MAP()


// CMfcStartDlg 메시지 처리기

BOOL CMfcStartDlg::OnInitDialog()
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
	m_TitleFont.CreatePointFont(120, _T("굴림"));
	m_Title.SetFont(&m_TitleFont, TRUE);
	
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMfcStartDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMfcStartDlg::OnPaint()
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
HCURSOR CMfcStartDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMfcStartDlg::OnBnClickedBtnCancel()
{
	// 화면 종료 기능
	OnOK();
}

void CMfcStartDlg::OnBnClickedBtnCancel2()
{
	// 화면 숨김 기능
	CloseWindow();
}

void CMfcStartDlg::OnBnClickedButtonNum()
{
	// 클릭된 버튼의 캡션 가져오기 로직
	UINT m_nBtnID = ((CButton*)GetFocus())->GetDlgCtrlID();
	CString m_sBtnCaption;
	GetDlgItemText(m_nBtnID, m_sBtnCaption);

	// m_bCalculation이 false일 경우 입력 값을 화면에 반영
	if (m_bCalculation == false) 
	{
		UpdateData(TRUE); // 변수의 값을 화면에 반영
		DoSaveNum(m_sBtnCaption);
		m_sInputNum = m_sSaveNum;
		UpdateData(FALSE); // 변수의 값을 화면에 반영
	}
	else 
	{
		m_sSaveNum = "";
		UpdateData(TRUE); // 변수의 값을 화면에 반영
		DoSaveNum(m_sBtnCaption);
		m_sInputNum = m_sSaveNum;
		UpdateData(FALSE); // 변수의 값을 화면에 반영
		m_bCalculation = false;
	}
}

void CMfcStartDlg::DoSaveNum(CString Num) 
{
	// 숫자의 길이를 더하는 기능 예(1 -> 12)
	m_sSaveNum = m_sSaveNum + Num;
}

void CMfcStartDlg::DoRefreshFunction()
{
	// 사칙연산 또는 결과 버튼 클릭시 갱신 기능
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_sSaveNum = "";
	m_sResult = "";
	m_sInputNum = "0";
	m_nCalculationNum = 0;
	UpdateData(FALSE);
}


void CMfcStartDlg::DoResultFunction()
{

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UINT m_nBtnID = ((CButton*)GetFocus())->GetDlgCtrlID();
	CString m_sBtnCaption;
	GetDlgItemText(m_nBtnID, m_sBtnCaption);
	
	
	if (m_bCalculation) 
	{
		UpdateData(TRUE);
		int length = m_sResult.GetLength();
		m_sResult = m_sResult.Left(length - 1) + m_sBtnCaption;
		UpdateData(FALSE);
	}
	else
	{
		UpdateData(TRUE);
		m_sResult = m_sResult + " " + m_sSaveNum + " " + m_sBtnCaption;
		UpdateData(FALSE);

		UpdateData(TRUE);
		resultList = DoSplitFunction();
		DoCalculationFunction(resultList);
		if (m_sBtnCaption == "=") 
		{
			m_sResult = "";
		}
		UpdateData(FALSE);
	}
	
	m_bCalculation = true;
	
}

void CMfcStartDlg::DoCalculationFunction(std::list<CString> calculationList)
{
	// 계산기능
	// for문을 이용하여 list 내부 값이 숫자인지 산술 연산자인지 구분하여 계산
	// 파라미터 : std::list<CString> calculationList
	UINT m_nSumNum = 0;
	UINT m_nSwitch = 1;
	BOOL m_bSwitch = TRUE;
	for (const auto& element : calculationList)
	{
		if (m_bSwitch == FALSE)
		{
			
			if (m_nSwitch == 1)
			{
				m_nSumNum = m_nSumNum + _ttoi(element);
			}
			else if (m_nSwitch == 2)
			{
				m_nSumNum = m_nSumNum - _ttoi(element);
			}
			else if (m_nSwitch == 3)
			{
				m_nSumNum = m_nSumNum * _ttoi(element);
			}
			else if (m_nSwitch == 4)
			{
				m_nSumNum = m_nSumNum / _ttoi(element);
			}
			m_bSwitch = TRUE;
		}
		else if (m_bSwitch == TRUE) 
		{
			if (element == "＋")
			{
				m_nSwitch = 1;
			}
			else if (element == "－")
			{
				m_nSwitch = 2;
			}
			else if (element == "×")
			{
				m_nSwitch = 3;
			}
			else if (element == "÷")
			{
				m_nSwitch = 4;
			}
			m_bSwitch = FALSE;
		}
		
	}
	UpdateData(TRUE);
	m_sInputNum.Format(_T("%d"), m_nSumNum);
	UpdateData(FALSE);
}

std::list<CString> CMfcStartDlg::DoSplitFunction()
{
	// 스플릿 기능
	// return : 스플릿 된 값을 list<CString>형으로 반환 예) [1, +, 1]
	std::list<CString> splitstrList;
	CString m_sSplitStr("");
	CString m_sSumStr("");
	
	int length = m_sResult.GetLength();

	UpdateData(TRUE);
	for (int i = 0; i < length; i++) {
		m_sSplitStr = m_sResult[i];
		if (m_sSplitStr == " ")
		{
			splitstrList.push_back(m_sSumStr);
			m_sSumStr = "";
		}
		else
		{
			m_sSumStr += m_sSplitStr;
		}
	}
	UpdateData(FALSE);
	return splitstrList;
}



void CMfcStartDlg::DoBackSpaceFunction()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 백스페이스바 지우기 기능
	UpdateData(TRUE);
	int len = m_sInputNum.GetLength();
	CString Num = m_sInputNum.Mid(0, len - 1);
	m_sInputNum =  Num;
	m_sSaveNum = Num;
	UpdateData(FALSE);
}




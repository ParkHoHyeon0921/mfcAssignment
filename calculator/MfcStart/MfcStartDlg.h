
// MfcStartDlg.h: 헤더 파일
//

#pragma once
#include <list>
//#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")

// CMfcStartDlg 대화 상자
class CMfcStartDlg : public CDialogEx
{
// 생성입니다.
public:
	CMfcStartDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCSTART_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// 제목 폰트 사이즈
	CFont m_TitleFont;
	// 제목
	CStatic m_Title;
	// 숫자 입력칸 폰트 사이즈
	CFont m_InPutFont;
	// 숫자 출력 값
	CString m_sInputNum;
	// 저장할 숫자 값
	CString m_sSaveNum;
	// 연산 과정 출력문
	CString m_sResult;
	// 계산할 숫자 값
	UINT m_nCalculationNum;
	// 연산 조건
	bool m_bCalculation;
	// 계산할 값을 리스트에 저장
	std::list<CString> resultList;
	// 삭제 기능
	afx_msg void OnBnClickedBtnCancel();
	// 번호 입력 기능
	afx_msg void OnBnClickedButtonNum();
	afx_msg void DoRefreshFunction();
	void DoSaveNum(CString Num);
	void DoCalculationFunction(std::list<CString> calculationList);
	std::list<CString> DoSplitFunction();
	
	afx_msg void DoResultFunction();
	afx_msg void DoBackSpaceFunction();
	afx_msg void OnBnClickedBtnCancel2();
};

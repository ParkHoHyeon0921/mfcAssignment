﻿
// mfcCImageDlg.h: 헤더 파일
//

#pragma once


// CmfcCImageDlg 대화 상자
class CmfcCImageDlg : public CDialogEx
{
private: // 이 밑은 전부 private라고 선언하는것
	CImage m_image;
	BOOL validImgPos(int x, int y);
	BOOL validXSwitch = true;
	BOOL validYSwitch = true;
	BOOL threadSwitch = true;
	// 생성입니다.
public:  // 이것 또한 이 밑은 전부 public라고 선언하는것
	CmfcCImageDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCCIMAGE_DIALOG };
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
	afx_msg void OnBnClickedBtnImage();
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnBnClickedBtnLoad();
	void UpdateDisplay();
	void ImageDistroy();
	void moveRect();
	void DrawCircle(unsigned char* fm, int i, int j, int nRadius, int nGray);
	bool isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius);
	void ThreadMoveRect();
	afx_msg void OnBnClickedBtnAction();
	afx_msg void OnBnClickedBtnStop();
	CButton m_cStopBtn;
};

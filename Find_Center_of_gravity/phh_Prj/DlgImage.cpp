﻿// DlgImage.cpp: 구현 파일
//


#include "pch.h"
#include "phh_Prj.h"
#include "afxdialogex.h"
#include "DlgImage.h"
#include "phh_PrjDlg.h"

// CDlgImage 대화 상자

IMPLEMENT_DYNAMIC(CDlgImage, CDialogEx)

CDlgImage::CDlgImage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLGIMAGE, pParent){
	m_pParent = pParent;
}

CDlgImage::~CDlgImage()
{
}

void CDlgImage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgImage, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDlgImage 메시지 처리기


BOOL CDlgImage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	MoveWindow(0, 0, 640, 480);
	InitImage();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

 
void CDlgImage::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	if (m_Image) {
		m_Image.Draw(dc, 0, 0);
	}
}


void CDlgImage::InitImage()
{
	int nWidth = IMAGE_WIDTH;
	int nHeight = IMAGE_HEIGHT;
	int nBpp = 24;

	m_Image.Create(nWidth, -nHeight, nBpp);
	/*if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++) {
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		}
		m_Image.SetColorTable(0, 256, rgb);
	}*/
	
	int nPitch = m_Image.GetPitch();
	
	unsigned char* fm = (unsigned char*)m_Image.GetBits();
	
	memset(fm, 0x80, nWidth * nHeight * 3);
}
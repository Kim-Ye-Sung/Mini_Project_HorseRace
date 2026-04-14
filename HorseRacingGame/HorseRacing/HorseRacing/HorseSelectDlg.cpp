#include "pch.h"
#include "HorseSelectDlg.h"
#include "HorseRacing.h"
#include "afxdialogex.h"
#include "NormalHorse.h"


IMPLEMENT_DYNAMIC(CHorseSelectDlg, CDialogEx)

CHorseSelectDlg::CHorseSelectDlg(CWnd* pParent) :CDialogEx(IDD_HORSE_SELECT_DIALOG, pParent)
{
	MyHorse = std::make_unique<NormalHorse>();
}

void CHorseSelectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BOOL CHorseSelectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	return TRUE;
}

void CHorseSelectDlg::OnPaint()
{
    CPaintDC dc(this);
    CDialogEx::OnPaint();

    if (MyHorse)
    {
        CImage& img = MyHorse->GetHorseImage();

        if (!img.IsNull())
        {
            int originalW = img.GetWidth();     // 원본 그림 크기 저장
            int originalH = img.GetHeight();

            int drawW = originalW / 4;  // 원본 그림 크기의 4분의1만큼의 크기 저장
            int drawH = originalH / 4;

            img.Draw(dc.m_hDC, 10, 10, drawW, drawH);  // 10,10의 위치에 내가 설정한 크기로 그림 출력
        }
    }
}

BEGIN_MESSAGE_MAP(CHorseSelectDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()
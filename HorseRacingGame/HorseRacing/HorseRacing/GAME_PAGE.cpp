#include "pch.h"
#include "GAME_PAGE.h"
#include "HorseRacing.h"
#include "HorseRacingDlg.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(CGAME_PAGE, CDialogEx)

CGAME_PAGE::CGAME_PAGE(CWnd* pParent) : CDialogEx(IDD_GAMEPAGE, pParent)
{
}

void CGAME_PAGE::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BOOL CGAME_PAGE::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	MoneyFont.CreatePointFont(250, _T("Microsoft Sans Serif"));	 // 머니폰트의 글꼴 크기를 30과 글꼴을 "Microsoft Sans Serif"로 설정
	GetDlgItem(MoneyText)->SetFont(&MoneyFont);  // MoneyText에 폰트 적용
	GetDlgItem(HandMoneyText)->SetFont(&MoneyFont);
	GetDlgItem(LoanText)->SetFont(&MoneyFont);
	GetDlgItem(LoanMoneyText)->SetFont(&MoneyFont);
	GetDlgItem(RepaymentText)->SetFont(&MoneyFont);
	GetDlgItem(RepaymentDateText)->SetFont(&MoneyFont);

	return TRUE;
}

BEGIN_MESSAGE_MAP(CGAME_PAGE, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CGAME_PAGE::OnBnClickedButton1)
	ON_BN_CLICKED(HolseSelectButton, &CGAME_PAGE::OnBnClickedHolseselectbutton)
END_MESSAGE_MAP()


void CGAME_PAGE::SetMoneysText()
{
	if (!Player)
	{
		return;
	}

	CString strLoanMoney;
	strLoanMoney.Format(_T("%dG"), Player->GetLoanMoney());
	GetDlgItem(LoanMoneyText)->SetWindowText(strLoanMoney);

	CString strDDay;
	strDDay.Format(_T("D - %d"), Player->GetDDay());
	GetDlgItem(RepaymentDateText)->SetWindowText(strDDay);

}

void CGAME_PAGE::OnBnClickedButton1()
{
	CHorseRacingDlg* pMain = (CHorseRacingDlg*)GetParent();

	if (pMain)	// 부모의 주소창이 제대로 있으면 실행
	{
		pMain->ShowMainControls(true);
		this->ShowWindow(SW_HIDE);
	}
}

void CGAME_PAGE::RefreshGamePage()
{
	SetMoneysText();
}

void CGAME_PAGE::OnBnClickedHolseselectbutton()
{
	CHorseRacingDlg* pMain = (CHorseRacingDlg*)GetParent();

	if (pMain)	// 부모의 주소창이 제대로 있으면 실행
	{
		this->ShowWindow(SW_HIDE);
		pMain->ShowHorseSelectPage();
	}
}

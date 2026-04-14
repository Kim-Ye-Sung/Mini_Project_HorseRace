#pragma once

class CGAME_PAGE : public CDialogEx
{
	DECLARE_DYNAMIC(CGAME_PAGE)

public:

	CGAME_PAGE(CWnd* pParent = nullptr);

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAMEPAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	BOOL OnInitDialog() override;

	DECLARE_MESSAGE_MAP()

private:
	CFont MoneyFont;	// 폰트 설정 변수

	class PlayerUser* Player = nullptr;

	void SetMoneysText();

public:
	afx_msg void OnBnClickedButton1();

	inline void SetPlayer(PlayerUser* Player) { this->Player = Player; }

	void RefreshGamePage();

	afx_msg void OnBnClickedHolseselectbutton();
};


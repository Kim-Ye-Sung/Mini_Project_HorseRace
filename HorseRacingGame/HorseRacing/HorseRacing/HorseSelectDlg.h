#pragma once

#include <memory>
#include "Horse.h"

class CHorseSelectDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHorseSelectDlg)

public:

	CHorseSelectDlg(CWnd* pParent = nullptr);

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HORSE_SELECT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	BOOL OnInitDialog() override;

	DECLARE_MESSAGE_MAP()

private:
	std::unique_ptr<Horse> MyHorse = nullptr;

public:
	afx_msg void OnPaint();
};


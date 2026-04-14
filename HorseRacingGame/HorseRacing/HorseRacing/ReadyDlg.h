#pragma once
class CReadyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CReadyDlg)

public:
	CReadyDlg(CWnd* pParent = nullptr);

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_READY_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	BOOL OnInitDialog() override;

	DECLARE_MESSAGE_MAP()
};


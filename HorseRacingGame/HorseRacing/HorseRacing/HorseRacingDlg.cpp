
// HorseRacingDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "HorseRacing.h"
#include "HorseRacingDlg.h"
#include "afxdialogex.h"

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


// CHorseRacingDlg 대화 상자



CHorseRacingDlg::CHorseRacingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HORSERACING_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHorseRacingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CHorseRacingDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(GameStartButton, &CHorseRacingDlg::OnBnClickedGamestartbutton)
	ON_BN_CLICKED(ExitButton, &CHorseRacingDlg::OnBnClickedExitbutton)
END_MESSAGE_MAP()


// CHorseRacingDlg 메시지 처리기

BOOL CHorseRacingDlg::OnInitDialog()
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

	CreateChildPage();	// 자식 페이지 추가

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CHorseRacingDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CHorseRacingDlg::OnPaint()
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
HCURSOR CHorseRacingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CHorseRacingDlg::OnBnClickedGamestartbutton()
{
	//SetDlgItemText(GameStartButton, _T("버튼이 눌렸습니다"));	// 객체의 텍스트를 변경

	ShowGamePage();
}

void CHorseRacingDlg::OnBnClickedExitbutton()
{
	//EndDialog(IDCANCEL);		// 프로그램을 종료한다.
	OnCancel();	 // 동일하게 프로그램을 종료하는 함수이다.
}

void CHorseRacingDlg::CreateChildPage()
{
	// 자식 페이지 생성
	GamePage_Obj.Create(IDD_GAMEPAGE, this);
	HorseSelect_Obj.Create(IDD_HORSE_SELECT_DIALOG, this);
	ReadyDlg_Obj.Create(IDD_READY_DIALOG, this);

	// 페이지 위치 지정
	CRect rc;
	GetClientRect(&rc);



	// 부모 다이얼로그 내부 전체를 페이지 영역으로 사용
	GamePage_Obj.MoveWindow(&rc);
	HorseSelect_Obj.MoveWindow(&rc);
	ReadyDlg_Obj.MoveWindow(&rc);

	// 위의 코드와 동일하게 부모 다이얼로그 내부 전체를 페이지 영역으로 사용한다.
	//GamePage_Obj.SetWindowPos(
	//	nullptr,
	//	rc.left,
	//	rc.top,
	//	rc.Width(),
	//	rc.Height(),
	//	SWP_NOZORDER
	//);

	ShareUser();
}

void CHorseRacingDlg::ShowGamePage()
{
	//this->ShowWindow(SW_HIDE);  // 이 코드는 절대 활성화 해서는 안된다. 
							      // 이 코드가 실행되면 부모의 창이 숨겨지고, 부모의 창이 숨겨지는 순간 프로그램이 종료된다.
	
	ShowMainControls(false);   // 따라서 부모 창에 있는 컨트롤들을 숨겨주는 함수를 따로 실행한다.

	GamePage_Obj.RefreshGamePage();		// 화면 설정을 먼저 하고
	GamePage_Obj.ShowWindow(SW_SHOW);	// 화면을 보여준다.
}

void CHorseRacingDlg::ShowHorseSelectPage()
{
	HorseSelect_Obj.HideSelectButton();
	HorseSelect_Obj.ShowWindow(SW_SHOW);
}

void CHorseRacingDlg::ShowReadyPage()
{
	ReadyDlg_Obj.ShowWindow(SW_SHOW);
}

void CHorseRacingDlg::ShareUser()
{
	GamePage_Obj.SetPlayer(&UserObj);
	HorseSelect_Obj.SetPlayer(&UserObj);
}

void CHorseRacingDlg::ShowMainControls(bool bshow)
{
	int bShow = bshow ? SW_SHOW : SW_HIDE;

	CWnd* pChild = GetWindow(GW_CHILD);

	while (pChild != nullptr)	// 현재 조절해야할 컨트롤러가 있다면
	{
		pChild->ShowWindow(bShow);	// 그 컨트롤러의 모습을 보이던가 숨기던가 해라

		pChild = pChild->GetNextWindow();	// 다음 컨트롤러를 찾아라.
	}
}

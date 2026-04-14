#include "pch.h"

// CHorseSelectDlg 클래스 선언이 들어있는 헤더
#include "HorseSelectDlg.h"

// 프로젝트 전체 헤더
#include "HorseRacing.h"

// MFC 다이얼로그 확장 기능 관련 헤더
#include "afxdialogex.h"

// 실제 말 객체로 사용할 NormalHorse 헤더
#include "NormalHorse.h"

#include "PlayerUser.h"
#include "HorseRacingDlg.h"

// MFC 런타임 클래스 정보 등록용 매크로
IMPLEMENT_DYNAMIC(CHorseSelectDlg, CDialogEx)


// 생성자
// CHorseSelectDlg 객체가 생성될 때 실행된다.
CHorseSelectDlg::CHorseSelectDlg(CWnd* pParent)
    : CDialogEx(IDD_HORSE_SELECT_DIALOG, pParent)
{
    Horses.push_back(std::make_unique<NormalHorse>());
    Horses.push_back(std::make_unique<NormalHorse>());
    Horses.push_back(std::make_unique<NormalHorse>());
    Horses.push_back(std::make_unique<NormalHorse>());
    Horses.push_back(std::make_unique<NormalHorse>());
}


// MFC 데이터 교환 함수
// UI 컨트롤과 멤버 변수 연결에 사용된다.
// 현재는 특별히 연결하는 것이 없어서 기본 호출만 유지한다.
void CHorseSelectDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}


// 다이얼로그 초기화 함수
// Create() 후, 화면이 실제 준비되는 시점에 한 번 호출된다.
BOOL CHorseSelectDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    return TRUE;
}


// 화면을 다시 그릴 필요가 있을 때 호출되는 함수
//
// 호출되는 경우 예시:
// 1. 다이얼로그가 처음 나타날 때
// 2. 창이 가려졌다가 다시 드러날 때
// 3. Invalidate() 호출로 재그리기가 요청됐을 때
void CHorseSelectDlg::OnPaint()
{
    // 실제 그림을 그릴 디바이스 컨텍스트 생성
    CPaintDC dc(this);

    // 부모 클래스 기본 그리기 처리
    CDialogEx::OnPaint();

    // 현재 다이얼로그 내부의 사용 가능한 클라이언트 영역을 얻는다.
    CRect clientRect;
    GetClientRect(&clientRect);

    // 카드 바깥 여백
    const int margin = 20;

    // 카드와 카드 사이 간격
    const int gap = 15;

    // 한 화면에 배치할 카드 수
    const int cardCount = 5;

    // 카드들 사이에 들어가는 전체 간격 계산
    // 카드가 5개면 간격은 4군데 생긴다.
    int totalGap = gap * (cardCount - 1);

    // 실제 카드들이 차지할 수 있는 전체 가로폭
    // 전체 너비에서 좌우 마진과 카드 사이 간격을 뺀 값
    int usableWidth = clientRect.Width() - margin * 2 - totalGap;

    // 카드 한 장의 너비
    int cardWidth = usableWidth / cardCount;

    // 카드 한 장의 높이
    int cardHeight = 300;

    // 첫 번째 카드가 시작될 x 좌표
    int startX = margin;

    // 카드들이 배치될 y 좌표
    int startY = 40;

    // 각 카드에 표시할 말 이름
    // 현재는 Horse 객체 안에 이름이 없어서
    // 임시로 여기서 배열로 관리한다.
    CString names[5] =
    {
        _T("기본마"),
        _T("슬로우스타터"),
        _T("폭주마"),
        _T("안정형"),
        _T("고위험형")
    };

    // 각 카드에 표시할 설명 문자열
    CString descs[5] =
    {
        _T("초보자용\n무난한 성능"),
        _T("후반에 강해짐"),
        _T("한번 터지면 빠름"),
        _T("확률 변동이 적음"),
        _T("기복이 크지만 강력")
    };

    // 다시 그릴 때마다 카드 위치 목록을 비운다.
    //
    // 이유:
    // OnPaint()는 여러 번 호출될 수 있으므로,
    // 이전에 저장된 위치가 남아 있으면 중복 저장될 수 있다.
    HorseCardRects.clear();

    // 카드 5개를 순서대로 그린다.
    for (int i = 0; i < cardCount && i < (int)Horses.size(); ++i)
    {
        // 현재 카드의 x 좌표 계산
        // 카드 하나의 너비 + 간격 만큼 오른쪽으로 이동
        int x = startX + i * (cardWidth + gap);

        // 현재 카드 전체 영역 생성
        CRect cardRect(x, startY, x + cardWidth, startY + cardHeight);

        // 클릭 판정을 위해 이 카드의 위치를 저장
        // 나중에 OnLButtonDown()에서 point가 이 rect 안에 있는지 검사한다.
        HorseCardRects.push_back(cardRect);

        // 현재 카드가 선택된 카드인지 검사
        // 선택된 카드이면 true, 아니면 false
        bool isSelected = (i == SelectedCardIndex);

        // 카드 하나를 실제로 그리는 함수 호출
        DrawHorseCard(dc, cardRect, Horses[i].get(), names[i], descs[i], isSelected);
    }
}


// 카드 한 장을 그리는 함수
void CHorseSelectDlg::DrawHorseCard(CDC& dc, const CRect& cardRect, Horse* horse, const CString& name, const CString& desc, bool isSelected)
{
    // 카드 전체 배경을 밝은 회색으로 채운다.
    dc.FillSolidRect(cardRect, RGB(245, 245, 245));

    // 일반 카드 테두리용 펜
    // 검정색, 두께 1
    CPen normalPen(PS_SOLID, 1, RGB(0, 0, 0));

    // 선택된 카드 테두리용 펜
    // 빨간색, 두께 3
    CPen selectedPen(PS_SOLID, 3, RGB(255, 0, 0));

    // 원래 사용 중이던 펜을 저장할 포인터
    CPen* oldPen = nullptr;

    // 현재 카드가 선택된 상태라면 빨간 펜 사용
    // 아니면 일반 검정 펜 사용
    if (isSelected)
        oldPen = dc.SelectObject(&selectedPen);
    else
        oldPen = dc.SelectObject(&normalPen);

    // 카드 외곽 테두리 그리기
    dc.Rectangle(cardRect);

    // 사용이 끝난 뒤 원래 펜으로 복구
    // GDI 객체 선택 후에는 복구 습관이 중요하다.
    dc.SelectObject(oldPen);

    // 카드 높이의 절반 지점 계산
    // 이 지점을 기준으로 상단 이미지 / 하단 텍스트 영역을 나눈다.
    int halfY = cardRect.top + cardRect.Height() / 2;

    // 카드 상단 절반 = 이미지 영역
    CRect imageRect = cardRect;
    imageRect.bottom = halfY;

    // 카드 하단 절반 = 텍스트 영역
    CRect textRect = cardRect;
    textRect.top = halfY;

    // 상단/하단 구분선 그리기
    dc.MoveTo(cardRect.left, halfY);
    dc.LineTo(cardRect.right, halfY);

    // 이미지가 너무 테두리에 붙지 않도록 안쪽 여백을 준다.
    CRect innerImageRect = imageRect;
    innerImageRect.DeflateRect(10, 10);

    // 실제 말 이미지를 상단 영역에 그림
    DrawSingleHorseImage(dc, innerImageRect, horse);

    // 텍스트도 카드 경계에 너무 붙지 않도록 여백 적용
    CRect innerTextRect = textRect;
    innerTextRect.DeflateRect(8, 8);

    // 화면에 출력할 최종 문자열 구성
    // 이름 + 빈 줄 + 설명
    CString info;
    info.Format(_T("%s\r\n\r\n%s"), (LPCTSTR)name, (LPCTSTR)desc);

    // 카드 하단 영역에 텍스트 출력
    // DT_LEFT      : 왼쪽 정렬
    // DT_TOP       : 위쪽부터 출력
    // DT_WORDBREAK : 영역 너비를 넘으면 자동 줄바꿈
    dc.DrawText(info, innerTextRect, DT_LEFT | DT_TOP | DT_WORDBREAK);
}


// 카드 상단 이미지 영역 안에 말 이미지를 출력하는 함수
void CHorseSelectDlg::DrawSingleHorseImage(CDC& dc, const CRect& imageRect, Horse* horse)
{
    // 말 객체가 없으면 그릴 수 없으므로 종료
    if (!horse)
        return;

    // Horse 객체 내부에 저장된 이미지 참조
    CImage& img = horse->GetHorseImage();

    // 이미지가 비어 있으면 종료
    // 예: Load 실패
    if (img.IsNull())
        return;

    // 원본 이미지 크기
    int originalW = img.GetWidth();
    int originalH = img.GetHeight();

    // 잘못된 이미지 방지
    if (originalW <= 0 || originalH <= 0)
        return;

    // imageRect 가로에 맞출 배율
    double scaleX = (double)imageRect.Width() / (double)originalW;

    // imageRect 세로에 맞출 배율
    double scaleY = (double)imageRect.Height() / (double)originalH;

    // 둘 중 더 작은 값을 사용해야 이미지가 영역 밖으로 넘치지 않고
    // 가로세로 비율도 유지된다.
    double scale = (scaleX < scaleY) ? scaleX : scaleY;

    // 최종 출력 크기 계산
    int drawW = (int)(originalW * scale);
    int drawH = (int)(originalH * scale);

    // 이미지가 영역 정중앙에 오도록 좌표 계산
    int drawX = imageRect.left + (imageRect.Width() - drawW) / 2;
    int drawY = imageRect.top + (imageRect.Height() - drawH) / 2;

    // 실제 이미지 출력
    img.Draw(dc.m_hDC, drawX, drawY, drawW, drawH);
}


// 마우스 왼쪽 버튼 클릭 처리 함수
void CHorseSelectDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
    // 저장해 둔 모든 카드 사각형을 순회하면서
    // 클릭 좌표(point)가 어느 카드 안에 들어있는지 검사한다.
    for (int i = 0; i < (int)HorseCardRects.size(); ++i)
    {
        // PtInRect(point)
        // -> point가 현재 사각형 안에 포함되면 true
        if (HorseCardRects[i].PtInRect(point))
        {
            // 클릭된 카드 번호를 선택 카드 번호로 저장
            SelectedCardIndex = i;

            // 화면 다시 그리기 요청
            // 그러면 OnPaint()가 다시 실행되고,
            // 선택된 카드만 빨간 테두리로 표시된다.
            Invalidate();

            // 이미 클릭된 카드를 찾았으므로 반복 종료
            break;
        }
    }

    // 부모 클래스에도 클릭 메시지 전달
    CDialogEx::OnLButtonDown(nFlags, point);

    GetDlgItem(SelectButton)->ShowWindow(SW_SHOW);  // 말을 하나 선택하고 나면 결정 버튼 보이기
}


// 메시지 맵
// 윈도우 메시지와 멤버 함수 연결
BEGIN_MESSAGE_MAP(CHorseSelectDlg, CDialogEx)
    // 화면 다시 그리기 메시지 -> OnPaint 호출
    ON_WM_PAINT()

    // 마우스 왼쪽 버튼 클릭 메시지 -> OnLButtonDown 호출
    ON_WM_LBUTTONDOWN()
    ON_BN_CLICKED(SelectButton, &CHorseSelectDlg::OnBnClickedSelectbutton)
END_MESSAGE_MAP()


void CHorseSelectDlg::OnBnClickedSelectbutton()
{
    if (!Player)
    {
        return;
    }

    // 선택한 말 포인터를 Player에게 전달
    Player->SetSelectHorse(Horses[SelectedCardIndex].get());

    CHorseRacingDlg* pMain = (CHorseRacingDlg*)GetParent();

    if (pMain)	// 부모의 주소창이 제대로 있으면 실행
    {
        this->ShowWindow(SW_HIDE);
        pMain->ShowReadyPage();
    }
}

void CHorseSelectDlg::HideSelectButton()
{
    GetDlgItem(SelectButton)->ShowWindow(SW_HIDE);  // 결정 버튼 숨김
}

#pragma once

// std::unique_ptr 사용을 위해 필요한 헤더
// unique_ptr는 동적 할당한 객체를 자동으로 삭제해 주는 스마트 포인터이다.
#include <memory>

// std::vector 사용을 위해 필요한 헤더
// vector는 크기가 가변적인 배열이다.
#include <vector>

// Horse 부모 클래스 선언이 들어있는 헤더
#include "Horse.h"

// CHorseSelectDlg
// 말 선택 화면을 담당하는 다이얼로그 클래스
// 이 클래스는 독립 실행 창이 아니라,
// 부모 다이얼로그(CHorseRacingDlg) 내부에 자식 페이지처럼 생성되어 사용된다.
class CHorseSelectDlg : public CDialogEx
{
	// MFC의 런타임 클래스 정보 기능을 사용하기 위한 매크로
	// 동적 생성, 타입 검사 등에 사용된다.
	DECLARE_DYNAMIC(CHorseSelectDlg)

public:

	// 생성자
	// pParent : 부모 윈도우 주소
	// 보통 메인 다이얼로그(CHorseRacingDlg)가 전달된다.
	CHorseSelectDlg(CWnd* pParent = nullptr);

#ifdef AFX_DESIGN_TIME
	// 이 다이얼로그가 사용할 리소스 ID
	// 리소스 에디터에서 만든 다이얼로그와 연결된다.
	enum { IDD = IDD_HORSE_SELECT_DIALOG };
#endif

protected:
	// MFC의 데이터 교환 함수
	// 컨트롤과 변수 연결(DDX/DDV)에 사용된다.
	// 지금은 별도로 연결한 컨트롤이 없어도 기본 형식으로 유지한다.
	virtual void DoDataExchange(CDataExchange* pDX);

	// 다이얼로그 초기화 함수
	// Create 이후 실제 화면이 준비될 때 한 번 호출된다.
	// 초기값 설정, 폰트 설정, 버튼 숨김/표시 등에 자주 사용된다.
	BOOL OnInitDialog() override;

	// 메시지 맵 선언
	// ON_WM_PAINT(), ON_WM_LBUTTONDOWN() 같은 메시지 연결에 필요하다.
	DECLARE_MESSAGE_MAP()

private:
	// 선택창에 표시할 말 객체 목록
	// Horse는 부모 클래스이고, NormalHorse 같은 자식 객체를 담기 위해
	// unique_ptr<Horse> 형태로 저장한다.
	//
	// 왜 unique_ptr를 쓰는가?
	// 1. new/delete를 직접 하지 않아도 자동 메모리 해제 가능
	// 2. 다형성 사용 가능 (부모 포인터로 자식 객체 관리)
	// 3. vector 안에 안전하게 저장 가능
	std::vector<std::unique_ptr<Horse>> Horses;

	// 각 카드의 화면상 위치(사각형 영역)를 저장하는 배열
	//
	// 이게 왜 필요한가?
	// 사용자가 마우스로 클릭했을 때
	// "지금 클릭한 좌표가 몇 번째 카드 안에 들어 있는가?"
	// 를 판단하기 위해 필요하다.
	//
	// OnPaint()에서 카드를 그릴 때 각 카드의 위치를 저장해 두고,
	// OnLButtonDown()에서 그 좌표를 검사한다.
	std::vector<CRect> HorseCardRects;

	// 현재 선택된 카드 번호
	//
	// 예:
	// -1 : 아무 카드도 선택되지 않음
	//  0 : 첫 번째 카드 선택
	//  1 : 두 번째 카드 선택
	//  ...
	//
	// OnLButtonDown()에서 값이 바뀌고,
	// OnPaint()에서 이 값을 보고 빨간 테두리를 그릴지 결정한다.
	int SelectedCardIndex = -1;

	// 카드 하나를 그리는 함수
	//
	// dc          : 그림을 그릴 디바이스 컨텍스트
	// cardRect    : 카드 전체 영역
	// horse       : 이 카드에 표시할 말 객체
	// name        : 카드에 표시할 말 이름
	// desc        : 카드에 표시할 설명 문자열
	// isSelected  : 현재 이 카드가 선택된 상태인지 여부
	//
	// 이 함수 안에서
	// - 카드 배경
	// - 카드 테두리
	// - 상단 이미지 영역
	// - 하단 텍스트 영역
	// 을 모두 그린다.
	void DrawHorseCard(CDC& dc, const CRect& cardRect, Horse* horse, const CString& name, const CString& desc, bool isSelected);

	// 카드 상단 이미지 영역에 말 그림을 그리는 함수
	//
	// dc        : 그림을 그릴 디바이스 컨텍스트
	// imageRect : 이미지를 배치할 사각형 영역
	// horse     : 그림을 가져올 말 객체
	//
	// 이 함수는 원본 이미지 크기에 상관없이
	// imageRect 안에 비율을 유지한 채 알맞게 맞춰서 그림을 출력한다.
	void DrawSingleHorseImage(CDC& dc, const CRect& imageRect, Horse* horse);

	class PlayerUser* Player = nullptr;

public:
	// WM_PAINT 메시지가 들어왔을 때 호출되는 함수
	// 화면 전체를 직접 그리는 역할을 한다.
	//
	// 여기서 하는 일:
	// 1. 전체 창 크기 계산
	// 2. 카드 5개 위치 계산
	// 3. 카드 위치 저장
	// 4. 카드 하나씩 그리기
	afx_msg void OnPaint();

	// 마우스 왼쪽 버튼 클릭 처리 함수
	//
	// 사용자가 카드 위를 클릭하면
	// 어떤 카드가 클릭됐는지 검사해서
	// SelectedCardIndex를 바꾸고 다시 그리기를 요청한다.
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	afx_msg void OnBnClickedSelectbutton();

	inline void SetPlayer(PlayerUser* Player) { this->Player = Player; }

	void HideSelectButton();
};
